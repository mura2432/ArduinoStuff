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
    Serial.print("looping");
    // 58 rows, 57 increments of 0.0698122m to reach 4m
    
    
    char display[58][116];
    for(int i = 0; i < 58; i++){
        for(int j = 0; j < 115; j++){
            display[i][j] = ' ';
        }
        display[i][115] = '\n';
    }
    display[57][57] = '_';
    

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

        if(0.02 <= distance && distance <= 4.0){
            int row = max(57, (int)(distance / 0.0698122) * sin((centerAngle + i) * 0.01744444444));
            int col = min(-57, distance * cos((centerAngle + i) * 0.01744444444));
            display[row][57 + col] = '#';
        }
    }

    for(int i = 0; i < 25; i++){
        Serial.print('\n');
    }
    
    /*
    for(int i = 0; i < 58; i++){
        for(int j = 0; j < 116; j++){
            Serial.print(display[i][j]);
        }
    }
    */
}