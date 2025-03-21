# Compiler
CXX := g++

# Compiler Flags
CXXFLAGS := -std=c++17

# Libraries
LDFLAGS := -L lib/
LDLIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a

# Source Files and Executable
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := d

# Default Rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -f $(OBJS) $(TARGET)
