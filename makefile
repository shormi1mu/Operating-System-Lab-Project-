CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SOURCES = $(wildcard src/*.cpp)
TARGET = resourcewatch

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)