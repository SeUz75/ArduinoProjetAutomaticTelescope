
#include <AccelStepper.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Servo.h>

Servo panServo; // Завъртаме ма хоризонталната ОС (азимут)
Servo tiltServo; // Завъртаме ма ветикалната ОС (елевация)

int azimudDegrees=0;
int heightDegrees=0;


static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);

  // Моторът за азимуд е в 9, и елевацията е в 10
  panServo.attach(9);
  tiltServo.attach(10);

}

void loop(){

   if (ss.available() > 0) {
    Serial.println("Reading GPS data..."); // Debugging line
  }
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print(gps.location.lat(), 6);
      Serial.print(',');
      Serial.println(gps.location.lng(), 6);
    }
  }

 // Обработка на позицията на луната
  if (Serial.available() > 0) {
    String moonsCoord = Serial.readString(); // Четене на входен стринг които са градуса на луната. Азимуд и лантитуде
    int commaIndex = moonsCoord.indexOf(','); // Намиране на запетаята
    
     azimudDegrees = moonsCoord.substring(0,commaIndex).toInt();
     heightDegrees = moonsCoord.substring(commaIndex+1).toInt();
  }

  panServo.write(azimudDegrees);
  tiltServo.write(heightDegrees);

}

