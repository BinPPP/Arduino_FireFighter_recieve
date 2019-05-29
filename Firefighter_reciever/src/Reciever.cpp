#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "Reciever.h"
#include "Display.h"
#include "Alarm.h"

SoftwareSerial mySerial(RF_RX, RF_TX); // RX, TX

byte gasValues[50];

char pingHeader[2] = {'f', 'u'};

Gas *ch4 = NULL;
Gas *ibut = NULL;
Gas *o2 = NULL;
Gas *co = NULL;
GasUnion ch4Union, ibutUnion, o2Union, coUnion;

void init_reciever(Gas *ch4_main, Gas *ibut_main, Gas *o2_main, Gas *co_main)
{
  Serial.begin(9600);
  mySerial.begin(9600);
  ch4 = ch4_main;
  ibut = ibut_main;
  o2 = o2_main;
  co = co_main;
}

void updateValuesFromBuffer()
{
  for (int i = 0; i < 4; i++)
  {
    ch4Union.b[3 - i] = gasValues[i + 16];
    ibutUnion.b[3 - i] = gasValues[i + 4 + 16];
    o2Union.b[3 - i] = gasValues[i + 8 + 16];
    coUnion.b[3 - i] = gasValues[i + 12 + 16];
  }
}

void updateGasFromUnion()
{
  ch4->val = ch4Union.val;
  ibut->val = ibutUnion.val;
  o2->val = o2Union.val;
  co->val = coUnion.val;
}

void rfListen()
{
  if (mySerial.available() > 1) //Read from HC-12 and put in buffer gasValues
  {
    mySerial.readBytes(gasValues, 50);

    if (headerCheck())
    {
      Serial.println("incoming message"); //debugging
      updateValuesFromBuffer();           //update values to the structs
      updateGasFromUnion();               //update the gas struct val

      alarmLevelUpdate(ch4); //update individual alarm level
      alarmLevelUpdate(ibut);
      alarmLevelUpdate(o2);
      alarmLevelUpdate(co);

      Serial.println("alarm is set to : ");
      //Serial.println(getHighestAlarmLevel(ch4, ibut, co, o2));
      Serial.println(ch4Union.val);
      Serial.println(ibutUnion.val);
      Serial.println(o2Union.val);
      Serial.println(coUnion.val);

      updateDisplayValues();
      setBuzzerStateHigh();
    }
    else if (pingHeaderCheck())
    {
      sendPingBack(pingHeader);
      Serial.print("ping recieved");
    }
  }
  //sendPingBack(pingHeader);
  //Serial.print("ping recieved");
}

void updateDisplayValues() //update all four lines in this function and print all four lines on LCD
{
  updateDisplayLine(ch4->val, 0);
  updateDisplayLine(ibut->val, 1);
  updateDisplayLine(o2->val, 2);
  updateDisplayLine(co->val, 3);
}

int headerCheck()
{
  //char header[] = "In MainActivity\n";
  for (int i = 0; i < 8; i++)
  {
    //Serial.print("header:");
    //Serial.println(header[i]);
    //Serial.print("gasValue:");
    //Serial.println((char)gasValues[i]);
    if (header[i] == (char)gasValues[i])
    {
      continue;
    }
    else
    {
      return 0;
    }
  }
  return 1;
  /*if (strncmp(header, (char *)gasValues, 8) == 0)
    return 1;
  else
    return 0;*/
}

int pingHeaderCheck()
{
  for (int i = 0; i < 2; i++)
  {
    if ((char)gasValues[i] != pingHeader[i])
    {
      return 0;
    }
  }
  return 1;
}

void sendPingBack(char *package)
{

  int i = mySerial.write((byte *)package, 2);
  Serial.println(i);
  mySerial.flush();
}
