// The Embedded C Version for Platform IO, Remember to define your board and Upload Port in the platformio.ini and Which is found under TEST.


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <Arduino> 

// Define pin numbers
#define LEFT_ECHO_PIN   5
#define LEFT_TRIG_PIN   6
#define RIGHT_ECHO_PIN  11
#define RIGHT_TRIG_PIN  12

// Replace with actual GPIO and UART functions from your platform
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, bool value);
uint32_t pulseIn(uint8_t pin, bool state);
void delayMicroseconds(uint32_t us);
void delay(uint32_t ms);
void Serial_begin(uint32_t baudrate);
void Serial_println(const char* str);

// Read distance using ultrasonic sensor
uint32_t readUltrasonicDistance(uint8_t trigPin, uint8_t echoPin) {
    digitalWrite(trigPin, false);
    delayMicroseconds(2);
    digitalWrite(trigPin, true);
    delayMicroseconds(10);
    digitalWrite(trigPin, false);

    uint32_t duration = pulseIn(echoPin, true);
    return (uint32_t)(duration * 0.034 / 2); // distance in cm
}

// Setup function
void setup() {
    pinMode(LEFT_TRIG_PIN, 1);   // OUTPUT
    pinMode(LEFT_ECHO_PIN, 0);   // INPUT
    pinMode(RIGHT_TRIG_PIN, 1);  // OUTPUT
    pinMode(RIGHT_ECHO_PIN, 0);  // INPUT

    Serial_begin(9600);
}

// Main loop
void loop() {
    uint32_t leftDistance = readUltrasonicDistance(LEFT_TRIG_PIN, LEFT_ECHO_PIN);
    uint32_t rightDistance = readUltrasonicDistance(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN);

    const uint32_t thresholdDistance = 30;

    if (leftDistance < thresholdDistance) {
        Serial_println("Scroll Up");
        // Add code to trigger scroll up
    }

    if (rightDistance < thresholdDistance) {
        Serial_println("Scroll Down");
        // Add code to trigger scroll down
    }

    delay(100); // Delay in ms
}

// Entry point
int main(void) {
    setup();
    while (1) {
        loop();
    }
}
