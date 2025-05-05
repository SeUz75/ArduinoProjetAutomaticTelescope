#include <TinyGPS++.h>
#include <Servo.h>

Servo azimuthServo; // Servo for horizontal axis (azimuth)
Servo heightServo;  // Servo for vertical axis (elevation)

const int ledPin = 10; // Built-in LED on protoShield
const int azimuthServoPin = 8;
const int heightServoPin = 7;

// The TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);   // Communication with Java program
  Serial1.begin(9600);  // Communication with GPS module (assuming it's connected to Serial1)

  // Initialize servos
  azimuthServo.attach(azimuthServoPin);
  heightServo.attach(heightServoPin);
  
  pinMode(ledPin, OUTPUT);
  
  // Set servos to initial position
  azimuthServo.write(0);
  heightServo.write(0);
  
  // Flash LED to indicate startup
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}

void loop() {
  // Process GPS data if available
  while (Serial1.available() > 0) {
     gps.encode(Serial1.read());
    if (gps.location.isUpdated()){
      Serial.print(gps.location.lat(), 6);
      Serial.print(',');
      Serial.println(gps.location.lng(), 6);
    }
  }

  // Check for celestial position data from Java
  if (Serial.available() > 0) {
    digitalWrite(ledPin, HIGH); // Indicate we're receiving data
    
    String moonCoords = Serial.readStringUntil('\n');
    int commaIndex = moonCoords.indexOf(',');
    
    if (commaIndex > 0) {
      // Extract azimuth and altitude
      String azimuthString = moonCoords.substring(0, commaIndex);
      String altitudeString = moonCoords.substring(commaIndex + 1);
      
      // Convert to float
      float azimuthDegrees = azimuthString.toFloat();
      float altitudeDegrees = altitudeString.toFloat();
      
      // FIXING THE RESTRICTED 180 DEGREES OF MY SERVO MOTORS
      // IF AZIMUTH > 180 I will be working with the other way around 
      if(azimuthDegrees > 180){
        azimuthDegrees = azimuthDegrees-180;

        // Flip the b angle around 90, maybe?
        altitudeDegrees = 90 + (90 - altitudeDegrees);

      } 
        // Move servos
      azimuthServo.write(azimuthDegrees);
      heightServo.write(altitudeDegrees);
    }
    digitalWrite(ledPin, LOW);
  }
}