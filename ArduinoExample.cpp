/**
 * RCWire - Arduino and RaspberryPi library for sending messages with 315/433MHz AM transmitter.
 *
 * Copyright (c) 2011 Gstöttner Robert.  All right reserved.
 *
 * Project home: https://github.com/Appyx/RCWire
 *
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 * This library is built on top of RCSwitch (https://github.com/sui77/rc-switch).
 * The modifications to the original library are marked as comments in the source.
 *
 */

#include "Arduino.h"
#include "RCWire.h"

#define LED_PIN 13

RCWire wire = RCWire(0, 12);

void handleMessage(const char *message);

bool messageReceived = false;

void setup() {
    Serial.begin(9600);
    pinMode(7, OUTPUT); //pin to control the door
    digitalWrite(7, LOW);
    wire.plugIn(0, handleMessage);
}

void loop() {
    if (messageReceived) { //busy wait for message (can't use delay in interrupt)
        messageReceived = false;
        digitalWrite(7, HIGH);
        delay(1500); //open the door
        digitalWrite(7, LOW);
        wire.reset(); //reset the wire so that the same message can be sent again.
    }
}

void handleMessage(const char *message) {
    RCWire::print("message received: ");
    RCWire::println(message);
    if (RCWire::stringEquals(message, "open the door")) { //could use strcmp too.
        messageReceived = true;
    }
}