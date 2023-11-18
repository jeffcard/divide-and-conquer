#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned char sw_decode(unsigned char);
unsigned char bcd2sseg(unsigned char);
unsigned char ssegtbl[] PROGMEM = {0xFC, 0xC0, 0x9E, 0xCE, 0xE2, 0x6E, 0x7E, 0xC8, 0xFE, 0xEE};

int main(void){
    // temporary switch values
    unsigned char key0 = 0xFF, key1 = 0xFF;

    // variables for bcd digits
    unsigned char dig0 = 0, dig1 = 0;

    // initialize ports
    DDRD = 0x00;
    PORTD = 0xFF;
    DDRB = 0xFF;
    PORTB = 0xFF;

    // lower digit display
    DDRA = 0xFF;
    // upper digit display
    DDRC = 0xFF;

    while(1){
        //read switches
		key1 = PIND;

        if((key1 != 0xFF) && (key0 == 0xFF)){
            _delay_ms(10);
            key1 = PIND;

            if((key1 != 0xFF) && (key0 == 0xFF)){
                // dig0 -> dig1
                dig1 = dig0;
                // decode switch, write to dig0
                dig0 = sw_decode(key1);
            }
        }
        key0 = key1;

        // decode dig0/1 to seven segment and display
        PORTA = bcd2sseg(dig0);
        _delay_ms(10);
        PORTA = 0xFF;

        PORTC = bcd2sseg(dig1);
        _delay_ms(10);
        PORTC = 0xFF;
    }
    return 0;
}

// decoding switch value to BCD
unsigned char sw_decode(unsigned char key)
{
    unsigned char x;
    switch(key){
        case 0xFE:
            x=1;
            break;
        case 0xFD:
            x=2;
            break;
        case 0xFB:
            x=3;
            break;
        case 0xF7:
            x=4;
            break;
        case 0xEF:
            x=5;
            break;
        case 0xDF:
            x=6;
            break;
        case 0xBF:
            x=7;
            break;
        case 0x7F:
            x=8;
            break;
        default:
            x=0;
    }
    return x;
}

unsigned char bcd2sseg(unsigned char x)
{
    return ~pgm_read_byte(&ssegtbl[x&0x0F]);
}

