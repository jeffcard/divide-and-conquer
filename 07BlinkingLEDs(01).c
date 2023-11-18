/*Method(a): By executing useless but harmless C instructions.*/
#include <avr/io.h>
#include <util/delay.h>

// Function declarations
void initialize(void);

int main(void)
{
	unsigned char x[10];
    unsigned long i;

	//initialize ports
	initialize();
	PORTB = 0xF0;

	while(1)
    {
        // complement LEDs
        PORTB = ~PORTB;

        // delay 0.5 seconds
        for (i = 0; i < 30000; i++)
        {
            x[i%10] = (unsigned char)i;
						if(i == 16) i++;
        }
    }
}

// Init Ports
void initialize(void)
{
	//initialize input port (PORT D)
	DDRD = 0x00;
	PORTD = 0xFF;

	//Init output port (PORT B)
	DDRB = 0xFF;
	PORTB = 0xFF;

	//Init output port (PORT A)
	DDRA = 0xFF;
	//PORTA = 0xFF;
}
