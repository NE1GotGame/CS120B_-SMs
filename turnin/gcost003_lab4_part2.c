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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xF8; PORTC = 0x07;

	unsigned char  tmpC;
	unsigned char button = 0;
    /* Insert your solution below */
    while (1){
	tmpC = PORTC;	/* making tmpC = 0x07 */
		
	if (button == 0){
		if (PINA == 0x03) {//depressed
			tmpC = 0;
			button = 1;
		}
		else if (PINA == 0x01){ //increase
			if (tmpC < 9){
				tmpC++;
				button = 1;
			}
		}
		else if (PINA == 0x02){ //decrease
			if (tmpC > 0){
				tmpC--;
				button = 1;
			}
		}
	}
	else {
		if (PINA == 0){
			button = 0;
		}
	}
	PORTC = tmpC;
    }
    return 1;
}

