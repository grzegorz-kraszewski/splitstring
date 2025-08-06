CC = g++
CCC = gcc
LD = g++
CFLAGS = -fbaserel -O2 -fomit-frame-pointer -mregparm -fno-exceptions -fno-rtti -D__NOLIBBASE__
LDFLAGS = -nostdlib -fbaserel -nostartfiles -fno-exceptions -fno-rtti
LIBS = 
OBJS = start.o main.o callargs.o
EXE = SplitString

all: $(OBJS) aux.o
	@echo "Linking $(EXE)..."
	@$(LD) $(LDFLAGS) -o $(EXE).db $^ $(LIBS)
	@strip $(EXE).db -o $(EXE) --strip-unneeded
	@Protect $(EXE) +E
	List $(EXE)

clean:
	rm -vf *.o $(EXE) $(EXE).db

start.o: start.cpp
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -fwritable-strings -c -o $@ $<

%.o: %.cpp
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

aux.o: aux.c
	@echo "Compiling $@..."
	@$(CCC) $(CFLAGS) -c -o $@ $<

# dependencies

callargs.o: callargs.cpp callargs.h main.h
main.o: main.cpp main.h callargs.h
start.o: start.cpp main.h
