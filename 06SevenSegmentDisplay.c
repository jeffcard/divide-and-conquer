#include <avr/io.h>

// Function declarations
void initialize(void);
unsigned char read_switches(void);
void write_leds(unsigned char x);
unsigned char switch2led(unsigned char x, unsigned char *p);
unsigned char decode_switches(unsigned char x);

int main(void)
{
		unsigned char x,y,z;

		//initialize ports
		initialize();

		while(1)
		{
				//Read switches and save to x
				x= read_switches();

				//Convert switch pattern to LED pattern
				y = switch2led(x, &z);

				//Write x to the LEDs
				write_leds(y);

				//z = decode_switches(x);
				PORTA = z;
		}
		return 0;
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

// Read from port D (switch port)
unsigned char read_switches(void)
{
		unsigned char x;

		//save input register value to x
		x = PIND;

		return x;
}

void write_leds(unsigned char x)
{
		PORTB = x;
}

unsigned char switch2led(unsigned char x, unsigned char *p)
{
		unsigned char val,dsp;

		val = 0xFF;
		switch(x)
		{
				case 0xFE:
					val = 0xFE;
					dsp = 0xFC;
					break;
				case 0xFD:
					val = 0xFC;
					dsp = 0xC0;
					break;
				case 0xFB:
					val = 0xF8;
					dsp = 0x9E;
					break;
				case 0xF7:
					val = 0xF0;
					dsp = 0xCE;
					break;
				case 0xEF:
					val = 0xE0;
					dsp = 0xE2;
					break;
				case 0xDF:
					val = 0xC0;
					dsp = 0x6E;
					break;
				case 0xBF:
					val = 0x80;
					dsp = 0x7E;
					break;
				case 0x7F:
					val = 0x00;
					dsp = 0xC8;
					break;
				default:
					return 0xFF;
		};
		dsp = ~dsp;
		*p = dsp;
		PORTB = val;
		PORTA = dsp;

		return val;
}

unsigned char decode_switches(unsigned char x)
{
		switch(x)
		{
				case 0xFE:
					return 0xFC;
					//break;
				case 0xFD:
					return 0x60;
					break;
				case 0xFB:
					return 0xDA;
					break;
				case 0xF7:
					return 0xF2;
					break;
				case 0xEF:
					return 0x66;
					break;
				case 0xDF:
					return 0xB6;
					break;
				case 0xBF:
					return 0xBE;
					break;
				case 0x7F:
					return 0xE0;
					break;
				default:
					return 0xFF;
		};
}
