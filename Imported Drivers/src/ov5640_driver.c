
#include <ov5640_driver.h>
#include "ov5640_registers.h"
#include "ov5640_reg_settings.h"

#define OV5640_POLARITY_PCLK_LOW  0x00U /* Signal Active Low          */
#define OV5640_POLARITY_PCLK_HIGH 0x01U /* Signal Active High         */
#define OV5640_POLARITY_HREF_LOW  0x00U /* Signal Active Low          */
#define OV5640_POLARITY_HREF_HIGH 0x01U /* Signal Active High         */
#define OV5640_POLARITY_VSYNC_LOW 0x01U /* Signal Active Low          */
#define OV5640_POLARITY_VSYNC_HIGH  0x00U /* Signal Active High         */

//static uint32_t ov5640_ConvertValue(uint32_t feature, uint32_t value);
uint32_t  jpeg_buf_size = 0;

const uint16_t jpeg_size_tbl[][2]=
{
  {160, 120},	//QQVGA
	{176, 144},	//QCIF
	{320, 240},	//QVGA
	{400, 240},	//WQVGA
	{352, 288},	//CIF
	{640, 480},	//VGA
  {800, 600},	//SVGA
};

const uint32_t jpeg_buf_max_size[]=
{
    20*1024,	//QQVGA
	30*1024,	//QCIF
	100*1024,	//QVGA
	100*1024,	//WQVGA
	100*1024,	//CIF
	200*1024,	//VGA
    400*1024,	//SVGA
};

void ov5640_Init(void) {
	uint32_t index = 0;
	  for(index=0; index< (sizeof(OV5640_default_reg_settings)/4) ; index++)
	  {
	    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_default_reg_settings[index][0], OV5640_default_reg_settings[index][1]);
	  }
}

void ov5640_Set_JPEG(void) {
	uint32_t index = 0;
	for(index=0; index<(sizeof(format_jpeg)/4); index++)
	{
	   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, format_jpeg[index][0], format_jpeg[index][1]);
	}
}

void ov5640_Set_RGB565(void) {
	uint32_t index = 0;
	for(index=0; index<(sizeof(format_rgb565)/4); index++)
	{
	   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, format_rgb565[index][0], format_rgb565[index][1]);
	}
}

void ov5640_Init_JPEG(uint16_t x_res, uint16_t y_res)
{
  //uint32_t index = 0;
  uint8_t tmp = 0;
  //uint8_t redreg = 0;
  //send initial config

  ov5640_Init();
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3035, 0X41); // slow down OV5640 clocks
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3036, 0x79);

  OV5640_Set_Size(4, 0, x_res, y_res);
  ov5640_Set_JPEG();
  OV5640_SetPCLK(OV5640_PCLK_24M);


  //set timings

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS,OV5640_TIMING_TC_REG21);
  tmp |= (1 << 5);
  printf("\ntemp for OV5640_TIMING_TC_REG21 = %i\n",tmp);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_TC_REG21, tmp);

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS,OV5640_SYSREM_RESET02);
  tmp &= ~((1 << 4) | (1 << 3) | (1 << 2));
  printf("\ntemp for OV5640_SYSREM_RESET02 = %i\n",tmp);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSREM_RESET02, tmp);


  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS,OV5640_CLOCK_ENABLE02);
  tmp |= ((1 << 5) | (1 << 3));
  printf("\ntemp for OV5640_CLOCK_ENABLE02 = %i\n",tmp);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_CLOCK_ENABLE02, tmp);
  //set polaratis

  tmp = (uint8_t)(OV5640_POLARITY_PCLK_HIGH << 5U) | (OV5640_POLARITY_HREF_HIGH << 1U) | OV5640_POLARITY_VSYNC_HIGH;
  printf("\ntemp for OV5640_POLARITY_CTRL = %i\n",tmp);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_POLARITY_CTRL, tmp);


}

int32_t OV5640_SetPCLK(uint32_t ClockValue)
{

  uint8_t tmp;

  switch(ClockValue)
  {
  case OV5640_PCLK_7M:
    tmp = 0x38;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);

    tmp = 0x16;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);

    break;
  case OV5640_PCLK_8M:
    tmp = 0x40;
    //ret = ov5640_write_reg(&pObj->Ctx, OV5640_SC_PLL_CONTRL2, &tmp, 1);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);
    tmp = 0x16;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;
  case OV5640_PCLK_9M:
  tmp = 0x00; //unsure
	CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);
    tmp = 0x18;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;
  case OV5640_PCLK_12M:
  tmp = 0x00; //unsure
	CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);
    tmp = 0x16;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;
  case OV5640_PCLK_24M:
  default:
    tmp = 0x60;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);

    tmp = 0x13;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;

    //return ret;

  }
}


