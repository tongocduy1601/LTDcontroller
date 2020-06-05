// 
// 
// 
#include "clock.h"
int counter;
int num_tasks = 0;

typedef struct task {
	uint16_t delay;
	uint16_t period;
	void(*ptask)();
	char id;
	int index;
	int cycle;
	bool run;
};
void start_timer() {
	timer1_attachInterrupt(timer_ISR);
	timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
	timer1_write(TICKS);
}
time_t get_time(void) {
	return counter;
}
task sch_tasks[MAX_TASKS];
void sort_timer() {
	if (num_tasks < 2) return;
	task tem;
	int current = 1;
	//tem = sch_tasks[current];
	int walker, i;
	while (current < num_tasks) {
		tem = sch_tasks[current];
		walker = current - 1;
		while (walker >= 0 && tem.delay < sch_tasks[walker].delay) {
			sch_tasks[walker + 1] = sch_tasks[walker];
			walker = walker - 1;
		}
		sch_tasks[walker + 1] = tem;
		current++;
	}
	for (i = 0; i < num_tasks; i++) {
		sch_tasks[i].index = i;
	}
	for (i = 1; i < num_tasks; i++) {
		sch_tasks[i].cycle = sch_tasks[i].delay - sch_tasks[i - 1].delay;
	}	
	sch_tasks[0].cycle = sch_tasks[0].delay;
}

uint32_t register_timer(uint16_t delay, timercallback callback_f, uint16_t period) {
	int index = 0;
	while ((index < MAX_TASKS) && (sch_tasks[index].ptask != NULL)) {
		index++;
	}
	if (index == MAX_TASKS) return -1;
	sch_tasks[index].delay = delay;
	sch_tasks[index].period = period;
	sch_tasks[index].ptask = callback_f;
	num_tasks++;
	int i, id;
	bool is_id;
	for (i = 0; i < num_tasks - 1; i++)
	{
		for (id = 0; id < num_tasks - 1; id++) {
			if (i + 65 == sch_tasks[id].id) {
				is_id = true;
				break;
			}
			else {
				is_id = false;
			}
		}
		if (!is_id) {
			break;
		}
	}
	sch_tasks[index].id = i+65;
	sort_timer();
	//(*sch_tasks[index].ptask)();
	return index;
}
int stop_timer(void) {
}

task tem[MAX_TASKS];
void ISR_dispatch() {
	int i=1,  tasks_run_count=1;
	if (sch_tasks[0].run) {
		while (sch_tasks[0].cycle == sch_tasks[i].cycle) {
			tem[i] = sch_tasks[i];
			i++;
			tasks_run_count++;
		}
		tem[0] = sch_tasks[0];
		i = 0;
		while (i < tasks_run_count) {
			(*tem[i].ptask)();
			remove_timer(tem[i].id);
			register_timer(tem[i].period, tem[i].ptask, tem[i].period);
			i++;
		}
	/*
		tasks_run_count = 1;
		while (tasks_run_count < num_tasks) {
			if (sch_tasks[0].cycle != sch_tasks[tasks_run_count].cycle) break;
			tem[i] = sch_tasks[i];
			i++;
			tasks_run_count++;
		}
		Serial.printf("tasks_run_count= %d\n", tasks_run_count);
		for (i = 0; i < tasks_run_count; i++) {			
			(*sch_tasks[i].ptask)();
			sch_tasks[i].run = false;
			remove_timer(sch_tasks[i].id);
			register_timer(tem[i].period, tem[i].ptask, tem[i].period);

		}
		for (i = 0; i < num_tasks; i++) {
			Serial.printf("task_id= %c\n", sch_tasks[i].id);
			
		}
		tasks_run_count = 0;
			for (int i = 0; i < num_tasks; i++) {
			//	Serial.printf("sch_task[%d].cycle= %d\n", i, sch_tasks[i].cycle);
			}*/
		
	}
}

task tem_t;
void ICACHE_RAM_ATTR timer_ISR() {
	tem_t = sch_tasks[0];
	//Serial.printf("tem_t.cycle= %d", tem_t.cycle);
	if (sch_tasks[0].ptask == NULL) {
		timer1_write(TICKS);
		return;
	}
	if (sch_tasks[0].cycle == 0) {
		sch_tasks[0].run = true;
		timer1_write(TICKS);
		return;
	}
	else {	
			sch_tasks[0].cycle--;
	}
	counter++;
	timer1_write(TICKS);
}
void remove_timer(uint32_t id) {
	int i;
	for (i = 0; i < num_tasks; i++) {
		if (sch_tasks[i].id == id) {
			tem_t = sch_tasks[i];
			sch_tasks[i] = sch_tasks[num_tasks - 1];
			sch_tasks[num_tasks - 1].cycle = 0;
			sch_tasks[num_tasks - 1].delay = 0;
			sch_tasks[num_tasks - 1].id = 0;
			sch_tasks[num_tasks - 1].ptask = NULL;
			break;
		}
	}
	num_tasks--;
	sort_timer();
	for (i = 0; i < num_tasks; i++) {
		sch_tasks[i].delay = sch_tasks[i].delay - tem_t.delay;
		//Serial.printf("sch_tasks[%d].id=%c,sch_tasks[%d].delay= %d\n",i,sch_tasks[i].id,i, sch_tasks[i].delay);
	}
	//Serial.printf("tem_t.delay= %d\n", tem_t.delay);
}