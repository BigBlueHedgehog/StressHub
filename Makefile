CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = stressHub
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) examples/gen.cpp examples/slow.cpp examples/fast.cpp 100

clean:
	rm -f $(TARGET)
	rm -rf tmp/