void ov5640_Init_RGB565(uint16_t x_res, uint16_t y_res)
{
  ov5640_Init();
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3035, 0X21);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3036, 0x98);


  OV5640_Set_Size(4, 0, x_res, y_res);
  ov5640_Set_RGB565();
  OV5640_SetPCLK(OV5640_PCLK_24M);

//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL1, 0X41);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x69);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x98);


}

uint16_t ov5640_ReadID(void)
{
  uint16_t read_val = 0;

  /* Initialize I2C */
  CAMERA_IO_Init();

  /* Prepare the camera to be configured */
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, SYSTEM_CTROL0, 0x80);
  CAMERA_Delay(500);

  read_val = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, 0x300A);
  read_val = read_val << 8;
  read_val |= CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, 0x300B);
  /* Get the camera ID */
  return read_val;
}

uint8_t OV5640_Set_Size(uint16_t offx,uint16_t offy,uint16_t width,uint16_t height)
{
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3212, 0x03);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_H, width >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_L, width &0xff);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_H, height >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_L, height &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3810, offx >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3811, offx &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3812, offy >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3813, offy &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3212, 0x13);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3212, 0xa3);

		//CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, FORMAT_CTRL00, 0x6F);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, CLOCK_POL_CONTROL, 0x22);

        if(width==jpeg_size_tbl[QQVGA_160_120][0] && height==jpeg_size_tbl[QQVGA_160_120][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[QQVGA_160_120];
        }
        else if(width==jpeg_size_tbl[QCIF_176_144][0] && height==jpeg_size_tbl[QCIF_176_144][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[QCIF_176_144];
        }
        else if(width==jpeg_size_tbl[QVGA_320_240][0] && height==jpeg_size_tbl[QVGA_320_240][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[QVGA_320_240];
        }
        else if(width==jpeg_size_tbl[WQVGA_400_240][0] && height==jpeg_size_tbl[WQVGA_400_240][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[WQVGA_400_240];
        }
        else if(width==jpeg_size_tbl[CIF_352_288][0] && height==jpeg_size_tbl[CIF_352_288][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[CIF_352_288];
        }
        else if(width==jpeg_size_tbl[VGA_640_480][0] && height==jpeg_size_tbl[VGA_640_480][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[VGA_640_480];
        }
        else if(width==jpeg_size_tbl[SVGA_800_600][0] && height==jpeg_size_tbl[SVGA_800_600][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[SVGA_800_600];
        }

        return 0;
}

//0-63, lower number means higher quality
//void OV5640_JPEG_Config(uint16_t quality, uint16_t width, uint16_t height) {
//	 //set JPEG quality
//	 uint8_t fifo_control = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00);
//	 printf("\nrfifo control: %x\n", fifo_control);
//	 //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00, fifo_control | 0x08);
//
//	 //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, COMPRESSION_CTRL07, quality & 0x3f);
//	 //set JPEG PACKET size, variable width
//
//
////	 uint16_t left_byte = width >> 8;
////	 uint16_t right_byte = width << 8;
////	 uint16_t bit_swapped;
//
//	 //&0x00FF;
//
//	 //swapped = (num>>8) | (num<<8);
//
//
//
//	  // = (width >> 8) + width &0x00FF;
//
//
//	 printf("\n Left byte = %x\n", left_byte);
//	 printf("\n  right_byte = %x\n", right_byte);
//
//	 //bit_swapped = right_byte | left_byte;
//
//	 printf("\n bits swapped = %x\n", bit_swapped);
//
//
//	 //width (variable)
//	 //CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H, bit_swapped);
//
//	 //Height (constant)
//     //CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H, height);
//
//	 uint16_t read_width = CAMERA_IO_Read_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H);
//     printf("\nread fifo width: %i\n", read_width);
//
//	 uint16_t read_height = CAMERA_IO_Read_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H);
//	 printf("\nread height width: %i\n", read_height);
//
//
//
//
//}

void OV5640_Set_FIFO_Width(uint16_t fifo_width)
 {
	 uint16_t left_byte, right_byte, bit_swapped;

	 left_byte	= fifo_width >> 8;
	 right_byte = fifo_width << 8;
	 bit_swapped = right_byte | left_byte;

	 CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H, bit_swapped);
}

void OV5640_Set_Comp_Ratio(uint16_t comp_ratio) {
	 CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, COMPRESSION_CTRL07, comp_ratio & 0x3f);

}


void OV5640_Set_NightMode(void)
{
	uint32_t index = 0;
	for(index=0; index<(sizeof(OV5640_NightMode)/4); index++)
	{
	   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_NightMode[index][0], OV5640_NightMode[index][1]);
	}
}

void OV5640_MirrorFlipConfig1(uint8_t Config)
{
  uint8_t tmp3820 = 0, tmp3821;

  tmp3820 = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20);
  tmp3820 &= 0xF9;
  tmp3821 = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21);
  tmp3821 &= 0xF9;

  switch (Config)
  {
  case OV5640_MIRROR:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x06);
    break;

  case OV5640_FLIP:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x06);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x00);
    break;
  case OV5640_MIRROR_FLIP:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x06);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x06);
    break;

  case OV5640_MIRROR_FLIP_NORMAL:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x06);
    break;

  default:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x00);
    break;
  }
}

