CXX = g++
CXXFLAGS = -Wall -Wextra -fpermissive -Wno-sign-compare
TARGET = build/run
SRCS = src/main.cpp
LIBS = -lglfw -lGL -I/usr/include/glm -I./include ./include/glad.c

# Default target
all: $(TARGET)

# Rule to link the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Rule to compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the directory
clean:
	rm -f $(TARGET) $(OBJS)

run:
	./$(TARGET)

# Phony targets
.PHONY: all clean
