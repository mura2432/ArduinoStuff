#include<Servo.h>

int trigPin = 2, echoPin = 3;

int servoPin = 9, centerAngle = 90;
Servo servo;

unsigned char bitmap[834];
int currbit = 0, checkbit = 0;
unsigned char c, checker;

void setup(){
    servo.attach(servoPin);
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
    while(!Serial);
}

void loop(){
    // Serial.print("looping");
    // 58 rows, 57 increments of 0.0698122m to reach 4m
    
    for(int i = 0; i < 834; i++){
        bitmap[i] = '00000000';
    }

    servo.write(centerAngle);

    for(int i = -30; i <= 30; i++){
        servo.write(centerAngle + i);
        delay(300);

        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        double duration = pulseIn(echoPin, HIGH);
        //100 is to convert cm to m
        double distance = duration * 0.0343 / (2.0 * 100.0);

        /*
        Serial.print(distance);
        Serial.print('\n');
        */

        if(0.02 <= distance && distance <= 4.0){
            int row = 57 - (int)(distance / 0.0698122 * sin((centerAngle + i) * 0.01744444444));
            int col = 57 + (int)(distance / 0.0698122 * cos((centerAngle + i) * 0.01744444444));
            
            /*
            Serial.print(row);
            Serial.print('\n');
            Serial.print(col);
            Serial.print('\n');
            Serial.print('\n');
            */

            // unsighed char goes to 2^8 (0 to 255), 8 bits
            // 2^7 + 2^6 + 2^5 + 2^4 + 2^3 + 2^2 + 2^1 + 2^0
            
            checker = bitmap[(row * 57 + col) / 8];
            for(int i = 0; i < 8 - (row * 57 + col) % 8; i++){
                checkbit = (checker & (1 << i)) != 0;
            }
            
            if(!checkbit){
                Serial.print("New Location Marked");
                Serial.print('\n');

                Serial.print("Row: ");
                Serial.print(row);
                Serial.print('\n');

                Serial.print("Col: ");
                Serial.print(col);
                Serial.print('\n');
                
                Serial.print("Old Bits: ");
                printBits(bitmap[(row * 57 + col)]);
                Serial.print('\n');

                bitmap[(row * 57 + col) / 8] += pow(2, 7 - (row * 57 + col) % 8);

                Serial.print("New Bits: ");
                printBits(bitmap[(row * 57 + col)]);
                Serial.print('\n');

                Serial.print("Corrected Bit: ");
                Serial.print(7 - (row * 57 + col) % 8);
                Serial.print('\n');

                Serial.print('\n');
            }
        }

        delay(100);
    }

    for(int i = 0; i < 40; i++){
        Serial.print('\n');
    }
    
    for(int i = 0; i < 833; i++){
        c = bitmap[i];
        for(int j = 0; j < 8; j++){
            if((i * 8 + j) % 115 == 0 && i != 0){
                Serial.print('\n');
            }

            currbit = (c & (1 << i)) != 0;        
            Serial.print(currbit);

        }
    }

    c = bitmap[833];
    for(int i = 0; i < 6; i++){
        currbit = (c & (1 << i)) != 0;
        Serial.print(currbit);
    }
    Serial.print('\n');

    /*
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
    */
}

void printBits(unsigned char toprint){
    for(int i = 0; i < 8; i++){
        Serial.print((toprint & (1 << i)) != 0);
    }
}