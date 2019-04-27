void clear_RXBuffer(void);
void usart_init(void);
void USART1_IRQHandler(void);
void USARTSend(volatile const char *pucBuffer);
void SetSysClockTo72(void);
