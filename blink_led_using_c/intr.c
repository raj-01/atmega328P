#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h> 



uint16_t count = 0 ; 
uint16_t count_ovf = 0 ; 

void initTimer0(void) {
/* must be /64 or more for ISR timing */
				
				TCCR0B |= (1 << WGM12) | (1 << CS02) | (1 << CS00);
				OCR0A = 245 ; 
/* both output compare interrupts */
				TIMSK0 |= (1 << OCIE0A ) ;
				//TIMSK0 |= (1 << TOIE0);
/* overflow interrupt enable */
				sei();
}


int main (void)
{
 /* set pin 5 of PORTB for output*/
 DDRB |= _BV(DDB5);
 PORTB  |=  _BV(PORTB5);
 initTimer0() ; 
 while(1) {
			if(count == 0 ){  
				if( count_ovf == 61 ){
				PORTB |= _BV(PORTB5);
				count_ovf = 0 ;
				count = 1 ; 
				//_delay_ms(1000);
				}
			}
				
			else {
				if( count_ovf == 244){
				PORTB &= ~ _BV(PORTB5);
				count = 0 ; 
				count_ovf = 0 ; 
				//_delay_ms(1000);
				}
			}
 }

}



ISR(TIMER0_COMPA_vect) {
			
			count_ovf++ ; 

}
