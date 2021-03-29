/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanTp.c  
*
* @brief  UDS transport layer protocol.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/25    CODER1     N/A           Original
*     1.1      2018/06/26    YCH        N/A           Original 
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "CanTp.h"
#include "CanTp_Cbk.h"
#include "CanTp_Cfg.h"

/************************************************************************************
* Internal data types and structures
*************************************************************************************/

/* ************************************************************ */
/* Rx-status (RAM)                                              */
/* ************************************************************ */
typedef struct
{
    uint8                   ChannelState;/* activation status */
    uint16                  Timer;
    PduInfoType             RxNPduInfo;
    PduLengthType           DataIndex;  /* Lengths */
    PduLengthType           DataLength;
    PduLengthType           FrameIndex;
    PduLengthType           AvailableBufLength;
    uint8                   WFTCounter;
    uint8                   BlockSizeCounter;  /* actual values */
    uint8                   BlockSize;
    uint8                   STMin;
    uint16_least            FlowStatus:4;
    uint16_least            ExpectedSN:4;
} CanTp_RxStateType;

/* ************************************************************ */
/* Tx-status (RAM)                                              */
/* ************************************************************ */
typedef struct
{
    uint8                   ChannelState;
    uint16                  Timer;
    PduInfoType             TxNPduInfo;
    PduLengthType           DataIndex;
    PduLengthType           DataLength;
    PduLengthType           FrameIndex;
    PduLengthType           RemainTxDataCnt;
    PduLengthType           PaddingLength;
    uint8                   BlockSizeCounter;
    uint8                   STMin;
    uint16_least            SeqNumber:4;
    uint16_least            Res:4;
} CanTp_TxStateType;


/************************************************************************************
* Global Data definitions
*************************************************************************************/
uint8 CanTp_RxBuf[CANTP_NUM_RX_CHANNELS][CANTP_MAX_FRAME_LENGTH];/* Buffer to receive CanTp-frames */
uint8 CanTp_TxBuf[CANTP_NUM_TX_CHANNELS][CANTP_MAX_FRAME_LENGTH];/* Buffer to store fragments when Tx-buffer is provided in slices */
/* Channel-, connection-administration data */
CanTp_RxStateType CanTp_RxState[CANTP_NUM_RX_CHANNELS];
CanTp_TxStateType CanTp_TxState[CANTP_NUM_TX_CHANNELS];
uint8  RxFormatOffset[CANTP_NUM_RX_CHANNELS];
uint8  TxFormatOffset[CANTP_NUM_TX_CHANNELS];
CanTp_AdminDataType CanTp_AdminData;

/************************************************************************************
* Local Data definitions
*************************************************************************************/
static uint8 TempFcMsg[CANTP_MAX_FRAME_LENGTH];

/************************************************************************************
* Prototypes of internal functions
*************************************************************************************/
static void CanTp_RxMainFunction(PduIdType CanTpRxSduId);
static void CanTp_TxMainFunction(PduIdType CanTpTxSduId);
static void CanTp_RxSFPdu(PduIdType CanTpRxPduId,uint8* SFDataBuf,uint8 CanDlc);
static void CanTp_RxFFPdu(PduIdType CanTpRxPduId,uint8* FFDataBuf,uint8 CanDlc);
static void CanTp_RxCFPdu(PduIdType CanTpRxPduId,uint8* CFDataBuf,uint8 CanDlc);
static void CanTp_RxFCPdu(PduIdType CanTpTxPduId,uint8* FCDataBuf,uint8 CanDlc);
static void CanTp_AssembleFC(PduIdType CanTpRxPduId,uint8 FlowStatus);
static void CanTp_DataCopy( uint8* dest, uint8* src,uint16 cnt);


/* BEGIN_FUNCTION_HDR
*************************************************************************************
* Function Name: CanTp_ChannelInit
* Description: This function initializes the CanTp module
*   
* Inputs:
*         tpChannelType: Tx or Rx Tp Channel
*         tpChannel:     The number ofTp Channel
* Outputs:
*         None.
* Limitations:
*         None.
*************************************************************************************
 END_FUNCTION_HDR*/
 void CanTp_ChannelInit(CanTpChannelType tpChannelType,PduIdType tpChannel)
{
    /******* RX *******/
    CanTp_CanInterruptDisable();
    if(tpChannelType==CANTP_RX_CHANNEL)
    {
        if((CANTP_RX_ADDRESSING_FORMAT(tpChannel) == CANTP_EXTENDED)||
           (CANTP_RX_ADDRESSING_FORMAT(tpChannel) == CANTP_MIXED))
        {
            RxFormatOffset[tpChannel]=1;
        }
        else
        {
            RxFormatOffset[tpChannel]=0;
        }
  /* activation status */
        CanTp_RxState[tpChannel].Timer=0;
        CanTp_RxState[tpChannel].ChannelState=cCanTpRxState_Idle;
        CanTp_RxState[tpChannel].RxNPduInfo.SduDataPtr=&CanTp_RxBuf[tpChannel][0];
        CanTp_RxState[tpChannel].RxNPduInfo.SduLength=0;
  /* Lengths */
        CanTp_RxState[tpChannel].DataIndex=0;
        CanTp_RxState[tpChannel].DataLength=0;
        CanTp_RxState[tpChannel].FrameIndex=0;
  /* buffer admin */
        CanTp_RxState[tpChannel].AvailableBufLength=0;
        CanTp_RxState[tpChannel].WFTCounter=0;
  /* actual values */
        CanTp_RxState[tpChannel].BlockSizeCounter=0;
        CanTp_RxState[tpChannel].BlockSize=CANTP_BS(tpChannel);
        CanTp_RxState[tpChannel].STMin=CANTP_STMIN(tpChannel);
  /* Bittypes */
        CanTp_RxState[tpChannel].ExpectedSN=0;
    }
      /******* TX **********/
    else /*CANTP_TX_CHANNEL*/
    {
        if((CANTP_TX_ADDRESSING_FORMAT(tpChannel) == CANTP_EXTENDED)||
           (CANTP_TX_ADDRESSING_FORMAT(tpChannel) == CANTP_MIXED))
        {
            TxFormatOffset[tpChannel]=1;
        }
        else
        {
            TxFormatOffset[tpChannel]=0;
        }
  /* activation status */
        CanTp_TxState[tpChannel].Timer=0;
        CanTp_TxState[tpChannel].ChannelState=cCanTpTxState_Idle;
        CanTp_TxState[tpChannel].TxNPduInfo.SduDataPtr=&CanTp_TxBuf[tpChannel][0];
        CanTp_TxState[tpChannel].TxNPduInfo.SduLength=0;
  /* Lengths */
        CanTp_TxState[tpChannel].DataIndex=0;
        CanTp_TxState[tpChannel].DataLength=0;
        CanTp_TxState[tpChannel].RemainTxDataCnt=0;
        CanTp_TxState[tpChannel].FrameIndex=0;
  /* actual values */
        CanTp_TxState[tpChannel].BlockSizeCounter=0;
        CanTp_TxState[tpChannel].STMin=0;
  /* Bittypes */
        CanTp_TxState[tpChannel].SeqNumber=0;
    }
    CanTp_CanInterruptRestore();
}

/* BEGIN_FUNCTION_HDR
********************************************************************************************
* Function Name: CanTp_Init
* Description:
*         This function initializes the CanTp module.
* Inputs:
*         CfgPtr: Pointer to the CanTp post-build configuration data.
* Outputs:
*         None.
* Limitations:
********************************************************************************************
 END_FUNCTION_HDR*/

void CanTp_Init(const void* const pCfgPtr)
{  
    uint8  i = 0;
    uint8  tpChannel;
    CanTp_AdminData.CfgPtr=pCfgPtr;
    
    dDiag_vCanIfInit();
    
    for(i=0;i<CANTP_MAX_FRAME_LENGTH;i++)
    {
       TempFcMsg[i] = 0;	
    }
    
    
    if(CanTp_AdminData.InternalState==CANTP_OFF)
    {
        CanTp_AdminData.InternalState=CANTP_ON;
    }
    else
    {
    	
    }
    /***** RX *********************************************************************/
    for (tpChannel=0;tpChannel<(uint8)CANTP_NUM_RX_CHANNELS;  tpChannel++)
    {
        (void)CanTp_ChannelInit(CANTP_RX_CHANNEL,tpChannel);
    }
    /***** TX *********************************************************************/
    for (tpChannel=0;tpChannel<(uint8)CANTP_NUM_TX_CHANNELS;  tpChannel++)
    {
        (void)CanTp_ChannelInit(CANTP_TX_CHANNEL,tpChannel);
    }
    
    CanTp_RxBuf[0][0] = 0;
    CanTp_RxBuf[1][0] = 0;
    CanTp_TxBuf[0][0] = 0;
}

