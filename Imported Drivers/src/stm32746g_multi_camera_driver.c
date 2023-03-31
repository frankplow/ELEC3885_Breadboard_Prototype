#include "stm32746g_multi_camera_driver.h"
#include "camera_I2C.h"
#include "stdio.h"
#include "stdbool.h"

#define OV5640

uint8_t cam_fb[CAM_FB_SIZE];// __attribute__ ((section (".sdram"), aligned (4)));
// uint8_t jpeg_search_buffer[CAM_FB_SIZE];
uint8_t frameCounter = 0;
uint8_t *cam_data_location;
uint8_t buffer_offset;
uint8_t packetCounter = 0;


void DCMI_DMA_TRANSFER_HALF_COMPLETE(DMA_HandleTypeDef *hdma);
void DCMI_DMA_TRANSFER_COMPLETE(DMA_HandleTypeDef *hdma);

DCMI_HandleTypeDef  hDcmiHandler;
CAMERA_DrvTypeDef   *camera_drv;
/* Camera current resolution naming (QQVGA, VGA, ...) */
static uint32_t CameraCurrentResolution;

uint32_t JPEG_counter = 0;
uint32_t current_JPEG_size = 0;
uint8_t bufferblockcounter;

uint16_t JPEG_Size = 0;
uint16_t JPEG_FIFO_SIZE_BUFFER[20];
uint16_t JPEG_HEX_SIZE_BUFFER[20];
uint16_t JPEG_PACKET_COUNT_BUFFER[20];



#ifdef OV5640
uint8_t CAM_Init(uint8_t format, uint16_t x_res, uint16_t y_res, uint16_t FPS, uint16_t FB_size, uint16_t FIFO_width, uint8_t jpeg_comp_ratio)
{
  DCMI_HandleTypeDef *phdcmi;
  uint8_t status = CAMERA_ERROR;

  /* Get the DCMI handle structure */
  phdcmi = &hDcmiHandler;

  /*** Configures the DCMI to interface with the camera module ***/
  /* DCMI configuration */
  phdcmi->Init.CaptureRate      = DCMI_CR_ALL_FRAME;
  phdcmi->Init.HSPolarity       = DCMI_HSPOLARITY_HIGH;
  phdcmi->Init.SynchroMode      = DCMI_SYNCHRO_HARDWARE;
  phdcmi->Init.VSPolarity       = DCMI_VSPOLARITY_HIGH;
  phdcmi->Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
  phdcmi->Init.PCKPolarity      = DCMI_PCKPOLARITY_RISING;
   if (format == FMT_JPEG) {
	   phdcmi->Init.JPEGMode 		  = DCMI_JPEG_ENABLE;
	   printf("enabled JPEG\n");
   }
  phdcmi->Instance              = DCMI;


    status = CAMERA_ERROR;
	BSP_CAMERA_PwrDown();
    BSP_CAMERA_PwrUp();
	HAL_Delay(1000);
  printf("\nCamera power Up\n");
  /* Read ID of Camera module via I2C */
  if(ov5640_ReadID(CAMERA_I2C_ADDRESS_OV5640) == OV5640_ID)
  {
	printf("\nread ID correct\n");
    /* Initialize the camera driver structure */
    //camera_drv = &ov5640_drv;
    //CameraHwAddress = CAMERA_I2C_ADDRESS_OV5640;
	    switch (format)
	        {
	    		case FMT_JPEG:
	    		{
	    			ov5640_Init_JPEG(x_res, y_res);
	    			OV5640_Set_Comp_Ratio(jpeg_comp_ratio);
	    			OV5640_Set_FIFO_Width(FIFO_width);
	    			break;
	    		}
	    		case FMT_RGB565:
	    		{
	    			OV5640_Set_NightMode();
	    			ov5640_Init_RGB565(x_res, y_res);
	    			break;
	    		}
	    		default:
	    		{
	    			break;
	    		}
	        }

    /* DCMI Initialization */
    BSP_CAMERA_MspInit(&hDcmiHandler, NULL);
    HAL_DCMI_Init(phdcmi);
    HAL_DCMI_DisableCROP(phdcmi);

    /*USER ADD CONFIG ====== */
    //OV5640_SetLightMode(CAMERA_I2C_ADDRESS_OV5640, OV5640_LIGHT_AUTO);
    //OV5640_MirrorFlipConfig(CAMERA_I2C_ADDRESS_OV5640, OV5640_FLIP);
    /*USER ADD CONFIG ====== */
    status = CAMERA_OK;
  }
  else
  {
    /* Return CAMERA_NOT_SUPPORTED status */
    status = CAMERA_NOT_SUPPORTED;
    printf("\nread ID incorrect\n");
  }

  return status;
}
#endif


