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

#include "RCWire.h"

#ifdef RPI
#include <stdio.h>
#include <wiringPi.h>
#endif

RCWire *RCWire::instance;

void (*RCWire::singlePortHandler)(const char *);


RCWire::RCWire(unsigned int rxPin, unsigned int txPin) {
    RCWire::instance = this;
    nextSubPackageNumber = 0;

    rcSwitch = RCSwitch();
    rcSwitch.enableTransmit(txPin);
    rcSwitch.enableReceive(rxPin);

}


void RCWire::plugIn(unsigned int port, void (*listener)(const char *message)) {
    singlePortHandler = listener;
    this->port = port;  //TODO: handle ports
}

int RCWire::getMaxMessageSize() {
    return (4 * (frameSize - 8) / 8) - 1;
}


void RCWire::changeProtocol(int protocol) {
    rcSwitch.setProtocol(protocol);
}


void RCWire::sendMessage(const char *text) {

    int characters = strlen(text);
    int fittingChars = (frameSize - 8) / 8;

    Header h = Header();
    h.setPort(port);
    h.setPackages(characters / fittingChars);

    for (int i = 0; i < characters; i += fittingChars) {

        unsigned char binaryText[frameSize - 8];  //minus header size
        encodeMessage(binaryText, text);

        h.setSubPackage(i / fittingChars);

        unsigned char message[frameSize];
        for (int j = 0; j < frameSize; j++) {
            if (j >= 8) {
                message[j] = binaryText[j - 8];
            } else {
                //header
                message[j] = h.getArray()[j];
            }
        }

        rcSwitch.send(message, frameSize);
        /*
        print("message sent: ");
        printArray(message, frameSize);
        println();

        char debug[(frameSize - 8) / 8];
        decodeMessage(debug, message);
        print(debug);
        println();*/

        text = text + fittingChars;
    }
}

/**
 * Builds the message
 * @param code 128bit code
 * @param protocol //TODO: handle protocols
 */
void RCWire::onRcMessage(unsigned char *code, int protocol) {
    Header header = Header(code);

    if (!instance->nextSubPackageNumber == header.getSubPackage()) {
        return;
    }
    if (header.getSubPackage() < header.getPackages()) {
        instance->nextSubPackageNumber = header.getSubPackage() + 1;
    } else {
        instance->nextSubPackageNumber = 0;
    }

    char message[(frameSize - 8) / 8];
    instance->decodeMessage(message, code);

    if (stringEquals(instance->lastMessage, message)) {
        return;
    }
    instance->storeLastMessage(message);

    for (int i = 0; i < (frameSize - 8) / 8; i++) {
        instance->buffer[i + header.getSubPackage() * (frameSize - 8) / 8] = message[i];
    }

    if (header.getSubPackage() == header.getPackages()) {
        instance->singlePortHandler(instance->buffer);

//        print("message is: ");
//        println(instance->buffer);
//        RCWire::singlePortHandler();
    }
}

void
RCWire::encodeMessage(unsigned char *result, const char *msg) {
    int breakIndex = frameSize - 8;
    for (int i = 0; i < frameSize - 8; i += 8) {
        char c = msg[i / 8];

        for (int j = 7; j >= 0; --j) {
            result[i + j] = (c & (1 << j)) ? (unsigned char) 1 : (unsigned char) 0;
        }
    }
}

void RCWire::decodeMessage(char *result, unsigned char *msg) {

    int resultIndex = 0;
    char c;

    for (int j = 8; j < frameSize; j += 8) {
        c = 0;
        for (int i = 0; i < 8; i++) {
            c |= (msg[j + i] == 1) << i;
        }

        result[resultIndex] = c;
        resultIndex += 1;
    }
}

void RCWire::storeLastMessage(char *message) {
    for (int i = 0; i < (frameSize - 8) / 8; i++) {
        lastMessage[i] = message[i];
    }
}

//TODO: ACK handling
/*void RCWire::sendAck(Header h) {
    h.setAck();
    unsigned char message[frameSize];
    for (int i = 0; i < frameSize; i++) {
        if (i >= 8) {
            message[i] = 1;
        } else {
            message[i] = 0;
        }
    }
    rcSwitch.send(message, frameSize);
    print("ack sent: ");
    printArray(message, frameSize);
    println();
}

bool RCWire::checkForAck(unsigned char *code) {

    int check = 0;
    for (int i = 8; i < frameSize; i++) {
        check += code[i];
    }
    println();
    return check > frameSize - 10;
}*/


bool RCWire::stringEquals(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}


/**
 * Some useful cross-platform printing methods.
 */

void RCWire::print(const char *string) {
#ifndef RPI
    Serial.print(string);
#else
    printf(string);
    fflush(stdout);
#endif
}

void RCWire::print(int value) {
#ifndef RPI
    Serial.print(value);
#else
    printf("%d",value);
    fflush(stdout);
#endif
}

void RCWire::println() {
#ifndef RPI
    Serial.println();
#else
    printf("\n");
    fflush(stdout);
#endif

}

void RCWire::println(const char *string) {
#ifndef RPI
    Serial.println(string);
#else
    printf("%s\n",string);
    fflush(stdout);
#endif
}

void RCWire::printArray(char *array, int size) {
    for (int i = 0; i < size; i++) {
        print(array[i]);
    }

}

void RCWire::printArray(unsigned char *array, int size) {
    for (int i = 0; i < size; i++) {
        print(array[i]);
    }

}
