/**
  * @brief  Set the OV5640 camera Light Mode.
  * @param  OV5640_I2C_ADDRESS : Device address on communication Bus.
  * @param  Effect : Effect to be configured
  * @retval None
  */
//void OV5640_SetLightMode(uint16_t OV5640_I2C_ADDRESS, uint8_t LightMode)
//{
//  uint32_t index = 0;
//
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3406, 0x00);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5190, 0x46);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5191, 0xf8);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5192, 0x04);
//
//  switch(LightMode)
//  {
//  case OV5640_LIGHT_AUTO:
//    for(index=0; index< (sizeof(OV5640_LightModeAuto)/4) ; index++)
//    {
//      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_LightModeAuto[index][0], OV5640_LightModeAuto[index][1]);
//    }
//    break;
//  case OV5640_LIGHT_SUNNY:
//    for(index=0; index< (sizeof(OV5640_LightModeSunny)/4) ; index++)
//    {
//      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_LightModeSunny[index][0], OV5640_LightModeSunny[index][1]);
//    }
//    break;
//  case OV5640_LIGHT_OFFICE:
//    for(index=0; index< (sizeof(OV5640_LightModeOffice)/4) ; index++)
//    {
//      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_LightModeOffice[index][0], OV5640_LightModeOffice[index][1]);
//    }
//    break;
//  case OV5640_LIGHT_CLOUDY:
//    for(index=0; index< (sizeof(OV5640_LightModeCloudy)/4) ; index++)
//    {
//      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_LightModeCloudy[index][0], OV5640_LightModeCloudy[index][1]);
//    }
//    break;
//  case OV5640_LIGHT_HOME:
//    for(index=0; index< (sizeof(OV5640_LightModeHome)/4) ; index++)
//    {
//      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_LightModeHome[index][0], OV5640_LightModeHome[index][1]);
//    }
//    break;
//  default :
//    /* Auto light mode used */
//    for(index=0; index< (sizeof(OV5640_LightModeAuto)/4) ; index++)
//    {
//      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_LightModeAuto[index][0], OV5640_LightModeAuto[index][1]);
//    }
//    break;
//  }
//}

/**
  * @brief  Set the OV5640 camera Special Effect.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @param  Effect: Effect to be configured
  * @retval None
  */
//void OV5640_SetEffect(uint16_t OV5640_I2C_ADDRESS, uint32_t Effect)
//{
//  switch(Effect)
//  {
//  case OV5640_COLOR_EFFECT_NONE:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0x7F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x00);
//    break;
//
//  case OV5640_COLOR_EFFECT_BLUE:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0xA0);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x40);
//    break;
//
//  case OV5640_COLOR_EFFECT_RED:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0xC0);
//    break;
//
//  case OV5640_COLOR_EFFECT_GREEN:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x60);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x60);
//    break;
//
//  case OV5640_COLOR_EFFECT_BW:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x80);
//    break;
//
//  case OV5640_COLOR_EFFECT_SEPIA:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0xA0);
//    break;
//
//  case OV5640_COLOR_EFFECT_NEGATIVE:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x40);
//    break;
//
//  case OV5640_COLOR_EFFECT_BW_NEGATIVE:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x58);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x40);
//    break;
//
//  case OV5640_COLOR_EFFECT_OVEREXPOSURE:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0xF0);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0xF0);
//    break;
//
//  case OV5640_COLOR_EFFECT_SOLARIZE:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x06);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x10);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5003, 0x09);
//    break;
//
//  default :
//    /* No effect */
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0x7F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x00);
//    break;
//  }
//}

