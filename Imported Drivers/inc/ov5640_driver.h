/**
  ******************************************************************************
  * @file    ov5640.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the ov5640.c
  *          driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OV5640_H
#define __OV5640_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "camera_I2C.h"
#include "stdio.h"
//#include "./camera_I2C.h"
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ov5640
  * @{
  */

/** @defgroup OV5640_Exported_Types
  * @{
  */
     
/**
  * @}
  */ 

/** @defgroup OV5640_Exported_Constants
  * @{
  */
/** 
  * @brief  OV5640 ID  
  */  
#define OV5640_ID  0x5640

#define XSIZE 1024
#define YSIZE 600

#define   QQVGA_160_120    0
#define   QCIF_176_144     1
#define   QVGA_320_240     2
#define   WQVGA_400_240    3
#define   CIF_352_288      4
#define   VGA_640_480      5
#define   SVGA_800_600     6
/** 
  * @brief  OV5640 Registers  
  */


/** 
 * @brief  OV5640 Features Parameters  
 */
 /* IMAGE TYPE SELECT */
 
/* Brightness */ 
#define OV5640_BRIGHTNESS_LEVEL4P       0x00   /* Brightness level +4         */   
#define OV5640_BRIGHTNESS_LEVEL3P       0x01   /* Brightness level +3         */
#define OV5640_BRIGHTNESS_LEVEL2P       0x02   /* Brightness level +2         */   
#define OV5640_BRIGHTNESS_LEVEL1P       0x04   /* Brightness level +1         */
#define OV5640_BRIGHTNESS_LEVEL0        0x08   /* Brightness level 0          */
#define OV5640_BRIGHTNESS_LEVEL1N       0x10   /* Brightness level -1         */
#define OV5640_BRIGHTNESS_LEVEL2N       0x20   /* Brightness level -2         */
#define OV5640_BRIGHTNESS_LEVEL3N       0x40   /* Brightness level -3         */
#define OV5640_BRIGHTNESS_LEVEL4N       0x80   /* Brightness level -4         */

/* Saturation */ 
#define OV5640_SATURATION_LEVEL4P       0x00   /* Saturation level +4         */   
#define OV5640_SATURATION_LEVEL3P       0x01   /* Saturation level +3         */
#define OV5640_SATURATION_LEVEL2P       0x02   /* Saturation level +2         */   
#define OV5640_SATURATION_LEVEL1P       0x04   /* Saturation level +1         */
#define OV5640_SATURATION_LEVEL0        0x08   /* Saturation level 0          */
#define OV5640_SATURATION_LEVEL1N       0x10   /* Saturation level -1         */
#define OV5640_SATURATION_LEVEL2N       0x20   /* Saturation level -2         */
#define OV5640_SATURATION_LEVEL3N       0x40   /* Saturation level -3         */
#define OV5640_SATURATION_LEVEL4N       0x80   /* Saturation level -4         */

/* Contrast */ 
#define OV5640_CONTRAST_LEVEL4P         0x00   /* Contrast level +4           */   
#define OV5640_CONTRAST_LEVEL3P         0x01   /* Contrast level +3           */
#define OV5640_CONTRAST_LEVEL2P         0x02   /* Contrast level +2           */   
#define OV5640_CONTRAST_LEVEL1P         0x04   /* Contrast level +1           */
#define OV5640_CONTRAST_LEVEL0          0x08   /* Contrast level 0            */
#define OV5640_CONTRAST_LEVEL1N         0x10   /* Contrast level -1           */
#define OV5640_CONTRAST_LEVEL2N         0x20   /* Contrast level -2           */
#define OV5640_CONTRAST_LEVEL3N         0x40   /* Contrast level -3           */
#define OV5640_CONTRAST_LEVEL4N         0x80   /* Contrast level -4           */


/* Hue Control */   
#define OV5640_HUE_150P                 0x0001   /* Hue 150+ degree           */ 
#define OV5640_HUE_120P                 0x0002   /* Hue 120+ degree           */   
#define OV5640_HUE_90P                  0x0004   /* Hue 90+ degree            */
#define OV5640_HUE_60P                  0x0008   /* Hue 60+ degree            */   
#define OV5640_HUE_30P                  0x0010   /* Hue 30+ degree            */
#define OV5640_HUE_0                    0x0020   /* Hue 0 degree              */
#define OV5640_HUE_30N                  0x0040   /* Hue 30- degree            */
#define OV5640_HUE_60N                  0x0080   /* Hue 60- degree            */
#define OV5640_HUE_90N                  0x0100   /* Hue 90- degree            */
#define OV5640_HUE_120N                 0x0200   /* Hue 120- degree           */    
#define OV5640_HUE_150N                 0x0400   /* Hue 150- degree           */   
#define OV5640_HUE_180N                 0x0800   /* Hue 180- degree           */

