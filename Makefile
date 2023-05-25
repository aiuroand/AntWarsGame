CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic 
LIBS=-lncurses 
OBJS=src/main.o src/map.o src/mapelement.o src/loop.o src/menu.o src/game.o src/screen.o src/rules.o src/wall.o

all: antwars

antwars: $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o 

run: 
	./antwars