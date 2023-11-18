/*Method(c): By using delay_basic library routines in AVR C */
#include <avr/io.h>
#include <util/delay_basic.h>

// function prototype for executing assembly instruction
void delay_ms(int duration);

void main(void) {
    // initialize ports
    DDRB = 0xFF; // set LED port as output
    PORTB = 0xF0; // turn left four off, turn right four on

    while(1)
    {
        // complement LEDs
        PORTB = ~PORTB;
        delay_ms(500);
    }

    return;
}

void delay_ms(int duration) {
    for(int i = 0; i < duration; i++){
        _delay_loop_2(500);
    }
}
