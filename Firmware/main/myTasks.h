#ifndef MY_TASKS_H
#define MY_TASKS_H

#include "Arduino.h"
#include "freertos/FreeRTOS.h"

/* Structs */
struct angleData {
  float pitch; /* Pitch in degrees between -180 and 180 */
  float roll;  /* Roll in degrees between -180 and 180 */
  float yaw;   /* Yaw in degrees between -180 and 180 */
};

/* Tasks */
void taskIMU(void *pvParameters);
void taskRemoteControl(void *pvParameters);

/* Task handles */
extern TaskHandle_t taskIMUHandle;
extern TaskHandle_t taskRemoteControlHandle;

/* Queue handles */
extern QueueHandle_t IMUDataQueue;

/* Semaphores */
extern SemaphoreHandle_t mutexI2C; /* I2C Mutex so only one task can access the I2C peripheral at a time */


#endif
