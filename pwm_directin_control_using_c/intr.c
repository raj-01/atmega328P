
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h> 

uint8_t dir_rotation = 0 ;  

uint8_t turn = 0 ; 
uint8_t count = 0 ; 

void initTimer0(void) {
/* must be /64 or more for ISR timing */
				
				TCCR0B |= (1 << WGM12) | (1 << CS01) | (1 << CS00);
				OCR0A = 101 ; 
/* both output compare interrupts */
				TIMSK0 |= (1 << OCIE0A ) ;
				//TIMSK0 |= (1 << TOIE0);
/* overflow interrupt enable */
				sei();
}


int main (void)
{
 /* set pin 5 of PORTB for output*/
DDRD = 0b11111111 ;
if( dir_rotation == 1){
		PORTD  |=  _BV(PORTD4);
}
else{
	PORTD  &=  ~_BV(PORTD5);
}
 
 //PORTD  |=  _BV(PORTD5);
 initTimer0() ; 
 while(1) {
			
 }

}



ISR(TIMER0_COMPA_vect) {
			
			count++ ; 
			if(count == 2 ){  
				
				PORTD |= _BV(PORTD5);
				count = 0 ; 
				//_delay_ms(1000);
				OCR0A = 13 ; 
			}
				
			if( count == 1 ){
				PORTD &= ~ _BV(PORTD5);	
				OCR0A = 236; 

				//_delay_ms(1000);
				}
}


