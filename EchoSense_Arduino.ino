//Here is the Arduino IDE Code for the Echosense!
//You will need to use Arduino IDE to upload it to your Arduino I will be soon uploading a Embdeed C Version for PLatfrom IO.

#define LEFT_ECHO_PIN 5
#define LEFT_TRIG_PIN 6
#define RIGHT_ECHO_PIN 11
#define RIGHT_TRIG_PIN 12

long readUltrasonicDistance(int trigPin, int echoPin) {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
long duration = pulseIn(echoPin, HIGH);
return duration * 0.034 / 2;
}

void setup() {
pinMode(LEFT_TRIG_PIN, OUTPUT);
pinMode(LEFT_ECHO_PIN, INPUT);
pinMode(RIGHT_TRIG_PIN, OUTPUT);
pinMode(RIGHT_ECHO_PIN, INPUT);

Serial.begin(9600);
}

void loop() {
long leftDistance = readUltrasonicDistance(LEFT_TRIG_PIN, LEFT_ECHO_PIN);
long rightDistance = readUltrasonicDistance(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN);

// Threshold distance to detect hand movement
const long thresholdDistance = 30;

if (leftDistance < thresholdDistance) {
Serial.println("Scroll Up");
// Add code to trigger scroll up
}

if (rightDistance < thresholdDistance) {
Serial.println("Scroll Down");
// Add code to trigger scroll down
}

delay(100); // Short delay to prevent rapid scrolling
}