#include <NewPing.h>

#define TRIGGER_PIN_1  32
#define ECHO_PIN_1     26
#define TRIGGER_PIN_2  12
#define ECHO_PIN_2     27
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).
#define NUM_READINGS 10 // Number of readings to take before filtering.

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance for sensor 1.
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup of pins and maximum distance for sensor 2.

int readings1[NUM_READINGS]; // Array to hold readings for sensor 1.
int readings2[NUM_READINGS]; // Array to hold readings for sensor 2.
int index1 = 0; // Index for current reading for sensor 1.
int index2 = 0; // Index for current reading for sensor 2.

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Take a reading from each sensor.
  int distance1 = sonar1.ping_cm();
  int distance2 = sonar2.ping_cm();

  // Add the readings to the arrays.
  readings1[index1] = distance1;
  readings2[index2] = distance2;

  // Increment the current reading index for each sensor.
  index1++;
  index2++;

  // If we have taken the maximum number of readings, filter the values and print the result.
  if (index1 == NUM_READINGS && index2 == NUM_READINGS) {
    // Filter the values for sensor 1 and print the result.
    int filteredDistance1 = filterValues(readings1, NUM_READINGS);
    Serial.print("Distance from sensor 1: ");
    Serial.print(filteredDistance1);
    Serial.println(" cm");

    // Filter the values for sensor 2 and print the result.
    int filteredDistance2 = filterValues(readings2, NUM_READINGS);
    Serial.print("Distance from sensor 2: ");
    Serial.print(filteredDistance2);
    Serial.println(" cm");

    // Reset the reading index for both sensors.
    index1 = 0;
    index2 = 0;

    // Add a delay before taking the next set of readings.
    delay(100);
  }
}

int filterValues(int readings[], int numReadings) {
  // Calculate the average value of the readings.
  int total = 0;
  for (int i = 0; i < numReadings; i++) {
    total += readings[i];
  }
  int average = total / numReadings;

  // Filter out any readings that are more than 10% different from the average.
  int filteredTotal = 0;
  int filteredCount = 0;
  for (int i = 0; i < numReadings; i++) {
    if (readings[i] >= average * 0.9 && readings[i] <= average * 1.1) {
      filteredTotal += readings[i];
      filteredCount++;
    }
  }

  // Calculate the new average value based on the filtered readings.
  int filteredAverage = filteredTotal / filteredCount;

  return filteredAverage;
}
