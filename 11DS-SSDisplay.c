#include <avr/io.h>
#include <util/delay.h>

// Function declarations
void initialize(void);
unsigned char read_switches(void);
void write_leds(unsigned char x);
void write_upper_ssd(unsigned char n);
void write_lower_ssd(unsigned char n);
//unsigned char interpret_switches(unsigned char x, unsigned char *p, unsigned char *num);
unsigned char decode_switches(unsigned char x);

// decode BCD values to seven-segment display pattern
unsigned char BCD2SSEG(unsigned char);

int main(void)
{
		unsigned char b_cnt;
		unsigned char sec1,sec10,sseg1,sseg10;
		unsigned char key0=0xFF, key1=0xFF;

		b_cnt = 0;
	  	sec1 = 0;
		sec10 = 0;

		//initialize ports
		initialize();

		while(1)
		{
			//Read switches and save to x
			key1 = PIND;
			
          	// Test if pressed
          	if((key1 !=0xFF) && (key0==0xFF))
          	{
              	//move dig0 to dig1
              	sec10 = sec1;
              	// decode switch and write to dig0
              	sec1 = decode_switches(key1);
        		//decode lower digit to seven-segments and display
        		sseg1 = BCD2SSEG(sec1);
				write_lower_ssd(sseg1);
				
        		//decode upper digit to seven-segments and display
				sseg10= BCD2SSEG(sec10);
				write_upper_ssd(sseg10);
          }
          key0 = key1;
		  //
		  _delay_ms(50);
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
	DDRC = 0xFF;
	//PORTA = 0xFF;


    //decode lower digit to seven-segments and display
	write_lower_ssd(BCD2SSEG(0));

    //decode upper digit to seven-segments and display
	write_upper_ssd(BCD2SSEG(0));
}

/*
// Read from port D (switch port)
unsigned char read_switches(void)
{
		unsigned char key1=0xFF;

		key1 = PIND;

		return key1;
}*/

void write_leds(unsigned char x)
{
	PORTB = x;
}

void write_upper_ssd(unsigned char n)
{

	PORTC = n;
}

void write_lower_ssd(unsigned char n)
{

	PORTA = n;
}



unsigned char decode_switches(unsigned char x)
{
	unsigned char index;

	switch(x)
	{
		case 0xFE:
			index = 0;
			break;
		case 0xFD:
			index = 1;
			break;
		case 0xFB:
			index = 2;
			break;
		case 0xF7:
			index = 3;
			break;
		case 0xEF:
			index = 4;
			break;
		case 0xDF:
			index = 5;
			break;
		case 0xBF:
			index = 6;
			break;
		case 0x7F:
			index = 7;
			break;
		default:
			index = x;
	};

	return index;
}

unsigned char BCD2SSEG(unsigned char x) {
	unsigned char dsp;

    switch(x)
    {
	      case 0x00: // 0
	          dsp =  0xFC;
	          break;
	      case 0x01:// 1
	          dsp =  0xC0;  //Hex value = 1
	          break;
	      case 0x02:// 2
	          dsp =  0x9E;
	          break;
	      case 0x03:// 3
	          dsp =  0xCE;
	          break;
	      case 0x04:// 4
	          dsp =  0xE2;
	          break;
	      case 0x05:// 5
	          dsp =  0x6E;
	          break;
	      case 0x06:// 6
	          dsp =  0x7E;
	          break;
	      case 0x07:// 7
	          dsp =  0xC8;
	          break;
	      case 0x08:// 8
	          dsp =  0xFE;
	          break;
	      case 0x09:// 9
	          dsp =  0xEE;
	          break;
	      default:
	      	dsp =  0x00; // turn off all LEDs
	 }
	dsp = ~dsp;

	return dsp;
}
