/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 #include <AccelStepper.h>
 #include <TinyGPS++.h>
#include <SoftwareSerial.h>

AccelStepper azimuthMotor(AccelStepper::DRIVER, 5, 6); // ПИН 2 и 3 за стъпки и посока
AccelStepper altitudeMotor(AccelStepper::DRIVER, 7, 8); // ПИН 4 и 5 за стъпки и посока

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

float stepsAzimuth=0;
float stepsAltitude =0;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);


  azimuthMotor.setMaxSpeed(1000); // Максимална скорост
  azimuthMotor.setAcceleration(500); // Ускорение
  altitudeMotor.setMaxSpeed(1000);
  altitudeMotor.setAcceleration(500);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print(gps.location.lat(), 6);
      Serial.print(',');
      Serial.println(gps.location.lng(), 6);
    }
  }

 // Обработка на входните данни за луната
  if (Serial.available() > 0) {
    String moonsCoord = Serial.readString(); // Четене на входен стринг
    int commaIndex = moonsCoord.indexOf(','); // Намиране на запетаята

    // Извличане на координати
    String latStr = moonsCoord.substring(0, commaIndex);
    String lngStr = moonsCoord.substring(commaIndex + 1);

    // Преобразуване в float
    float latitudeMoon = latStr.toFloat();  // Височина на Луната
    float longitudeMoon = lngStr.toFloat(); // Азимут на Луната

    // Преобразуване в стъпки
    stepsAzimuth = longitudeMoon * (3200.0 / 360.0); // Стъпки за азимута
    stepsAltitude = latitudeMoon * (3200.0 / 360.0); // Стъпки за височината

    // Извеждане за проверка
    Serial.println(stepsAzimuth);
    Serial.println(stepsAltitude);
  }

  // Движение на моторите
  azimuthMotor.move(stepsAzimuth); // Азимут
  altitudeMotor.move(stepsAltitude); // Височина

  azimuthMotor.runToPosition(); // Изпълнение на движение за азимут
  altitudeMotor.runToPosition(); // Изпълнение на движение за височина
}

