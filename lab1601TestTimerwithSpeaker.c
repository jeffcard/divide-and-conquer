// Generate 800 Hz square wave and play to speaker connected to PC5
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define SPKR 0x20 //PC5

volatile unsigned char tone;
unsigned char notes[] = {216};

int main(void)
{
	unsigned char x;

    DDRC = 0XFF; // Set Port C as output
    TCCR0 = 0x03; // Set prescaler as 64

    TCNT0 = 0xDC; // preload value = 220
    TIMSK = 0x02; // Enable T0 overflow

    DDRC = 0xFF; // Set PORTC (speaker port) as output
    TCCR0 = 0x03; // Set prescaler as 16

    MCUCR = 0x02; // Ex0 is triggered on falling edge
    GIMSK |= 0x40l; // enable INT0
    sei(); // enable global interrupt

    while(1)
    {
        x = PIND;
        if (x==0xFE) tone =pgm_read_byte(&notes[0]);
    }
    return 0;
}

// Interrupt service routing for Timer 0 overflow
ISR(TIMER0_OVF_vect)
{
    // toggle speaker port (PC5)
    PORTC ^= 0x20; // 00100000 = 0x20
    // reload the timer value
    TCNT0 = 0xDC; // preload value = 220
}
