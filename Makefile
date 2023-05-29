CXXFLAGS = -std=c++17 -Wall -pedantic 
HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
LIBS=-lncurses
VALGRIND = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./aiuroand

.PHONY: compile
compile: aiuroand

aiuroand: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@ $(LIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@ $(LIBS)

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile
	mv doc/html/* doc
	rm -r doc/html

.PHONY: clean
clean:
	rm -rf username build/ debug/ doc/ 2>/dev/null
	rm aiuroand

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done

