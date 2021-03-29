/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Intc_Drv.c
*
* @brief    Interrupt Source File, Init Intc Vector and Function image
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/01      Lwt       		N/A          Original
*     1.1        2012/09/05      Lwt           	N/A          Modify include file
*     1.2        2012/09/07      Lwt           	N/A          Move Func Declaration to Src File
*     1.3        2012/09/14      jiaoyu			N/A          deliver to ChuangQu
*     1.4        2012/09/24      Lwt           	N/A          Modify PWM ISR
*     1.5        2012/10/11      Lwt           	N/A          Modify include file
*     1.6        2012/11/02      Lwt			N/A          Add History Comment
*     1.7        2012/12/11      Lwt			N/A          eTimer Update, Add eTimer INTC Vector
*******************************************************************************/

#ifndef M_INTC_DRV_C
#define M_INTC_DRV_C
#endif


/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include	"m_Intc_Drv.h"
#include	"m_Intc_Cfg.h"


/*******************************************************************************
* Global ISR Function Prototypes
*******************************************************************************/
#ifdef IRQ_0_FCN
   extern void IRQ_0_FCN();
#endif

#ifdef IRQ_1_FCN
   extern void IRQ_1_FCN();
#endif

#ifdef IRQ_2_FCN
   extern void IRQ_2_FCN();
#endif

#ifdef IRQ_3_FCN
   extern void IRQ_3_FCN();
#endif

#ifdef IRQ_4_FCN
   extern void IRQ_4_FCN();
#endif

#ifdef IRQ_5_FCN
   extern void IRQ_5_FCN();
#endif

#ifdef IRQ_6_FCN
   extern void IRQ_6_FCN();
#endif

#ifdef IRQ_7_FCN
   extern void IRQ_7_FCN();
#endif

#ifdef IRQ_8_FCN
   extern void IRQ_8_FCN();
#endif

#ifdef IRQ_9_FCN
   extern void IRQ_9_FCN();
#endif

#ifdef IRQ_10_FCN
   extern void IRQ_10_FCN();
#endif

#ifdef IRQ_11_FCN
   extern void IRQ_11_FCN();
#endif

#ifdef IRQ_12_FCN
   extern void IRQ_12_FCN();
#endif

#ifdef IRQ_13_FCN
   extern void IRQ_13_FCN();
#endif

#ifdef IRQ_14_FCN
   extern void IRQ_14_FCN();
#endif

#ifdef IRQ_15_FCN
   extern void IRQ_15_FCN();
#endif

#ifdef IRQ_16_FCN
   extern void IRQ_16_FCN();
#endif

#ifdef IRQ_17_FCN
   extern void IRQ_17_FCN();
#endif

#ifdef IRQ_18_FCN
   extern void IRQ_18_FCN();
#endif

#ifdef IRQ_19_FCN
   extern void IRQ_19_FCN();
#endif

#ifdef IRQ_20_FCN
   extern void IRQ_20_FCN();
#endif

#ifdef IRQ_21_FCN
   extern void IRQ_21_FCN();
#endif

#ifdef IRQ_22_FCN
   extern void IRQ_22_FCN();
#endif

#ifdef IRQ_23_FCN
   extern void IRQ_23_FCN();
#endif

#ifdef IRQ_24_FCN
   extern void IRQ_24_FCN();
#endif

#ifdef IRQ_25_FCN
   extern void IRQ_25_FCN();
#endif

#ifdef IRQ_26_FCN
   extern void IRQ_26_FCN();
#endif

#ifdef IRQ_27_FCN
   extern void IRQ_27_FCN();
#endif

#ifdef IRQ_28_FCN
   extern void IRQ_28_FCN();
#endif

#ifdef IRQ_29_FCN
   extern void IRQ_29_FCN();
#endif

#ifdef IRQ_30_FCN
   extern void IRQ_30_FCN();
#endif

#ifdef IRQ_31_FCN
   extern void IRQ_31_FCN();
#endif

#ifdef IRQ_32_FCN
   extern void IRQ_32_FCN();
#endif

#ifdef IRQ_33_FCN
   extern void IRQ_33_FCN();
#endif

#ifdef IRQ_34_FCN
   extern void IRQ_34_FCN();
#endif

#ifdef IRQ_35_FCN
   extern void IRQ_35_FCN();
#endif

#ifdef IRQ_36_FCN
   extern void IRQ_36_FCN();
#endif

#ifdef IRQ_37_FCN
   extern void IRQ_37_FCN();
#endif

#ifdef IRQ_38_FCN
   extern void IRQ_38_FCN();
#endif

#ifdef IRQ_39_FCN
   extern void IRQ_39_FCN();
#endif

#ifdef IRQ_40_FCN
   extern void IRQ_40_FCN();
#endif

#ifdef IRQ_41_FCN
   extern void IRQ_41_FCN();
#endif

#ifdef IRQ_42_FCN
   extern void IRQ_42_FCN();
#endif

#ifdef IRQ_43_FCN
   extern void IRQ_43_FCN();
#endif

#ifdef IRQ_44_FCN
   extern void IRQ_44_FCN();
#endif

#ifdef IRQ_45_FCN
   extern void IRQ_45_FCN();
#endif

#ifdef IRQ_46_FCN
   extern void IRQ_46_FCN();
#endif

#ifdef IRQ_47_FCN
   extern void IRQ_47_FCN();
#endif

#ifdef IRQ_48_FCN
   extern void IRQ_48_FCN();
#endif

#ifdef IRQ_49_FCN
   extern void IRQ_49_FCN();
#endif

#ifdef IRQ_50_FCN
   extern void IRQ_50_FCN();
#endif

#ifdef IRQ_51_FCN
   extern void IRQ_51_FCN();
#endif

#ifdef IRQ_52_FCN
   extern void IRQ_52_FCN();
#endif

#ifdef IRQ_53_FCN
   extern void IRQ_53_FCN();
#endif

#ifdef IRQ_54_FCN
   extern void IRQ_54_FCN();
#endif

#ifdef IRQ_55_FCN
   extern void IRQ_55_FCN();
#endif

#ifdef IRQ_56_FCN
   extern void IRQ_56_FCN();
#endif

#ifdef IRQ_57_FCN
   extern void IRQ_57_FCN();
#endif

#ifdef IRQ_58_FCN
   extern void IRQ_58_FCN();
#endif

#ifdef IRQ_59_FCN
   extern void IRQ_59_FCN();
#endif

#ifdef IRQ_60_FCN
   extern void IRQ_60_FCN();
#endif

#ifdef IRQ_61_FCN
   extern void IRQ_61_FCN();
#endif

#ifdef IRQ_62_FCN
   extern void IRQ_62_FCN();
#endif

#ifdef IRQ_63_FCN
   extern void IRQ_63_FCN();
#endif

#ifdef IRQ_64_FCN
   extern void IRQ_64_FCN();
#endif

#ifdef IRQ_65_FCN
   extern void IRQ_65_FCN();
#endif

#ifdef IRQ_66_FCN
   extern void IRQ_66_FCN();
#endif

#ifdef IRQ_67_FCN
   extern void IRQ_67_FCN();
#endif

#ifdef IRQ_68_FCN
   extern void IRQ_68_FCN();
#endif

#ifdef IRQ_69_FCN
   extern void IRQ_69_FCN();
#endif

#ifdef IRQ_70_FCN
   extern void IRQ_70_FCN();
#endif

#ifdef IRQ_71_FCN
   extern void IRQ_71_FCN();
#endif

#ifdef IRQ_72_FCN
   extern void IRQ_72_FCN();
#endif

#ifdef IRQ_73_FCN
   extern void IRQ_73_FCN();
#endif

#ifdef IRQ_74_FCN
   extern void IRQ_74_FCN();
#endif

#ifdef IRQ_75_FCN
   extern void IRQ_75_FCN();
#endif

#ifdef IRQ_76_FCN
   extern void IRQ_76_FCN();
#endif

#ifdef IRQ_77_FCN
   extern void IRQ_77_FCN();
#endif

#ifdef IRQ_78_FCN
   extern void IRQ_78_FCN();
#endif

#ifdef IRQ_79_FCN
   extern void IRQ_79_FCN();
#endif

#ifdef IRQ_80_FCN
   extern void IRQ_80_FCN();
#endif

#ifdef IRQ_81_FCN
   extern void IRQ_81_FCN();
#endif

#ifdef IRQ_82_FCN
   extern void IRQ_82_FCN();
#endif

#ifdef IRQ_83_FCN
   extern void IRQ_83_FCN();
#endif

#ifdef IRQ_84_FCN
   extern void IRQ_84_FCN();
#endif

#ifdef IRQ_85_FCN
   extern void IRQ_85_FCN();
#endif

#ifdef IRQ_86_FCN
   extern void IRQ_86_FCN();
#endif

#ifdef IRQ_87_FCN
   extern void IRQ_87_FCN();
#endif

#ifdef IRQ_88_FCN
   extern void IRQ_88_FCN();
#endif

#ifdef IRQ_89_FCN
   extern void IRQ_89_FCN();
#endif

#ifdef IRQ_90_FCN
   extern void IRQ_90_FCN();
#endif

#ifdef IRQ_91_FCN
   extern void IRQ_91_FCN();
#endif

#ifdef IRQ_92_FCN
   extern void IRQ_92_FCN();
#endif

#ifdef IRQ_93_FCN
   extern void IRQ_93_FCN();
#endif

#ifdef IRQ_94_FCN
   extern void IRQ_94_FCN();
#endif

#ifdef IRQ_95_FCN
   extern void IRQ_95_FCN();
#endif

#ifdef IRQ_96_FCN
   extern void IRQ_96_FCN();
#endif

#ifdef IRQ_97_FCN
   extern void IRQ_97_FCN();
#endif

#ifdef IRQ_98_FCN
   extern void IRQ_98_FCN();
#endif

#ifdef IRQ_99_FCN
   extern void IRQ_99_FCN();
#endif

#ifdef IRQ_100_FCN
   extern void IRQ_100_FCN();
#endif

#ifdef IRQ_101_FCN
   extern void IRQ_101_FCN();
#endif

#ifdef IRQ_102_FCN
   extern void IRQ_102_FCN();
