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
void init_usart(void);
extern uint16_t rxbuf[64];
extern int rxbuf_pos;
extern GPIO_InitTypeDef GPIOInitStruct;