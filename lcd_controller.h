// lcd_controller.h

#ifndef _LCD_CONTROLLER_h
#define _LCD_CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define max_temp 30
#define max_humidity 50
#define pin16 16 //1th dht11 D0
#define pin05 5   // 2th dht11 D1
#define pin04 4   // 3th dht11  D2
#define pin14 14   // 1th fan D5
#define pin0 0 // heater  is represented by led1 D3
#define pin12 12 // 2th fan D6
#define pin13 13 // 3th fan D7
#define pin02  2  //bump is represented by led2 D4
#define error_readSensor -200
//void ICACHE_RAM_ATTR isr_heater_pump();
float humid_average();
float temp_average();
void sch();

void dht_begin();
void heater_pump();

#endif

