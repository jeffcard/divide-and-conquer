#include <avr/io.h>
#include <util/delay.h>

//display the number of 2 on the two seven-segment screens
int main(){
    unsigned char p = 0xFD;
    unsigned char q = 0x9E;

    DDRA = 0xFF;
	  DDRC = 0xFF;

	q = ~q;

    while(1){
          PORTA = p;
          PORTC = q;
          _delay_ms(10);

          PORTA = 0xFF;
          PORTC = 0xFF;
          _delay_ms(10);

          PORTA = q;
          PORTC = q;
          _delay_ms(10);

          PORTA = 0xFF;
          PORTC = 0xFF;
          _delay_ms(10);
    }

    return 0;
}
