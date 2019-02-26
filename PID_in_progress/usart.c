#include<avr/io.h>
#include <stdio.h>
#include <math.h>
#include <avr/pgmspace.h>
//#include <util/setbaud.h>
//#include<avr/interrupt.h> 

#define clk  16000000 
#define USART_BAUDRATE 115200
#define set_ubbr   ((clk)/(USART_BAUDRATE*16)  - 1 )  

//function for initialisig usart 

void usart__init( ) {
	UBRR0 = 16 ;
	//UBRR0L =  ;
	//UBRR0L = ( unsigned char  ) ( set_ubbr)  ; 
	// enabling receiver and transmitter 
	UCSR0B 	=  ( 1 << RXEN0)|( 1 << TXEN0 ) ; 
	UCSR0C = (0<<USBS0);       // 1 stop bit 
	UCSR0C =  (1 << UCSZ01) | (1 << UCSZ00);    //8 data bits
	UCSR0A =(1<<U2X0);
}



void  UsartTransmit( char data, FILE *stream) {
				/* Wait for empty transmit buffer */
				//loop_until_bit_is_set(UCSR0A, UDRE0); 
				while ( !( UCSR0A & (1<<UDRE0)) ) ; 
				UDR0 = data ;       /* send data */ 
}

unsigned char  UsartReceive( FILE *stream ){
		/* Wait for data to be received */
			while (!(UCSR0A & (1<<RXC0)));
		/* Get and return received data from buffer */
			return UDR0;
}

FILE usart0_str = FDEV_SETUP_STREAM(UsartTransmit, UsartReceive, _FDEV_SETUP_RW );



int main(){
	 
	//inialising usart i.e baudrate , stop bit
	stdin=stdout=&usart0_str;
	uint16_t  u16Data = 526;
	double fltData = 3.141593;
	uint8_t u8Data; 

	printf("\nunsigned int = %u",u16Data);
	fprintf(stdout,"\ndouble = %08.3f", fltData);

	
	usart__init( ) ;
	
	while(1){
	scanf("%c",&u8Data);
	printf("\nunsigned int = %u",u16Data);
	fprintf(stdout ,"\ndouble = %f", fltData);
	printf("%c; Key code: %u",u8Data, u8Data);
	}


}