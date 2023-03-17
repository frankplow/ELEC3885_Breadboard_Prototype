/*
 * camera.c
 *
 *  Created on: Jan 12, 2023
 *      Author: sol
 */

#include "camera_application.h"

#include <stdbool.h>

#include <fatfs.h>

DMA2D_HandleTypeDef hdma2d_eval;
uint32_t  *ptrLcd;
uint8_t status = CAMERA_OK;
uint8_t frameCounter;
uint8_t lineCounter;
//JPEG counter
uint8_t jpeg_packet_counter = 0;
uint64_t jpeg_frame_size = 0;
uint32_t jpeg_packet_size;



uint8_t cam_fb[CAM_FB_SIZE];// __attribute__ ((section (".sdram"), aligned (4)));
uint8_t lcd_fb[LCD_FB_SIZE] __attribute__ ((section (".sdram"), aligned (4)));



bool frame_data_available = false;
bool frame_packet_data_available1 = false;
bool frame_packet_data_available2 = false;



void LCD_init(void) {


	BSP_LCD_Init();
	uint32_t  *ptrLcd;
	/* Init LCD screen buffer */
	ptrLcd = (uint32_t*)(lcd_fb);
	for (int i=0; i<(BSP_LCD_GetXSize()*BSP_LCD_GetYSize()); i++)
	{
	ptrLcd[i]=0;
	}
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, lcd_fb);

	/* Set LCD Foreground Layer  */
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
		  printf("done screen\n");
}

void initialiseCapture(void) {
    memset(cam_fb, 255, CAM_FB_SIZE);
	//BSP_CAMERA_Init(CAMERA_R320x240);
    BSP_CAMERA_Init(FMT_JPEG, 320, 240);
    //BSP_CAMERA_Init(FMT_JPEG, 800, );
	BSP_CAMERA_ContinuousStart(cam_fb);
    //jpeg_packet_size= *((uint32_t *)0x4002642c);
}

BSP_CAMERA_LineEventCallback(void) {
//	lineCounter++;
//
//	if (lineCounter == 20) {
//		//printf("\n80 lines\n");
//		frame_packet_data_available1 = true;
//	} else if (lineCounter >= 40) {
//		lineCounter = 0;
//		frame_packet_data_available2 = true;
//	}

	//jpeg_packet_counter++;
}

BSP_CAMERA_VsyncEventCallback(void) {
	LCD_DMA_Transfer_RGBTOARGB8888((uint32_t *)cam_fb, (uint32_t *)lcd_fb);
	frameCounter++;
	frame_data_available = true;
	//jpeg_frame_size = ()jpeg_packet_counter * jpeg_packet_size;
//	printf("\nPACKET PER FRAME:  %i\n", jpeg_packet_counter);
//	printf("\nPACKET packet size:  %i\n", jpeg_packet_size);
//	printf("\nJPEG FRAME SIZE: %i\n", jpeg_frame_size);
//	jpeg_packet_counter = 0;
}


void FPSCalculate(void) {
printf("\n%i FPS\n", frameCounter);
	frameCounter = 0;
}



void LCD_DMA_Transfer_RGBTOARGB8888(void *pSrc, void *pDst) {
	  /* Enable DMA2D clock */
	  //__HAL_RCC_DMA2D_CLK_ENABLE();

	  /* Configure the DMA2D Mode, Color Mode and output offset */
	  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
	  hdma2d_eval.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
	  //hdma2d_eval.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
	  hdma2d_eval.Init.OutputOffset = 0;

	  /* Foreground Configuration */
	  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
	  hdma2d_eval.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
	  hdma2d_eval.LayerCfg[1].InputOffset = 0;

	  hdma2d_eval.Instance = DMA2D;

	  /* DMA2D Initialization */
	  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
	  {

	    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
	    {
	      if (HAL_DMA2D_Start(&hdma2d_eval, (uint32_t)pSrc, (uint32_t)pDst, X_RES, Y_RES) == HAL_OK)
	      {
	        /* Polling For DMA transfer */
	        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
	      }
	    }
	  }
	  else
	  {
	    /* FatFs Initialization Error */
		  printf("\nFatFs Initialization Error\n");
	    while(1);
	  }

}

void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst)
{
  /* Enable DMA2D clock */
  __HAL_RCC_DMA2D_CLK_ENABLE();

  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d_eval.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
  //hdma2d_eval.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
  hdma2d_eval.Init.OutputOffset = 0;

  /* Foreground Configuration */
  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d_eval.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d_eval.LayerCfg[1].InputOffset = 0;

  hdma2d_eval.Instance = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&hdma2d_eval, (uint32_t)pSrc, (uint32_t)pDst, 480, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */

        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
      }
    }
  }
  else
  {
    /* FatFs Initialization Error */
	  printf("\nFatFs Initialization Error\n");
    while(1);
  }
}


void BSP_CAMERA_ErrorCallback(void) {
	//printf("\nDCMI ERROR\n");
}
