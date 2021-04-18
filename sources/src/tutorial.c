#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//#define SLAVE_ADDRESS		0x08


void vT_led(void *p)
{
    // Block for 100ms.
    const portTickType xDelay = 100 / portTICK_RATE_MS;

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

void sandbox()
{
    SystemInit();
    init_leds();
    xTaskCreate(vT_timer, (const char*) "Timer Task", 128, NULL, 1, NULL);
    xTaskCreate(vT_led, (const char*) "LED Task", 128, NULL, 1, NULL);
    // Start RTOS scheduler
    vTaskStartScheduler();
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
// 	printf("ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
// 	fflush(stdout);
// 	assert(false);
}

