/*
    sandbox.c

    This file represents the testing functions for STM32F103C8T6 board.

    STM32F103

    Created by alimovlex.
    Copyright (c) 2020 alimovlex. All rights reserved.
*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "config.h"
#include "misc.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LiquidCrystal_I2C.h"
#include "lcd_i2c.h"
#include <string.h>
//#define SLAVE_ADDRESS		0x08

void LED_test()
{
    int i;
    init_leds();
    while (1) {


        /* Toggle LED which connected to PC13*/
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")

        /* delay */
        for(i=0;i<0x100000;i++);

        /* Toggle LED which connected to PC13*/
        GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set C13 to High level ("1")

        /* delay */
        for(i=0;i<0x100000;i++);
    }


}

void timer_test()
{
        SetSysClockToHSE();
        init_leds();
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        init_timer();
        while(1)
        {

        }
}

void button_test(void)
{
    init_button();
    init_leds();

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

void usart_test(void) {
    int i;
    init_usart();

    while (1)
    {
        /* Wait until there's data in the receive data register */
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

        /* Read a byte */
        rxbuf[rxbuf_pos++] = USART_ReceiveData(USART1);

        /* Check if the previous byte was a newline */
        if ((rxbuf[rxbuf_pos-1] == '\n' || rxbuf[rxbuf_pos-1] == '\r') && rxbuf_pos != 0) {

            /* Send the line back */
            for (i = 0; i < rxbuf_pos; i++) {
                USART_SendData(USART1, rxbuf[i]);

                /* Wait until the byte has been transmitted */
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }

            rxbuf_pos = 0;
        }
    }
}

void lcd_test(void)
{
    int i;
/*  while(1)
  {
    if((USART1->SR & USART_SR_RXNE)) //????????? ??????????? ?????? ?? ??????????
    {
      data = USART1->DR; //????????? ???????? ??????
    //  Usart1_Send_symbol(data); //? ??? ?? ???????? ?? ???????
      break;
    }
  }*/
    Delay(3000);
//  Usart1_Send_String("Start");

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
//  Usart1_Send_String("End");
    Delay(2000);
    LCDI2C_clear();

    displayKeyCodes();

    Delay(2000);
/*
  LCDI2C_createChar(0, bell);
//  Usart1_Send_String("char1");
  LCDI2C_createChar(1, note);
  LCDI2C_createChar(2, clock);
  LCDI2C_createChar(3, heart);
  LCDI2C_createChar(4, duck);
  LCDI2C_createChar(5, check);
  LCDI2C_createChar(6, cross);
  LCDI2C_createChar(7, retarrow);
  LCDI2C_clear();
//  Usart1_Send_String("endchar");

//    int i;
  for (i=0; i<8; i++) {
        LCDI2C_write(i);
  }

  Delay(3000);*/
    LCDI2C_createChar(0, habr1);
    LCDI2C_createChar(1, habr2);
    LCDI2C_createChar(2, habr3);
    LCDI2C_createChar(3, habr4);
    LCDI2C_createChar(4, habr5);
    LCDI2C_createChar(5, habr6);
    LCDI2C_createChar(6, habr7);
    LCDI2C_createChar(7, habr8);

    LCDI2C_clear();
    LCDI2C_write_String("HELLO MGTOW!");
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

void SD_Card_test(void)
{

}




