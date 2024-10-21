CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic
TARGET = main
SOURCES = $(TARGET).cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf $(TARGET) build/

.PHONY: all clean