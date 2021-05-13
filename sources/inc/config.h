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
void Delay(uint32_t ms);
void DelayMC(uint32_t mc);
void init_I2C1(void);
void I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress);
void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx);
extern uint16_t rxbuf[64];
extern int rxbuf_pos;
extern GPIO_InitTypeDef GPIOInitStruct;