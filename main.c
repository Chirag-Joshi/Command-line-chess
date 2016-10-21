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
			if(j == 0)
				printf("%d  ", i + 1);
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
	//if(i == 0 && j == 7)
	printf("\n    a  b  c  d  e  f  g  h\n");
}

void change_board(int move1, int move2, int move3, int move4) {
	board[move4][move3] = board[move2][move1];
	board[move2][move1] = x;
	print_board();
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		if(!strcmp(argv[1], "-h")) {
			printf("Usage is ./chess\n");
			return 0;
		}
	}
	printf("Welcome to CHESS!!\n\n");
	printf("Enter 'new' to start new game.\nEnter simple moves like 'a2a3' to move.\n\n");
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
					if(board[move4][move3] > 0) {
						printf("Move not possible!!\n");
						break;
					} 
					else if((board[move4][move3] == 0) && (move4 == (move2 + 1)) && (move1 == move3)) {
						change_board(move1, move2, move3, move4);
					}	
					else if((board[move4][move3] < 0) && (move3 == (move1 + 1)) && (move4 == (move2 + 1))) {
						change_board(move1, move2, move3, move4);
					}
					else if((board[move4][move3] < 0) && (move3 == (move1 - 1)) && (move4 == (move2 + 1))) {
						change_board(move1, move2, move3, move4);
					}
					else { 
						printf("Move not possible!!\n");
						continue;
					}
					break;
				case bishop : {
						int i, j, k = 0, count = 0;
						//Checking if valid move for bishop and last piece is not positive
						if((move3 == move1) || (move2 == move4) || (board[move4][move3] > 0)) {
							printf("Move not possible!! bishop - last piece is wrong or invalid move for bishop\n");
							break;
						}

						//Moving bishop diagonally up to right side
						else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and dest are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i++, j++, k++) {
								if(board[j][i] == x)
									count++;
								else 
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! bishop - middle places not empty\n");
								break;
							}
						}
						
						//Moving bishop diagonally up to left side
						else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and dest are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i--, j++, k++) {
								if(board[j][i] == x) 
									count++;
								else
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! bishop - moddle places not empty diag up left\n");
								break;
							}
						}
						
						//Moving bishop diagonally down to right side
						else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and destination are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i++, j--, k++) {
								if(board[j][i] == x)
									count++;
								else
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! bishop - middle places not empty diag down right\n");
								break;
							}
						}					
						
						//Moving bishop diagonally down to left side
						else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and destination are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i--, j--, k++) {
								if(board[j][i] == x)
									count++;
								else
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! bishop - middle places not empty diag down left\n");
								break;
							}
						}
						
						//For any other problem
						else {
							printf("Move not possible - bishop shitload went wrong\n");
							break;
						}
				}

				case rook : {
						    int i, count = 0, k = 0;
						    //Checking if legal move for rook
						    if((board[move4][move3] > 0)) {
							    printf("Move not possible!! rook - end point has wrong piece\n");
							    break;
						    }
						    //Moving rook vertically upwards
						    else if((move1 == move3) && (move2 < move4)) {
							    //Checking if all places from src to dest. are empty
							    for(i = move2 + 1; i < move4; i++, k++) {
								    if(board[i][move3] == x)
									    count++;
								    else 
									    continue;
							    }
							    if(count == k) {
								    change_board(move1, move2, move3, move4);
								    break;
							    } 
							    else {
								    printf("Move not possible rook - middle places not empty\n");
								    break;
							    }
						    }		
						    //Moving rook vertically downward
						    else if((move1 == move3) && (move2 > move4)) {
							    //Checking if all places from src to dest are empty
							    for(i = move4; i < move2; i++, k++) {
								    if(board[i][move3] == x) 
									    count++;
								    else
									    continue;
							    }
							    if(count == k) {
								    change_board(move1, move2, move3, move4);
								    break;
							    } 
							    else {
								    printf("Move not possible rook - middle places not empty\n");
								    break;
							    }
						    }
						    //Moving rook horizontally to right
						    else if((move2 == move4) && (move3 > move1)) {
							    //Checking if all places from src to dest are empty
							    for(i = move1 + 1; i < move3; i++, k++) {
								    if(board[move4][i] == x)
									    count++;
								    else 
									    continue;
							    }
							    if(count == k) {
								    change_board(move1, move2, move3, move4);
								    break;
							    } 
							    else {
								    printf("Move not possible rook - middle places not empty\n");
								    break;
							    }
						    }
						    //Moving rook horizontally left
						    else if((move2 == move4) && (move3 < move1)) {
							    //Checking if all places from src to dest are empty
							    for(i = move3; i < move1; i++, k++) {
								    if(board[move4][i] == x)
									    count++;
								    else
									    continue;
							    }
							    if(count == k) {
								    change_board(move1, move2, move3, move4);
								    break;
							    } 
							    else {
								    printf("Move not possible rook - middle places not empty\n");
								    break;
							    }
						    }
						    //For any other problem
						    else {
							    printf("Move not possible!! rook - some shitload went wrong\n");
							    continue;
						    }
					    }	
				case knight : {



					      }
				case queen : {
						     int i, j, k = 0, count = 0;
						     //Checking if endpoint has correct piece
						     if(board[move4][move3] > 0) {
							     printf("Move not possible queen end point has wrong piece\n");
							     break;
						     }
						     //Moving queen vertically upwards
						     else if((move1 == move3) && (move2 < move4)) {
							     //Checking if all places from src to dest. are empty
							     for(i = move2 + 1; i < move4; i++, k++) {
								     if(board[i][move3] == x)
									     count++;
								     else 
									     continue;
							     }
							     if(count == k) {
								     change_board(move1, move2, move3, move4);
							     } 
							     else {
								     printf("Move not possible queen vertically up - middle places not empty\n");
								     break;
							     }
						     }
						     //Moving queen vertically downwards		
						     else if((move1 == move3) && (move2 > move4)) {
							     //Checking if all places from src to dest are empty
							     for(i = move4; i < move2; i++, k++) {
								     if(board[i][move3] == x) 
									     count++;
								     else
									     continue;
							     }
							     if(count == k) {
								     change_board(move1, move2, move3, move4);
							     } 
							     else {
								     printf("Move not possible queen vertically down - middle places not empty\n");
								     break;
							     }
						     }
						     //Moving queen horizontally right
						     else if((move2 == move4) && (move3 > move1)) {
							     //Checking if all places from src to dest are empty
							     for(i = move1 + 1; i < move3; i++, k++) {
								     if(board[move4][i] == x)
									     count++;
								     else 
									     continue;
							     }
							     if(count == k) {
								     change_board(move1, move2, move3, move4);
							     } 
							     else {
								     printf("Move not possible queen horizontally right - middle places not empty\n");
								     break;
							     }
						     }
						     //Moving queen horizontally left
						     else if((move2 == move4) && (move3 < move1)) {
							     //Checking if all places from src to dest are empty
							     for(i = move3; i < move1; i++, k++) {
								     if(board[move4][i] == x)
									     count++;
								     else
									     continue;
							     }
							     if(count == k) {
								     change_board(move1, move2, move3, move4);
							     } 
							     else {
								     printf("Move not possible queen horizontally left - middle places not empty\n");
								     break;
							     }
						     }

						//Moving queen diagonally up to right side
						else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and dest are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i++, j++, k++) {
								if(board[j][i] == x)
									count++;
								else 
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! queen - middle places not empty diag up right\n");
								break;
							}
						}
						
						//Moving queen diagonally up to left side
						else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and dest are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i--, j++, k++) {
								if(board[j][i] == x) 
									count++;
								else
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! queen - moddle places not empty diag up left\n");
								break;
							}
						}
						
						//Moving queen diagonally down to right side
						else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and destination are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i++, j--, k++) {
								if(board[j][i] == x)
									count++;
								else
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! queen - middle places not empty diag down right\n");
								break;
							}
						}					
						
						//Moving queen diagonally down to left side
						else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
							//Checking if middle places between src and destination are empty
							for(i = (move1 + 1), j = (move2 + 1); i < move3 && j < move4; i--, j--, k++) {
								if(board[j][i] == x)
									count++;
								else
									continue;
							}
							if(count == k) {
								change_board(move1, move2, move3, move4);
								break;
							}
							else {
								printf("Move not possible!! queen - middle places not empty diag down left\n");
								break;
							}
						}
						
						//For any other problem
						else {
							printf("Move not possible - queen shitload went wrong\n");
							break;
						}


					     } 
					     /*	case king : 
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


