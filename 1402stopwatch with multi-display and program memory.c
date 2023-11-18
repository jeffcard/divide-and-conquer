#include <avr/pgmspace.h>
#include <avr/io.h>
//#include <util/delay.h>

// Function declarations
void initialize(void);
unsigned char read_switches(void);
//void write_leds(unsigned char x);
void write_upper_ssd(unsigned char n);
void write_lower_ssd(unsigned char n);
//unsigned char interpret_switches(unsigned char x, unsigned char *p, unsigned char *num);
//unsigned char decode_switches(unsigned char x);

// decode BCD values to seven-segment display pattern
unsigned char BCD2SSEG(unsigned char);
unsigned char ssegtbl[] PROGMEM = {0xFC, 0xC0, 0x9E, 0xCE, 0xE2, 0x6E, 0x7E, 0xC8, 0xFE, 0xEE};
//unsigned char digittbl[] PROGMEM = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

// executing assembly instruction
void delay_ms(int duration);

int main(void)
{
		unsigned char x;
		unsigned char b_cnt, cnt;
		unsigned char sec1,sec10,sseg1,sseg10;

		b_cnt = 0;
		cnt = 0;
	  	sec1 = 0;
		sec10 = 0;

		//initialize ports
		initialize();

		while(1)
		{
				//Read switches and save to x
				x = read_switches();

				// test if SW1 is pressed,
				if (x == 0xFE)
				{
						// stop counting
						b_cnt = 0;
						// clear both digits
					  	sec1 = 0;
						sec10 = 0;

						//decode lower digit to seven-segments and display
						write_lower_ssd(BCD2SSEG(0));
					  	//decode upper digit to seven-segments and display
						write_upper_ssd(BCD2SSEG(0));
				}
				else if (x == 0xFD)
				{
						b_cnt = 1;
						//cnt = 100;
				}
				else if (x == 0xFB)
				{
						b_cnt = 0;
				}
				else ;

				// test if SW2 is pressed,
				if (b_cnt == 1 && x == 0xFF)
				{
						// delay 1 second _delay_ms(1000);
				        if (sec1>9)
				        {
				            sec1 = 0;
				            sec10++;
				            if (sec10>9)
							{
								sec1 = 0;
				                sec10 = 0;
							}
				        }

		        		//decode lower digit to seven-segments and display
		        		sseg1 = BCD2SSEG(sec1);
						write_lower_ssd(sseg1);

		        		//decode upper digit to seven-segments and display
						sseg10= BCD2SSEG(sec10);
						write_upper_ssd(sseg10);
						
						
						if (cnt < 100) cnt++;
						// delay 0.5 seconds
						else 
						{
							cnt =0;
							// increment stop watch sec1++;
							sec1++;
						}
				}
				else
				{		
						//decode lower digit to seven-segments and display
						sseg1 = BCD2SSEG(sec1);
						write_lower_ssd(sseg1);
						//decode upper digit to seven-segments and display
						sseg10= BCD2SSEG(sec10);
						write_upper_ssd(sseg10);
				}

				delay_ms(10);
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
/*
	  //decode lower digit to seven-segments and display
		write_lower_ssd(BCD2SSEG(0));

	  //decode upper digit to seven-segments and display
		write_upper_ssd(BCD2SSEG(0));*/
}

// Read from port D (switch port)
unsigned char read_switches(void)
{
		unsigned char y;
		y = PIND;

		return y;
}

/*
void write_leds(unsigned char x)
{
		PORTB = x;
}*/

void write_upper_ssd(unsigned char n)
{
		PORTC = n;
		delay_ms(10);
        PORTC = 0xFF;
}

void write_lower_ssd(unsigned char n)
{
		PORTA = n;
		delay_ms(10);
        PORTA = 0xFF;
}

void delay_ms(int duration)
{
		unsigned char x;
    for(int i = 0; i < duration; i++){
        for(int i = 0; i < 200; i++){
						x= read_switches();
						if(x != 0xFF)return;
            asm("nop" ::);
        }
    }
}

unsigned char BCD2SSEG(unsigned char x)
{
	return ~pgm_read_byte(&ssegtbl[x&0x0F]);
}
