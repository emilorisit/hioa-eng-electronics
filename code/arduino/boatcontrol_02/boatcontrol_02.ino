// ------------------------------ Includes for ADK/USB ------------------------------ //
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

// ------------------------------ Includes for GPS ------------------------------ //
#include <TinyGPS++.h>

// ------------------------------ Defining constants ------------------------------ //
#define FUEL_SENSOR_PIN 47                      // External clock pin for timer 5
#define BATTERY_ONE_PIN A0
#define BATTERY_TWO_PIN A1
#define RELAY_PIN 2
#define COMPUTER_BAUD_RATE 115200               // Serial baudrate
#define FUEL_TANK_SIZE 25
#define GPS_BAUD_RATE 4800
#define COMMAND_READING 0x1
#define COMMAND 0x3
#define TARGET_SPEED 0x5
#define TARGET_NM_PER_LITER 0x6
#define TARGET_FUEL_CONSUMPTION 0x7
#define TARGET_RELAY_PIN 0x2
#define TARGET_BATTERY_ONE_PIN 0x8
#define TARGET_BATTERY_TWO_PIN 0x9

// Identifying the accessory for the Android unit
AndroidAccessory acc("Manufacturer",
"Project04",
"Description",
"Version",
"URI",
"Serial");

// ------------------ Variables ------------------------//
volatile float pulses;                // Counts pulses from sensor
float litersHour;                     // Estimated liters of fuel in an hour
int count;
int sec;
float liters_per_pulse = 0.0005 ;     // Liters per pulse from datasheet of sensor

int currentADCValue;

byte sntmsg[6];
byte rcvmsg[3];
int speedInKnots = 7;
float nmPerLiterFloat;
float  fuelConsumptionFloat;
float fuelRemainingFloat;
int distanceRemaining;

TinyGPSPlus gps;                      // Creates GPS

void setup() {
  Serial.begin(COMPUTER_BAUD_RATE);
  Serial3.begin(GPS_BAUD_RATE);
  acc.powerOn();
  pinMode(RELAY_PIN, OUTPUT);

  // -------------- Timer 1 -------------------- //
  cli();
  TCCR1A = 0;                                                     // set entire TCCR1A register to 0
  TCCR1B = 0;                                                     // same for TCCR1B
  TCNT1  = 0;                                                     // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;                                                                    
  TCCR1B |= (1 << WGM12);                                         // turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);                            // Set CS10 and CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);                                       // enable timer compare interrupt
  // -------------- Timer 5 -------------------- //               // Used to measure fuel flow
  TCCR5A = 0;                                                     // reset timer/counter control register A
  bitSet(TCCR5B ,CS52);                                           // 52, 51 and 50 enabling external clock source on rising edge
  bitSet(TCCR5B ,CS51);
  bitSet(TCCR5B ,CS50); 
  bitSet(TCCR5B ,ICES5);                                          // Input capture edge select
  bitSet(TCCR5B ,ICNC5);                                          // Input capture noice canceler
  sei();

}

// -------------- Timer 1 interrupt -------------------- // 
ISR(TIMER1_COMPA_vect){
  sec++;
}

void loop() {

  // Read from GPS-module and get speed in knots.
  if(Serial3.available() > 0){
  }
  if(gps.location.isValid()){
    speedInKnots = (int)gps.speed.knots();
  }

  if (millis() > 5000 && gps.charsProcessed() < 10){
    Serial.println("No GPS data received: check wiring");
  }

  if(sec == 3){                                                 // Pulses the last 3 seconds, converts to an average
    sec = 0;
    pulses = TCNT5;
    TCNT5 = 0;
    litersHour = ((pulses / 3) * liters_per_pulse) * 3600;
    nmPerLiterFloat = speedInKnots/litersHour;
    fuelConsumptionFloat += (pulses * liters_per_pulse);
    fuelRemainingFloat = FUEL_TANK_SIZE - fuelConsumptionFloat;
    distanceRemaining = (int)fuelRemainingFloat * nmPerLiterFloat;
  }  

  currentADCValue = analogRead(BATTERY_ONE_PIN);
  sendSpeed();
  sendNmPerLiter();
  sendFuelConsumption();
  sendVoltageBatOne();
  readCommand();  

} // LOOP

// ------------------------- Methodes --------------------- //
void sendSpeed(){
  if (acc.isConnected()) {                            // Checks to find Android, then sets up byte array
    sntmsg[0] = COMMAND_READING;                      // based on bitshifting
    sntmsg[1] = TARGET_SPEED;
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
    int nmPerLiter = (int)nmPerLiterFloat;
    sntmsg[0] = COMMAND_READING;
    sntmsg[1] = TARGET_NM_PER_LITER;
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
    int fuelRemaining = (int)fuelRemainingFloat;
    sntmsg[0] = COMMAND_READING;
    sntmsg[1] = TARGET_FUEL_CONSUMPTION;
    sntmsg[2] = (byte) (fuelRemaining >> 24);
    sntmsg[3] = (byte) (fuelRemaining >> 16);
    sntmsg[4] = (byte) (fuelRemaining >> 8);
    sntmsg[5] = (byte) fuelRemaining;
    acc.write(sntmsg, 6);
    delay(100);
  }
}
void sendVoltageBatOne(){
  if (acc.isConnected()) {  
    int voltageMeasured = (int)getCurrentVoltage(currentADCValue)*10; // Multiple by 10 to get decimal after bitshift
    sntmsg[0] = COMMAND_READING;
    sntmsg[1] = TARGET_BATTERY_ONE_PIN;
    sntmsg[2] = (byte) (voltageMeasured >> 24);
    sntmsg[3] = (byte) (voltageMeasured >> 16);
    sntmsg[4] = (byte) (voltageMeasured >> 8);
    sntmsg[5] = (byte) voltageMeasured;
    acc.write(sntmsg, 6);
    delay(100);
  }
}

// Produces a command for the relay, based on a byte array from Android
void readCommand(){
  if (acc.isConnected()) {  
    int rcvlen = acc.read(rcvmsg, sizeof(rcvmsg), 1);
    if (rcvlen > 0){
      if (rcvmsg[0] == COMMAND){
        if ( rcvmsg[1] == TARGET_RELAY_PIN){
          byte value = rcvmsg[2];
          if (value == 0x1){
            digitalWrite(RELAY_PIN, HIGH);
          }
          else if(value == 0x0){
            digitalWrite(RELAY_PIN, LOW);
          }
        }
      } 
    }
    delay(100);
  }
}

// Calculates the voltage from the analog reading
float getCurrentVoltage(int currentADCValue){
  return 5 * currentADCValue / 1024;
}











