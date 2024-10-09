CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O3
TARGET = main
SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean run

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)