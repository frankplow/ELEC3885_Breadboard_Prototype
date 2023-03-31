/*
 * ov5640_registers.h
 *
 *  Created on: Mar 7, 2023
 *      Author: sol
 */

#ifndef INC_OV5640_REGISTERS_H_
#define INC_OV5640_REGISTERS_H_
/* system control registers */
#define SYSTEM_CTROL0   0x3008  // Bit[7]: Software reset
                                // Bit[6]: Software power down
                                // Bit[5]: Reserved
                                // Bit[4]: SRB clock SYNC enable
                                // Bit[3]: Isolation suspend select
                                // Bit[2:0]: Not used

#define DRIVE_CAPABILITY 0x302c // Bit[7:6]:
                                //          00: 1x
                                //          01: 2x
                                //          10: 3x
                                //          11: 4x

#define SC_PLLS_CTRL0    0x303a // Bit[7]: PLLS bypass
#define SC_PLLS_CTRL1    0x303b // Bit[4:0]: PLLS multiplier
#define SC_PLLS_CTRL2    0x303c // Bit[6:4]: PLLS charge pump control
                                // Bit[3:0]: PLLS system divider
#define SC_PLLS_CTRL3    0x303d // Bit[5:4]: PLLS pre-divider
                                //          00: 1
                                //          01: 1.5
                                //          10: 2
                                //          11: 3
                                // Bit[2]: PLLS root-divider - 1
                                // Bit[1:0]: PLLS seld5
                                //          00: 1
                                //          01: 1
                                //          10: 2
                                //          11: 2.5

/* AEC/AGC control functions */
#define AEC_PK_MANUAL   0x3503  // AEC Manual Mode Control
                                // Bit[7:6]: Reserved
                                // Bit[5]: Gain delay option
                                //         Valid when 0x3503[4]=1’b0
                                //         0: Delay one frame latch
                                //         1: One frame latch
                                // Bit[4:2]: Reserved
                                // Bit[1]: AGC manual
                                //         0: Auto enable
                                //         1: Manual enable
                                // Bit[0]: AEC manual
                                //         0: Auto enable
                                //         1: Manual enable

//gain = {0x350A[1:0], 0x350B[7:0]} / 16

//new


#define X_ADDR_ST_H     0x3800 //Bit[3:0]: X address start[11:8]
#define X_ADDR_ST_L     0x3801 //Bit[7:0]: X address start[7:0]
#define Y_ADDR_ST_H     0x3802 //Bit[2:0]: Y address start[10:8]
#define Y_ADDR_ST_L     0x3803 //Bit[7:0]: Y address start[7:0]
#define X_ADDR_END_H    0x3804 //Bit[3:0]: X address end[11:8]
#define X_ADDR_END_L    0x3805 //Bit[7:0]:
#define Y_ADDR_END_H    0x3806 //Bit[2:0]: Y address end[10:8]
#define Y_ADDR_END_L    0x3807 //Bit[7:0]:
// Size after scaling
#define X_OUTPUT_SIZE_H 0x3808 //Bit[3:0]: DVP output horizontal width[11:8]
#define X_OUTPUT_SIZE_L 0x3809 //Bit[7:0]:
#define Y_OUTPUT_SIZE_H 0x380a //Bit[2:0]: DVP output vertical height[10:8]
#define Y_OUTPUT_SIZE_L 0x380b //Bit[7:0]:
#define X_TOTAL_SIZE_H  0x380c //Bit[3:0]: Total horizontal size[11:8]
#define X_TOTAL_SIZE_L  0x380d //Bit[7:0]:
#define Y_TOTAL_SIZE_H  0x380e //Bit[7:0]: Total vertical size[15:8]
#define Y_TOTAL_SIZE_L  0x380f //Bit[7:0]:
#define X_OFFSET_H      0x3810 //Bit[3:0]: ISP horizontal offset[11:8]
#define X_OFFSET_L      0x3811 //Bit[7:0]:
#define Y_OFFSET_H      0x3812 //Bit[2:0]: ISP vertical offset[10:8]
#define Y_OFFSET_L      0x3813 //Bit[7:0]:
#define X_INCREMENT     0x3814 //Bit[7:4]: Horizontal odd subsample increment
                               //Bit[3:0]: Horizontal even subsample increment
#define Y_INCREMENT     0x3815 //Bit[7:4]: Vertical odd subsample increment
                               //Bit[3:0]: Vertical even subsample increment
// Size before scaling
//#define X_INPUT_SIZE    (X_ADDR_END - X_ADDR_ST + 1 - (2 * X_OFFSET))
//#define Y_INPUT_SIZE    (Y_ADDR_END - Y_ADDR_ST + 1 - (2 * Y_OFFSET))

/* mirror and flip registers */
#define TIMING_TC_REG20 0x3820  // Timing Control Register
                                // Bit[2:1]: Vertical flip enable
                                //         00: Normal
                                //         11: Vertical flip
                                // Bit[0]: Vertical binning enable
#define TIMING_TC_REG21 0x3821  // Timing Control Register
                                // Bit[5]: Compression Enable
                                // Bit[2:1]: Horizontal mirror enable
                                //         00: Normal
                                //         11: Horizontal mirror
                                // Bit[0]: Horizontal binning enable

#define PCLK_RATIO       0x3824 // Bit[4:0]: PCLK ratio manual

/* frame control registers */
#define FRAME_CTRL01    0x4201  // Control Passed Frame Number When both ON and OFF number set to 0x00,frame control is in bypass mode
                                // Bit[7:4]: Not used
                                // Bit[3:0]: Frame ON number
#define FRAME_CTRL02    0x4202  // Control Masked Frame Number When both ON and OFF number set to 0x00,frame control is in bypass mode
                                // Bit[7:4]: Not used
                                // BIT[3:0]: Frame OFF number

/* format control registers */
#define FORMAT_CTRL00   0x4300

#define CLOCK_POL_CONTROL 0x4740// Bit[5]: PCLK polarity 0: active low
                                //          1: active high
                                // Bit[3]: Gate PCLK under VSYNC
                                // Bit[2]: Gate PCLK under HREF
                                // Bit[1]: HREF polarity
                                //          0: active low
                                //          1: active high
                                // Bit[0] VSYNC polarity
                                //          0: active low
                                //          1: active high

#define ISP_CONTROL_01   0x5001 // Bit[5]: Scale enable
                                //          0: Disable
                                //          1: Enable

