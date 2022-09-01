/*
 * ultrasonic.cpp
 *
 * Created: 01-06-2015 13:03:59
 *  Author: Urvashi
 */ 



#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BR 9600
#define PS ((F_CPU/(16UL*BR))-1)



void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(char *str);



void lcd_init()
{
	disp_cmd(0X02);
	disp_cmd(0X28);
	disp_cmd(0X0C);
	disp_cmd(0X06);
}

/*void disp_cmd(unsigned int cmd)
{
	PORTD=((cmd)& 0XF0);
	PORTD=PORTD + 0X02;
	_delay_ms(2);
	PORTD=PORTD - 0X02;
	PORTD=((cmd<<4)& 0XF0);
	PORTD=PORTD + 0X02;
	_delay_ms(2);
	PORTD=PORTD - 0X02;
}
void disp_data( int cmd)
{
	PORTD=((cmd)  & 0XF0);
	PORTD=PORTD+ 0X03;
	_delay_ms(2);
	PORTD=PORTD - 0X03;
	PORTD=((cmd<<4)& 0XF0);
	PORTD=PORTD + 0X03;
	_delay_ms(2);
	PORTD=PORTD - 0X03;
}*/
void disp_cmd(unsigned int cmd)
{
	PORTB=((cmd)& 0XF0);
	PORTB=(PORTB>>2) + 0X02;
	_delay_ms(2);
	PORTB=PORTB - 0X02;
	PORTB=((cmd<<4)& 0XF0);
	PORTB=(PORTB>>2) + 0X02;
	_delay_ms(2);
	PORTB=PORTB - 0X02;
	
	
}
void disp_data( int cmd)
{
	PORTB=(cmd  & 0XF0);
	PORTB=(PORTB>>2)+ 0X03;
	_delay_ms(2);
	PORTB=PORTB - 0X03;
	PORTB=((cmd<<4)& 0XF0);
	PORTB=(PORTB>>2)+ 0X03;
	_delay_ms(2);
	PORTB=PORTB - 0X03;
}
void disp_string( char *str)
{
	int i=0;
	while (str[i]!='\0')
	{
		disp_data (str[i]);
		i++;
		
	}
}

void disp_num(unsigned int num)
{
	int a=0;
	if (num==0)
	{
		disp_data(48);
	}
	disp_cmd (0X04);
	while (num!=0)
	{
		a=num % 10;
		disp_data(a+48);
		num=num/10;
	}
	disp_cmd (0X06);
}






void usart_init()
{
	UCSRB =(1<<RXEN) | (1<<TXEN);
	UCSRC =(1<<URSEL) | (1<<USBS) | (1<<UCSZ1) | (1<<UCSZ0);
	UBRRL=PS;
	UBRRH=(PS>>8);
}

void usart_tx(unsigned char data)
{
	while((UCSRA & 0x20)==0);
	UDR=data;
}
void usart_txstring(char *str)
{
	int i=0;
	while (str[i]!='\0')
	{
		usart_tx(str[i]);
		_delay_ms(100);
		i++;
		
	}
}

unsigned int usart_rx()
{
	while((UCSRA & 0x80)==0);
	return UDR;
}



 

        int main()
        {
			
	        DDRB = 0XFF;
	        DDRD = 0XFF;
			DDRC = 0XFE;
			lcd_init();
			usart_init();
	        disp_cmd(0X80);
	        disp_string("WELCOME");
			 
	      
	       
		    while(1)
			{
				
			if (PINC==0X01)
			{
				//PORTB=0XFF;
				disp_cmd(0XC0);
				disp_string("DETECTED        ");
				usart_tx('A');
				_delay_ms(100);
				
				_delay_ms(100);
				//PORTB=0X00;
				
				//_delay_ms(1000);
			}
			
			else
			{
				disp_cmd(0XC0);
				disp_string("NOT DETECTED    ");
				
				
			}
		
			
			}
		}						
			 
			
		
		

			
	
		
			


