int trigPin = 2, echoPin = 3;

void setup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
    while(!Serial);
}

void loop(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    double duration = pulseIn(echoPin, HIGH);
    double distance = duration * 0.0343 / 2.0;

    Serial.print(distance);
    Serial.print('\n');
}