#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
//#include <"print_char.h">


#define pawn 1
#define bishop 2
#define knight 3
#define rook 4
#define queen 5
#define king 6
#define x 0


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

int board[8][8];

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
			switch(board[i][j]) {
				case x :
					piece = " . ";
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
}


int main() {
	printf("Welcome to CHESS!!\n\n");
	initialize_board();
	
	char *command;
	command  = (char *)malloc(128);
	
	while(1) {
		printf("Command -> ");
		scanf("%s", command);
		if(strcmp(command, "quit") == 0)
			return 0;
		else if(strcmp(command, "new") == 0) {
			initialize_board();
			print_board();
		}
		else if(command[0] >= 'a' && atoi(command + 0) <= 'h' && atoi(command + 1) >= 1 && atoi(command + 1) <= 8 && command[2] >= 'a' && command[2] <= 'h' && atoi(command + 3) >= 1 && atoi(command + 3) <= 8) {
			int move1, move2, move3, move4;
			
			move1 = command[0] - 'a';
			move2 = command[1] - '1';
			move3 = command[2] - 'a';
			move4 = command[3] - '1';
		/*	board[move4][move3] = board[move2][move1];
			board[move2][move1] = x;
			print_board(); */


			switch(board[move2][move1]) {
				case x :
					printf("Move not possible!!\n");
					continue;
				case pawn : 
					if((board[move4][move3] == 0) && (move4 == (move2 + 1)) && (move1 == move3)) {
						board[move4][move3] = board[move2][move1];
						board[move2][move1] = x;
						print_board();
					}	
					else if((board[move4][move3] != 0) && (move3 == (move1 + 1)) && (move4 == (move2 + 1))) {
						board[move4][move3] = board[move2][move1];
						board[move2][move1] = x;
						print_board();
					}
					else if((board[move4][move3] != 0) && (move3 == (move1 - 1)) && (move4 == (move2 + 1))) {
						board[move4][move3] = board[move2][move1];
						board[move2][move1] = x;
						print_board();
					}
					else { 
						printf("Move not possible!!\n");
						continue;
					}
					break;
				case bishop : { 
					int i, j, k = 0, count = 0;
					if((move3 == move1) || (move2 == move4)) {
						printf("Move not possible!!\n");
						break;	
					}
					else if((move3 > move1) && (move4 > move2) && (abs(move1 - move3) == abs(move2 - move4))) {
						for(i = move1, j = move2; i < move3 && j < move4; i++, j++, k++) {
							if(board[j][i] == x)
								count++;
							else 
								continue;
						}
						if(count == k) {
							board[move4][move3] = board[move2][move1];
							board[move2][move1] = x;
							print_board();
						}
					}
					else if((move3 > move1) && (move4 < move2) && (abs(move1-move3) == abs(move2 - move4))) {
						for(i = move1, j = move2; i < move3 && j < move4; i++, j--, k++) {
							if(board[j][i] == x)
								count++;
							else 
								continue;
						}
						if(count == k) {
							board[move4][move3] = board[move2][move1];
							board[move2][move1] = x;
							print_board();
						}
					}
					else if((move3 < move1) && (move4 < move2) && (abs(move1-move3) == abs(move2 - move4))) {
						for(i = move1, j = move2; i < move3 && j < move4; i--, j--, k++) {
							if(board[j][i] == x)
								count++;
							else 
								continue;
						}
						if(count == k) {
							board[move4][move3] = board[move2][move1];
							board[move2][move1] = x;
							print_board();
						}
					}
					else if((move3 < move1) && (move4 > move2) && (abs(move1-move3) == abs(move2 - move4))) {
						for(i = move1, j = move2; i < move3 && j < move4; i--, j++, k++) {
							if(board[j][i] == x)
								count++;
							else 
								continue;
						}
						if(count == k) {
							board[move4][move3] = board[move2][move1];
							board[move2][move1] = x;
							print_board();
						}
					}
					else {
						printf("Move not possible!!");
						continue;
					}
				}
	

	
				case rook : {
					
					
				}
			/*	case knight : 
				case queen : 
				case king : 
				case -pawn : 
				case -bishop : 
				case -knight : 
				case -rook : 
				case -queen : 
				case -king : */


			}
		}
		else
			printf("Invalid move!!\n");
	}
	return 0;
}


