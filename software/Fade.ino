/*
  RPi-WS2812-HAT Fade Example
 */

#include <WS2812.h>

#define DATAPIN     1 //digital output pin (data input of LEDs)
#define LEDCOUNT   64 //number of LEDs to drive
#define INTENSITY 100 //light intensity

WS2812 LED(LEDCOUNT);

byte intensity=0;
byte sign=1;

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

  if(sign)
  {
    intensity++;
    if(intensity == INTENSITY)
    {
      sign = 0;
    }
  }
  else
  {
    intensity--;
    if(intensity == 0)
    {
      sign = 1;
    }
  }

  for(byte i=0; i < LEDCOUNT; i++)
  {
    if((i % 3) == 0) //first LED, and every third after that
    {
      value.r = intensity;
      value.g = 0; 
      value.b = 0; 
      LED.set_crgb_at(i, value);
    }
    else if((i % 3) == 1) //second LED, and every third after that
    { 
      value.r = 0;
      value.g = intensity; 
      value.b = 0; 
      LED.set_crgb_at(i, value);
    }
    else //third LED, and every third after that
    {
      value.r = 0;
      value.g = 0; 
      value.b = intensity; 
      LED.set_crgb_at(i, value);
    }
  }

  LED.sync(); //send the values to the LEDs
  delay(10); //wait 10ms
}
