#!/usr/bin/python 

import time
import smbus
from random import randint

bus = smbus.SMBus(1)
addr = 0x20 #default: 0x20
intensity = 50 #0...255

#switch off leds
bus.write_byte(addr, 0xFF)
time.sleep(0.100) #wait 100ms

#switch on random leds
while True:
  x = randint(0, 63)
  r = randint(0, intensity)
  g = randint(0, intensity)
  b = randint(0, intensity)
  bus.write_i2c_block_data(addr, x, [r, g, b]) #led red green blue
  time.sleep(0.100) #wait 100ms
