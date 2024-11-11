#define STEP_PIN 3
#define DIR_PIN 4


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

  // Call receiveData to check for incoming data
  receiveData();

  if (newData) {
    // Convert degrees to steps and move the motor
    degreesToSteps(coordinatesOfMoonDegr);
    newData = false; // Reset newData after processing
  }

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
      coordinatesOfMoonDegr[0] = inputString.substring(0, commaIndex).toFloat(); // Azimuth
      coordinatesOfMoonDegr[1] = inputString.substring(commaIndex + 1).toFloat(); // Altitude
    }
    inputString = ""; // Clear the input string for new data
  }
}



// TODO !! !- FROM DEGREES -> STEPS -> DONE ------------------


void degreesToSteps(int degrees[2]){
   // MAKE SURE you know what kind of motor you got ! 
    int steps[2];

    //LETS SAY YOU HAVE A 1.8 STEPPER MOTOR SO : 
    // first we have AZIMUTH !!
    // problem came up, my coordinates are float and my STEPS have to be int so I round the number and we will test it and then ACT !
    steps[0] = round((degrees[0]/1.8)* 200); // so here we have the degrees which comes from the arduino and per step is 1.8 degrees and we need 200 steps
    // for full revolution 

    steps[1] = round((degrees[1]/1.8)*200);

    // We will need 2 FORs 
    // 1 for amizuth and 1 for altitude
    // now that we have the steps for azimuth and altitude
    for (int i = 0; i < steps[0]; i++) {
      digitalWrite(STEP_PIN, HIGH);   // Step
      delayMicroseconds(800);         // Adjust speed here (lower value = faster)
      digitalWrite(STEP_PIN, LOW);    // Reset step
      delayMicroseconds(800);         // Delay between steps
  
      // Print every 10 steps to reduce serial flooding
      if (i % 10 == 0) {
        Serial.print("Step: ");
        Serial.println(i + 1);
      }
    }

    // And the second For is for ALTITUDE of the Telescope 
     for (int i = 0; i < steps[1]; i++) {
      digitalWrite(STEP_PIN, HIGH);   // Step
      delayMicroseconds(800);         // Adjust speed here (lower value = faster)
      digitalWrite(STEP_PIN, LOW);    // Reset step
      delayMicroseconds(800);         // Delay between steps
  
      // Print every 10 steps to reduce serial flooding
      if (i % 10 == 0) {
        Serial.print("Step: ");
        Serial.println(i + 1);
      }
    }
    Serial.println("Rotation complete.");
    
}
