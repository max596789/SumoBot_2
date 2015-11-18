/*
 * MotorDrive.c
 *
 * Created: 11/8/2014 7:15:51 PM
 *  Author: Jacob
 */ 

#include "MotorDrive.h"
#include "PWM.h"
#include <avr/io.h>
#include <stdint.h>

void initMotorDriver()
{
	DDRD |= 0xF0; //1111 1100  
	initPWM();	//Will set PINB1 and PINB2 for output of PWM
}

void driveDirection(enum Direction dir, enum Speed speed)
{
	switch (dir)
	{
	case RIGHT :
		backwards();
			changeDutyCycleOCR1A(DUTY_CYCLE_20);
			changeDutyCycleOCR1B(DUTY_CYCLE_10);
		break;
	case LEFT :
		backwards();
			changeDutyCycleOCR1A(DUTY_CYCLE_20);
			changeDutyCycleOCR1B(DUTY_CYCLE_10);
		break;
	case FORWARD :
		backwards();
		if (speed == FAST)
		{
			changeDutyCycleOCR1A(DUTY_CYCLE_50);
			changeDutyCycleOCR1B(DUTY_CYCLE_50);
		}
		else
		{
			changeDutyCycleOCR1A(DUTY_CYCLE_10);
			changeDutyCycleOCR1B(DUTY_CYCLE_10);
		}

		break;
	case BACKWARD :
		forwards();
		if (speed == FAST)
		{
			changeDutyCycleOCR1A(DUTY_CYCLE_50);
			changeDutyCycleOCR1B(DUTY_CYCLE_50);
		}
		else
		{
			changeDutyCycleOCR1A(DUTY_CYCLE_10);
			changeDutyCycleOCR1B(DUTY_CYCLE_10);
		}
		break;
	}
}

void forwards(void)
{
	PORTD |=  (1<<PIND6) | (1<<PIND4);
	PORTD &= ~((1<<PIND5) | (1<<PIND7));
}

void backwards(void)
{
	PORTD |=  (1<<PIND5) | (1<<PIND7);
	PORTD &= ~((1<<PIND6) | (1<<PIND4));
}

void stop(void)
{
	PORTD &= ~((1<<PIND6) | (1<<PIND4) | (1<<PIND5) | (1<<PIND7));
}
