# Frequently Asked Questions

## How much power does the LED-Matrix need?
The Matrix consists of 64 RGB LEDs and each LED needs about 60mA (3 * 20mA) at full brightness.
Therefore the maximum current is 64 * 0.06A = 3.8A.


## How is the ATtiny85 connected to the RPi?
The ATtiny85 is connected via SDA+SCL (I2C) to the Raspberry Pi.


## Can the Raspberry Pi control the WS2812 LEDs directly?
For direct control of the WS2812 LEDs from the Raspberry Pi have a look at the examples from: [626Pilot](https://github.com/626Pilot/RaspberryPi-NeoPixel-WS2812) and [jgarff](https://github.com/jgarff/rpi_ws281x).
The jumper next to the reset switch has to be closed to position 18.
Then the data input of the first WS2812 LED is connected to GPIO18 of the Raspberry Pi.


## How to flash/update the ID EEPROM?
The EEPROM on the HAT can be updated as follows.
Before the update the **WP** jumper next to the EEPROM has to be closed.

* Install [EEPROM utils](https://github.com/raspberrypi/hats/tree/master/eepromutils):
    ```
    $ git clone --depth=1 https://github.com/raspberrypi/hats
    $ cd hats/eepromutils
    $ make
    $ chmod +x eepflash.sh
    ```

* Generate EEPROM data:
    ```
    $ wget https://github.com/watterott/RPi-WS2812-HAT/raw/master/docs/rpi-ws2812-hat.txt
    $ ./eepmake rpi-ws2812-hat.txt rpi-ws2812-hat.eep
    ```

* Update/Flash EEPROM:
    ```
    $ sudo ./eepflash.sh -w -t=24c32 -f=rpi-ws2812-hat.eep
    ```
    Note: For a Device Tree Kernel add to ```/boot/config.txt``` the following line before flashing: ```dtparam=i2c0=on``` (before any dtoverlay statement).
