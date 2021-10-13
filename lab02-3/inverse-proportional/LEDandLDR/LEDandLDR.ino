int ldrPin = A0;
int ldrReading = 0;
int ledPin = 3;
int ledBrightness = 0;

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldrReading = analogRead(ldrPin);
  Serial.print("Analog reading = ");
  Serial.println(ldrReading);
  //invert value so that LED gets dimmer, not brighter
  ldrReading = 1023 - ldrReading;
  //map 0-1023 to 0-255 range for analogWrite()
  ledBrightness = map(ldrReading, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);

  delay(100);
}
