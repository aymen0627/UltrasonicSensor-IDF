#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ultrasonic.h>
#include <esp_err.h>

#define MAX_DISTANCE_CM 500 // 5m max

#define TRIGGER_GPIO 32 //share trigger pin

#define ECHO_GPIO_1 25
#define ECHO_GPIO_2 26

//this obtains x amount of readings before it decides if there is an object or not
#define DEBOUNCE_THRESHOLD 3 // Adjust the threshold value as per your requirements

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

    ultrasonic_init(&sensor1);
    ultrasonic_init(&sensor2);

    bool objectDetected = false; // Flag to indicate if an object is detected
    int debounceCounter = 0; // Counter for debouncing

    while (true)
    {
        float distance1, distance2;

        // Activate shared trigger pin
        gpio_set_direction(TRIGGER_GPIO, GPIO_MODE_OUTPUT);
        gpio_set_level(TRIGGER_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(TRIGGER_GPIO, 0);

        esp_err_t res1 = ultrasonic_measure(&sensor1, MAX_DISTANCE_CM, &distance1);
        esp_err_t res2 = ultrasonic_measure(&sensor2, MAX_DISTANCE_CM, &distance2);

        if (res1 != ESP_OK && res2 != ESP_OK)
        {
            printf("Error: No readings from sensors\n");
            debounceCounter = 0; // Reset the debounce counter
            objectDetected = false; // Reset the object detection flag
        }
        else if (res1 != ESP_OK)
        {
            printf("Error: Sensor 1 - %s\n", esp_err_to_name(res1));
            debounceCounter = 0; // Reset the debounce counter
            objectDetected = false; // Reset the object detection flag
        }
        else if (res2 != ESP_OK)
        {
            printf("Error: Sensor 2 - %s\n", esp_err_to_name(res2));
            debounceCounter = 0; // Reset the debounce counter
            objectDetected = false; // Reset the object detection flag
        }
        else
        {
            // Both sensors have valid readings, so prioritize the reading from the sensor with the shorter distance
            float distance = (distance1 < distance2) ? distance1 : distance2;
            
            if (distance < 1.0 && !objectDetected)
            {
                debounceCounter++;
                if (debounceCounter >= DEBOUNCE_THRESHOLD)
                {
                    printf("Object detected: Distance: %0.04f cm\n", distance * 100);
                    objectDetected = true; // Set the object detection flag

                    // Perform the necessary actions here, such as activating the license plate detecting camera
                    // and verifying if a vehicle has passed
                    // ...
                }
            }
            else if (distance >= 1.0 && objectDetected)
            {
                debounceCounter--;
                if (debounceCounter <= 0)
                {
                    printf("Object cleared: Distance: %0.04f cm\n", distance * 100);
                    objectDetected = false; // reset detection flag
                }
            }

        // Ensure the debounce counter stays within the valid range
        if (debounceCounter < 0)
            debounceCounter = 0;
        else if (debounceCounter > DEBOUNCE_THRESHOLD)
            debounceCounter = DEBOUNCE_THRESHOLD;
    }

    vTaskDelay(pdMS_TO_TICKS(500));
}
}


void app_main()
{
xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}