/* BEGIN_FUNCTION_HDR
*********************************************************************************************
* Function Name:CanTp_Shutdown
* Description:
*          This function is called to shutdown the CanTp module.
* Inputs:
*          None.
* Outputs:
*          None.
* Limitations:
*          None.
*********************************************************************************************
 END_FUNCTION_HDR*/
void CanTp_Shutdown(void)
{
    CanTp_Init(CanTp_AdminData.CfgPtr);
    CanTp_AdminData.InternalState=CANTP_OFF;
}

/* BEGIN_FUNCTION_HDR
*********************************************************************************************
* Function Name:CanTp_Transmit
* Description:
*        This service is used to request the transfer of segmented data.
*
* Inputs:
*        CanTpTxSduId: This parameter contains the unique CanTp module identifier of
*                      the CAN N-SDU to be transmitted.
*                      Range: 0..(maximum number of L-PDU IDs received ) - 1
*        CanTpTxInfoPtr: An indicator of a structure with CAN N-SDU related data:
*                        indicator of a CAN N-SDU buffer and the length of this buffer.
* Outputs:
*   None.
* Limitations:
*   None.
*********************************************************************************************
END_FUNCTION_HDR*/
Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* pData)
{
    uint8 i;
    Std_ReturnType  ErrorStatus=E_OK;
    PduInfoType CanTpTxNPduInfo;
    PduIdType CanTpRxSduId;

    CanTpRxSduId =CanTpTxSduId; /*Input parameter is the received SDU ID*/
    CanTpTxSduId=RX_TO_TX_CHANNEL(CanTpRxSduId);/*the received SDU ID is mapped to transmeted SDU ID*/
  /*******************************************************************************
  * Protocol checks
  *******************************************************************************/
    if (pData->SduLength <CANTP_TX_DL(CanTpTxSduId)) /*N-SDU length less than the minimum data length.*/
    {
        CanTp_TxState[CanTpTxSduId].Timer=0;
        CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_Idle;
        CanTp_NUSDataConfirm(CanTpTxSduId,NTFRSLT_E_NOT_OK );/* inform application NTFRSLT_E_NOT_OK.*/
    }
    else if((pData->SduLength > TX_SF_DataLength(CanTpTxSduId))
        &&(CANTP_TX_TA_TYPE(CanTpTxSduId)==CANTP_FUNCTIONAL))
    {
        CanTp_TxState[CanTpTxSduId].Timer=0;
        CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_Idle;
        CanTp_NUSDataConfirm(CanTpTxSduId,NTFRSLT_E_CAN_WRONG_FFTATYPE );/* inform application .*/
    }
  /*******************************************************************************
  * Check if the same connection (not tpChannel) is currently running
  *******************************************************************************/
    else if((CanTp_TxState[CanTpTxSduId].ChannelState!= cCanTpTxState_Idle)
#if(CANTP_CHANNEL_MODE==CANTP_MODE_HALF_DUPLEX)
     || (CanTp_RxState[CanTpRxSduId].ChannelState!= cCanTpRxState_Idle)/*Check status of the related Rx channel*/
#endif
    )
    {
        ErrorStatus=E_NOT_OK;/* Transmission in progress - return busy  */
    }
    else
    {
        /*******************************************************************************
        * check and modify state and timer
        *******************************************************************************/
        if(pData->SduLength <= TX_SF_DataLength(CanTpTxSduId))
        {     /*(0)1 to 6/7 bytes will be a SingleFrame*/
            CanTp_TxState[CanTpTxSduId].ChannelState = cCanTpTxState_WaitForSFConf;
            CanTp_TxState[CanTpTxSduId].FrameIndex=0;
            CanTp_TxState[CanTpTxSduId].DataLength=pData->SduLength;
            CanTp_TxBuf[CanTpTxSduId][TX_TPCI_OFFSET(CanTpTxSduId)]=(uint8)pData->SduLength;
            CanTpTxNPduInfo.SduDataPtr=&CanTp_TxBuf[CanTpTxSduId][TX_SF_OFFSET(CanTpTxSduId)];
            CanTpTxNPduInfo.SduLength=pData->SduLength;
            if(CANTP_TX_PADDING_ACTIVATION(CanTpTxSduId)==CANTP_ON)
            {
                CanTp_TxState[CanTpTxSduId].TxNPduInfo.SduLength=CANTP_MAX_FRAME_LENGTH;
                CanTp_TxState[CanTpTxSduId].PaddingLength =(uint8)(TX_SF_DataLength(CanTpTxSduId)-(uint8)pData->SduLength);
                for (i=(uint8)(CANTP_MAX_FRAME_LENGTH-CanTp_TxState[CanTpTxSduId].PaddingLength);i<CANTP_MAX_FRAME_LENGTH;i++)
                {
                    CanTp_TxBuf[CanTpTxSduId][i]=CANTP_FILLPATTERN;
                }
            }
            else
            {
                CanTp_TxState[CanTpTxSduId].TxNPduInfo.SduLength=pData->SduLength+1+(uint16)TX_TPCI_OFFSET(CanTpTxSduId);
            }
        }
        else
        {
            CanTp_TxState[CanTpTxSduId].ChannelState = cCanTpTxState_WaitForFFConf;
            CanTp_TxState[CanTpTxSduId].DataLength=pData->SduLength;
            CanTp_TxState[CanTpTxSduId].RemainTxDataCnt=pData->SduLength;
            CanTp_TxState[CanTpTxSduId].DataIndex=0;
            CanTp_TxState[CanTpTxSduId].FrameIndex=(uint16)(pData->SduLength/TX_CF_DataLength(CanTpTxSduId));  /* Correct calculation means txSEG=(count-6+6)/7 or (count-5+5)/6 */
            if(CANTP_TX_PADDING_ACTIVATION(CanTpTxSduId)==CANTP_ON)
            {
                CanTp_TxState[CanTpTxSduId].PaddingLength = (uint8)((CanTp_TxState[CanTpTxSduId].FrameIndex*TX_CF_DataLength(CanTpTxSduId))-(pData->SduLength-TX_FF_DataLength(CanTpTxSduId)));
            }
            CanTp_TxState[CanTpTxSduId].TxNPduInfo.SduLength=CANTP_MAX_FRAME_LENGTH;
            CanTp_TxState[CanTpTxSduId].SeqNumber=cCanTpSNStartValue;
            CanTp_TxBuf[CanTpTxSduId][TX_TPCI_OFFSET(CanTpTxSduId)]=(cCanTp_FF)|(uint8)(pData->SduLength >> 8);
            CanTp_TxBuf[CanTpTxSduId][TX_DL_OFFSET(CanTpTxSduId)]=(uint8)pData->SduLength;
            CanTpTxNPduInfo.SduDataPtr=&CanTp_TxBuf[CanTpTxSduId][TX_FF_OFFSET(CanTpTxSduId)];
            CanTpTxNPduInfo.SduLength=TX_FF_DataLength(CanTpTxSduId);
        }
        CanTp_TxState[CanTpTxSduId].Timer = CANTP_NAS(CanTpTxSduId);
      /*******************************************************************************
      * start transmission
      *******************************************************************************/
        (void)CanTp_CopyTxData(CanTpTxSduId,&CanTpTxNPduInfo,NULL_PTR,&CanTp_TxState[CanTpTxSduId].RemainTxDataCnt);

        if(CANTP_TX_ADDRESSING_FORMAT(CanTpTxSduId)==CANTP_EXTENDED)/*Addressing Format is Extended */
        {
            CanTp_TxBuf[CanTpTxSduId][TARGET_OFFSET]=CANTP_TX_NTA(CanTpTxSduId);/*Target Address */
        }
        else if(CANTP_TX_ADDRESSING_FORMAT(CanTpTxSduId)==CANTP_MIXED)/*Addressing Format is Mixed */
        {
            CanTp_TxBuf[CanTpTxSduId][AE_OFFSET]=CANTP_TX_NAE(CanTpTxSduId);/*Extended Address */
        }
        else /*Addressing Format is Standard */
        {
        }
        if(CanTp_CanTransmit(CanTpTxSduId,&CanTp_TxState[CanTpTxSduId].TxNPduInfo)!=E_OK)
        {
            CanTp_TxState[CanTpTxSduId].ChannelState|=cCanTpState_Retransmit;
        }
        else
        {
        	
        }
    }
    return ErrorStatus;
}

