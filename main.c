#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"


int main(int argc, char *argv[]) {
	if(argc > 1) {
		if(!strcmp(argv[1], "-h")) {
			printf("Usage is ./program\n");
			return 0;
		}
	}

	char player1[128], player2[128];
	//For checking check
	int white_check_flag = 0, black_check_flag = 0;
	
	//For casteling white 
	w_rook_flag = 0;
	w_king_flag = 0;
	//For casteling black
	b_rook_flag = 0;
	b_king_flag = 0;

	printf("Welcome to CHESS!!\n\n");


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
				turn = WHITE;
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
				print_board();
			}
			else if(strcmp(command, "help") == 0) {
				printf("This is the game of Chess.\n"
				       "Enter simple moves like 'a2a3' or 'e2f4' to move pieces.\n"
				       "Type 'new' to start a new game or 'load' to load pre-exesting game.\n"
				       "You can type 'help' in an ongoing game.\n");
			}

			else {
				printf("Invalid command!!\n");
				continue;
			}
		}

		else if(turn == WHITE) {
		//	system("clear");
			//Checking if there was check on white by black, if there was sets the flag
			if(white_check() == 1) {
				printf("Check on %s.\n", player1);
				white_check_flag = 1;
			}

			//For ending game in favour of white as black flag was set, 2 cases
			if(black_check_flag == 1) {
				//Case 1 : Black is still in check, so white wins
				if(black_check() == 1) {
					printf("%s Wins!!\n", player1);
					return 0;
				}
				//Case 2 : Black acted accordingly and is not in check
				else {
					black_check_flag = 0;
					continue;
				}
			}

			printf("%s -> ", player1);
			scanf("%s", command);
			if(strcmp(command, "quit") == 0) {
				printf("Thanks for playing!!\n");
				return 0;
			}
			else if(strcmp(command, "help") == 0) {
				printf("This is the game of Chess.\n"
				       "Enter simple moves like 'a2a3' or 'e2f4' to move pieces.\n"
				       "Type 'save' to save the current game.\n"
				       "To castle, use the commands 'castlekingside' and 'castlequeenside'\n");
			}
			else if(strcmp(command, "castlekingside") == 0) {
				if(white_castle_kingside() == 1) {
					print_board();
					turn = BLACK;
					continue;
				}
				else {
					printf("Move not possible!! castleing king side\n");
					continue;
				}
			}
			else if(strcmp(command, "castlequeenside") == 0) {
				if(white_castle_queenside() == 1) {
					print_board();
					turn = BLACK;
					continue;
				}
				else {
					printf("Move not possible!! castle king side\n");
					continue;
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
							    if(move_w_pawn(move1, move2, move3, move4) == 1) {
								    simulate_board(move1, move2, move3, move4);
								    if(white_check() == 1) {
									    printf("%s Wins!!\n", player2);
									    return 0;
								    }
								    rev_simulate_board(move1, move2, move3, move4);
								    change_board(move1, move2, move3, move4);
								    turn = BLACK;
								    continue;
							    }
							    else {
								    printf("Move not possible!! white pawn\n");
								    continue;
							    }
							    continue;
						    }

					case bishop : {
							      if(move_w_bishop(move1, move2, move3, move4) == 1) {
								      simulate_board(move1, move2, move3, move4);
								      if(white_check() == 1) {
									      printf("%s Wins!!\n", player2);
									      return 0;
								      }
								      rev_simulate_board(move1, move2, move3, move4);
								      change_board(move1, move2, move3, move4);
								      turn = BLACK;
								      continue;
							      }
							      else {
								      printf("Move not possible!! white bishop\n");
								      continue;
							      }
							      continue;
						      }

					case rook : {
							    if(move_w_rook(move1, move2, move3, move4) == 1) {
								    simulate_board(move1, move2, move3, move4);
								    if(white_check() == 1) {
									    printf("%s Wins!!\n", player2);
									    return 0;
								    }
								    rev_simulate_board(move1, move2, move3, move4);
								    change_board(move1, move2, move3, move4);
								    turn = BLACK;
								    if(w_rook_flag == 0)
									    w_rook_flag = 1;
								    continue;
							    }
							    else {
								    printf("Move not possible!! white rook\n");
								    continue;
							    }
							    continue;
						    }	
					case knight :{
							     if(move_w_knight(move1, move2, move3, move4) == 1) {
								     simulate_board(move1, move2, move3, move4);
								     if(white_check() == 1) {
									     printf("%s Wins!!\n", player2);
									     return 0;
								     }
								     rev_simulate_board(move1, move2, move3, move4);
								     change_board(move1, move2, move3, move4);
								     turn = BLACK;
								     continue;
							     }
							     else {
								     printf("Move not possible!! white knight\n");
								     continue;
							     }
							     continue;
						     }
					case queen : {
							     if(move_w_queen(move1, move2, move3, move4) == 1) {
								     simulate_board(move1, move2, move3, move4);
								     if(white_check() == 1) {
									     printf("%s Wins!!\n", player2);
									     return 0;
								     }
								     rev_simulate_board(move1, move2, move3, move4);
								     change_board(move1, move2, move3, move4);
								     turn = BLACK;
								     continue;
							     }
							     else {
								     printf("move not possible!! white queen\n");
								     continue;
							     }
							     continue;
						     } 
					case king : { 
							    if(move_w_king(move1, move2, move3, move4) == 1) {
								    if(w_king_flag == 0)
									    w_king_flag = 1;
								    simulate_board(move1, move2, move3, move4);
								    if(white_check() == 1) {
									    printf("%s Wins!!\n", player2);
									    return 0;
								    }
								    rev_simulate_board(move1, move2, move3, move4);
								    change_board(move1, move2, move3, move4);
								    turn = BLACK;
								    continue;
							    }
							    else {
								    printf("move not possible!! white king\n");
								    continue;
							    }
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
			
		//	system("clear");
			//For checking whether there is a check on black by white
			if(black_check() == 1) {
				printf("Check on %s.\n", player2);
				black_check_flag = 1;
			}

			//For ending game in favour of black as white flag was set, 2 cases
			if(white_check_flag == 1) {
				//Case 1 : White is still in check, so black wins
				if(white_check() == 1) {
					printf("%s Wins!!\n", player2);
					return 0;
				}
				//Case 2 : White acted accordingly and is not in check
				else {
					white_check_flag = 0;
					continue;
				}
			}
			printf("%s -> ", player2);
			scanf("%s", command);
			if(strcmp(command, "quit") == 0) {
				printf("Thanks for playing!!\n");
				return 0;
			}	
			else if(strcmp(command, "castlekingside") == 0) {
				if(black_castle_kingside() == 1) {
					print_board();
					turn = WHITE;
					continue;
				}
				else {
					printf("Move not possible!! castleing king side\n");
					continue;
				}
			}
			else if(strcmp(command, "castlequeenside") == 0) {
				if(black_castle_queenside() == 1) {
					print_board();
					turn = WHITE;
					continue;
				}
				else {
					printf("Move not possible!! castle king side\n");
					continue;
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

					case -pawn : { 
							     if(move_b_pawn(move1, move2, move3, move4) == 1) {
								     simulate_board(move1, move2, move3, move4);
								     if(black_check() == 1) {
									     printf("%s Wins!!\n", player1);
									     return 0;
								     }
								     rev_simulate_board(move1, move2, move3, move4);
								     change_board(move1, move2, move3, move4);
								     turn = WHITE;
								     continue;
							     }
							     else {
								     printf("Move not possible!! black pawn\n");
								     continue;
							     }
							     continue;
						     }

					case -bishop : {
							       if(move_b_bishop(move1, move2, move3, move4) == 1) {
								       simulate_board(move1, move2, move3, move4);
								       if(black_check() == 1) {
									       printf("%s Wins!!\n", player1);
									       return 0;
								       }
								       rev_simulate_board(move1, move2, move3, move4);
								       change_board(move1, move2, move3, move4);
								       turn = WHITE;
								       continue;
							       }
							       else {
								       printf("Move not possible!! black bishop\n");
								       continue;
							       }
							       continue;
						       }

					case -rook : { 
							     if(move_b_rook(move1, move2, move3, move4) == 1) {
								     simulate_board(move1, move2, move3, move4);
								     if(black_check() == 1) {
									     printf("%s Wins!!\n", player1);
									     return 0;
								     }
								     rev_simulate_board(move1, move2, move3, move4);
								     change_board(move1, move2, move3, move4);
								     turn = WHITE;
								     if(b_rook_flag == 0)
									     b_rook_flag = 1;
								     continue;
							     }
							     else {
								     printf("Move not possible!! black rook\n");
								     continue;
							     }
							     continue;
						     }
					case -knight : { 
							       if(move_b_knight(move1, move2, move3, move4) == 1) {
								       simulate_board(move1, move2, move3, move4);
								       if(black_check() == 1) {
									       printf("%s Wins!!\n", player1);
									       return 0;
								       }
								       rev_simulate_board(move1, move2, move3, move4);
								       change_board(move1, move2, move3, move4);
								       turn = WHITE;
								       continue;
							       }
							       else {
								       printf("Move not possible!! black knight\n");
								       continue;
							       }
							       continue;
						       }
					case -queen : { 
							      if(move_b_queen(move1, move2, move3, move4) == 1) {
								      simulate_board(move1, move2, move3, move4);
								      if(black_check() == 1) {
									      printf("%s Wins!!\n", player1);
									      return 0;
								      }
								      rev_simulate_board(move1, move2, move3, move4);
								      change_board(move1, move2, move3, move4);
								      turn = WHITE;
								      continue;
							      }
							      else {
								      printf("Move not possible!! black queen\n");
								      continue;
							      }
							      continue;
						      }
					case -king : {
							     if(move_b_king(move1, move2, move3, move4) == 1) {
								     if(b_king_flag == 0)
									     b_king_flag = 1;
								     simulate_board(move1, move2, move3, move4);
								     if(black_check() == 1) {
									     printf("%s Wins!!\n", player1);
									     return 0;
								     }
								     rev_simulate_board(move1, move2, move3, move4);
								     change_board(move1, move2, move3, move4);
								     turn = WHITE;
								     continue;
							     }
							     else {
								     printf("Move not possible!! black king\n");
								     continue;
							     }
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

		else
			printf("Invalid move!!\n");
	}
	return 0;
}


