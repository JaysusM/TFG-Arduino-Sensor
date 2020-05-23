#include <SoftwareSerial.h>
#define BT_SERIAL_RX 15
#define BT_SERIAL_TX 14
SoftwareSerial BluetoothSerial(BT_SERIAL_RX, BT_SERIAL_TX);

const int sampleWindow = 50;
unsigned int sample;

void setup() 
{
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
      sample = analogRead(0);
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
   double volts = (peakToPeak * 5.0) / 1024;

   BluetoothSerial.println(volts);
   delay(2000);
}