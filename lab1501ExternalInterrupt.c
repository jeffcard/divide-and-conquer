// LED blinking with interrupt control
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

volatile unsigned char iLED=0;
unsigned char LEDtb1[] PROGMEM = {0x00, 0xF0, 0x33, 0x55, 0x03, 0x30, 0x01, 0x80};

int main(void)
{
    DDRB = 0xFF; // set LED port as output
    PORTB = 0xFF; // turn off all LEDs

    DDRC = 0xFF; // Set PORTC (speaker port) as output
    TCCR0 = 0x03; // Set prescaler as 16

    MCUCR = 0x02; // Ex0 is triggered on falling edge
    GIMSK |= 0x40l; // enable INT0
    sei(); // enable global interrupt

    while(1)
    {
        _delay_ms(500);
        PORTB = ~PORTB;
        PORTC = ~PORTC;
    }

    return 0;
}

ISR(INT0_vect)
{
    iLED++; if(iLED>7) iLED =0;
    PORTB = pgm_read_byte(&LEDtb1[iLED]);
}
