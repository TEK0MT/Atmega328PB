#ifndef ATMEGA328PB_USART_H
#define ATMEGA328PB_USART_H
#include "../GPIO/gpio.h"

#define UCSR0A                  (*(volatile uint8_t *)(0xC0))
#define UCSR0B                  (*(volatile uint8_t *)(0xC1))
#define UCSR0C                  (*(volatile uint8_t *)(0xC2))
#define UDR0                    (*(volatile uint8_t *)(0xC6))

#define UCSR1A                  (*(volatile uint8_t *)(0xC8))
#define UCSR1B                  (*(volatile uint8_t *)(0xC9))
#define UCSR1C                  (*(volatile uint8_t *)(0xCA))
#define UDR1                    (*(volatile uint8_t *)(0xCE))


#define ASYNCHRONOUSE_MODE      0x00
#define SYNCHRONOUSE_MODE       0x01

#define USART_DISABLED_PARITY   0x00
#define USART_EVEN_PARITY       0x02
#define USART_ODD_PARITY        0x03

#define USART_STOP_ONE_BIT      0x00
#define USART_STOP_TWO_BIT      0x01


#define USART0_ENABLE_TX()                   (SET_BIT(UCSR0B,3))
#define USART0_ENABLE_RX()                   (SET_BIT(UCSR0B,4))
#define USART0_MODE_SELECTION(MODE)          (UCSR0C |= MODE)
#define USART0_PARITY_SELECTION(MODE)        (UCSR0C |= (MODE << 4))
#define USART0_STOP_SELECTION(MODE)          (UCSR0C |= (MODE << 3))



#define USART1_ENABLE_TX()                   (SET_BIT(UCSR1B,3))
#define USART1_ENABLE_RX()                   (SET_BIT(UCSR1B,4))
#define USART1_MODE_SELECTION(MODE)          (UCSR1C |= MODE)
#define USART1_PARITY_SELECTION(MODE)        (UCSR1C |= (MODE << 4))
#define USART1_STOP_SELECTION(MODE)          (UCSR1C |= (MODE << 3))

typedef enum{
    FIVE_BIT,
    SIX_BIT,
    SEVEN_BIT,
    EIGHT_BIT,
    NINE_BIT 
}Usart_data_Size;

typedef enum{
    Rising_Edge,
    Falling_Edge
}Usart_edge;
typedef enum{
    USART0,
    USART1
}Usart_selection;

typedef enum{
    Master,
    Slave
}Usart_mode;

typedef struct{
    Usart_data_Size data_size       :3;
    Usart_edge edge                 :1;
    uint8_t clock_mode              :1;
    Usart_mode mode                 :1;
    Usart_selection selection       :1;
    uint8_t stop_bit                :1;
    uint8_t parity                  :2;
}Usart_Type;

std_status Usart_Init(Usart_Type usart);
std_status Usart_DeInit(Usart_Type usart);
std_status Usart_Send_DataBlocking(Usart_Type usart);
std_status Usart_Send_NonBlocking(Usart_Type usart);
std_status Usart_Recieve_DataBlocking(Usart_Type usart);
std_status Usart_Recieve_NonBlocking(Usart_Type usart);

#endif /* ATMEGA328PB_USART_H */