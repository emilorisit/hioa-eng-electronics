// ------------------------------ Includes for Android Communication ------------------------------ //
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

// ------------------------------ Includes for GPS ------------------------------ //
#include <TinyGPS++.h>

// ------------------------------ Defining constants ------------------------------ //
#define FUEL_SENSOR_PIN 47                      // External clock pin for timer 5
#define COMPUTER_BAUD_RATE 115200               // Serial baudrate
#define LITERS_PER_PULSE 0.0005                 // Liters per pulse from datasheet of sensor
#define GPS_BAUD_RATE 4800

#define COMMAND_ACK 0xff                    
#define COMMAND_GPS_SPEED 0x1                   // Command variable for GPS-Speed
#define COMMAND_NM_PER_LITER 0x2                // Command variable for nautical miles per liter
#define COMMAND_CONSUMED 0x3                    // Command variable for fuel consumed
#define TARGET_GPS 0xF                          // Target variable GPS
#define TARGET_FUEL 0x2F                          // Target variable fuel

// ------------------------------ Create Android Accessory ------------------------------ //
AndroidAccessory acc("Manufacturer",
"Model",
"Description",
"Version",
"URI",
"Serial");

// ------------------ Variables ------------------------//
volatile float pulses;                // Counts pulses from sensor
float litersHour;                     // Estimated liters of fuel in an hour
int count;
int sec;


// -- Fuel economy -- //
int nmPerLiter;
int speedKnots;
int fuelConsumption;

byte sntmsg[6];                      // Creates byte for sending to Arduino
byte rcvmsg[6];                      // Creates byte for sending to Arduino



TinyGPSPlus gps;                                // Creates GPS

void setup()
{
  acc.powerOn();
  Serial.begin(COMPUTER_BAUD_RATE);
  Serial3.begin(GPS_BAUD_RATE);

  // -------------- Timer 1 -------------------- //
  cli();
  TCCR1A = 0;                                                    // set entire TCCR1A register to 0
  TCCR1B = 0;                                                    // same for TCCR1B
  TCNT1  = 0;                                                    //initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;                                                // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // -------------- Timer 5 -------------------- //  
  TCCR5A = 0;                                                          // reset timer/counter control register A

  // -- Start second counter -- //
  bitSet(TCCR5B ,CS52);
  bitSet(TCCR5B ,CS51);
  bitSet(TCCR1B ,CS50); 
  bitSet(TCCR1B ,ICES5); 
  bitSet(TCCR1B ,ICNC5);

  sei();

}  
// -------------- Timer 1 interrupt -------------------- // 
ISR(TIMER1_COMPA_vect){

  sec++;
}

void loop()
{
  // Read from GPS-module and get speed in knots.
  //  while(Serial3.available() > 0){
  //   gps.encode(Serial3.read());
  // }
  // if(gps.location.isValid()){
  //   speedKnots = (int)gps.speed.knots();
  // }


  //  if (millis() > 5000 && gps.charsProcessed() < 10)
  //   Serial.println(F("No GPS data received: check wiring"));


  if(sec == 3){                                                  // Pulses the last 3 seconds, converts to an average

    sec = 0;
    pulses = TCNT5;
    TCNT5 = 0;
    litersHour = ((pulses / 3) * LITERS_PER_PULSE) * 3600;
    nmPerLiter = (int)speedKnots * litersHour;
    fuelConsumption += (pulses * LITERS_PER_PULSE);

  }
  if (acc.isConnected()) {                                      // Writing to the connected Android device

    // ------------------------------- SEND TO ANDROIDD ----------------------------------------- //
    speedKnots = 19; // Debug value, no GPS indoors
    sntmsg[0] = (byte) (COMMAND_GPS_SPEED);
    sntmsg[1] = (byte) (TARGET_GPS);
    sntmsg[2] = (byte) (speedKnots >> 24);      // Bitshifting to fit into bytes
    sntmsg[3] = (byte) (speedKnots >> 16);
    sntmsg[4] = (byte) (speedKnots >> 8);
    sntmsg[5] = (byte) speedKnots;
    Serial.println("Printer speed");
    acc.write(sntmsg, sizeof(sntmsg));
    delay(100);
    readFromAndroid();
      nmPerLiter = 5; // Debug value, no GPS indoors
    sntmsg[0] = (byte) (COMMAND_NM_PER_LITER);
    sntmsg[1] = (byte) (TARGET_GPS);
    sntmsg[2] = (byte) (nmPerLiter >> 24);      // Bitshifting to fit into bytes
    sntmsg[3] = (byte) (nmPerLiter >> 16);
    sntmsg[4] = (byte) (nmPerLiter >> 8);
    sntmsg[5] = (byte) nmPerLiter;
    Serial.println("Printer nm_per_liter");
    acc.write(sntmsg, sizeof(sntmsg));
    delay(100);
    readFromAndroid();
      fuelConsumption = 3; // Debug value, no GPS indoors
    sntmsg[0] = (byte) (COMMAND_CONSUMED);
    sntmsg[1] = (byte) (TARGET_GPS);
    sntmsg[2] = (byte) (fuelConsumption >> 24);      // Bitshifting to fit into bytes
    sntmsg[3] = (byte) (fuelConsumption >> 16);
    sntmsg[4] = (byte) (fuelConsumption >> 8);
    sntmsg[5] = (byte) fuelConsumption;
    Serial.println("Printer fuel consumption");
    acc.write(sntmsg, sizeof(sntmsg));
    readFromAndroid();




    }





}


    void readFromAndroid(){
      // ------------------------------- Read from Android ----------------------------------------- //
      int len = acc.read(rcvmsg, sizeof(rcvmsg), 1);
      if(len>0) {
        if(rcvmsg[0] == COMMAND_ACK){
          byte value = rcvmsg[2];
          Serial.print("The following value is acked: ");
          Serial.println(rcvmsg[2]);

        }
      }else{
       Serial.println("nothing from android"); 
      }
    }


