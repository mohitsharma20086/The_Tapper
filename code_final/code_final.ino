// in between change krna h game ko
// start end time ka difference 50 mili se jyada ho
// else wala part kaise hoga reee
// sequence[count] != sequence[count-1] isme check kr konsa on h 

#include <TM1637Display.h>


#define CLK 3
#define DIO 4

TM1637Display display = TM1637Display(CLK, DIO);
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};


#define led_1 5
#define led_2 6
#define led_3 9
#define led_4 10
#define sensor_1 7
#define sensor_2 8
#define sensor_3 11
#define sensor_4 12
#define tonePin A1

#define on_off 2
#define game_option 13

int delay_upper = 1800;
int delay_lower = 1500;

int delay_game_2 = 800;

int total_c = 3;
int sequence[3];

int score = 0;

void setup() {
  pinMode(led_1 , OUTPUT);
  pinMode(led_2 , OUTPUT);
  pinMode(led_3 , OUTPUT);
  pinMode(led_4 , OUTPUT);
  pinMode(sensor_1 , INPUT);
  pinMode(sensor_2 , INPUT);
  pinMode(sensor_3 , INPUT);
  pinMode(sensor_4 , INPUT);
  pinMode(game_option, INPUT);
  pinMode(on_off, INPUT);

  pinMode(2, INPUT);
  pinMode(1, INPUT);
  
  display.clear();
  display.setBrightness(3);
  
  Serial.begin(9600);
  randomSeed(4);    
}


void loop() {
  if(digitalRead(on_off) != LOW){
    if(digitalRead(game_option) != LOW){
      game2();
    }
    if(digitalRead(game_option) == LOW){
      game1();
    }
  }
}


// game1 code start here 

void game1(){
  intitalize();
  while(1){
    if(digitalRead(on_off) != LOW){
      if(digitalRead(game_option) != LOW){
        game2();
        return;
      }
    }
    int randnumber = random(4)+1;
    if(randnumber == 1){
      tapping(sensor_1, led_1, sensor_2, sensor_3, sensor_4);
    }
    else if(randnumber == 2){
      tapping(sensor_2, led_2, sensor_1, sensor_3, sensor_4);
    }
     else if(randnumber == 3){
      tapping(sensor_3, led_3, sensor_1, sensor_2, sensor_4);
    }
     else if(randnumber == 4){
      tapping(sensor_4, led_4, sensor_1, sensor_2, sensor_3);
    }
    delay(random(delay_lower, delay_upper));
    }
}


void tapping(int touch_switch, int led_light, int other_1 , int other_2, int other_3) { 
  analogWrite(led_light , 120);
  int wait = random(900, 1800);
  long st = millis(); 

  while(millis() -  st < wait ){
    if(digitalRead(other_1) == HIGH || digitalRead(other_2) == HIGH || digitalRead(other_3) == HIGH ){
      Serial.println("Wrong Sensor is touched");
      score = score - 2;
      analogWrite( led_light , 0);
      if(score < 0 ){
        score = 0;
      }
      printScore();
      wrongtap();
      return;
    }
    if(digitalRead(touch_switch) == HIGH){
      Serial.println("Sensor is touched");
      analogWrite( led_light , 0);
      score = score+1;
      printScore();
      righttap();
      return;
    }
  }
  if( delay_lower >= 1000){
    delay_lower = delay_lower - 70;
  }
  else if( delay_lower >= 500){
    delay_lower = delay_lower - 50;
  }
  if( delay_upper >= 1300){
    delay_upper = delay_upper - 70;
  }
  else if( delay_upper >= 700){
    delay_upper = delay_upper - 50;
  }
  score = score - 2;
  analogWrite( led_light , 0);
  if(score < 0 ){
    score = 0;
  }
  printScore();
  wrongtap();
  delay(500);
}

// game1 code ends here


// game2 code start here

void game2(){
  intitalize();
  delay(2000);
  while(1){
    if(digitalRead(on_off) != LOW){
      if(digitalRead(game_option) == LOW){
        game1();
        return;
      }
    }
    printScore();
    int t = random(4)+1;
    sequence[0]= t;
    int count = 1;
    while(count < total_c){
      t = random(4)+1;
      if( t != sequence[count-1]){
      sequence[count]= t;
      count++;
      }
    }
    display_sequence();
    check_sequence();
  }
}



void display_sequence(){
  for(int i=0;i<total_c;i++){
    if (sequence[i]==1){
       analogWrite(led_1 , 120);
       delay(delay_game_2);
       analogWrite( led_1 , 0);
    }
    else if(sequence[i]==2){
       analogWrite(led_2 , 120);
       delay(delay_game_2);
       analogWrite( led_2 , 0);
    }
      else if(sequence[i]==3){
       analogWrite(led_3 , 120);
       delay(delay_game_2);
       analogWrite( led_3 , 0);
    }
     else if(sequence[i]==4){
       analogWrite(led_4 , 120);
       delay(delay_game_2);
       analogWrite( led_4 , 0);
    }
  }
}

