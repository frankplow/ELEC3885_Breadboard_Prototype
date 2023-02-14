/*
 * camera.h
 *
 *  Created on: Jan 12, 2023
 *      Author: sol
 */

#ifndef __CAMERA_APPLICATION_H
#define __CAMERA_APPLICATION_H

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
//#include "stm32746g_discovery_sdram.h"
#include "stm32746g_multi_camera_driver.h"
#include "stm32746g_discovery_lcd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define X_RES 480
#define Y_RES 272
#define CAM_FB_SIZE X_RES * Y_RES * 2
#define LCD_FB_SIZE 259200

extern uint8_t frameCounter;
void initialiseCapture(void);
void BSP_CAMERA_LineEventCallback(void);
void BSP_CAMERA_FrameEventCallback(void);
void BSP_CAMERA_VsyncEventCallback(void);
void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst);
void LCD_DMA_Transfer_RGBTOARGB8888(void *pSrc, void *pDst);
void LCD_init(void);
void FPSCalculate(void);

#endif /* INC_CAMERA_H_ */
