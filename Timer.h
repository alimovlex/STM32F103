#include "stdint.h"
void delay_ms(uint32_t n_msec);
void TIM2_init(void);
void TIM2_IRQHandler(void);
void delay_us(uint32_t n_usec);
void TIM4_init(void);
void TIM4_IRQHandler(void);