/* output format control registers */
#define FORMAT_CTRL     0x501F // Format select
                                // Bit[2:0]:
                                //  000: YUV422
                                //  001: RGB
                                //  010: Dither
                                //  011: RAW after DPC
                                //  101: RAW after CIP

/* ISP top control registers */
#define PRE_ISP_TEST_SETTING_1  0x503D  // Bit[7]: Test enable
                                        //         0: Test disable
                                        //         1: Color bar enable
                                        // Bit[6]: Rolling
                                        // Bit[5]: Transparent
                                        // Bit[4]: Square black and white
                                        // Bit[3:2]: Color bar style
                                        //         00: Standard 8 color bar
                                        //         01: Gradual change at vertical mode 1
                                        //         10: Gradual change at horizontal
                                        //         11: Gradual change at vertical mode 2
                                        // Bit[1:0]: Test select
                                        //         00: Color bar
                                        //         01: Random data
                                        //         10: Square data
                                        //         11: Black image

//exposure = {0x3500[3:0], 0x3501[7:0], 0x3502[7:0]} / 16 × tROW

#define SCALE_CTRL_1     0x5601 // Bit[6:4]: HDIV RW
                                //          DCW scale times
                                //          000: DCW 1 time
                                //          001: DCW 2 times
                                //          010: DCW 4 times
                                //          100: DCW 8 times
                                //          101: DCW 16 times
                                //          Others: DCW 16 times
                                // Bit[2:0]: VDIV RW
                                //          DCW scale times
                                //          000: DCW 1 time
                                //          001: DCW 2 times
                                //          010: DCW 4 times
                                //          100: DCW 8 times
                                //          101: DCW 16 times
                                //          Others: DCW 16 times

#define SCALE_CTRL_2     0x5602 // X_SCALE High Bits
#define SCALE_CTRL_3     0x5603 // X_SCALE Low Bits
#define SCALE_CTRL_4     0x5604 // Y_SCALE High Bits
#define SCALE_CTRL_5     0x5605 // Y_SCALE Low Bits
#define SCALE_CTRL_6     0x5606 // Bit[3:0]: V Offset

#define VFIFO_CTRL0C     0x460C // Bit[1]: PCLK manual enable
                                //          0: Auto
                                //          1: Manual by PCLK_RATIO

#define VFIFO_X_SIZE_H   0x4602
#define VFIFO_X_SIZE_L   0x4603
#define VFIFO_Y_SIZE_H   0x4604
#define VFIFO_Y_SIZE_L   0x4605

#define COMPRESSION_CTRL00 0x4400 //
#define COMPRESSION_CTRL01 0x4401 //
#define COMPRESSION_CTRL02 0x4402 //
#define COMPRESSION_CTRL03 0x4403 //
#define COMPRESSION_CTRL04 0x4404 //
#define COMPRESSION_CTRL05 0x4405 //
#define COMPRESSION_CTRL06 0x4406 //
#define COMPRESSION_CTRL07 0x4407 // Bit[5:0]: QS
#define COMPRESSION_ISI_CTRL 0x4408 //
#define COMPRESSION_CTRL09 0x4409 //
#define COMPRESSION_CTRL0a 0x440a //
#define COMPRESSION_CTRL0b 0x440b //
#define COMPRESSION_CTRL0c 0x440c //
#define COMPRESSION_CTRL0d 0x440d //
#define COMPRESSION_CTRL0E 0x440e //

#define JPG_MODE_SELECT	0x4713

/**
 * @brief register value
 */
#define TEST_COLOR_BAR  0xC0    /* Enable Color Bar roling Test */

#define AEC_PK_MANUAL_AGC_MANUALEN  0x02    /* Enable AGC Manual enable */
#define AEC_PK_MANUAL_AEC_MANUALEN  0x01    /* Enable AEC Manual enable */

#define TIMING_TC_REG20_VFLIP   0x06 /* Vertical flip enable */
#define TIMING_TC_REG21_HMIRROR 0x06 /* Horizontal mirror enable */

#define OV5640_SYSREM_RESET00                      0x3000U
#define OV5640_SYSREM_RESET01                      0x3001U
#define OV5640_SYSREM_RESET02                      0x3002U
#define OV5640_SYSREM_RESET03                      0x3003U
#define OV5640_CLOCK_ENABLE00                      0x3004U
#define OV5640_CLOCK_ENABLE01                      0x3005U
#define OV5640_CLOCK_ENABLE02                      0x3006U
#define OV5640_CLOCK_ENABLE03                      0x3007U
#define OV5640_SYSTEM_CTROL0                       0x3008U
#define OV5640_CHIP_ID_HIGH_BYTE                   0x300AU
#define OV5640_CHIP_ID_LOW_BYTE                    0x300BU
#define OV5640_MIPI_CONTROL00                      0x300EU
#define OV5640_PAD_OUTPUT_ENABLE00                 0x3016U
#define OV5640_PAD_OUTPUT_ENABLE01                 0x3017U
#define OV5640_PAD_OUTPUT_ENABLE02                 0x3018U
#define OV5640_PAD_OUTPUT_VALUE00                  0x3019U
#define OV5640_PAD_OUTPUT_VALUE01                  0x301AU
#define OV5640_PAD_OUTPUT_VALUE02                  0x301BU
#define OV5640_PAD_SELECT00                        0x301CU
#define OV5640_PAD_SELECT01                        0x301DU
#define OV5640_PAD_SELECT02                        0x301EU
#define OV5640_CHIP_REVISION                       0x302AU
#define OV5640_PAD_CONTROL00                       0x301CU
#define OV5640_SC_PWC                              0x3031U
#define OV5640_SC_PLL_CONTRL0                      0x3034U
#define OV5640_SC_PLL_CONTRL1                      0x3035U
#define OV5640_SC_PLL_CONTRL2                      0x3036U
#define OV5640_SC_PLL_CONTRL3                      0x3037U
#define OV5640_SC_PLL_CONTRL4                      0x3038U
#define OV5640_SC_PLL_CONTRL5                      0x3039U
#define OV5640_SC_PLLS_CTRL0                       0x303AU
#define OV5640_SC_PLLS_CTRL1                       0x303BU
#define OV5640_SC_PLLS_CTRL2                       0x303CU
#define OV5640_SC_PLLS_CTRL3                       0x303DU
#define OV5640_IO_PAD_VALUE00                      0x3050U
#define OV5640_IO_PAD_VALUE01                      0x3051U
#define OV5640_IO_PAD_VALUE02                      0x3052U