/* BEGIN_FUNCTION_HDR
******************************************************************************************************
* Function Name:CanTp_RxIndication
* Description:
*    This function is called by the CAN Interface after a successful reception of a Rx CAN L-PDU.
* Inputs:
*    CanTpRxPduId: ID of CAN L-PDU that has been received. Identifies the data that has been received.
*           Range: 0..(maximum number of L-PDU IDs received ) - 1
* CanTpRxPduPtr: Indicator of structure with received L-SDU (payload) and data length.
* Outputs:
*          None.
* Limitations:
*    CANTP235: The function CanTp_RxIndication shall be callable in interrupt context 
*    (it could be called from the CAN receive interrupt).
******************************************************************************************************
 END_FUNCTION_HDR*/
void CanTp_RxIndication(PduIdType CanTpRxPduId, const PduInfoType* pCanTpRxPduPtr)
{
    Std_ReturnType  ErrorStatus=E_OK;

    CanTp_CanInterruptDisable();

    CanTp_DataCopy(&CanTp_RxBuf[CanTpRxPduId][0], pCanTpRxPduPtr->SduDataPtr,pCanTpRxPduPtr->SduLength);
    if(CANTP_RX_ADDRESSING_FORMAT(CanTpRxPduId)==CANTP_EXTENDED)/*Addressing Format is Extended */
    {
        if(CanTp_RxBuf[CanTpRxPduId][TARGET_OFFSET]!=CANTP_RX_NTA(CanTpRxPduId))/*Check Target Address */
        {
            ErrorStatus=E_NOT_OK;
        }
        else
        {
        }
    }
    else if(CANTP_RX_ADDRESSING_FORMAT(CanTpRxPduId)==CANTP_MIXED)/*Addressing Format is Mixed */
    {
        if(CanTp_RxBuf[CanTpRxPduId][AE_OFFSET]!=CANTP_RX_NAE(CanTpRxPduId)) /*Check Extend Address */
        {
            ErrorStatus=E_NOT_OK;
        }
        else
        {
        }
    }
    else
    {
    }
    if(ErrorStatus==E_OK)
    {
        switch(CanTp_RxBuf[CanTpRxPduId][RX_TPCI_OFFSET(CanTpRxPduId)] & cCanTp_FrameTypeMask)
        {
            case cCanTp_SF:
            {
                CanTp_RxSFPdu(CanTpRxPduId,CanTp_RxBuf[CanTpRxPduId],(uint8)pCanTpRxPduPtr->SduLength);/*Receive SingleFrame*/
            }
            break;
            case cCanTp_FF:
            {
                CanTp_RxFFPdu(CanTpRxPduId,CanTp_RxBuf[CanTpRxPduId],(uint8)pCanTpRxPduPtr->SduLength); /*Receive FirstFrame*/
            }
            break;
            case cCanTp_CF:
            {
                CanTp_RxCFPdu(CanTpRxPduId,CanTp_RxBuf[CanTpRxPduId],(uint8)pCanTpRxPduPtr->SduLength);/*Receive ConsectiveFrame*/
            }
            break;
            case cCanTp_FC:
            {
                CanTp_RxFCPdu(CanTpRxPduId,CanTp_RxBuf[CanTpRxPduId],(uint8)pCanTpRxPduPtr->SduLength);/*Receive FlowControlFrame*/
            }
            break;
            default:
            break;
        }
    }
    else
    {
    }
    CanTp_CanInterruptRestore();
}

/* BEGIN_FUNCTION_HDR
****************************************************************************************************
* Function Name: CanTp_TxConfirmation
* Description:
*     All transmitted CAN frames(SF, FF, CF, FC) belonging to the CAN Transport Layer
*     will be confirmed by this function.
* Inputs:
*       CanTpTxPduId: ID of CAN L-PDU that has been transmitted.
*          Range: 0..(maximum number of L-PDU IDs received ) - 1
* Outputs:
*        None.
* Limitations:
*        CANTP236: The function CanTp_TxConfirmation shall be callable in interrupt context
*  (it could be called from the CAN transmit interrupt).
****************************************************************************************************
 END_FUNCTION_HDR*/
void CanTp_TxConfirmation(PduIdType CanIfTxPduId)
{
    PduIdType CanTpRxChannelMaped;
    /*Check if it is the Tx Confirmation of FF,SF,CF N-PDU*/
    if((CanTp_TxState[CanIfTxPduId].ChannelState&cCanTpCanTxStateMask)!= 0)
    {
        switch(CanTp_TxState[CanIfTxPduId].ChannelState&cCanTpCanTxStateMask)
        {
            case cCanTpTxState_WaitForSFConf:
            case cCanTpTxState_WaitForLastCFConf:
            {
                CanTp_TxState[CanIfTxPduId].ChannelState=cCanTpTxState_Idle;
                CanTp_TxState[CanIfTxPduId].Timer=0;
                CanTp_NUSDataConfirm(CanIfTxPduId,NTFRSLT_OK );/* inform application */
            }
            break;
            case cCanTpTxState_WaitForFFConf:
            {
                CanTp_TxState[CanIfTxPduId].DataIndex+=TX_FF_DataLength(CanIfTxPduId);
                CanTp_TxState[CanIfTxPduId].ChannelState=cCanTpTxState_WaitFC;
                CanTp_TxState[CanIfTxPduId].Timer=CANTP_NBS(CanIfTxPduId);
            }
            break;
            case cCanTpTxState_WaitForCFConf:
            {
               CanTp_TxState[CanIfTxPduId].DataIndex+=TX_CF_DataLength(CanIfTxPduId);
               if(CanTp_TxState[CanIfTxPduId].BlockSizeCounter!=0)
               {
                   CanTp_TxState[CanIfTxPduId].BlockSizeCounter--;
                   if(CanTp_TxState[CanIfTxPduId].BlockSizeCounter==0)
                   {
                       CanTp_TxState[CanIfTxPduId].ChannelState=cCanTpTxState_WaitFC;
                       CanTp_TxState[CanIfTxPduId].Timer=CANTP_NBS(CanIfTxPduId);
                   }
                   else
                   {
                       CanTp_TxState[CanIfTxPduId].ChannelState=cCanTpTxState_WaitForTpTxCF;
                       CanTp_TxState[CanIfTxPduId].Timer=CanTp_TxState[CanIfTxPduId].STMin;
                   }
               }
               else
               {
                    CanTp_TxState[CanIfTxPduId].ChannelState=cCanTpTxState_WaitForTpTxCF;
                    CanTp_TxState[CanIfTxPduId].Timer=CanTp_TxState[CanIfTxPduId].STMin;
               }
            }
            break;
            default:
            break;
        }
    }
    else
#if(CANTP_CHANNEL_MODE!=CANTP_MODE_HALF_DUPLEX)
    {

    }
#else
    {
#endif
      /*Check if it is the Tx Confirmation of FC N-PDU*/
    CanTpRxChannelMaped=CANTP_RXFC_NPDU_ID(CanIfTxPduId);
    if((CanTp_RxState[CanTpRxChannelMaped].ChannelState&cCanTpCanTxStateMask)!= 0)
    {
        switch(CanTp_RxState[CanTpRxChannelMaped].ChannelState&cCanTpCanTxStateMask)
        {
            case cCanTpRxState_WaitForFCConf:
            {
                CanTp_RxState[CanTpRxChannelMaped].ChannelState=cCanTpRxState_WaitCF;
                CanTp_RxState[CanTpRxChannelMaped].Timer=CANTP_NCR(CanTpRxChannelMaped);
            }
            break;
            case cCanTpRxState_WaitForFCWaitConf:
            {
                CanTp_RxState[CanTpRxChannelMaped].WFTCounter++;
                if(CanTp_RxState[CanTpRxChannelMaped].WFTCounter==CANTP_WFTMAX(CanTpRxChannelMaped))/*CANTP223*/
                {
                    CanTp_RxState[CanTpRxChannelMaped].ChannelState=cCanTpRxState_Idle;
                    CanTp_RxState[CanTpRxChannelMaped].Timer=0;
                    CanTp_NUSDataIndication(CanTpRxChannelMaped,NTFRSLT_E_WFT_OVRN);
                }
                else
                {
                    CanTp_RxState[CanTpRxChannelMaped].ChannelState=cCanTpRxState_WaitForRxBuffer;
                    CanTp_RxState[CanTpRxChannelMaped].Timer=CANTP_NBR(CanTpRxChannelMaped);
                }
            }
            break;
            case cCanTpRxState_WaitForFCOverConf:
            {
                CanTp_RxState[CanTpRxChannelMaped].ChannelState=cCanTpRxState_Idle;
                CanTp_RxState[CanTpRxChannelMaped].Timer=0;
            }
            break;
            default:
            break;
        }
    }
    else
    {
    }
#if(CANTP_CHANNEL_MODE==CANTP_MODE_HALF_DUPLEX)
    }
#endif
}

