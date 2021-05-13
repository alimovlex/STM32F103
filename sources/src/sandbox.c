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

void SD_Card_test(void)
{

}