uint8_t BSP_CAMERA_DeInit(void)
{ 
  hDcmiHandler.Instance              = DCMI;

  HAL_DCMI_DeInit(&hDcmiHandler);
  BSP_CAMERA_MspDeInit(&hDcmiHandler, NULL);
  return CAMERA_OK;
}


void BSP_CAMERA_ContinuousStart()
{ 
  /* Start the camera capture */
  HAL_DCMI_Start_DMA2(&hDcmiHandler, DCMI_MODE_CONTINUOUS, cam_fb, (CAM_FB_SIZE/4));//GetSize(CameraCurrentResolution)); //0x1900
}


void BSP_CAMERA_SnapshotStart(uint8_t *buff)
{ 
  /* Start the camera capture */
  HAL_DCMI_Start_DMA(&hDcmiHandler, DCMI_MODE_SNAPSHOT, (uint32_t)buff, GetSize(CameraCurrentResolution));
}


void BSP_CAMERA_Suspend(void) 
{
  /* Suspend the Camera Capture */
  HAL_DCMI_Suspend(&hDcmiHandler);  
}


void BSP_CAMERA_Resume(void) 
{
  /* Start the Camera Capture */
  HAL_DCMI_Resume(&hDcmiHandler);
}


uint8_t BSP_CAMERA_Stop(void) 
{
  uint8_t status = CAMERA_ERROR;

  if(HAL_DCMI_Stop(&hDcmiHandler) == HAL_OK)
  {
     status = CAMERA_OK;
  }
  
  /* Set Camera in Power Down */
  BSP_CAMERA_PwrDown();

  return status;
}


void BSP_CAMERA_PwrUp(void)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock */
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
  gpio_init_structure.Pin       = GPIO_PIN_13;
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure);

  /* De-assert the camera POWER_DOWN pin (active high) */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13, GPIO_PIN_RESET);

  HAL_Delay(3);     /* POWER_DOWN de-asserted during 3ms */
}


void BSP_CAMERA_PwrDown(void)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock */
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
  gpio_init_structure.Pin       = GPIO_PIN_13;
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure);

  /* Assert the camera POWER_DOWN pin (active high) */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13, GPIO_PIN_SET);

}


__weak void BSP_CAMERA_MspInit(DCMI_HandleTypeDef *hdcmi, void *Params)
{
  static DMA_HandleTypeDef hdma_handler;
  GPIO_InitTypeDef gpio_init_structure;
  
  /*** Enable peripherals and GPIO clocks ***/
  /* Enable DCMI clock */
  __HAL_RCC_DCMI_CLK_ENABLE();

  /* Enable DMA2 clock */
  __HAL_RCC_DMA2_CLK_ENABLE();
  
  /* Enable GPIO clocks */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
  gpio_init_structure.Pin       = GPIO_PIN_4 | GPIO_PIN_6;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOA, &gpio_init_structure);

  gpio_init_structure.Pin       = GPIO_PIN_3;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  gpio_init_structure.Pin       = GPIO_PIN_5 | GPIO_PIN_6;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);

  gpio_init_structure.Pin       = GPIO_PIN_9;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);

  gpio_init_structure.Pin       = GPIO_PIN_9 | GPIO_PIN_10  | GPIO_PIN_11  |\
                                  GPIO_PIN_12 | GPIO_PIN_14;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure);

  /*** Configure the DMA ***/
  /* Set the parameters to be configured */
  hdma_handler.Init.Channel             = DMA_CHANNEL_1;
  hdma_handler.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_handler.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_handler.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_handler.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  hdma_handler.Init.Mode                = DMA_CIRCULAR;
  hdma_handler.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_handler.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  hdma_handler.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma_handler.Init.MemBurst            = DMA_MBURST_SINGLE;
  hdma_handler.Init.PeriphBurst         = DMA_PBURST_SINGLE; 

  hdma_handler.Instance = DMA2_Stream1;

  /* Associate the initialized DMA handle to the DCMI handle */
  __HAL_LINKDMA(hdcmi, DMA_Handle, hdma_handler);
  
  /*** Configure the NVIC for DCMI and DMA ***/
  /* NVIC configuration for DCMI transfer complete interrupt */
  HAL_NVIC_SetPriority(DCMI_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DCMI_IRQn);  
  
  /* NVIC configuration for DMA2D transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(hdcmi->DMA_Handle);  
}


/**
  * @brief  DeInitializes the DCMI MSP.
  * @param  hdcmi: HDMI handle 
  * @param  Params
  * @retval None
  */
