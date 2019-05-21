/* 
 * File:   Controller.c
 * Author: TySto
 *
 * Created on May 13, 2019, 9:57 PM
 */

#include <xc.h>
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
 


#define S1_TX PD5
#define S1_RX PD4
#define S2_TX PD7
#define S2_RX PD6
#define S3_TX PB1
#define S3_RX PB0
#define S4_TX PB3
#define S4_RX PB2

#define SOL PB4

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char String[]="2550x002550x00255";

/*
 * 
 */
int main(void) {
    USART_init();
    DDRB = _BV(SOL);
    
    while (1) {
        USART_putstring(String);
        _delay_ms(500);
        
        
        
        /*
         *  TESTING OF SOLENOID
         */
//        PORTB = _BV(SOL);
//        _delay_ms(400);
//        PORTB &= ~_BV(SOL);
//        _delay_ms(400);
    }
    
    
    return (0);
}

void USART_init(void){
 
 UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
 UBRR0L = (uint8_t)(BAUD_PRESCALLER);
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C = (3<<UCSZ00);
}
 
unsigned char USART_receive(void){
 
 while(!(UCSR0A & (1<<RXC0)));
 return UDR0;
 
}
 
void USART_send( unsigned char data){
 
 while(!(UCSR0A & (1<<UDRE0)));
 UDR0 = data;
 
}
 
void USART_putstring(char* StringPtr){
 
while(*StringPtr != 0x00){
 USART_send(*StringPtr);
 StringPtr++;}
 
}

