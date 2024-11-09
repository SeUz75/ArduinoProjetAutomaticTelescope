#define STEP_PIN 3
#define DIR_PIN 4


float coordinatesOfMoonRad[2];
float coordinatesOfMoonDegr[2];
String inputString = ""; //String to hold the incomming data
bool newData=false;





void setup() {

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);


  // Start the Serial Monitor
  Serial.begin(9600);
  Serial.println("Stepper motor control initialized.");

}

void loop() {

  digitalWrite(DIR_PIN, HIGH);
  Serial.println("Rotating clockwise.");
//  movemotor(200);
//
//  delay(1000);    // Wait 1 second
//
//  // Set the direction to counterclockwise
//  digitalWrite(DIR_PIN, LOW);   // LOW for counterclockwise
//  Serial.println("Rotating counterclockwise.");
//  movemotor(200); // Move 200 steps counterclockwise
//  delay(1000);    // Wait 1 second




   // CONVERTING RADIANS FROM MY JAVA PROGRAM TO DEGREES : 


}


// Function to receive data from the Java project (Moon's Altitude and Azimuth)
void receiveData() {
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == '\n') { // End of message
      newData = true;
      break;
    }
    inputString += receivedChar;
  }

  if (newData) {
    int commaIndex = inputString.indexOf(','); // Find the comma
    if (commaIndex != -1) {
      // Extracting and converting the data
      coordinatesOfMoon[0] = inputString.substring(0, commaIndex).toFloat(); // Azimuth
      coordinatesOfMoon[1] = inputString.substring(commaIndex + 1).toFloat(); // Altitude
    }
    inputString = ""; // Clear the input string for new data
  }
}

void covertingRadToDegrees(float[2] coordinatesOfMoon){
  
}



// TODO !! !- FROM DEGREES -> STEPS 

//// Function to move the motor by a specified number of steps
//void movemotor(int steps) {
//  for (int i = 0; i < steps; i++) {
//    digitalWrite(STEP_PIN, HIGH);   // Step
//    delayMicroseconds(800);         // Adjust speed here (lower value = faster)
//    digitalWrite(STEP_PIN, LOW);    // Reset step
//    delayMicroseconds(800);         // Delay between steps
//
//    // Print every 10 steps to reduce serial flooding
//    if (i % 10 == 0) {
//      Serial.print("Step: ");
//      Serial.println(i + 1);
//    }
//  }
//  Serial.println("Rotation complete.");
//}
