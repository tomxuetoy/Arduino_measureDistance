//Feel free to use this code. 
//Please be respectful by acknowledging the author in the code if you use or modify it. 
//Author: Bruce Allen 
//Date: 23/07/09  
//Digital pin 7 for reading in the pulse width from the MaxSonar device. 
//This variable is a constant because the pin will not change throughout execution of this code.

// Modified by Tom Xue for HC-SR04 ultrasonic sensor
// pin 13 to be set as output pin and provides the trig signal (to start it) to HC-SR04
const int pwPin = 7, trigPin = 13; 

//variables needed to store values
long pulse, inches, cm;
void setup() {
  //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);
  pinMode(pwPin, INPUT);
  pinMode(trigPin, OUTPUT);
}
void loop() {
  digitalWrite(trigPin, HIGH);
  delay(1); // should provide a >10us width high level trig signal, here 1ms
  digitalWrite(trigPin, LOW);

  //Used to read in the pulse that is being sent by the HC-SR04 ultrasonic sensor.
  //Pulse Width representation with a scale factor of 147 us per Inch.
  pulse = pulseIn(pwPin, HIGH);
  //147uS per inch
  // inches = pulse/147;

  //change inches to centimetres
  // cm = inches * 2.54;

  // Tom Xue: I am used to this kind of calculation
  cm = pulse*0.340*0.100/2;
  inches = cm/2.54;
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}