#endif

#ifdef IRQ_103_FCN
   extern void IRQ_103_FCN();
#endif

#ifdef IRQ_104_FCN
   extern void IRQ_104_FCN();
#endif

#ifdef IRQ_105_FCN
   extern void IRQ_105_FCN();
#endif

#ifdef IRQ_106_FCN
   extern void IRQ_106_FCN();
#endif

#ifdef IRQ_107_FCN
   extern void IRQ_107_FCN();
#endif

#ifdef IRQ_108_FCN
   extern void IRQ_108_FCN();
#endif

#ifdef IRQ_109_FCN
   extern void IRQ_109_FCN();
#endif

#ifdef IRQ_110_FCN
   extern void IRQ_110_FCN();
#endif

#ifdef IRQ_111_FCN
   extern void IRQ_111_FCN();
#endif

#ifdef IRQ_112_FCN
   extern void IRQ_112_FCN();
#endif

#ifdef IRQ_113_FCN
   extern void IRQ_113_FCN();
#endif

#ifdef IRQ_114_FCN
   extern void IRQ_114_FCN();
#endif

#ifdef IRQ_115_FCN
   extern void IRQ_115_FCN();
#endif

#ifdef IRQ_116_FCN
   extern void IRQ_116_FCN();
#endif

#ifdef IRQ_117_FCN
   extern void IRQ_117_FCN();
#endif

#ifdef IRQ_118_FCN
   extern void IRQ_118_FCN();
#endif

#ifdef IRQ_119_FCN
   extern void IRQ_119_FCN();
#endif

#ifdef IRQ_120_FCN
   extern void IRQ_120_FCN();
#endif

#ifdef IRQ_121_FCN
   extern void IRQ_121_FCN();
#endif

#ifdef IRQ_122_FCN
   extern void IRQ_122_FCN();
#endif

#ifdef IRQ_123_FCN
   extern void IRQ_123_FCN();
#endif

#ifdef IRQ_124_FCN
   extern void IRQ_124_FCN();
#endif

#ifdef IRQ_125_FCN
   extern void IRQ_125_FCN();
#endif

#ifdef IRQ_126_FCN
   extern void IRQ_126_FCN();
#endif

#ifdef IRQ_127_FCN
   extern void IRQ_127_FCN();
#endif

#ifdef IRQ_128_FCN
   extern void IRQ_128_FCN();
#endif

#ifdef IRQ_129_FCN
   extern void IRQ_129_FCN();
#endif

#ifdef IRQ_130_FCN
   extern void IRQ_130_FCN();
#endif

#ifdef IRQ_131_FCN
   extern void IRQ_131_FCN();
#endif

#ifdef IRQ_132_FCN
   extern void IRQ_132_FCN();
#endif

#ifdef IRQ_133_FCN
   extern void IRQ_133_FCN();
#endif

#ifdef IRQ_134_FCN
   extern void IRQ_134_FCN();
#endif

#ifdef IRQ_135_FCN
   extern void IRQ_135_FCN();
#endif

#ifdef IRQ_136_FCN
   extern void IRQ_136_FCN();
#endif

#ifdef IRQ_137_FCN
   extern void IRQ_137_FCN();
#endif

#ifdef IRQ_138_FCN
   extern void IRQ_138_FCN();
#endif

#ifdef IRQ_139_FCN
   extern void IRQ_139_FCN();
#endif

#ifdef IRQ_140_FCN
   extern void IRQ_140_FCN();
#endif

#ifdef IRQ_141_FCN
   extern void IRQ_141_FCN();
#endif

#ifdef IRQ_142_FCN
   extern void IRQ_142_FCN();
#endif

#ifdef IRQ_143_FCN
   extern void IRQ_143_FCN();
#endif

#ifdef IRQ_144_FCN
   extern void IRQ_144_FCN();
#endif

#ifdef IRQ_145_FCN
   extern void IRQ_145_FCN();
#endif

#ifdef IRQ_146_FCN
   extern void IRQ_146_FCN();
#endif

#ifdef IRQ_147_FCN
   extern void IRQ_147_FCN();
#endif

#ifdef IRQ_148_FCN
   extern void IRQ_148_FCN();
#endif

#ifdef IRQ_149_FCN
   extern void IRQ_149_FCN();
#endif

#ifdef IRQ_150_FCN
   extern void IRQ_150_FCN();
#endif

#ifdef IRQ_151_FCN
   extern void IRQ_151_FCN();
#endif

#ifdef IRQ_152_FCN
   extern void IRQ_152_FCN();
#endif

#ifdef IRQ_153_FCN
   extern void IRQ_153_FCN();
#endif

#ifdef IRQ_154_FCN
   extern void IRQ_154_FCN();
#endif

#ifdef IRQ_155_FCN
   extern void IRQ_155_FCN();
#endif

#ifdef IRQ_156_FCN
   extern void IRQ_156_FCN();
#endif

#ifdef IRQ_157_FCN
   extern void IRQ_157_FCN();
#endif

#ifdef IRQ_158_FCN
   extern void IRQ_158_FCN();
#endif

#ifdef IRQ_159_FCN
   extern void IRQ_159_FCN();
#endif

#ifdef IRQ_160_FCN
   extern void IRQ_160_FCN();
#endif

#ifdef IRQ_161_FCN
   extern void IRQ_161_FCN();
#endif

#ifdef IRQ_162_FCN
   extern void IRQ_162_FCN();
#endif

#ifdef IRQ_163_FCN
   extern void IRQ_163_FCN();
#endif

#ifdef IRQ_164_FCN
   extern void IRQ_164_FCN();
#endif

#ifdef IRQ_165_FCN
   extern void IRQ_165_FCN();
#endif

#ifdef IRQ_166_FCN
   extern void IRQ_166_FCN();
#endif

#ifdef IRQ_167_FCN
   extern void IRQ_167_FCN();
#endif

#ifdef IRQ_168_FCN
   extern void IRQ_168_FCN();
#endif

#ifdef IRQ_169_FCN
   extern void IRQ_169_FCN();
#endif

#ifdef IRQ_170_FCN
   extern void IRQ_170_FCN();
#endif

#ifdef IRQ_171_FCN
   extern void IRQ_171_FCN();
#endif

#ifdef IRQ_172_FCN
   extern void IRQ_172_FCN();
#endif

#ifdef IRQ_173_FCN
   extern void IRQ_173_FCN();
#endif

#ifdef IRQ_174_FCN
   extern void IRQ_174_FCN();
#endif

#ifdef IRQ_175_FCN
   extern void IRQ_175_FCN();
#endif

#ifdef IRQ_176_FCN
   extern void IRQ_176_FCN();
#endif

#ifdef IRQ_177_FCN
   extern void IRQ_177_FCN();
#endif

#ifdef IRQ_178_FCN
   extern void IRQ_178_FCN();
#endif

#ifdef IRQ_179_FCN
   extern void IRQ_179_FCN();
#endif

#ifdef IRQ_180_FCN
   extern void IRQ_180_FCN();
#endif

#ifdef IRQ_181_FCN
   extern void IRQ_181_FCN();
#endif

#ifdef IRQ_182_FCN
   extern void IRQ_182_FCN();
#endif

#ifdef IRQ_183_FCN
   extern void IRQ_183_FCN();
#endif

#ifdef IRQ_184_FCN
   extern void IRQ_184_FCN();
#endif

#ifdef IRQ_185_FCN
   extern void IRQ_185_FCN();
#endif

#ifdef IRQ_186_FCN
   extern void IRQ_186_FCN();
#endif

#ifdef IRQ_187_FCN
   extern void IRQ_187_FCN();
#endif

#ifdef IRQ_188_FCN
   extern void IRQ_188_FCN();
#endif

#ifdef IRQ_189_FCN
   extern void IRQ_189_FCN();
#endif

#ifdef IRQ_190_FCN
   extern void IRQ_190_FCN();
#endif

#ifdef IRQ_191_FCN
   extern void IRQ_191_FCN();
#endif

#ifdef IRQ_192_FCN
   extern void IRQ_192_FCN();
#endif

#ifdef IRQ_193_FCN
   extern void IRQ_193_FCN();
#endif

#ifdef IRQ_194_FCN
   extern void IRQ_194_FCN();
#endif

#ifdef IRQ_195_FCN
   extern void IRQ_195_FCN();
#endif

#ifdef IRQ_196_FCN
   extern void IRQ_196_FCN();
#endif

#ifdef IRQ_197_FCN
   extern void IRQ_197_FCN();
#endif

#ifdef IRQ_198_FCN
   extern void IRQ_198_FCN();
#endif

#ifdef IRQ_199_FCN
   extern void IRQ_199_FCN();
#endif

#ifdef IRQ_200_FCN
   extern void IRQ_200_FCN();
#endif

#ifdef IRQ_201_FCN
   extern void IRQ_201_FCN();
#endif

#ifdef IRQ_202_FCN
   extern void IRQ_202_FCN();
#endif

#ifdef IRQ_203_FCN
   extern void IRQ_203_FCN();
#endif

#ifdef IRQ_204_FCN
   extern void IRQ_204_FCN();
#endif

#ifdef IRQ_205_FCN
   extern void IRQ_205_FCN();
#endif

#ifdef IRQ_206_FCN
   extern void IRQ_206_FCN();
#endif

#ifdef IRQ_207_FCN
   extern void IRQ_207_FCN();
#endif

#ifdef IRQ_208_FCN
   extern void IRQ_208_FCN();
#endif

#ifdef IRQ_209_FCN
   extern void IRQ_209_FCN();
#endif

#ifdef IRQ_210_FCN
   extern void IRQ_210_FCN();
#endif

#ifdef IRQ_211_FCN
   extern void IRQ_211_FCN();
#endif

#ifdef IRQ_212_FCN
   extern void IRQ_212_FCN();
#endif

#ifdef IRQ_213_FCN
   extern void IRQ_213_FCN();
#endif

#ifdef IRQ_214_FCN
   extern void IRQ_214_FCN();
#endif

#ifdef IRQ_215_FCN
   extern void IRQ_215_FCN();
#endif

#ifdef IRQ_216_FCN
   extern void IRQ_216_FCN();
#endif