__weak void BSP_CAMERA_MspDeInit(DCMI_HandleTypeDef *hdcmi, void *Params)
{
  /* Disable NVIC  for DCMI transfer complete interrupt */
  HAL_NVIC_DisableIRQ(DCMI_IRQn);  
  
  /* Disable NVIC for DMA2 transfer complete interrupt */
  HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn);
  
  /* Configure the DMA stream */
  HAL_DMA_DeInit(hdcmi->DMA_Handle);  

  /* Disable DCMI clock */
  __HAL_RCC_DCMI_CLK_DISABLE();

  /* GPIO pins clock and DMA clock can be shut down in the application 
     by surcharging this __weak function */ 
}

/**
  * @brief  Line event callback
  * @param  hdcmi: pointer to the DCMI handle  
  * @retval None
  */
void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
{        
  BSP_CAMERA_LineEventCallback();
  packetCounter++;
}

/**
  * @brief  Line Event callback.
  * @retval None
  */
__weak void BSP_CAMERA_LineEventCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_LineEventCallback could be implemented in the user file
   */
}

/**
  * @brief  VSYNC event callback
  * @param  hdcmi: pointer to the DCMI handle  
  * @retval None
  */
void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi)
{        
  BSP_CAMERA_VsyncEventCallback();
  frameCounter++;

  if (frameCounter > 20) {
	  JPEG_search_Full_Frame();
	  for (uint8_t i = 0; i < 20; i++) {
		  printf("\n#: %i : Packet #: %i Fifo size : %i Hex Size ; %i difference %i \n",
				  i, JPEG_PACKET_COUNT_BUFFER[i], JPEG_FIFO_SIZE_BUFFER[i], JPEG_HEX_SIZE_BUFFER[i],(JPEG_FIFO_SIZE_BUFFER[i] - JPEG_HEX_SIZE_BUFFER[i]) );
	  }
  }

  JPEG_Size = packetCounter * FIFO_SIZE;
  JPEG_FIFO_SIZE_BUFFER[frameCounter] = JPEG_Size;
  JPEG_PACKET_COUNT_BUFFER[frameCounter - 1] = packetCounter;
  packetCounter = 0;
  JPEG_Size = 0;




}
/**
  * @brief  VSYNC Event callback.
  * @retval None
  */
__weak void BSP_CAMERA_VsyncEventCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_VsyncEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Frame event callback
  * @param  hdcmi: pointer to the DCMI handle  
  * @retval None
  */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
  BSP_CAMERA_FrameEventCallback();
}

/**
  * @brief  Frame Event callback.
  * @retval None
  */
__weak void BSP_CAMERA_FrameEventCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_FrameEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Error callback
  * @param  hdcmi: pointer to the DCMI handle  
  * @retval None
  */
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi)
{        
  BSP_CAMERA_ErrorCallback();
}

/**
  * @brief  Error callback.
  * @retval None
  */
__weak void BSP_CAMERA_ErrorCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_ErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */  
  

void FPSCalculate(void) {
printf("\n%i FPS\n", frameCounter);
	frameCounter = 0;
}


