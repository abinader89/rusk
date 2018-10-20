SRCDIR=src
BINDIR=bin
INCDIR=include

SDLDIR=/Library/Frameworks/SDL2.framework/Headers

CPPFLAGS=-c -std=c++11 -Wall -I$(INCDIR) -I$(SDLDIR)
LINKERFLAGS=-lSDL2

all: main

main: main.o Hex.o GameModel.o Game.o Player.o
	g++ -std=c++11 -Wall $(LINKERFLAGS) -o $@ $(addprefix $(BINDIR)/, $^)

main.o: $(SRCDIR)/model/main.cpp $(INCDIR)/Game.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Player.o: $(SRCDIR)/model/Player.cpp $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Hex.o: $(SRCDIR)/model/Hex.cpp $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

GameModel.o: $(SRCDIR)/model/GameModel.cpp $(INCDIR)/GameModel.h $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Game.o: $(SRCDIR)/model/Game.cpp $(INCDIR)/Game.h $(INCDIR)/GameModel.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

clean:
	rm $(BINDIR)/*
	rm main
