CC = g++
CFLAGS = -march=native -O2

default: build

all: build run clean

build:
	mkdir -p ./bin/
	$(CC) ${CFLAGS} ./src/*.cpp -o ./bin/wilpac

run:
	clear
	./bin/wilpac

clean:
	rm -r ./bin/
