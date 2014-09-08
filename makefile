HEADERSDIR=include
SRCDIR=src
BINDIR=bin

all:	clean chat

chat:	$(BINDIR)/validator.o $(BINDIR)/main.o
	g++ -Wall $(BINDIR)/validator.o $(BINDIR)/main.o -o chat

$(BINDIR)/main.o:	$(BINDIR)/validator.o
	g++ -Wall -I$(HEADERSDIR) $(SRCDIR)/main.cpp -c -o $(BINDIR)/main.o

$(BINDIR)/validator.o:	$(HEADERSDIR)/validator.h $(HEADERSDIR)/p1.h
	g++ -Wall -I$(HEADERSDIR) $(SRCDIR)/validator.cpp -c -o $(BINDIR)/validator.o

clean:
	rm -rf bin/
	mkdir bin