/* SCCB control [0x3100 ~ 0x3108]                       */
#define OV5640_SCCB_ID                             0x3100U
#define OV5640_SCCB_SYSTEM_CTRL0                   0x3102U
#define OV5640_SCCB_SYSTEM_CTRL1                   0x3103U
#define OV5640_SYSTEM_ROOT_DIVIDER                 0x3108U

/* SRB control [0x3200 ~ 0x3213]                        */
#define OV5640_GROUP_ADDR0                         0x3200U
#define OV5640_GROUP_ADDR1                         0x3201U
#define OV5640_GROUP_ADDR2                         0x3202U
#define OV5640_GROUP_ADDR3                         0x3203U
#define OV5640_SRM_GROUP_ACCESS                    0x3212U
#define OV5640_SRM_GROUP_STATUS                    0x3213U

/* AWB gain control [0x3400 ~ 0x3406]                   */
#define OV5640_AWB_R_GAIN_MSB                      0x3400U
#define OV5640_AWB_R_GAIN_LSB                      0x3401U
#define OV5640_AWB_G_GAIN_MSB                      0x3402U
#define OV5640_AWB_G_GAIN_LSB                      0x3403U
#define OV5640_AWB_B_GAIN_MSB                      0x3404U
#define OV5640_AWB_B_GAIN_LSB                      0x3405U
#define OV5640_AWB_MANUAL_CONTROL                  0x3406U

/* AEC/AGC control [0x3500 ~ 0x350D]                    */
#define OV5640_AEC_PK_EXPOSURE_19_16               0x3500U
#define OV5640_AEC_PK_EXPOSURE_HIGH                0x3501U
#define OV5640_AEC_PK_EXPOSURE_LOW                 0x3502U
#define OV5640_AEC_PK_MANUAL                       0x3503U
#define OV5640_AEC_PK_REAL_GAIN_9_8                0x350AU
#define OV5640_AEC_PK_REAL_GAIN_LOW                0x350BU
#define OV5640_AEC_PK_VTS_HIGH                     0x350CU
#define OV5640_AEC_PK_VTS_LOW                      0x350DU

/* VCM control [0x3600 ~ 0x3606]                        */
#define OV5640_VCM_CONTROL_0                       0x3602U
#define OV5640_VCM_CONTROL_1                       0x3603U
#define OV5640_VCM_CONTROL_2                       0x3604U
#define OV5640_VCM_CONTROL_3                       0x3605U
#define OV5640_VCM_CONTROL_4                       0x3606U

/* timing control [0x3800 ~ 0x3821]                    */
#define OV5640_TIMING_HS_HIGH                      0x3800U
#define OV5640_TIMING_HS_LOW                       0x3801U
#define OV5640_TIMING_VS_HIGH                      0x3802U
#define OV5640_TIMING_VS_LOW                       0x3803U
#define OV5640_TIMING_HW_HIGH                      0x3804U
#define OV5640_TIMING_HW_LOW                       0x3805U
#define OV5640_TIMING_VH_HIGH                      0x3806U
#define OV5640_TIMING_VH_LOW                       0x3807U
#define OV5640_TIMING_DVPHO_HIGH                   0x3808U
#define OV5640_TIMING_DVPHO_LOW                    0x3809U
#define OV5640_TIMING_DVPVO_HIGH                   0x380AU
#define OV5640_TIMING_DVPVO_LOW                    0x380BU
#define OV5640_TIMING_HTS_HIGH                     0x380CU
#define OV5640_TIMING_HTS_LOW                      0x380DU
#define OV5640_TIMING_VTS_HIGH                     0x380EU
#define OV5640_TIMING_VTS_LOW                      0x380FU
#define OV5640_TIMING_HOFFSET_HIGH                 0x3810U
#define OV5640_TIMING_HOFFSET_LOW                  0x3811U
#define OV5640_TIMING_VOFFSET_HIGH                 0x3812U
#define OV5640_TIMING_VOFFSET_LOW                  0x3813U
#define OV5640_TIMING_X_INC                        0x3814U
#define OV5640_TIMING_Y_INC                        0x3815U
#define OV5640_HSYNC_START_HIGH                    0x3816U
#define OV5640_HSYNC_START_LOW                     0x3817U
#define OV5640_HSYNC_WIDTH_HIGH                    0x3818U
#define OV5640_HSYNC_WIDTH_LOW                     0x3819U
#define OV5640_TIMING_TC_REG20                     0x3820U
#define OV5640_TIMING_TC_REG21                     0x3821U

/* AEC/AGC power down domain control [0x3A00 ~ 0x3A25] */
#define OV5640_AEC_CTRL00                          0x3A00U
#define OV5640_AEC_CTRL01                          0x3A01U
#define OV5640_AEC_CTRL02                          0x3A02U
#define OV5640_AEC_CTRL03                          0x3A03U
#define OV5640_AEC_CTRL04                          0x3A04U
#define OV5640_AEC_CTRL05                          0x3A05U
#define OV5640_AEC_CTRL06                          0x3A06U
#define OV5640_AEC_CTRL07                          0x3A07U
#define OV5640_AEC_B50_STEP_HIGH                   0x3A08U
#define OV5640_AEC_B50_STEP_LOW                    0x3A09U
#define OV5640_AEC_B60_STEP_HIGH                   0x3A0AU
#define OV5640_AEC_B60_STEP_LOW                    0x3A0BU
#define OV5640_AEC_AEC_CTRL0C                      0x3A0CU
#define OV5640_AEC_CTRL0D                          0x3A0DU
#define OV5640_AEC_CTRL0E                          0x3A0EU
#define OV5640_AEC_CTRL0F                          0x3A0FU
#define OV5640_AEC_CTRL10                          0x3A10U
#define OV5640_AEC_CTRL11                          0x3A11U
#define OV5640_AEC_CTRL13                          0x3A13U
#define OV5640_AEC_MAX_EXPO_HIGH                   0x3A14U
#define OV5640_AEC_MAX_EXPO_LOW                    0x3A15U
#define OV5640_AEC_CTRL17                          0x3A17U
#define OV5640_AEC_GAIN_CEILING_HIGH               0x3A18U
#define OV5640_AEC_GAIN_CEILING_LOW                0x3A19U
#define OV5640_AEC_DIFF_MIN                        0x3A1AU
#define OV5640_AEC_CTRL1B                          0x3A1BU
#define OV5640_LED_ADD_ROW_HIGH                    0x3A1CU
#define OV5640_LED_ADD_ROW_LOW                     0x3A1DU
#define OV5640_AEC_CTRL1E                          0x3A1EU
#define OV5640_AEC_CTRL1F                          0x3A1FU
#define OV5640_AEC_CTRL20                          0x3A20U
#define OV5640_AEC_CTRL21                          0x3A21U
#define OV5640_AEC_CTRL25                          0x3A25U

