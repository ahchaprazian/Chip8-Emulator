CC = g++
CFLAGS = -Wall --std=c++0x -g -DBOOST_LOG_DYN_LINK
LIBS = -L/opt/homebrew/lib -lSDL2 -lboost_log-mt -lboost_log -lboost_log_setup -lpthread
INCLUDES = -I/opt/homebrew/include -I/opt/homebrew/Cellar/boost.1.83.0/include
OBJ = main.o chip8.o

ALL: chip8

chip8: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o chip8 $(OBJ)

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

chip8.o: chip8.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c chip8.cpp -o chip8.o

clean: 
	rm -f $(OBJ) chip8