/*Method(b): By executing assembly instruction (nop). */
#include <avr/io.h>

// function prototype for executing assembly instruction
void delay_ms(int duration);

int main(void) {
    // initialize ports
    DDRB = 0xFF; // set LED port as output
    PORTB = 0xF0; // turn left four off, turn right four on

    while(1)
    {
        delay_ms(500);
        PORTB = 0xF0;
		
        delay_ms(500);
        PORTB = 0x0F;
    }

    return 0;
}

void delay_ms(int duration) {
    for(int i = 0; i < duration; i++){
        for(int i = 0; i < 200; i++){
            asm("nop" ::) ;
        }
    }
}
