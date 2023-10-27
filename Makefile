#-Wall and -Wextra for warnings,-std for c89 standard
CFLAGS = -Wall -Wextra -std=c89 

all: traffic

# Linking the final executable which is traffic
traffic: main.o linkedlist.o game.o terminal.o
	gcc $(CFLAGS) -o traffic main.o linkedlist.o game.o terminal.o

main.o: main.c game.h linkedlist.h terminal.h
	echo "compiling main file"
	gcc $(CFLAGS) -c main.c

game.o: game.c game.h
	echo "compiling game file"
	gcc $(CFLAGS) -c game.c

linkedlist.o: linkedlist.c linkedlist.h
	echo "compiling linkedlist file"
	gcc $(CFLAGS) -c linkedlist.c

terminal.o: terminal.c terminal.h
	echo "compiling terminal file"
	gcc $(CFLAGS) -c terminal.c

clean:
# removing everything but source files
	rm main.o linkedlist.o game.o traffic