/* strobe control [0x3B00 ~ 0x3B0C]                      */
#define OV5640_STROBE_CTRL                         0x3B00U
#define OV5640_FREX_EXPOSURE02                     0x3B01U
#define OV5640_FREX_SHUTTER_DLY01                  0x3B02U
#define OV5640_FREX_SHUTTER_DLY00                  0x3B03U
#define OV5640_FREX_EXPOSURE01                     0x3B04U
#define OV5640_FREX_EXPOSURE00                     0x3B05U
#define OV5640_FREX_CTRL07                         0x3B06U
#define OV5640_FREX_MODE                           0x3B07U
#define OV5640_FREX_RQST                           0x3B08U
#define OV5640_FREX_HREF_DLY                       0x3B09U
#define OV5640_FREX_RST_LENGTH                     0x3B0AU
#define OV5640_STROBE_WIDTH_HIGH                   0x3B0BU
#define OV5640_STROBE_WIDTH_LOW                    0x3B0CU

/* 50/60Hz detector control [0x3C00 ~ 0x3C1E]            */
#define OV5640_5060HZ_CTRL00                       0x3C00U
#define OV5640_5060HZ_CTRL01                       0x3C01U
#define OV5640_5060HZ_CTRL02                       0x3C02U
#define OV5640_5060HZ_CTRL03                       0x3C03U
#define OV5640_5060HZ_CTRL04                       0x3C04U
#define OV5640_5060HZ_CTRL05                       0x3C05U
#define OV5640_LIGHTMETER1_TH_HIGH                 0x3C06U
#define OV5640_LIGHTMETER1_TH_LOW                  0x3C07U
#define OV5640_LIGHTMETER2_TH_HIGH                 0x3C08U
#define OV5640_LIGHTMETER2_TH_LOW                  0x3C09U
#define OV5640_SAMPLE_NUMBER_HIGH                  0x3C0AU
#define OV5640_SAMPLE_NUMBER_LOW                   0x3C0BU
#define OV5640_SIGMA_DELTA_CTRL0C                  0x3C0CU
#define OV5640_SUM50_BYTE4                         0x3C0DU
#define OV5640_SUM50_BYTE3                         0x3C0EU
#define OV5640_SUM50_BYTE2                         0x3C0FU
#define OV5640_SUM50_BYTE1                         0x3C10U
#define OV5640_SUM60_BYTE4                         0x3C11U
#define OV5640_SUM60_BYTE3                         0x3C12U
#define OV5640_SUM60_BYTE2                         0x3C13U
#define OV5640_SUM60_BYTE1                         0x3C14U
#define OV5640_SUM5060_HIGH                        0x3C15U
#define OV5640_SUM5060_LOW                         0x3C16U
#define OV5640_BLOCK_CNTR_HIGH                     0x3C17U
#define OV5640_BLOCK_CNTR_LOW                      0x3C18U
#define OV5640_B6_HIGH                             0x3C19U
#define OV5640_B6_LOW                              0x3C1AU
#define OV5640_LIGHTMETER_OUTPUT_BYTE3             0x3C1BU
#define OV5640_LIGHTMETER_OUTPUT_BYTE2             0x3C1CU
#define OV5640_LIGHTMETER_OUTPUT_BYTE1             0x3C1DU
#define OV5640_SUM_THRESHOLD                       0x3C1EU

/* OTP control [0x3D00 ~ 0x3D21]                         */
/* MC control [0x3F00 ~ 0x3F0D]                          */
/* BLC control [0x4000 ~ 0x4033]                         */
#define OV5640_BLC_CTRL00                          0x4000U
#define OV5640_BLC_CTRL01                          0x4001U
#define OV5640_BLC_CTRL02                          0x4002U
#define OV5640_BLC_CTRL03                          0x4003U
#define OV5640_BLC_CTRL04                          0x4004U
#define OV5640_BLC_CTRL05                          0x4005U

/* frame control [0x4201 ~ 0x4202]                       */
#define OV5640_FRAME_CTRL01                        0x4201U
#define OV5640_FRAME_CTRL02                        0x4202U

/* format control [0x4300 ~ 0x430D]                      */
#define OV5640_FORMAT_CTRL00                       0x4300U
#define OV5640_FORMAT_CTRL01                       0x4301U
#define OV5640_YMAX_VAL_HIGH                       0x4302U
#define OV5640_YMAX_VAL_LOW                        0x4303U
#define OV5640_YMIN_VAL_HIGH                       0x4304U
#define OV5640_YMIN_VAL_LOW                        0x4305U
#define OV5640_UMAX_VAL_HIGH                       0x4306U
#define OV5640_UMAX_VAL_LOW                        0x4307U
#define OV5640_UMIN_VAL_HIGH                       0x4308U
#define OV5640_UMIN_VAL_LOW                        0x4309U
#define OV5640_VMAX_VAL_HIGH                       0x430AU
#define OV5640_VMAX_VAL_LOW                        0x430BU
#define OV5640_VMIN_VAL_HIGH                       0x430CU
#define OV5640_VMIN_VAL_LOW                        0x430DU

/* JPEG control [0x4400 ~ 0x4431]                        */
#define OV5640_JPEG_CTRL00                         0x4400U
#define OV5640_JPEG_CTRL01                         0x4401U
#define OV5640_JPEG_CTRL02                         0x4402U
#define OV5640_JPEG_CTRL03                         0x4403U
#define OV5640_JPEG_CTRL04                         0x4404U
#define OV5640_JPEG_CTRL05                         0x4405U
#define OV5640_JPEG_CTRL06                         0x4406U
#define OV5640_JPEG_CTRL07                         0x4407U
#define OV5640_JPEG_ISI_CTRL1                      0x4408U
#define OV5640_JPEG_CTRL09                         0x4409U
#define OV5640_JPEG_CTRL0A                         0x440AU
#define OV5640_JPEG_CTRL0B                         0x440BU
#define OV5640_JPEG_CTRL0C                         0x440CU
#define OV5640_JPEG_QT_DATA                        0x4410U
#define OV5640_JPEG_QT_ADDR                        0x4411U
#define OV5640_JPEG_ISI_DATA                       0x4412U
#define OV5640_JPEG_ISI_CTRL2                      0x4413U
#define OV5640_JPEG_LENGTH_BYTE3                   0x4414U
#define OV5640_JPEG_LENGTH_BYTE2                   0x4415U
#define OV5640_JPEG_LENGTH_BYTE1                   0x4416U
#define OV5640_JFIFO_OVERFLOW                      0x4417U

