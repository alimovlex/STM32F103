/*
    main.c
    STM32F103

    Created by alimovlex.
    Copyright (c) 2020 alimovlex. All rights reserved.
*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "sandbox.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tutorial.h"
int main(void)
{
    sandbox();
    //timer_test();
    //button();
    //LED_test();
    //usart_test();
    //lcd_test();
}


