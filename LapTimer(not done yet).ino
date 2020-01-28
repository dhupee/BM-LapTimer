#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     12
#define MAX_DISTANCE 400
//#define LED          7
#define STARTSTOP    A0
#define RESET        A1

LiquidCrystal_I2C lcd(0x3F ,2,1,0,4,5,6,7,3, POSITIVE);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool trigger1 = false;
bool trigger2 = false; 

float duration, distance;
int iterations = 5;

unsigned long start, finish, dataStopWatch;
int i=0;
int fPaus = 0;
long lastButton = 0; 
long delayAntiBouncing = 50; 
long dataPause = 0;

void setup(){
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  digitalWrite(A0,1);
  digitalWrite(A1,1);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0); 
  lcd.print("BIMASAKTI UGM");
  lcd.setCursor(0, 1); 
  lcd.print("  LAP TIMER  ");
  delay(2000);
  lcd.clear();
  lcd.print("  Made by   ");
  lcd.setCursor(0, 1); 
  lcd.print(" dhupee_haj ");
  delay(2000);
  lcd.print("start/stop");
}

void loop(){

  /*  duration = sonar.ping_median(iterations);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  
  distance = (duration / 2) * 0.0343;
  
  // Send results to Serial Monitor
  Serial.print("Distance = ");
  if (distance >= 250 || distance <= 2) {
    Serial.println("STAND BY");
    lcd.print("STAND BY");
  }
  else if (distance <=150 && distance >= 2 && trigger1 = false) {
   //GAS NGITUNG STOPWATCH
   if ((millis() - lastButton) > delayAntiBouncing){
      if (i==0){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Start Timer");
          start = millis();
          fPaus = 0;
        }
       else if (i==1){
        lcd.setCursor(0, 0);
        lcd.print("Stop Timer  ");
        dataPause = dataStopWatch;
        fPaus = 1;
        }
       i =!i;
      }
      lastButton = millis();
   
  }
  else if (distance <=150 && distance >= 2 && trigger1 = false) {
  
  }
  else{
    Serial.println("STAND BY");
    lcd.print("STAND BY");
  }
  delay(500);

if (i==1){
      finish = millis(); 
      float jam, menit, detik, miliDetik;
      unsigned long over;

      // MATH time!!!
      dataStopWatch = finish - start;
      dataStopWatch = dataPause + dataStopWatch;

      jam = int(dataStopWatch / 3600000);
      over = dataStopWatch % 3600000;
      menit = int(over / 60000);
      over = over % 60000;
      detik = int(over / 1000);
      miliDetik = over % 1000;

      lcd.setCursor(0, 1);
      lcd.print(jam, 0); 
      lcd.print(":"); 
      lcd.print(menit, 0);
      lcd.print(":");
      lcd.print(detik, 0);
      lcd.print(".");
      if (jam < 10){
          lcd.print(miliDetik, 0);
          lcd.print("   ");
       }
  
}*/



//yang ini dari kode stopwatch yang pake tombol  
if (digitalRead(A0)==0){
  if ((millis() - lastButton) > delayAntiBouncing){
      if (i==0){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Start Timer");
          start = millis();
          fPaus = 0;
        }
       else if (i==1){
        lcd.setCursor(0, 0);
        lcd.print("Stop Timer  ");
        dataPause = dataStopWatch;
        fPaus = 1;
        }
       i =!i;
      }
      lastButton = millis();
  }
 else if (digitalRead(A1)==0 && fPaus == 1){
  dataStopWatch = 0;
  dataPause = 0; 
  lcd.clear();
  lcd.print("Reset Stopwatch");
  lcd.setCursor(0, 1); 
  lcd.print("0:0:0.0");  
  delay(2000);
  lcd.clear();
  lcd.print("  Tekan Tombol");
  lcd.setCursor(0, 1); 
  lcd.print("  Start / Stop");
 }
  
  if (i==1){
      finish = millis(); 
      float jam, menit, detik, miliDetik;
      unsigned long over;

      // MATH time!!!
      dataStopWatch = finish - start;
      dataStopWatch = dataPause + dataStopWatch;

      jam = int(dataStopWatch / 3600000);
      over = dataStopWatch % 3600000;
      menit = int(over / 60000);
      over = over % 60000;
      detik = int(over / 1000);
      miliDetik = over % 1000;

      lcd.setCursor(0, 1);
      lcd.print(jam, 0); 
      lcd.print(":"); 
      lcd.print(menit, 0);
      lcd.print(":");
      lcd.print(detik, 0);
      lcd.print(".");
      if (jam < 10){
          lcd.print(miliDetik, 0);
          lcd.print("   ");
       }
   }
}
