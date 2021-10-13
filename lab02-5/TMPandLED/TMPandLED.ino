int sensorPin = A0;
int LEDpin = 13;
int reading = 0;
float voltage = 0;
float currentTemp = 0.0;
float referenceTemp = NULL;
float tolerance = NULL;
float deviation = 0.0;
bool firstRun = 0;
bool secondRun = 0;
String answer = "0.0";

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  //IF FIRST RUN, ASK FOR REFERENCE TEMP
  if(firstRun==0)
  {
    delay(2000);
    Serial.println("Please enter reference temperature.");
    firstRun = 1;
  }
  
  //IF SECOND RUN AND REFERENCE TEMP IS INITIALIZED, ASK FOR TOLERANCE
  if(firstRun==1 && secondRun==0 && referenceTemp!=NULL)
  {
    Serial.println("Please enter tolerance margin.");
    secondRun = 1;
  }

  //STORE SERIAL INPUT AS FLOAT
  if(Serial.available())
  {
    if(secondRun==0)
    {
      answer = Serial.readString();
      answer.trim();
      referenceTemp = answer.toFloat();
      Serial.print("Reference temperature = ");
      Serial.println(referenceTemp);
    }
    else
    {
      answer = Serial.readString();
      answer.trim();
      tolerance = answer.toFloat();
      Serial.print("Tolerance margin = ");
      Serial.println(tolerance);
    }
  }

  //IF REFERENCE TEMP AND TOLERANCE ARE INITIALIZED
  if(referenceTemp!=NULL && tolerance!=NULL)
  {
    //READ AND DISPLAY VOLTAGE AND CURRENT TEMPERATURE
    reading = analogRead(sensorPin);
    //Serial.print("Analog input: ");
    //Serial.println(reading);
    voltage = reading * 5.0;
    voltage /= 1024.0;
    //Serial.print(voltage);
    //Serial.print(" volts, ");
    currentTemp = (voltage - 0.5) * 100;
    Serial.print(currentTemp);
    Serial.println(" °C");
    
    //IF CURRENT VALUE IS OUTSIDE TOLERANCE MARGIN
    deviation = referenceTemp - currentTemp;
    deviation = abs(deviation);
    //Serial.println(deviation);
    if(deviation > tolerance)
    {
      //BLINK LED
      digitalWrite(LEDpin, HIGH);
      delay(500);
      digitalWrite(LEDpin, LOW);
      delay(500);
    }
    else
    {
      digitalWrite(LEDpin, LOW);
      delay(1000);
    }
  }
}