/* VFIFO control [0x4600 ~ 0x460D]                       */
#define OV5640_VFIFO_CTRL00                        0x4600U
#define OV5640_VFIFO_HSIZE_HIGH                    0x4602U
#define OV5640_VFIFO_HSIZE_LOW                     0x4603U
#define OV5640_VFIFO_VSIZE_HIGH                    0x4604U
#define OV5640_VFIFO_VSIZE_LOW                     0x4605U
#define OV5640_VFIFO_CTRL0C                        0x460CU
#define OV5640_VFIFO_CTRL0D                        0x460DU

/* DVP control [0x4709 ~ 0x4745]                         */
#define OV5640_DVP_VSYNC_WIDTH0                    0x4709U
#define OV5640_DVP_VSYNC_WIDTH1                    0x470AU
#define OV5640_DVP_VSYNC_WIDTH2                    0x470BU
#define OV5640_PAD_LEFT_CTRL                       0x4711U
#define OV5640_PAD_RIGHT_CTRL                      0x4712U
#define OV5640_JPG_MODE_SELECT                     0x4713U
#define OV5640_656_DUMMY_LINE                      0x4715U
#define OV5640_CCIR656_CTRL                        0x4719U
#define OV5640_HSYNC_CTRL00                        0x471BU
#define OV5640_DVP_VSYN_CTRL                       0x471DU
#define OV5640_DVP_HREF_CTRL                       0x471FU
#define OV5640_VSTART_OFFSET                       0x4721U
#define OV5640_VEND_OFFSET                         0x4722U
#define OV5640_DVP_CTRL23                          0x4723U
#define OV5640_CCIR656_CTRL00                      0x4730U
#define OV5640_CCIR656_CTRL01                      0x4731U
#define OV5640_CCIR656_FS                          0x4732U
#define OV5640_CCIR656_FE                          0x4733U
#define OV5640_CCIR656_LS                          0x4734U
#define OV5640_CCIR656_LE                          0x4735U
#define OV5640_CCIR656_CTRL06                      0x4736U
#define OV5640_CCIR656_CTRL07                      0x4737U
#define OV5640_CCIR656_CTRL08                      0x4738U
#define OV5640_POLARITY_CTRL                       0x4740U
#define OV5640_TEST_PATTERN                        0x4741U
#define OV5640_DATA_ORDER                          0x4745U

/* MIPI control [0x4800 ~ 0x4837]                        */
#define OV5640_MIPI_CTRL00                         0x4800U
#define OV5640_MIPI_CTRL01                         0x4801U
#define OV5640_MIPI_CTRL05                         0x4805U
#define OV5640_MIPI_DATA_ORDER                     0x480AU
#define OV5640_MIN_HS_ZERO_HIGH                    0x4818U
#define OV5640_MIN_HS_ZERO_LOW                     0x4819U
#define OV5640_MIN_MIPI_HS_TRAIL_HIGH              0x481AU
#define OV5640_MIN_MIPI_HS_TRAIL_LOW               0x481BU
#define OV5640_MIN_MIPI_CLK_ZERO_HIGH              0x481CU
#define OV5640_MIN_MIPI_CLK_ZERO_LOW               0x481DU
#define OV5640_MIN_MIPI_CLK_PREPARE_HIGH           0x481EU
#define OV5640_MIN_MIPI_CLK_PREPARE_LOW            0x481FU
#define OV5640_MIN_CLK_POST_HIGH                   0x4820U
#define OV5640_MIN_CLK_POST_LOW                    0x4821U
#define OV5640_MIN_CLK_TRAIL_HIGH                  0x4822U
#define OV5640_MIN_CLK_TRAIL_LOW                   0x4823U
#define OV5640_MIN_LPX_PCLK_HIGH                   0x4824U
#define OV5640_MIN_LPX_PCLK_LOW                    0x4825U
#define OV5640_MIN_HS_PREPARE_HIGH                 0x4826U
#define OV5640_MIN_HS_PREPARE_LOW                  0x4827U
#define OV5640_MIN_HS_EXIT_HIGH                    0x4828U
#define OV5640_MIN_HS_EXIT_LOW                     0x4829U
#define OV5640_MIN_HS_ZERO_UI                      0x482AU
#define OV5640_MIN_HS_TRAIL_UI                     0x482BU
#define OV5640_MIN_CLK_ZERO_UI                     0x482CU
#define OV5640_MIN_CLK_PREPARE_UI                  0x482DU
#define OV5640_MIN_CLK_POST_UI                     0x482EU
#define OV5640_MIN_CLK_TRAIL_UI                    0x482FU
#define OV5640_MIN_LPX_PCLK_UI                     0x4830U
#define OV5640_MIN_HS_PREPARE_UI                   0x4831U
#define OV5640_MIN_HS_EXIT_UI                      0x4832U
#define OV5640_PCLK_PERIOD                         0x4837U

/* ISP frame control [0x4901 ~ 0x4902]                   */
#define OV5640_ISP_FRAME_CTRL01                    0x4901U
#define OV5640_ISP_FRAME_CTRL02                    0x4902U

