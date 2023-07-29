#ifndef MY_TASKS_H
#define MY_TASKS_H

/* Structs */
struct angleData {
  float pitch; /* Pitch in degrees between -180 and 180 */
  float roll;  /* Roll in degrees between -180 and 180 */
  float yaw;   /* Yaw in degrees between -180 and 180 */
};

/* Task handles */
extern TaskHandle_t taskIMUHandle;

/* Queue handles */
extern QueueHandle_t IMUDataQueue;

#endif