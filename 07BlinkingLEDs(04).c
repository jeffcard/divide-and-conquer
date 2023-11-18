/*Method(d): By using delay library routines in AVR C */
#include <avr/io.h>
#include <util/delay.h>

void main(void) {
    // initialize ports
    DDRB = 0xFF; // set LED port as output
    PORTB = 0xF0; // turn left four off, turn right four on

    while(1)
    {
        // complement LEDs
        PORTB = ~PORTB;

        // delay 0.5 seconds
        _delay_ms(500);
    }

    return;
}