void check_sequence(){
  int wait = 500; 
  int count=0;
  int old_1 = 0, new_1 = 0;
  int old_2 = 0, new_2 = 0;
  int old_3 = 0, new_3 = 0;
  int old_4 = 0, new_4 = 0;
  long st = millis()+100;
  while(count< total_c){
    if(digitalRead(on_off) != LOW){
      if(digitalRead(game_option) == LOW){
        game1();
        return;
      }
    }
    int temp = 0;
    old_1 = new_1; new_1 = digitalRead(sensor_1);
    int old_2 = new_2; new_2 = digitalRead(sensor_2);
    int old_3 = new_3; new_3 = digitalRead(sensor_3);
    int old_4 = new_2; new_4 = digitalRead(sensor_4);
    if(new_1 == HIGH ){
      temp++;
    }
    if(new_2 == HIGH ){
      temp++;
    }
    if(new_3 == HIGH ){
      temp++;
    }
    if(new_4 == HIGH ){
      temp++;
    }
    if(temp == 1){
      if(new_1 == HIGH && millis() -  st < wait && new_1 == old_1){
        continue;
      }
      if(new_2 == HIGH && millis() -  st < wait && new_2 == old_2 ){
        continue;
      }
      if(new_3 == HIGH && millis() -  st < wait && new_3 == old_3){
        continue;
      }
      if(new_4 == HIGH && millis() -  st < wait && new_4 == old_4 ){
        continue;
      }
      if(digitalRead(sensor_1) == HIGH && sequence[count]==1 && (digitalRead(sensor_2) == LOW || digitalRead(sensor_3) == LOW || digitalRead(sensor_4) == LOW)){
        Serial.println("Sensor 1 is touched");
        count++;
        score = score+1;
        printScore();
        righttap();
        st = millis();
        continue;
      }
      else if(digitalRead(sensor_2) == HIGH && sequence[count]==2 && (digitalRead(sensor_1) == LOW || digitalRead(sensor_3) == LOW || digitalRead(sensor_4) == LOW)){
        Serial.println("Sensor 2 is touched");
        count++;
        score = score+1;
        printScore();
        righttap();
        st = millis();
        continue;
      }
      else if(digitalRead(sensor_3) == HIGH && sequence[count]==3 && (digitalRead(sensor_1) == LOW || digitalRead(sensor_2) == LOW || digitalRead(sensor_4) == LOW)){
        Serial.println("Sensor 3 is touched");
        count++;
        score = score+1;
        printScore();
        righttap();
        st = millis();
        continue;
      }
      else if(digitalRead(sensor_4) == HIGH && sequence[count]==4 && (digitalRead(sensor_1) == LOW || digitalRead(sensor_2) == LOW || digitalRead(sensor_3) == LOW)){
        Serial.println("Sensor 4 is touched");
        count++;
        score = score+1;
        printScore();
        righttap();
        st = millis();
        continue;
      }
      else {
        score = score - 5;
        if(score < 0 ){
          score = 0;
        }
        printScore();
        wrongtap();
        delay(500);
        return;
    }
    }
    
  }
  if( delay_game_2 > 700){
    delay_game_2 = delay_lower - 70;
  }
  else if( delay_lower >= 450){
    delay_lower = delay_lower - 50;
  }
  else if( delay_lower >= 250){
    delay_lower = delay_lower - 30;
  }
}


//game2 code ends here



// play some sound and light show at the start of the game
void intitalize(){
  display.setSegments(data);
  start();
  start_light_show();
  score = 0;
  printScore();
  
}

void printScore(){
  display.showNumberDec(score);
}

void righttap() {
    tone(tonePin, 700, 474.999625);
    delay(116.66625);
    tone(tonePin, 900, 249.99975);
    delay(277.7775);
}

void wrongtap() {
    tone(tonePin, 493, 249.99975);
    delay(150.7775);
    tone(tonePin, 659, 174.999625);
    delay(316.66625);
}


void start() {
    tone(tonePin, 195, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 261, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 329, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 391, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 523, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 659, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 783, 294.7591125);
    delay(327.510125);
    delay(17.237375);
    tone(tonePin, 659, 294.7591125);
    delay(327.510125);
    delay(17.237375);
    tone(tonePin, 207, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 261, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 311, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 415, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 523, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 622, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 830, 294.7591125);
    delay(327.510125);
    delay(17.237375);
    tone(tonePin, 622, 294.7591125);
    delay(327.510125);
    delay(17.237375);
    tone(tonePin, 233, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 293, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 349, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 466, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 587, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 698, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 932, 294.7591125);
    delay(327.510125);
    delay(17.237375);
    tone(tonePin, 932, 98.2530375);
    delay(109.170041667);
    delay(5.02756770833);
    tone(tonePin, 932, 98.2530375);
    delay(109.170041667);
    delay(5.74579166667);
    tone(tonePin, 932, 97.6066359375);
    delay(108.451817708);
    delay(7.18223958333);
    tone(tonePin, 659, 294.7591125);
    delay(327.510125);

}


void start_light_show(){
  analogWrite(led_1 , 120);
  delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 120);
  delay(100);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 120);
  delay(100);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 120);
  delay(100); 
  analogWrite(led_1 , 120);
  delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 120);
  delay(100);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 120);
  delay(100);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 120);
  delay(100);   
  analogWrite(led_4 , 0);
  analogWrite(led_1 , 120);
  delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 120);
  delay(100);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 120);
  delay(100);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 120);
  delay(100);   
  analogWrite(led_4 , 0);
  analogWrite(led_1 , 120);
  delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 120);
  delay(100);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 120);
  delay(100);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 120);
  delay(100);   
  analogWrite(led_4 , 0);
    delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 120);
  delay(100);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 120);
  delay(100);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 120);
  delay(100);   
  analogWrite(led_4 , 0);
  analogWrite(led_1 , 120);
  delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 120);
  delay(100);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 120);
  delay(100);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 120);
  delay(100);   
  analogWrite(led_4 , 0);
  delay(100);
  analogWrite(led_1 , 120);
  analogWrite(led_2 , 120);
  analogWrite(led_3 , 120);
  analogWrite(led_4 , 120);
  delay(100);
  analogWrite(led_1 , 0);
  analogWrite(led_2 , 0);
  analogWrite(led_3 , 0);
  analogWrite(led_4 , 0);
}
