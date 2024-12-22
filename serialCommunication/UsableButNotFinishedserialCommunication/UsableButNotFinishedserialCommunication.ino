#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin =4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

SoftwareSerial ss(RXPin,TXPin);
void setup() {
  Serial.begin(9600);      // Serial for communication with PC/Java
  ss.begin(GPSBaud);   // Serial for communication with GPS module
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print(gps.location.lat(), 6);
      Serial.print(","); 
      Serial.println(gps.location.lng(), 6);
      delay(2000); // 2-second interval
    }
  }
}







 // WHEN MY GPS MODULE WORKS I WILL USE THIS CODE FOR NOW I WILL HARDCODE MY COORDSS
  // while (gpsSerial.available() > 0) {
  //   char c = gpsSerial.read(); // Read data from GPS module
  //   gps.encode(c);             // Parse the data

  //   // If a new location is available, send latitude and longitude
  //   if (gps.location.isUpdated()) {
  //     float latitude = gps.location.lat();
  //     float longitude = gps.location.lng();
  //     Serial.print(latitude, 6); // Send latitude with 6 decimal places
  //     Serial.print(",");
  //     Serial.println(longitude, 6); // Send longitude with 6 decimal places
  //   }
  // }
