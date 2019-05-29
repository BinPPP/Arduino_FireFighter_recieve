#include "Arduino.h"
#define RF_RX 5
#define RF_TX 6

const char header[] = "In MainActivity\n";

struct Gas
{
  float val;
  float upper_limit;
  float lower_limit;
  float critical_limit;
  int alarm_level;
};

union GasUnion {
  float val;
  byte b[4];
};

int headerCheck();
void init_reciever(Gas *ch4_main, Gas *ibut_main, Gas *o2_main, Gas *co_main);
void updateValuesFromBuffer();
void updateGasFromUnion();
void updateDisplayValues();
void rfListen();
int pingHeaderCheck();
void sendPingBack(char *package);
