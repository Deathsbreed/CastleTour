CXX=clang++
CXXFLAGS= -O3 -Wall

INCLUDES= -Iinclude/irrlicht
LIBS= -lIrrlicht -lGL -lGLU -lXrandr -lXext -lX11

MV=mv
MKDIR=mkdir -p
RM=rm -rf

SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix src/, $(notdir $(SRC_FILES:.cpp=.o)))

all: $(OBJ_FILES)
	$(MKDIR) bin
	$(CXX) $(CXXFLAGS) $(LIBS) -o bin/castletour src/*.o

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(RM) src/*.o
	$(RM) bin
