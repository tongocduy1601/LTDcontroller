// clock.h

#ifndef _CLOCK_h
#define _CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define TICKS 5000
#define MAX_TASKS 10

void ISR_dispatch();
//int start_timer(char* timer_vaddr);
void start_timer();
time_t get_time(void);
//uint32_t register_timer(uint64_t delay, timercallback callback_f, void* data,uint32_t);
uint32_t register_timer(uint16_t delay, timercallback callback_f, uint16_t);
void remove_timer(uint32_t id);
int stop_timer(void);
void sch_update();
void  ICACHE_RAM_ATTR timer_ISR();
#endif

