/*
 * gpio.c
 *
 * Created: 3/3/2025 4:36:08 PM
 *  Author: Mohamed Tarek
 */ 
#include "gpio.h"

std_status GPIO_PIN_DIRECTION(pin_config_t *pin_t,PIN_DIRECTION_T direction){
	std_status ret = STD_OK;
	if((pin_t->port == PORTB_t && pin_t->Pin > PORTB_MAX) || (pin_t->port == PORTC_t && pin_t->Pin > PORTC_MAX) || (pin_t->port == PORTD_t && pin_t->Pin > PORTD_MAX) || (pin_t->port == PORTE_t && pin_t->Pin > PORTE_MAX) ){
		ret = STD_NOT_OK;
	}
	else{
		if(direction == PIN_OUTPUT){
		SET_BIT(DDRx_BASE + pin_t->port * 3,pin_t->Pin);
		}
		else{
			CLEAR_BIT(DDRx_BASE + pin_t->port * 3,pin_t->Pin);
		}
	}
	return ret;
}
std_status GPIO_PIN_WRITE_LOGIC(pin_config_t *pin_t,PIN_LOGIC_T logic){
	std_status ret = STD_OK;
	if((pin_t->port == PORTB_t && pin_t->Pin > PORTB_MAX) || (pin_t->port == PORTC_t && pin_t->Pin > PORTC_MAX) || (pin_t->port == PORTD_t && pin_t->Pin > PORTD_MAX) || (pin_t->port == PORTE_t && pin_t->Pin > PORTE_MAX) ){
		ret = STD_NOT_OK;
	}
	else{
		if(logic == LOGIC_HIGH){
			SET_BIT(PORTx_BASE + pin_t->port * 3,pin_t->Pin);
		}
		else{
			CLEAR_BIT(PORTx_BASE + pin_t->port * 3,pin_t->Pin);
		}
	}
	return ret;
}
std_status GPIO_PIN_TOGGLE_LOGIC(pin_config_t *pin_t){
	std_status ret = STD_OK;
	if((pin_t->port == PORTB_t && pin_t->Pin > PORTB_MAX) || (pin_t->port == PORTC_t && pin_t->Pin > PORTC_MAX) || (pin_t->port == PORTD_t && pin_t->Pin > PORTD_MAX) || (pin_t->port == PORTE_t && pin_t->Pin > PORTE_MAX) ){
		ret = STD_NOT_OK;
	}
	else{
		SET_BIT(PINx_BASE + pin_t->port * 3,pin_t->Pin);
	}
	return ret;
}

std_status GPIO_PIN_GET_LOGIC(pin_config_t *pin_t,PIN_LOGIC_T *logic){
	std_status ret = STD_OK;
	if((pin_t->port == PORTB_t && pin_t->Pin > PORTB_MAX) || (pin_t->port == PORTC_t && pin_t->Pin > PORTC_MAX) || (pin_t->port == PORTD_t && pin_t->Pin > PORTD_MAX) || (pin_t->port == PORTE_t && pin_t->Pin > PORTE_MAX) ){
		ret = STD_NOT_OK;
	}
	else{
		 *logic = READ_BIT((PINx_BASE + pin_t->port * 3), pin_t->Pin);
	}
	return ret;
}
std_status GPIO_PIN_INIT(pin_config_t *pin_t){
	std_status ret = STD_OK;
	if((pin_t->port == PORTB_t && pin_t->Pin > PORTB_MAX) || (pin_t->port == PORTC_t && pin_t->Pin > PORTC_MAX) || (pin_t->port == PORTD_t && pin_t->Pin > PORTD_MAX) || (pin_t->port == PORTE_t && pin_t->Pin > PORTE_MAX) ){
		ret = STD_NOT_OK;
	}
	else{
		GPIO_PIN_DIRECTION(pin_t , pin_t->direc);
		GPIO_PIN_WRITE_LOGIC(pin_t,pin_t->logic);
	}
	return ret;
}

std_status GPIO_PORT_DIRECTION(PORT_T port,uint8_t direction){
	*(DDRx_BASE + port * 3) = direction;
}
std_status GPIO_PORT_LOGIC(PORT_T port,uint8_t logic){
	*(PORTx_BASE + port * 3) = logic;
}