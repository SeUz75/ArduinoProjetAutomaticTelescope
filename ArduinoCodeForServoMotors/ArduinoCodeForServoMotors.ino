
#include <AccelStepper.h>
#include <TinyGPS++.h>

#include <Servo.h>

Servo azimuthServo; // Завъртаме ма хоризонталната ОС (азимут)
Servo heightServo; // Завъртаме ма ветикалната ОС (елевация)

int azimudDegrees=0;
int heightDegrees=0;



const int ledPin=10; // Built-in LED on protoShield

// The TinyGPS++ object
TinyGPSPlus gps;


void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);

  // Моторът за азимуд е в 8, и елевацията е в 7
  azimuthServo.attach(7);
  heightServo.attach(8);
  pinMode(ledPin, OUTPUT);
  azimuthServo.write(0);
  heightServo.write(0);

}

void loop(){

  while (Serial1.available() > 0) {
    char c = Serial1.read();
    gps.encode(c);  // <--- Това липсваше
    if (gps.location.isUpdated()){
      Serial.print(gps.location.lat(), 6);
      Serial.print(',');
      Serial.println(gps.location.lng(), 6);
    }
  }


 // Обработка на входните данни за луната
 if (Serial.available()>0) {
      digitalWrite(ledPin,HIGH);
      delay(1000);
    // Read the incoming data
    // String receivedData = Serial.readStringUntil('\n');
    // int position = receivedData.toInt();

    // -----------------------------
     String moonsCoord = Serial.readStringUntil('\n'); // Четене на входен стринг
    int commaIndex = moonsCoord.indexOf(','); // Намиране на запетаята

    // Извличане на координати
    String lontitudeString = moonsCoord.substring(0, commaIndex);
    String azimuthString = moonsCoord.substring(commaIndex + 1);

    // Преобразуване в float
    int lontitude = lontitudeString.toInt();  // Височина на Луната
    int azimuth = azimuthString.toInt(); // Азимут на Луната



    //--------------------
    
    // Move servos
    heightServo.write(lontitude);
    azimuthServo.write(azimuth);
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

