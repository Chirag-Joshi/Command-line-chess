chess : board.o main.o moves.o headers.h
	gcc main.o board.o moves.o -Wall -o chess

main.o : main.c headers.h board.c moves.c
	gcc -c main.c

board.o : board.c headers.h main.c moves.c
	gcc -c board.c

moves.o : board.c headers.h main.c moves.c
	gcc -c moves.c

clear : 
	rm *.o chess

