#include<Servo.h>

// Grid will be 58 rows, 115 cols. Space between row/col is 0.0698122m

int trigPin = 2, echoPin = 3;

int servoPin = 9, centerAngle = 90;
Servo servo;

static uint64_t map_[105];
int totalShift = 0;
double distance = 0.0;

void setup(){
    servo.attach(servoPin);
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
    while(!Serial);
}

void loop(){
    servo.write(centerAngle);

    reset();

    for(int i = -30; i <= 30; i++){
        servo.write(centerAngle + i);
        delay(300);

        distance = getDist();

        if(0.02 <= distance && distance <= 4.0){
            totalShift = (57 - (int)(distance / 0.0698122 * sin((centerAngle + i) * 0.01744444444))) * 115 + (57 + (int)(distance / 0.0698122 * cos((centerAngle + i) * 0.01744444444)));
            
            if(getBit(63 - totalShift % 64, totalShift / 64) == false){
                Serial.print("Distance: ");
                Serial.print(distance);
                Serial.print('\n');

                Serial.print("Angle: ");
                Serial.print(centerAngle + i);
                Serial.print('\n');

                Serial.print("Grid Row: ");
                Serial.print(57 - (int)(distance / 0.0698122 * sin((centerAngle + i) * 0.01744444444)));
                Serial.print('\n');

                Serial.print("Grid Col: ");
                Serial.print(57 + (int)(distance / 0.0698122 * cos((centerAngle + i) * 0.01744444444)));
                Serial.print('\n');

                Serial.print("Modification Row: ");
                Serial.print(totalShift / 64);
                Serial.print('\n');

                Serial.print("Modification Index (Counting from leftmost): ");
                Serial.print(63 - totalShift % 64);
                Serial.print('\n');
                
                Serial.print("Original: ");
                printBitVersion(totalShift / 64);
                Serial.print((unsigned int)map_[totalShift / 64]);
                Serial.print('\n');

                setBit(63 - totalShift % 64, totalShift / 64, true);
                
                Serial.print("Modified: ");
                printBitVersion(totalShift / 64);
                Serial.print((int)map_[totalShift / 64]);
                Serial.print('\n');
                
                Serial.print('\n');
            }
        }

        delay(100);
    }

    clearTerm();
    display();
}

// Reset map
void reset(){
    for(int i = 0; i < 105; i++){
        map_[i] = (uint64_t) (0);
    }
}
// Get the current distance from ultrasonic
double getDist(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    double duration = pulseIn(echoPin, HIGH);

    return duration * 0.0343 / (2.0 * 100.0);
}

// Get the xth bit in the yth index of the array
bool getBit(unsigned x, unsigned y){
    return !!(map_[y] & (1 << x));
}

// Set the xth bit in the yth index of the array to v
void setBit(unsigned x, unsigned y, bool v){
    uint64_t r = map_[y];
    r &= ~(1 << x);

    r |= v << x;

    map_[y] = r;
}

// Clear terminal (bootleg way lmao)
void clearTerm(){
    for(int i = 0; i < 40; i++){
        Serial.print('\n');
    }
}

// Print out current radar
void display(){
    for(int i = 0; i < 104; i++){
        uint64_t r = map[i];
        for(int j = 0; j < 64; j++){
            if(i != 0 && j != 0 && (64 * i + j) % 115 == 0){
                Serial.print('\n');
            }

            Serial.print(getBit(j, i) == false ? '0' : '1');
        }
    }

    for(int i = 0; i < 14; i++){
        Serial.print(getBit(i, 104) == false ? '0' : '1');
    }
    Serial.print('\n');
}

// Print out binary version of a number
void printBitVersion(uint64_t x){
    for(int i = 63; i >= 0; i--){
        Serial.print(getBit(i, x) ? '1' : '0');
    }
    Serial.print('\n');
}