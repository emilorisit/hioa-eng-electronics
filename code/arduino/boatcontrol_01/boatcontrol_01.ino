#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define COMMAND_READING 0x1

#define TARGET_SPEED 0x5
#define TARGET_NM_PER_LITER 0x6
#define TARGET_FUEL_CONSUMPTION 0x7
//#define INPUT_PIN A0

AndroidAccessory acc("Manufacturer",
"Project04",
"Description",
"Version",
"URI",
"Serial");

byte sntmsg[6];
int speedInKnots;
int nmPerLiter;
int fuelConsumption;

void setup() {
  Serial.begin(19200);
  acc.powerOn();






}

void loop() {
  sendSpeed();
  sendNmPerLiter();
  sendFuelConsumption();
}

void sendSpeed(){
  if (acc.isConnected()) {  
    sntmsg[0] = COMMAND_READING;
    sntmsg[1] = TARGET_SPEED;
    speedInKnots = 17.4;
    sntmsg[2] = (byte) (speedInKnots >> 24);
    sntmsg[3] = (byte) (speedInKnots >> 16);
    sntmsg[4] = (byte) (speedInKnots >> 8);
    sntmsg[5] = (byte) speedInKnots;
    acc.write(sntmsg, 6);
    delay(100);
  }
}

void sendNmPerLiter(){
  if (acc.isConnected()) {  
    sntmsg[0] = COMMAND_READING;
    sntmsg[1] = TARGET_NM_PER_LITER;
    nmPerLiter = 2.1;
    sntmsg[2] = (byte) (nmPerLiter >> 24);
    sntmsg[3] = (byte) (nmPerLiter >> 16);
    sntmsg[4] = (byte) (nmPerLiter >> 8);
    sntmsg[5] = (byte) nmPerLiter;
    acc.write(sntmsg, 6);
    delay(100);
  }
}
void sendFuelConsumption(){
  if (acc.isConnected()) {  
    sntmsg[0] = COMMAND_READING;
    sntmsg[1] = TARGET_FUEL_CONSUMPTION;
    fuelConsumption = 3.6;
    sntmsg[2] = (byte) (fuelConsumption >> 24);
    sntmsg[3] = (byte) (fuelConsumption >> 16);
    sntmsg[4] = (byte) (fuelConsumption >> 8);
    sntmsg[5] = (byte) fuelConsumption;
    acc.write(sntmsg, 6);
    delay(100);
  }
}


