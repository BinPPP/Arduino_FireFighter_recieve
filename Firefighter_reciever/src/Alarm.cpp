#include "Reciever.h"
#include "Arduino.h"
#include "Alarm.h"

volatile int ledState;
long previousMillis = 0;
BuzzerState buzzerState;
Gas *ch4_alarm;
Gas *ibut_alarm;
Gas *o2_alarm;
Gas *co_alarm;

void init_alarm(Gas *ch4_main, Gas *ibut_main, Gas *o2_main, Gas *co_main)
{
  pinMode(LED, OUTPUT); //buzzer and led
  pinMode(buzzer, OUTPUT);
  alarmOff();
  ch4_alarm = ch4_main;
  ibut_alarm = ibut_main;
  o2_alarm = o2_main;
  co_alarm = co_main;

  ch4_alarm->lower_limit = ch4_lower_limit;
  ch4_alarm->upper_limit = ch4_upper_limit;
  ch4_alarm->critical_limit = ch4_critical_limit;
  ch4_alarm->alarm_level = def_alarm_level;

  ibut_alarm->lower_limit = ibut_lower_limit;
  ibut_alarm->upper_limit = ibut_upper_limit;
  ibut_alarm->critical_limit = ibut_critical_limit
                                   ibut_alarm->alarm_level = def_alarm_level;

  o2_alarm->lower_limit = o2_lower_limit;
  o2_alarm->upper_limit = o2_upper_limit;
  o2_alarm->critical_limit = o2_critical_limit;
  o2_alarm->alarm_level = def_alarm_level;

  co_alarm->lower_limit = co_lower_limit
                              co_alarm->upper_limit = co_upper_limit
                                                          co_alarm->critical_limit = co_critical_limit
                                                                                         co_alarm->alarm_level = def_alarm_level;

  ledState = LOW;
  alarmOff();
  pinMode(interruptPin, INPUT);                                                     //interrupt init
  attachInterrupt(digitalPinToInterrupt(interruptPin), setBuzzerStateLow, FALLING); //FALLING-PRESS and RELEASE
}

void alarmLevelUpdate(Gas *gas)
{
  if (gas->val > gas->lower_limit && gas->val < gas->upper_limit) //never getting gas->alarm_level=0
  {
    //Serial.println("gas->val");
    //Serial.println(gas->val);
    //Serial.println("gas->lower_limit");
    //Serial.println(gas->lower_limit);
    gas->alarm_level = 0;
  }
  else if (gas->val >= gas->critical_limit)
    gas->alarm_level = 2;

  else
    gas->alarm_level = 1;
}

int getHighestAlarmLevel(Gas *ch4_alarm, Gas *ibut_alarm, Gas *co_alarm, Gas *o2_alarm)
{
  int alarm_state = 0;
  if (ch4_alarm->alarm_level > alarm_state)
    alarm_state = ch4_alarm->alarm_level;
  if (ibut_alarm->alarm_level > alarm_state)
    alarm_state = ibut_alarm->alarm_level;
  if (o2_alarm->alarm_level > alarm_state)
    alarm_state = o2_alarm->alarm_level;
  if (co_alarm->alarm_level > alarm_state)
    alarm_state = co_alarm->alarm_level;
  //Serial.println("getHighestAlarmLevel");
  //Serial.println(alarm_state);
  return alarm_state;
}

void alarmOn(long interval)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis; // save the last time you blinked the LED
    //ledState = (ledState == LOW) ? HIGH : LOW;//Toggle LED state
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(LED, ledState); //write the current led state to the output
    switch (buzzerState)
    { //write the current buzzer state to the output, if buzzer state is off, buzzer is set to low
    case ON:
      digitalWrite(buzzer, ledState);
      break;
    case OFF:
      digitalWrite(buzzer, LOW);
      break;
    }
    //Serial.println("ledState is : ");
    //Serial.println(ledState);
    //Serial.println("buzzerState is :");
    //Serial.println(buzzerState);
  }
}

void alarmOff()
{
  digitalWrite(LED, LOW);
  digitalWrite(buzzer, LOW);
}

void handleAlarm()
{
  int alarm_state = getHighestAlarmLevel(ch4_alarm, ibut_alarm, co_alarm, o2_alarm);
  //Serial.println("At handle alarm");
  //Serial.println(alarm_state);
  if (alarm_state == 1)
  {
    alarmOn(200);
  }
  else if (alarm_state == 2)
  {
    alarmOn(100);
  }
  else
  {
    alarmOff();
  }
  //Serial.println(alarm_state);
}

void setBuzzerStateLow()
{
  buzzerState = OFF;
}

void setBuzzerStateHigh()
{
  buzzerState = ON;
}