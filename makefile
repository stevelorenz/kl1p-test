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
HEADER = -I./include
LIBB = -L./ -lKLab64 -lKLab64_d 
LIBRA = -lpthread -ldl -larmadillo

# Compiling rules
all: test-cs

test-cs: main.o
		$(CC) main.o $(LIBB) $(LIBRA) -o test-cs

main.o: main.cpp
		$(CC) $(CFLAGS) $(HEADER) main.cpp

clean:
		rm *.o
		rm test-cs
