CXX = g++

#BENCHMARKS_SRC = time_measurement.cpp ../../algorithms/random_array.cpp
#BENCHMARKS_OUT = time_measurement.exe
TESTS_SRC = tests.cpp ../../algorithms/random_array.cpp
TESTS_OUT = tests.exe
INCLUDE = ../../algorithms ../../data_structures

all: build tests

build:
#	$(CXX) $(BENCHMARKS_SRC) -o$(BENCHMARKS_OUT) $(addprefix -I, $(INCLUDE))
	$(CXX) $(TESTS_SRC) -o$(TESTS_OUT) $(addprefix -I, $(INCLUDE))

tests:
	python tests.py $(TESTS_OUT)

benchmarks: build
	python benchmarks.py $(BENCHMARKS_OUT)
