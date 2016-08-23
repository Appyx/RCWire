#include "Arduino.h"
#include "WirelessWire.h"

WirelessWire wire = WirelessWire(0, 12);

void handleMessage(const char *message);

void setup() {
    Serial.begin(9600);
    wire.plugIn(0, handleMessage);  //same port as on Arduino

}

void loop() {

}

void handleMessage(const char *message) {
    RCWire::println(message); //useful method for cross - platform printing
}
