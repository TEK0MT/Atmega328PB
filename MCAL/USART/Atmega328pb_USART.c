#include "Atmega328pb_USART.h"

static std_status Usart_BaudRate_Select(Usart_Type *usart);
static std_status Usart_DATA_Frame_Select(Usart_Type *usart);

std_status Usart_Init(Usart_Type *usart){
    std_status ret = STD_OK;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        
        if(usart->selection == USART0){
            /*Select Asunchronouse or Synchronouse*/
            USART0_MODE_SELECTION(usart->clock_mode);

            /*Define the mode Transmitter or Reciever*/
            if(usart->func == Transmitter){
                USART0_ENABLE_TX();
            }
            else if (usart->func == Reciever)
            {
                USART0_ENABLE_RX();
            }
            else{
                ret = STD_NOT_OK;
            }
            /*Stop bit selection*/
            USART0_STOP_SELECTION(usart->stop_bit);
            /*Parity bit selection*/
            USART0_PARITY_SELECTION(usart->parity);
            /*Defines the edge to run*/
            if(usart->edge == Rising_Edge_Transmit){
                USART0_RISING_EDGE_TRANSMIT();
            }
            else if((usart->edge == Falling_Edge_Transmit)){
                USART0_FALLING_EDGE_TRANSMIT();
            }
            else{
                ret = STD_NOT_OK;
            }

            
        }
        else if(usart->selection == USART1){
            /*Select Asunchronouse or Synchronouse*/
            USART1_MODE_SELECTION(usart->clock_mode);

            /*Define the mode Transmitter or Reciever*/
            if(usart->func == Transmitter){
                USART1_ENABLE_TX();
            }
            else if (usart->func == Reciever)
            {
                USART1_ENABLE_RX();
            }
            else{
                ret = STD_NOT_OK;
            }
            /*Stop bit selection*/
            USART1_STOP_SELECTION(usart->stop_bit);
            /*Parity bit selection*/
            USART1_PARITY_SELECTION(usart->parity);
            /*Defines the edge to run*/
            if(usart->edge == Rising_Edge_Transmit){
                USART1_RISING_EDGE_TRANSMIT();
            }
            else if((usart->edge == Falling_Edge_Transmit)){
                USART1_FALLING_EDGE_TRANSMIT();
            }
            else{
                ret = STD_NOT_OK;
            }
        }
        else{
            ret = STD_NOT_OK;
        }
        /*Assigning the baud rate*/
        Usart_BaudRate_Select(usart);
        /*Assigning data frame*/
        Usart_DATA_Frame_Select(usart);
    }
    return ret;
}


std_status Usart_DeInit(Usart_Type *usart){
    std_status ret = STD_OK;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->selection == USART0){
            /* Disable TX and RX */
            UCSR0B = 0x00;
            
            /* Clear baud rate */
            UBRR0H = 0x00;
            UBRR0L = 0x00;
            
            /* Reset control registers */
            UCSR0A = 0x00;
            UCSR0B = 0x00;
            UCSR0C = 0x00;
            
            /* Clear data register */
            UDR0 = 0x00;
        }
        else if(usart->selection == USART1){
             /* Disable TX and RX */
             UCSR1B = 0x00;
            
             /* Clear baud rate */
             UBRR1H = 0x00;
             UBRR1L = 0x00;
             
             /* Reset control registers */
             UCSR1A = 0x00;
             UCSR1B = 0x00;
             UCSR1C = 0x00;
             
             /* Clear data register */
             UDR1 = 0x00;
        }
        else{
            ret = STD_NOT_OK;
        }
    }
    return ret;
}
std_status Usart_Send_DataBlocking(Usart_Type *usart,uint16_t data){
    std_status ret = STD_OK;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->selection == USART0){
            if(usart->data_size == NINE_BIT)
            {
                UCSR0B |= ((data & 0x200) >> 9);
            }
            UDR0 = (uint8_t)(data);
            while(!(UCSR0A & 0x40));
        }
        else if(usart->selection == USART1){
            if(usart->data_size == NINE_BIT)
            {
                UCSR1B |= ((data & 0x200) >> 9);
            }
            UDR1 = (uint8_t)(data);
            while(!(UCSR1A & 0x40));
        }
        else{
            ret = STD_NOT_OK;
        }
        
    }
    return ret;
}
std_status Usart_Send_NonBlocking(Usart_Type *usart,uint16_t data){
    std_status ret = STD_OK;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->selection == USART0){
            if(usart->data_size == NINE_BIT)
            {
                UCSR0B |= ((data & 0x200) >> 9);
            }
            UDR0 = (uint8_t)(data);
            
        }
        else if(usart->selection == USART1){
            if(usart->data_size == NINE_BIT)
            {
                UCSR1B |= ((data & 0x200) >> 9);
            }
            UDR1 = (uint8_t)(data);
        }
        else{
            ret = STD_NOT_OK;
        }
    }
    return ret;
}
std_status Usart_Recieve_DataBlocking(Usart_Type *usart,uint16_t *data){
    std_status ret = STD_OK;
    *data = 0x00;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->selection == USART0){
            while(!(UCSR0A & 0x80));
            if(usart->data_size == NINE_BIT)
            {
                *data |= ((UCSR0B & 0x02) << 8);
            }
            *data |= UDR0;
            
        }
        else if(usart->selection == USART1){
            while(!(UCSR1A & 0x80));
            if(usart->data_size == NINE_BIT)
            {
                *data |= ((UCSR1B & 0x02) << 8);
            }
            *data |= UDR1;
        }
        else{
            ret = STD_NOT_OK;
        }
    }
    return ret;
}
std_status Usart_Recieve_NonBlocking(Usart_Type *usart,uint16_t *data){
    std_status ret = STD_OK;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->selection == USART0){
            if(usart->data_size == NINE_BIT)
            {
                *data |= ((UCSR0B & 0x02) << 8);
            }
            *data |= UDR0;
        }
        else if(usart->selection == USART1){
            if(usart->data_size == NINE_BIT)
            {
                *data |= ((UCSR1B & 0x02) << 8);
            }
            *data |= UDR1;
        }
        else{
            ret = STD_NOT_OK;
        }
    }
    return ret;
}

