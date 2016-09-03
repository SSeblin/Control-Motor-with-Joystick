/*
FOR THIS MODULE, I AM TRYING TO MAKE A MOTOR MOVE FRONT AND 
BACKWARD WITH A H BRIDGE SN754410 THE LEFT AND RIGHT IS MANAGED 
WITH A SERVO MOTOR. 
*/

#include <Servo.h>
Servo servoWheel;

//BEGIN H-BRIDGE DECLARATION
const int controlPin1=2;
const int controlPin2=3;
const int enablePin=9;

int angle; //Angle of the Servo

//Define analog pins for Joystick
const int VRx =0;
const int VRy =1;


int calY, rawY;


void setup() {

  servoWheel.attach(10); //The digital pin where the servo is attached
  Serial.begin(9600); //Initialize serie port

pinMode (controlPin1, OUTPUT);
pinMode (controlPin2, OUTPUT);
pinMode (enablePin, OUTPUT);

//JOYSTICK CALIBRATION ON Y
calY = analogRead(VRy);
  //END JOYSTICK CALIBRATION

digitalWrite (enablePin,LOW);

}

void loop() {


//HERE IS TO MEASURE VALUES OF X AND Y SENT BY JOYSTICK
rawX = analogRead(VRx);
rawY = analogRead(VRy)- calY;

// AND TO DISPLAY THEM ON MY SCREEN
Serial.print("Valeur X : ");
Serial.println((int)(rawX));
Serial.print("Valeur y : ");
Serial.println((int)(rawY));
//END OF DISPLAY MODULE 

// MOVE FORWARD MODULE 
if (rawY>100){ //If joystick is used following the growing Y axis
  digitalWrite(enablePin, HIGH);
      digitalWrite(controlPin1, HIGH);
      digitalWrite(controlPin2,LOW);
      } 
      
else if (rawY<-100){ //If joystick is used following the decreasing Y axis
      digitalWrite(enablePin, HIGH);
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2,HIGH);
      }

 else {
      digitalWrite(enablePin, LOW);
}


//MOVE LEFT OR RIGHT MODULE 

  angle = map(rawX,0,1023,0,180);
  Serial.print(", Angle: ");
  Serial.println(angle);

  servoWheel.write(angle);
  delay(30);

} //THIS IS THE END