HAL_StatusTypeDef HAL_DCMI_Start_DMA2(DCMI_HandleTypeDef *hdcmi, uint32_t DCMI_Mode, uint32_t pData, uint32_t Length)
{
  /* Initialize the second memory address */
  uint32_t SecondMemAddress = 0;

  /* Check function parameters */
  assert_param(IS_DCMI_CAPTURE_MODE(DCMI_Mode));

  /* Process Locked */
  __HAL_LOCK(hdcmi);

  /* Lock the DCMI peripheral state */
  hdcmi->State = HAL_DCMI_STATE_BUSY;

  /* Enable DCMI by setting DCMIEN bit */
  __HAL_DCMI_ENABLE(hdcmi);

  /* Configure the DCMI Mode */
  hdcmi->Instance->CR &= ~(DCMI_CR_CM);
  hdcmi->Instance->CR |= (uint32_t)(DCMI_Mode);

  /* Set the DMA memory0 conversion complete callback */
  hdcmi->DMA_Handle->XferCpltCallback = DCMI_DMA_TRANSFER_COMPLETE;
  hdcmi->DMA_Handle->XferHalfCpltCallback = DCMI_DMA_TRANSFER_HALF_COMPLETE;


  /* Set the DMA error callback */
  hdcmi->DMA_Handle->XferErrorCallback = DCMI_DMAError;

  /* Set the dma abort callback */
  hdcmi->DMA_Handle->XferAbortCallback = NULL;

  /* Reset transfer counters value */
  hdcmi->XferCount = 0;
  hdcmi->XferTransferNumber = 0;
  hdcmi->XferSize = 0;
  hdcmi->pBuffPtr = 0;

  if (Length <= 0xFFFFU)
  {
    /* Enable the DMA Stream */
    if (HAL_DMA_Start_IT(hdcmi->DMA_Handle, (uint32_t)&hdcmi->Instance->DR, (uint32_t)pData, Length) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else /* DCMI_DOUBLE_BUFFER Mode */
  {
    /* Set the DMA memory1 conversion complete callback */
    hdcmi->DMA_Handle->XferM1CpltCallback = DCMI_DMAXferCplt;

    /* Initialize transfer parameters */
    hdcmi->XferCount = 1;
    hdcmi->XferSize = Length;
    hdcmi->pBuffPtr = pData;

    /* Get the number of buffer */
    while (hdcmi->XferSize > 0xFFFFU)
    {
      hdcmi->XferSize = (hdcmi->XferSize / 2U);
      hdcmi->XferCount = hdcmi->XferCount * 2U;
    }

    /* Update DCMI counter  and transfer number*/
    hdcmi->XferCount = (hdcmi->XferCount - 2U);
    hdcmi->XferTransferNumber = hdcmi->XferCount;

    /* Update second memory address */
    SecondMemAddress = (uint32_t)(pData + (4 * hdcmi->XferSize));

    /* Start DMA multi buffer transfer */
    if (HAL_DMAEx_MultiBufferStart_IT(hdcmi->DMA_Handle, (uint32_t)&hdcmi->Instance->DR, (uint32_t)pData, SecondMemAddress, hdcmi->XferSize) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  /* Enable Capture */
  hdcmi->Instance->CR |= DCMI_CR_CAPTURE;

  /* Release Lock */
  __HAL_UNLOCK(hdcmi);

  /* Return function status */
  return HAL_OK;
}


void DCMI_DMA_TRANSFER_COMPLETE(DMA_HandleTypeDef *hdma)
{
  //printf("\n FULL transfer complete\n");
  //JPEG_search();
  uint32_t tmp = 0;
  cam_data_location = &cam_fb;
 //buffer_offset = 0;//CAM_FB_SIZE / 2;

  DCMI_HandleTypeDef *hdcmi = (DCMI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdcmi->XferCount != 0)
  {
    /* Update memory 0 address location */
    tmp = ((hdcmi->DMA_Handle->Instance->CR) & DMA_SxCR_CT);
    if (((hdcmi->XferCount % 2) == 0) && (tmp != 0))
    {
      tmp = hdcmi->DMA_Handle->Instance->M0AR;
      HAL_DMAEx_ChangeMemory(hdcmi->DMA_Handle, (tmp + (8 * hdcmi->XferSize)), MEMORY0);
      hdcmi->XferCount--;
    }
    /* Update memory 1 address location */
    else if ((hdcmi->DMA_Handle->Instance->CR & DMA_SxCR_CT) == 0)
    {
      tmp = hdcmi->DMA_Handle->Instance->M1AR;
      HAL_DMAEx_ChangeMemory(hdcmi->DMA_Handle, (tmp + (8 * hdcmi->XferSize)), MEMORY1);
      hdcmi->XferCount--;
    }
  }
  /* Update memory 0 address location */
  else if ((hdcmi->DMA_Handle->Instance->CR & DMA_SxCR_CT) != 0)
  {
    hdcmi->DMA_Handle->Instance->M0AR = hdcmi->pBuffPtr;
  }
  /* Update memory 1 address location */
  else if ((hdcmi->DMA_Handle->Instance->CR & DMA_SxCR_CT) == 0)
  {
    tmp = hdcmi->pBuffPtr;
    hdcmi->DMA_Handle->Instance->M1AR = (tmp + (4 * hdcmi->XferSize));
    hdcmi->XferCount = hdcmi->XferTransferNumber;
  }

  /* Enable the Frame interrupt */
  //frame_packet_data_available2 = true;

  /* Check if the frame is transferred */
  if (hdcmi->XferCount == hdcmi->XferTransferNumber)
  {
	__HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_FRAME);

	}

    /* When snapshot mode, set dcmi state to ready */
    if ((hdcmi->Instance->CR & DCMI_CR_CM) == DCMI_MODE_SNAPSHOT)
    {
      hdcmi->State = HAL_DCMI_STATE_READY;
    }
  }

void DCMI_DMA_TRANSFER_HALF_COMPLETE(DMA_HandleTypeDef *hdma) {
	//frame_packet_data_available1 = true;
	  cam_data_location = &cam_fb + (CAM_FB_SIZE /2);
	  //printf("\n Half transfer complete\n");

}

//void Get_JPEG_Size(void) {
//
//}

void JPEG_search_mini(void) {
//	uint32_t i=0;
//	for(i=0;i<(CAM_FB_SIZE/2);i++)//search for 0XFF 0XD8 and 0XFF 0XD9, get size of JPG
//	{
//		JPEG_counter = JPEG_counter + 1;
//		if((jpeg_search_buffer[i] ==0XFF)&&((jpeg_search_buffer[i + 1])==0XD8))
//		{
//			//current_JPEG_size = JPEG_counter;
//			printf("found JPEG\n");
//			//JPEG_counter = 0;
//
//		} else {
//			printf("done JPEG search\n");
//			break;
//		}
//	}
}

void JPEG_search_Full_Frame(void) {
			printf("\nsearching frame\n");
			//uint8_t *p;
	        uint32_t i=0,jpgstart=0,jpglen=0, padding_counter = 0;
	        uint8_t  head=0;
	        uint8_t found_jpeg_footer;
	        uint8_t jpeg_frame_counter = 1;

	        HAL_DCMI_Stop(&hDcmiHandler);

	        //p=(uint8_t*)cam_fb;

	        for(i=0;i<CAM_FB_SIZE; i++)//search for 0XFF 0XD8 and 0XFF 0XD9, get size of JPG
	        {
	                if((cam_fb[i]==0XFF)&&(cam_fb[i+1]==0XD8))
	                {
	                		found_jpeg_footer = 0;
	                		//printf("%i, total size: %d \r\n", jpeg_frame_counter, (jpglen + padding_counter)); //+ offset
	                		JPEG_HEX_SIZE_BUFFER[jpeg_frame_counter] = jpglen + padding_counter;
	                		padding_counter = 0;
	                		jpeg_frame_counter++;



	                        jpgstart=i;
	                        head=1;	// Already found  FF D8
	                        printf("\nfound header\n");
	                }
	                if((cam_fb[i]==0XFF)&&(cam_fb[i+1]==0XD9)&&head) //search for FF D9
	                {
                        	printf("\nfound footer\n");
	                        jpglen=i-jpgstart+2;
	                        found_jpeg_footer = 1;
	                }
	                if(((found_jpeg_footer == 1) && (cam_fb[i] == 0x00)) && (cam_fb[i+1]!=0XFF)&&(cam_fb[i+2]!=0XD8)) {
	                	padding_counter++;
	                }

	        }
	        if(jpglen)
	        {

	                printf("padding :  %d \r\n" , padding_counter);
	                //printf("jpgstart :  %d \r\n" , jpgstart);
	        }
}