static std_status Usart_BaudRate_Select(Usart_Type *usart){
    std_status ret = STD_OK;
    uint16_t ubrr = 0;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->baud_mode == BAUD_RATE_NORMAL){
            ubrr = (F_CPU / (16 * usart->rate)) - 1;
        }
        else if(usart->baud_mode == BAUD_RATE_DOUBLE){
            ubrr = (F_CPU / (8 * usart->rate)) - 1;
        }
        else if((usart->clock_mode == SYNCHRONOUSE_MODE) && (usart->mode == Master)){
            ubrr = (F_CPU / (2 * usart->rate)) - 1;
        }
        else {
            ret = STD_NOT_OK;
        }
        if(usart->selection == USART0 && usart->mode != Slave){
            UBRR0H = (uint8_t)(ubrr >> 8);
            UBRR0L = (uint8_t)(ubrr);
        }
        else if(usart->selection == USART1&& usart->mode != Slave){
            UBRR1H = (uint8_t)(ubrr >> 8);
            UBRR1L = (uint8_t)(ubrr);
        }
        else{
            ret = STD_NOT_OK;
        }
    }
    return ret;
}

static std_status Usart_DATA_Frame_Select(Usart_Type *usart){
    std_status ret = STD_OK;
    if(usart == NULL){
        ret = STD_NOT_OK;
    }
    else{
        if(usart->selection == USART0){
            UCSR0C &= ~(0x06);
            UCSR0B &= ~(0x04);
            switch(usart->data_size){
                case FIVE_BIT :
                UCSR0C &= ~(0x06);
                UCSR0B &= ~(0x04);
                break;
                case SIX_BIT :
                UCSR0C |= (0x02);
                UCSR0B &= ~(0x04);
                break;
                case SEVEN_BIT :
                UCSR0C |= (0x04);
                UCSR0B &= ~(0x04);
                break;
                case EIGHT_BIT :
                UCSR0C |= (0x06);
                UCSR0B &= ~(0x04);
                break;
                case NINE_BIT :
                UCSR0C |= (0x06);
                UCSR0B |= (0x04);
                break;
                default :
                ret = STD_NOT_OK;
            }
        }
        else if(usart->selection == USART1){
            UCSR1C &= ~(0x06);
            UCSR1B &= ~(0x04);
            switch(usart->data_size){
                case FIVE_BIT :
                UCSR1C &= ~(0x06);
                UCSR1B &= ~(0x04);
                break;
                case SIX_BIT :
                UCSR1C |= (0x02);
                UCSR1B &= ~(0x04);
                break;
                case SEVEN_BIT :
                UCSR1C |= (0x04);
                UCSR1B &= ~(0x04);
                break;
                case EIGHT_BIT :
                UCSR1C |= (0x06);
                UCSR1B &= ~(0x04);
                break;
                case NINE_BIT :
                UCSR1C |= (0x06);
                UCSR1B |= (0x04);
                break;
                default :
                ret = STD_NOT_OK;
            }
        }
        else{
            ret = STD_NOT_OK;
        }
    }
    return ret;
}