/* Mirror/Flip */
#define OV5640_MIRROR                   0x00   /* Set camera mirror config    */
#define OV5640_FLIP                     0x01   /* Set camera flip config      */
#define OV5640_MIRROR_FLIP              0x02   /* Set camera mirror and flip  */
#define OV5640_MIRROR_FLIP_NORMAL       0x04   /* Set camera normal mode      */
   
/* Zoom */
#define OV5640_ZOOM_x8                  0x00
#define OV5640_ZOOM_x4                  0x11   
#define OV5640_ZOOM_x2                  0x22   
#define OV5640_ZOOM_x1                  0x44   

/* Special Effect */
#define OV5640_COLOR_EFFECT_NONE              0x00 /* No effect               */
#define OV5640_COLOR_EFFECT_BLUE              0x01 /* Blue effect             */
#define OV5640_COLOR_EFFECT_RED               0x02 /* Red effect              */
#define OV5640_COLOR_EFFECT_GREEN             0x04 /* Green effect            */
#define OV5640_COLOR_EFFECT_BW                0x08 /* Black and White effect  */
#define OV5640_COLOR_EFFECT_SEPIA             0x10 /* Sepia effect            */
#define OV5640_COLOR_EFFECT_NEGATIVE          0x20 /* Negative effect         */
#define OV5640_COLOR_EFFECT_BW_NEGATIVE       0x40 /* BW Negative effect      */
#define OV5640_COLOR_EFFECT_OVEREXPOSURE      0x80 /* Over exposure effect    */
#define OV5640_COLOR_EFFECT_SOLARIZE          0x100 /* Solarized effect       */ 
   
/* Light Mode */
#define OV5640_LIGHT_AUTO               0x00   /* Light Mode Auto             */
#define OV5640_LIGHT_SUNNY              0x01   /* Light Mode Sunny            */
#define OV5640_LIGHT_OFFICE             0x02   /* Light Mode Office           */
#define OV5640_LIGHT_HOME               0x04   /* Light Mode Home             */
#define OV5640_LIGHT_CLOUDY             0x08   /* Light Mode Claudy           */

/* Saturation */ 
#define OV5640_SATURATION_0             0x00   /* Color saturation 0          */
#define OV5640_SATURATION_1             0x01   /* Color saturation 1          */
#define OV5640_SATURATION_2             0x02   /* Color saturation 2          */
#define OV5640_SATURATION_3             0x04   /* Color saturation 3          */

/* Exposure */ 
#define OV5640_EXPOSURE_LEVEL_0         0x00   /* Exposure Level 0            */
#define OV5640_EXPOSURE_LEVEL_1         0x01   /* Exposure Level 1            */
#define OV5640_EXPOSURE_LEVEL_2         0x02   /* Exposure Level 2            */
#define OV5640_EXPOSURE_LEVEL_3         0x04   /* Exposure Level 3            */

/**
  * @}
  */
  
/** @defgroup OV5640_Exported_Functions
  * @{
  */ 

#define OV5640_I2C_ADDRESS 0x78

void ov5640_Init(void);
void ov5640_Set_RGB565(void);
void ov5640_Set_JPEG(void);
void ov5640_Init_JPEG(uint16_t x_res, uint16_t y_res);
void ov5640_Init_RGB565(uint16_t x_res, uint16_t y_res);
uint8_t OV5640_Set_Size(uint16_t offx, uint16_t offy, uint16_t width, uint16_t height);

//void OV5640_JPEG_Config(uint16_t quality, uint16_t width, uint16_t height);


void OV5640_Set_NightMode(void);
int32_t OV5640_SetPCLK(uint32_t ClockValue);


void OV5640_Set_FIFO_Width(uint16_t fifo_width);
void OV5640_Set_Comp_Ratio(uint16_t comp_ratio);

void  OV5640_MirrorFlipConfig1(uint8_t Config);
uint16_t ov5640_ReadID();
void     CAMERA_IO_Init(void);
//void     CAMERA_IO_Write_OV5640(uint8_t addr, uint16_t reg, uint16_t value);
//uint16_t CAMERA_IO_Read_OV5640(uint8_t Addr, uint16_t Reg);
void     CAMERA_Delay(uint32_t delay);
void ov5640_Config(uint32_t feature, uint32_t value, uint32_t BR_value);


extern CAMERA_DrvTypeDef   ov5640_drv;
/**
  * @}
  */    
#ifdef __cplusplus
}
#endif

#endif /* __OV5640_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
