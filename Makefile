CC=g++ -g -frtti
CFLAGS=-c -Wall -I./include -DDEBUG -fno-objc-arc

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include
TOOLSSRC=tools-src
TOOLSOBJ=tools-obj
TOOLSBIN=tools
LIBS=

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE := $(BINDIR)/devocomp-int

DICTTOOLSRC := $(TOOLSSRC)/dictionary.cpp
DICTTOOLBIN := $(TOOLSBIN)/dictionary
DICTTOOLOBJ := $(DICTTOOLSRC:$(TOOLSSRC)/dictionary.cpp=$(TOOLSOBJ)/dictionary.o)

all: $(SOURCES) $(EXECUTABLE) tools

$(EXECUTABLE): $(OBJECTS) $(LIBS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -I=$(INCDIR) $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE) $(TOOLSOBJ)/*.o $(TOOLSBIN)/*

tools: $(DICTTOOLBIN)

$(DICTTOOLBIN): $(DICTTOOLOBJ) $(LIBS)
	$(CC) $(LDFLAGS) $(DICTTOOLOBJ) $(LIBS) -o $@

tools-obj/dictionary.o:
	$(CC) $(CFLAGS) -I=$(INCDIR) tools-src/dictionary.cpp -o $@
