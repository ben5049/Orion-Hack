#include "pinAssignments.h"
#include "config.h"
#include "myTasks.h"

/* Semaphores */
SemaphoreHandle_t mutexI2C; /* I2C Mutex so only one task can access the I2C peripheral at a time */

/* Queues */
QueueHandle_t IMUDataQueue;


void setup() {
  // put your setup code here, to run once:

  /* Create I2C mutex */
  if (mutexI2C == NULL) {
    mutexI2C = xSemaphoreCreateMutex();
    if (mutexI2C != NULL) {
      xSemaphoreGive(mutexI2C);
    }
  }

  /* Create queues */
  IMUDataQueue = xQueueCreate(1, sizeof(angleData));

  /* Create tasks */
  xTaskCreatePinnedToCore(
    taskIMU,           /* Function that implements the task */
    "IMU",             /* Text name for the task */
    10000,             /* Stack size in words, not bytes */
    nullptr,           /* Parameter passed into the task */
    TASK_IMU_PRIORITY, /* Task priority */
    &taskIMUHandle,    /* Pointer to store the task handle */
    tskNO_AFFINITY);
}

void loop() {
  // put your main code here, to run repeatedly:
}
