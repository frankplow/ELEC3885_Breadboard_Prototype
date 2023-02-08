/*
 * camera.h
 *
 *  Created on: Jan 12, 2023
 *      Author: sol
 */

#ifndef INC_CAMERA_APPLICATION_H_
#define INC_CAMERA_APPLICATION_H_

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_ov5640.h"
#include "stm32746g_discovery_lcd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define CAM_FB_SIZE 259200
uint8_t cam_fb[CAM_FB_SIZE] __attribute__ ((section (".sdram"), aligned (4)));

#define LCD_FB_SIZE CAM_FB_SIZE
char lcd_fb[LCD_FB_SIZE] __attribute__ ((section (".sdram"), aligned (4)));

void initialiseCapture(void);
void BSP_CAMERA_LineEventCallback(void);
void BSP_CAMERA_FrameEventCallback(void);
void BSP_CAMERA_VsyncEventCallback(void);
void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst);
void LCD_DMA_Transfer_RGBTOARGB8888(void *pSrc, void *pDst);
void LCD_init(void);
void FPSCalculate(void);

#endif /* INC_CAMERA_H_ */