/* BEGIN_FUNCTION_HDR
*****************************************************************************************************
* Function Name:CanTp_MainFunction
* Description:
*   The main function for scheduling the CAN TP.
* Inputs:
*   None.
* Outputs:
*   None.
* Limitations:
*       CANTP164: The main function for scheduling the CAN TP (Entry point for scheduling)
*        The main function will be called by the Schedule Manager or by the Free Running
*       Timer module according of the call period needed. CanTp_MainFunction is involved
*       in handling of CAN TP timeouts N_As, N_Bs, N_Cs, N_Ar, N_Br,N_Cr and STMmin.
*       CANTP300: The function CanTp_MainFunction is affected by configuration
*       parameter CanTpMainFunctionPeriod.
******************************************************************************************************
 END_FUNCTION_HDR*/
void CanTp_MainFunction(void)
{
    PduIdType  CanTpSduId;/*equal to request or response MessageID, fg: 7F0,7DF, 7F1;*/
     /*****Rx Task******************/
    for (CanTpSduId=0;CanTpSduId<CANTP_NUM_RX_CHANNELS;CanTpSduId++)
    {
        CanTp_RxMainFunction(CanTpSduId);
    }
    /*****Tx Task******************/
    for (CanTpSduId=0;CanTpSduId<(uint8)CANTP_NUM_TX_CHANNELS;CanTpSduId++)
    {
        CanTp_TxMainFunction(CanTpSduId);
    }
}

/* BEGIN_FUNCTION_HDR
****************************************************************************************************
* Function Name:CanTp_GetVersionInfo
* Description:
*    This function returns the version information of the CanTp module.
* Inputs:
*   pVersionInfo: Indicator as to where to store the version information of this module.
* Outputs:
*   None.
* Limitations:
*   The function CanTp_GetVersionInfo shall be pre compile time
* configurable (On/Off) by the configuration parameter:CANTP_VERSION_INFO_API.
****************************************************************************************************
 END_FUNCTION_HDR*/

#if (CANTP_VERSION_INFO_API == STD_ON)
void CanTp_GetVersionInfo(Std_VersionInfoType* pVersionInfo)
{
    pVersionInfo->vendorID = CANTP_VENDOR_ID;
    pVersionInfo->moduleID = CANTP_MODULE_ID;
    pVersionInfo->instanceID = 0;
    pVersionInfo->sw_major_version = CANTP_SW_MAJOR_VERSION;
    pVersionInfo->sw_minor_version = CANTP_SW_MINOR_VERSION;
    pVersionInfo->sw_patch_version = CANTP_SW_PATCH_VERSION;
}
#endif

#if (CANTP_TC == STD_ON)
/* BEGIN_FUNCTION_HDR
****************************************************************************************************
* Function Name: CanTp_CancelTransmitRequest
* Description: This service cancels the transmission of an N-SDU that has already
*       requested for transmission by calling CanTp_Transmit service.
* Inputs:
*    CanTpTxSduId: This parameter contains the unique CanTp module identifier of the
*                    N-SDU to be cancelled for transmission.
*           Range: 0..(maximum number of L-PDU IDs transmmited ) - 1.
* Outputs:
*       E_OK: Cancellation request of the specified N-SDU is accepted.
*   E_NOT_OK: Cancellation request is rejected; the reason can be
*            that request is issued for an N-SDU that is not segmented,
*            request is issued after the last CF has been requested for
*            transmission or cancellation is not possible for the related N-SDU
*            due to configuration.
* Limitations:
*   None.
******************************************************************************************************
 END_FUNCTION_HDR*/
Std_ReturnType CanTp_CancelTransmitRequest(PduIdType CanTpTxSduId)
{
    Std_ReturnType result=NTFRSLT_E_CANCELATION_OK;
    if(((CanTp_TxState[CanTpTxSduId].ChannelState&cCanTpInternalStateMask)!=cCanTpTxState_Idle)
      &&((CanTp_TxState[CanTpTxSduId].ChannelState&cCanTpCanTxStateMask)!=cCanTpTxState_WaitForLastCFConf))
    {
        result=CanTp_CanCancelTransmit(CanTpTxSduId);
        CanTp_ChannelInit(CANTP_TX_CHANNEL,CanTpTxSduId);
    }
    else
    {
        result=NTFRSLT_E_CANCELATION_NOT_OK;
    }
    return result;
}
#endif
/* BEGIN_FUNCTION_HDR
***********************************************************************************************************
* Function Name: CanTp_CancelReceiveRequest
* Description:This service is used to cancel the reception of an ongoing N-SDU.
* Inputs:
*    CanTpRxSduId: Identifier of the received N-SDU.
*           Range: 0..(maximum number of L-PDU IDs received ) - 1.
* Outputs:
*    E_OK: Cancellation request of the specified N-SDU is accepted.
*    E_NOT_OK: Cancellation request is rejected; the reason can be
*   that request is issued for an N-SDU that is not segmented or
*   request is issued for an N-SDU that is not in the reception
*   process..
* Limitations:
*    None.
***********************************************************************************************************
 END_FUNCTION_HDR*/
