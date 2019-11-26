# arguments
PKG_DIR = ./
INC_DIR = $(PKG_DIR)./include
SRC_DIR = $(PKG_DIR)./src
OBJ_DIR = $(PKG_DIR)./build

# build flags
CC = g++
CXXFLAGS = -g -std=c++11
LIBRARIES = -lwiringPi

# objects and sources
INCLUDES = $(wildcard $(INC_DIR)/*.h)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp main.cpp) 
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o))) 

EXE = test1
# Create executable
$(EXE): $(OBJECTS) 
	$(CC) $(CXXFLAGS) -o $(EXE) $(OBJECTS) $(LIBRARIES)

# build
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CC) -c $(CXXFLAGS) $< -o $@

# build main
$(OBJ_DIR)/main.o: main.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@



# clean files created by make
clean:
	rm $(OBJECTS)
	rm $(EXE)