#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ultrasonic.h>
#include <esp_err.h>

#define MAX_DISTANCE_CM 500 // 5m max

#define TRIGGER_GPIO 32
#define ECHO_GPIO_1 25
#define ECHO_GPIO_2 26
#define ECHO_GPIO_3 35

void ultrasonic_test(void *pvParameters)
{
    ultrasonic_sensor_t sensor1 = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO_1
    };

    ultrasonic_sensor_t sensor2 = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO_2
    };

    ultrasonic_sensor_t sensor3 = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO_3
    };

    ultrasonic_init(&sensor1);
    ultrasonic_init(&sensor2);
    ultrasonic_init(&sensor3);

    while (true)
    {
        float distance1, distance2, distance3;

        esp_err_t res1 = ultrasonic_measure(&sensor1, MAX_DISTANCE_CM, &distance1);
        esp_err_t res2 = ultrasonic_measure(&sensor2, MAX_DISTANCE_CM, &distance2);
        esp_err_t res3 = ultrasonic_measure(&sensor3, MAX_DISTANCE_CM, &distance3);

        if (res1 != ESP_OK)
        {
            printf("Sensor 1 - Error %d\n", res1);
        }
        else
        {
            printf("Sensor 1 - Distance: %.2f cm\n", distance1 * 100);
        }

        if (res2 != ESP_OK)
        {
            printf("Sensor 2 - Error %d\n", res2);
        }
        else
        {
            printf("Sensor 2 - Distance: %.2f cm\n", distance2 * 100);
        }

        if (res3 != ESP_OK)
        {
            printf("Sensor 3 - Error %d\n", res3);
        }
        else
        {
            printf("Sensor 3 - Distance: %.2f cm\n", distance3 * 100);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void app_main()
{
    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
