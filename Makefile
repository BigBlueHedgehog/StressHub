CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = stresshub
SRC = src/main.cpp src/config.cpp src/compiler.cpp src/runner.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) examples/gen.cpp examples/slow.cpp examples/slow.cpp 20

demo-fail: $(TARGET)
	./$(TARGET) examples/gen.cpp examples/slow.cpp examples/fast.cpp 100

clean:
	rm -f $(TARGET)
	rm -rf tmp/
