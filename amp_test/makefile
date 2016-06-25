# Compiler
CC = clang++

# Compiling options
CFLAGS = -c -Wall

ifeq ($(BUILD), debug)   
# "Debug" build - no optimization, and debugging symbols
CFLAGS += -O0 -g
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG
endif

# Compiling header and libs
HEADER = -I../include
LIBB = -L../ -lKLab64 -lKLab64_d 
LIBRA = -lpthread -ldl -larmadillo

# Compiling rules
all: test-amp
test-amp: main.o CompressedSensingExample.o 
		$(CC) main.o CompressedSensingExample.o  $(LIBB) $(LIBRA) -o test-amp

main.o: main.cpp
		$(CC) $(CFLAGS) $(HEADER) main.cpp

CompressedSensingExample.o: CompressedSensingExample.cpp
		$(CC) $(CFLAGS) $(HEADER) CompressedSensingExample.cpp

clean:
		rm *.o
		rm test-amp
