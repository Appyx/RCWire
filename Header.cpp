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

//bit 0 = sync
//bit 1+2 = subpackage number
//bit 3+4 = packages
//bit 5+6+7 = port number

Header::Header(int init) {
    for (int i = 0; i < 8; i++) {
        array[i] = (unsigned char) init;
    }
}

Header::Header(unsigned char *header) {
    for (int i = 0; i < 8; i++) {
        array[i] = header[i];
    }
}

void Header::setPort(int port) {
    if (port > 7) {
        return;
    }
    array[5] = (unsigned char) intToBinary(port, 2);
    array[6] = (unsigned char) intToBinary(port, 1);
    array[7] = (unsigned char) intToBinary(port, 0);

}

void Header::setSync(bool flag) {
    array[0] = (unsigned char) flag;
}

int Header::getPort() {
    return binaryToInt(array[7], array[6], array[5]);
}

void Header::setSubPackage(int number) {
    if (number > 3) {
        return;
    }
    array[1] = (unsigned char) intToBinary(number, 1);
    array[2] = (unsigned char) intToBinary(number, 0);
}

int Header::getSubPackage() {
    return binaryToInt(array[2], array[1]);
}

void Header::setPackages(int number) {
    if (number > 3) {
        return;
    }
    array[3] = (unsigned char) intToBinary(number, 1);
    array[4] = (unsigned char) intToBinary(number, 0);
}

int Header::getPackages() {
    return binaryToInt(array[4], array[3]);
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

int Header::binaryToInt(int bit0, int bit1, int bit2) {
    int number = 0;
    number |= bit0 == 1 ? 0x01 : 0x00;
    number |= bit1 == 1 ? 0x02 : 0x00;
    number |= bit2 == 1 ? 0x04 : 0x00;
    return number;
}

void Header::print() {
    RCWire::println("----------");
    RCWire::print("sync: ");
    RCWire::print(array[0]);
    RCWire::println();
    RCWire::print("subpackage: ");
    RCWire::print(array[1]);
    RCWire::print(array[2]);
    RCWire::println();
    RCWire::print("packages: ");
    RCWire::print(array[3]);
    RCWire::print(array[4]);
    RCWire::println();
    RCWire::print("port: ");
    RCWire::print(array[5]);
    RCWire::print(array[6]);
    RCWire::print(array[7]);
    RCWire::println();
    RCWire::println("----------");

}

unsigned char *Header::getArray() {
    return array;
}

bool Header::equals(Header header) {
    for (int i = 0; i < 8; i++) {
        if (array[i] != header.getArray()[i]) {
            return false;
        }
    }
    return true;
}

Header::Header() {

}

void Header::toggleSync() {
    if (array[0] == 0) {
        array[0] = 1;
    } else {
        array[0] = 0;
    }
}












