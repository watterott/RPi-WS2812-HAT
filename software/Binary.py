#!/usr/bin/python 
'''
Binary Clock for RPi-WS2812-HAT
Written by Peter Onion
Based on GameOfLife.py by Werner Ziegelwanger
'''

import time
import numpy
import math
import smbus

# Initialise Globals
bus = smbus.SMBus(1)
addr = 0x20 #default: 0x20
intensity = 10  

board = numpy.zeros((8,8), dtype=numpy.byte)
color = [intensity, intensity, intensity]


# Convert 0..59 into an RGB rainbow (used with seconds of minute as input) 
def t2rgb(t):
  if t < 10:
    r = intensity
    g = intensity * t / 10.0
    b = 0
    return [int(r),int(g),int(b)]
  t -= 10
  if t < 10:
    r = intensity * (10.0 - t) / 10.0
    g = intensity 
    b = 0
    return [int(r),int(g),int(b)]
  t -= 10
  if t < 10:
    r = 0
    g = intensity 
    b = intensity * t / 10.0
    return [int(r),int(g),int(b)]
  t -= 10
  if t < 10:
    r = 0
    g = intensity * (10.0 - t) / 10.0
    b = intensity
    return [int(r),int(g),int(b)]
  t -= 10
  if t < 10:
    r = intensity * t / 10.0
    g = 0
    b = intensity 
    return [int(r),int(g),int(b)]
  t -= 10
  if t < 10:
    r = intensity 
    g = 0
    b =  intensity * (10.0 - t) / 10.0
    return [int(r),int(g),int(b)]

  return [0,0,0]


def draw(board):
  global color
  bus.write_byte(addr, 0xFE) #write block
  for x in range(8):
    for y in range(8):
      #set pixel with color or dim background
      if board[x][y] == 1:
        bus.write_i2c_block_data(addr, color[0], [color[1], color[2]]) #red green blue
      else:
        bus.write_i2c_block_data(addr, 1, [1, 1]) # dim white
    time.sleep(0.020) #wait 20ms


def binaryTime(b):
  global color

  # Get the current time
  now = time.localtime(None)

  # Split out hours/minutes/seconds
  hr = now.tm_hour
  h = hr / 10
  r = hr % 10
  mn = now.tm_min
  m = mn / 10
  n = mn % 10
  sc = now.tm_sec
  s = sc / 10
  c = sc % 10

  color = t2rgb(sc)
  
  # Comment these out to get minutes and seconds display
  c = n
  s = m
  n = r
  m = h

  # Starting position
  x = 6
  y = 6

  # Set 2x2 blocks depending on bits in the values
  if c & 1:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if c & 2:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if c & 4:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if c & 8:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i
 
  x -= 2
  y = 6

  if s & 1:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if s & 2:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if s & 4:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if s & 8:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i
 
  x -= 2
  y = 6

  if n & 1:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if n & 2:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if n & 4:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if n & 8:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i
 
  x -= 2
  y = 6

  if m & 1:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if m & 2:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if m & 4:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i

  y -= 2

  if m & 8:
    i = 1
  else:
    i = 0
  
  b[x,y] = i
  b[x,y+1] = i
  b[x+1,y] = i
  b[x+1,y+1] = i
  return b


while True:
  binaryTime(board)
  draw(board)

  # Sleep until the next second
  now = time.time()
  (a,b) = math.modf(now)
  time.sleep(1.0 - a)
