int led_1 = 5;
int led_2 = 6;
int led_3 = 9;
int led_4 = 10;
int sensor_1 = 7;
int sensor_2 = 8;
int sensor_3 = 11;
int sensor_4 = 12;

int led = led_4;
int sensor = sensor_4;

  
void setup() {
  Serial.begin(9600);
  pinMode(led , OUTPUT);
  pinMode(sensor , INPUT);
}


void loop() {
  analogWrite(led , 120);
  if(digitalRead(sensor) == HIGH){
      Serial.println("Sensor is touched");
      analogWrite( led , 0);
      delay(500);
  }
}
