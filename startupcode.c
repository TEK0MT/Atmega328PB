#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>  
#include <stdint.h>  

extern volatile  uint8_t _sbss , _ebss , _sdata, _edata,_sidata;

void reset_handler(void);
void default_handler(void);
void main(void);


void INT0_ISR(void)              __attribute__((weak, alias("default_handler")));
void INT1_ISR(void)              __attribute__((weak, alias("default_handler")));
void PCINT0_ISR(void)            __attribute__((weak, alias("default_handler")));
void PCINT1_ISR(void)            __attribute__((weak, alias("default_handler")));
void PCINT2_ISR(void)            __attribute__((weak, alias("default_handler")));
void PCINT3_ISR(void)            __attribute__((weak, alias("default_handler"))); 
void WDT_ISR(void)               __attribute__((weak, alias("default_handler")));
void TIMER2_COMPA_ISR(void)      __attribute__((weak, alias("default_handler")));
void TIMER2_COMPB_ISR(void)      __attribute__((weak, alias("default_handler")));
void TIMER2_OVF_ISR(void)        __attribute__((weak, alias("default_handler")));
void TIMER1_CAPT_ISR(void)       __attribute__((weak, alias("default_handler")));
void TIMER1_COMPA_ISR(void)      __attribute__((weak, alias("default_handler")));
void TIMER1_COMPB_ISR(void)      __attribute__((weak, alias("default_handler")));
void TIMER1_OVF_ISR(void)        __attribute__((weak, alias("default_handler")));
void TIMER0_COMPA_ISR(void)      __attribute__((weak, alias("default_handler")));
void TIMER0_COMPB_ISR(void)      __attribute__((weak, alias("default_handler")));
void TIMER0_OVF_ISR(void)        __attribute__((weak, alias("default_handler")));
void SPI_STC_ISR(void)           __attribute__((weak, alias("default_handler")));
void USART0_RX_ISR(void)         __attribute__((weak, alias("default_handler")));
void USART0_UDRE_ISR(void)       __attribute__((weak, alias("default_handler")));
void USART0_TX_ISR(void)         __attribute__((weak, alias("default_handler")));
void USART1_RX_ISR(void)         __attribute__((weak, alias("default_handler"))); 
void USART1_UDRE_ISR(void)       __attribute__((weak, alias("default_handler"))); 
void USART1_TX_ISR(void)         __attribute__((weak, alias("default_handler"))); 
void ADC_ISR(void)               __attribute__((weak, alias("default_handler")));
void EE_READY_ISR(void)          __attribute__((weak, alias("default_handler")));
void ANALOG_COMP_ISR(void)       __attribute__((weak, alias("default_handler")));
void TWI_ISR(void)               __attribute__((weak, alias("default_handler")));
void SPM_READY_ISR(void)         __attribute__((weak, alias("default_handler")));
void TIMER3_CAPT_ISR(void)       __attribute__((weak, alias("default_handler"))); 
void TIMER3_COMPA_ISR(void)      __attribute__((weak, alias("default_handler"))); 
void TIMER3_COMPB_ISR(void)      __attribute__((weak, alias("default_handler"))); 
void TIMER3_OVF_ISR(void)        __attribute__((weak, alias("default_handler"))); 




void (*const Vector_Table[])(void) __attribute__((section(".vectors"))) = {
    reset_handler,   // Reset vector (0x0000)
    INT0_ISR,        // External Interrupt Request 0
    INT1_ISR,        // External Interrupt Request 1
    PCINT0_ISR,      // Pin Change Interrupt Request 0
    PCINT1_ISR,      // Pin Change Interrupt Request 1
    PCINT2_ISR,      // Pin Change Interrupt Request 2
    PCINT3_ISR,      // Pin Change Interrupt Request 3 (ATmega328PB only)
    WDT_ISR,         // Watchdog Timer Interrupt
    TIMER2_COMPA_ISR,// Timer/Counter2 Compare Match A
    TIMER2_COMPB_ISR,// Timer/Counter2 Compare Match B
    TIMER2_OVF_ISR,  // Timer/Counter2 Overflow
    TIMER1_CAPT_ISR, // Timer/Counter1 Capture Event
    TIMER1_COMPA_ISR,// Timer/Counter1 Compare Match A
    TIMER1_COMPB_ISR,// Timer/Counter1 Compare Match B
    TIMER1_OVF_ISR,  // Timer/Counter1 Overflow
    TIMER0_COMPA_ISR,// Timer/Counter0 Compare Match A
    TIMER0_COMPB_ISR,// Timer/Counter0 Compare Match B
    TIMER0_OVF_ISR,  // Timer/Counter0 Overflow
    SPI_STC_ISR,     // SPI Serial Transfer Complete
    USART0_RX_ISR,   // USART0 Receive Complete
    USART0_UDRE_ISR, // USART0 Data Register Empty
    USART0_TX_ISR,   // USART0 Transmit Complete
    USART1_RX_ISR,   // USART1 Receive Complete (ATmega328PB only)
    USART1_UDRE_ISR, // USART1 Data Register Empty (ATmega328PB only)
    USART1_TX_ISR,   // USART1 Transmit Complete (ATmega328PB only)
    ADC_ISR,         // ADC Conversion Complete
    EE_READY_ISR,    // EEPROM Ready
    ANALOG_COMP_ISR, // Analog Comparator
    TWI_ISR,         // 2-Wire Serial Interface - I2C
    SPM_READY_ISR,   // Store Program Memory Ready
    TIMER3_CAPT_ISR, // Timer/Counter3 Capture Event (ATmega328PB only)
    TIMER3_COMPA_ISR,// Timer/Counter3 Compare Match A (ATmega328PB only)
    TIMER3_COMPB_ISR,// Timer/Counter3 Compare Match B (ATmega328PB only)
    TIMER3_OVF_ISR   // Timer/Counter3 Overflow (ATmega328PB only)
};

void reset_handler(void)
{
    volatile uint8_t *MemStart = &_sbss;
    volatile uint8_t *MemEnd   = &_ebss;
    volatile uint8_t *src      = &_sidata;
    size_t size = MemEnd - MemStart;
    uint8_t counter = 0;
    for(counter = 0;counter < size;counter++)
    {
        *MemStart++ = 0;
    }
    MemStart = &_sdata;
    MemEnd   = &_edata;  
    size = MemEnd - MemStart;
    for(counter = 0;counter < size;counter++)
    {
        *MemStart++ = *src++;
    }

    main();

    while(1);

}

void default_handler(void)
{
    while(1);
}