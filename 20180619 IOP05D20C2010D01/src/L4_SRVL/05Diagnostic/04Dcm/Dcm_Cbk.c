/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm_Cbk.c  
*
* @brief  callback function calledby PduR Router.
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
#include "Dcm.h"
#include "Dcm_Cbk.h"
#include "Dcm_Cfg.h"

/**************************************************************************************************
* Internal Functin Prototype (Scope:local)
**************************************************************************************************/
STATIC void DiagCopy( uint8* dest, uint8* src,uint32 cnt);


/**************************************************************************************************
*                              Global Function Implementation                                     *
**************************************************************************************************/


/**************************************************************************************************
* Name         :  Dcm_StartOfReception 
* Called by    :  Can_PduRouter 
* Preconditions:  None
* Parameters   :  -DcmRxPduId: Receive PduId
                  -TpSduLength:Length in Single Frame or Fist Frame
                  -Length:     Avaliable buffer size Dcm can provided  
* Return code  :  BUFREQ_E_NOT_OK,BUFREQ_E_BUSY and BUFREQ_E_OVFL  
* Description  :  Callbak function provided by Dcm to Can_PduRouter   
*                
***************************************************************************************************/
BufReq_ReturnType Dcm_StartOfReception
(
    PduIdType     DcmRxPduId,
    PduLengthType TpSduLength,
    PduLengthType *Length
)
{   
    BufReq_ReturnType result=BUFREQ_OK;
    if(gMsgContextType.dcmRxPduId==DcmRxPduId)
    {
        result=BUFREQ_E_NOT_OK;
    }
    else
    {
        /* If request is under processing, do not receive any other request(including UDS and OBD request) any more,
           volatile with AUTOSAR standard */
        if((gDiagState&DIAG_UDS_PROCESSING)==DIAG_UDS_PROCESSING)
        {
            result=BUFREQ_E_BUSY;
        }
        else
        {
            if(TpSduLength>gDcmDslAvailableBufferSize[DcmRxPduId])
            {
                result=BUFREQ_E_OVFL;
            } 
            else
            {
                if(gSesCtrlType!=DCM_DEFAULT_SESSION)
                {
                    gS3ServerTimerStartFlag=0;
                }
                else
                {
                }
                switch(DcmRxPduId)
                {
                    case UDS_PHYSICAL_ON_CAN_Rx:
                    Set_ActiveProtocol(DCM_UDS_ON_CAN);
                    gMsgContextType.reqData=gUDS_Physical_DiagBuffer;
                    break;
                    
                    case UDS_FUNCTIONAL_ON_CAN_Rx:
                    Set_ActiveProtocol(DCM_UDS_ON_CAN);
                    gMsgContextType.reqData=gUDS_Functional_DiagBuffer;
                    break;
                   
                    #if(ISO_15031_5==STD_ON)
                    case OBD_PHYSICAL_ON_CAN_Rx:
                    Set_ActiveProtocol(DCM_OBD_ON_CAN);
                    gMsgContextType.reqData=gOBD_Physical_DiagBuffer;
                    break;
                    
                    case OBD_FUNCTIONAL_ON_CAN_Rx:
                    Set_ActiveProtocol(DCM_OBD_ON_CAN);
                    gMsgContextType.reqData=gOBD_Functional_DiagBuffer; 
                    break;
                    #endif

                    default:
                    break;
                }
                *Length=(uint16)gDcmDslAvailableBufferSize[DcmRxPduId];
                gMsgContextType.reqDataLen=TpSduLength;
                /* Stop S3 Timer */
                if(gSesCtrlType!=DCM_DEFAULT_SESSION)
                {
                    gS3ServerTimerStartFlag=0;
                }
                else
                {
                }
            }
        }
    }
    return result;
}
/***************************************************************************************************
* Name         :  Dcm_CopyRxData 
* Called by    :  Can_PduRouter 
* Preconditions:  None
* Parameters   :  -DcmRxPduId:     Receive PduId
                  -PduInfoPointer: Pointer to a PduInfoType which indicates
                   the number of bytes to be copied (SduLength) and the 
                   location of the source data (SduDataPtr).
                  -RxBufferSizePtr:Remaining free place in receive buffer after
                   completion of this call.
* Return code  :  BUFREQ_OK,BUFREQ_E_BUSY
* Description  :  Callbak function Dcm provided by Dcm to Can_PduRouter
*                
***************************************************************************************************/
BufReq_ReturnType Dcm_CopyRxData
(
    PduIdType                                    DcmRxPduId,
    P2VAR(PduInfoType,AUTOMATIC,DCM_APPL_DATA)   PduInfoPointer,
    P2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) RxBufferSizePtr
)
{
    BufReq_ReturnType result=BUFREQ_OK;
    /* If request is under processing, do not receive any other request(including UDS and OBD request) any more,
       volatile with AUTOSAR standard */
    if(gDiagState==DIAG_UDS_PROCESSING)
    {
        if((DcmRxPduId==UDS_FUNCTIONAL_ON_CAN_Rx)||(DcmRxPduId==UDS_PHYSICAL_ON_CAN_Rx))
        {
            result=BUFREQ_E_BUSY;
        }
        else
        {
                   
        }
    }
    else
    {
        switch(DcmRxPduId)
        {
            case UDS_PHYSICAL_ON_CAN_Rx:
            gMsgContextType.msgAddInfo.reqType=0;
            break;
            
            case UDS_FUNCTIONAL_ON_CAN_Rx:
            gMsgContextType.msgAddInfo.reqType=1;
            break;
            
            #if(ISO_15031_5==STD_ON)
            case OBD_PHYSICAL_ON_CAN_Rx:
            gMsgContextType.msgAddInfo.reqType=0;
            break;
            
            case OBD_FUNCTIONAL_ON_CAN_Rx:
            gMsgContextType.msgAddInfo.reqType=1;
            break;
            #endif
            
            default:
            break;
        }
        DiagCopy(gMsgContextType.reqData,PduInfoPointer->SduDataPtr,PduInfoPointer->SduLength);
        gMsgContextType.reqData+=(uint8)PduInfoPointer->SduLength; 
        gDcmDslAvailableBufferSize[DcmRxPduId]-=(PduInfoPointer->SduLength);
        *RxBufferSizePtr=(uint16)gDcmDslAvailableBufferSize[DcmRxPduId];
    }
    return result;
}
/***************************************************************************************************
* Name         :  Dcm_RxIndication 
* Called by    :  Can_PduRouter 
* Preconditions:  None
* Parameters   :  -DcmRxPduId:     Receive PduId
                  -Result:         NTFRSLT_OK means the complete N-PDU has been 
                  received and is stored in the receive buffer.Any other value 
                  means the N_PDU has not been received,
* Return code  :  None
* Description  :  Callbak function Dcm provided by Dcm to Can_PduRouter
*                
***************************************************************************************************/
void Dcm_RxIndication
(
    PduIdType       DcmRxPduId,
    NotifResultType Result
)
{
   uint8 i;
   if(Result==NTFRSLT_OK)
   {
      Set_PduId(DcmRxPduId);
      /* Start P2 Timer */
      gP2ServerTimerStartFlag=1;
      Set_P2_Server_Timer(gDcmDspSessionRow[gSesCtrlType-1].DcmDspSessionP2ServerMax);

      switch(DcmRxPduId)
      {
          case UDS_PHYSICAL_ON_CAN_Rx:
          gDcmDslAvailableBufferSize[DcmRxPduId]=UDS_PHYS_BUFFER_SIZE;/* Reset available buffer size */
          gMsgContextType.reqData=gUDS_Physical_DiagBuffer;
          gMsgContextType.resData=gUDS_Physical_DiagBuffer;
          Set_DiagState(DIAG_UDS_INDICATION);
          break;
          
          case UDS_FUNCTIONAL_ON_CAN_Rx:
          gDcmDslAvailableBufferSize[DcmRxPduId]=UDS_FUNC_BUFFER_SIZE;/* Reset available buffer size */
          gMsgContextType.reqData=gUDS_Functional_DiagBuffer;
          gMsgContextType.resData=gUDS_Physical_DiagBuffer; /* Response is always put in physical buffer since it is always phisical.
                                                               And only request has two kinds(functional and phisical) */ 
          /* If these codes aren't added,it will find out one bug. Take 0x10 service for example, 
             if send 0x10 01 by functional CANID, then get correct response 0x50 01. Then send 0x10 03
             by functional CANID, then get fasle response 0x50 01,2011,11.30 */
          for(i=0;i<UDS_FUNC_BUFFER_SIZE;i++)                                                           
          {
              gUDS_Physical_DiagBuffer[i]=gUDS_Functional_DiagBuffer[i];
          }
          Set_DiagState(DIAG_UDS_INDICATION);
          break;
          
          #if(ISO_15031_5==STD_ON)
          case OBD_PHYSICAL_ON_CAN_Rx:
          gDcmDslAvailableBufferSize[DcmRxPduId]=OBD_PHYS_BUFFER_SIZE;
          gMsgContextType.reqData=gOBD_Physical_DiagBuffer;
          gMsgContextType.resData=gOBD_Physical_DiagBuffer; 
          Set_DiagState(DIAG_OBD_INDICATION);
          break;
          
          case OBD_FUNCTIONAL_ON_CAN_Rx:
          gDcmDslAvailableBufferSize[DcmRxPduId]=OBD_FUNC_BUFFER_SIZE;
          gMsgContextType.reqData=gOBD_Functional_DiagBuffer;
          gMsgContextType.resData=gOBD_Functional_DiagBuffer; 
          Set_DiagState(DIAG_OBD_INDICATION);
          break;
          #endif
          default:
          break;
      }
   }
   else
   {
        CanTp_ChannelInit(CANTP_TX_CHANNEL,DcmRxPduId);
   }
}
/***************************************************************************************************
* Name         :  Dcm_CopyTxData 
* Called by    :  Can_PduRouter 
* Preconditions:  None
* Parameters   :  -DcmTxPduId:     Transmitt PduId
                  -PduInfoPtr:     Pointer to a PduInfoType, which indicates the 
                  number of bytes to be copied (SduLength) and the location 
                  where the data have to be copied to (SduDataPtr).
                  -RetryInfoPtr:   None used
                  -TxDataCntPtr:   Remaining Tx data after completion of this call
* Return code  :  
* Description  :  Callbak function Dcm provided by Dcm to Can_PduRouter
*                
***************************************************************************************************/
BufReq_ReturnType Dcm_CopyTxData
(
    PduIdType                                    DcmTxPduId,
    P2VAR(PduInfoType,AUTOMATIC,DCM_APPL_DATA)   PduInfoPtr,
    P2VAR(RetryInfoType,AUTOMATIC,DCM_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) TxDataCntPtr
)
{
    BufReq_ReturnType result=BUFREQ_OK;
    (void)(DcmTxPduId);
    
    #if(DCM_SERVICE_22_COMBINED_DID==STD_OFF)
    DiagCopy(PduInfoPtr->SduDataPtr,gMsgContextType.resData,PduInfoPtr->SduLength);
    #else
    if(gNegativeResponseCode!=0)
    {
        DiagCopy(PduInfoPtr->SduDataPtr,gNegativeResponseBuffer,NEG_RESP_BUFFER_SIZE); 
    }
    else
    {
        DiagCopy(PduInfoPtr->SduDataPtr,gMsgContextType.resData,PduInfoPtr->SduLength);
    }
    #endif
    
    (gMsgContextType.resData)+=(PduInfoPtr->SduLength);
    (void)RetryInfoPtr;
    if(gResponseLength>=PduInfoPtr->SduLength)
    {
        gResponseLength-=(PduInfoPtr->SduLength);
    }
    else
    {
        gResponseLength=0;  /* Last frame */
    }
    *TxDataCntPtr=gResponseLength;
    return result;
}
/***************************************************************************************************
* Name         :  Dcm_TxConfirmation 
* Called by    :  Can_PduRouter 
* Preconditions:  None
* Parameters   :  -DcmTxPduId: Transmitt PduId
                  -Result:     NTFRSLT_OK means the complete N-PDU has been 
                   transmitted.Any other value means an error occurred during 
                   transmission.
* Return code  :  None
* Description  :  Callbak function Dcm provided by Dcm to Can_PduRouter
*                
***************************************************************************************************/
void Dcm_TxConfirmation
(
   PduIdType       DcmTxPduId,
   NotifResultType Result
)
{
    switch(Result)
    {
        case NTFRSLT_OK:
        {
            if((gDiagState&DIAG_UDS_RCRP)==DIAG_UDS_RCRP)/* 0x78 negative response */
            {
                ClrNegativeResponseCode();
                Clr_DiagState(DIAG_UDS_RCRP);
                Set_P2_Server_Timer(gDcmDspSessionRow[gSesCtrlType-1].DcmDspSessionP2StarServerMax);/* Set enhances P2 timer */
            }
            else/* Positive response or other negative response */
            {
                Clr_ActiveProtocol();
                Reset_PduId();
                #if(DCM_SERVICE_22_COMBINED_DID==STD_OFF)
                #else
                ClrNegativeResponseCode();
                #endif
            }
            /* Start S3 Timer */
            if(gSesCtrlType!=DCM_DEFAULT_SESSION)
            {
                gS3ServerTimerStartFlag=1;
                Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
            }
            else
            {
            }
        }
        break;
      
        case NTFRSLT_E_NOT_OK:
        /*break;*/

        case NTFRSLT_E_TIMEOUT_A:
        /*break;*/

        case NTFRSLT_E_TIMEOUT_BS:
        /*break;*/

        case NTFRSLT_E_TIMEOUT_CR:
        /*break;*/

        case NTFRSLT_E_WRONG_SN:
        /*break;*/

        case NTFRSLT_E_INVALID_FS:
        /*break;*/

        case NTFRSLT_E_UNEXP_PDU:
        /*break;*/

        case NTFRSLT_E_WFT_OVRN:
        /*break;*/

        case NTFRSLT_E_ABORT:
        /*break;*/

        case NTFRSLT_E_NO_BUFFER:
        /*break;*/

        case NTFRSLT_E_CANCELATION_OK:
        /*break;*/

        case NTFRSLT_E_CANCELATION_NOT_OK:
        /*break;*/

        case NTFRSLT_PARAMETER_OK:
        /*break;*/

        case NTFRSLT_E_PARAMETER_NOT_OK:
        /*break;*/

        case NTFRSLT_E_RX_ON:
        /*break;*/

        case NTFRSLT_E_VALUE_NOT_OK:
        CanTp_ChannelInit(CANTP_TX_CHANNEL,DcmTxPduId);
        break;

        default:
        
        break;
    }
}
     
/***************************************************************************************************
* Name         :  DiagCopy 
* Called by    :  Dcm_CopyRxData and Dcm_CopyTxData 
* Preconditions:  None
* Parameters   :  -dest:pointing to the destination where data should be copied to
                  -src: pointing to the source where data should be copied frome
                  -cnt: the total length of the data should be copied
* Return code  : None 
* Description  : Move number of cnt data from source to destination 
*                
***************************************************************************************************/
STATIC void DiagCopy( uint8* dest, uint8* src,uint32 cnt)
{
	uint32 i;
	for(i=0;i<cnt;i++)
	{
		dest[i]=src[i] ;
	}
}


/*******************************************************  End  ******************************************************/
