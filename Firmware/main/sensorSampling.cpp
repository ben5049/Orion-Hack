#include "Wire.h"
#include "MPU6050_light.h"
#include "myTasks.h"
#include "config.h"

/* Task handles */
TaskHandle_t taskIMUHandle = nullptr;

/* Task to sample the IMU and process data */
void taskIMU(void *pvParameters) {

  (void)pvParameters;

  /* IMU Control */
  MPU6050 mpu(Wire);
  static bool initialised = false;
  static uint8_t status;

  /* IMU Data */
  struct angleData IMUData;

  /* Task timing */
  const TickType_t xFrequency = configTICK_RATE_HZ / IMU_SAMPLING_FREQUENCY_DMP;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  /* Main loop */
  while (true) {

    /* Pause the task until enough time has passed */
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    /* Initialise IMU */
    if (!initialised) {
      if (xSemaphoreTake(mutexI2C, pdMS_TO_TICKS(1000)) == pdTRUE) {
        status = mpu.begin();
      }
      if (status != 0) {
        Serial.println("Unable to boot MPU6050");
        vTaskDelay(pdMS_TO_TICKS(1000));
        initialised = false;
      } else {
        initialised = true;
        Serial.println("Calibrating IMU");
        mpu.calcOffsets();
        Serial.println("Calibration complete");
      }
    }

    /* Get IMU samples */
    if (xSemaphoreTake(mutexI2C, pdMS_TO_TICKS(1000)) == pdTRUE) {
      mpu.update();
    }

    /* Pack readings into IMU data */
    IMUData.pitch = mpu.getAngleX();
    IMUData.roll = mpu.getAngleY();
    IMUData.yaw = mpu.getAngleZ();

    /* Write the struct that stores the IMU data to a single item queue to distribute to other tasks */
    xQueueOverwrite(IMUDataQueue, &IMUData);
  }
}