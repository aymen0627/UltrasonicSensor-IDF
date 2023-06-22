# UltrasonicSensor-IDF
Practice using VS Code IDF extension w/ HCSR04 Sensor


### NOTE ###

IDF VS Code extension V1.6.2 changes baud rate automatically to 460800

To temp fix this, per IDF project, add line: ' "idf.monitorBaudRate":"115200", '
in settings.json per .vscode file.

##############################################################################

Switching from Arudiono IDE to Espressif IDF for SD2 project for more control over clock speed and overall project component applications.

This repo holds introductory ultrasonic sensor IDF launch files.


From VS Code, launch sample_project directly from esp-idf --> using command palette.

From there, use main folder and components for simple project.


# Documention and resources used:  

-UncleRus Repo:
https://github.com/UncleRus/esp-idf-lib

- UncleRus esp ultrasonic driver files:
https://esp-idf-lib.readthedocs.io/en/latest/groups/ultrasonic.html#ultrasonic-driver-for-ultrasonic-range-meters-hc-sr04-hy-srf05
