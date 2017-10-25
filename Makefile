#g++ -fopenmp -std=c++11 src/main.cpp -o bin/game.out -Wall -Wextra -I "include/rapidjson" -I "include/googletest" #-O3

GTEST_DIR = "include/googletest"
RAPIDJSON_DIR = "include/rapidjson"
TEST_DIR = tests

CXX = g++
CPPFLAGS += -fopenmp -std=c++11 
#-isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra
#$(RAPIDJSON_DIR) 
#-pthread -O3			<--- might mess with timings

MAIN = main.cpp
MAIN_OUT = game
TESTS = rules_uitest

all: 
	make main

main:
	mkdir -p bin
	mkdir -p results
	$(CXX) $(CPPFLAGS) ./src/$(MAIN) -o bin/$(MAIN_OUT).out $(CXXFLAGS)

clean :
	rm -f bin/*
	rm -f results/*
