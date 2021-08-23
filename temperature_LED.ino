// Simple temperature indicator based on TM1637 LED display and thermistor.
// Original thermistor code from: Thermistor Example #3 from the Adafruit Learning System guide on Thermistors
// https://learn.adafruit.com/thermistor/overview by Limor Fried, Adafruit
// Industries MIT License - please keep attribution and consider buying parts
// from Adafruit
// connect 10K NTC thermistor between A0 and ground, connect 10K resistor between 3V3 and A0.
// connect TM637 to power/5V, connect CLK to 20 and DIO to 21.
// TM1637 library found in library manager or https://github.com/avishorp/TM1637

// which analog pin to connect
#define THERMISTORPIN A0
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000

#include <Arduino.h>
#include <TM1637Display.h>
// Module connection pins (Digital Pins)
#define CLK 20
#define DIO 21

TM1637Display display(CLK, DIO);

int samples[NUMSAMPLES];

void setup(void) {
  // initialize serial monitor and analog reference pin for thermistor
  Serial.begin(115200);
  analogReference(EXTERNAL);

  // initialize LED display with max brightness, clear display 
  display.setBrightness(0x0f);
  display.clear();
}

void loop(void) {

  // start counter and average values
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(THERMISTORPIN);
    delay(10);
  }

  // average all the samples out
  average = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
    average += samples[i];
  }
  average /= NUMSAMPLES;

  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;

  // convert resistance to temperature in celcius 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;          // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15; // convert absolute temp to C

  // print temperature in serial monitor, show temperature (decimal form) on display
  Serial.print("Ambient temperature:");
  Serial.print(steinhart);
  Serial.println(" C");
  display.showNumberDec(steinhart);

  delay(1000);
}