#ifdef IRQ_217_FCN
   extern void IRQ_217_FCN();
#endif

#ifdef IRQ_218_FCN
   extern void IRQ_218_FCN();
#endif

#ifdef IRQ_219_FCN
   extern void IRQ_219_FCN();
#endif

#ifdef IRQ_220_FCN
   extern void IRQ_220_FCN();
#endif

#ifdef IRQ_221_FCN
   extern void IRQ_221_FCN();
#endif
   
   
   
/*******************************************************************************
* Global Variables
*******************************************************************************/
/* Use next line with Green Hills compile */
/* #pragma ghs section rodata=".isrvectbl" */
/* Use pragma next two lines with CodeWarrior compile */
#pragma section const_type ".intc_sw_isr_vector_table" ".intc_sw_isr_vector_table" data_mode=far_abs 

/* Vector Table. ISRs called are: */
/* Software Settable Interrupt 4, Vector 4 */
const uint32 IntcIsrVectorTable[] = {
    #ifdef IRQ_0_FCN             /* ISR 0 */
        (uint32)&IRQ_0_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_1_FCN             /* ISR 1 */
        (uint32)&IRQ_1_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_2_FCN             /* ISR 2 */
        (uint32)&IRQ_2_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_3_FCN             /* ISR 3 */
        (uint32)&IRQ_3_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_4_FCN             /* ISR 4 */
        (uint32)&IRQ_4_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_5_FCN            /* ISR 5 */
        (uint32)&IRQ_5_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_6_FCN             /* ISR 6 */
        (uint32)&IRQ_6_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_7_FCN            /* ISR 7 */
        (uint32)&IRQ_7_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_8_FCN             /* ISR 8 */
        (uint32)&IRQ_8_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_9_FCN             /* ISR 9 */
        (uint32)&IRQ_9_FCN,
    #else
        (uint32)&dummy,
    #endif
    #ifdef IRQ_10_FCN            /* ISR 10 */
        (uint32)&IRQ_10_FCN,
    #else
        (uint32)&dummy,
    #endif
	#ifdef IRQ_11_FCN            /* ISR 11 */
		(uint32)&IRQ_11_FCN,
	#else
		(uint32)&dummy,
	#endif
	#ifdef IRQ_12_FCN            /* ISR 12 */
		(uint32)&IRQ_12_FCN,
	#else
		(uint32)&dummy,
	#endif
	#ifdef IRQ_13_FCN            /* ISR 13 */
		(uint32)&IRQ_13_FCN,
	#else
		(uint32)&dummy,
	#endif
	#ifdef IRQ_14_FCN            /* ISR 14 */
		(uint32)&IRQ_14_FCN,
	#else
		(uint32)&dummy,
	#endif
	#ifdef IRQ_15_FCN            /* ISR 15 */
		(uint32)&IRQ_15_FCN,
	#else
		(uint32)&dummy,
	#endif
                    #ifdef IRQ_16_FCN            /* ISR 16 */
                       (uint32)&IRQ_16_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_17_FCN            /* ISR 17 */
                       (uint32)&IRQ_17_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_18_FCN            /* ISR 18 */
                       (uint32)&IRQ_18_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_19_FCN            /* ISR 19 */
                       (uint32)&IRQ_19_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_20_FCN            /* ISR 20 */
                       (uint32)&IRQ_20_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_21_FCN           /* ISR 21 */
                       (uint32)&IRQ_21_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_22_FCN            /* ISR 22 */
                       (uint32)&IRQ_22_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_23_FCN            /* ISR 23 */
                       (uint32)&IRQ_23_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_24_FCN            /* ISR 24 */
                       (uint32)&IRQ_24_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_25_FCN            /* ISR 25 */
                       (uint32)&IRQ_25_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_26_FCN            /* ISR 26 */
                       (uint32)&IRQ_26_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_27_FCN            /* ISR 27 */
                       (uint32)&IRQ_27_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_28_FCN            /* ISR 28 */
                       (uint32)&IRQ_28_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_29_FCN            /* ISR 29 */
                       (uint32)&IRQ_29_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_30_FCN            /* ISR 30 */
                       (uint32)&IRQ_30_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_31_FCN            /* ISR 31 */
                       (uint32)&IRQ_31_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_32_FCN            /* ISR 32 */
                       (uint32)&IRQ_32_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_33_FCN            /* ISR 33 */
                       (uint32)&IRQ_33_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_34_FCN            /* ISR 34 */
                       (uint32)&IRQ_34_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_35_FCN            /* ISR 35 */
                       (uint32)&IRQ_35_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_36_FCN            /* ISR 36 */
                       (uint32)&IRQ_36_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_37_FCN            /* ISR 37 */
                       (uint32)&IRQ_37_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_38_FCN            /* ISR 38 */
                       (uint32)&IRQ_38_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_39_FCN            /* ISR 39 */
                       (uint32)&IRQ_39_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_40_FCN            /* ISR 40 */
                       (uint32)&IRQ_40_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_41_FCN            /* ISR 41 */
                       (uint32)&IRQ_41_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_42_FCN            /* ISR 42 */
                       (uint32)&IRQ_42_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_43_FCN            /* ISR 43 */
                       (uint32)&IRQ_43_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_44_FCN            /* ISR 44 */
                       (uint32)&IRQ_44_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_45_FCN            /* ISR 45 */
                       (uint32)&IRQ_45_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_46_FCN            /* ISR 46 */
                       (uint32)&IRQ_46_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_47_FCN            /* ISR 47 */
                       (uint32)&IRQ_47_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_48_FCN            /* ISR 48 */
                       (uint32)&IRQ_48_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_49_FCN            /* ISR 49 */
                       (uint32)&IRQ_49_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_50_FCN            /* ISR 50 */
                       (uint32)&IRQ_50_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_51_FCN            /* ISR 51 */
                       (uint32)&IRQ_51_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_52_FCN            /* ISR 52 */
                       (uint32)&IRQ_52_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_53_FCN            /* ISR 53 */
                       (uint32)&IRQ_53_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_54_FCN            /* ISR 54 */
                       (uint32)&IRQ_54_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_55_FCN            /* ISR 55 */
                       (uint32)&IRQ_55_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_56_FCN            /* ISR 56 */
                       (uint32)&IRQ_56_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_57_FCN            /* ISR 57 */
                       (uint32)&IRQ_57_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_58_FCN            /* ISR 58 */
                       (uint32)&IRQ_58_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_59_FCN            /* ISR 59 */
                       (uint32)&IRQ_59_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_60_FCN            /* ISR 60 */
                       (uint32)&IRQ_60_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_61_FCN            /* ISR 61 */
                       (uint32)&IRQ_61_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_62_FCN            /* ISR 62 */
                       (uint32)&IRQ_62_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_63_FCN            /* ISR 63 */
                       (uint32)&IRQ_63_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_64_FCN            /* ISR 64 */
                       (uint32)&IRQ_64_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_65_FCN            /* ISR 65 */
                       (uint32)&IRQ_65_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_66_FCN            /* ISR 66 */
                       (uint32)&IRQ_66_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_67_FCN            /* ISR 67 */
                       (uint32)&IRQ_67_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_68_FCN            /* ISR 68 */
                       (uint32)&IRQ_68_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_69_FCN            /* ISR 69 */
                       (uint32)&IRQ_69_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_70_FCN            /* ISR 70 */
                       (uint32)&IRQ_70_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_71_FCN            /* ISR 71 */
                       (uint32)&IRQ_71_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_72_FCN            /* ISR 72 */
                       (uint32)&IRQ_72_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_73_FCN            /* ISR 73 */
                       (uint32)&IRQ_73_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_74_FCN            /* ISR 74 */
                       (uint32)&IRQ_74_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_75_FCN            /* ISR 75 */
                       (uint32)&IRQ_75_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_76_FCN            /* ISR 76 */
                       (uint32)&IRQ_76_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_77_FCN            /* ISR 77 */
                       (uint32)&IRQ_77_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_78_FCN            /* ISR 78 */
                       (uint32)&IRQ_78_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_79_FCN            /* ISR 79 */
                       (uint32)&IRQ_79_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_80_FCN            /* ISR 80 */
                       (uint32)&IRQ_80_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_81_FCN            /* ISR 81 */
                       (uint32)&IRQ_81_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_82_FCN            /* ISR 82 */
                       (uint32)&IRQ_82_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_83_FCN            /* ISR 83 */
                       (uint32)&IRQ_83_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_84_FCN            /* ISR 84 */
                       (uint32)&IRQ_84_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_85_FCN            /* ISR 85 */
                       (uint32)&IRQ_85_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_86_FCN            /* ISR 86 */
                       (uint32)&IRQ_86_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_87_FCN            /* ISR 87 */
                       (uint32)&IRQ_87_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_88_FCN            /* ISR 88 */
                       (uint32)&IRQ_88_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_89_FCN            /* ISR 89 */
                       (uint32)&IRQ_89_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_90_FCN            /* ISR 90 */
                       (uint32)&IRQ_90_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_91_FCN            /* ISR 91 */
                       (uint32)&IRQ_91_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_92_FCN            /* ISR 92 */
                       (uint32)&IRQ_92_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_93_FCN            /* ISR 93 */
                       (uint32)&IRQ_93_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_94_FCN            /* ISR 94 */
                       (uint32)&IRQ_94_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_95_FCN            /* ISR 95 */
                       (uint32)&IRQ_95_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_96_FCN            /* ISR 96 */
                       (uint32)&IRQ_96_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_97_FCN            /* ISR 97 */
                       (uint32)&IRQ_97_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_98_FCN            /* ISR 98 */
                       (uint32)&IRQ_98_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_99_FCN            /* ISR 99 */
                       (uint32)&IRQ_99_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_100_FCN           /* ISR 100 */
                       (uint32)&IRQ_100_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_101_FCN           /* ISR 101 */
                       (uint32)&IRQ_101_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_102_FCN           /* ISR 102 */
                       (uint32)&IRQ_102_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_103_FCN           /* ISR 103 */
                       (uint32)&IRQ_103_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_104_FCN           /* ISR 104 */
                       (uint32)&IRQ_104_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_105_FCN           /* ISR 105 */
                       (uint32)&IRQ_105_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_106_FCN           /* ISR 106 */
                       (uint32)&IRQ_106_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_107_FCN           /* ISR 107 */
                       (uint32)&IRQ_107_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_108_FCN           /* ISR 108 */
                       (uint32)&IRQ_108_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_109_FCN           /* ISR 109 */
                       (uint32)&IRQ_109_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_110_FCN           /* ISR 110 */
                       (uint32)&IRQ_110_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_111_FCN           /* ISR 111 */
                       (uint32)&IRQ_111_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_112_FCN           /* ISR 112 */
                       (uint32)&IRQ_112_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_113_FCN           /* ISR 113 */
                       (uint32)&IRQ_113_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_114_FCN           /* ISR 114 */
                       (uint32)&IRQ_114_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_115_FCN           /* ISR 115 */
                       (uint32)&IRQ_115_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_116_FCN           /* ISR 116 */
                       (uint32)&IRQ_116_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_117_FCN           /* ISR 117 */
                       (uint32)&IRQ_117_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_118_FCN           /* ISR 118 */
                       (uint32)&IRQ_118_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_119_FCN           /* ISR 119 */
                       (uint32)&IRQ_119_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_120_FCN           /* ISR 120 */
                       (uint32)&IRQ_120_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_121_FCN           /* ISR 121 */
                       (uint32)&IRQ_121_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_122_FCN           /* ISR 122 */
                       (uint32)&IRQ_122_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_123_FCN           /* ISR 123 */
                       (uint32)&IRQ_123_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_124_FCN           /* ISR 124 */
                       (uint32)&IRQ_124_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_125_FCN           /* ISR 125 */
                       (uint32)&IRQ_125_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_126_FCN           /* ISR 126 */
                       (uint32)&IRQ_126_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_127_FCN           /* ISR 127 */
                       (uint32)&IRQ_127_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_128_FCN           /* ISR 128 */
                       (uint32)&IRQ_128_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_129_FCN           /* ISR 129 */
                       (uint32)&IRQ_129_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_130_FCN           /* ISR 130 */
                       (uint32)&IRQ_130_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_131_FCN           /* ISR 131 */
                       (uint32)&IRQ_131_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_132_FCN           /* ISR 132 */
                       (uint32)&IRQ_132_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_133_FCN           /* ISR 133 */
                       (uint32)&IRQ_133_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_134_FCN           /* ISR 134 */
                       (uint32)&IRQ_134_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_135_FCN           /* ISR 135 */
                       (uint32)&IRQ_135_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_136_FCN           /* ISR 136 */
                       (uint32)&IRQ_136_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_137_FCN           /* ISR 137 */
                       (uint32)&IRQ_137_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_138_FCN           /* ISR 138 */
                       (uint32)&IRQ_138_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_139_FCN           /* ISR 139 */
                       (uint32)&IRQ_139_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_140_FCN           /* ISR 140 */
                       (uint32)&IRQ_140_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_141_FCN           /* ISR 141 */
                       (uint32)&IRQ_141_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_142_FCN           /* ISR 142 */
                       (uint32)&IRQ_142_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_143_FCN           /* ISR 143 */
                       (uint32)&IRQ_143_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_144_FCN           /* ISR 144 */
                       (uint32)&IRQ_144_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_145_FCN           /* ISR 145 */
                       (uint32)&IRQ_145_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_146_FCN           /* ISR 146 */
                       (uint32)&IRQ_146_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_147_FCN           /* ISR 147 */
                       (uint32)&IRQ_147_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_148_FCN           /* ISR 148 */
                       (uint32)&IRQ_148_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_149_FCN           /* ISR 149 */
                       (uint32)&IRQ_149_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_150_FCN           /* ISR 150 */
                       (uint32)&IRQ_150_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_151_FCN           /* ISR 151 */
                       (uint32)&IRQ_151_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_152_FCN           /* ISR 152 */
                       (uint32)&IRQ_152_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_153_FCN           /* ISR 153 */
                       (uint32)&IRQ_153_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_154_FCN           /* ISR 154 */
                       (uint32)&IRQ_154_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_155_FCN           /* ISR 155 */
                       (uint32)&IRQ_155_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_156_FCN           /* ISR 156 */
                       (uint32)&IRQ_156_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_157_FCN           /* ISR 157 */
                       (uint32)&IRQ_157_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_158_FCN           /* ISR 158 */
                       (uint32)&IRQ_158_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_159_FCN           /* ISR 159 */
                       (uint32)&IRQ_159_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_160_FCN           /* ISR 160 */
                       (uint32)&IRQ_160_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_161_FCN           /* ISR 161 */
                       (uint32)&IRQ_161_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_162_FCN           /* ISR 162 */
                       (uint32)&IRQ_162_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_163_FCN           /* ISR 163 */
                       (uint32)&IRQ_163_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_164_FCN           /* ISR 164 */
                       (uint32)&IRQ_164_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_165_FCN           /* ISR 165 */
                       (uint32)&IRQ_165_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_166_FCN           /* ISR 166 */
                       (uint32)&IRQ_166_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_167_FCN           /* ISR 167 */
                       (uint32)&IRQ_167_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_168_FCN           /* ISR 168 */
                       (uint32)&IRQ_168_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_169_FCN           /* ISR 169 */
                       (uint32)&IRQ_169_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_170_FCN           /* ISR 170 */
                       (uint32)&IRQ_170_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_171_FCN           /* ISR 171 */
                       (uint32)&IRQ_171_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_172_FCN           /* ISR 172 */
                       (uint32)&IRQ_172_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_173_FCN           /* ISR 173 */
                       (uint32)&IRQ_173_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_174_FCN           /* ISR 174 */
                       (uint32)&IRQ_174_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_175_FCN           /* ISR 175 */
                       (uint32)&IRQ_175_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_176_FCN           /* ISR 176 */
                       (uint32)&IRQ_176_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_177_FCN           /* ISR 177 */
                       (uint32)&IRQ_177_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_178_FCN           /* ISR 178 */
                       (uint32)&IRQ_178_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_179_FCN           /* ISR 179 */
                       (uint32)&IRQ_179_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_180_FCN           /* ISR 180 */
                       (uint32)&IRQ_180_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_181_FCN           /* ISR 181 */
                       (uint32)&IRQ_181_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_182_FCN           /* ISR 182 */
                       (uint32)&IRQ_182_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_183_FCN           /* ISR 183 */
                       (uint32)&IRQ_183_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_184_FCN           /* ISR 184 */
                       (uint32)&IRQ_184_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_185_FCN           /* ISR 185 */
                       (uint32)&IRQ_185_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_186_FCN           /* ISR 186 */
                       (uint32)&IRQ_186_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_187_FCN           /* ISR 187 */
                       (uint32)&IRQ_187_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_188_FCN           /* ISR 188 */
                       (uint32)&IRQ_188_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_189_FCN           /* ISR 189 */
                       (uint32)&IRQ_189_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_190_FCN           /* ISR 190 */
                       (uint32)&IRQ_190_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_191_FCN           /* ISR 191 */
                       (uint32)&IRQ_191_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_192_FCN           /* ISR 192 */
                       (uint32)&IRQ_192_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_193_FCN           /* ISR 193 */
                       (uint32)&IRQ_193_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_194_FCN           /* ISR 194 */
                       (uint32)&IRQ_194_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_195_FCN           /* ISR 195 */
                       (uint32)&IRQ_195_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_196_FCN           /* ISR 196 */
                       (uint32)&IRQ_196_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_197_FCN           /* ISR 197 */
                       (uint32)&IRQ_197_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_198_FCN           /* ISR 198 */
                       (uint32)&IRQ_198_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_199_FCN           /* ISR 199 */
                       (uint32)&IRQ_199_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_200_FCN           /* ISR 200 */
                       (uint32)&IRQ_200_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_201_FCN           /* ISR 201 */
                       (uint32)&IRQ_201_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_202_FCN           /* ISR 202 */
                       (uint32)&IRQ_202_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_203_FCN           /* ISR 203 */
                       (uint32)&IRQ_203_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_204_FCN           /* ISR 204 */
                       (uint32)&IRQ_204_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_205_FCN           /* ISR 205 */
                       (uint32)&IRQ_205_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_206_FCN           /* ISR 206 */
                       (uint32)&IRQ_206_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_207_FCN           /* ISR 207 */
                       (uint32)&IRQ_207_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_208_FCN           /* ISR 208 */
                       (uint32)&IRQ_208_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_209_FCN           /* ISR 209 */
                       (uint32)&IRQ_209_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_210_FCN           /* ISR 210 */
                       (uint32)&IRQ_210_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_211_FCN           /* ISR 211 */
                       (uint32)&IRQ_211_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_212_FCN           /* ISR 212 */
                       (uint32)&IRQ_212_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_213_FCN           /* ISR 213 */
                       (uint32)&IRQ_213_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_214_FCN           /* ISR 214 */
                       (uint32)&IRQ_214_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_215_FCN           /* ISR 215 */
                       (uint32)&IRQ_215_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_216_FCN           /* ISR 216 */
                       (uint32)&IRQ_216_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_217_FCN           /* ISR 217 */
                       (uint32)&IRQ_217_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_218_FCN           /* ISR 218 */
                       (uint32)&IRQ_218_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_219_FCN           /* ISR 219 */
                       (uint32)&IRQ_219_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_220_FCN           /* ISR 220 */
                       (uint32)&IRQ_220_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_221_FCN           /* ISR 221 */
                       (uint32)&IRQ_221_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_222_FCN           /* ISR 222 */
                       (uint32)&IRQ_222_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_223_FCN           /* ISR 223 */
                       (uint32)&IRQ_223_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_224_FCN           /* ISR 224 */
                       (uint32)&IRQ_224_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_225_FCN           /* ISR 225 */
                       (uint32)&IRQ_225_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_226_FCN           /* ISR 226 */
                       (uint32)&IRQ_226_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_227_FCN           /* ISR 227 */
                       (uint32)&IRQ_227_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_228_FCN           /* ISR 228 */
                       (uint32)&IRQ_228_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_229_FCN           /* ISR 229 */
                       (uint32)&IRQ_229_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_230_FCN           /* ISR 230 */
                       (uint32)&IRQ_230_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_231_FCN           /* ISR 231 */
                       (uint32)&IRQ_231_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_232_FCN           /* ISR 232 */
                       (uint32)&IRQ_232_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_233_FCN           /* ISR 233 */
                       (uint32)&IRQ_233_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_234_FCN           /* ISR 234 */
                       (uint32)&IRQ_234_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_235_FCN           /* ISR 235 */
                       (uint32)&IRQ_235_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_236_FCN           /* ISR 236 */
                       (uint32)&IRQ_236_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_237_FCN           /* ISR 237 */
                       (uint32)&IRQ_237_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_238_FCN           /* ISR 238 */
                       (uint32)&IRQ_238_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_239_FCN           /* ISR 239 */
                       (uint32)&IRQ_239_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_240_FCN           /* ISR 240 */
                       (uint32)&IRQ_240_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_241_FCN           /* ISR 241 */
                       (uint32)&IRQ_241_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_242_FCN           /* ISR 242 */
                       (uint32)&IRQ_242_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_243_FCN           /* ISR 243 */
                       (uint32)&IRQ_243_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_244_FCN           /* ISR 244 */
                       (uint32)&IRQ_244_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_245_FCN           /* ISR 245 */
                       (uint32)&IRQ_245_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_246_FCN           /* ISR 246 */
                       (uint32)&IRQ_246_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_247_FCN           /* ISR 247 */
                       (uint32)&IRQ_247_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_248_FCN           /* ISR 248 */
                       (uint32)&IRQ_248_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_249_FCN           /* ISR 249 */
                       (uint32)&IRQ_249_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_250_FCN           /* ISR 250 */
                       (uint32)&IRQ_250_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_251_FCN           /* ISR 251 */
                       (uint32)&IRQ_251_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_252_FCN           /* ISR 252 */
                       (uint32)&IRQ_252_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_253_FCN           /* ISR 253 */
                       (uint32)&IRQ_253_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_254_FCN           /* ISR 254 */
                       (uint32)&IRQ_254_FCN,
                    #else
                       (uint32)&dummy,
                    #endif
                    #ifdef IRQ_255_FCN           /* ISR 255 */
                       (uint32)&IRQ_255_FCN,
                    #else
                       (uint32)&dummy,
                    #endif

};



