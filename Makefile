CXX := g++
CPPFLAGS := -Isrc
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g

.PHONY: all run test clean

all: build/sqlp_demo

