SRCDIR=src
BINDIR=bin
INCDIR=include
TESTDIR=testSuite

SDLDIR=/Library/Frameworks/SDL2.framework/Headers

CPPFLAGS=-c -std=c++11 -Wall -I$(INCDIR) -I$(SDLDIR)
LINKERFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image

TESTCPPFLAGS=-c -std=c++11 -Wall -I$(INCDIR) -I$(SDLDIR) -fprofile-arcs -ftest-coverage
TESTLINKERFLAGS=-fprofile-arcs -lSDL2 -lSDL2_ttf -lSDL2_image

CXXTEST_HOME ?= cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

all: main test

main: main.o Hex.o GameModel.o PangaeaGameModel.o RiverGameModel.o RingGameModel.o Game.o
	g++ -std=c++11 -Wall $(LINKERFLAGS) -o $@ $(addprefix $(BINDIR)/, $^)

test: Hex.test GameModel.test PangaeaGameModel.test RiverGameModel.test RingGameModel.test Hex.cxxtest.test PangaeaGameModel.cxxtest.test RiverGameModel.cxxtest.test RingGameModel.cxxtest.test runner.test
	g++ $(TESTLINKERFLAGS) $(addprefix $(BINDIR)/, $^) -I$(CXXTEST_INCLUDE) -o $@

main.o: $(SRCDIR)/main.cpp $(INCDIR)/Game.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

main.test: $(SRCDIR)/main.cpp $(INCDIR)/Game.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

Hex.o: $(SRCDIR)/Hex.cpp $(INCDIR)/Hex.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Hex.test: $(SRCDIR)/Hex.cpp $(INCDIR)/Hex.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

Hex.cxxtest.test: Hex.cxxtest.cpp
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) $(BINDIR)/Hex.cxxtest.cpp -o $(BINDIR)/$@

Hex.cxxtest.cpp: $(TESTDIR)/Hex.cxxtest.h $(SRCDIR)/Hex.cpp $(INCDIR)/Hex.h
	$(CXXTEST_GEN) --part --error-printer $< -o $(BINDIR)/$@

GameModel.o: $(SRCDIR)/GameModel.cpp $(INCDIR)/GameModel.h $(INCDIR)/Hex.h
	g++ $(CPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

GameModel.test: $(SRCDIR)/GameModel.cpp $(INCDIR)/GameModel.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

PangaeaGameModel.o: $(SRCDIR)/PangaeaGameModel.cpp $(INCDIR)/PangaeaGameModel.h $(INCDIR)/Hex.h
	g++ $(CPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

PangaeaGameModel.test: $(SRCDIR)/PangaeaGameModel.cpp $(INCDIR)/PangaeaGameModel.h $(INCDIR)/Hex.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

PangaeaGameModel.cxxtest.test: PangaeaGameModel.cxxtest.cpp
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) $(BINDIR)/PangaeaGameModel.cxxtest.cpp -o $(BINDIR)/$@

PangaeaGameModel.cxxtest.cpp: $(TESTDIR)/PangaeaGameModel.cxxtest.h $(SRCDIR)/PangaeaGameModel.cpp $(INCDIR)/PangaeaGameModel.h
	$(CXXTEST_GEN) --part --error-printer $< -o $(BINDIR)/$@

RiverGameModel.o: $(SRCDIR)/RiverGameModel.cpp $(INCDIR)/RiverGameModel.h $(INCDIR)/Hex.h
	g++ $(CPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

RiverGameModel.test: $(SRCDIR)/RiverGameModel.cpp $(INCDIR)/RiverGameModel.h $(INCDIR)/Hex.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

RiverGameModel.cxxtest.test: RiverGameModel.cxxtest.cpp
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) $(BINDIR)/RiverGameModel.cxxtest.cpp -o $(BINDIR)/$@

RiverGameModel.cxxtest.cpp: $(TESTDIR)/RiverGameModel.cxxtest.h $(SRCDIR)/RiverGameModel.cpp $(INCDIR)/RiverGameModel.h
	$(CXXTEST_GEN) --part --error-printer $< -o $(BINDIR)/$@

RingGameModel.o: $(SRCDIR)/RingGameModel.cpp $(INCDIR)/RingGameModel.h $(INCDIR)/Hex.h
	g++ $(CPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

RingGameModel.test: $(SRCDIR)/RingGameModel.cpp $(INCDIR)/RingGameModel.h $(INCDIR)/Hex.h
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@ $<

RingGameModel.cxxtest.test: RingGameModel.cxxtest.cpp
	g++ $(TESTCPPFLAGS) -I$(CXXTEST_INCLUDE) $(BINDIR)/RingGameModel.cxxtest.cpp -o $(BINDIR)/$@

RingGameModel.cxxtest.cpp: $(TESTDIR)/RingGameModel.cxxtest.h $(SRCDIR)/RingGameModel.cpp $(INCDIR)/RingGameModel.h
	$(CXXTEST_GEN) --part --error-printer $< -o $(BINDIR)/$@

Game.o: $(SRCDIR)/Game.cpp $(INCDIR)/Game.h $(INCDIR)/GameModel.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

runner.cpp:
	$(CXXTEST_GEN) --root --error-printer -o $@

runner.test: runner.cpp
	g++ $(TESTCPPFLAGS) $< -I$(CXXTEST_INCLUDE) -o $(BINDIR)/$@

clean:
	rm -f $(BINDIR)/*
	rm -f *.g*
	rm -f main
	rm -f test