/**
  * @brief  Set the OV5640 camera Brightness Level.
  * @note   The brightness of OV5640 could be adjusted. Higher brightness will
  *         make the picture more bright. The side effect of higher brightness
  *         is the picture looks foggy.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @param  Level: Value to be configured
  * @retval None
  */
//void OV5640_SetBrightness(uint16_t OV5640_I2C_ADDRESS, uint8_t Level)
//{
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//
//  switch(Level)
//  {
//  case OV5640_BRIGHTNESS_LEVEL4P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x40);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL3P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x30);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL2P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x20);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL1P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x10);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL0:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x00);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL1N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x10);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL2N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x20);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL3N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x30);
//    break;
//
//  case OV5640_BRIGHTNESS_LEVEL4N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x40);
//    break;
//
//  default:
//    /* Level 0 as default */
//    Level = OV5640_BRIGHTNESS_LEVEL0;
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5587, 0x00);
//    break;
//  }
//
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x04);
//
//  if(Level < OV5640_SATURATION_LEVEL1N)
//  {
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x01);
//  }
//  else
//  {
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x09);
//  }
//}

/**
  * @brief  Set the OV5640 camera Saturation Level.
  * @note   The color saturation of OV5640 could be adjusted. High color saturation
  *         would make the picture looks more vivid, but the side effect is the
  *         bigger noise and not accurate skin color.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @param  Level: Value to be configured
  * @retval None
  */
//void OV5640_SetSaturation(uint16_t OV5640_I2C_ADDRESS, uint8_t Level)
//{
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//
//  switch(Level)
//  {
//  case OV5640_SATURATION_LEVEL4P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x40);
//    break;
//
//  case OV5640_SATURATION_LEVEL3P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x50);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x50);
//    break;
//
//  case OV5640_SATURATION_LEVEL2P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x60);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x60);
//    break;
//
//  case OV5640_SATURATION_LEVEL1P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x70);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x70);
//    break;
//
//  case OV5640_SATURATION_LEVEL0:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x80);
//    break;
//
//  case OV5640_SATURATION_LEVEL1N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x30);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x30);
//    break;
//
//  case OV5640_SATURATION_LEVEL2N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x20);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x20);
//    break;
//
//  case OV5640_SATURATION_LEVEL3N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x10);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x10);
//    break;
//
//  case OV5640_SATURATION_LEVEL4N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x00);
//    break;
//
//  default:
//    /* Level 0 as default */
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5583, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5584, 0x40);
//    break;
//  }
//
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x02);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x41);
//}
//
///**
//  * @brief  Set the OV5640 camera Contrast Level.
//  * @note   The contrast of OV5640 could be adjusted. Higher contrast will make
//  *         the picture sharp. But the side effect is loosing dynamic range.
//  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
//  * @param  Level: Value to be configured
//  * @retval None
//  */
//void OV5640_SetContrast(uint16_t OV5640_I2C_ADDRESS, uint8_t Level)
//{
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x04);
//
//  switch(Level)
//  {
//  case OV5640_CONTRAST_LEVEL4P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x30);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x30);
//    break;
//
//  case OV5640_CONTRAST_LEVEL3P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x2C);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x2C);
//    break;
//
//  case OV5640_CONTRAST_LEVEL2P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x28);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x28);
//    break;
//
//  case OV5640_CONTRAST_LEVEL1P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x24);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x24);
//    break;
//
//  case OV5640_CONTRAST_LEVEL0:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x20);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x20);
//    break;
//
//  case OV5640_CONTRAST_LEVEL1N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x1C);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x1C);
//    break;
//
//  case OV5640_CONTRAST_LEVEL2N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x18);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x18);
//    break;
//
//  case OV5640_CONTRAST_LEVEL3N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x14);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x14);
//    break;
//
//  case OV5640_CONTRAST_LEVEL4N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x10);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x10);
//    break;
//
//  default:
//    /* Level 0 as default */
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5586, 0x20);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5585, 0x20);
//    break;
//  }
//
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x41);
//}
//
///**
//  * @brief  Set the OV5640 camera Hue degree.
//  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
//  * @param  Level: Value to be configured
//  * @retval None
//  */
//void OV5640_SetHueDegree(uint16_t OV5640_I2C_ADDRESS, uint16_t Degree)
//{
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, ISP_CONTROL_01, 0xFF);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5580, 0x01);
//
//  switch(Degree)
//  {
//  case OV5640_HUE_150P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x31);
//    break;
//
//  case OV5640_HUE_120P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x31);
//    break;
//
//  case OV5640_HUE_90P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x31);
//    break;
//
//  case OV5640_HUE_60P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x01);
//    break;
//
//  case OV5640_HUE_30P:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x01);
//    break;
//
//  case OV5640_HUE_0:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x01);
//    break;
//
//  case OV5640_HUE_30N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x02);
//    break;
//
//  case OV5640_HUE_60N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x02);
//    break;
//
//  case OV5640_HUE_90N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x02);
//    break;
//
//  case OV5640_HUE_120N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x32);
//    break;
//
//  case OV5640_HUE_150N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x6F);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x40);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x32);
//    break;
//
//  case OV5640_HUE_180N:
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x32);
//    break;
//
//  default:
//    /* Hue degree 0 as default */
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5581, 0x80);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5582, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5588, 0x01);
//    break;
//  }
//}

