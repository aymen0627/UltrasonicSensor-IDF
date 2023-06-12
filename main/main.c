#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ultrasonic.h>
#include <esp_err.h>

#define MAX_DISTANCE_CM 500 // 5m max

#define TRIGGER_GPIO_1 5 //sensor1
#define ECHO_GPIO_1 14

#define TRIGGER_GPIO_2 5 //sensor2
#define ECHO_GPIO_2 26 


#define TRIGGER_GPIO_3 5 //sensor3
#define ECHO_GPIO_3 35

#define TRIGGER_GPIO_4 5 //sensor4
#define ECHO_GPIO_4 36 //VP on ESP

#define TRIGGER_GPIO_5 5 //sensor5
#define ECHO_GPIO_5 15

#define TRIGGER_GPIO_6 5 //sensor6
#define ECHO_GPIO_6 18 

#define TRIGGER_GPIO_7 5 //sensor7
#define ECHO_GPIO_7 21

#define TRIGGER_GPIO_8 5 //sensor8
#define ECHO_GPIO_8 22

void ultrasonic_test(void *pvParameters)
{
    ultrasonic_sensor_t sensor1 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_1
    };

    ultrasonic_sensor_t sensor2 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_2
    };

    ultrasonic_sensor_t sensor3 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_3
    };

    ultrasonic_sensor_t sensor4 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_4
    };

    ultrasonic_sensor_t sensor5 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_5
    };

    ultrasonic_sensor_t sensor6 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_6
    };

    ultrasonic_sensor_t sensor7 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_7
    };

    ultrasonic_sensor_t sensor8 = {
        .trigger_pin = TRIGGER_GPIO_1,
        .echo_pin = ECHO_GPIO_8
    };

    ultrasonic_init(&sensor1);
    ultrasonic_init(&sensor2);
    ultrasonic_init(&sensor3);
    ultrasonic_init(&sensor4);
    ultrasonic_init(&sensor5);
    ultrasonic_init(&sensor6);
    ultrasonic_init(&sensor7);
    ultrasonic_init(&sensor8);

    while (true)
    {
        float distance1, distance2, distance3,distance4, distance5,distance6, distance7, distance8;

        esp_err_t res1 = ultrasonic_measure(&sensor1, MAX_DISTANCE_CM, &distance1);
        esp_err_t res2 = ultrasonic_measure(&sensor2, MAX_DISTANCE_CM, &distance2);
        esp_err_t res3 = ultrasonic_measure(&sensor3, MAX_DISTANCE_CM, &distance3);
        esp_err_t res4 = ultrasonic_measure(&sensor4, MAX_DISTANCE_CM, &distance4);
        esp_err_t res5 = ultrasonic_measure(&sensor5, MAX_DISTANCE_CM, &distance5);
        esp_err_t res6 = ultrasonic_measure(&sensor6, MAX_DISTANCE_CM, &distance6);
        esp_err_t res7 = ultrasonic_measure(&sensor7, MAX_DISTANCE_CM, &distance7);
        esp_err_t res8 = ultrasonic_measure(&sensor8, MAX_DISTANCE_CM, &distance8);

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

        if (res4 != ESP_OK)
        {
            printf("Sensor 4 - Error %d\n", res4);
        }
        else
        {
            printf("Sensor 4 - Distance: %.2f cm\n", distance4 * 100);
        }

        if(res5 != ESP_OK)
        {
            printf("Sensor 5 - Error %d\n", res5);
        }
        else
        {
            printf("Sensor 5 - Distance: %.2f cm\n", distance5 * 100);
        }

        if(res6 != ESP_OK)
        {
            printf("Sensor 6 - Error %d\n", res6);
        }
        else
        {
            printf("Sensor 6 - Distance: %.2f cm\n", distance6 * 100);
        }

        if(res7 != ESP_OK)
        {
            printf("Sensor 7 - Error %d\n", res7);
        }
        else
        {
            printf("Sensor 7 - Distance: %.2f cm\n", distance7 * 100);
        }

        if(res8 != ESP_OK)
        {
            printf("Sensor 8 - Error %d\n", res8);
        }
        else
        {
            printf("Sensor 8 - Distance: %.2f cm\n", distance8 * 100);
        }



        vTaskDelay(pdMS_TO_TICKS(900));
    }
}

void app_main()
{    
    //function executed, name of the task, stack size * x (* arbitrary allocation size), parameter passed into task, handle for task)
    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
