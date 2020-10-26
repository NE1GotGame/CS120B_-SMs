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

enum States{start, B0unpressed, B0pressed, B1not, B1pressed} state;

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void TickSM() {
	
	switch(state) {
		case start: 
			state = B0unpressed; 
			break;
		case B0unpressed: 
			if((tmpA & 0x01) == 0x01) { 
				state = B0pressed;
			}
			else {
				state = B0unpressed;
			}
			break;
		case B0pressed: 
			if((tmpA & 0x01) == 0x00) {
				state = B1not;
			}
			else {
				state = B0pressed;
			}			
			break;
		case B1not: 
			if((tmpA & 0x01) == 0x01) { 
				state = B1pressed; 
			}
			else {
				state = B1not;
			}
			break;
		case B1pressed:
			if((tmpA & 0x01) == 0x00) {
				state = B0unpressed;
			}
			else {
				state = B1pressed;
			}
			break;
	}

	switch(state) {
		case start: 
			tmpB = 0x01; 
			break;
		case B0unpressed: 
			tmpB = 0x01; 
			break;
		case B0pressed: 
			tmpB = 0x02; 
			break;
		case B1not: 
			tmpB = 0x02; 				
			break;
		case B1pressed: 
			tmpB = 0x01; 
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    
    state = start;
    
    while (1) {
	tmpA = PINA & 0x01;
	TickSM();
	PORTB = tmpB;
    }
    return 1;
}