Std_ReturnType CanTp_CancelReceiveRequest(PduIdType CanTpRxSduId)
{
    Std_ReturnType result=NTFRSLT_E_CANCELATION_OK;
    if((CanTp_RxState[CanTpRxSduId].ChannelState&cCanTpInternalStateMask)!=cCanTpRxState_Idle)
    {
        CanTp_ChannelInit(CANTP_RX_CHANNEL,CanTpRxSduId);
    }
    else
    {
        result=NTFRSLT_E_CANCELATION_NOT_OK;
    }
    return result;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************************
* Function Name:
* Description:This service is used to request the change of reception parameters
*      BS and STmin for a specified N-SDU.
* Inputs:
*    id:Identifier of the received N-SDU on which the reception
*        parameter has to be changed.
*    parameter:Specify the parameter to which the value has to be changed (BS
*        or STmin).
*    value:The new value of the parameter.
* Outputs:
*    E_OK: request is accepted.
*    E_NOT_OK: request is not accepted.
* Limitations:
*    CANTP303: A parameter change is only possible if the related N-SDU is not in the
*  process of reception , i.e. a change of parameter value it is not possible after
*  reception of FF until indication for last CF reception of the related N-SDU.
************************************************************************************************************
 END_FUNCTION_HDR*/
Std_ReturnType CanTp_ChangeParameterRequest(PduIdType CanTpSduId,CanTpParameterType parameter,uint16 value)
{
    Std_ReturnType result=NTFRSLT_PARAMETER_OK;
    if((CanTp_RxState[CanTpSduId].ChannelState&cCanTpInternalStateMask)==cCanTpRxState_Idle)
    {
        if(parameter==CANTP_BS_PARAMETER)
        {
            CanTp_RxState[CanTpSduId].BlockSize=(uint8)value;  /*NTFRSLT_E_VALUE_NOT_OK*/
        }
        else /*CANTP_STMIN_PARAMETER*/
        {
            CanTp_RxState[CanTpSduId].STMin=(uint8)value;
        }
    }
    else
    {
        result=NTFRSLT_E_RX_ON;
    }
    return result;
}
/* BEGIN_FUNCTION_HDR
**************************************************************************************************************
* Function Name: CanTp_RxMainFunction
* Description:
     This function is called by CanTp_MainFunction to handl of CAN TP
     timeouts N_Ar, N_Br. N_Cr and STMmin.
* Inputs:
*    CanTpRxSduId:Identifier of the received N-SDU.
* Outputs:
*    None.
* Limitations:
*    None.
**************************************************************************************************************
 END_FUNCTION_HDR*/
static void CanTp_RxMainFunction(PduIdType CanTpRxSduId)
{
    BufReq_ReturnType  BufReqResult;
    if(CanTp_RxState[CanTpRxSduId].Timer!= 0) /* Set a prestate for checking a interrupt while decrementing */
    {
        CanTp_RxState[CanTpRxSduId].Timer--;
        if((CanTp_RxState[CanTpRxSduId].ChannelState & cCanTpState_Retransmit)==cCanTpState_Retransmit)
        {
            if(CanTp_RxState[CanTpRxSduId].Timer== 0)
            {
                CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_Idle;
                CanTp_NUSDataIndication(CanTpRxSduId,NTFRSLT_E_TIMEOUT_A);
            }
            else
            {
                CanTp_AssembleFC(CanTpRxSduId,(uint8)CanTp_RxState[CanTpRxSduId].FlowStatus);/*flow status */
            }
        }
        else if((CanTp_RxState[CanTpRxSduId].ChannelState & cCanTpInternalStateMask) ==cCanTpRxState_WaitForRxBuffer)/*CANTP222*/
        {
            /*Before expiration of the N_Br timer,CanTp call the service to provide an Rx buffer again*/
            BufReqResult=CanTp_CopyRxData(CanTpRxSduId,&CanTp_RxState[CanTpRxSduId].RxNPduInfo,&CanTp_RxState[CanTpRxSduId].AvailableBufLength);
            if(BufReqResult==BUFREQ_OK)
            {
                if(CanTp_RxState[CanTpRxSduId].DataLength>RX_SF_DataLength(CanTpRxSduId)) /*SF or FF */
                {
                    if(CanTp_RxState[CanTpRxSduId].DataIndex<RX_FF_DataLength(CanTpRxSduId))/*CF or FF*/
                    {
                        CanTp_RxState[CanTpRxSduId].DataIndex=RX_FF_DataLength(CanTpRxSduId);/*FF*/
                    }
                    else
                    {
                        CanTp_RxState[CanTpRxSduId].DataIndex+=RX_CF_DataLength(CanTpRxSduId);/*CF*/
                    }
                    if(CanTp_RxState[CanTpRxSduId].AvailableBufLength>=(PduLengthType)(CanTp_RxState[CanTpRxSduId].DataLength-CanTp_RxState[CanTpRxSduId].DataIndex))
                    {
                        CanTp_RxState[CanTpRxSduId].BlockSizeCounter=CANTP_BS(CanTpRxSduId);
                    }
                    else
                    {
                        CanTp_RxState[CanTpRxSduId].BlockSizeCounter=(uint8)(CanTp_RxState[CanTpRxSduId].AvailableBufLength/RX_CF_DataLength(CanTpRxSduId))+1;
                    }
                    CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_WaitForTxFC;/*CANTP224*/
                    CanTp_RxState[CanTpRxSduId].FlowStatus=(uint16)cCanTp_FC_FS_CTS;
                    CanTp_RxState[CanTpRxSduId].Timer=1; /*Transmit FC in the task */
                }
                else  /*SF*/
                {
                    CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_Idle;
                    CanTp_RxState[CanTpRxSduId].Timer=0;
                    CanTp_NUSDataIndication(CanTpRxSduId,NTFRSLT_OK);
                }
            }
            else
            {
                if(CanTp_RxState[CanTpRxSduId].Timer==1)/*Before expiration of the N_Br timer,Send FC Wait*/
                {
                    if(CanTp_RxState[CanTpRxSduId].DataLength>RX_SF_DataLength(CanTpRxSduId))/*Multi Frame,Transmit FC WAIT */
                    {
                        if(CANTP_WFTMAX(CanTpRxSduId)!=0)
                        {
                            CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_WaitForTxFCWait;
                            CanTp_RxState[CanTpRxSduId].FlowStatus=(uint16)cCanTp_FC_FS_Wait;
                        }
                        else
                        {
                            CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_Idle;
                            CanTp_RxState[CanTpRxSduId].Timer=0;
                            CanTp_NUSDataIndication(CanTpRxSduId,NTFRSLT_E_NO_BUFFER );
                        }
                    }
                    else  /*SF*/
                    {
                        CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_Idle;
                        CanTp_RxState[CanTpRxSduId].Timer=0;
                        CanTp_NUSDataIndication(CanTpRxSduId,NTFRSLT_E_NO_BUFFER );
                    }
                }
            }
        }
        else
        {
            if(CanTp_RxState[CanTpRxSduId].Timer==0)/* CF timeout occured, do not notify application now! */
            {
                if((CanTp_RxState[CanTpRxSduId].ChannelState&cCanTpInternalStateMask) == cCanTpRxState_WaitForTxFC)
                {
                	CanTp_RxState[CanTpRxSduId].ChannelState =cCanTpRxState_WaitForFCConf;
                    CanTp_AssembleFC(CanTpRxSduId,cCanTp_FC_FS_CTS);
                    CanTp_RxState[CanTpRxSduId].Timer=CANTP_NAR(CanTpRxSduId);
                }
                else if((CanTp_RxState[CanTpRxSduId].ChannelState&cCanTpInternalStateMask) == cCanTpRxState_WaitForTxFCOverrun)
                {
                    CanTp_AssembleFC(CanTpRxSduId,cCanTp_FC_FS_Overrun);
                    CanTp_RxState[CanTpRxSduId].ChannelState =cCanTpRxState_WaitForFCOverConf;
                    CanTp_RxState[CanTpRxSduId].Timer=CANTP_NAR(CanTpRxSduId);
                }
                else if((CanTp_RxState[CanTpRxSduId].ChannelState&cCanTpInternalStateMask) == cCanTpRxState_WaitForTxFCWait)
                {
                    CanTp_AssembleFC(CanTpRxSduId,cCanTp_FC_FS_Wait);
                    CanTp_RxState[CanTpRxSduId].ChannelState =cCanTpRxState_WaitForFCWaitConf;
                    CanTp_RxState[CanTpRxSduId].Timer=CANTP_NAR(CanTpRxSduId);
                }
                else if((CanTp_RxState[CanTpRxSduId].ChannelState&cCanTpInternalStateMask) == cCanTpRxState_WaitCF)
                {
                    CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_Idle;
                    CanTp_NUSDataIndication(CanTpRxSduId,(uint16)NTFRSLT_E_TIMEOUT_CR); /* Notify application */
                }
                else if((CanTp_RxState[CanTpRxSduId].ChannelState&cCanTpCanTxStateMask)!= 0)
                {
                    CanTp_RxState[CanTpRxSduId].ChannelState=cCanTpRxState_Idle;
                    CanTp_NUSDataIndication(CanTpRxSduId,(uint16)NTFRSLT_E_TIMEOUT_A); /* Notify application */
                }
                else
                {
                }
            }
            else
            {
            }
        }
    }
 }
/* BEGIN_FUNCTION_HDR
****************************************************************************************************************
* Function Name:
* Description:
     This function is called by CanTp_MainFunction to handl of CAN TP
     timeouts N_As, N_Bs, N_Cs.
* Inputs:
*    CanTpTxSduId:Identifier of the Transimmited N-SDU.
* Outputs:
*    None.
* Limitations:
*    None.
****************************************************************************************************************
 END_FUNCTION_HDR*/
static void CanTp_TxMainFunction(PduIdType CanTpTxSduId)
{
    Std_ReturnType CanTxReturn=E_OK;
    PduInfoType CanTpTxNPduInfo;
    uint8 i;
    if(CanTp_TxState[CanTpTxSduId].Timer!= 0) /* Set a prestate for checking a interrupt while decrementing */
    {
        CanTp_TxState[CanTpTxSduId].Timer--;
        if((CanTp_TxState[CanTpTxSduId].ChannelState & cCanTpState_Retransmit)==cCanTpState_Retransmit)
        {
            if(CanTp_TxState[CanTpTxSduId].Timer== 0)
            {
                CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_Idle;
                CanTp_TxState[CanTpTxSduId].Timer=0;
                CanTp_NUSDataConfirm(CanTpTxSduId,NTFRSLT_E_TIMEOUT_A );
            }
            else
            {
                (void)CanTp_CanTransmit(CANTP_TXNPDU_ID(CanTpTxSduId),&CanTp_TxState[CanTpTxSduId].TxNPduInfo);
            }
        }
        else
        {
            if(CanTp_TxState[CanTpTxSduId].Timer== 0) /* Set a prestate for checking a interrupt while decrementing */
            {
                switch(CanTp_TxState[CanTpTxSduId].ChannelState&cCanTpInternalStateMask) /*Disabling the interrupt is not necessary  Do Rx stuff even if waiting for confirmation interrupt */
                {
                    case  cCanTpTxState_WaitFC:
                    {
                        CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_Idle;
                        CanTp_TxState[CanTpTxSduId].Timer=0;
                        CanTp_NUSDataConfirm(CanTpTxSduId,NTFRSLT_E_TIMEOUT_BS );
                    }
                    break;
                    case  cCanTpTxState_WaitForTpTxCF:
                    {
                        CanTp_TxState[CanTpTxSduId].FrameIndex--;
                        CanTp_TxBuf[CanTpTxSduId][TX_TPCI_OFFSET(CanTpTxSduId)]=(cCanTp_CF)|(uint8)CanTp_TxState[CanTpTxSduId].SeqNumber;
                        if(CanTp_TxState[CanTpTxSduId].SeqNumber==0x0F)
                        {
                            CanTp_TxState[CanTpTxSduId].SeqNumber=0;
                        }
                        else
                        {
                            CanTp_TxState[CanTpTxSduId].SeqNumber++;
                        }
                        if(CanTp_TxState[CanTpTxSduId].RemainTxDataCnt!=(CanTp_TxState[CanTpTxSduId].DataLength-CanTp_TxState[CanTpTxSduId].DataIndex))
                        {
                            CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_Idle;
                            CanTp_TxState[CanTpTxSduId].Timer=0;
                            CanTp_NUSDataConfirm(CanTpTxSduId,NTFRSLT_E_NOT_OK );
                        }
                        else
                        {
                        }
                        CanTpTxNPduInfo.SduDataPtr=&CanTp_TxBuf[CanTpTxSduId][TX_CF_OFFSET(CanTpTxSduId)];
                        if (CanTp_TxState[CanTpTxSduId].FrameIndex == 0)/*Transmit the last CF*/
                        {
                           CanTpTxNPduInfo.SduLength=CanTp_TxState[CanTpTxSduId].RemainTxDataCnt;
                           CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_WaitForLastCFConf;
                           if(CANTP_TX_PADDING_ACTIVATION(CanTpTxSduId)==CANTP_ON)
                            {
                                CanTp_TxState[CanTpTxSduId].TxNPduInfo.SduLength=CANTP_MAX_FRAME_LENGTH;
                                for (i=(uint8)(CANTP_MAX_FRAME_LENGTH-CanTp_TxState[CanTpTxSduId].PaddingLength);i<CANTP_MAX_FRAME_LENGTH;i++)
                                {
                                    CanTp_TxBuf[CanTpTxSduId][i]=CANTP_FILLPATTERN;
                                }
                            }
                            else
                            {
                                 CanTp_TxState[CanTpTxSduId].TxNPduInfo.SduLength=(uint16)(CanTpTxNPduInfo.SduLength+TX_CF_OFFSET(CanTpTxSduId));
                            }
                        }
                        else
                        {
                            CanTpTxNPduInfo.SduLength=TX_CF_DataLength(CanTpTxSduId);
                            CanTp_TxState[CanTpTxSduId].TxNPduInfo.SduLength=CANTP_MAX_FRAME_LENGTH;
                            CanTp_TxState[CanTpTxSduId].ChannelState=cCanTpTxState_WaitForCFConf;

                        }
                        CanTp_TxState[CanTpTxSduId].Timer=CANTP_NAS(CanTpTxSduId);
                        (void)CanTp_CopyTxData(CanTpTxSduId,&CanTpTxNPduInfo,NULL_PTR,&CanTp_TxState[CanTpTxSduId].RemainTxDataCnt);
                        if(CANTP_TX_ADDRESSING_FORMAT(CanTpTxSduId)==CANTP_EXTENDED)
                        {
                             CanTp_TxBuf[CanTpTxSduId][TARGET_OFFSET]=CANTP_TX_NTA(CanTpTxSduId);
                        }
                        else if(CANTP_TX_ADDRESSING_FORMAT(CanTpTxSduId)==CANTP_MIXED)
                        {
                            CanTp_TxBuf[CanTpTxSduId][AE_OFFSET]=CANTP_TX_NAE(CanTpTxSduId);
                        }
                        else
                        {
                        }
                        CanTxReturn=CanTp_CanTransmit(CANTP_TXNPDU_ID(CanTpTxSduId),&CanTp_TxState[CanTpTxSduId].TxNPduInfo);
                        if(CanTxReturn!=E_OK)
                        {
                            CanTp_TxState[CanTpTxSduId].ChannelState|=cCanTpState_Retransmit;
                        }
                        else
                        {
                        	
                        }
                  
                    }
                    break;
                    default:
                    break;
                }
            }
            else
            {
            }
        }
    }
    else
    {
    }
}
/* BEGIN_FUNCTION_HDR
***************************************************************************************************************
* Function Name: CanTp_RxSFPdu
* Description:
*    This function is called by CanTp_RxIndication after a successful reception of a Rx FF-PDU.
* Inputs:
*   ID of CAN L-PDU that has been received. Identifies the data that has been received.
*   Range: 0..(maximum number of L-PDU IDs received ) - 1
* Outputs:
*   None.
* Limitations:
*   None.
***************************************************************************************************************
 END_FUNCTION_HDR*/
static void CanTp_RxSFPdu(PduIdType CanTpRxPduId,uint8* SFDataBuf,uint8 CanDlc)
{
    BufReq_ReturnType  BufReqResult;
    PduIdType CanTpTxChannelMaped;
    CanTpTxChannelMaped=RX_TO_TX_CHANNEL(CanTpRxPduId);/*Get the related TP Tx Channel */
    if(CanDlc<=(SFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_DLMaskSF))
    {
        /*CAN data link error,abort CAN frame*/
    }
#if(CANTP_CHANNEL_MODE==CANTP_MODE_HALF_DUPLEX)
    else if (CanTp_TxState[CanTpTxChannelMaped].ChannelState!= cCanTpTxState_Idle)
    {
        /*Ignore*/
    }
#endif
    else if(((SFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_DLMaskSF)>RX_SF_DataLength(CanTpRxPduId)) /*check SF Length*/
     ||((SFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_DLMaskSF)<CANTP_RX_DL(CanTpRxPduId)))
    {
        CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
        CanTp_RxState[CanTpRxPduId].Timer=0;
        CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_CAN_WRONG_SFDL);
    }
    else
    {
        if(CanTp_RxState[CanTpRxPduId].ChannelState!=cCanTpRxState_Idle)/* Reception is in progress,wait Tx FC conf*/
        {
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
            CanTp_RxState[CanTpRxPduId].Timer=0;
            CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_UNEXP_PDU);/*Terminate the current reception, report an error indication, with parameter Result set to NTFRSLT_E_UNEXP_PDU, to the upper layer*/
        }
        else
        {
        }
        CanTp_RxState[CanTpRxPduId].DataLength=(uint16)SFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_DLMaskSF;
        CanTp_RxState[CanTpRxPduId].DataIndex=0;
        CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduDataPtr=&SFDataBuf[RX_SF_OFFSET(CanTpRxPduId)];
        CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduLength=SFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)];
        BufReqResult=CanTp_NUSDataSFIndication(CanTpRxPduId,CanTp_RxState[CanTpRxPduId].DataLength,&CanTp_RxState[CanTpRxPduId].AvailableBufLength);
        if(BufReqResult==BUFREQ_OK)
        {
            (void)CanTp_CopyRxData(CanTpRxPduId,&CanTp_RxState[CanTpRxPduId].RxNPduInfo,&CanTp_RxState[CanTpRxPduId].AvailableBufLength);
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
            CanTp_RxState[CanTpRxPduId].Timer=0;
            CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_OK);
        }
        else
        {
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitForRxBuffer;
            CanTp_RxState[CanTpRxPduId].Timer=CANTP_NBR(CanTpRxPduId);//¿ªÊ¼¼Ætimeout
        }
    }
}
/* BEGIN_FUNCTION_HDR
*******************************************************************************************************************
* Function Name: CanTp_RxFFPdu
* Description:
*    This function is called by CanTp_RxIndication after a successful reception of a Rx FF-PDU.
* Inputs:
*   ID of CAN L-PDU that has been received. Identifies the data that has been received.
*   Range: 0..(maximum number of L-PDU IDs received ) - 1
* Outputs:
*   None.
* Limitations:
*   None.
********************************************************************************************************************
 END_FUNCTION_HDR*/
