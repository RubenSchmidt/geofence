#include <NMEAGPS.h>
#include <NeoSWSerial.h>

// This sets the default ports to listen for the GPS signal to 3 and 4.
// It also uses NeoSWSerial instead to do software serial.
#include "GPSport.h"
#include "Streamers.h"

#define DEBUG_PORT Serial

// Check configuration
#ifndef NMEAGPS_INTERRUPT_PROCESSING
#error You must define NMEAGPS_INTERRUPT_PROCESSING in NMEAGPS_cfg.h!
#endif

static NMEAGPS gps;

//--------------------------

static void GPSisr( uint8_t c )
{
  gps.handle( c );

} // GPSisr

void setup() {
  // Start the normal trace output
  DEBUG_PORT.begin(9600);
  while (!DEBUG_PORT)
    ;

  DEBUG_PORT.print( F("NMEA_isr.INO: started\n") );
  DEBUG_PORT.print( F("fix object size = ") );
  DEBUG_PORT.println( sizeof(gps.fix()) );
  DEBUG_PORT.print( F("NMEAGPS object size = ") );
  DEBUG_PORT.println( sizeof(gps) );
  DEBUG_PORT.println( F("Looking for GPS device on " USING_GPS_PORT) );

  trace_header( DEBUG_PORT );

  DEBUG_PORT.flush();

  // Start the UART for the GPS device
  gps_port.attachInterrupt( GPSisr );
  gps_port.begin( 9600 );

}

void doSomeWork() {
  gps_fix fix = gps.read();
    if (fix.valid.location) {
    Serial.print( fix.latitude() );
    Serial.print( ',' );
    Serial.println( fix.longitudeL() );
  }
}

void loop() {
  if (gps.available()) {
    //doSomeWork();
    // Print all the things!
    trace_all( DEBUG_PORT, gps, gps.read() );
  }

  if (gps.overrun()) {
    gps.overrun( false );
    DEBUG_PORT.println( F("DATA OVERRUN: took too long to use gps.read() data!") );

  }
}