/* ISP top control [0x5000 ~ 0x5063]                     */
#define OV5640_ISP_CONTROL00                       0x5000U
#define OV5640_ISP_CONTROL01                       0x5001U
#define OV5640_ISP_CONTROL03                       0x5003U
#define OV5640_ISP_CONTROL05                       0x5005U
#define OV5640_ISP_MISC0                           0x501DU
#define OV5640_ISP_MISC1                           0x501EU
#define OV5640_FORMAT_MUX_CTRL                     0x501FU
#define OV5640_DITHER_CTRL0                        0x5020U
#define OV5640_DRAW_WINDOW_CTRL00                  0x5027U
#define OV5640_DRAW_WINDOW_LEFT_CTRL_HIGH          0x5028U
#define OV5640_DRAW_WINDOW_LEFT_CTRL_LOW           0x5029U
#define OV5640_DRAW_WINDOW_RIGHT_CTRL_HIGH         0x502AU
#define OV5640_DRAW_WINDOW_RIGHT_CTRL_LOW          0x502BU
#define OV5640_DRAW_WINDOW_TOP_CTRL_HIGH           0x502CU
#define OV5640_DRAW_WINDOW_TOP_CTRL_LOW            0x502DU
#define OV5640_DRAW_WINDOW_BOTTOM_CTRL_HIGH        0x502EU
#define OV5640_DRAW_WINDOW_BOTTOM_CTRL_LOW         0x502FU
#define OV5640_DRAW_WINDOW_HBW_CTRL_HIGH           0x5030U          /* HBW: Horizontal Boundary Width */
#define OV5640_DRAW_WINDOW_HBW_CTRL_LOW            0x5031U
#define OV5640_DRAW_WINDOW_VBW_CTRL_HIGH           0x5032U          /* VBW: Vertical Boundary Width */
#define OV5640_DRAW_WINDOW_VBW_CTRL_LOW            0x5033U
#define OV5640_DRAW_WINDOW_Y_CTRL                  0x5034U
#define OV5640_DRAW_WINDOW_U_CTRL                  0x5035U
#define OV5640_DRAW_WINDOW_V_CTRL                  0x5036U
#define OV5640_PRE_ISP_TEST_SETTING1               0x503DU
#define OV5640_ISP_SENSOR_BIAS_I                   0x5061U
#define OV5640_ISP_SENSOR_GAIN1_I                  0x5062U
#define OV5640_ISP_SENSOR_GAIN2_I                  0x5063U

/* AWB control [0x5180 ~ 0x51D0]                         */
#define OV5640_AWB_CTRL00                          0x5180U
#define OV5640_AWB_CTRL01                          0x5181U
#define OV5640_AWB_CTRL02                          0x5182U
#define OV5640_AWB_CTRL03                          0x5183U
#define OV5640_AWB_CTRL04                          0x5184U
#define OV5640_AWB_CTRL05                          0x5185U
#define OV5640_AWB_CTRL06                          0x5186U     /* Advanced AWB control registers: 0x5186 ~ 0x5190 */
#define OV5640_AWB_CTRL07                          0x5187U
#define OV5640_AWB_CTRL08                          0x5188U
#define OV5640_AWB_CTRL09                          0x5189U
#define OV5640_AWB_CTRL10                          0x518AU
#define OV5640_AWB_CTRL11                          0x518BU
#define OV5640_AWB_CTRL12                          0x518CU
#define OV5640_AWB_CTRL13                          0x518DU
#define OV5640_AWB_CTRL14                          0x518EU
#define OV5640_AWB_CTRL15                          0x518FU
#define OV5640_AWB_CTRL16                          0x5190U
#define OV5640_AWB_CTRL17                          0x5191U
#define OV5640_AWB_CTRL18                          0x5192U
#define OV5640_AWB_CTRL19                          0x5193U
#define OV5640_AWB_CTRL20                          0x5194U
#define OV5640_AWB_CTRL21                          0x5195U
#define OV5640_AWB_CTRL22                          0x5196U
#define OV5640_AWB_CTRL23                          0x5197U
#define OV5640_AWB_CTRL24                          0x5198U
#define OV5640_AWB_CTRL25                          0x5199U
#define OV5640_AWB_CTRL26                          0x519AU
#define OV5640_AWB_CTRL27                          0x519BU
#define OV5640_AWB_CTRL28                          0x519CU
#define OV5640_AWB_CTRL29                          0x519DU
#define OV5640_AWB_CTRL30                          0x519EU
#define OV5640_AWB_CURRENT_R_GAIN_HIGH             0x519FU
#define OV5640_AWB_CURRENT_R_GAIN_LOW              0x51A0U
#define OV5640_AWB_CURRENT_G_GAIN_HIGH             0x51A1U
#define OV5640_AWB_CURRENT_G_GAIN_LOW              0x51A2U
#define OV5640_AWB_CURRENT_B_GAIN_HIGH             0x51A3U
#define OV5640_AWB_CURRENT_B_GAIN_LOW              0x51A4U
#define OV5640_AWB_AVERAGE_R                       0x51A5U
#define OV5640_AWB_AVERAGE_G                       0x51A6U
#define OV5640_AWB_AVERAGE_B                       0x51A7U
#define OV5640_AWB_CTRL74                          0x5180U

/* CIP control [0x5300 ~ 0x530F]                         */
#define OV5640_CIP_SHARPENMT_TH1                   0x5300U
#define OV5640_CIP_SHARPENMT_TH2                   0x5301U
#define OV5640_CIP_SHARPENMT_OFFSET1               0x5302U
#define OV5640_CIP_SHARPENMT_OFFSET2               0x5303U
#define OV5640_CIP_DNS_TH1                         0x5304U
#define OV5640_CIP_DNS_TH2                         0x5305U
#define OV5640_CIP_DNS_OFFSET1                     0x5306U
#define OV5640_CIP_DNS_OFFSET2                     0x5307U
#define OV5640_CIP_CTRL                            0x5308U
#define OV5640_CIP_SHARPENTH_TH1                   0x5309U
#define OV5640_CIP_SHARPENTH_TH2                   0x530AU
#define OV5640_CIP_SHARPENTH_OFFSET1               0x530BU
#define OV5640_CIP_SHARPENTH_OFFSET2               0x530CU
#define OV5640_CIP_EDGE_MT_AUTO                    0x530DU
#define OV5640_CIP_DNS_TH_AUTO                     0x530EU
#define OV5640_CIP_SHARPEN_TH_AUTO                 0x530FU

/* CMX control [0x5380 ~ 0x538B]                         */
#define OV5640_CMX_CTRL                            0x5380U
#define OV5640_CMX1                                0x5381U
#define OV5640_CMX2                                0x5382U
#define OV5640_CMX3                                0x5383U
#define OV5640_CMX4                                0x5384U
#define OV5640_CMX5                                0x5385U
#define OV5640_CMX6                                0x5386U
#define OV5640_CMX7                                0x5387U
#define OV5640_CMX8                                0x5388U
#define OV5640_CMX9                                0x5389U
#define OV5640_CMXSIGN_HIGH                        0x538AU
#define OV5640_CMXSIGN_LOW                         0x538BU

