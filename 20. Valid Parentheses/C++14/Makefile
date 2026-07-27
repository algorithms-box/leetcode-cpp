CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -O2

.PHONY: run test clean cmake_config cmake_build cmake_test cmake_clean all

all: run

run: valid_parentheses
	./valid_parentheses

test: valid_parentheses
	./valid_parentheses

valid_parentheses: valid_parentheses.cpp
	$(CXX) $(CXXFLAGS) -o valid_parentheses valid_parentheses.cpp

cmake_config:
	cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake

cmake_build:
	cmake --build build

cmake_test:
	cd build && ctest --output-on-failure

cmake_clean:
	rm -rf build

clean:
	rm -f valid_parentheses
