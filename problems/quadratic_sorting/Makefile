CXX = g++

BENCHMARK_SRC = time_measurement.cpp ../../algorithms/random_array.cpp
BENCHMARK_OUT = time_measurement.exe
TESTS_SRC = tests.cpp ../../algorithms/random_array.cpp
TESTS_OUT = tests.exe
INCLUDE = ../../algorithms

all: build tests

build:
	$(CXX) $(BENCHMARK_SRC) -o$(BENCHMARK_OUT) -I$(INCLUDE)
	$(CXX) $(TESTS_SRC) -o$(TESTS_OUT) -I$(INCLUDE)

tests:
	python tests.py $(TESTS_OUT)

benchmark:
	python benchmark.py $(BENCHMARK_OUT)
