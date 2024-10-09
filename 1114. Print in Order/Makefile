CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O3 -pthread
TARGET = print_in_order
SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean run

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)