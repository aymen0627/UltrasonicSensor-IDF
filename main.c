#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ultrasonic.h>
#include <esp_err.h>

#define MAX_DISTANCE_CM 500 // 5m max

#define TRIGGER_GPIO_1 32
#define ECHO_GPIO_1 25

#define TRIGGER_GPIO_2 27
#define ECHO_GPIO_2 26

void ultrasonic_test(void *pvParameters)
{
    ultrasonic_sensor_t sensor1 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_1
    };

    ultrasonic_sensor_t sensor2 = {
        .trigger_pin = TRIGGER_GPIO_2,
        .echo_pin = ECHO_GPIO_2
    };

    ultrasonic_init(&sensor1);
    ultrasonic_init(&sensor2);

    while (true)
    {
        float distance1, distance2;
        esp_err_t res1 = ultrasonic_measure(&sensor1, MAX_DISTANCE_CM, &distance1);
        esp_err_t res2 = ultrasonic_measure(&sensor2, MAX_DISTANCE_CM, &distance2);

        if (res1 != ESP_OK && res2 != ESP_OK)
        {
            printf("Error: No readings from sensors\n");
        }
        else if (res1 != ESP_OK)
        {
            printf("Error: Sensor 1 - %d: %s\n", res1, esp_err_to_name(res1));
            printf("Distance: %0.04f cm\n", distance2 * 100);
        }
        else if (res2 != ESP_OK)
        {
            printf("Error: Sensor 2 - %d: %s\n", res2, esp_err_to_name(res2));
            printf("Distance: %0.04f cm\n", distance1 * 100);
        }
        else
        {
            // Both sensors have valid readings, so prioritize the reading from the sensor with the shorter distance
            float distance = distance1 < distance2 ? distance1 : distance2;
            printf("Distance: %0.04f cm\n", distance * 100);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void app_main()
{
    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
