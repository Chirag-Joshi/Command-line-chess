#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "headers.h"


int main(int argc, char *argv[]) {
	if(argc > 1) {
		if(!strcmp(argv[1], "-h")) {
			printf("Usage is ./chess\n");
			return 0;
		}
	}

	char player1[128], player2[128];

	printf("Welcome to CHESS!!\n\n");
	printf("Player 1 name -> ");
	scanf("%s", player1);
	
	while(1) {
		printf("Player 2 name -> ");
		scanf("%s", player2);
		if(strcmp(player1, player2) == 0) {
			printf("Name already taken!\n");
			continue;
		}
		else
			break;
	}

	printf("Enter 'new' to start new game.\nEnter simple moves like 'a2a3' to move.\n\n");
	initialize_board();
	turn = OTHER;

	char *command;
	command  = (char *)malloc(128);
	while(1) {
		if(turn == OTHER) {
			printf("Command -> ");
			scanf("%s", command);
			if(strcmp(command, "quit") == 0) {
				printf("Thanks for playing!!\n");
				return 0;
			}
			else if(strcmp(command, "new") == 0) {
				initialize_board();
				print_board();
				turn = WHITE;
			}

			else {
				printf("Invalid command!!\n");
				continue;
			}
		}

		else if(turn == WHITE) {
			printf("%s -> ", player1);
			scanf("%s", command);
			if(strcmp(command, "quit") == 0) {
				printf("Thanks for playing!!\n");
				return 0;
			}
	
			else if(command[0] >= 'a' && atoi(command + 0) <= 'h' && atoi(command + 1) >= 1 
					&& atoi(command + 1) <= 8 && command[2] >= 'a' && command[2] <= 'h' 
					&& atoi(command + 3) >= 1 && atoi(command + 3) <= 8) {
				int move1, move2, move3, move4;

				move1 = command[0] - 'a';
				move2 = command[1] - '1';
				move3 = command[2] - 'a';
				move4 = command[3] - '1';

				switch(board[move2][move1]) {
					case x :
							printf("Move not possible!!\n");
							continue;
					case pawn : {
							move_w_pawn(move1, move2, move3, move4);
							continue;
						    }

					case bishop : {

							move_w_bishop(move1, move2, move3, move4);
							continue;
						      }

					case rook : {
							move_w_rook(move1, move2, move3, move4);
							continue;
						    }	
					case knight :{
							move_w_knight(move1, move2, move3, move4);
							continue;
						     }
					case queen : {
							move_w_queen(move1, move2, move3, move4);
							continue;
						     } 
					case king : {
							move_w_king(move1, move2, move3, move4);
							continue;
						    }
					default : {
							printf("It is %s's turn.\n", player1);
							continue;
						  }
				}
			}
			else {
				printf("Invalid move!!\n");
				continue;
			}
		}

		else if(turn == BLACK) {
			printf("%s -> ", player2);
			scanf("%s", command);
			if(strcmp(command, "quit") == 0) {
				printf("Thanks for playing!!\n");
				return 0;
			}	

			else if(command[0] >= 'a' && atoi(command + 0) <= 'h' && atoi(command + 1) >= 1 
					&& atoi(command + 1) <= 8 && command[2] >= 'a' && command[2] <= 'h' 
					&& atoi(command + 3) >= 1 && atoi(command + 3) <= 8) {
				int move1, move2, move3, move4;

				move1 = command[0] - 'a';
				move2 = command[1] - '1';
				move3 = command[2] - 'a';
				move4 = command[3] - '1';

				switch(board[move2][move1]) {
					case x :
						printf("Move not possible!!\n");
						continue;
				
					case -pawn : { 
							move_b_pawn(move1, move2, move3, move4);
							continue;
						     }

					case -bishop : {
							move_b_bishop(move1, move2, move3, move4);
							continue;
						       }

					case -rook : {
							move_b_rook(move1, move2, move3, move4);
							continue;
						     }
					case -queen : {
							move_b_queen(move1, move2, move3, move4);
							continue;
						      }
					case -king : {
							move_b_king(move1, move2, move3, move4);
							continue;
						     }
					case -knight : {
							move_b_knight(move1, move2, move3, move4);
							continue;
						       }
					default : {
							printf("It is %s's turn.\n", player2);
							continue;
						  }
				}
			}

			else {
				printf("Invalid move!!\n");
				continue;
			}
		}





/*

		if(strcmp(command, "quit") == 0)
			return 0;
		else if(strcmp(command, "new") == 0) {
			if(new_cnt > 0) {
				printf("Are you sure you want a new game? Previous progress will be lost. y/n  ");
				scanf("%c", &new_option); 
				printf("\n");	
				if(new_option == 'y') {		
					initialize_board();
					print_board();
					new_cnt++;
					continue;
				}
				else if(new_option == 'n')
					continue;

				else {
					printf("Invalid option!\n");
					continue;
				}
			}
			else {
				initialize_board();
				print_board();
				new_cnt++;
			}
		}
		else if(command[0] >= 'a' && atoi(command + 0) <= 'h' && atoi(command + 1) >= 1 
			&& atoi(command + 1) <= 8 && command[2] >= 'a' && command[2] <= 'h' 
			&& atoi(command + 3) >= 1 && atoi(command + 3) <= 8) {
			int move1, move2, move3, move4;

			move1 = command[0] - 'a';
			move2 = command[1] - '1';
			move3 = command[2] - 'a';
			move4 = command[3] - '1';

			switch(board[move2][move1]) {
				case x :
					printf("Move not possible!!\n");
					continue;
				case pawn : {
						    move_w_pawn(move1, move2, move3, move4);
						    continue;
					    }

				case bishop : {

						      move_w_bishop(move1, move2, move3, move4);
						      continue;
					      }

				case rook : {
						    move_w_rook(move1, move2, move3, move4);
						    continue;
					    }	
				case knight :{
						     move_w_knight(move1, move2, move3, move4);
						     continue;
					     }
				case queen : {
						     move_w_queen(move1, move2, move3, move4);
						     continue;
					     } 
				case king : {
						    move_w_king(move1, move2, move3, move4);
						    continue;
					    }

				case -pawn : { 
						     move_b_pawn(move1, move2, move3, move4);
						     continue;
					     }


				case -bishop : 	{
							move_b_bishop(move1, move2, move3, move4);
							continue;
						}

				case -rook : {
						     move_b_rook(move1, move2, move3, move4);
						     continue;
					     }
				case -queen : {
						      move_b_queen(move1, move2, move3, move4);
						      continue;
					      }
				case -king : {
						     move_b_king(move1, move2, move3, move4);
						     continue;
					     }
				case -knight : {
						       move_b_knight(move1, move2, move3, move4);
						       continue;
					       }
			}
		}*/
		else
			printf("Invalid move!!\n");
	}
	return 0;
}


