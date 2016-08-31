# RCWire

This library enables you to use cheap 315/433MHz AM transmitter for a textual communication between Arduino and RaspberryPi.  
You can also use it for two Arduinos or two RaspberryPis.
(For the RaspberryPi version look at the Known Issues section.)

The plan is to create a network of Arduinos in my home, which are controlling several devices.  
The RaspberryPi should be the "Control Center" which sends the messages.

I think this is the cheapest solution for creating a wireless network of ICs.

## How to use?
```
//create an object
RCWire wire = RCWire(0, 12); 

//plug in the wire
wire.plugIn(0, handleMessage); //The port has to be the same for sender and receiver

//send a message
wire.sendMessage("this is a really long message i think");

//do something in your callback function
void handleMessage(const char *message) {
    RCWire::println(message); //useful method for cross - platform printing
}
```
Note for Arduino: the receiver pin is not the pin on the board, it's the interrupt number.  
Note for RaspberryPi: take a look at the WiringPi pin mappings. <a>https://projects.drogon.net/raspberry-pi/wiringpi/pins/</a>

## Installation-Hardware
There are many tutorials out there for wiring up the boards.  
The rxPin 0 in the ArduinoExample.cpp conforms to the pin 2 and the txPin 12 conforms to pin 12 on the Arduino board.  
For the Raspberry the pin mappings are equal to the WiringPi mappings.

Update: I testet it with 173mm antennas and it worked very well for distances < 50m indoor.

## Installation-Arduino
Just copy the files RCWire,RCSwitch,Header into the appropriate library folder.  
For the Arduino IDE check this link: <a>https://www.arduino.cc/en/Guide/Libraries#toc5</a>  
For PlatformIO just copy the files into the lib folder.  
Take a look at the ArduinoExample.cpp.


## Installation-RaspberryPi
First you have to install the well known library WiringPI <a>http://wiringpi.com/download-and-install/</a>  
Then just clone the git repo and run the make command.  
Now you should have a send application which takes the text to be sent as parameter.  
(This application will only work with the ArduinoExample.cpp counterpart. 
Note that you have to change the message after it was sent once if your sender doesn't run in an infinite loop.)

## Features
* You can send text with a maximum length of 59 characters in the default setup.  
(The text is split into four 128 bit frames with a 8 bit header. For longer messages
the header has to be bigger. And I think you won't be able to send more without crc-checks.) 

* You can change the transmission-protocol (thanks to RCSwitch).

* Specify a "port", so that it's possible to have multiple RCWires in
one area without disturbing each other.

* Coming maybe: A signal repeater function. (Use an Arduino to overcome greater distances)

# Known Issues

On the RaspberryPi you are currently not able to receive and send in the same application.








