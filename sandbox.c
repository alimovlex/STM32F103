#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "delay.h"
#include "timer.h"
#include "i2c.h"
#include "usart.h"
#include "ff.h"
#include "LiquidCrystal_I2C.h"
#include "lcd_i2c.h"
//#define SLAVE_ADDRESS		0x08
GPIO_InitTypeDef GPIOInitStruct;
void LED()
{
		
	// Initialize GPIOA as output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	
	while (1)
	{
		/* LED blink every 1s */
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay(1000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay(1000);
	}
}

void button(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
		// Cofigure PA1 as input with internal pull-up resistor
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	
	// Initialize GPIOA as output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	
	while (1)
	{
		// If button on PA1 is pressed (button circuit is active low)
		if (!(GPIO_ReadInputData(GPIOA) & GPIO_Pin_0))
		{
			// Turn on LED on PA0 (LED circuit is active low)
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}
		else
		{
			// Turn off LED on PA0
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}
	}
}

void timer(void)
{

	// Initialize timer interrupt
	TIM2_INT_Init();
	
	// Initialize PB12 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	
	while (1)
	{
		// Blink LED on PC13
		GPIOC->BRR = GPIO_Pin_13;
		DelayMC(2500);
		GPIOC->BSRR = GPIO_Pin_13;
		Delay(2500);
	}
}

void sd_card(void)
{
	char	buff[1024];	

	FATFS FATFS_Obj;
	DIR dir;
	FIL file;
	UINT nRead, nWritten;
//	static uint8_t ReciveByte=0x00; 		
	USART1_Init();
	f_mount(&FATFS_Obj, "0", 1);
	f_opendir(&dir, "/");
	f_mkdir("0:UARTdata");
  f_open(&file, "0:UARTdata/data.txt", FA_CREATE_NEW | FA_READ | FA_WRITE);
	f_write(&file, &buff, nRead, &nWritten);
	f_close(&file);
	
}

void usart(void)
{
	USART1_Init();
	Usart1_Send_String("Hello MGTOW");
}

void lcd(void)
{
	int i;
	FILE *fp;
	char buff[255];
	char *sstr = "Hi, It works!!!";
	//srand((unsigned)time(NULL));
	LCDI2C_init(0x27,20,4);
  // ------- Quick 3 blinks of backlight  -------------
  for( i = 0; i< 3; i++)
  {
    LCDI2C_backlight();
    Delay(100);
    LCDI2C_noBacklight();
    Delay(100);
  }
  LCDI2C_backlight(); // finish with backlight on
	//fp=fopen("test.txt","r");
       
			LCDI2C_write_String(sstr);
  //fclose(fp);
}	

void demo(void)
{
  int i;
  Delay(3000);
  LCDI2C_init(0x27,20,4);
  // ------- Quick 3 blinks of backlight  -------------
  for( i = 0; i< 3; i++)
  {
    LCDI2C_backlight();
    Delay(250);
    LCDI2C_noBacklight();
    Delay(250);
  }
  LCDI2C_backlight(); // finish with backlight on
  LCDI2C_write(53);
  Delay(2000);
  LCDI2C_clear();
  displayKeyCodes();
  Delay(2000);
  LCDI2C_createChar(0, bell);
  LCDI2C_createChar(1, note);
 // LCDI2C_createChar(2, clock);
  LCDI2C_createChar(3, heart);
  LCDI2C_createChar(4, duck);
  LCDI2C_createChar(5, check);
  LCDI2C_createChar(6, cross);
  LCDI2C_createChar(7, retarrow);
  LCDI2C_clear();
  for (i=0; i<8; i++) {
        LCDI2C_write(i);
  }
  Delay(3000);
  LCDI2C_createChar(0, habr1);
  LCDI2C_createChar(1, habr2);
  LCDI2C_createChar(2, habr3);
  LCDI2C_createChar(3, habr4);
  LCDI2C_createChar(4, habr5);
  LCDI2C_createChar(5, habr6);
  LCDI2C_createChar(6, habr7);
  LCDI2C_createChar(7, habr8);
  LCDI2C_clear();
  //LCDI2C_write_String("HELLO MGTOW!");
  LCDI2C_setCursor(16,0);
  LCDI2C_write(0);
  LCDI2C_write(1);
  LCDI2C_write(2);
  LCDI2C_write(3);
  LCDI2C_setCursor(16,1);
  LCDI2C_write(4);
  LCDI2C_write(5);
  LCDI2C_write(6);
  LCDI2C_write(7);
  LCDI2C_setCursor(16,2);
  LCDI2C_write(201);
  LCDI2C_write(177);
  LCDI2C_write(162);
}