static void CanTp_RxFFPdu(PduIdType CanTpRxPduId,uint8* FFDataBuf,uint8 CanDlc)
{
    BufReq_ReturnType  BufReqResult;
    PduLengthType CanTpDataLength;
    PduIdType CanTpTxChannelMaped;
    CanTpTxChannelMaped=RX_TO_TX_CHANNEL(CanTpRxPduId);/*Get the related TP Tx Channel */
    CanTpDataLength=(uint16)((uint16)(FFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_DLMaskFF)<< 8)
                    |(uint16)FFDataBuf[RX_DL_OFFSET(CanTpRxPduId)];
    if(CanDlc<CANTP_MAX_FRAME_LENGTH)
    {
        /*Ignore*/
    }
#if(CANTP_CHANNEL_MODE==CANTP_MODE_HALF_DUPLEX)
    else if (CanTp_TxState[CanTpTxChannelMaped].ChannelState!= cCanTpTxState_Idle)
    {
         /*Ignore*/
    }
#endif
    else if(CANTP_RX_TA_TYPE(CanTpRxPduId)==CANTP_FUNCTIONAL)/*Target Addressing Format*/
    {
        CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
        CanTp_RxState[CanTpRxPduId].Timer=0;
        CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_CAN_WRONG_FFTATYPE);
    }
    else if(CanTpDataLength<=  RX_SF_DataLength(CanTpRxPduId))
    {
        CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
        CanTp_RxState[CanTpRxPduId].Timer=0;
        CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_CAN_WRONG_FFDL);
    }
    else
    {
        if (CanTp_RxState[CanTpRxPduId].ChannelState!=cCanTpRxState_Idle)/* Reception is in progress,wait Tx FC conf*/
        {
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
            CanTp_RxState[CanTpRxPduId].Timer=0;
            CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_UNEXP_PDU);/*Terminate the current reception, report an indication, with parameter Result set to NTFRSLT_E_UNEXP_PDU, to the upper layer*/
        }
        else
        {
        	
        }
        /*start a time-out N_Br before requesting an Rx buffer. If a buffer has not been provided  before the timer elapsed,
        the CanTp module shall abort the communication*/
        CanTp_RxState[CanTpRxPduId].DataLength=CanTpDataLength;
        CanTp_RxState[CanTpRxPduId].FrameIndex=(uint16)(CanTp_RxState[CanTpRxPduId].DataLength/RX_CF_DataLength(CanTpRxPduId));
        CanTp_RxState[CanTpRxPduId].ExpectedSN=(uint16)cCanTpSNStartValue;
        CanTp_RxState[CanTpRxPduId].DataIndex=0;
        CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduDataPtr=&FFDataBuf[RX_FF_OFFSET(CanTpRxPduId)];
        CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduLength=RX_FF_DataLength(CanTpRxPduId);
        BufReqResult=CanTp_NUSDataFFIndication(CanTpRxPduId,CanTp_RxState[CanTpRxPduId].DataLength,&CanTp_RxState[CanTpRxPduId].AvailableBufLength);
        if(BufReqResult==BUFREQ_OK)
        {
            if(CanTp_RxState[CanTpRxPduId].AvailableBufLength>=CanTp_RxState[CanTpRxPduId].DataLength)
            {
                CanTp_RxState[CanTpRxPduId].BlockSizeCounter=CANTP_BS(CanTpRxPduId);
            }
            else
            {
                CanTp_RxState[CanTpRxPduId].BlockSizeCounter=(uint8)(CanTp_RxState[CanTpRxPduId].AvailableBufLength/RX_CF_DataLength(CanTpRxPduId))+1;
            }
            (void)CanTp_CopyRxData(CanTpRxPduId,&CanTp_RxState[CanTpRxPduId].RxNPduInfo,&CanTp_RxState[CanTpRxPduId].AvailableBufLength);
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitForTxFC;
            CanTp_RxState[CanTpRxPduId].FlowStatus=(uint16)cCanTp_FC_FS_CTS;
            CanTp_RxState[CanTpRxPduId].DataIndex=RX_FF_DataLength(CanTpRxPduId);
            CanTp_RxState[CanTpRxPduId].Timer=1; /*Transmit FC in the task immediately*/
        }
        else if(BufReqResult==BUFREQ_E_OVFL)
        {
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitForTxFCOverrun;
            CanTp_RxState[CanTpRxPduId].FlowStatus=(uint16)cCanTp_FC_FS_Overrun;
            CanTp_RxState[CanTpRxPduId].Timer=1; /*Transmit FC in the task immediately*/
        }
        else /*BUFREQ_E_BUSY  or BUFREQ_E_NOT_OK*/
        {
            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitForRxBuffer;
            CanTp_RxState[CanTpRxPduId].Timer=CANTP_NBR(CanTpRxPduId);
            CanTp_RxState[CanTpRxPduId].WFTCounter=0;
        }
    }
}
/* BEGIN_FUNCTION_HDR
***************************************************************************************************************
* Function Name: CanTp_RxCFPdu
* Description:
*     This function is called by CanTp_RxIndication after a successful reception of a Rx CF-PDU.
* Inputs:
*   ID of CAN L-PDU that has been received. Identifies the data that has been received.
*   Range: 0..(maximum number of L-PDU IDs received ) - 1
* Outputs:
*   None.
* Limitations:
*   None.
***************************************************************************************************************
 END_FUNCTION_HDR*/
