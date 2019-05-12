#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#define BUF_SIZE	29

char source[BUF_SIZE] = "Message from\nMemory using DMA";
char destination[BUF_SIZE];
		
void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		// Display received data to the LCD
		//lcd16x2_clrscr();
		//lcd16x2_puts(destination);

		// Clear DMA1 Channel1 half transfer, transfer complete and 
		// global interrupt pending bits
		DMA_ClearITPendingBit(DMA1_IT_GL1);
	}
}

void DMA1_Init(void)
{
	// Initialization struct
	DMA_InitTypeDef DMA_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Step 1: Initialize DMA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = BUF_SIZE;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) source;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) destination;
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	// Enable DMA1 transfer complete interrupt
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	
	// Step 2: Initialize NVIC
	// Set NVIC prority group to group 4 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	// Set System Timer IRQ at higher priority
	NVIC_SetPriority(SysTick_IRQn, 0);
	// Set DMA1 channel 1 IRQ at lower priority
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

