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
//#define SLAVE_ADDRESS		0x08
extern volatile uint8_t Receive_Buffer[64];
extern volatile uint32_t Receive_length ;
extern volatile uint32_t length ;
uint8_t Send_Buffer[64];
uint32_t packet_sent=1;
uint32_t packet_receive=1;

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

void UART_test()
{
    GPIO_InitTypeDef GPIO_InitStructure;
       USART_InitTypeDef USART_InitStructure;

       uint16_t rxbuf[64];
       int rxbuf_pos = 0;
       int i;

       /* Enable peripheral clocks for USART1 on GPIOA */
       RCC_APB2PeriphClockCmd(
           RCC_APB2Periph_USART1 |
           RCC_APB2Periph_GPIOA |
           RCC_APB2Periph_AFIO, ENABLE);

       /* Configure PA9 and PA10 as USART1 TX/RX */

       /* PA9 = alternate function push/pull output */
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
       GPIO_Init(GPIOA, &GPIO_InitStructure);

       /* PA10 = floating input */
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
       GPIO_Init(GPIOA, &GPIO_InitStructure);

       /* Configure and initialize usart... */
       USART_InitStructure.USART_BaudRate = 115200;
       USART_InitStructure.USART_WordLength = USART_WordLength_8b;
       USART_InitStructure.USART_StopBits = USART_StopBits_1;
       USART_InitStructure.USART_Parity = USART_Parity_No;
       USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
       USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

       USART_Init(USART1, &USART_InitStructure);

       /* Enable USART1 */
       USART_Cmd(USART1, ENABLE);

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

void USB_test()
{
    Set_System();
    SetSysClockTo72();
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();

    init_leds();

    while (1)
    {
      if (bDeviceState == CONFIGURED)
      {
        CDC_Receive_DATA();
        // Check to see if we have data yet
        if (Receive_length  != 0)
        {
            // If received symbol '1' then LED turn on, else LED turn off
            if (Receive_Buffer[0]=='1')
            {
                GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            }
            else {
                GPIO_SetBits(GPIOC, GPIO_Pin_13);
            }

            // Echo
            if (packet_sent == 1) {
                CDC_Send_DATA ((uint8_t*)Receive_Buffer,Receive_length);
            }

            Receive_length = 0;
        }
      }
    }
}

void SD_Card_test(void)
{

}




