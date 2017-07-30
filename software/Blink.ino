/*
  RPi-WS2812-HAT Blink Example
 */

#include <WS2812.h>

#define DATAPIN     1 //digital output pin (data input of LEDs)
#define LEDCOUNT   64 //number of LEDs to drive
#define INTENSITY 100 //light intensity

WS2812 LED(LEDCOUNT);

void setup()
{
  //init LEDs
  LED.setOutput(DATAPIN);
  //LED.setColorOrderRGB(); //uncomment for RGB color order
  //LED.setColorOrderBRG(); //uncomment for BRG color order
  LED.setColorOrderGRB(); //ucomment for GRB color order (default)
}

void loop()
{
  cRGB value;

  value.r = INTENSITY; value.g = 0; value.b = 0; //red
  for(byte i=0; i < LEDCOUNT; i++){ LED.set_crgb_at(i, value); } //set value to LEDs
  LED.sync(); //send the values to the LEDs
  delay(1000); //wait 1s

  value.r = 0; value.g = INTENSITY; value.b = 0; //green
  for(byte i=0; i < LEDCOUNT; i++){ LED.set_crgb_at(i, value); } //set value to LEDs
  LED.sync(); //send the values to the LEDs
  delay(1000); //wait 1s

  value.r = 0; value.g = 0; value.b = INTENSITY; //blue
  for(byte i=0; i < LEDCOUNT; i++){ LED.set_crgb_at(i, value); } //set value to LEDs
  LED.sync(); //send the values to the LEDs
  delay(1000); //wait 1s

  value.r = INTENSITY; value.g = INTENSITY; value.b = INTENSITY; //white
  for(byte i=0; i < LEDCOUNT; i++){ LED.set_crgb_at(i, value); } //set value to LEDs
  LED.sync(); //send the values to the LEDs
  delay(1000); //wait 1s
}
