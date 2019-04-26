SRC_DIR := .
OBJ_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/test_*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CPPFLAGS := -I../src/include -I../vendor
LDFLAGS :=
CXXFLAGS :=
CC := g++

.PHONY: all clean

all: main

main: main.o $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp ../src/include/numcpp.h
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o test_main