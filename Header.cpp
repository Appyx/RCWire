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

#include "Header.h"
#include "RCWire.h"

//bit 0 = ack
//bit 1 = sync
//bit 2+3 = subpackage number
//bit 4+5 = packages
//bit 6+7 = port number

Header::Header() {
    for (int i = 0; i < 8; i++) {
        array[i] = 0;
    }
}

Header::Header(unsigned char *header) {
    for (int i = 0; i < 8; i++) {
        array[i] = header[i];
    }
}

void Header::setPort(int port) {
    if (port > 3) {
        return;
    }
    array[6] = (unsigned char) intToBinary(port, 1);
    array[7] = (unsigned char) intToBinary(port, 0);

}

int Header::getPort() {
    return binaryToInt(array[7], array[6]);
}

void Header::setSync(int value) {
    array[1] = (unsigned char) value;
}

int Header::getSync() {
    return array[1];
}

void Header::setAck() {
    array[0] = 1;
}

void Header::setSubPackage(int number) {
    if (number > 3) {
        return;
    }
    array[2] = (unsigned char) intToBinary(number, 1);
    array[3] = (unsigned char) intToBinary(number, 0);
}

int Header::getSubPackage() {
    return binaryToInt(array[3], array[2]);
}

void Header::setPackages(int number) {
    if (number > 3) {
        return;
    }
    array[4] = (unsigned char) intToBinary(number, 1);
    array[5] = (unsigned char) intToBinary(number, 0);
}

int Header::getPackages() {
    return binaryToInt(array[5], array[4]);
}

bool Header::isAck() {
    return array[0] == 1;
}

int Header::intToBinary(int number, int bit) {
    return (number >> bit) & 1;
}

int Header::binaryToInt(int bit0, int bit1) {
    int number = 0;
    number |= bit0 == 1 ? 0x01 : 0x00;
    number |= bit1 == 1 ? 0x02 : 0x00;
    return number;
}

void Header::print() {
    WirelessWire::println("----------");
    WirelessWire::print("ack: ");
    WirelessWire::print(array[0]);
    WirelessWire::println();
    WirelessWire::print("sync: ");
    WirelessWire::print(array[1]);
    WirelessWire::println();
    WirelessWire::print("subpackage: ");
    WirelessWire::print(array[2]);
    WirelessWire::print(array[3]);
    WirelessWire::println();
    WirelessWire::print("packages: ");
    WirelessWire::print(array[4]);
    WirelessWire::print(array[5]);
    WirelessWire::println();
    WirelessWire::print("port: ");
    WirelessWire::print(array[6]);
    WirelessWire::print(array[7]);
    WirelessWire::println();
    WirelessWire::println("----------");

}

unsigned char *Header::getArray() {
    return array;
}












