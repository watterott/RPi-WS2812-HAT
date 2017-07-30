# RPi-WS2812-HAT
The examples can be compiled and uploaded using the Arduino IDE.

## Files
* [Arduino IDE](http://arduino.cc/en/Main/Software)
* [Arduino Boards Package](https://github.com/watterott/Arduino-Boards#watterott-boards-package)
* [Libraries](https://github.com/watterott/Arduino-Libs)
  * [light_WS2812](https://github.com/watterott/Arduino-Libs/tree/master/light_WS2812)
  * [TinyWire](https://github.com/watterott/Arduino-Libs/tree/master/TinyWire)
* [Examples](https://github.com/watterott/RPi-WS2812-HAT/tree/master/software)

## Installation
* Download and install the [Arduino IDE](http://arduino.cc/en/Main/Software).
* Install the [Boards Package](https://github.com/watterott/Arduino-Boards#watterott-boards-package).
* Download the [Examples](https://github.com/watterott/RPi-WS2812-HAT/archive/master.zip).
* On a Windows operating system a driver installation is needed. The drivers are included with the BSP or you can find them [here](https://github.com/watterott/Arduino-Boards/raw/master/files/micronucleus_driver.zip).

## Build and Upload
* Start the Arduino IDE.
* Open the respective Arduino Sketch ```.ino```.
* Select **ATtiny85 (16.5MHz)** under **Tools->Board**.
* Start build and upload: **File->Upload**.
* When the compiling has finished and *Uploading...* is shown, press the **reset switch** to start the bootloader.
* Wait till the upload has finished and *Done uploading* is shown.


# Raspberry Pi Examples

* Upload the ```I2C_Slave.ino``` example to the ATtiny85 on the RPi-WS2812-HAT.

* Install i2c-tools and python-smbus:

    ```
    $ sudo apt-get install i2c-tools
    $ sudo apt-get install python-smbus
    ```

* Activate I2C device:

    ```
    $ sudo modprobe i2c_bcm2708 baudrate=400000
    $ sudo modprobe i2c-dev
    ```
    Note: For a Device Tree Kernel add to ```/boot/config.txt``` the following line: ```dtparam=i2c1``` (before any dtoverlay statement).

* Test I2C bus:

    ```
    $ sudo i2cdetect -y 1
    ```

* Download and run the Python examples (```Random.py```, ```Fill.py```...):

    ```
    $ wget https://github.com/watterott/RPi-WS2812-HAT/raw/master/software/Random.py
    $ sudo python Random.py
    ```
