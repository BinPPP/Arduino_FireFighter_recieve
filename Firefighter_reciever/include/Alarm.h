#define LED 13
#define buzzer 2
#define interruptPin 3

#define ch4_upper_limit 10.0f
#define ch4_lower_limit 0.00f
#define ch4_critical_limit 20.00f;
#define def_alarm_level 0;
  
#define ibut_upper_limit 100.0f;
#define  ibut_lower_limit 0.00f;
#define  ibut_critical_limit 200.00f;

  //o2 init
#define  o2_upper_limit 23.00f;
#define  o2_lower_limit 19.00f;
#define  o2_critical_limit 23.00f;

  //co init
#define  co_upper_limit 20.0f;
#define  co_lower_limit  0.00f;
#define  co_critical_limit 100.00f;


enum BuzzerState {ON, OFF};


void init_alarm(Gas* ch4_main,Gas*  ibut_main,Gas* o2_main,Gas* co_main);
void alarmLevelUpdate( Gas * gas);
int getHighestAlarmLevel(Gas ch4,Gas ibut,Gas co,Gas o2);
void alarmOn(long interval);
void alarmOff();
void setBuzzerStateLow();
void setBuzzerStateHigh();
void handleAlarm();

