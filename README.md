# RCWire

This library enables you to use cheap 315/433MHz AM transmitter for a cheap textual  
communication between Arduino and RaspberryPi.  
You can also use it for two Arduinos or two RaspberryPis.
(For the RaspberryPi version look at the Known Issues section.)

## How to use?
```
//create an object
WirelessWire wire = WirelessWire(0, 12); 

//plug in the wire
wire.plugIn(0, handleMessage);

//do something in your callback function
void handleMessage(const char *message) {
    RCWire::println(message); //useful method for cross - platform printing
}
```
Note for Arduino: the receiver pin is not the pin on the board, it's the interrupt numebr.

## Installation-Hardware
There are many tutorial out there for wiring up the boards.

## Installation-Arduino
Just copy the files RCWire,RCSwitch,Header into the appropriate library folder.  
For the Arduino IDE check this link: <a>https://www.arduino.cc/en/Guide/Libraries#toc5</a>  
For PlatformIO just copy the files into the lib folder.  
Take a look at the ArduioExample.cpp.


## Installation-RaspberryPi
First you have to install the well known library WiringPI <a>http://wiringpi.com/download-and-install/</a>  
Then just clone the git repo and run the make command.  
Now you should have a send application which takes the text to be sent as parameter.  
(This application will only work with the ArduinoExample.cpp counterpart.)

## Features
* You can send text with a maximum length of 59 characters in the default setup.  
(The text is split into four 128 bit frames with a 8 bit header. For longer messages  
the header has to be bigger. And I think you won't be able to send more without crc-checks.) 

* You can change the transmission-protocol (thanks to RCSwitch).

* Coming soon: ACK-flag will be sent after successful message. --> Retransmission   
(This will probably only work with two Arduinos because of the ISRs on the RaspberryPi) 

* Coming soon: Specify a "port", so that it's possible to have multiple RCWires in  
one area without disturbing each other.

* Coming maybe: Dynamic protocol switching.

# Known Issues

On the RaspberryPi you are currently not able to receive and send in the same application.

Sending a message takes a long time, this is due to the high rate of retransmissions.  
(I am playing with that issue, and I am trying to reach higher distances.)








