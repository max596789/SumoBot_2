/*
 * Sensors.c
 *
 * Created: 11/8/2014 7:20:26 PM
 *  Author: Jacob
 */ 

#include "Sensors.h"
#include <stdint.h>

void initSensors(void)
{
	/* Initialize all of the sensors and set appropriate ubbr for USART */
	initADC();
}

struct ADCResult ADCInfo(void)
{
	struct ADCResult Info; 
	
	switch(getADCConverted())
	{
		case IR_PROXIMITY_SENSOR :
			Info.Source = IR_PROXIMITY_SENSOR;
			changeADCSource(FRONT_FLOOR_SENSOR_R);
			break;
		case FRONT_FLOOR_SENSOR_R :
			Info.Source = FRONT_FLOOR_SENSOR_R;
			changeADCSource(FRONT_FLOOR_SENSOR_L); //Should be Right_IR_Sensor if using
			break;
		case FRONT_FLOOR_SENSOR_L :
		Info.Source = FRONT_FLOOR_SENSOR_L;
		changeADCSource(IR_PROXIMITY_SENSOR); //Should be Right_IR_Sensor if using
		break;
	}
	
	Info.Result = getADCResult();
	return Info;
}

void startNewADCConversion(void)
{	startConversion();	}

void changeToIR_PROXIMITY()
{
	changeADCSource(IR_PROXIMITY_SENSOR);
}

void changeToFLOOR_R()
{
	changeADCSource(FRONT_FLOOR_SENSOR_R);
}
void changeToFLOOR_L()
{
	changeADCSource(FRONT_FLOOR_SENSOR_L);
}