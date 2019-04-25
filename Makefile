all: main

main: main.cpp src/include/numcpp.h
	g++ -g -o main -std=c++11 -Isrc/include main.cpp

clean:
	rm main main.o