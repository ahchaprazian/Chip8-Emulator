CC = clang++
CFLAGS = -Wall --std=c++0x -g
LIBS = -L/opt/homebrew/lib -lSDL2
OBJ = main.o chip8.o

ALL: chip8

chip8: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o chip8 $(OBJ)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

chip8.o: chip8.cpp
	$(CC) $(CFLAGS) -c chip8.cpp -o chip8.o

clean: 
	rm -f $(OBJ) chip8