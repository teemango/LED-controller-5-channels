/* 
Code adapted from that for two channels by Tim Perkins
(Support thread:http://www.ultimatereef.net/threads/need-easy-simple-two-channel-arduino-led-controller.816975)
*/

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

// You need to set these to the pins you will use
const int const_RB1_pin  = 5;
const int const_RB2_pin = 6;
const int const_TB_pin = 9;
const int const_NW_pin = 10;
const int const_Lime_pin = 11;
const int const_fan_pin   = 7;

unsigned int current_time = 0;
byte fade_duration = 0;
byte RB1_target_PWM = 0;
byte RB1_actual_PWM = 0;
byte RB2_target_PWM = 0;
byte RB2_actual_PWM = 0;
byte TB_target_PWM = 0;
byte TB_actual_PWM = 0;
byte NW_target_PWM = 0;
byte NW_actual_PWM = 0;
byte Lime_target_PWM = 0;
byte Lime_actual_PWM = 0;
byte now_HH = 0;
byte now_MM = 0;
byte now_SS = 0;

void setup() {
  // don't need serial unless you have it hooked to your PC
  Serial.begin(115200);
  Wire.begin();
  delay(10000);
  // Time the Time function to use the RTC
  setSyncProvider(RTC.get);
  // Time the Time function to sync with the RTC every minute
  setSyncInterval(60);
  // This can be useful for checking if things aren't working!
   if (timeStatus() != timeSet) {
       Serial.println("Unable to sync with the RTC");
   } else {
       Serial.println("RTC has set the system time");
   }
  pinMode(const_RB1_pin, OUTPUT);
  pinMode(const_RB2_pin, OUTPUT);
  pinMode(const_TB_pin, OUTPUT);
  pinMode(const_NW_pin, OUTPUT);
  pinMode(const_Lime_pin, OUTPUT);
  pinMode(const_fan_pin, OUTPUT);
}
void loop() {
  // Convert the time into a usable number - 8:15 am is 815, ten thirty pm is 2230
  current_time = (hour() * 100) + minute();
  if (current_time >= 2030) {
    RB1_target_PWM = 0;
    RB2_target_PWM = 0;
    TB_target_PWM = 0;
    NW_target_PWM = 0;
    Lime_target_PWM = 0;
    fade_duration = 90;   
  } else if (current_time >= 1400) {
    RB1_target_PWM = 110;
    RB2_target_PWM = 110;
    TB_target_PWM = 100;
    NW_target_PWM = 60;
    Lime_target_PWM = 70;
    fade_duration = 40;  
  } else if (current_time >= 1100) {
    RB1_target_PWM = 25;
    RB2_target_PWM = 25;
    TB_target_PWM = 10;
    NW_target_PWM = 0;
    Lime_target_PWM = 10;
    fade_duration = 30;    
  } else if (current_time >= 900) {
    RB1_target_PWM = 30;
    RB2_target_PWM = 0;
    TB_target_PWM = 0;
    NW_target_PWM = 0;
    Lime_target_PWM = 0;
    fade_duration = 60;
  }
  if ((RB1_actual_PWM != RB1_target_PWM) ||
      (RB2_actual_PWM != RB2_target_PWM) ||
      (TB_actual_PWM != TB_target_PWM) ||
      (NW_actual_PWM != NW_target_PWM) ||
      (Lime_actual_PWM != Lime_target_PWM)) {
    fade_LEDs();
  }
}

void fade_LEDs() {
  unsigned long wait_time;
  unsigned long fade_start_millis;
  int i = 0;
  int j = 0;
  
  // which color has further to fade in the time? 
  // I did not know how to adapt this block of code with five instead of two channels, so just chose my two royal blue channels,
  // since they are on all the time; am certainly open to suggestions on how to properly handle more than two channels,
  // but this code has been working well for years on my reef tank
  i = RB1_actual_PWM - RB1_target_PWM;
  j = RB2_actual_PWM - RB2_target_PWM;
  
  // if the lights are dimming, the value of i/j will be negative - just get the number & ignore the sign
  i = abs(i);
  j = abs(j);
    
  Serial.print("i");  Serial.print(i);
  Serial.print(" j=");
  Serial.println(j);
  // convert fade_duration into milliseconds
  if (i > j) {
    wait_time = (fade_duration * 60000) / i;
  } else {
    wait_time = (fade_duration * 60000) / j;
  
  }
  fade_start_millis = millis();
  Serial.print("Wait=");
  Serial.println(wait_time);
  while ((RB1_actual_PWM != RB1_target_PWM) ||
         (RB2_actual_PWM != RB2_target_PWM) ||
         (TB_actual_PWM != TB_target_PWM) ||
         (NW_actual_PWM != NW_target_PWM) ||
         (Lime_actual_PWM != Lime_target_PWM)) {    
    
    if (wait_time <= (millis() - fade_start_millis)) {
      if (RB1_target_PWM > RB1_actual_PWM) {
        RB1_actual_PWM += 1; 
      } else if (RB1_target_PWM < RB1_actual_PWM) {
        RB1_actual_PWM -= 1;
      }
      if (RB2_target_PWM > RB2_actual_PWM) {
        RB2_actual_PWM += 1;
      } else if (RB2_target_PWM < RB2_actual_PWM) {
        RB2_actual_PWM -= 1;
      }
      if (TB_target_PWM > TB_actual_PWM) {
        TB_actual_PWM += 1;
      } else if (TB_target_PWM < TB_actual_PWM) {
        TB_actual_PWM -= 1;
      }
      if (NW_target_PWM > NW_actual_PWM) {
        NW_actual_PWM += 1;
      } else if (NW_target_PWM < NW_actual_PWM) {
        NW_actual_PWM -= 1;
      }
      if (Lime_target_PWM > Lime_actual_PWM) {
        Lime_actual_PWM += 1;
      } else if (Lime_target_PWM < Lime_actual_PWM) {
        Lime_actual_PWM -= 1;
      }
      analogWrite(const_RB1_pin, RB1_actual_PWM);
      analogWrite(const_RB2_pin, RB2_actual_PWM);
      analogWrite(const_TB_pin, TB_actual_PWM);
      analogWrite(const_NW_pin, NW_actual_PWM);
      analogWrite(const_Lime_pin, Lime_actual_PWM);
      fade_start_millis = millis();
      now_HH = hour();
      now_MM = minute();
      now_SS = second();
      Serial.print("Time ");
      Serial.print(now_HH);
      Serial.print(":");
      if (now_MM < 10) {
        Serial.print("0");}
      Serial.print(now_MM);
      Serial.print(":");
      if (now_SS < 10) {
        Serial.print("0     ");}
      Serial.print(now_SS);
      Serial.print(" RB1 actual ");
      Serial.print(RB1_actual_PWM);
      Serial.print(" RB2 actual ");
      Serial.println(RB2_actual_PWM);
      Serial.print(" TB actual ");
      Serial.print(TB_actual_PWM);
      Serial.print(" NW actual ");
      Serial.print(NW_actual_PWM);
      Serial.print(" Lime actual ");
      Serial.print(Lime_actual_PWM);
    }
    // 128 is 25% of both lights on full so if the total exceeds this turn fans on
    if (int(RB1_actual_PWM + RB2_actual_PWM) >= 128) {
      digitalWrite(const_fan_pin, HIGH);
    } else {
      digitalWrite(const_fan_pin, LOW);
    }
 }
}
