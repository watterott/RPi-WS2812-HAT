/*
  RPi-WS2812-HAT Game Of Life Demonstration
 */

#include <WS2812.h>

#define DATAPIN     1 //digital output pin (data input of LEDs)
#define LEDCOUNT   64 //number of LEDs to drive
#define INTENSITY 100 //light intensity

WS2812 LED(LEDCOUNT);

cRGB drawcolor[5] = {{  0,  0, INTENSITY/1},  //alive
                     {  0,  0,           0},  //dead
                     {  0,  0, INTENSITY/8},  //die1
                     {  0,  0, INTENSITY/4},  //die2
                     {  0,  0, INTENSITY/2}}; //die3
#define ALIVE_COLOR (0)
#define DEAD_COLOR  (1)
#define DIE1_COLOR  (2)
#define DIE2_COLOR  (3)
#define DIE3_COLOR  (4)

#define X_SIZE      (8)   //cell width
#define Y_SIZE      (8)   //cell height
uint8_t frame[X_SIZE][Y_SIZE];

#define DEL_CELL    (4)
#define ON_CELL     (0xAA)
#define NEW_CELL    (0xFF)

uint8_t alive(uint8_t x, uint8_t y)
{
  if((x < X_SIZE) && (y < Y_SIZE))
  {
    if((frame[x][y] == ON_CELL) || (frame[x][y] == NEW_CELL))
    {
      return 1;
    }
  }

  return 0;
}

uint8_t neighbors(uint8_t x, uint8_t y)
{
  uint8_t count=0;

  //3 above
  if(alive(x-1,y-1)){ count++; }
  if(alive(x,  y-1)){ count++; }
  if(alive(x+1,y-1)){ count++; }

  //2 on each side
  if(alive(x-1,  y)){ count++; }
  if(alive(x+1,  y)){ count++; }

  //3 below
  if(alive(x-1,y+1)){ count++; }
  if(alive(x  ,y+1)){ count++; }
  if(alive(x+1,y+1)){ count++; }

  return count;
}

uint8_t play_gol(void)
{
  uint8_t x, y, count, same=1;

  //update cells
  for(x=0; x < X_SIZE; x++)
  {
    for(y=0; y < Y_SIZE; y++)
    {
      count = neighbors(x, y);
      if((count == 3) && !alive(x, y))
      {
        frame[x][y] = NEW_CELL; //new cell
        same = 0;
      }
      if(((count < 2) || (count > 3)) && alive(x, y))
      {
        frame[x][y] = DEL_CELL; //cell dies
        same = 0;
      }
    }
  }

  return same;
}

void draw_gol(void)
{
  uint8_t c, x, y, color;

  for(x=0; x < X_SIZE; x++)
  {
    for(y=0; y < Y_SIZE; y++)
    {
      c = frame[x][y];
      color = DEAD_COLOR;
      if(c && (c != ON_CELL))
      {
        if(c == NEW_CELL) //new
        {
          frame[x][y] = ON_CELL;
          color = ALIVE_COLOR;
        }
        else if(c == 1) //del
        {
          frame[x][y]--;
          color = DEAD_COLOR;
        }
        else if(c == 2) //die
        {
          frame[x][y]--;
          color = DIE1_COLOR;
        }
        else if(c == 3) //die
        {
          frame[x][y]--;
          color = DIE2_COLOR;
        }
        else if(c <= DEL_CELL) //die
        {
          frame[x][y]--;
          color = DIE3_COLOR;
        }
      }
      LED.set_crgb_at((x*X_SIZE)+y, drawcolor[color]);
    }
  }
  LED.sync(); //send the values to the LEDs
}

void init_gol(void)
{
  uint8_t x, y;
  uint16_t c;

  //generate random start data
  srand(rand() + frame[X_SIZE/2][Y_SIZE/2]); //+ analogRead(2)
  for(x=0; x < X_SIZE; x++)
  {
    c = (rand() | (rand()<<1)) & 0xAAAA; //0xAAAA 0x3333 0xA924A
    for(y=0; y < Y_SIZE; y++)
    {
      if(c & (1<<y))
      {
        frame[x][y] = NEW_CELL;
      }
      else
      {
        frame[x][y] = 0;
      }
    }
  }
}

void setup()
{
  //init LEDs
  LED.setOutput(DATAPIN);
  //LED.setColorOrderRGB(); //uncomment for RGB color order
  //LED.setColorOrderBRG(); //uncomment for BRG color order
  LED.setColorOrderGRB(); //ucomment for GRB color order (default)

  //init gol
  init_gol();
}


void loop()
{
  uint32_t m;
  static uint32_t prevMillis=0;
  static uint8_t same=0;

  m = millis();
  if((m - prevMillis) >= 100) //update every 100ms (10Hz)
  {
    prevMillis = m;

    if(play_gol()) //no generation change
    {
      if(++same > 10) //no change since 10 runs-> restart
      {
        same = 0;
        init_gol();
      }
    }
    else
    {
      same = 0;
    }
    
    draw_gol();
  }
}
