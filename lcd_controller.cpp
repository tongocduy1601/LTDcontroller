

#include "lcd_controller.h"
#include "DHTesp.h"
bool heater, pump;
DHTesp dht1;
DHTesp dht2;
DHTesp dht3;
float temp, humid;
float temp1, temp2, temp3;
void dht_begin() {
	dht1.setup(pin16, DHTesp::DHT11);
	dht2.setup(pin05, DHTesp::DHT11);
	dht3.setup(pin04, DHTesp::DHT11);
}
float  temp_average() {

	temp1 = dht1.getTemperature();
	temp2 = dht2.getTemperature();
	temp3 = dht3.getTemperature();
	// three temperature values is different;
	if (isnan(temp1)) {
		if (isnan(temp2)) {
			return NAN;
		}
		else {
			if (isnan(temp3)) {
				return NAN;
			}
			else {
				return (temp2 + temp3) / 2;
			}
		}
	}
	else {
		if (isnan(temp2)) {
			if (isnan(temp3)) {
				return NAN;
			}
			else {
				return (temp1 + temp3) / 2;
			}
		}
		else {
			if (isnan(temp3)) {
				return (temp1 + temp2) / 2;
			}
			else {
				return (temp1 + temp2 + temp3) / 3;
			}
		}
	}


}

float humid_average() {
	float humid1 = dht1.getHumidity();
	float humid2 = dht2.getHumidity();
	float humid3 = dht3.getHumidity();
	if (isnan(humid1)) {
		if (isnan(humid2)) {
			Serial.printf("sensors 12 are not active \n");
			return NAN;
		}
		else {
			if (isnan(humid3)) {
				Serial.printf("sensors  1 3are not active\n");
				return NAN;
			}
			return (temp2 + temp3) / 2;
		}
	}
	else {
		if (isnan(humid2)) {
			if (isnan(humid3)) {
				Serial.printf("sensors  23 are not active\n");
				return NAN;
			}
			else {
				return (temp1 + temp3) / 2;
			}
		}
		else {
			if (isnan(humid3)) {
				Serial.printf("sensors are not active\n");
				return NAN;
			}
			else {
				return (humid1 + humid2) / 2;
			}
		}
	}
	return (temp1 + temp2 + temp3) / 3;
}
void heater_pump() {
	temp = dht1.getTemperature();
	humid = dht1.getHumidity();
	Serial.printf("%f, %f\n", temp, humid);
	/*if (isnan(temp)) {
		digitalWrite(pin0, LOW);
		digitalWrite(pin02, LOW);
		heater = false;
		pump = false;
		return;
	}
	if(temp >= max_temp)
		{
			digitalWrite(pin0, LOW);
			digitalWrite(pin02, HIGH);
			heater = false;
			pump = true;
	}
	else {
		digitalWrite(pin0, HIGH);
		digitalWrite(pin02, LOW);
		heater = true;
		pump = false;
	}*/

}

void sch() {
	if (heater&&pump == false) {
		digitalWrite(pin12, HIGH);
		digitalWrite(pin14, LOW);
	}
	if (!heater&&pump) {
		digitalWrite(pin12, LOW);
		digitalWrite(pin14, HIGH);
	}
	if (!heater && !pump) {
		digitalWrite(pin12, LOW);
		digitalWrite(pin14, LOW);
	}

	if (isnan(humid)) {
		Serial.printf("sensors are not avtive\n");
	}
	if (humid >= max_humidity) {
		digitalWrite(pin13, HIGH);
	}

}





