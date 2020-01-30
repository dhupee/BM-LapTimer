//THIS CODE IS FOR FL LapTimer
//created by dhupee_haj

#include <Wire.h>               //include Wire library
#include <LiquidCrystal_I2C.h>  //include LiquidCrystal_I2C library from fmalpartida
#include <NewPing.h>            //include NewPing library
//#include <DHT.h>                //include DHT Libraries from Adafruit


//#define DHTPIN 6              // DHT-22 Output Pin connection
//#define DHTTYPE DHT11         // DHT Type
#define TRIGGER_PIN  12         //make trigger pin and echo pin parallel
#define ECHO_PIN     12         //make trigger pin and echo pin parallel
#define MAX_DISTANCE 400        //max distance of the sensor is 400 cm
//#define LED          7
#define STARTSTOP    A0         //define start/stop button
#define RESET        A1         //define reset button

LiquidCrystal_I2C lcd(0x3F ,2,1,0,4,5,6,7,3, POSITIVE); //check your i2c lcd address before connect

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

bool  FLtrigger = false;   //FL = Finish Line
bool  sector1   = false;
//bool  sector2   = false; //just use if you need multisector laptimer
//bool  sector3   = false; //just use if you need multisector laptimer
//bool  sector4   = false; //just use if you need multisector laptimer 

//float hum;    // Stores humidity value in percent
//float temp;   // Stores temperature value in Celcius
//float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
//float soundsp;  // Stores calculated speed of sound in M/S
//float soundcm;  // Stores calculated speed of sound in cm/ms
int   iterations = 7;

unsigned long start, finish, dataStopWatch;

int  i=0;
int  fPause = 0;
long lastButton = 0; 
long delayAntiBouncing = 50; 
long dataPause = 0;

void setup(){
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  digitalWrite(A0,1);
  digitalWrite(A1,1);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);        // Opening screen :3
  lcd.print("BIMASAKTI UGM");
  lcd.setCursor(0, 1); 
  lcd.print("  LAP TIMER  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Made by   ");
  lcd.setCursor(0, 1);
  lcd.print(" dhupee_haj  "); //THAT'S ME !!
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Press Button");
  lcd.setCursor(0, 1); 
  lcd.print("  Start / Stop");
}

void loop(){

  /*delay(2000);                     // Delay so DHT-22 sensor can stabalize
    hum = dht.readHumidity();     // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);  // Calculate the Speed of Sound in M/S
    soundcm = soundsp / 10000;                          // Convert to cm/ms
    duration = sonar.ping_median(iterations);
    distance = (duration / 2) * soundcm;                  // Calculate the distance
  */

   duration = sonar.ping_median(iterations); 
   distance = (duration / 2) * 0.00343;   //use this if not use dht compensator
  
 if ((distance <=150 && distance >= 2 && FLtrigger == false) || digitalRead(A0)==0) { //if ultrasonic trigger object or start/stop button pressed then STOPWATCH START!!
   if ((millis() - lastButton) > delayAntiBouncing){
      if (i==0){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Start Timer");
          start = millis();
          fPause = 0;
          FLtrigger = true;
          //give data message to another MCU with NRF24 for start stopwatch
        }
       else if (i==1){
          lcd.setCursor(0, 0);
          lcd.print("Stop Timer  ");
          dataPause = dataStopWatch;
          fPause = 1;
          //give data message to another MCU with NRF24 for stop stopwatch
        }
       i =!i;
      }
      lastButton = millis();
  }
  
  // else if (another MCU trigger object after this MCU trigger then stopwatch triggered) {}
  
   else if (digitalRead(A1)==0 && fPause == 1){
      dataStopWatch = 0;
      dataPause = 0;
      FLtrigger = false; 
      lcd.clear();
      lcd.print("Reset Stopwatch");
      lcd.setCursor(0, 1); 
      lcd.print("0:0:0.0");  
      delay(2000);
      lcd.clear();
      lcd.print("  Press Button");
      lcd.setCursor(0, 1); 
      lcd.print("  Start / Stop");
 }

if (i==1){
      finish = millis(); 
      float hour, minute, second, milisecond;
      unsigned long over;

      // MATH time!!!
      dataStopWatch = finish - start;
      dataStopWatch = dataPause + dataStopWatch;

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
