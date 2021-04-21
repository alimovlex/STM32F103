//
// Created by alimovlex
//

//
//void SetSysClockTo72(void);
void SetSysClockToHSE(void);
void TIM4_IRQHandler(void);
void init_leds(void);
void init_timer(void);
void init_button(void);
extern GPIO_InitTypeDef GPIOInitStruct;