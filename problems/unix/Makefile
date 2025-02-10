CXX = g++

SRC = unix.cpp
OUT = unix.exe
INCLUDE = ../../data_structures

all: build tests

build:
	$(CXX) $(SRC) -o$(OUT) -I$(INCLUDE)

tests:
	python tests.py
