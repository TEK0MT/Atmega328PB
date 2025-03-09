/*
 * GccApplication1.c
 *
 * Created: 3/3/2025 1:56:42 PM
 * Author : Mohamed Tarek
 */ 
#include "MCAL/GPIO/gpio.h"
#include "MCAL/USART/Atmega328pb_USART.h"	


Usart_Type usart = {.data_size = EIGHT_BIT,.edge = Falling_Edge_Transmit,.clock_mode = ASYNCHRONOUSE_MODE,.mode = Master,.func = Transmitter,.selection = USART0,.baud_mode = BAUD_RATE_NORMAL,.rate = BAUD_9600,.stop_bit = USART_STOP_ONE_BIT,.parity = USART_ODD_PARITY};

int main(void)
{
    /* Replace with your application code */
	Usart_Init(&usart);
	int i = 0;
    while (1) 
    {
		i = 0;
		Usart_Send_DataBlocking(&usart,'H');
		while(i++ < 100000);
    }
}

