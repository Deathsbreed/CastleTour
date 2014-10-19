CXX=clang++
CXXFLAGS= -O3 -Wall

INCLUDES= -Iinclude/irrlicht
LIBS= -lIrrlicht -lX11 -lGL

MV=mv
MKDIR=mkdir -p
RM=rm -rf

main:
	$(MKDIR) bin
	$(CXX) $(INCLUDES) -c -o src/main.o src/main.cpp
	$(CXX) $(INCLUDES) -c -o src/eventReceiver.o src/eventReceiver.cpp
	$(CXX) $(LIBS) -o bin/castletour src/*.o

clean:
	$(RM) src/*.o
	$(RM) bin