/* gamma control [0x5480 ~ 0x5490]                       */
#define OV5640_GAMMA_CTRL00                        0x5480U
#define OV5640_GAMMA_YST00                         0x5481U
#define OV5640_GAMMA_YST01                         0x5482U
#define OV5640_GAMMA_YST02                         0x5483U
#define OV5640_GAMMA_YST03                         0x5484U
#define OV5640_GAMMA_YST04                         0x5485U
#define OV5640_GAMMA_YST05                         0x5486U
#define OV5640_GAMMA_YST06                         0x5487U
#define OV5640_GAMMA_YST07                         0x5488U
#define OV5640_GAMMA_YST08                         0x5489U
#define OV5640_GAMMA_YST09                         0x548AU
#define OV5640_GAMMA_YST0A                         0x548BU
#define OV5640_GAMMA_YST0B                         0x548CU
#define OV5640_GAMMA_YST0C                         0x548DU
#define OV5640_GAMMA_YST0D                         0x548EU
#define OV5640_GAMMA_YST0E                         0x548FU
#define OV5640_GAMMA_YST0F                         0x5490U

/* SDE control [0x5580 ~ 0x558C]                         */
#define OV5640_SDE_CTRL0                           0x5580U
#define OV5640_SDE_CTRL1                           0x5581U
#define OV5640_SDE_CTRL2                           0x5582U
#define OV5640_SDE_CTRL3                           0x5583U
#define OV5640_SDE_CTRL4                           0x5584U
#define OV5640_SDE_CTRL5                           0x5585U
#define OV5640_SDE_CTRL6                           0x5586U
#define OV5640_SDE_CTRL7                           0x5587U
#define OV5640_SDE_CTRL8                           0x5588U
#define OV5640_SDE_CTRL9                           0x5589U
#define OV5640_SDE_CTRL10                          0x558AU
#define OV5640_SDE_CTRL11                          0x558BU
#define OV5640_SDE_CTRL12                          0x558CU

/* scale control [0x5600 ~ 0x5606]                       */
#define OV5640_SCALE_CTRL0                         0x5600U
#define OV5640_SCALE_CTRL1                         0x5601U
#define OV5640_SCALE_CTRL2                         0x5602U
#define OV5640_SCALE_CTRL3                         0x5603U
#define OV5640_SCALE_CTRL4                         0x5604U
#define OV5640_SCALE_CTRL5                         0x5605U
#define OV5640_SCALE_CTRL6                         0x5606U


/* AVG control [0x5680 ~ 0x56A2]                         */
#define OV5640_X_START_HIGH                        0x5680U
#define OV5640_X_START_LOW                         0x5681U
#define OV5640_Y_START_HIGH                        0x5682U
#define OV5640_Y_START_LOW                         0x5683U
#define OV5640_X_WINDOW_HIGH                       0x5684U
#define OV5640_X_WINDOW_LOW                        0x5685U
#define OV5640_Y_WINDOW_HIGH                       0x5686U
#define OV5640_Y_WINDOW_LOW                        0x5687U
#define OV5640_WEIGHT00                            0x5688U
#define OV5640_WEIGHT01                            0x5689U
#define OV5640_WEIGHT02                            0x568AU
#define OV5640_WEIGHT03                            0x568BU
#define OV5640_WEIGHT04                            0x568CU
#define OV5640_WEIGHT05                            0x568DU
#define OV5640_WEIGHT06                            0x568EU
#define OV5640_WEIGHT07                            0x568FU
#define OV5640_AVG_CTRL10                          0x5690U
#define OV5640_AVG_WIN_00                          0x5691U
#define OV5640_AVG_WIN_01                          0x5692U
#define OV5640_AVG_WIN_02                          0x5693U
#define OV5640_AVG_WIN_03                          0x5694U
#define OV5640_AVG_WIN_10                          0x5695U
#define OV5640_AVG_WIN_11                          0x5696U
#define OV5640_AVG_WIN_12                          0x5697U
#define OV5640_AVG_WIN_13                          0x5698U
#define OV5640_AVG_WIN_20                          0x5699U
#define OV5640_AVG_WIN_21                          0x569AU
#define OV5640_AVG_WIN_22                          0x569BU
#define OV5640_AVG_WIN_23                          0x569CU
#define OV5640_AVG_WIN_30                          0x569DU
#define OV5640_AVG_WIN_31                          0x569EU
#define OV5640_AVG_WIN_32                          0x569FU
#define OV5640_AVG_WIN_33                          0x56A0U
#define OV5640_AVG_READOUT                         0x56A1U
#define OV5640_AVG_WEIGHT_SUM                      0x56A2U

