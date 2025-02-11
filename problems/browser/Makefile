CXX = g++

SRC = browser.cpp
OUT = browser.exe
INCLUDE = ../../data_structures

all: build tests

build:
	$(CXX) $(SRC) -o$(OUT) -I$(INCLUDE)

tests:
	python tests.py $(OUT)
