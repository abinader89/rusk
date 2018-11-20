SRCDIR=src
BINDIR=bin
INCDIR=include
TESTDIR=testSuite

SDLDIR=/Library/Frameworks/SDL2.framework/Headers

CPPFLAGS=-c -std=c++11 -Wall -I$(INCDIR) -I$(SDLDIR)
LINKERFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image

TESTCPPFLAGS=-c -std=c++11 -Wall -I$(INCDIR) -I$(SDLDIR) -fprofile-arcs -ftest-coverage
TESTLINKERFLAGS=-fprofile-arcs -lSDL2

CXXTEST_HOME ?= cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

all: main test

main: main.o Hex.o GameModel.o Game.o Player.o
	g++ -std=c++11 -Wall $(LINKERFLAGS) -o $@ $(addprefix $(BINDIR)/, $^)

test: GameModel.test Hex.test GameModel.cxxtest.test runner.test
	g++ $(TESTLINKERFLAGS) $(addprefix $(BINDIR)/, $^) -I$(CXXTEST_INCLUDE) -o $@

main.o: $(SRCDIR)/main.cpp $(INCDIR)/Game.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

main.test: $(SRCDIR)/main.cpp $(INCDIR)/Game.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

Player.o: $(SRCDIR)/Player.cpp $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Player.test: $(SRCDIR)/Player.cpp $(INCDIR)/Player.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

Hex.o: $(SRCDIR)/Hex.cpp $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Hex.test: $(SRCDIR)/Hex.cpp $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

GameModel.o: $(SRCDIR)/GameModel.cpp $(INCDIR)/GameModel.h $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $< 

GameModel.test: $(SRCDIR)/GameModel.cpp $(INCDIR)/GameModel.h $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

GameModel.cxxtest.test: GameModel.cxxtest.cpp
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) $(BINDIR)/GameModel.cxxtest.cpp -o $(BINDIR)/$@

GameModel.cxxtest.cpp: $(TESTDIR)/GameModel.cxxtest.h $(SRCDIR)/GameModel.cpp $(INCDIR)/GameModel.h
	$(CXXTEST_GEN) --part --error-printer $< -o $(BINDIR)/$@

Game.o: $(SRCDIR)/Game.cpp $(INCDIR)/Game.h $(INCDIR)/GameModel.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Game.test: $(SRCDIR)/Game.cpp $(INCDIR)/Game.h $(INCDIR)/GameModel.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

runner.cpp:
	$(CXXTEST_GEN) --root --error-printer -o $@

runner.test: runner.cpp
	g++ $(TESTCPPFLAGS) $< -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@

clean:
	rm -f $(BINDIR)/*
	rm -f *.g*
	rm -f main
	rm -f test
