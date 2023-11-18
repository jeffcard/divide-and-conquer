// Generate 800 Hz square wave and play to speaker connected to PC5
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define SPKR 0x20 //PC5

volatile unsigned char tone;
unsigned char notes[] PROGMEM = {-110,-90,-87,-82,-73,-65,-58,-55};
unsigned char x;

int main(void)
{
	DDRD = 0x00; // Set switch port
    PORTD = 0xFF; // Initialize PORTD

    DDRC = 0XFF; // Set Port C as output
    TCCR0 = 0x03; // Set prescaler as 64

    TCNT0 = 0xDC; // preload value = 220
    TIMSK = 0x02; // Enable T0 overflow

    DDRC = 0xFF; // Set PORTC (speaker port) as output
    TCCR0 = 0x03; // Set prescaler as 16

    MCUCR = 0x02; // Ex0 is triggered on falling edge
    GIMSK |= 0x40l; // enable INT0
    sei(); // enable global interrupt

    while(1) {
        x = PIND;
        if (x==0xFE) tone =pgm_read_byte(&notes[0]);
        if (x==0xFD) tone =pgm_read_byte(&notes[1]);
        if (x==0xFB) tone =pgm_read_byte(&notes[2]);
        if (x==0xF7) tone =pgm_read_byte(&notes[3]);
        if (x==0xEF) tone =pgm_read_byte(&notes[4]);
        if (x==0xDF) tone =pgm_read_byte(&notes[5]);
        if (x==0xBF) tone =pgm_read_byte(&notes[6]);
        if (x==0x7F) tone =pgm_read_byte(&notes[7]);
    }

    return 0;
}

// Interrupt service routing for Timer 0 overflow
ISR(TIMER0_OVF_vect)
{
    if (x!=0xFF) PORTC ^= SPKR; // toggle speaker
    else PORTC &= 0xFF; // turn off
    // reload the timer value
    TCNT0 = tone; // preload value = 220
}
