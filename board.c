#include <stdio.h>
#include <stdlib.h>
#include "headers.h"


int start[8][8] = {
	{rook, knight, bishop, queen, king, bishop, knight, rook},
	{pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
	{x, x, x, x, x, x, x, x},
	{x, x, x, x, x, x, x, x},
	{x, x, x, x, x, x, x, x}, 
	{x, x, x, x, x, x, x, x}, 
	{-pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn},
	{-rook, -knight, -bishop, -queen, -king, -bishop, -knight, -rook}
};

void initialize_board() {
	int i, j;
	for(i = 0; i < 8; i++) 
		for(j = 0; j < 8; j++)
			board[i][j] = start[i][j];
}

void print_board() {
	//	setlocale(LC_ALL, "");
	int i, j;
	char *piece;
	piece = (char *)malloc(128*sizeof(char));
	for(i = 7; i >= 0; i--) {
		printf("\n");
		for(j = 0; j < 8; j++) {
			if(j == 0)
				printf("%d  ", i + 1);
			switch(board[i][j]) {
				case x :
					piece = " - ";
					printf("%s", piece);
					break;
				case pawn : 
					printf(" P ");
					//	wprintf(L" \u2659 ");
					//	print_wpawn();
					break;
				case bishop : 
					printf(" B ");
					//	wprintf(L" \u2657 ");
					//	print_wbishop();
					break;
				case knight : 
					printf(" N ");
					//	wprintf(L" \u2658 ");
					//	print_wknight();
					break;
				case rook : 
					printf(" R ");
					//	wprintf(L" \u2656 ");
					//	print_wrook();
					break;
				case queen : 
					printf(" Q ");
					//	wprintf(L" \u2655 ");
					//	print_wqueen();
					break;
				case king : 
					printf(" K ");
					//	wprintf(L" \u2654 ");
					//	print_wking();
					break;
				case -pawn : 
					printf(" p ");
					//	wprintf(L" \u265F ");
					//	print_bpawn();
					break;
				case -bishop : 
					printf(" b ");
					//	wprintf(L" \u265D ");
					//	print_bbishop();
					break;	
				case -knight : 
					printf(" n ");
					//	wprintf(L" \u265E ");
					//	print_bknight();
					break;
				case -rook : 
					printf(" r ");
					//	wprintf(L" \u265C ");
					//	print_brook();
					break;
				case -queen : 
					printf(" q ");
					//	wprintf(L" \u265B ");
					//	print_bqueen();
					break;
				case -king : 
					printf(" k ");
					//	wprintf(L" \u265A ");
					//	print_bking();
					break;
			}
		}
	}
	printf("\n");
	printf("\n    a  b  c  d  e  f  g  h\n");
}

void change_board(int move1, int move2, int move3, int move4) {
	board[move4][move3] = board[move2][move1];
	board[move2][move1] = x;
	print_board();
}

