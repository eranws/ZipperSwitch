/*
 Zipper Switch
 
 This example demonstrates the use of a zipper as an on/off switch to activate a servo motor
 
 It reads a digital input on pin 8, and once the zipper is open it turns a servo motor every half second to +/- 45 degrees.
 For demonstration purposes, the motor react only when the zipper is first closed and then opened again. (for the surprise of the testee)
 
 The circuit: 
 * Servo motor on pin 9
 * Zipper attached in one side to pin 8, and on the other side to the ground.
 
 An internal 20K-ohm resistor is pulled to 5V. This configuration causes the input to 
 read HIGH when the zipper is open, and LOW when it is closed. 
 

 by Eran Weissenstern created 20 Nov 2014 
 code adapted from 'Input Pull-up' example by Scott Fitzgerald created 14 March 2012
 
 
 
 This example code is in the public domain
 
 */

int inputPin = 8;
int servoPin = 9;
int ledPin = 13;

boolean closedOnce = false; // start only when closed - for the surprise!

#include <Servo.h> 

Servo servo;  // create servo object to control a servo 
int val = 0;

void setup(){
  //start serial connection
  Serial.begin(9600);
  //configure inputPin as an input and enable the internal pull-up resistor
  pinMode(inputPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT); 
  servo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
  servo.write(90);
}


void loop(){
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(inputPin);

  //print out the value of the pushbutton
  Serial.println(sensorVal);

  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the 
  // button's pressed, and off when it's not:

  if (sensorVal == HIGH) { //zip is open
    //zipper closes
    val = millis(); // milliseconds
    val /= 500; // odd-even
    val %=2; // 0,1
    val = (val * 2) - 1; // map to -1,1
    val = 90 + (val * 45); // map to 45, 135
    
    Serial.println(val);
  } 
  else { //zipper is open
    closedOnce = true;
    val = 90;   
  }

  
  digitalWrite(ledPin, sensorVal); 
  
  if (closedOnce)
  {
    servo.write(val);
  }
  
  delay(100);
}




