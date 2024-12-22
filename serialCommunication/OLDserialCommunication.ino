#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps; // Create a GPS object
SoftwareSerial gpsSerial(4, 3); // RX, TX

void setup() {
  Serial.begin(9600);      // Serial for communication with PC/Java
  gpsSerial.begin(9600);   // Serial for communication with GPS module
  delay(2000);             // Allow time for Arduino initialization
}

void loop() {
  delay(1000); // Delay to simulate time between updates
  String gpsData = "42.1354,24.7453"; // Simulated GPS coordinates
  Serial.println(gpsData); // Send simulated coordinates to Java

  // Listen for Java's response
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n'); // Read data sent from Java
    Serial.println(receivedData); // Echo back the received data
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
