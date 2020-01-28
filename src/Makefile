CC=g++

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: libhamshield.so

clean:
	rm HamShield_comms.o HamShield.o libhamshield.so

install: libhamshield.so HamShield.h HamShield_comms.h
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 libhamshield.so $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 644 HamShield.h HamShield_comms.h $(DESTDIR)$(PREFIX)/include/

libhamshield.so: HamShield.o HamShield_comms.o
	$(CC) -shared HamShield.o HamShield_comms.o -o libhamshield.so

HamShield.o: HamShield.cpp
	$(CC) -fpic -c HamShield.cpp -o HamShield.o

HamShield_comms.o: HamShield_comms.cpp
	$(CC) -fpic -c HamShield_comms.cpp -o HamShield_comms.o