# rcmix

The LXRobotics P20 RC Mixer is a device which can mix up to 4 standard RC PWM inputs (pulse period 20 ms, pulse duration 1-2 ms) to up to 6 standard RC PWM outputs applying any used definable control algorithm.

![LXRobotics P20 RCMix](https://www.lxrobotics.com/wp-content/uploads/mz_product_page_rcmix_side_small.jpg)

## Installation

* Install the Arduino IDE

```
sudo apt-get install arduino
```
* Clone this repository

```
git clone https://github.com/lxrobotics/rcmix.git
```

## Building

* Open project in Arduino IDE by left clicking on `rcmixarduino.ino`

* Select ATMega32U4 MCU via the menu `Tools - Board - Arduino Leonardo`

* Compile with `Ctrl+R`

## Upload

* Connect an **AVR ISP mkII** with the rcmix hardware
 
* After successful compilation of the Arduino sketch select `Tools - Programmer - AVRISP mkII`
 
* Upload with `Ctrl+U`