/**
  * @brief  Control OV5640 camera mirror/vflip.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @param  Config: To configure mirror, flip, both or nothing
  * @retval None
  */


/**
  * @brief  Control OV5640 camera mirror/vflip.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @param  Zoom: Zoom to be configured
  * @retval None
  */
//void OV5640_ZoomConfig(uint16_t OV5640_I2C_ADDRESS, uint8_t Zoom)
//{
//  int32_t res = 0;
//
//  /* Get camera resolution */
//  res = OV5640_GetResolution(OV5640_I2C_ADDRESS);
//
//  if(Zoom == OV5640_ZOOM_x1)
//  {
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5600, 0x10);
//  }
//  else
//  {
//    switch (res)
//    {
//    case CAMERA_R320x240:
//    case CAMERA_R480x272:
//      Zoom = Zoom >> 1;
//      break;
//    case CAMERA_R640x480:
//      Zoom = Zoom >> 2;
//      break;
//    default:
//      break;
//    }
//
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x5600, 0x00);
//    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, SCALE_CTRL_1, Zoom);
//  }
//}

/**
  * @brief  Get OV5640 camera resolution.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @retval Camera resolution else 0xFF
  */
//int32_t OV5640_GetResolution(uint16_t OV5640_I2C_ADDRESS)
//{
//  uint16_t x_size = 0, y_size = 0;
//  int32_t res = CAMERA_R640x480;
//
//  x_size = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_H) << 8;
//  x_size |= CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_L);
//  y_size = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_H) << 8;
//  y_size |= CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_L);
//
//  if((x_size == 640) && (y_size == 480))
//  {
//    res = CAMERA_R640x480;
//  }
//  else if((x_size == 480) && (y_size == 272))
//  {
//    res = CAMERA_R480x272;
//  }
//  else if((x_size == 320) && (y_size == 240))
//  {
//    res = CAMERA_R320x240;
//  }
//  else if((x_size == 160) && (y_size == 120))
//  {
//    res = CAMERA_R160x120;
//  }
//  else
//  {
//    res = 0xFF;
//  }
//  return res;
//}

/**
  * @brief  Configures the OV5640 camera feature.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @param  feature: Camera feature to be configured
  * @param  value: Value to be configured
  * @param  brightness_value: Brightness value to be configured
  * @retval None
  */
//void ov5640_Config(uint32_t feature, uint32_t value, uint32_t brightness_value)
//{
//  uint32_t value_tmp;
//  uint32_t br_value;
//
//  /* Convert the input value into ov5640 parameters */
//  value_tmp = ov5640_ConvertValue(feature, value);
//  br_value = ov5640_ConvertValue(CAMERA_CONTRAST_BRIGHTNESS, brightness_value);
//
//  switch(feature)
//  {
//  case CAMERA_CONTRAST_BRIGHTNESS:
//    {
//      OV5640_SetContrast(OV5640_I2C_ADDRESS, value_tmp);
//      OV5640_SetBrightness(OV5640_I2C_ADDRESS, br_value);
//      break;
//    }
//  case CAMERA_BLACK_WHITE:
//  case CAMERA_COLOR_EFFECT:
//    {
//      OV5640_SetEffect(OV5640_I2C_ADDRESS, value_tmp);
//      break;
//    }
//  default:
//    {
//      break;
//    }
//  }
//}

