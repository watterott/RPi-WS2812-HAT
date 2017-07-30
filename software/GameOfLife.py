#!/usr/bin/python 
'''
Game Of Live for RPi-WS2812-HAT
originally written by Werner Ziegelwanger
http://developer-blog.net/hardware/raspberrypi/raspberry-pi-game-life/
'''

import time
import random
import numpy
import smbus

bus = smbus.SMBus(1)
addr = 0x20 #default: 0x20
intensity = 50 #0...255

board = numpy.zeros((8,8), dtype=numpy.byte)
color = [intensity, intensity, 0]

def initialize(board):
  #initialize random number generator
  random.seed(time.time())
  #loop board
  for y in range(8):
    for x in range(8):
      #set element randomized
      rand = random.randint(0,1)
      board[x][y] = rand

def draw(board):
  bus.write_byte(addr, 0xFE) #write block
  for x in range(8):
    for y in range(8):
      #set pixel with color or unset it
      if board[x][y] == 1:
        bus.write_i2c_block_data(addr, color[0], [color[1], color[2]]) #red green blue
      else:
        bus.write_i2c_block_data(addr, 0, [0, 0]) #red green blue
    time.sleep(0.020) #wait 20ms

def compute(board):
  #game of live logic
  xmax, ymax = board.shape
  b = board.copy()
  for x in range(xmax):
    for y in range(ymax):
      n = numpy.sum(board[max(x - 1, 0):min(x + 2, xmax), max(y - 1, 0):min(y + 2, ymax)]) - board[x, y]
      if board[x, y]:
        if n < 2 or n > 3:
          b[x, y] = 0
        elif n == 3:
          b[x, y] = 1
  return b

initialize(board)
while True:
  draw(board)
  board = compute(board)
  time.sleep(1.5)
