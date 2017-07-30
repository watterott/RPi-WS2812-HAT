/*
  RPi-WS2812-HAT I2C Slave Example
  
  I2C Address: 0x20
  
  Data:
    Set one LED at 0...63
      [0...63] [rrr] [ggg] [bbb]
    Set all LEDs (64 LEDs x 24bit color)
      [254] [rrr] [ggg] [bbb] ... [rrr] [ggg] [bbb]
    Set all LEDs off
      [255]
 */

#include <WS2812.h>
#include <TinyWireS.h>

#define I2C_SLAVE_ADDR 0x20 //7-bit address

#define DATAPIN     1 //digital output pin (data input of LEDs)
#define LEDCOUNT   64 //number of LEDs to drive
#define INTENSITY 100 //light intensity

WS2812 LED(LEDCOUNT);

volatile byte state=0, sync=0;
volatile unsigned long counter=0;

void reset(void)
{
  //flush buffers
  TinyWireS.begin(I2C_SLAVE_ADDR); 

  state = 0;
  sync  = 0;

  //switch off LEDs
  for(byte i=0; i < LEDCOUNT; i++)
  {
    cRGB value = {0,0,0};
    LED.set_crgb_at(i, value);
  }
  LED.sync();
}

void requestEvent()
{  
  TinyWireS.send(0x00); //return 0
}

void receiveEvent(uint8_t size)
{
  byte r, s;
  static cRGB color;
  static byte led_pos=0, block=0;

  counter = 0;

  if(size > 32) //buffer overflow, TWI_RX_BUFFER_SIZE=32
  {
    reset();
    return;
  }

  s = state;
  while(size)
  {
    r = TinyWireS.receive();
    size--;
    if(s == 0) //new block
    {
      if(r == 0xFF) //clear
      {
        for(byte i=0; i < LEDCOUNT; i++)
        {
          cRGB value = {0,0,0};
          LED.set_crgb_at(i, value);
        }
        sync = 1;
      }
      if(r == 0xFE) //receive LEDCOUNT
      {
        s++;
        led_pos = 0;
        block   = 1;
      }
      else if(r < LEDCOUNT)
      {
        s++;
        led_pos = r;
        block   = 0;
      }
    }
    else if(s == 1) //red value
    {
      s++;
      color.r = r;
    }
    else if(s == 2) //green value
    {
      s++;
      color.g = r;
    }
    else if(s == 3) //blue value
    {
      color.b = r;
      LED.set_crgb_at(led_pos++, color);
      if(led_pos >= LEDCOUNT)
      {
        led_pos = 0;
        s       = 0;
        sync    = 1;
      }
      else if(block != 0)
      {
        s = 1;
      }
      else
      {
        s    = 0;
        sync = 1;
      }
    }
  }
  state = s;
}

void setup()
{
  //init LEDs
  LED.setOutput(DATAPIN);
  //LED.setColorOrderRGB(); //uncomment for RGB color order
  //LED.setColorOrderBRG(); //uncomment for BRG color order
  LED.setColorOrderGRB(); //ucomment for GRB color order (default)

  //init I2C
  TinyWireS.begin(I2C_SLAVE_ADDR);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);

  //switch off LEDs
  reset();

  //disable all timer interrupts (needed to work with RPi)
  TIMSK = 0;
}

void loop()
{
  TinyWireS_stop_check();

  if(sync != 0)
  {
    sync = 0;
    LED.sync();
  }

  if(state != 0) //receiving data
  {
    if(++counter > 150000) //reset I2C after 150000 loops of no data (about 1s)
    {
      counter = 0;
      state   = 0;
      sync    = 1;
      //reset();
    }
  }
}
