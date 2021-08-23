# temperature_LED_display
Simple temperature indicator based on TM1637 LED display and thermistor.
Original thermistor code from: Thermistor Example #3 from the Adafruit Learning System guide on Thermistors
https://learn.adafruit.com/thermistor/overview by Limor Fried, Adafruit
Industries MIT License - please keep attribution and consider buying parts
from Adafruit

Usage instructions:

  connect 10K NTC thermistor between A0 and ground, connect 10K resistor between 3V3 and A0.
  connect TM637 to power/5V, connect CLK to 20 and DIO to 21.
  TM1637 library found in library manager or https://github.com/avishorp/TM1637
