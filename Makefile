CC=g++

CFLAGS= -g

LFLAGS= -lm

SRCDIR = src
OBJDIR = bin
INCDIR = include

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)



triangulate: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm  bin/* || true

purge: clean
	rm ./triangulate || true