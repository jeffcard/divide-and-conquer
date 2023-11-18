#include <avr/io.h>

int main(void)
{
    /* initialize variables */
    unsigned​ ​char​ x = ​0​, key0 = ​0xFF​, key1 = ​0xFF​;

    /* Define and initialize ports */
    DDRD = ​0x00​;
    PORTD = ​0xFF​;
    DDRB = ​0xFF​;
    PORTB = ​0xFF​;

    /* Main loop for detecting switch states */
    ​while​(​1​){
        key1 = PIND;
        ​if​((key1 != ​0xFF​) && (key0 == ​0xFF​)) ​/* key pressed */
        {
            x++;              /* increment counter */
            PORTB = ~x;       /* display counter value to LEDs */
        }
        key0 = key1;      /* update old av value */
    }

    ​return​ ​0​;
}
