/*
 * gpio.h
 *
 * Created: 3/3/2025 2:09:25 PM
 *  Author: Mohamed Tarek
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#include "../CORE/CORE.h"



#define PORTB_MAX		7
#define PORTC_MAX		6
#define PORTD_MAX		4
#define PORTE_MAX		3

#define PINx_BASE		((volatile uint8_t *)0x23)
#define DDRx_BASE		((volatile uint8_t *)0x24)
#define PORTx_BASE		((volatile uint8_t *)0x25)


typedef enum{
	PIN_INPUT = 0,
	PIN_OUTPUT
}PIN_DIRECTION_T;

typedef enum{
	LOGIC_LOW = 0,
	LOGIC_HIGH
}PIN_LOGIC_T;

typedef enum{
	PORTB_t = 0,
	PORTC_t,
	PORTD_t,
	PORTE_t
}PORT_T;
typedef enum{
	PIN0_t = 0,
	PIN1_t,
	PIN2_t,
	PIN3_t,
	PIN4_t,
	PIN5_t,
	PIN6_t,
	PIN7_t
}PIN_T;


typedef struct{
	PIN_T			Pin					:3;
	PORT_T			port				:2;
	PIN_LOGIC_T     logic				:1;
	PIN_DIRECTION_T direc				:1;
}pin_config_t;

std_status GPIO_PIN_DIRECTION(pin_config_t *pin_t,PIN_DIRECTION_T direction);
std_status GPIO_PIN_WRITE_LOGIC(pin_config_t *pin_t,PIN_LOGIC_T logic);
std_status GPIO_PIN_TOGGLE_LOGIC(pin_config_t *pin_t);
std_status GPIO_PIN_GET_LOGIC(pin_config_t *pin_t,PIN_LOGIC_T *logic);
std_status GPIO_PIN_INIT(pin_config_t *pin_t);

std_status GPIO_PORT_DIRECTION(PORT_T port,uint8_t direction);
std_status GPIO_PORT_LOGIC(PORT_T port,uint8_t logic);

#endif /* GPIO_H_ */
