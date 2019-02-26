#include<avr/io.h>
#include <stdio.h>
#include <math.h>
#include <avr/pgmspace.h>
#include<avr/interrupt.h> 

#define clk  16000000 
#define USART_BAUDRATE 115200
#define set_ubbr   ((clk)/(USART_BAUDRATE*8)  - 1 ) 

//function for initialisig usart 

void usart__init( ) {
	UBRR0 = set_ubbr ;   // or calculated vlaue of ubbr can be assigned 
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




//defing varibles...note is_data_ready is acting as flag 0-->false and 1-->true
 
uint8_t is_data_reddy = 0 ; 
uint8_t ovf_enable = 0 ; 
uint16_t capture_time ; 
int past_count =  0 ; 
uint16_t future_count = 0 ; 
uint8_t num_ovf = 0 ; 
uint8_t data ; 

void init_timer1(){

	//setting ICR1 bits for capturing rising edge 
	TCCR1B |= ( 1<<ICES1 ) ;
	// enbling input capture icr1 interrupt vector 
	TIMSK1 |= (1<<ICIE1);
	//enabling timer overflow interrpt vector 
	TIMSK1 |= (1<TOIE1);
	//setting prescalar value to 64 
	TCCR1B|=(1<<CS02)|(0<<CS01)|(1<<CS00);
	// setting global interupt 
	sei() ; 
}

ISR( TIMER1_CAPT_vect ){
			PORTD &= ~ _BV(PORTD5);
			future_count = ICR1 ; 
			// changing cpature on falling edge by setting TCCR1B = 0 
			//TCCR1B &= ~(1<<ICES1);
			// desabling the input capture interupt 
			//TIMSK1 &= ~(1<<ICIE1);
			// making data ready flag = true 
			is_data_reddy = 1 ; 
			ovf_enable = 1 ; 
			printf("\n yeah i am in input capture = %u", data );
			printf("\nunsigned int = %u",( future_count - past_count) );
			past_count = future_count ;
				
}

ISR( TIMER1_OVF_vect ){
	PORTD &= ~ _BV(PORTD5);
	if( ovf_enable == 1 ){
		past_count =  past_count - 65535 ; 
		ovf_enable = 0 ; 
	}
}


// setting variables for pwm 
uint8_t dir_rotation = 1 ;  

uint8_t turn = 0 ; 
uint8_t count = 0 ; 

// initialising 8 bit timer 
void initTimer0(void) {
/* must be /64 or more for ISR timing */
				
				TCCR0B |= (1 << WGM12) | (0 << CS01) | (1 << CS00);
				OCR0A = 11 ; 
/* both output compare interrupts */
				TIMSK0 |= (1 << OCIE0A ) ;
				//TIMSK0 |= (1 << TOIE0);
/* overflow interrupt enable */
				sei();
}



ISR(TIMER0_COMPA_vect) {
			printf("\n this is tmer0 = %u", data );
			count++ ; 
			
			
			if(count == 2 ){  
				
				PORTD |= _BV(PORTD5);
				count = 0 ; 
				//_delay_ms(1000);
				OCR0A = 20 ; 

			}
				
			if( count == 1 ){
				PORTD &= ~ _BV(PORTD5);	
				OCR0A = 235; 
				//_delay_ms(1000);
				// enabling the timer1 input capture interupt
				//TIMSK1 |= (1<<ICIE1);
				
				}
}



int main(){
	// for usart use .....
	stdin=stdout=&usart0_str;
	// initialising usart 
	usart__init( ) ;
	//initilising timer
	init_timer1() ;

	/* set pin 5 of PORTD for output*/
	//DDRD |= 0b11111111;
	DDRD |= 1<<DDD5 ; 
	if( dir_rotation == 1){
			PORTD  |=  _BV(PORTD4);
	}
	else{
		PORTD  &=  ~_BV(PORTD4);
	}
 
 	PORTD  |=  _BV(PORTD5);
 	initTimer0() ; 

	scanf("%c",&data);
	printf("\n yeah i am in main = %u", data );

	while(1){
			if( is_data_reddy == 1  ){
				// send the data of pulse using usart 
				printf("\nunsigned int = %u",( future_count - past_count) );
				past_count = future_count ;
				is_data_reddy = 0 ;  
			}
			
	}


}