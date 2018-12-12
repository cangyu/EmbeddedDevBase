#include "bsp.h"

void BSP_BLE_Init(void)
{
    /*Clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
    /*GPIO*/
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin = BLE_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(BLE_TX_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = BLE_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(BLE_RX_GPIO, &GPIO_InitStructure);
    
    /*USART*/
    USART_InitTypeDef USART_InitStructure;
    
    USART_DeInit(BLE_UART);
	USART_InitStructure.USART_BaudRate = BLE_UART_BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(BLE_UART, &USART_InitStructure);	
	USART_Cmd(BLE_UART, ENABLE);
}