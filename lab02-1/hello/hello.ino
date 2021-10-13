bool firstRun = 0;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); 
}

void loop() {

  if(firstRun==0)
  {
    delay(2000);
    Serial.println("QUESTION 315");
    Serial.println("Have you ever engaged in any activity which might indicate that you may"); 
    Serial.println("not be considered to be a person of good character?");
    firstRun = 1;
  }
 if(Serial.available()) 
 {
   String answer = Serial.readString();
   Serial.print(answer);
   answer.trim();
   if(answer=="No." || answer=="No" || answer=="no." || answer=="no")
   {
    wait();
    Serial.println("APPLICATION UPDATE");
    Serial.println("Your visa application has been successful."); //NEVER ACCEPTED? LOL
   }
   else
   {
    wait();
    Serial.println("APPLICATION UPDATE");
    Serial.println("Your visa application has been rejected.");
   }
 }
}

void wait() 
{
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.println(".");
  delay(1000);
}
