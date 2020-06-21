#include <SoftwareSerial.h>
#define BT_SERIAL_RX 15
#define BT_SERIAL_TX 14
#define SENSOR_PIN 0
SoftwareSerial BluetoothSerial(BT_SERIAL_RX, BT_SERIAL_TX);

const int sampleWindow = 50;
unsigned int sample;

void setup() 
{
   pinMode(SENSOR_PIN, INPUT);
   Serial.begin(9600);
   BluetoothSerial.begin(9600);
}


void loop() 
{
   unsigned long startMillis= millis();
   unsigned int peakToPeak = 0;

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(SENSOR_PIN);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;
         }
         else if (sample < signalMin)
         {
            signalMin = sample;
         }
      }
   }
   peakToPeak = signalMax - signalMin;
   double volts = (peakToPeak * 5 * (5/ 1.5)) / 1024;

   BluetoothSerial.println(volts);
   Serial.println(volts);
   delay(500);
}
