#include<Servo.h>

int trigPin = 2, echoPin = 3;

int servoPin = 9, centerAngle = 90;
Servo servo;

void setup(){
    servo.attach(servoPin);
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
    while(!Serial);
}

void loop(){
    servo.write(centerAngle);

    for(int i = -30; i <= 30; i++){
        servo.write(centerAngle + i);
        delayMicroseconds(10000);

        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        double duration = pulseIn(echoPin, HIGH);
        double distance = duration * 0.0343 / 2.0;

        Serial.print(distance);
        Serial.print(" ");
        Serial.print(centerAngle + i);
        Serial.print('\n');
    }
}

