// interrupt 0 (pin 2) to detect the rising edge of echo signal from ultrasonic sensor
// interrupt 1 (pin 3) to detect the falling edge of echo signal from ultrasonic sensor
// pin 13 outputs the trig signal to ultrasonic
// Principle: distance = (d2 - d1) * 340m/s
// But due to the time precision of millis() is 1ms, the distance precision is 340mm, very bad way!

#include <SoftwareSerial.h>

int outPin = 13;
volatile float d1, d2;
float distance;

// the setup routine runs once when you press reset:
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // initialize the digital pin as an output.
  pinMode(outPin, OUTPUT);

  // interrupt 0 is on digital pin 2
  attachInterrupt(0, measure1, RISING);
  // interrupt 1 is on digital pin 3
  attachInterrupt(1, measure2, FALLING);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(outPin, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1); // keep high for at least 10us, here for 1ms
  digitalWrite(outPin, LOW); // turn the LED off (LOW is the voltage level)

  if(d2 > d1)
    distance = (d2-d1)*0.017;

  //if (Serial.available())
  {
    delay(100); // 4.5m/340 = 13.2ms
    Serial.print("The distance is: ");
    Serial.print(distance);
    Serial.print("cm    ");
    Serial.print(distance/2.54);
    Serial.println("inches");
  }
}

// 2cm = 0.02m, 0.02m/340 = 58.8us, Can Arduino ( e.g. millis() ) measure so small time slot?
void measure1()
{
  d1 = micros();
}

void measure2()
{
  d2 = micros();
}
