/*
 * Sensors.h
 *
 * Created: 11/8/2014 7:20:38 PM
 *  Author: Jacob
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_

#include "ADC.h"
#include <stdint.h>

#define FRONT_FLOOR_SENSOR_L ADC2
#define FRONT_FLOOR_SENSOR_R ADC1
#define IR_PROXIMITY_SENSOR ADC0

typedef enum {
	 false,
	  true
} bool;

struct ADCResult  
{
	uint8_t Source;
	uint16_t Result;
};

void initSensors(void);
struct ADCResult ADCInfo(void);
void startNewADCConversion(void);
void changeToIR_PROXIMITY();
void changeToFLOOR_R();
void changeToFLOOR_L();

#endif /* SENSORS_H_ */