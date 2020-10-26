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

enum States{start, wait, increment, decrement, reset, waitInc, waitDec} state;

unsigned char button1;
unsigned char button2;
unsigned char tmpC;

void Tick() {
	
	switch(state) {
		case start: 
			state = wait; 
		break;
		case wait:
			if((button1 + button2) == 0x03) {
				state = reset;
			}
			else if((button1 + button2) == 0x01) {
				state = increment;
			}			
			else if((button1 + button2) == 0x02) {
				state = decrement; 
			}
			else {
				state = wait;
			}
			break;
		case increment:
			if((button1 + button2) == 0x03) {
				state = reset;
			}
			else {
				state = waitInc;
			}
			break;
		case decrement:
			if((button1 + button2) == 0x03) {
				state = reset;
			}
			else {
				state = waitDec;
			}
			break;
		case reset:
			if((button1 + button2) == 0x00) {
				state = wait;
			}
			else {
				state = reset;
			}
			break;

		case waitInc:
			if((button1 + button2) == 0x00)
				state = wait;
			else {
				state = waitInc;
			}
			break;

		case waitDec:
			if((button1 + button2) == 0x00) {
				state = wait;
			}
			else {
				state = waitDec;
			}
			break;
		default:
			break;

	}

	switch(state) {
		case start: 
			tmpC = 0x07; 
			break;
		case wait:  
			break;
		case increment: 
			if(tmpC < 0x09) {
				tmpC = tmpC + 0x01;
			}
			break;
		case decrement:
			if(tmpC > 0x00) {
				tmpC = tmpC - 0x01;
			}
			break;
		case reset: 
			tmpC = 0;  
			break;
		case waitInc: break;
		case waitDec: break;
		default:
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
  //  DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    
    state = start;
    tmpC = 7;
    while (1) {
	button1 = PINA & 0x01;
	button2 = PINA & 0x02;
	Tick();
	PORTC = tmpC;
    }
    return 1;
}
