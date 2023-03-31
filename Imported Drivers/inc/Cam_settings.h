/*
 * Cam_settings.h
 *
 *  Created on: 30 Mar 2023
 *      Author: sol
 */

#ifndef INC_CAM_SETTINGS_H_
#define INC_CAM_SETTINGS_H_

#define FMT_JPEG 0x00
#define FMT_RGB565 0x01

#include "stdint.h"

struct res_table
{						//	x     y   partial FB SIZE
	uint16_t QQVGA[2];// = {160, 120};
	uint16_t QVGA[2];// = {320, 240};
	uint16_t LCD[2];// =  {480, 270};
	uint16_t VGA[2]; //=  {640, 480};
	uint16_t SVGA[2];// = {800, 600};

};

struct Cam_config {
	uint8_t img_format;
	uint16_t x_res;
	uint16_t y_res;
	uint16_t FPS;
	uint16_t FB_size;
	uint16_t FIFO_width;
	uint8_t jpeg_comp_ratio; //1 - 63 lower = more compression

};

extern struct Cam_config default_settings;


//void set_default_config(void){
//	default_config.format = FMT_JPEG;
//	default_config.x_res = 320;
//	default_config.y_res = 240;
//	default_config.FPS = 8.5;
//	default_config.FB_size = 320 * 40 * 2; // 25600
//	default_config.FIFO_width = 40;
//	default_config.jpeg_comp_ratio = 12;
//}

#endif
