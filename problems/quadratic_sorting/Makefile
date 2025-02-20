CXX = g++

SRC = time_measurement.cpp ../../algorithms/random_array.cpp
OUT = time_measurement.exe
INCLUDE = ../../algorithms

all: build tests

build:
	$(CXX) $(SRC) -o$(OUT) -I$(INCLUDE)

tests:
	python tests.py $(OUT)