static void CanTp_RxCFPdu(PduIdType CanTpRxPduId,uint8* CFDataBuf,uint8 CanDlc)
{
    BufReq_ReturnType  BufReqResult;
    PduIdType CanTpTxChannelMaped;
    PduLengthType LastCFLength=0;
    CanTpTxChannelMaped=RX_TO_TX_CHANNEL(CanTpRxPduId);/*Get the related TP Tx Channel */
    if (CanTp_RxState[CanTpRxPduId].ChannelState != cCanTpRxState_WaitCF)
    {
        /*Ignore*/
    }
#if(CANTP_CHANNEL_MODE==CANTP_MODE_HALF_DUPLEX)
    else if (CanTp_TxState[CanTpTxChannelMaped].ChannelState!= cCanTpTxState_Idle)
    {
         /*Ignore*/
    }
#endif
    else if((CFDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_SNMask)!=CanTp_RxState[CanTpRxPduId].ExpectedSN)
    {
        CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
        CanTp_RxState[CanTpRxPduId].Timer=0;
        CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_WRONG_SN);
    }
    else
    {
        CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduDataPtr=&CFDataBuf[RX_CF_OFFSET(CanTpRxPduId)];
        LastCFLength=CanTp_RxState[CanTpRxPduId].DataLength-CanTp_RxState[CanTpRxPduId].DataIndex;
        if(LastCFLength<=(uint16)RX_CF_DataLength(CanTpRxPduId))/*the last CF*/
        {
            if(CanDlc<=LastCFLength)
            {
                /*CAN data link error,abort CAN frame*/
            }
            else
            {
                CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduLength=LastCFLength;
                (void)CanTp_CopyRxData(CanTpRxPduId,&CanTp_RxState[CanTpRxPduId].RxNPduInfo,&CanTp_RxState[CanTpRxPduId].AvailableBufLength);
                CanTp_RxState[CanTpRxPduId].DataIndex=CanTp_RxState[CanTpRxPduId].DataLength;
                CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
                CanTp_RxState[CanTpRxPduId].Timer=0;
                CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_OK);
            }
        }
        else /*is not last CF*/
        {
            if(CanDlc<=RX_CF_DataLength(CanTpRxPduId))
            {
                /*CAN data link error,abort CAN frame*/
            }
            else
            {
                CanTp_RxState[CanTpRxPduId].RxNPduInfo.SduLength=RX_CF_DataLength(CanTpRxPduId);
                BufReqResult=CanTp_CopyRxData(CanTpRxPduId,&CanTp_RxState[CanTpRxPduId].RxNPduInfo,&CanTp_RxState[CanTpRxPduId].AvailableBufLength);
                CanTp_RxState[CanTpRxPduId].DataIndex+=RX_CF_DataLength(CanTpRxPduId);
                CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitCF;
                CanTp_RxState[CanTpRxPduId].Timer=CANTP_NCR(CanTpRxPduId);
                /*check SN */
                if(CanTp_RxState[CanTpRxPduId].ExpectedSN<cCanTp_SNMask)
                {
                    CanTp_RxState[CanTpRxPduId].ExpectedSN++;
                }
                else
                {
                    CanTp_RxState[CanTpRxPduId].ExpectedSN=0;
                }
                /*check BS */
                if(CanTp_RxState[CanTpRxPduId].BlockSizeCounter!=0)
                {
                    CanTp_RxState[CanTpRxPduId].BlockSizeCounter--;
                    if(CanTp_RxState[CanTpRxPduId].BlockSizeCounter==0)/*is the last CF of block*/
                    {
                        if(BufReqResult==BUFREQ_OK)
                        {
                            if(CanTp_RxState[CanTpRxPduId].AvailableBufLength>=(PduLengthType)(CanTp_RxState[CanTpRxPduId].DataLength-CanTp_RxState[CanTpRxPduId].DataIndex))
                            {
                                CanTp_RxState[CanTpRxPduId].BlockSizeCounter=CANTP_BS(CanTpRxPduId);
                            }
                            else
                            {
                                CanTp_RxState[CanTpRxPduId].BlockSizeCounter=(uint8)(CanTp_RxState[CanTpRxPduId].AvailableBufLength/RX_CF_DataLength(CanTpRxPduId))+1;
                            }
                            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitForTxFC;
                            CanTp_RxState[CanTpRxPduId].FlowStatus=(uint16)cCanTp_FC_FS_CTS;
                            CanTp_RxState[CanTpRxPduId].Timer=1; /*Transmit FC in the task */
                        }
                        else /* CANTP268 */
                        {
                            CanTp_RxState[CanTpRxPduId].DataIndex-=RX_CF_DataLength(CanTpRxPduId);
                            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_WaitForRxBuffer;
                            CanTp_RxState[CanTpRxPduId].Timer=CANTP_NBR(CanTpRxPduId);
                            CanTp_RxState[CanTpRxPduId].WFTCounter=0;
                        }
                    }
                    /*CANTP271: If the PduR_CanTpCopyRxData() returns BUFREQ_E_NOT_OK or
            BUFREQ_E_OVFL or BUFREQ_E_BUSY after reception of a Consecutive Frame in a
            block the CanTp shall abort the reception of N-SDU.*/
                    else
                    {
                        if(BufReqResult!=BUFREQ_OK)
                        {
                            CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
                            CanTp_RxState[CanTpRxPduId].Timer=0;
                            CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_NO_BUFFER);
                        }
                        else
                        {
                        }
                    }
                }
                else/*BS=0*/
                {
                    /* !CANTP270:In case that remaining buffer is too small for the next Consecutive
                Frame reception the CanTp might call PduR_CanTpCopyRxData() with a data
                length 0 (zero) and NULL-PTR as data buffer until a buffer of sufficient size is
                provided. These calls might be performed in the time limit of STmin.*/
                    if(BufReqResult!=BUFREQ_OK)
                    {
                        CanTp_RxState[CanTpRxPduId].ChannelState=cCanTpRxState_Idle;
                        CanTp_RxState[CanTpRxPduId].Timer=0;
                        CanTp_NUSDataIndication(CanTpRxPduId,NTFRSLT_E_NO_BUFFER);
                    }
                    else
                    {
                    }
                }
            }
        }
    }
}
/* BEGIN_FUNCTION_HDR
**************************************************************************************************************
* Function Name: CanTp_AssembleFC
* Description:
*    This function is called by CanTp_RxIndication after a successful reception of a Rx FC-PDU.
* Inputs:
*   ID of CAN L-PDU that has been received. Identifies the data that has been received.
*   Range: 0..(maximum number of L-PDU IDs received ) - 1
* Outputs:
*   None.
* Limitations:
*   None.
**************************************************************************************************************
 END_FUNCTION_HDR*/
