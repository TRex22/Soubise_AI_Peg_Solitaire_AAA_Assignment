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
	make clean
	make main
	# make test

test:
	# $(CXX) $(CPPFLAGS) -lgtest_main ./$(TEST_DIR)/$(TESTS).cpp -o ./$(TEST_DIR)/$(TESTS).o
	# bash compile_and_run_tests.sh

main:
	mkdir -p bin
	mkdir -p results
	$(CXX) $(CPPFLAGS) ./src/$(MAIN) -o bin/$(MAIN_OUT).out $(CXXFLAGS)
	# cp -rf data/* bin/

clean :
	rm -f bin/*
	rm -f results/*

	# rm -f tests/*.o
	# rm -f tests/runTests 
	# rm -f tests/cmake_install*
	# rm -f tests/CMakeCache*
	# rm -rf tests/CMakeFiles
	# rm -f tests/*.json

# gtest:
# 	bash install_google_test.sh

