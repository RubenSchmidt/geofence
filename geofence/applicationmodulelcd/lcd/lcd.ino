#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
// software serial : TX = digital pin 10, RX = digital pin 11
SoftwareSerial mySerial(10,11);
String inData ="";

void setup() {
  lcd.begin(16, 2);
  mySerial.begin(9600);
  lcd.setCursor(0,0);
}

void loop() {
// lcd.autoscroll();
	if (mySerial.available()) {
		char rec=mySerial.read();
		

		if (rec=='\n')
		{
			inData.pop_back();
			lcd.setCursor(0,0);
			lcd.print(inData);

			inData="";
		}
    	else {
    		
			inData += rec;
    	}
	}

}