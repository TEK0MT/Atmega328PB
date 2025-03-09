/*
 * GccApplication1.c
 *
 * Created: 3/3/2025 1:56:42 PM
 * Author : Mohamed Tarek
 */ 
#include "MCAL/GPIO/gpio.h"
#include "MCAL/USART/Atmega328pb_USART.h"	


pin_config_t pin1 = {.port = PORTB_t,.Pin = PIN0_t,.direc = PIN_INPUT,.logic = LOGIC_LOW};
pin_config_t pin2 = {.port = PORTB_t,.Pin = PIN1_t,.direc = PIN_OUTPUT,.logic = LOGIC_LOW};
PIN_LOGIC_T logic = LOGIC_LOW;
int main(void)
{
    /* Replace with your application code */
	GPIO_PIN_INIT(&pin1);
	GPIO_PIN_INIT(&pin2);
	
    while (1) 
    {
		GPIO_PIN_GET_LOGIC(&pin1,&logic);
		if(logic == LOGIC_HIGH){
		GPIO_PIN_WRITE_LOGIC(&pin2,LOGIC_HIGH);
		}
		else{
		GPIO_PIN_WRITE_LOGIC(&pin2,LOGIC_LOW);
		}
    }
}

