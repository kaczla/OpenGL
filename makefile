SOURCE_DIR = ./src/
MAIN = $(SOURCE_DIR)main.cpp
CXXFLAGS = -std=c++11
CXXFLAGS += -O3
APP_NAME = opengl.app

all:
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(APP_NAME) $(LFLAGS)
