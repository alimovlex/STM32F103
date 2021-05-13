/*
    config.c

    This file represents the general port configuration for STM32F103C8T6 board.

    STM32F103

    Created by alimovlex.
    Copyright (c) 2020 alimovlex. All rights reserved.
*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "misc.h"
#include "config.h"
GPIO_InitTypeDef GPIOInitStruct;
USART_InitTypeDef USART_InitStructure;
I2C_InitTypeDef i2c;
uint16_t rxbuf[64];
int rxbuf_pos = 0;

void Delay(uint32_t ms)
{
    volatile uint32_t nCount;
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);

    nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
    for (; nCount!=0; nCount--);
}


void DelayMC(uint32_t mc)
{
    volatile uint32_t nCount;
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);

    nCount=(RCC_Clocks.HCLK_Frequency/10000000)*mc;
    for (; nCount!=0; nCount--);
}

void SetSysClockToHSE(void)
{
    ErrorStatus HSEStartUpStatus;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig( RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* HCLK = SYSCLK */
        RCC_HCLKConfig( RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config( RCC_HCLK_Div1);

        /* PCLK1 = HCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);

        /* Select HSE as system clock source */
        RCC_SYSCLKConfig( RCC_SYSCLKSource_HSE);

        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x04)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock configuration.
     User can add here some code to deal with this error */

        /* Go to infinite loop */
        while (1)
        {
        }
    }
}

void TIM4_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
        {

            TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
            GPIOC->ODR ^= GPIO_Pin_13;
        }
}

void init_leds()
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
 GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
 GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOC, &GPIOInitStruct);
}

void init_timer()
{
    TIM_TimeBaseInitTypeDef TIMER_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseStructInit(&TIMER_InitStructure);
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER_InitStructure.TIM_Prescaler = 8000;
    TIMER_InitStructure.TIM_Period = 500;
    TIM_TimeBaseInit(TIM4, &TIMER_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void init_button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIOInitStruct);
}

void init_usart()
{
    /* Enable peripheral clocks for USART1 on GPIOA */
    RCC_APB2PeriphClockCmd(
            RCC_APB2Periph_USART1 |
            RCC_APB2Periph_GPIOA |
            RCC_APB2Periph_AFIO, ENABLE);

    /* Configure PA9 and PA10 as USART1 TX/RX */

    /* PA9 = alternate function push/pull output */
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIOInitStruct);

    /* PA10 = floating input */
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIOInitStruct);

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
}

void init_I2C1(void)
{
    // Включаем тактирование нужных модулей
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // А вот и настройка I2C
    i2c.I2C_ClockSpeed = 100000;
    i2c.I2C_Mode = I2C_Mode_I2C;
    i2c.I2C_DutyCycle = I2C_DutyCycle_2;
    // Адрес я тут взял первый пришедший в голову
    i2c.I2C_OwnAddress1 = 0x15;
    i2c.I2C_Ack = I2C_Ack_Enable;
    i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &i2c);

    // I2C использует две ноги микроконтроллера, их тоже нужно настроить
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOInitStruct);

    // Ну и включаем, собственно, модуль I2C1
    I2C_Cmd(I2C1, ENABLE);
}

/*******************************************************************/
void I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress)
{
    // На всякий слуыай ждем, пока шина осовободится
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
    // Генерируем старт - тут все понятно )
    I2C_GenerateSTART(I2Cx, ENABLE);
    // Ждем пока взлетит нужный флаг
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
    // Посылаем адрес подчиненному  //возможно тут нужен сдвиг влево  //судя по исходникам - да, нужен сдвиг влево
    //http://microtechnics.ru/stm32-ispolzovanie-i2c/#comment-8109
    I2C_Send7bitAddress(I2Cx, slaveAddress<<1, transmissionDirection);
    // А теперь у нас два варианта развития событий - в зависимости от выбранного направления обмена данными
    if(transmissionDirection== I2C_Direction_Transmitter)
    {
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    }
    if(transmissionDirection== I2C_Direction_Receiver)
    {
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    }
}

/*******************************************************************/
void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data)
{
    // Просто вызываем готоваую функцию из SPL и ждем, пока данные улетят
    I2C_SendData(I2Cx, data);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}



/*******************************************************************/
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx)
{
    uint8_t data;
    // Тут картина похожа, как только данные пришли быстренько считываем их и возвращаем
    while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );

    data = I2C_ReceiveData(I2Cx);
    return data;
}
