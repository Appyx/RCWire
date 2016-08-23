
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