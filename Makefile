# Defines the RPI variable which is needed by RCSwitch.h and RCWire.h
CXXFLAGS=-DRPI

all: send
	
send: Header.o RCSwitch.o WirelessWire.o RaspberryExample.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
