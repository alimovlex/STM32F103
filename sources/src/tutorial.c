/*
    tutorial.c

    This file represents the tutorials for STM32F103C8T6 board.

    STM32F103

    Created by alimovlex.
    Copyright (c) 2020 alimovlex. All rights reserved.
*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "LiquidCrystal_I2C.h"
#include "lcd_i2c.h"
//#define SLAVE_ADDRESS		0x08


void vT_led(void *p)
{
    // Block for 100ms.
    const portTickType xDelay = 100 / portTICK_RATE_MS;
    init_leds();
    for(;;)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        vTaskDelay(xDelay);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        vTaskDelay(xDelay);
    }
}

void vT_timer(void *p)
{

    SetSysClockToHSE();
    init_leds();
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    init_timer();
    for(;;)
    {

    }
}

void vT_usart(void *p)
{
    init_usart();
    int i;
    for(;;)
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

void vT_lcd(void *p)
{
    int i;
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
    LCDI2C_write_String("HELLO MGTOW!");
}



void sandbox()
{
    SystemInit();
    xTaskCreate(vT_timer, (const char*) "Timer Task", 128, NULL, 1, NULL);
    xTaskCreate(vT_led, (const char*) "LED Task", 128, NULL, 1, NULL);
    xTaskCreate(vT_usart, (const char*) "USART Task", 128, NULL, 1, NULL);
    xTaskCreate(vT_lcd, (const char*) "LCD Task", 128, NULL, 1, NULL);
    // Start RTOS scheduler
    vTaskStartScheduler();
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
// 	printf("ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
// 	fflush(stdout);
// 	assert(false);
}

