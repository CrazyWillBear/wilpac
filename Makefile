CC=g++

all: build run clean

build:
	mkdir -p ./bin/
	$(CC) ./src/*.cpp -o ./bin/main

run:
	clear
	./bin/main

clean:
	rm -r ./bin/