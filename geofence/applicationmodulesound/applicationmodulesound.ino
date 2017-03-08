#include <Arduino.h>

#include "output.h"

const int gpsInputPort = 7;
const int speakerPort = 10;

int gpsValue = HIGH;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(gpsInputPort, INPUT);

}

char buffer[73];

void loop() {
	static int i = 0;

	gpsValue = digitalRead(gpsInputPort);
	if (gpsValue == HIGH) {
		tone(speakerPort, 1000, 200);
	}

	delay(1000);

	for(int j = 0; j < 3; j++) {
		strcpy_P(buffer, (const char*)pgm_read_word(&(nmea_table[i++])));
		Serial.println(buffer);
		if(i >= 147) i = 0;
	}

#if 0
	Serial.println("$GPGGA,150042,6324.916253,N,01024.387120,E,1,05,2.0,20.0,M,41.0,M,,*71");
	Serial.println("$GPRMC,150042,A,6324.916253,N,01024.387120,E,0.0,,150217,0.2,W,A*26");
#endif
}
