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


#include <cstring>
#include "RCWire.h"
#include <sstream>
#include <iostream>

void onMessage(const char *message);

int main(int argc, char **argv) {
#ifdef RPI
    wiringPiSetup();
#endif
    RCWire wire = RCWire(2, 0);
    wire.plugIn(0, onMessage); //same port as on Raspberry

    std::ostringstream buf;

    for (int i = 1; i < argc; i++) {
        buf << argv[i];
        buf << " ";
    }
    if (buf.str().size() > wire.getMaxMessageSize()) {
        std::cout << "error -" << " maximum size = " << wire.getMaxMessageSize()
                  << " but actual size = " << buf.str().size() << std::endl;
        exit(1);
    }

    wire.sendMessage(buf.str().c_str());
}

void onMessage(const char *message) {
    //No output handling - we're only sending
}