/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mINTC_Enable_Irq
   Description:     Intc enabled
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void 	mINTC_Enable_Irq(void)
{
	IRQ_ENABLE();					/* Enable external interrupts */
}


/* *****************************************************************************
   Function:        mINTC_SetCurrPriority_Irq
   Description:     Set Intc's Priority
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void 	mINTC_SetCurrPriority_Irq(uint8	Peri)
{
	INTC.CPR.B.PRI = Peri;		/* PRIOR_0 Single Core: Lower INTC's current priority */
}


/* *****************************************************************************
   Function:        dummy
   Description:     Null function
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void    dummy(void)
{
    return;
}


/* *****************************************************************************
   Function:        mINTC_Init
   Description:     init INTC function
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void 	mINTC_Init(void)
{  
#ifdef HVEN_ON
    /* Initialize INTC for hardware vector mode */
    INTC.MCR.B.HVEN = HVEN_HW;
#else
    /* Initialize INTC for software vector mode */
    INTC.MCR.B.HVEN = HVEN_SW; 
    /* Set INTC ISR vector table base addr. */
    INTC.IACKR.R = (uint32) &IntcIsrVectorTable[0];
#endif   

    /* Use the default vector table entry offsets of 4 bytes */
    INTC.MCR.B.VTES = VTES_BYTE4;

