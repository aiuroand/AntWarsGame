CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic 
LIBS=
OBJS=src/main.o src/map.o

all: antwars

antwars: $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o 