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
#include <stdbool.h>

//#define X_RES 320
//#define Y_RES 240
#define X_RES 320
#define Y_RES 80
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

extern uint8_t cam_fb[CAM_FB_SIZE];
extern bool frame_data_available;
extern bool frame_packet_data_available;

#endif /* INC_CAMERA_H_ */
