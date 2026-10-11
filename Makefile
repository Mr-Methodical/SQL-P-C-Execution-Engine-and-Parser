CXX := g++
CPPFLAGS := -Isrc
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g

.PHONY: all run test clean

all: build/sqlp_demo

build/sqlp_demo: src/main.cc src/path.h Makefile
	mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/main.cc -o $@

build/path_test: tests/path_test.cc src/path.h Makefile
	mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/path_test.cc -o $@

run: build/sqlp_demo
	./build/sqlp_demo

test: build/path_test
	./build/path_test

clean:
	rm -rf build
