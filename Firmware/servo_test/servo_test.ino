#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

int servoPin = 2;

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin); // attaches the servo on pin 2 to the servo object
  myservo.write(180); // AS A CONTINUOUS SERVO, THIS SHOULD ROTATE CONTINUOUSLY AT MAX POWER
} 

void loop() {
//  myservo.write(180); // AS A CONTINUOUS SERVO, THIS SHOULD ROTATE CONTINUOUSLY AT MAX POWER
//#  delay(1000);
  myservo.write(0); // AS A CONTINUOUS SERVO, THIS SHOULD ROTATE CONTINUOUSLY AT MAX POWER
  delay(1000);
  myservo.write(180); // AS A CONTINUOUS SERVO, THIS SHOULD ROTATE CONTINUOUSLY AT MAX POWER
  delay(1000);
  }
