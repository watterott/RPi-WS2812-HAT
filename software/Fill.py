#!/usr/bin/python 

import time
import smbus

bus = smbus.SMBus(1)
addr = 0x20 #default: 0x20
intensity = 50 #0...255

#fade on leds
for i in range(intensity):
  bus.write_byte(addr, 0xFE) #write block
  for x in range(8):
    for y in range(8):
      bus.write_i2c_block_data(addr, 0, [0, i]) #red green blue
    time.sleep(0.05) #wait 5ms
