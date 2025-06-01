#include<Servo.h>

int trigPin = 2, echoPin = 3;

int servoPin = 9, centerAngle = 90;
Servo servo;

unsigned char bitmap[834];
int currbit = 0;
unsigned char c;

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
    
    for(int i = 0; i < 834; i++){
        bitmap[i] = '\0';
    }

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
            int row = 57 - (int)(distance / 0.0698122 * sin((centerAngle + i) * 0.01744444444));
            int col = 57 + (int)(distance / 0.0698122 * cos((centerAngle + i) * 0.01744444444));
            bitmap[(row * 57 + col) / 8] += pow(2, 7 - (row * 57 + col) % 8) - 1;
        }
    }

    for(int i = 0; i < 25; i++){
        Serial.print('\n');
    }
    
    for(int i = 0; i < 833; i++){
        c = bitmap[i];
        for(int j = 0; j < 8; j++){
            currbit = (c & (1 << i)) != 0;
            if(currbit){
                Serial.print('#');
            }else{
                Serial.print('0xE8');
            }
        }
        Serial.print('\n');
    }
}