/* LENC control [0x5800 ~ 0x5849]                        */
#define OV5640_GMTRX00                             0x5800U
#define OV5640_GMTRX01                             0x5801U
#define OV5640_GMTRX02                             0x5802U
#define OV5640_GMTRX03                             0x5803U
#define OV5640_GMTRX04                             0x5804U
#define OV5640_GMTRX05                             0x5805U
#define OV5640_GMTRX10                             0x5806U
#define OV5640_GMTRX11                             0x5807U
#define OV5640_GMTRX12                             0x5808U
#define OV5640_GMTRX13                             0x5809U
#define OV5640_GMTRX14                             0x580AU
#define OV5640_GMTRX15                             0x580BU
#define OV5640_GMTRX20                             0x580CU
#define OV5640_GMTRX21                             0x580DU
#define OV5640_GMTRX22                             0x580EU
#define OV5640_GMTRX23                             0x580FU
#define OV5640_GMTRX24                             0x5810U
#define OV5640_GMTRX25                             0x5811U
#define OV5640_GMTRX30                             0x5812U
#define OV5640_GMTRX31                             0x5813U
#define OV5640_GMTRX32                             0x5814U
#define OV5640_GMTRX33                             0x5815U
#define OV5640_GMTRX34                             0x5816U
#define OV5640_GMTRX35                             0x5817U
#define OV5640_GMTRX40                             0x5818U
#define OV5640_GMTRX41                             0x5819U
#define OV5640_GMTRX42                             0x581AU
#define OV5640_GMTRX43                             0x581BU
#define OV5640_GMTRX44                             0x581CU
#define OV5640_GMTRX45                             0x581DU
#define OV5640_GMTRX50                             0x581EU
#define OV5640_GMTRX51                             0x581FU
#define OV5640_GMTRX52                             0x5820U
#define OV5640_GMTRX53                             0x5821U
#define OV5640_GMTRX54                             0x5822U
#define OV5640_GMTRX55                             0x5823U
#define OV5640_BRMATRX00                           0x5824U
#define OV5640_BRMATRX01                           0x5825U
#define OV5640_BRMATRX02                           0x5826U
#define OV5640_BRMATRX03                           0x5827U
#define OV5640_BRMATRX04                           0x5828U
#define OV5640_BRMATRX05                           0x5829U
#define OV5640_BRMATRX06                           0x582AU
#define OV5640_BRMATRX07                           0x582BU
#define OV5640_BRMATRX08                           0x582CU
#define OV5640_BRMATRX09                           0x582DU
#define OV5640_BRMATRX20                           0x582EU
#define OV5640_BRMATRX21                           0x582FU
#define OV5640_BRMATRX22                           0x5830U
#define OV5640_BRMATRX23                           0x5831U
#define OV5640_BRMATRX24                           0x5832U
#define OV5640_BRMATRX30                           0x5833U
#define OV5640_BRMATRX31                           0x5834U
#define OV5640_BRMATRX32                           0x5835U
#define OV5640_BRMATRX33                           0x5836U
#define OV5640_BRMATRX34                           0x5837U
#define OV5640_BRMATRX40                           0x5838U
#define OV5640_BRMATRX41                           0x5839U
#define OV5640_BRMATRX42                           0x583AU
#define OV5640_BRMATRX43                           0x583BU
#define OV5640_BRMATRX44                           0x583CU
#define OV5640_LENC_BR_OFFSET                      0x583DU
#define OV5640_MAX_GAIN                            0x583EU
#define OV5640_MIN_GAIN                            0x583FU
#define OV5640_MIN_Q                               0x5840U
#define OV5640_LENC_CTRL59                         0x5841U
#define OV5640_BR_HSCALE_HIGH                      0x5842U
#define OV5640_BR_HSCALE_LOW                       0x5843U
#define OV5640_BR_VSCALE_HIGH                      0x5844U
#define OV5640_BR_VSCALE_LOW                       0x5845U
#define OV5640_G_HSCALE_HIGH                       0x5846U
#define OV5640_G_HSCALE_LOW                        0x5847U
#define OV5640_G_VSCALE_HIGH                       0x5848U
#define OV5640_G_VSCALE_LOW                        0x5849U

/* AFC control [0x6000 ~ 0x603F]                         */
#define OV5640_AFC_CTRL00                          0x6000U
#define OV5640_AFC_CTRL01                          0x6001U
#define OV5640_AFC_CTRL02                          0x6002U
#define OV5640_AFC_CTRL03                          0x6003U
#define OV5640_AFC_CTRL04                          0x6004U
#define OV5640_AFC_CTRL05                          0x6005U
#define OV5640_AFC_CTRL06                          0x6006U
#define OV5640_AFC_CTRL07                          0x6007U
#define OV5640_AFC_CTRL08                          0x6008U
#define OV5640_AFC_CTRL09                          0x6009U
#define OV5640_AFC_CTRL10                          0x600AU
#define OV5640_AFC_CTRL11                          0x600BU
#define OV5640_AFC_CTRL12                          0x600CU
#define OV5640_AFC_CTRL13                          0x600DU
#define OV5640_AFC_CTRL14                          0x600EU
#define OV5640_AFC_CTRL15                          0x600FU
#define OV5640_AFC_CTRL16                          0x6010U
#define OV5640_AFC_CTRL17                          0x6011U
#define OV5640_AFC_CTRL18                          0x6012U
#define OV5640_AFC_CTRL19                          0x6013U
#define OV5640_AFC_CTRL20                          0x6014U
#define OV5640_AFC_CTRL21                          0x6015U
#define OV5640_AFC_CTRL22                          0x6016U
#define OV5640_AFC_CTRL23                          0x6017U
#define OV5640_AFC_CTRL24                          0x6018U
#define OV5640_AFC_CTRL25                          0x6019U
#define OV5640_AFC_CTRL26                          0x601AU
#define OV5640_AFC_CTRL27                          0x601BU
#define OV5640_AFC_CTRL28                          0x601CU
#define OV5640_AFC_CTRL29                          0x601DU
#define OV5640_AFC_CTRL30                          0x601EU
#define OV5640_AFC_CTRL31                          0x601FU
#define OV5640_AFC_CTRL32                          0x6020U
#define OV5640_AFC_CTRL33                          0x6021U
#define OV5640_AFC_CTRL34                          0x6022U
#define OV5640_AFC_CTRL35                          0x6023U
#define OV5640_AFC_CTRL36                          0x6024U
#define OV5640_AFC_CTRL37                          0x6025U
#define OV5640_AFC_CTRL38                          0x6026U
#define OV5640_AFC_CTRL39                          0x6027U
#define OV5640_AFC_CTRL40                          0x6028U
#define OV5640_AFC_CTRL41                          0x6029U
#define OV5640_AFC_CTRL42                          0x602AU
#define OV5640_AFC_CTRL43                          0x602BU
#define OV5640_AFC_CTRL44                          0x602CU
#define OV5640_AFC_CTRL45                          0x602DU
#define OV5640_AFC_CTRL46                          0x602EU
#define OV5640_AFC_CTRL47                          0x602FU
#define OV5640_AFC_CTRL48                          0x6030U
#define OV5640_AFC_CTRL49                          0x6031U
#define OV5640_AFC_CTRL50                          0x6032U
#define OV5640_AFC_CTRL51                          0x6033U
#define OV5640_AFC_CTRL52                          0x6034U
#define OV5640_AFC_CTRL53                          0x6035U
#define OV5640_AFC_CTRL54                          0x6036U
#define OV5640_AFC_CTRL55                          0x6037U
#define OV5640_AFC_CTRL56                          0x6038U
#define OV5640_AFC_CTRL57                          0x6039U
#define OV5640_AFC_CTRL58                          0x603AU
#define OV5640_AFC_CTRL59                          0x603BU
#define OV5640_AFC_CTRL60                          0x603CU
#define OV5640_AFC_READ58                          0x603DU
#define OV5640_AFC_READ59                          0x603EU
#define OV5640_AFC_READ60                          0x603FU

/**
  * @}
  */


#endif // __OV3660_REG_REGS_H__


//#endif /* INC_OV5640_REGISTERS_H_ */
