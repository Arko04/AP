CXX = g++
CXXFLAGS = -std=c++11

SRCDIR = src
BUILD_DIR = build

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# List of object files to be created
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# The final executable
TARGET = program

$(BUILD_DIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
