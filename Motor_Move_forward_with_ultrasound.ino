
const int motorPin=9; 

// BEGIN ULTRASONIC DECLARATIONS
//Define pins for ultrasonic
int const trigPin = 10;
int const echoPin = 11;


// BEGIN JOYSTICK DECLARATIONS
//Define (analog) pins for Joystick
const int minimumValueOnX=10;
const int VRx =0;
const int VRy =1;
const int SW =2;
// Read variables
int calX, calY, calSW, rawX, rawY, rawSW;


void setup() {

  Serial.begin(9600); //Initialize serie port

  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
  
 // pinMode(switchPin, INPUT); 
  pinMode(motorPin, OUTPUT); 


//JOYSTICK CALIBRATION TO (0,0)
calX = analogRead(VRx);
calY = analogRead(VRy);
calSW = analogRead(SW);
  //END JOYSTICK CALIBRATION



}

void loop() {

//HERE IS TO SET THE TRIG AND ECHO ROUTINE
int duration, distance;
// Output pulse with 1ms width on trigPin
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);
// Measure the pulse input in echo pin
duration = pulseIn(echoPin, HIGH);
// Distance is half the duration devided by 29.1 (from datasheet)
distance = (duration/2) / 29.1;
//END ECHO ROUTINE


//HERE IS TO MEASURE VALUES OF (X, Y) SENT BY JOYSTICK
rawX = analogRead(VRx)- calX;
rawY = analogRead(VRy)- calY;
rawSW = analogRead(SW)- calSW;

// AND TO DISPLAY THEM ON MY SCREEN
Serial.print("Valeur X : ");
Serial.println((int)(rawX));
Serial.print("Valeur y : ");
Serial.println((int)(rawY));
Serial.print("Switch : ");
//END OF DISPLAY MODULE 

  
  if (rawX>minimumValueOnX){ //If joystick is used following the X axis
// if distance less than 0.2 meter and more than 0 (0 or less means over range)
      if (distance <= 20 && distance >= 0) {
      digitalWrite(motorPin, LOW); // Don't Move
      } else {
      digitalWrite(motorPin, HIGH); // Move
      }
// Waiting 60 ms won't hurt any one
delay(60);
}


 else {
digitalWrite (motorPin, LOW); //Joystick is not used following X axis so don't move
}
}
