

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_TemperatureSignal.h"
/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3POWERCIRCUITDATA_START_SEC_CONST
#include "MemMap.h"
/*Temperature table*/
const sint16 Temperature_Table[34] =
{
    /*Temperature value in s16p08*/

-80,  -70,  -60,  -50,  -40,
-30,  -20,  -10,  0,    10,
20,	  30,   40,	  50,   60,
70,	  80,   90,   100,  110,
120,  130,  140,  150,  160,
170,  180,  190,  200,  210,
220,  230,  240,  250,
};

/*Temperature table*/
const uint16 ADresult_Table[34] =
{
    /*ADC result for each temperature*/
9    ,
13 	 ,
18 	 ,
24 	 , 
33 	 , 
43 	 , 
57 	 , 
73 	 ,
93 	 ,
117  ,
145  ,
177  ,
213  , 
253  , 
297  , 
343  , 
391  ,
440  ,
489  ,
537  , 
583  , 
627  , 
668  ,
706  ,
741  , 
773  , 
801  , 
827  , 
849  ,
869  ,
887  ,
902  , 
916  , 
928   
	 
};	 


/*AD Result Value*/

#define d_L3POWERCIRCUITDATA_STOP_SEC_CONST
#include "MemMap.h"
/*End of L3_Temperature_Signal_Data.c file*/
