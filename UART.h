void clear_RXBuffer(void) ;
extern void usart_init(void);
void USART1_IRQHandler(void);
void USARTSend(volatile const char *pucBuffer);
void SetSysClockTo72(void);
void usart_dma_init(void);
void USARTSendDMA(char *pucBuffer);
void DMA1_Channel4_IRQHandler(void);
