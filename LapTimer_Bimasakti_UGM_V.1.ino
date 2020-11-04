/*  THIS CODE IS FOR FSAE ULtrasonic LapTimer
 *  
 *        created by dhupee_haj 
 *        
 *  This Code is originally intented for helping my time calculate time on FSAE car testing
 *  but I decided that maybe its a good idea to share this knowledge to everybody.
 * 
 *  This project use HC-SR04 Ultrasonic Sensor for detecting car
 *  
 *  This project is not limited to FSAE car, you can use this for another froject that need lap timing
 *  also its not limited to this spesific application
 *  
*/




#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIGGER_PIN  7      //make trigger pin and echo pin parallel
#define ECHO_PIN     7      //make trigger pin and echo pin parallel
#define MAX_DISTANCE 400    //max distance of the sensor is 400 cm
#define START_BUTTON 2
#define PAUSE_STOP_BUTTON 3

LiquidCrystal_I2C lcd(0x3F ,2,1,0,4,5,6,7,3, POSITIVE);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

unsigned long start, finish, dataStopWatch;
int  i=0;
int  fPaus = 0;
long lastButton = 0; 
long delayAntiBouncing = 50; 
long dataPaus = 0;
const int RelayRed = 8;
const int RelayGreen = 9;
const int Buzzer = 10;
bool startTrig = false;

float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
int iterations = 5;

void setup(){

  Serial.begin(9600);
  pinMode(START_BUTTON,INPUT_PULLUP);     // start/stop button pinmode
  pinMode(PAUSE_STOP_BUTTON,INPUT_PULLUP);     // reset button pinmode
  pinMode(RelayRed ,OUTPUT);    // RelayRed output pinmode
  pinMode(RelayGreen ,OUTPUT);  // RelayGreen output 
  
  digitalWrite(RelayRed, HIGH);
  digitalWrite(RelayGreen, HIGH);
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0); 
  lcd.print("BIMASAKTI UGM");
  lcd.setCursor(0, 1); 
  lcd.print(" BY: DHUPEE  ");
  delay(2000);
  lcd.clear();
  lcd.print("  Select");
  lcd.setCursor(0, 1); 
  lcd.print("  Start / Stop");
}

void loop(){

duration = sonar.ping_median(iterations); 
distance = (duration / 2) * 0.0343;       //measure distance in cm
Serial.print("Distance=");
Serial.println(distance);
  
if ((digitalRead(START_BUTTON)==0) || (distance <=150 && distance >= 5 && startTrig == true)){
  if ((millis() - lastButton) > delayAntiBouncing){
      if (i==0){
          startTrig = true;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Stand By.");
          digitalWrite(RelayRed, LOW);
          digitalWrite(RelayGreen, HIGH);
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Stand By..");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Stand By...");
          delay(1000);
          digitalWrite(RelayRed, HIGH);
          digitalWrite(RelayGreen, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Start Timer");
          start = millis();
          fPaus = 0;
          Serial.println("START!");
        }
       else if (i==1){
        startTrig = false;
        lcd.setCursor(0, 0);
        lcd.print("Stop Timer  ");
        dataPaus = dataStopWatch;
        fPaus = 1;
        digitalWrite(RelayRed, HIGH);
        digitalWrite(RelayGreen, HIGH);
        Serial.println("PAUSE!");
        }
       i =!i;
      }
      lastButton = millis();
  }
 else if (digitalRead(PAUSE_STOP_BUTTON)==0 && fPaus == 1){
  dataStopWatch = 0;
  dataPaus = 0; 
  lcd.clear();
  lcd.print("Reset Stopwatch");
  lcd.setCursor(0, 1); 
  lcd.print("0:0:0.0");  
  delay(2000);
  lcd.clear();
  lcd.print("  Select");
  lcd.setCursor(0, 1); 
  lcd.print("  Start / Stop");
 }
  
  if (i==1){
      finish = millis(); 
      float hour, minute, second, milisecond;
      unsigned long over;

      // MATH time!!!
      dataStopWatch = finish - start;
      dataStopWatch = dataPaus + dataStopWatch;

      hour = int(dataStopWatch / 3600000);
      over = dataStopWatch % 3600000;
      minute = int(over / 60000);
      over = over % 60000;
      second = int(over / 1000);
      milisecond = over % 1000;

      lcd.setCursor(0, 1);
      lcd.print(hour, 0); 
      lcd.print(":"); 
      lcd.print(minute, 0);
      lcd.print(":");
      lcd.print(second, 0);
      lcd.print(".");
      if (hour < 10){
          lcd.print(milisecond, 0);
          lcd.print("   ");
       }
   }
}
