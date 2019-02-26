#include<avr/io.h>
#define BAUD_TOL 4

#define BAUD  115200 
#include <util/setbaud.h>
 


/*#define clk    16000000UL
# define   set_ubbr  (( unsigned int  ) ((clk)/(BAUD*16UL)  - 1 ))  */ 

//function for initialisig usart 

void usart__init( ) {
	
	//UCSR0A |= _BV(U2X0);
	UBRR0 = UBRRH_VALUE ; 
	UBRR0L = UBRRL_VALUE;
	
	
	// enabling receiver and transmitter 
	UCSR0B 	= (0<<UCSZ02)|( 1 << RXEN0)|( 1 << TXEN0 ) ; 
	UCSR0C = (1<<USBS0)|(1 << UCSZ01) | (1 << UCSZ00);    /* 8 data bits, 1 stop bit */
	
}


void transmitByte( unsigned int a ) {
				/* Wait for empty transmit buffer */
				loop_until_bit_is_set(UCSR0A, UDRE0);
				//while ( !( UCSR0A & (1<<UDRE0)) ) ; 
				UDR0 = a ;       /* send data */ 

}



int main(){
	 
	//inialising usart i.e baudrate , stop bit
	//UCSR0A |= _BV(U2X0);
	  
	usart__init( ) ;
	while(1){
	transmitByte( 1) ;
	}


}