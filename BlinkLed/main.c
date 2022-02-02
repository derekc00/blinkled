/*
 * BlinkLed.c
 *
 * Created: 1/21/2022 9:00:05 PM
 * Author : Derek Chang and David Lieu
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "avr.h"

void avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{
	// PC0 -> input / button
	// PD7 -> output / LED
	
	SET_BIT(DDRD, PD7);			// set PD7 as output
	CLR_BIT(DDRC, PC0);			// set PC0 as Input
    while (1)
    {							
		if (!GET_BIT(PINC, PC0))	// check if PINC PC0 is 1 or 0 (aka 5V or gnd)
		{
			PORTD ^= (1 << PD7);	// flip PD7 (aka flip output pin from 0 to 1 or viceversa)
			avr_wait(500);			// delay 1/2 second
			
		} else {
			CLR_BIT(PORTD, PD7);	// turn off LED off when button not pressed
		}
    }
	return(0);				// should never get here, this is to prevent a compiler warning
}