CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic
TARGET = main
SOURCE = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: all clean
