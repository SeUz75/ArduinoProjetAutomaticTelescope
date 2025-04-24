
#include <AccelStepper.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Servo.h>

Servo azimuthServo; // Завъртаме ма хоризонталната ОС (азимут)
Servo heightServo; // Завъртаме ма ветикалната ОС (елевация)

int azimudDegrees=0;
int heightDegrees=0;


static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
const int ledPin=10; // Built-in LED on protoShield

// The TinyGPS++ object
TinyGPSPlus gps;


void setup(){
  Serial.begin(9600);
  Serial1.begin(GPSBaud);

  // Моторът за азимуд е в 9, и елевацията е в 10
  azimuthServo.attach(7);
  heightServo.attach(8);
  pinMode(ledPin, OUTPUT);
  azimuthServo.write(0);
  heightServo.write(0);

}

void loop(){

  // This sketch displays information every time a new sentence is correctly encoded.
  if (Serial1.available() > 0){
    gps.encode(Serial1.read());
    if (gps.location.isUpdated()){
      Serial.print(gps.location.lat(), 6);
      Serial.print(',');
      Serial.println(gps.location.lng(), 6);
    }
    delay(2000);
  }


 if (Serial.available()>0) {
      digitalWrite(ledPin,HIGH);
      delay(1000);
    // Read the incoming data
    String receivedData = Serial.readStringUntil('\n');
    int position = receivedData.toInt();
    
    // Move servos
    heightServo.write(position);
    azimuthServo.write(position);
    delay(1000);
    //for(int i=0;i<position ; i++){
    //  digitalWrite(ledPin,HIGH);
    //  delay(1000);
    //  digitalWrite(ledPin,LOW);
    //  delay(1000);
    //}
      digitalWrite(ledPin,LOW);
      delay(1000);
  }

}

