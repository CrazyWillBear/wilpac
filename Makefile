CC = clang++
CFLAGS = -march=native

default: build run clean

all: build run clean build-release install

build:
	mkdir -p ./bin/
	$(CC) ${CFLAGS} ./src/*.cpp -o ./bin/wilpac

run:
	clear
	./bin/wilpac

clean:
	rm -r ./bin/

build-release:
	mkdir -p ./bin/
	$(CC) ${CFLAGS} ./src/*.cpp -Ofast -o ./bin/wilpac