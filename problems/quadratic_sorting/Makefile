CXX = g++

SRC = time_measurement.cpp
OUT = time_measurement.exe
INCLUDE = ../../algorithms

all: build tests

build:
	$(CXX) $(SRC) -o$(OUT) -I$(INCLUDE)

tests:
	python tests.py $(OUT)
