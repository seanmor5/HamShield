# HamShield for Raspberry Pi

This repository is a hack for HamShield integration with the Raspberry Pi Compute Module and Raspberry Pi IO board.

You can purchase HamShield (as well as smaller variants or LoRa version) at http://www.enhancedradio.com/.

## Layout

The HamShield library is designed to work out of the box with the Arduino. While it also integrates nicely with a typical Raspberry Pi, there are some issues when working with the Raspberry Pi Compute Module and IO Board. These issues are fixed using some tweaks to the HamShield Library (namely configuring WiringPi to work without re-mapping), and by adjusting the connections between the Raspberry Pi and HamShield.

Note this has only been tested on a HamShield LoRa. The wiring configuration is:

```
Vin	<->	Any 5v pin, these pins share a common node
Vg	<->	Any ground pin, these pins share a common node
nCS	<->	pin 17, BCM17 on GPIO board
DAT	<->	pin 27, BCM27 on GPIO board
CLK	<-> pin 22, BCM22 on GPIO board
MIC	<->	pin 18, BCM18 on GPIO board
RST	<->	pin 23, BCM23 on GPIO board
```

## Installation

On a Raspbian image, install WiringPi.

```
$ apt-get install wiringpi wiringpi2
```

Next, clone this repository.

```
$ git clone https://github.com/seanmor5/HamShield
```

Navigate to the `src` directory and run the following:

```
$ make
...
$ make install
```

You should be good to go. Test the installation by compiling and running one of the examples.

