#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* initialize variables */
    unsigned char x = 0, key0 = 0xFF, key1 = 0xFF;

    /* Define and initialize ports */
    DDRD = 0x00;
    PORTD = 0xFF;
    DDRB = 0xFF;
    PORTB = 0xFF;

    /* Main loop for detecting switch states */
    while(1){
        key1 = PIND;

        /* 1. detect if key pressed */
        if((key1 != 0xFF) && (key0 == 0xFF))
        {
            /* 2. delay 10ms */
            _delay_ms(10);

            /* 3. read input again, and test if still pressed */
            key1 = PIND;
            if((key1 != 0xFF) && (key0 == 0xFF)) /* key is still pressed */
            {
                x++;  /* increment counter */
            }
        }
        PORTB= ~x;    /* display counter values to LEDs */
        key0 = key1;  /* update old av value */
    }

    /* 4. return value zero */
    return 0;
}
