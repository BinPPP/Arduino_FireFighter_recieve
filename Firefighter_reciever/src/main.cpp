#include <Arduino.h>
#include"Reciever.h"
#include"Display.h"
#include"Alarm.h"

Gas ch4_m, ibut_m, o2_m, co_m;
void setup() {
  
  ch4_m = {10.0f,0.00f,20.00f,0};//ch4 structure init
  ibut_m= {100.0f,0.00f,200.00f,0};//ibut init
  o2_m={23.00f,19.00f,23.00f,0}; //o2 init
  co_m= {20.0f,0.00f,100.00f,0}; //co init
  init_reciever(&ch4_m,&ibut_m,&o2_m,&co_m);
  init_display();
  init_alarm(&ch4_m,&ibut_m,&o2_m,&co_m);
}

void loop() {
  rfListen();
  handleAlarm();
}