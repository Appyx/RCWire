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

#ifndef OPENER_HEADER_H
#define OPENER_HEADER_H


class Header {

public:

    Header();

    Header(unsigned char *header);

    Header(int init);

    int getSubPackage();

    void setSubPackage(int number);

    int getPort();

    void setPort(int port);

    void setSync(bool flag);

    void setPackages(int number);

    int getPackages();

    void print();

    unsigned char *getArray();

    bool equals(Header header);

    void toggleSync();

private:
    unsigned char array[8];

    int intToBinary(int number, int bit);

    int binaryToInt(int bit0, int bit1, int bit2);

    int binaryToInt(int bit0, int bit1);


};


#endif //OPENER_HEADER_H
