SRCDIR=src
BINDIR=bin
INCDIR=include

SDLDIR=/Library/Frameworks/SDL2.framework/Headers

CPPFLAGS=-c -std=c++11 -Wall -I$(INCDIR) -I$(SDLDIR)
LINKERFLAGS=-lSDL2

all: Rusk

Rusk: main.o Hex.o GameModel.o Game.o Player.o
	g++ -std=c++11 -Wall $(LINKERFLAGS) -o $@ $(addprefix $(BINDIR)/, $^)

main.o: $(SRCDIR)/main.cpp $(INCDIR)/Game.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Player.o: $(SRCDIR)/Player.cpp $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Hex.o: $(SRCDIR)/Hex.cpp $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

GameModel.o: $(SRCDIR)/GameModel.cpp $(INCDIR)/GameModel.h $(INCDIR)/Hex.h $(INCDIR)/Player.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

Game.o: $(SRCDIR)/Game.cpp $(INCDIR)/Game.h $(INCDIR)/GameModel.h
	g++ $(CPPFLAGS) -o $(BINDIR)/$@ $<

clean:
	rm $(BINDIR)/*
	rm Rusk
