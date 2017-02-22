#include <Arduino.h>

const int gpsInputPort = 7;
const int speakerPort = 8;

int gpsValue = HIGH;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(gpsInputPort, INPUT);

}

void loop() {

	gpsValue = digitalRead(gpsInputPort);
	if (gpsValue == HIGH) {
		tone(speakerPort, 1000, 500);
	}
  	delay(1000);
	Serial.println("$GPGGA,150042,6324.916253,N,01024.387120,E,1,05,2.0,20.0,M,41.0,M,,*71");
	Serial.println("$GPRMC,150042,A,6324.916253,N,01024.387120,E,0.0,,150217,0.2,W,A*26");
}
