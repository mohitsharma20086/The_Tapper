void setup() {
  Serial.begin(9600);
  pinMode(2 , INPUT);
  pinMode(13 , INPUT);

}

void loop() {
  if(digitalRead(2) != LOW){
    Serial.println("on");
    if(digitalRead(13) != LOW){
      Serial.println("not low");
    }
    if(digitalRead(13) == LOW){
       Serial.println("low");
    }
  }
  else if(digitalRead(2)== LOW){
    Serial.println("off");
    delay(100);
  }
}