#ifdef HVEN_ON
    #ifdef IRQ_59_PRIORITY       /* ISR 59 */
       INTC_InstallINTCInterruptHandler(IRQ_59_FCN_ISR, 59, IRQ_59_PRIORITY);
       INTC.SSCIR[59].R = SSCIR_CLR;
    #endif     
  
#else
    #ifdef IRQ_0_PRIORITY        /* ISR 0 */
       INTC.PSR[0].B.PRI = IRQ_0_PRIORITY;
    #endif
    #ifdef IRQ_1_PRIORITY        /* ISR 1 */
       INTC.PSR[1].B.PRI = IRQ_1_PRIORITY;
    #endif
    #ifdef IRQ_2_PRIORITY        /* ISR 2 */
       INTC.PSR[2].B.PRI = IRQ_2_PRIORITY;
    #endif
    #ifdef IRQ_3_PRIORITY        /* ISR 3 */
       INTC.PSR[3].B.PRI = IRQ_3_PRIORITY;
    #endif
    #ifdef IRQ_4_PRIORITY        /* ISR 4 */
       INTC.PSR[4].B.PRI = IRQ_4_PRIORITY;
    #endif
    #ifdef IRQ_5_PRIORITY        /* ISR 5 */
       INTC.PSR[5].B.PRI = IRQ_5_PRIORITY;
    #endif
    #ifdef IRQ_6_PRIORITY        /* ISR 6 */
       INTC.PSR[6].B.PRI = IRQ_6_PRIORITY;
    #endif
    #ifdef IRQ_7_PRIORITY        /* ISR 7 */
       INTC.PSR[7].B.PRI = IRQ_7_PRIORITY;
    #endif
    #ifdef IRQ_8_PRIORITY        /* ISR 8 */
       INTC.PSR[8].B.PRI = IRQ_8_PRIORITY;
    #endif
    #ifdef IRQ_9_PRIORITY        /* ISR 9 */
       INTC.PSR[9].B.PRI = IRQ_9_PRIORITY;
    #endif
    #ifdef IRQ_10_PRIORITY       /* ISR 10 */
       INTC.PSR[10].B.PRI = IRQ_10_PRIORITY;
    #endif
    #ifdef IRQ_11_PRIORITY       /* ISR 11 */
       INTC.PSR[11].B.PRI = IRQ_11_PRIORITY;
    #endif
    #ifdef IRQ_12_PRIORITY       /* ISR 12 */
       INTC.PSR[12].B.PRI = IRQ_12_PRIORITY;
    #endif
    #ifdef IRQ_13_PRIORITY       /* ISR 13 */
       INTC.PSR[13].B.PRI = IRQ_13_PRIORITY;
    #endif
    #ifdef IRQ_14_PRIORITY       /* ISR 14 */
       INTC.PSR[14].B.PRI = IRQ_14_PRIORITY;
    #endif
    #ifdef IRQ_15_PRIORITY       /* ISR 15 */
       INTC.PSR[15].B.PRI = IRQ_15_PRIORITY;
    #endif
    #ifdef IRQ_16_PRIORITY       /* ISR 16 */
       INTC.PSR[16].B.PRI = IRQ_16_PRIORITY;
    #endif
    #ifdef IRQ_17_PRIORITY       /* ISR 17 */
       INTC.PSR[17].B.PRI = IRQ_17_PRIORITY;
    #endif
    #ifdef IRQ_18_PRIORITY       /* ISR 18 */
       INTC.PSR[18].B.PRI = IRQ_18_PRIORITY;
    #endif
    #ifdef IRQ_19_PRIORITY       /* ISR 19 */
       INTC.PSR[19].B.PRI = IRQ_19_PRIORITY;
    #endif
    #ifdef IRQ_20_PRIORITY       /* ISR 20 */
       INTC.PSR[20].B.PRI = IRQ_20_PRIORITY;
    #endif
    #ifdef IRQ_21_PRIORITY       /* ISR 21 */
       INTC.PSR[21].B.PRI = IRQ_21_PRIORITY;
    #endif
    #ifdef IRQ_22_PRIORITY       /* ISR 22 */
       INTC.PSR[22].B.PRI = IRQ_22_PRIORITY;
    #endif
    #ifdef IRQ_23_PRIORITY       /* ISR 23 */
       INTC.PSR[23].B.PRI = IRQ_23_PRIORITY;
    #endif
    #ifdef IRQ_24_PRIORITY       /* ISR 24 */
       INTC.PSR[24].B.PRI = IRQ_24_PRIORITY;
    #endif
    #ifdef IRQ_25_PRIORITY       /* ISR 25 */
       INTC.PSR[25].B.PRI = IRQ_25_PRIORITY;
    #endif
    #ifdef IRQ_26_PRIORITY       /* ISR 26 */
       INTC.PSR[26].B.PRI = IRQ_26_PRIORITY;
    #endif
    #ifdef IRQ_27_PRIORITY       /* ISR 27 */
       INTC.PSR[27].B.PRI = IRQ_27_PRIORITY;
    #endif
    #ifdef IRQ_28_PRIORITY       /* ISR 28 */
       INTC.PSR[28].B.PRI = IRQ_28_PRIORITY;
    #endif
    #ifdef IRQ_29_PRIORITY       /* ISR 29 */
       INTC.PSR[29].B.PRI = IRQ_29_PRIORITY;
    #endif
    #ifdef IRQ_30_PRIORITY       /* ISR 30 */
       INTC.PSR[30].B.PRI = IRQ_30_PRIORITY;
    #endif
    #ifdef IRQ_31_PRIORITY       /* ISR 31 */
       INTC.PSR[31].B.PRI = IRQ_31_PRIORITY;
    #endif
    #ifdef IRQ_32_PRIORITY       /* ISR 32 */
       INTC.PSR[32].B.PRI = IRQ_32_PRIORITY;
    #endif
    #ifdef IRQ_33_PRIORITY       /* ISR 33 */
       INTC.PSR[33].B.PRI = IRQ_33_PRIORITY;
    #endif
    #ifdef IRQ_34_PRIORITY       /* ISR 34 */
       INTC.PSR[34].B.PRI = IRQ_34_PRIORITY;
    #endif
    #ifdef IRQ_35_PRIORITY       /* ISR 35 */
       INTC.PSR[35].B.PRI = IRQ_35_PRIORITY;
    #endif
    #ifdef IRQ_36_PRIORITY       /* ISR 36 */
       INTC.PSR[36].B.PRI = IRQ_36_PRIORITY;
    #endif
    #ifdef IRQ_37_PRIORITY       /* ISR 37 */
       INTC.PSR[37].B.PRI = IRQ_37_PRIORITY;
    #endif
    #ifdef IRQ_38_PRIORITY       /* ISR 38 */
       INTC.PSR[38].B.PRI = IRQ_38_PRIORITY;
    #endif
    #ifdef IRQ_39_PRIORITY       /* ISR 39 */
       INTC.PSR[39].B.PRI = IRQ_39_PRIORITY;
    #endif
    #ifdef IRQ_40_PRIORITY       /* ISR 40 */
       INTC.PSR[40].B.PRI = IRQ_40_PRIORITY;
    #endif
    #ifdef IRQ_41_PRIORITY       /* ISR 41 */
       INTC.PSR[41].B.PRI = IRQ_41_PRIORITY;
    #endif
    #ifdef IRQ_42_PRIORITY       /* ISR 42 */
       INTC.PSR[42].B.PRI = IRQ_42_PRIORITY;
    #endif
    #ifdef IRQ_43_PRIORITY       /* ISR 43 */
       INTC.PSR[43].B.PRI = IRQ_43_PRIORITY;
    #endif
    #ifdef IRQ_44_PRIORITY       /* ISR 44 */
       INTC.PSR[44].B.PRI = IRQ_44_PRIORITY;
    #endif
    #ifdef IRQ_45_PRIORITY       /* ISR 45 */
       INTC.PSR[45].B.PRI = IRQ_45_PRIORITY;
    #endif
    #ifdef IRQ_46_PRIORITY       /* ISR 46 */
       INTC.PSR[46].B.PRI = IRQ_46_PRIORITY;
    #endif
    #ifdef IRQ_47_PRIORITY       /* ISR 47 */
       INTC.PSR[47].B.PRI = IRQ_47_PRIORITY;
    #endif
    #ifdef IRQ_48_PRIORITY       /* ISR 48 */
       INTC.PSR[48].B.PRI = IRQ_48_PRIORITY;
    #endif
    #ifdef IRQ_49_PRIORITY       /* ISR 49 */
       INTC.PSR[49].B.PRI = IRQ_49_PRIORITY;
    #endif
    #ifdef IRQ_50_PRIORITY       /* ISR 50 */
       INTC.PSR[50].B.PRI = IRQ_50_PRIORITY;
    #endif
    #ifdef IRQ_51_PRIORITY       /* ISR 51 */
       INTC.PSR[51].B.PRI = IRQ_51_PRIORITY;
    #endif
    #ifdef IRQ_52_PRIORITY       /* ISR 52 */
       INTC.PSR[52].B.PRI = IRQ_52_PRIORITY;
    #endif
    #ifdef IRQ_53_PRIORITY       /* ISR 53 */
       INTC.PSR[53].B.PRI = IRQ_53_PRIORITY;
    #endif
    #ifdef IRQ_54_PRIORITY       /* ISR 54 */
       INTC.PSR[54].B.PRI = IRQ_54_PRIORITY;
    #endif
    #ifdef IRQ_55_PRIORITY       /* ISR 55 */
       INTC.PSR[55].B.PRI = IRQ_55_PRIORITY;
    #endif
    #ifdef IRQ_56_PRIORITY       /* ISR 56 */
       INTC.PSR[56].B.PRI = IRQ_56_PRIORITY;
    #endif
    #ifdef IRQ_57_PRIORITY       /* ISR 57 */
       INTC.PSR[57].B.PRI = IRQ_57_PRIORITY;
    #endif
    #ifdef IRQ_58_PRIORITY       /* ISR 58 */
       INTC.PSR[58].B.PRI = IRQ_58_PRIORITY;
    #endif
    #ifdef IRQ_59_PRIORITY       /* ISR 59 */
       INTC.PSR[59].B.PRI = IRQ_59_PRIORITY;
    #endif
    #ifdef IRQ_60_PRIORITY       /* ISR 60 */
       INTC.PSR[60].B.PRI = IRQ_60_PRIORITY;
    #endif
    #ifdef IRQ_61_PRIORITY       /* ISR 61 */
       INTC.PSR[61].B.PRI = IRQ_61_PRIORITY;
    #endif
    #ifdef IRQ_62_PRIORITY       /* ISR 62 */
       INTC.PSR[62].B.PRI = IRQ_62_PRIORITY;
    #endif
    #ifdef IRQ_63_PRIORITY       /* ISR 63 */
       INTC.PSR[63].B.PRI = IRQ_63_PRIORITY;
    #endif
    #ifdef IRQ_64_PRIORITY       /* ISR 64 */
       INTC.PSR[64].B.PRI = IRQ_64_PRIORITY;
    #endif
    #ifdef IRQ_65_PRIORITY       /* ISR 65 */
       INTC.PSR[65].B.PRI = IRQ_65_PRIORITY;
    #endif
    #ifdef IRQ_66_PRIORITY       /* ISR 66 */
       INTC.PSR[66].B.PRI = IRQ_66_PRIORITY;
    #endif
    #ifdef IRQ_67_PRIORITY       /* ISR 67 */
       INTC.PSR[67].B.PRI = IRQ_67_PRIORITY;
    #endif
    #ifdef IRQ_68_PRIORITY       /* ISR 68 */
       INTC.PSR[68].B.PRI = IRQ_68_PRIORITY;
    #endif
    #ifdef IRQ_69_PRIORITY       /* ISR 69 */
       INTC.PSR[69].B.PRI = IRQ_69_PRIORITY;
    #endif
    #ifdef IRQ_70_PRIORITY       /* ISR 70 */
       INTC.PSR[70].B.PRI = IRQ_70_PRIORITY;
    #endif
    #ifdef IRQ_71_PRIORITY       /* ISR 71 */
       INTC.PSR[71].B.PRI = IRQ_71_PRIORITY;
    #endif
    #ifdef IRQ_72_PRIORITY       /* ISR 72 */
       INTC.PSR[72].B.PRI = IRQ_72_PRIORITY;
    #endif
    #ifdef IRQ_73_PRIORITY       /* ISR 73 */
       INTC.PSR[73].B.PRI = IRQ_73_PRIORITY;
    #endif
    #ifdef IRQ_74_PRIORITY       /* ISR 74 */
       INTC.PSR[74].B.PRI = IRQ_74_PRIORITY;
    #endif
    #ifdef IRQ_75_PRIORITY       /* ISR 75 */
       INTC.PSR[75].B.PRI = IRQ_75_PRIORITY;
    #endif
    #ifdef IRQ_76_PRIORITY       /* ISR 76 */
       INTC.PSR[76].B.PRI = IRQ_76_PRIORITY;
    #endif
    #ifdef IRQ_77_PRIORITY       /* ISR 77 */
       INTC.PSR[77].B.PRI = IRQ_77_PRIORITY;
    #endif
    #ifdef IRQ_78_PRIORITY       /* ISR 78 */
       INTC.PSR[78].B.PRI = IRQ_78_PRIORITY;
    #endif
    #ifdef IRQ_79_PRIORITY       /* ISR 79 */
       INTC.PSR[79].B.PRI = IRQ_79_PRIORITY;
    #endif
    #ifdef IRQ_80_PRIORITY       /* ISR 80 */
       INTC.PSR[80].B.PRI = IRQ_80_PRIORITY;
    #endif
    #ifdef IRQ_81_PRIORITY       /* ISR 81 */
       INTC.PSR[81].B.PRI = IRQ_81_PRIORITY;
    #endif
    #ifdef IRQ_82_PRIORITY       /* ISR 82 */
       INTC.PSR[82].B.PRI = IRQ_82_PRIORITY;
    #endif
    #ifdef IRQ_83_PRIORITY       /* ISR 83 */
       INTC.PSR[83].B.PRI = IRQ_83_PRIORITY;
    #endif
    #ifdef IRQ_84_PRIORITY       /* ISR 84 */
       INTC.PSR[84].B.PRI = IRQ_84_PRIORITY;
    #endif
    #ifdef IRQ_85_PRIORITY       /* ISR 85 */
       INTC.PSR[85].B.PRI = IRQ_85_PRIORITY;
    #endif
    #ifdef IRQ_86_PRIORITY       /* ISR 86 */
       INTC.PSR[86].B.PRI = IRQ_86_PRIORITY;
    #endif
    #ifdef IRQ_87_PRIORITY       /* ISR 87 */
       INTC.PSR[87].B.PRI = IRQ_87_PRIORITY;
    #endif
    #ifdef IRQ_88_PRIORITY       /* ISR 88 */
       INTC.PSR[88].B.PRI = IRQ_88_PRIORITY;
    #endif
    #ifdef IRQ_89_PRIORITY       /* ISR 89 */
       INTC.PSR[89].B.PRI = IRQ_89_PRIORITY;
    #endif
    #ifdef IRQ_90_PRIORITY       /* ISR 90 */
       INTC.PSR[90].B.PRI = IRQ_90_PRIORITY;
    #endif
    #ifdef IRQ_91_PRIORITY       /* ISR 91 */
       INTC.PSR[91].B.PRI = IRQ_91_PRIORITY;
    #endif
    #ifdef IRQ_92_PRIORITY       /* ISR 92 */
       INTC.PSR[92].B.PRI = IRQ_92_PRIORITY;
    #endif
    #ifdef IRQ_93_PRIORITY       /* ISR 93 */
       INTC.PSR[93].B.PRI = IRQ_93_PRIORITY;
    #endif
    #ifdef IRQ_94_PRIORITY       /* ISR 94 */
       INTC.PSR[94].B.PRI = IRQ_94_PRIORITY;
    #endif
    #ifdef IRQ_95_PRIORITY       /* ISR 95 */
       INTC.PSR[95].B.PRI = IRQ_95_PRIORITY;
    #endif
    #ifdef IRQ_96_PRIORITY       /* ISR 96 */
       INTC.PSR[96].B.PRI = IRQ_96_PRIORITY;
    #endif
    #ifdef IRQ_97_PRIORITY       /* ISR 97 */
       INTC.PSR[97].B.PRI = IRQ_97_PRIORITY;
    #endif
    #ifdef IRQ_98_PRIORITY       /* ISR 98 */
       INTC.PSR[98].B.PRI = IRQ_98_PRIORITY;
    #endif
    #ifdef IRQ_99_PRIORITY       /* ISR 99 */
       INTC.PSR[99].B.PRI = IRQ_99_PRIORITY;
    #endif
    #ifdef IRQ_100_PRIORITY      /* ISR 100 */
       INTC.PSR[100].B.PRI = IRQ_100_PRIORITY;
    #endif
    #ifdef IRQ_101_PRIORITY      /* ISR 101 */
       INTC.PSR[101].B.PRI = IRQ_101_PRIORITY;
    #endif
    #ifdef IRQ_102_PRIORITY      /* ISR 102 */
       INTC.PSR[102].B.PRI = IRQ_102_PRIORITY;
    #endif
    #ifdef IRQ_103_PRIORITY      /* ISR 103 */
       INTC.PSR[103].B.PRI = IRQ_103_PRIORITY;
    #endif
    #ifdef IRQ_104_PRIORITY      /* ISR 104 */
       INTC.PSR[104].B.PRI = IRQ_104_PRIORITY;
    #endif
    #ifdef IRQ_105_PRIORITY      /* ISR 105 */
       INTC.PSR[105].B.PRI = IRQ_105_PRIORITY;
    #endif
    #ifdef IRQ_106_PRIORITY      /* ISR 106 */
       INTC.PSR[106].B.PRI = IRQ_106_PRIORITY;
    #endif
    #ifdef IRQ_107_PRIORITY      /* ISR 107 */
       INTC.PSR[107].B.PRI = IRQ_107_PRIORITY;
    #endif
    #ifdef IRQ_108_PRIORITY      /* ISR 108 */
       INTC.PSR[108].B.PRI = IRQ_108_PRIORITY;
    #endif
    #ifdef IRQ_109_PRIORITY      /* ISR 109 */
       INTC.PSR[109].B.PRI = IRQ_109_PRIORITY;
    #endif
    #ifdef IRQ_110_PRIORITY      /* ISR 110 */
       INTC.PSR[110].B.PRI = IRQ_110_PRIORITY;
    #endif
    #ifdef IRQ_111_PRIORITY      /* ISR 111 */
       INTC.PSR[111].B.PRI = IRQ_111_PRIORITY;
    #endif
    #ifdef IRQ_112_PRIORITY      /* ISR 112 */
       INTC.PSR[112].B.PRI = IRQ_112_PRIORITY;
    #endif
    #ifdef IRQ_113_PRIORITY      /* ISR 113 */
       INTC.PSR[113].B.PRI = IRQ_113_PRIORITY;
    #endif
    #ifdef IRQ_114_PRIORITY      /* ISR 114 */
       INTC.PSR[114].B.PRI = IRQ_114_PRIORITY;
    #endif
    #ifdef IRQ_115_PRIORITY      /* ISR 115 */
       INTC.PSR[115].B.PRI = IRQ_115_PRIORITY;
    #endif
    #ifdef IRQ_116_PRIORITY      /* ISR 116 */
       INTC.PSR[116].B.PRI = IRQ_116_PRIORITY;
    #endif
    #ifdef IRQ_117_PRIORITY      /* ISR 117 */
       INTC.PSR[117].B.PRI = IRQ_117_PRIORITY;
    #endif
    #ifdef IRQ_118_PRIORITY      /* ISR 118 */
       INTC.PSR[118].B.PRI = IRQ_118_PRIORITY;
    #endif
    #ifdef IRQ_119_PRIORITY      /* ISR 119 */
       INTC.PSR[119].B.PRI = IRQ_119_PRIORITY;
    #endif
    #ifdef IRQ_120_PRIORITY      /* ISR 120 */
       INTC.PSR[120].B.PRI = IRQ_120_PRIORITY;
    #endif
    #ifdef IRQ_121_PRIORITY      /* ISR 121 */
       INTC.PSR[121].B.PRI = IRQ_121_PRIORITY;
    #endif
    #ifdef IRQ_122_PRIORITY      /* ISR 122 */
       INTC.PSR[122].B.PRI = IRQ_122_PRIORITY;
    #endif
    #ifdef IRQ_123_PRIORITY      /* ISR 123 */
       INTC.PSR[123].B.PRI = IRQ_123_PRIORITY;
    #endif
    #ifdef IRQ_124_PRIORITY      /* ISR 124 */
       INTC.PSR[124].B.PRI = IRQ_124_PRIORITY;
    #endif
    #ifdef IRQ_125_PRIORITY      /* ISR 125 */
       INTC.PSR[125].B.PRI = IRQ_125_PRIORITY;
    #endif
    #ifdef IRQ_126_PRIORITY      /* ISR 126 */
       INTC.PSR[126].B.PRI = IRQ_126_PRIORITY;
    #endif
    #ifdef IRQ_127_PRIORITY      /* ISR 127 */
       INTC.PSR[127].B.PRI = IRQ_127_PRIORITY;
    #endif
    #ifdef IRQ_128_PRIORITY      /* ISR 128 */
       INTC.PSR[128].B.PRI = IRQ_128_PRIORITY;
    #endif
    #ifdef IRQ_129_PRIORITY      /* ISR 129 */
       INTC.PSR[129].B.PRI = IRQ_129_PRIORITY;
    #endif
    #ifdef IRQ_130_PRIORITY      /* ISR 130 */
       INTC.PSR[130].B.PRI = IRQ_130_PRIORITY;
    #endif
    #ifdef IRQ_131_PRIORITY      /* ISR 131 */
       INTC.PSR[131].B.PRI = IRQ_131_PRIORITY;
    #endif
    #ifdef IRQ_132_PRIORITY      /* ISR 132 */
       INTC.PSR[132].B.PRI = IRQ_132_PRIORITY;
    #endif
    #ifdef IRQ_133_PRIORITY      /* ISR 133 */
       INTC.PSR[133].B.PRI = IRQ_133_PRIORITY;
    #endif
    #ifdef IRQ_134_PRIORITY      /* ISR 134 */
       INTC.PSR[134].B.PRI = IRQ_134_PRIORITY;
    #endif
    #ifdef IRQ_135_PRIORITY      /* ISR 135 */
       INTC.PSR[135].B.PRI = IRQ_135_PRIORITY;
    #endif
    #ifdef IRQ_136_PRIORITY      /* ISR 136 */
       INTC.PSR[136].B.PRI = IRQ_136_PRIORITY;
    #endif
    #ifdef IRQ_137_PRIORITY      /* ISR 137 */
       INTC.PSR[137].B.PRI = IRQ_137_PRIORITY;
    #endif
    #ifdef IRQ_138_PRIORITY      /* ISR 138 */
       INTC.PSR[138].B.PRI = IRQ_138_PRIORITY;
    #endif
    #ifdef IRQ_139_PRIORITY      /* ISR 139 */
       INTC.PSR[139].B.PRI = IRQ_139_PRIORITY;
    #endif
    #ifdef IRQ_140_PRIORITY      /* ISR 140 */
       INTC.PSR[140].B.PRI = IRQ_140_PRIORITY;
    #endif
    #ifdef IRQ_141_PRIORITY      /* ISR 141 */
       INTC.PSR[141].B.PRI = IRQ_141_PRIORITY;
    #endif
    #ifdef IRQ_142_PRIORITY      /* ISR 142 */
       INTC.PSR[142].B.PRI = IRQ_142_PRIORITY;
    #endif
    #ifdef IRQ_143_PRIORITY      /* ISR 143 */
       INTC.PSR[143].B.PRI = IRQ_143_PRIORITY;
    #endif
    #ifdef IRQ_144_PRIORITY      /* ISR 144 */
       INTC.PSR[144].B.PRI = IRQ_144_PRIORITY;
    #endif
    #ifdef IRQ_145_PRIORITY      /* ISR 145 */
       INTC.PSR[145].B.PRI = IRQ_145_PRIORITY;
    #endif
    #ifdef IRQ_146_PRIORITY      /* ISR 146 */
       INTC.PSR[146].B.PRI = IRQ_146_PRIORITY;
    #endif
    #ifdef IRQ_147_PRIORITY      /* ISR 147 */
       INTC.PSR[147].B.PRI = IRQ_147_PRIORITY;
    #endif
    #ifdef IRQ_148_PRIORITY      /* ISR 148 */
       INTC.PSR[148].B.PRI = IRQ_148_PRIORITY;
    #endif
    #ifdef IRQ_149_PRIORITY      /* ISR 149 */
       INTC.PSR[149].B.PRI = IRQ_149_PRIORITY;
    #endif
    #ifdef IRQ_150_PRIORITY      /* ISR 150 */
       INTC.PSR[150].B.PRI = IRQ_150_PRIORITY;
    #endif
    #ifdef IRQ_151_PRIORITY      /* ISR 151 */
       INTC.PSR[151].B.PRI = IRQ_151_PRIORITY;
    #endif
    #ifdef IRQ_152_PRIORITY      /* ISR 152 */
       INTC.PSR[152].B.PRI = IRQ_152_PRIORITY;
    #endif
    #ifdef IRQ_153_PRIORITY      /* ISR 153 */
       INTC.PSR[153].B.PRI = IRQ_153_PRIORITY;
    #endif
    #ifdef IRQ_154_PRIORITY      /* ISR 154 */
       INTC.PSR[154].B.PRI = IRQ_154_PRIORITY;
    #endif
    #ifdef IRQ_155_PRIORITY      /* ISR 155 */
       INTC.PSR[155].B.PRI = IRQ_155_PRIORITY;
    #endif
    #ifdef IRQ_156_PRIORITY      /* ISR 156 */
       INTC.PSR[156].B.PRI = IRQ_156_PRIORITY;
    #endif
    #ifdef IRQ_157_PRIORITY      /* ISR 157 */
       INTC.PSR[157].B.PRI = IRQ_157_PRIORITY;
    #endif
    #ifdef IRQ_158_PRIORITY      /* ISR 158 */
       INTC.PSR[158].B.PRI = IRQ_158_PRIORITY;
    #endif
    #ifdef IRQ_159_PRIORITY      /* ISR 159 */
       INTC.PSR[159].B.PRI = IRQ_159_PRIORITY;
    #endif
    #ifdef IRQ_160_PRIORITY      /* ISR 160 */
       INTC.PSR[160].B.PRI = IRQ_160_PRIORITY;
    #endif
    #ifdef IRQ_161_PRIORITY      /* ISR 161 */
       INTC.PSR[161].B.PRI = IRQ_161_PRIORITY;
    #endif
    #ifdef IRQ_162_PRIORITY      /* ISR 162 */
       INTC.PSR[162].B.PRI = IRQ_162_PRIORITY;
    #endif
    #ifdef IRQ_163_PRIORITY      /* ISR 163 */
       INTC.PSR[163].B.PRI = IRQ_163_PRIORITY;
    #endif
    #ifdef IRQ_164_PRIORITY      /* ISR 164 */
       INTC.PSR[164].B.PRI = IRQ_164_PRIORITY;
    #endif
    #ifdef IRQ_165_PRIORITY      /* ISR 165 */
       INTC.PSR[165].B.PRI = IRQ_165_PRIORITY;
    #endif
    #ifdef IRQ_166_PRIORITY      /* ISR 166 */
       INTC.PSR[166].B.PRI = IRQ_166_PRIORITY;
    #endif
    #ifdef IRQ_167_PRIORITY      /* ISR 167 */
       INTC.PSR[167].B.PRI = IRQ_167_PRIORITY;
    #endif
    #ifdef IRQ_168_PRIORITY      /* ISR 168 */
       INTC.PSR[168].B.PRI = IRQ_168_PRIORITY;
    #endif
    #ifdef IRQ_169_PRIORITY      /* ISR 169 */
       INTC.PSR[169].B.PRI = IRQ_169_PRIORITY;
    #endif
    #ifdef IRQ_170_PRIORITY      /* ISR 170 */
       INTC.PSR[170].B.PRI = IRQ_170_PRIORITY;
    #endif
    #ifdef IRQ_171_PRIORITY      /* ISR 171 */
       INTC.PSR[171].B.PRI = IRQ_171_PRIORITY;
    #endif
    #ifdef IRQ_172_PRIORITY      /* ISR 172 */
       INTC.PSR[172].B.PRI = IRQ_172_PRIORITY;
    #endif
    #ifdef IRQ_173_PRIORITY      /* ISR 173 */
       INTC.PSR[173].B.PRI = IRQ_173_PRIORITY;
    #endif
    #ifdef IRQ_174_PRIORITY      /* ISR 174 */
       INTC.PSR[174].B.PRI = IRQ_174_PRIORITY;
    #endif
    #ifdef IRQ_175_PRIORITY      /* ISR 175 */
       INTC.PSR[175].B.PRI = IRQ_175_PRIORITY;
    #endif
    #ifdef IRQ_176_PRIORITY      /* ISR 176 */
       INTC.PSR[176].B.PRI = IRQ_176_PRIORITY;
    #endif
    #ifdef IRQ_177_PRIORITY      /* ISR 177 */
       INTC.PSR[177].B.PRI = IRQ_177_PRIORITY;
    #endif
    #ifdef IRQ_178_PRIORITY      /* ISR 178 */
       INTC.PSR[178].B.PRI = IRQ_178_PRIORITY;
    #endif
    #ifdef IRQ_179_PRIORITY      /* ISR 179 */
       INTC.PSR[179].B.PRI = IRQ_179_PRIORITY;
    #endif
    #ifdef IRQ_180_PRIORITY      /* ISR 180 */
       INTC.PSR[180].B.PRI = IRQ_180_PRIORITY;
    #endif
    #ifdef IRQ_181_PRIORITY      /* ISR 181 */
       INTC.PSR[181].B.PRI = IRQ_181_PRIORITY;
    #endif
    #ifdef IRQ_182_PRIORITY      /* ISR 182 */
       INTC.PSR[182].B.PRI = IRQ_182_PRIORITY;
    #endif
    #ifdef IRQ_183_PRIORITY      /* ISR 183 */
       INTC.PSR[183].B.PRI = IRQ_183_PRIORITY;
    #endif
    #ifdef IRQ_184_PRIORITY      /* ISR 184 */
       INTC.PSR[184].B.PRI = IRQ_184_PRIORITY;
    #endif
    #ifdef IRQ_185_PRIORITY      /* ISR 185 */
       INTC.PSR[185].B.PRI = IRQ_185_PRIORITY;
    #endif
    #ifdef IRQ_186_PRIORITY      /* ISR 186 */
       INTC.PSR[186].B.PRI = IRQ_186_PRIORITY;
    #endif
    #ifdef IRQ_187_PRIORITY      /* ISR 187 */
       INTC.PSR[187].B.PRI = IRQ_187_PRIORITY;
    #endif
    #ifdef IRQ_188_PRIORITY      /* ISR 188 */
       INTC.PSR[188].B.PRI = IRQ_188_PRIORITY;
    #endif
    #ifdef IRQ_189_PRIORITY      /* ISR 189 */
       INTC.PSR[189].B.PRI = IRQ_189_PRIORITY;
    #endif
    #ifdef IRQ_190_PRIORITY      /* ISR 190 */
       INTC.PSR[190].B.PRI = IRQ_190_PRIORITY;
    #endif
    #ifdef IRQ_191_PRIORITY      /* ISR 191 */
       INTC.PSR[191].B.PRI = IRQ_191_PRIORITY;
    #endif
    #ifdef IRQ_192_PRIORITY      /* ISR 192 */
       INTC.PSR[192].B.PRI = IRQ_192_PRIORITY;
    #endif
    #ifdef IRQ_193_PRIORITY      /* ISR 193 */
       INTC.PSR[193].B.PRI = IRQ_193_PRIORITY;
    #endif
    #ifdef IRQ_194_PRIORITY      /* ISR 194 */
       INTC.PSR[194].B.PRI = IRQ_194_PRIORITY;
    #endif
    #ifdef IRQ_195_PRIORITY      /* ISR 195 */
       INTC.PSR[195].B.PRI = IRQ_195_PRIORITY;
    #endif
    #ifdef IRQ_196_PRIORITY      /* ISR 196 */
       INTC.PSR[196].B.PRI = IRQ_196_PRIORITY;
    #endif
    #ifdef IRQ_197_PRIORITY      /* ISR 197 */
       INTC.PSR[197].B.PRI = IRQ_197_PRIORITY;
    #endif
    #ifdef IRQ_198_PRIORITY      /* ISR 198 */
       INTC.PSR[198].B.PRI = IRQ_198_PRIORITY;
    #endif
    #ifdef IRQ_199_PRIORITY      /* ISR 199 */
       INTC.PSR[199].B.PRI = IRQ_199_PRIORITY;
    #endif
    #ifdef IRQ_200_PRIORITY      /* ISR 200 */
       INTC.PSR[200].B.PRI = IRQ_200_PRIORITY;
    #endif
    #ifdef IRQ_201_PRIORITY      /* ISR 201 */
       INTC.PSR[201].B.PRI = IRQ_201_PRIORITY;
    #endif
    #ifdef IRQ_202_PRIORITY      /* ISR 202 */
       INTC.PSR[202].B.PRI = IRQ_202_PRIORITY;
    #endif
    #ifdef IRQ_203_PRIORITY      /* ISR 203 */
       INTC.PSR[203].B.PRI = IRQ_203_PRIORITY;
    #endif
    #ifdef IRQ_204_PRIORITY      /* ISR 204 */
       INTC.PSR[204].B.PRI = IRQ_204_PRIORITY;
    #endif
    #ifdef IRQ_205_PRIORITY      /* ISR 205 */
       INTC.PSR[205].B.PRI = IRQ_205_PRIORITY;
    #endif
    #ifdef IRQ_206_PRIORITY      /* ISR 206 */
       INTC.PSR[206].B.PRI = IRQ_206_PRIORITY;
    #endif
    #ifdef IRQ_207_PRIORITY      /* ISR 207 */
       INTC.PSR[207].B.PRI = IRQ_207_PRIORITY;
    #endif
    #ifdef IRQ_208_PRIORITY      /* ISR 208 */
       INTC.PSR[208].B.PRI = IRQ_208_PRIORITY;
    #endif
    #ifdef IRQ_209_PRIORITY      /* ISR 209 */
       INTC.PSR[209].B.PRI = IRQ_209_PRIORITY;
    #endif
    #ifdef IRQ_210_PRIORITY      /* ISR 210 */
       INTC.PSR[210].B.PRI = IRQ_210_PRIORITY;
    #endif
    #ifdef IRQ_211_PRIORITY      /* ISR 211 */
       INTC.PSR[211].B.PRI = IRQ_211_PRIORITY;
    #endif
    #ifdef IRQ_212_PRIORITY      /* ISR 212 */
       INTC.PSR[212].B.PRI = IRQ_212_PRIORITY;
    #endif
    #ifdef IRQ_213_PRIORITY      /* ISR 213 */
       INTC.PSR[213].B.PRI = IRQ_213_PRIORITY;
    #endif
    #ifdef IRQ_214_PRIORITY      /* ISR 214 */
       INTC.PSR[214].B.PRI = IRQ_214_PRIORITY;
    #endif
    #ifdef IRQ_215_PRIORITY      /* ISR 215 */
       INTC.PSR[215].B.PRI = IRQ_215_PRIORITY;
    #endif
    #ifdef IRQ_216_PRIORITY      /* ISR 216 */
       INTC.PSR[216].B.PRI = IRQ_216_PRIORITY;
    #endif
    #ifdef IRQ_217_PRIORITY      /* ISR 217 */
       INTC.PSR[217].B.PRI = IRQ_217_PRIORITY;
    #endif
    #ifdef IRQ_218_PRIORITY      /* ISR 218 */
       INTC.PSR[218].B.PRI = IRQ_218_PRIORITY;
    #endif
    #ifdef IRQ_219_PRIORITY      /* ISR 219 */
       INTC.PSR[219].B.PRI = IRQ_219_PRIORITY;
    #endif
    #ifdef IRQ_220_PRIORITY      /* ISR 220 */
       INTC.PSR[220].B.PRI = IRQ_220_PRIORITY;
    #endif
    #ifdef IRQ_221_PRIORITY      /* ISR 221 */
       INTC.PSR[221].B.PRI = IRQ_221_PRIORITY;
    #endif
#endif
}
 




/* End of file */