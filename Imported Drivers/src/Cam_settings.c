/*
 * Cam_settings.c
 *
 *  Created on: 30 Mar 2023
 *      Author: sol
 */

#include "Cam_settings.h"


// 320 x 240, 7.5 FPS, JPEG 25kb partial frame buffer

struct Cam_config default_settings =  {
		.img_format = FMT_JPEG,
		.x_res = 320,
		.y_res = 240,
		.FPS = 7.5,
		.FB_size = 320 * 40 * 2, // 25600
		.FIFO_width = 40,
		.jpeg_comp_ratio = 12
};
