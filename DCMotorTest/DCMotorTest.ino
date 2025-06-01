int motorPin = 3;

int minimum(int a, int b){
    return (a < b) ? a : b;
}

void setup() {
    pinMode(motorPin, OUTPUT);
    Serial.begin(9600);
    while (!Serial);
    Serial.print("Speed 0 to 255 \n");
}

int currentspeed = 0;

void loop() {
    if (Serial.available()) {
        int speed = Serial.parseInt();

        if(0 < speed && speed < 256 && currentspeed != speed && speed != 0){
            currentspeed = speed;
        }

        Serial.print(speed);
        Serial.print(" | ");
        Serial.print(currentspeed);
        Serial.print("\n");

        analogWrite(motorPin, currentspeed);
    }
}