/**
  * @brief  Read the OV5640 Camera identity.
  * @param  OV5640_I2C_ADDRESS: Device address on communication Bus.
  * @retval the OV5640 ID
  */


/******************************************************************************
                            Static Functions
*******************************************************************************/
/**
  * @brief  Convert input values into ov5640 parameters.
  * @param  feature: Camera feature to be configured
  * @param  value: Value to be configured
  * @retval The converted value
  */
//static uint32_t ov5640_ConvertValue(uint32_t feature, uint32_t value)
//{
//  uint32_t ret = 0;
//
//  switch(feature)
//  {
//  case CAMERA_BLACK_WHITE:
//    {
//      switch(value)
//      {
//      case CAMERA_BLACK_WHITE_BW:
//        {
//          ret =  OV5640_COLOR_EFFECT_BW;
//          break;
//        }
//      case CAMERA_BLACK_WHITE_NEGATIVE:
//        {
//          ret =  OV5640_COLOR_EFFECT_NEGATIVE;
//          break;
//        }
//      case CAMERA_BLACK_WHITE_BW_NEGATIVE:
//        {
//          ret =  OV5640_COLOR_EFFECT_BW_NEGATIVE;
//          break;
//        }
//      case CAMERA_BLACK_WHITE_NORMAL:
//      default:
//        {
//          ret =  OV5640_COLOR_EFFECT_NONE;
//          break;
//        }
//      }
//      break;
//    }
//  case CAMERA_CONTRAST_BRIGHTNESS:
//    {
//      switch(value)
//      {
//      case CAMERA_BRIGHTNESS_LEVEL0:
//        {
//          ret =  OV5640_BRIGHTNESS_LEVEL4N;
//          break;
//        }
//      case CAMERA_BRIGHTNESS_LEVEL1:
//        {
//          ret =  OV5640_BRIGHTNESS_LEVEL2N;
//          break;
//        }
//      case CAMERA_BRIGHTNESS_LEVEL2:
//        {
//          ret =  OV5640_BRIGHTNESS_LEVEL0;
//          break;
//        }
//      case CAMERA_BRIGHTNESS_LEVEL3:
//        {
//          ret =  OV5640_BRIGHTNESS_LEVEL2P;
//          break;
//        }
//      case CAMERA_BRIGHTNESS_LEVEL4:
//        {
//          ret =  OV5640_BRIGHTNESS_LEVEL4P;
//          break;
//        }
//      case CAMERA_CONTRAST_LEVEL0:
//        {
//          ret =  OV5640_CONTRAST_LEVEL4N;
//          break;
//        }
//      case CAMERA_CONTRAST_LEVEL1:
//        {
//          ret =  OV5640_CONTRAST_LEVEL2N;
//          break;
//        }
//      case CAMERA_CONTRAST_LEVEL2:
//        {
//          ret =  OV5640_CONTRAST_LEVEL0;
//          break;
//        }
//      case CAMERA_CONTRAST_LEVEL3:
//        {
//          ret =  OV5640_CONTRAST_LEVEL2P;
//          break;
//        }
//      case CAMERA_CONTRAST_LEVEL4:
//        {
//          ret =  OV5640_CONTRAST_LEVEL4P;
//          break;
//        }
//      default:
//        {
//          ret =  OV5640_CONTRAST_LEVEL0;
//          break;
//        }
//      }
//      break;
//    }
//  case CAMERA_COLOR_EFFECT:
//    {
//      switch(value)
//      {
//      case CAMERA_COLOR_EFFECT_ANTIQUE:
//        {
//          ret =  OV5640_COLOR_EFFECT_SEPIA;
//          break;
//        }
//      case CAMERA_COLOR_EFFECT_BLUE:
//        {
//          ret =  OV5640_COLOR_EFFECT_BLUE;
//          break;
//        }
//      case CAMERA_COLOR_EFFECT_GREEN:
//        {
//          ret =  OV5640_COLOR_EFFECT_GREEN;
//          break;
//        }
//      case CAMERA_COLOR_EFFECT_RED:
//        {
//          ret =  OV5640_COLOR_EFFECT_RED;
//          break;
//        }
//      case CAMERA_COLOR_EFFECT_NONE:
//      default:
//        {
//          ret =  OV5640_COLOR_EFFECT_NONE;
//          break;
//        }
//      }
//      break;
//    default:
//      {
//        ret = 0;
//        break;
//      }
//    }
//  }
//
//  return ret;
//}

/**
  * @}
  */

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
