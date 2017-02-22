#include <NMEAGPS.h>
#include <NeoSWSerial.h>

#include <SD.h>

// This sets the default ports to listen for the GPS signal to 3 and 4.
// It also uses NeoSWSerial instead to do software serial.
#include "GPSport.h"
#include "Streamers.h"
#include "fenceCheck.h"
#include "fence_data.h"

#define DEBUG_PORT Serial

// Check configuration
#ifndef NMEAGPS_INTERRUPT_PROCESSING
#error You must define NMEAGPS_INTERRUPT_PROCESSING in NMEAGPS_cfg.h!
#endif

static NMEAGPS gps;
const int applicationModulePort = 8;

struct coordinate fence[20];
uint32_t points;
struct coordinate pos;
gps_fix fix;

//--------------------------

static void GPSisr( uint8_t c )
{
	gps.handle( c );

} // GPSisr

void setup() {
	// Start the normal trace output
	DEBUG_PORT.begin(9600);
	while (!DEBUG_PORT);
	DEBUG_PORT.print( F("NMEA_isr.INO: started\n") );
	DEBUG_PORT.print( F("fix object size = ") );
	DEBUG_PORT.println( sizeof(gps.fix()) );
	DEBUG_PORT.print( F("NMEAGPS object size = ") );
	DEBUG_PORT.println( sizeof(gps) );
	DEBUG_PORT.println( F("Looking for GPS device on " USING_GPS_PORT) );
	trace_header( DEBUG_PORT );
	DEBUG_PORT.flush();

	pinMode(applicationModulePort, OUTPUT);
	// Start the UART for the GPS device
	gps_port.attachInterrupt( GPSisr );
	gps_port.begin( 9600 );

  // Initialise SD card
	pinMode(10, OUTPUT);
	//pinMode(SS, OUTPUT);
	if(!SD.begin(10)) {
		DEBUG_PORT.println("Error in SD.begin()");
		return;
	}

	// Import fence here
	// Set number of points here.
  auto err = load_fence_from_sd("map", fence, &points);
  if(err != LOAD_FENCE_FROM_SD_OK) {
    DEBUG_PORT.print("Fence load error: ");
    DEBUG_PORT.println(err);
  }
}

void doSomeWork() {
	pos.latitude = fix.latitudeL();
	pos.longitude = fix.longitudeL();
	int status = insideFence(fence, pos, points);
	if (status == 1 ) {
		digitalWrite(applicationModulePort, HIGH);
	} else {
		digitalWrite(applicationModulePort, LOW);
	}		
}

void loop() {
	if (gps.available()) {
		fix = gps.read();
		if (fix.valid.location) {
			doSomeWork(); 
		}
		// Print all the things!
		trace_all( DEBUG_PORT, gps, fix );
	}

	if (gps.overrun()) {
		gps.overrun( false );
		DEBUG_PORT.println( F("DATA OVERRUN: took too long to use gps.read() data!") );
	}
}