static void CanTp_RxFCPdu(PduIdType CanTpRxPduId,uint8* FCDataBuf,uint8 CanDlc)
{
    PduIdType CanTpTxChannelMaped;
    CanTpTxChannelMaped=CANTP_TXFC_NPDU_ID(CanTpRxPduId);/*Get the related TP Tx Channel */
    if(CanDlc<RX_FC_DataLength(CanTpRxPduId))
    {
        /*CAN data link error,abort CAN frame*/
    }
#if(CANTP_CHANNEL_MODE==CANTP_MODE_HALF_DUPLEX)
    else if (CanTp_RxState[CanTpRxPduId].ChannelState!= cCanTpRxState_Idle)
    {
         /*Ignore*/
    }
#endif
    else if(CanTpTxChannelMaped!=RX_TO_TX_CHANNEL(CanTpRxPduId)) /*Compara the FC ID and Tx Channel ID,Require in development */
    {
        /*Ignore*/
    }
    else if((CanTp_TxState[CanTpTxChannelMaped].ChannelState & cCanTpInternalStateMask)!=cCanTpTxState_WaitFC)
    {
        /*FC NotExpected,Ignore*/
    }
    else
    {
        switch(FCDataBuf[RX_TPCI_OFFSET(CanTpRxPduId)]&cCanTp_FSMask)/*Check FS */
        {
            case  cCanTp_FC_FS_CTS:
            {
                CanTp_TxState[CanTpTxChannelMaped].ChannelState=cCanTpTxState_WaitForTpTxCF;
                CanTp_TxState[CanTpTxChannelMaped].BlockSizeCounter=FCDataBuf[RX_BS_OFFSET(CanTpRxPduId)];
                if ((FCDataBuf[RX_STMIN_OFFSET(CanTpRxPduId)] & 0x80) == 0x80)
                {
                    if ((FCDataBuf[RX_STMIN_OFFSET(CanTpRxPduId)] > 0xF0)
                        && (FCDataBuf[RX_STMIN_OFFSET(CanTpRxPduId)] <= 0xF9)) /*F1 - F9£º STmin range: 100 ¦Ìs - 900 ¦Ìs*/
                    {
                        CanTp_TxState[CanTpTxChannelMaped].STMin = 1;
                    }
                    else /*80 -F0£¬ FA - FF*/
                    {
                        CanTp_TxState[CanTpTxChannelMaped].STMin = (uint8)((127 / CANTP_MAIN_FUNCTION_PERIOD)+1); /* Max STmin time */
                    }
                }
                else /*00 - 7F£¬STmin range: 0 ms -127 ms*/
                {
                    CanTp_TxState[CanTpTxChannelMaped].STMin = (uint8)(FCDataBuf[RX_STMIN_OFFSET(CanTpRxPduId)] / CANTP_MAIN_FUNCTION_PERIOD)+1;
                }
                CanTp_TxState[CanTpTxChannelMaped].Timer=CanTp_TxState[CanTpTxChannelMaped].STMin;
            }
            break;
            case  cCanTp_FC_FS_Wait:
            {
                CanTp_TxState[CanTpTxChannelMaped].ChannelState=cCanTpTxState_WaitFC;
                CanTp_TxState[CanTpTxChannelMaped].Timer=(uint16)(CANTP_NBS(CanTpTxChannelMaped)-1);
            }
            break;
            case  cCanTp_FC_FS_Overrun:
            {
                CanTp_TxState[CanTpTxChannelMaped].ChannelState=cCanTpTxState_Idle;
                CanTp_TxState[CanTpTxChannelMaped].Timer=0;
                CanTp_NUSDataConfirm(CanTpTxChannelMaped,NTFRSLT_E_NO_BUFFER);
            }
            break;
            default:
            {
                CanTp_TxState[CanTpTxChannelMaped].ChannelState=cCanTpTxState_Idle;
                CanTp_TxState[CanTpTxChannelMaped].Timer=0;
                CanTp_NUSDataConfirm(CanTpTxChannelMaped,NTFRSLT_E_INVALID_FS );    /* inform application */
            }
            break;
        }
    }
}
/* BEGIN_FUNCTION_HDR
*************************************************************************************************************
* Function Name: CanTp_AssembleFC
* Description:
*            Assemble FC .
* Inputs:
*         CanTpRxPduId.
*         FlowStatus
* Outputs:
*   None.
* Limitations:
*   None.
*************************************************************************************************************
 END_FUNCTION_HDR*/

/*static*/ void CanTp_AssembleFC(PduIdType CanTpRxPduId, uint8 FlowStatus)
{
    
    PduInfoType CanTpTxFCPduInfo;
    PduIdType CanTpTxFCPduIdMaped;
    uint8 i;
    CanTpTxFCPduIdMaped=CANTP_TXFC_NPDU_ID(CanTpRxPduId);
    if(CANTP_TX_ADDRESSING_FORMAT(CanTpTxFCPduIdMaped)==CANTP_EXTENDED)
    {
        TempFcMsg[TARGET_OFFSET]=CANTP_TX_NTA(CanTpTxFCPduIdMaped);
    }
    else if(CANTP_TX_ADDRESSING_FORMAT(CanTpTxFCPduIdMaped)==CANTP_MIXED)
    {
        TempFcMsg[AE_OFFSET]=CANTP_TX_NAE(CanTpRxPduId);
    }
    else
    {
    }
    TempFcMsg[TX_TPCI_OFFSET(CanTpTxFCPduIdMaped)]=(uint8)(cCanTp_FC|FlowStatus);
    TempFcMsg[TX_BS_OFFSET(CanTpTxFCPduIdMaped)]=CanTp_RxState[CanTpRxPduId].BlockSize;
    TempFcMsg[TX_STMIN_OFFSET(CanTpTxFCPduIdMaped)]=CanTp_RxState[CanTpRxPduId].STMin;
    CanTpTxFCPduInfo.SduDataPtr=TempFcMsg;
    if(CANTP_RX_PADDING_ACTIVATION(CanTpRxPduId)==CANTP_ON)
    {
        for (i=(uint8)(TX_STMIN_OFFSET(CanTpTxFCPduIdMaped)+1);i<CANTP_MAX_FRAME_LENGTH;i++)
        {
            TempFcMsg[i]=CANTP_FILLPATTERN;
        }
        CanTpTxFCPduInfo.SduLength=CANTP_MAX_FRAME_LENGTH;
    }
    else
    {
        CanTpTxFCPduInfo.SduLength=TX_FC_DataLength(CanTpTxFCPduIdMaped);
    }
    if(CanTp_CanTransmit(CanTpTxFCPduIdMaped,&CanTpTxFCPduInfo)!=E_OK)
    {
        CanTp_RxState[CanTpRxPduId].ChannelState|=cCanTpState_Retransmit;
    }
    else
    {
    	
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name: CanTp_DataCopy
* Description:
*             Copy data .
* Inputs:
*             src, source data pointer buffer
*             cnt, source data size.
* Outputs:
*             dest.destination data pointer buffer
* Limitations:
*             None.
********************************************************************
 END_FUNCTION_HDR*/
static void CanTp_DataCopy( uint8* dest, uint8* src,uint16 cnt)
{
    uint16 i;
    for(i=0;i<cnt;i++)
    {
        dest[i]=src[i] ;
    }
}

/************************ Version 1.0.0 ***************************/


