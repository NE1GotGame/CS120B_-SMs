/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum locking_state {start, pound, Y, locked, unlocked} state;

unsigned char Lock(unsigned char buttons_lock) {
	buttons_lock = PINA;

	switch (state) {
		case start:
				state = pound;
				break;
		case pound:	
				if(PINA == 0x04){
					state = Y;
				}
				else {
					state = pound;
				}
				break;
		case Y:	
				if (PINA == 0x00){
					state = locked;
				}
				else if(PINA == 0x04){
					state = Y;
				}
				else {
					state = pound;
				}
				break;
		case locked:	
				if (PINA == 0x02) {
					state = unlocked;
				}
				else if(PINA == 0x00){
					state = locked;
				}
				else {
					state = pound;
				}
				break;
		case unlocked:	
				if(PINA == 0x80){
					state = pound;
				}
				else {
					state = unlocked;
				}
				break;
		default:	
				break;
	}

	switch(state){
		case pound:
		case Y:
		case locked:	
				PORTB = 0x00;
				break;
		case unlocked:	
				PORTB = 0x01;
		default:	
				break;
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char  buttons_lock = 0x00;
    /* Insert your solution below */
    while (1){
	Lock(buttons_lock);
    }
    return 1;
}

