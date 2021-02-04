#include "DHT.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 11,12, A2, A3,A4);
#define DHTTYPE DHT11 
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad
int smokeA0 = A5;
char ent_pass[5];
char pass[5]={'1','2','3','4','\0'};
int i=0;
int j=0;
int c=0;
int k=3;
int DHTPIN=10;
int q;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
DHT dht(DHTPIN, DHTTYPE);
void setup(){
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(smokeA0, INPUT);
 dht.begin();
  
  delay(100);
  lcd.begin(16,2);
  lcd.print("Home Automation");
  delay(9000);
  lcd.clear();
  
}


void ir(){
  delay(10);
  if(!digitalRead(A0)){
  lcd.clear();
  lcd.print("Theif");
  delay(10);
  lcd.setCursor(1,5);
  delay(10);
  lcd.print("is near");
  buzz();
  delay(2000);
  lcd.clear();}
  
}
void buzz(){
  digitalWrite(A1,HIGH);
  delay(2000);
  digitalWrite(A1,LOW);
  delay(2000);
  lcd.clear();
}
void temp(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  delay(200);
  
  
   if (isnan(t) || isnan(h)) {
    
    lcd.print("Can't read");
    
    
    delay(100);
    
  } else {
   
    lcd.print("Humid:");
    delay(10); 
    lcd.setCursor(2,1);
    delay(10);
    String hum=String(h);
    lcd.print(hum + " %");
    delay(2000);
    lcd.clear();
    lcd.print("Temp:"); 
    delay(10);
    String tem=String(t);
    lcd.setCursor(2,1);
    delay(10);
    lcd.print(tem+" *C");
    delay(2000);
    lcd.clear();
    
  }
  
}
void gas(){
  int analogSensor = analogRead(smokeA0);

  lcd.print("Gas conc");
  delay(10);
  String an=String(analogSensor);
  lcd.setCursor(2,1);
  delay(10);
  lcd.print(an+" ppm");
  delay(2000);
  lcd.clear();
}


void loop(){
  ir();
  
  char key = keypad.getKey();
  if ((key)&&(i<5)){
   lcd.print("*");
   
 
   
  if (key==pass[i]){
    c++;
    i++;
    if (c==4){
      delay(10);
      lcd.clear();
     
      delay(10);
      lcd.print("unlocked");
          delay(1000);
          for(q=1;q<3;q++){
          lcd.clear();
          c=0;
          i=0;
          delay(10);
          gas();
          
          delay(100);
          temp();
          
          delay(100);
          lcd.clear();}}
  }
  
  else {lcd.clear();lcd.setCursor(2,1);lcd.print("wrong password");
        if (k>0){
        lcd.clear();
        lcd.print("counts left=");
        k--;
        String k1=String(k);
        lcd.setCursor(2,1);
        lcd.print(k1);
        i=0;
        }
        else {lcd.clear();lcd.print("You are caught");
              
              k=3;
              c=0;
              buzz();
              buzz();
              buzz();}
  }
  }
  
 
}

  
