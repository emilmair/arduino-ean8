.PHONY: all init upload test clean

all:
	@echo "try one of the targets: init, upload, test or clean"

clean:
	rm -rf ./build
	mkdir build

init:
	pio init --board uno

upload:
	pio run --target upload

test:
	make clean
	g++ -I include/processing.h test/main.cpp src/processing.cpp -o build/test
	./build/test