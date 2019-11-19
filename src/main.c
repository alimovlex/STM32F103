/************************************************************************************************************
 * Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.
 * After program start green LED (STAT) will blink, when jumper LED_E is closed.
 *
 * Running Release code will set ReadOutProtection (see down) via function FLASH_ReadOutProtection_Enable().
 * Do not run Release code until you know how to set back ReadOutProtection!
 ************************************************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_flash.h"
#include "sandbox.h"
#include "FreeRTOS.h"
#include "task.h"
#include "config.h"
#include "tutorial.h"

int main(void)
{
    sandbox();
    return 0;
}



