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
  Servo myservo;
  int val;    // variable to read the value from the analog pin


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
      myservo.setPeriodHertz(50);
      myservo.attach(SERVO_PIN, 500, 2400);
      initialised = true;
    }

    Dabble.processInput();

    angle = GamePad.getAngle();

    Serial.println(angle);

    val = map(angle, 0, 360, -180, 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val);

  }
}
