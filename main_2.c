/*
 * main_2.c
 *
 * Created: 11/18/2015 1:46:20 AM
 *  Author: JCooper
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "MotorDrive.h"
#include "Sensors.h"
#define F_CPU 1000000UL //Make sure you change the fuses to 20MHz
#include <util/delay.h>

const int NUM_STATES = 3;

typedef enum 
{
	SEARCHING,
	REVERSING,
	ATTACKING
}DriveState;

typedef struct  
{
	DriveState State; 
	void (*functionPtr)(ADCResult);
}stateMachineType;

stateMachineType stateMachine[] = 
{
	{SEARCHING, search},
	{REVERSING, reverse},
	{ATTACKING, attack}
};

struct ADCResult data;
DriveState state = SEARCHING;
void search(ADCResult);
void reverse(ADCResult);
void attack(ADCResult);
uint8_t flag = 0;

int main(void)
{
	sei();
	startNewADCConversion();
	_delay_ms(100);
	
	while(1)
	{
		if (state < NUM_STATES)
		{
			(*stateMachine[state].functionPtr)(data);
		} 
		else
		{
		}
				
	}
}

ISR(ADC_vect)
{
	cli();
	
	//Read data and load it into Sensors or find some way to deal with it
	data = ADCInfo();
	flag = 1; 
	sei();
}

void search(ADCResult sample)
{
	driveDirection(LEFT, NORMAL);
	
	if (sample.Source == IR_PROXIMITY_SENSOR)
	{
		if (sample.Result > 500)
		{
			state = ATTACKING;
		} 
		else
		{
			state = SEARCHING;
		}	
	}
	else if (sample.Source == FRONT_FLOOR_SENSOR_L)
	{
			if (sample.Result > 500)
			{
				state = REVERSING;
			}
			else
			{
				state = SEARCHING;
			}
	} 
	else if (sample.Source == FRONT_FLOOR_SENSOR_L)
	{
			if (sample.Result > 500)
			{
				state = REVERSING;
			}
			else
			{
				state = SEARCHING;
			}
	}
	startNewADCConversion();
};

void reverse(ADCResult sample)
{
	driveDirection(BACKWARD, NORMAL);
	_delay_ms(2000);
	changeToIR_PROXIMITY();
	state = SEARCHING;
	startNewADCConversion();
};

void attack(ADCResult sample)
{
	driveDirection(FORWARD, FAST);
	if (sample.Source == IR_PROXIMITY_SENSOR)
	{
		if (sample.Result > 500)
		{
			state = ATTACKING;
			changeToIR_PROXIMITY();
		}
		else
		{
			state = SEARCHING;
		}
	}
	else {}
	startNewADCConversion();
};