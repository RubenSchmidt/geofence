#include <Arduino.h>

const int gpsInputPort = 7;
const int speakerPort = 10;

int gpsValue = HIGH;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(gpsInputPort, INPUT);

}

void loop() {

	gpsValue = digitalRead(gpsInputPort);
	if (gpsValue == HIGH) {
		tone(speakerPort, 1000, 200);
	}
}
