CXX = g++
CXXFLAGS = -std=c++11 -Wall

# List of source files
SOURCES = main.cpp linkedlist.hpp zombie.h zombie.cpp

# Object files to be generated
OBJECTS = $(SOURCES:.cpp=.o)

# Name of the executable
TARGET = exe

# Compile and link the program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Compile each source file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the generated object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)
