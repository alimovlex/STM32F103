#include "stm32f10x.h"
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "stm32f10x_rtc.h"              // Keil::Device:StdPeriph Drivers:RTC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_wwdg.h"             // Keil::Device:StdPeriph Drivers:WWDG
#include "Source.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;
int main(void)
{
	init();
	
  return 0;
}
