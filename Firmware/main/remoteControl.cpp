#include "myTasks.h"
#include "config.h"
#include "pinAssignments.h"
#include <ESP32Servo.h>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

/* Task handles */
TaskHandle_t taskRemoteControlHandle = nullptr;

volatile uint32_t angle;


/* Task to sample the IMU and process data */
void taskRemoteControl(void *pvParameters) {

  (void)pvParameters;

  static bool initialised = false;

  Servo myservo1;
  Servo myservo2;
  Servo myservo3;
  
  /* Task timing */
  const TickType_t xFrequency = configTICK_RATE_HZ / REMOTE_CONTROL_FREQUENCY;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  /* Main loop */
  while (true) {

    /* Pause the task until enough time has passed */
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    /* Initialise Dabble */
    if (!initialised) {
      Dabble.begin("MyEsp32");
      ESP32PWM::allocateTimer(0);
      ESP32PWM::allocateTimer(1);
      ESP32PWM::allocateTimer(2);
      ESP32PWM::allocateTimer(3);
      myservo1.setPeriodHertz(50);
      myservo1.attach(SERVO_PIN1, 500, 2400);
      myservo1.write(90);
//      myservo2.setPeriodHertz(50);
//      myservo2.attach(SERVO_PIN2, 500, 2400);
//      myservo2.write(90);
//      myservo3.setPeriodHertz(50);
//      myservo3.attach(SERVO_PIN3, 500, 2400);
//      myservo3.write(90);
      initialised = true;
    }

      Dabble.processInput();

      angle = GamePad.getAngle();

      Serial.println(angle);
      if ((0 < angle) && (angle < 120)) {
        myservo1.write(0);
      }
      else {
        myservo1.write(20);
      }

      if (120 <= angle && angle < 240) {
        myservo2.write(0);
      }
      else {
        myservo2.write(90);
      }

      if (240 <= angle && angle <= 360) {
        myservo3.write(0);
      }
      else {
        myservo3.write(90);
      }


      //      val = map(angle, 0, 360, -180, 180);     // scale it to use it with the servo (value between 0 and 180)
      //      myservo1.write(val);



    
  }
}
