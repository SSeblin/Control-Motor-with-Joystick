/*
FOR THIS MODULE, I AM TRYING TO MAKE A MOTOR MOVE FRONT AND 
BACK WITH A H BRIDGE SN754410
*/
//BEGIN H-BRIDGE DECLARATION
const int controlPin1=2;
const int controlPin2=3;
const int enablePin=9;


// BEGIN JOYSTICK DECLARATIONS
//Define (analog) pins for Joystick
const int VRx =0;
const int VRy =1;
const int SW =2;
// Read variables
int calX, calY, calSW, rawX, rawY, rawSW;


void setup() {

  Serial.begin(9600); //Initialize serie port

pinMode (controlPin1, OUTPUT);
pinMode (controlPin2, OUTPUT);
pinMode (enablePin, OUTPUT);

//JOYSTICK CALIBRATION TO (0,0)
calX = analogRead(VRx);
calY = analogRead(VRy);
calSW = analogRead(SW);
  //END JOYSTICK CALIBRATION

digitalWrite (enablePin,LOW);

}

void loop() {


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


if (rawY>10){ //If joystick is used following the growing Y axis
  digitalWrite(enablePin, HIGH);
      digitalWrite(controlPin1, HIGH);
      digitalWrite(controlPin2,LOW);
      } 
      
else if (rawY<-10){ //If joystick is used following the decreasing Y axis
      digitalWrite(enablePin, HIGH);
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2,HIGH);
      }
// Waiting 60 ms won't hurt any one
//delay(60);

 else {
      digitalWrite(enablePin, LOW);
}


} //THIS IS THE END
