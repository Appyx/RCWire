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


#ifndef OPENER_RCWIRE_H
#define OPENER_RCWIRE_H


#include "RCSwitch.h"
#include "Header.h"

class RCWire {

public:
    /**
    * Creates the wire
    * @param rxPin Receive pin (it's not the pin number on the board - it's the interrupt number)
    * @param txPin Transmit pin (pin on the board)
    * @return
    */
    RCWire(unsigned int rxPin, unsigned int txPin);

    /**
    * Plugs the wire in and only listens and sends on the specified port
    * @param port 0-3
    * @param listener Any function
    */
    void plugIn(unsigned int port, void (*listener)(const char *message));

    /**
    * Sends a string with a maximum length of 59 chars.
    * @param text The text to send
    */
    void sendMessage(const char *text);

    int getMaxMessageSize();

    /**
    * Changes the RC protocol.
    * @param protocol A number which can be looked up in the RCSwitch.cpp file.
    */
    void changeProtocol(int protocol);

    static void onRcMessage(unsigned char *code, int protocol);

    static void print(const char *string);

    static void print(int value);

    static void println();

    static void println(const char *string);

    static void printArray(char *array, int size);

    static void printArray(unsigned char *array, int size);

    static const int frameSize = 128;

    static bool stringEquals(const char *s1, const char *s2);

private:

    int nextSubPackageNumber;

    int port;

    char buffer[(frameSize - 8) / 8 * 4];

//    static bool checkForAck(unsigned char *code);

//    void sendAck(Header h);

    static RCWire *instance;

    char lastMessage[(frameSize - 8) / 8];

    void storeLastMessage(char *message);

    RCSwitch rcSwitch;

    static void (*singlePortHandler)(const char *);

    void encodeMessage(unsigned char *result, const char *msg);

    void decodeMessage(char *result, unsigned char *msg);


};


#endif //OPENER_RCWIRE_H
