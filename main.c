/* This file is part of Command Line Chess.
 * Copyright (C) 2016 Chirag Joshi
 * Command line chess is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */    

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

	char choice[128];
	//For casteling white 
	w_rook_flag = 0;
	w_king_flag = 0;
	//For casteling black
	b_rook_flag = 0;
	b_king_flag = 0;

	FILE *fp;
	printf("Welcome to CHESS!!\n\n");


	printf("Enter 'new' to start new game.\nOr enter 'load' to load a previously saved game.\nEnter simple moves like 'a2a3' to move.\n\n");
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
				printf("Which game?\nPress 1 for 1 Player game.\nPress 2 for 2 Player game.\n");

				while(1) {
					scanf("%s", choice);
					if(strcmp(choice, "1") == 0) {
						player = COMP;
						printf("Enter your name : ");
						scanf("%s", player1);
						break;
					}
					else if(strcmp(choice, "2") == 0) {
						player = TWO;
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
						break;
					}
					else {
						printf("Invalid Option!!\n");
						continue;
					}
				}
				print_board();
			}
			else if(strcmp(command, "load") == 0) {
				fp = fopen("savefile", "r");
				if(fp == NULL) {
					printf("No saved game exests.\n");
					continue;
				}
				int temp;
				fscanf(fp, "%d %d", &temp, &turn); 
				fscanf(fp, "%d %d", &white_check_flag, &black_check_flag);
				fscanf(fp, "%d %d %d %d", &w_king_flag, &w_rook_flag, &b_king_flag, &b_rook_flag);
				fscanf(fp, "%s %s", player1, player2);
				int i, j;
				for(i = 0; i < 8; i++)
					for(j = 0; j < 0; j++)
						fscanf(fp, "%d", &board[i][j]);
				fclose(fp);
				print_board();
				continue;
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

			else if(strcmp(command, "save") == 0) {
				fp = fopen("savefile", "w");
				if(fp == NULL) {
					print_board();
					printf("Error, cannot save the game.\n");
					continue;
				}
				fprintf(fp, "%d%d", player, WHITE);
				fprintf(fp, "%d%d", white_check_flag, black_check_flag);
				fprintf(fp, "%d%d%d%d", w_king_flag, w_rook_flag, b_king_flag, b_rook_flag);
				fprintf(fp, "%s%s", player1, player2);
				int i, j;
				for(i = 0; i < 8; i++)
					for(j = 0; j < 8; j++)
						fprintf(fp, "%d", board[i][j]);
				fclose(fp);
				print_board();
				printf("Game has been saved!\n");
				continue;
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
					print_board();
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
					print_board();
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
						print_board();
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
								    print_board();
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
								      print_board();
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
								    print_board();
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
								     print_board();
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
								     print_board();
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
								    print_board();
								    printf("move not possible!! white king\n");
								    continue;
							    }
							    continue;
						    }
					default : {
							  print_board();
							  printf("It is %s's turn.\n", player1);
							  continue;
						  }
				}
			}
			else {
				print_board();
				printf("Invalid move!!\n");
				continue;
			}
		}

		else if(turn == BLACK && player == TWO) {

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
					print_board();
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
					print_board();
					printf("Move not possible!! castle king side\n");
					continue;
				}
			}

			else if(strcmp(command, "help") == 0) {
				printf("This is the game of Chess.\n"
						"Enter simple moves like 'a7a5' or 'c8d6' to move pieces.\n"
						"Type 'save' to save the current game.\n"
						"To castle, use the commands 'castlekingside' and 'castlequeenside'\n");
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
						print_board();
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
								     print_board();
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
								       print_board();
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
								     print_board();
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
								       print_board();
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
								      print_board();
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
								     print_board();
								     printf("Move not possible!! black king\n");
								     continue;
							     }
							     continue;
						     }

					default : {
							  print_board();
							  printf("It is %s's turn.\n", player2);
							  continue;
						  }
				}
			}

			else {
				print_board();
				printf("Invalid move!!\n");
				continue;
			}
		}

		else if(turn == BLACK && player == COMP) { 
			kill_structure *kill_struct;
			kill_struct = (kill_structure *)malloc(sizeof(int)*65536);

			normal_structure *normal_struct;
			normal_struct = (normal_structure *)malloc(sizeof(int)*65536);

			best_pawn_structure *best_pawn;
			best_pawn = (best_pawn_structure *)malloc(sizeof(int)*65536);

			best_knight_structure *best_knight;
			best_knight = (best_knight_structure *)malloc(sizeof(int)*65536);

			best_rook_structure *best_rook;
			best_rook = (best_rook_structure *)malloc(sizeof(int)*65536);

			best_bishop_structure *best_bishop;
			best_bishop = (best_bishop_structure *)malloc(sizeof(int)*65536);

			best_queen_structure *best_queen;
			best_queen = (best_queen_structure *)malloc(sizeof(int)*65536);

			best_move_structure best_move[16];
			int kill_struct_count, normal_struct_count; 
			int best_pawn_count = 0, best_knight_count = 0, best_rook_count = 0, best_bishop_count = 0, best_queen_count = 0, best_count = 0, kill_count = 0;

			int pawn_kill_no = 0;
			int i, j, k, l, s, t, move;
			int loop_count, if_count;
			//Genrating all possible moves for black pieces
			for(i = 0; i < 8; i++) {
				for(j = 0; j < 8; j++) {
					kill_struct_count = 0;
					normal_struct_count = 0;
					switch (board[i][j]) {
						//If the piece on board is pawn
						case -pawn : {
								     kill_struct_count = 0;
								     normal_struct_count = 0;
								     //Checking all moves for pawn
								     for(k = 0; k < 8; k++) {
									     for(l = 0; l < 8; l++) {
										     //If a move is legal for pawn
										     if(move_b_pawn(j, i, l, k) == 1) {
											     //If the pawn kills a white piece, store in kill structure
											     if(board[k][l] > 0) {
												     kill_struct[kill_struct_count].move1 = i;
												     kill_struct[kill_struct_count].move2 = j;
												     kill_struct[kill_struct_count].move3 = k;
												     kill_struct[kill_struct_count].move4 = l;
												     kill_struct_count++;
											     }

											     //If the pawn does not kill anyone, store in normal
											     else{
												     normal_struct[normal_struct_count].move1 = i;
												     normal_struct[normal_struct_count].move2 = j;
												     normal_struct[normal_struct_count].move3 = k;
												     normal_struct[normal_struct_count].move4 = l;
												     normal_struct_count++;
											     }
										     }
										     else
											     continue;
									     }
								     }


								     //If the pawn kills no one, kill struct count will be 0						 
								     k = 0;
								     if(kill_struct_count == 0) {
									     pawn_kill_no = 1;
									     while(k != normal_struct_count) { 
										     simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
										     loop_count = 0;
										     if_count = 0;
										     //Now generating all white kills and ensuring that the moved paawn will not be killed
										     for(s = 0; s < 8; s++) {
											     for(t = 0; t < 8; t++) {
												     if((move_w_pawn(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
														     (move_w_bishop(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) && 
														     (move_w_knight(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
														     (move_w_rook(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
														     (move_w_queen(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0)) {
													     if_count++;
													     loop_count++;
												     }
												     else
													     loop_count++;



											     }
										     }
										     rev_simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
										     if(if_count == loop_count) {

											     best_pawn[best_pawn_count].move1 = normal_struct[k].move1;
											     best_pawn[best_pawn_count].move2 = normal_struct[k].move2;
											     best_pawn[best_pawn_count].move3 = normal_struct[k].move3; 
											     best_pawn[best_pawn_count].move4 = normal_struct[k].move4;
											     best_pawn[best_pawn_count].kill = 0;
											     best_pawn_count++;
										     }
										     k++;
									     }
								     }

								     //Now the pawn kills someone, even if pawn is lost, not much damage is done, do it
								     k = 0;
								     if(kill_struct_count != 0) {
									     while(k != kill_struct_count) {
										     best_pawn[best_pawn_count].move1 = kill_struct[k].move1;
										     best_pawn[best_pawn_count].move2 = kill_struct[k].move2;
										     best_pawn[best_pawn_count].move3 = kill_struct[k].move3;
										     best_pawn[best_pawn_count].move4 = kill_struct[k].move4;
										     best_pawn[best_pawn_count].kill = piece_value(kill_struct[k].move3, kill_struct[k].move4);
										     best_pawn_count++;
										     k++;
									     }

									     best_pawn_structure temp;
									     for(i = 0; i < best_pawn_count; i++)
										     for(j = i + 1; j < best_pawn_count; j++)
											     if(best_pawn[i].kill > best_pawn[j].kill) {
												     temp = best_pawn[i];
												     best_pawn[i]= best_pawn[j]; 
												     best_pawn[j]= temp;
											     }



								     }

							     }

						case -knight : { 
								       kill_struct_count = 0;
								       normal_struct_count = 0;
								       //Checking all moves for knight
								       for(k = 0; k < 8; k++) {
									       for(l = 0; l < 8; l++) {
										       //If a move is legal for knight
										       if(move_b_knight(j, i, l, k) == 1) {
											       //If the knight kills a white piece, store in kill structure
											       if(board[k][l] > 0) {
												       kill_struct[kill_struct_count].move1 = i;
												       kill_struct[kill_struct_count].move2 = j;
												       kill_struct[kill_struct_count].move3 = k;
												       kill_struct[kill_struct_count].move4 = l;
												       kill_struct_count++;
											       }

											       //If the knight does not kill anyone, store in normal
											       else{
												       normal_struct[normal_struct_count].move1 = i;
												       normal_struct[normal_struct_count].move2 = j;
												       normal_struct[normal_struct_count].move3 = k;
												       normal_struct[normal_struct_count].move4 = l;
												       normal_struct_count++;
											       }
										       }
										       else
											       continue;
									       }
								       }


								       //For the moves where knight kills no one, store the kill value as 0 					 
								       k = 0;
								       while(k != normal_struct_count) { 
									       loop_count = 0;
									       if_count = 0;
									       simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3); //print_board(); return 0;
									       //Now generating all white moves with the destination as the moved knight and ensuring that the moved knight will not be killed
									       for(s = 0; s < 8; s++) {
										       for(t = 0; t < 8; t++) {

											       if((move_w_pawn(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													       (move_w_bishop(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													       (move_w_knight(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) && 
													       (move_w_rook(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													       (move_w_queen(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0)) {
												       if_count++;
												       loop_count++;
											       }
											       else 
												       loop_count++;


										       }
									       }
									       rev_simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3); 
									       if(loop_count == if_count) {
										       best_knight[best_knight_count].move1 = normal_struct[k].move1;
										       best_knight[best_knight_count].move2 = normal_struct[k].move2;
										       best_knight[best_knight_count].move3 = normal_struct[k].move3; 
										       best_knight[best_knight_count].move4 = normal_struct[k].move4;
										       best_knight[best_knight_count].kill = 0;
										       best_knight_count++;
									       }
									       k++;
								       }


								       //Now, when the knight does kill some pieces, store the kill value as the piece killed
								       k = 0;
								       while(k != kill_struct_count) { 
									       loop_count = 0;
									       if_count = 0;
									       simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									       //Now generating all white moves with destinaltion as the moved kinght and ensuring that the moved knight will not be killed
									       for(s = 0; s < 8; s++) {
										       for(t = 0; t < 8; t++) {
											       if((move_w_pawn(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													       (move_w_bishop(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													       (move_w_knight(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) && 
													       (move_w_rook(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													       (move_w_queen(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0)) {
												       if_count++;
												       loop_count++;
											       }
											       else 
												       loop_count++;


										       }
									       }
									       rev_simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									       if(loop_count == if_count) {
										       best_knight[best_knight_count].move1 = kill_struct[k].move1;
										       best_knight[best_knight_count].move2 = kill_struct[k].move2;
										       best_knight[best_knight_count].move3 = kill_struct[k].move3; 
										       best_knight[best_knight_count].move4 = kill_struct[k].move4;
										       best_knight[best_knight_count].kill = piece_value(best_knight[best_knight_count].move3, best_knight[best_knight_count].move4);
										       best_knight_count++;
									       }
									       k++;
								       }



								       best_knight_structure temp;
								       for(s = 0; s < best_knight_count; s++)
									       for(t = s + 1; t < best_knight_count; t++)
										       if(best_knight[s].kill > best_knight[t].kill) {
											       temp = best_knight[s];
											       best_knight[s]= best_knight[t]; 
											       best_knight[t]= temp;
										       }



							       }

						case -rook : {
								     kill_struct_count = 0;
								     normal_struct_count = 0;
								     //Checking all moves for rook
								     for(k = 0; k < 8; k++) {
									     for(l = 0; l < 8; l++) {
										     //If a move is legal for rook
										     if(move_b_rook(j, i, k, l) == 1) {;
											     //If the rook kills a white piece, store in kill structure
											     if(board[k][l] > 0) {
												     kill_struct[kill_struct_count].move1 = i;
												     kill_struct[kill_struct_count].move2 = j;
												     kill_struct[kill_struct_count].move3 = k;
												     kill_struct[kill_struct_count].move4 = l;
												     kill_struct_count++;
											     }

											     //If the rook does not kill anyone, store in normal
											     else{
												     normal_struct[normal_struct_count].move1 = i;
												     normal_struct[normal_struct_count].move2 = j;
												     normal_struct[normal_struct_count].move3 = k;
												     normal_struct[normal_struct_count].move4 = l;
												     normal_struct_count++;
											     }
										     }
										     else
											     continue;
									     }
								     }

								     //For the moves where rook kills no one, store the kill value as 0 					 
								     k = 0;
								     while(k != normal_struct_count) { 
									     loop_count = 0;
									     if_count = 0;
									     simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
									     for(s = 0; s < 8; s++) {
										     for(t = 0; t < 8; t++) {
											     //Now generating all white moves with the destination as the moved rook and ensuring that the moved rook will not be killed
											     if((move_w_pawn(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													     (move_w_bishop(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													     (move_w_knight(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) && 
													     (move_w_rook(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													     (move_w_queen(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0)) {
												     if_count++;
												     loop_count++;
											     }
											     else 
												     loop_count++;   


										     }
									     }
									     rev_simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
									     if(loop_count == if_count) {
										     best_rook[best_rook_count].move1 = normal_struct[k].move1;
										     best_rook[best_rook_count].move2 = normal_struct[k].move2;
										     best_rook[best_rook_count].move3 = normal_struct[k].move3; 
										     best_rook[best_rook_count].move4 = normal_struct[k].move4;
										     best_rook[best_rook_count].kill = 0;
										     best_rook_count++;
									     }

									     k++;
								     }


								     //Now, when the rook does kill some pieces, store the kill value as the piece killed
								     k = 0;
								     while(k != kill_struct_count) { 
									     loop_count = 0;
									     if_count = 0;
									     simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									     for(s = 0; s < 8; s++) {
										     for(t = 0; t < 8; t++) {
											     //Now generating all white moves with destinaltion as the moved kinght and ensuring that the moved rook will not be killed
											     if((move_w_pawn(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													     (move_w_bishop(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													     (move_w_knight(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) && 
													     (move_w_rook(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													     (move_w_queen(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0)) { 
												     if_count++;
												     loop_count++;
											     }
											     else 
												     loop_count++;

										     }
									     }
									     rev_simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									     if(loop_count == if_count) {
										     best_rook[best_rook_count].move1 = kill_struct[k].move1;
										     best_rook[best_rook_count].move2 = kill_struct[k].move2;
										     best_rook[best_rook_count].move3 = kill_struct[k].move3; 
										     best_rook[best_rook_count].move4 = kill_struct[k].move4;
										     best_rook[best_rook_count].kill = piece_value(best_rook[best_rook_count].move3, best_rook[best_rook_count].move4);
										     best_rook_count++;
									     }
									     k++;						     
								     }



								     best_rook_structure temp;
								     for(s = 0; s < best_rook_count; s++)
									     for(t = s + 1; t < best_rook_count; t++)
										     if(best_rook[s].kill > best_rook[t].kill) {
											     temp = best_rook[s];
											     best_rook[s]= best_rook[t]; 
											     best_rook[t]= temp;
										     }



							     }

						case -bishop : {
								       kill_struct_count = 0;
								       normal_struct_count = 0;
								       //Checking all moves for bishop
								       for(k = 0; k < 8; k++) {
									       for(l = 0; l < 8; l++) {
										       //If a move is legal for bishop
										       if(move_b_bishop(j, i, l, k) == 1) {
											       //If the bishop kills a white piece, store in kill structure
											       if(board[k][l] > 0) {
												       kill_struct[kill_struct_count].move1 = i;
												       kill_struct[kill_struct_count].move2 = j;
												       kill_struct[kill_struct_count].move3 = k;
												       kill_struct[kill_struct_count].move4 = l;
												       kill_struct_count++;
											       }

											       //If the bishop does not kill anyone, store in normal
											       else{
												       normal_struct[normal_struct_count].move1 = i;
												       normal_struct[normal_struct_count].move2 = j;
												       normal_struct[normal_struct_count].move3 = k;
												       normal_struct[normal_struct_count].move4 = l;
												       normal_struct_count++;
											       }
										       }
										       else
											       continue;
									       }
								       }


								       //For the moves where bishop kills no one, store the kill value as 0 					 
								       k = 0;
								       while(k != normal_struct_count) { 
									       loop_count = 0;
									       if_count = 0;
									       simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
									       for(s = 0; s < 8; s++) {
										       for(t = 0; t < 8; t++) {
											       //Now generating all white moves with the destination as the moved bishop and ensuring that the moved bishop will not be killed
											       if((move_w_pawn(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													       (move_w_bishop(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													       (move_w_knight(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) && 
													       (move_w_rook(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													       (move_w_queen(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0)) {
												       if_count++;
												       loop_count++;
											       }
											       else 
												       loop_count++;

										       }
									       }
									       rev_simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
									       if(loop_count == if_count) {
										       best_bishop[best_bishop_count].move1 = normal_struct[k].move1;
										       best_bishop[best_bishop_count].move2 = normal_struct[k].move2;
										       best_bishop[best_bishop_count].move3 = normal_struct[k].move3;
										       best_bishop[best_bishop_count].move4 = normal_struct[k].move4;
										       best_bishop[best_bishop_count].kill = 0;
										       best_bishop_count++;
									       }
									       k++;
								       }


								       //Now, when the bishop does kill some pieces, store the kill value as the piece killed
								       k = 0;
								       while(k != kill_struct_count) { 
									       loop_count = 0;
									       if_count = 0;
									       simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									       for(s = 0; s < 8; s++) {
										       for(t = 0; t < 8; t++) {
											       if((move_w_pawn(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													       (move_w_bishop(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													       (move_w_knight(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) && 
													       (move_w_rook(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													       (move_w_queen(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0)) {
												       if_count++;
												       loop_count++;
											       }
											       else 
												       loop_count++;
											       //Now generating all white moves with destinaltion as the moved kinght and ensuring that the moved bishop will not be killed

										       }
									       }
									       rev_simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									       if(loop_count == if_count) {
										       best_bishop[best_bishop_count].move1 = kill_struct[k].move1;
										       best_bishop[best_bishop_count].move2 = kill_struct[k].move2;
										       best_bishop[best_bishop_count].move3 = kill_struct[k].move3;
										       best_bishop[best_bishop_count].move4 = kill_struct[k].move4;
										       best_bishop[best_bishop_count].kill = piece_value(best_bishop[best_bishop_count].move3, best_bishop[best_bishop_count].move4);
										       best_bishop_count++;
									       }

									       k++;
								       }



								       best_bishop_structure temp;
								       for(s = 0; s < best_bishop_count; s++)
									       for(t = s + 1; t < best_bishop_count; t++)
										       if(best_bishop[s].kill > best_bishop[t].kill) {
											       temp = best_bishop[s];
											       best_bishop[s]= best_bishop[t]; 
											       best_bishop[t]= temp;
										       }



							       }

						case -queen : {
								      kill_struct_count = 0;
								      normal_struct_count = 0;
								      //Checking all moves for queen
								      for(k = 0; k < 8; k++) {
									      for(l = 0; l < 8; l++) {
										      //If a move is legal for queen
										      if(move_b_queen(j, i, l, k) == 1) {
											      //If the queen kills a white piece, store in kill structure
											      if(board[k][l] > 0) {
												      kill_struct[kill_struct_count].move1 = i;
												      kill_struct[kill_struct_count].move2 = j;
												      kill_struct[kill_struct_count].move3 = k;
												      kill_struct[kill_struct_count].move4 = l;
												      kill_struct_count++;
											      }

											      //If the queen does not kill anyone, store in normal
											      else{
												      normal_struct[normal_struct_count].move1 = i;
												      normal_struct[normal_struct_count].move2 = j;
												      normal_struct[normal_struct_count].move3 = k;
												      normal_struct[normal_struct_count].move4 = l;
												      normal_struct_count++;
											      }
										      }
										      else
											      continue;
									      }
								      }


								      //For the moves where queen kills no one, store the kill value as 0 					 
								      k = 0;
								      while(k != normal_struct_count) { 
									      loop_count = 0;
									      if_count = 0;
									      simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
									      for(s = 0; s < 8; s++) {
										      for(t = 0; t < 8; t++) {
											      if((move_w_pawn(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													      (move_w_bishop(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													      (move_w_knight(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) && 
													      (move_w_rook(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0) &&
													      (move_w_queen(t, s, normal_struct[k].move3, normal_struct[k].move4) == 0)) {
												      if_count++;
												      loop_count++;
											      }
											      else 
												      loop_count++;
										      }
									      }
									      rev_simulate_board(normal_struct[k].move2, normal_struct[k].move1, normal_struct[k].move4, normal_struct[k].move3);
									      if(loop_count == if_count) {
										      best_queen[best_queen_count].move1 = normal_struct[k].move1;
										      best_queen[best_queen_count].move2 = normal_struct[k].move2;
										      best_queen[best_queen_count].move3 = normal_struct[k].move3; 
										      best_queen[best_queen_count].move4 = normal_struct[k].move4;
										      best_queen[best_queen_count].kill = 0;
										      best_queen_count++;
									      }
									      k++;
								      }


								      //Now, when the queen does kill some pieces, store the kill value as the piece killed
								      k = 0;
								      while(k != kill_struct_count) { 
									      loop_count = 0;
									      if_count = 0;
									      simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									      //Now generating all white moves with destinaltion as the moved kinght and ensuring that the moved queen will not be killed
									      for(s = 0; s < 8; s++) {
										      for(t = 0; t < 8; t++) {
											      if((move_w_pawn(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													      (move_w_bishop(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													      (move_w_knight(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) && 
													      (move_w_rook(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0) &&
													      (move_w_queen(t, s, kill_struct[k].move3, kill_struct[k].move4) == 0)) {
												      if_count++;
												      loop_count++;
											      }
											      else 
												      loop_count++;

										      }
									      }
									      rev_simulate_board(kill_struct[k].move2, kill_struct[k].move1, kill_struct[k].move4, kill_struct[k].move3);
									      if(loop_count == if_count) {
										      best_queen[best_queen_count].move1 = kill_struct[k].move1;
										      best_queen[best_queen_count].move2 = kill_struct[k].move2;
										      best_queen[best_queen_count].move3 = kill_struct[k].move3;
										      best_queen[best_queen_count].move4 = kill_struct[k].move4;
										      best_queen[best_queen_count].kill = piece_value(best_queen[best_queen_count].move3, best_queen[best_queen_count].move4);
										      best_queen_count++;
									      }
									      k++;
								      }



								      best_queen_structure temp;
								      for(s = 0; s < best_queen_count; s++)
									      for(t = s + 1; t < best_queen_count; t++)
										      if(best_queen[s].kill > best_queen[t].kill) {
											      temp = best_queen[s];
											      best_queen[s]= best_queen[t]; 
											      best_queen[t]= temp;
										      }



							      }


					}



				}


			}
			//The best move of pawn is stored in best move
			if(best_pawn_count != 0) {
				if(pawn_kill_no == 1)
					move = random_number(0, best_pawn_count - 1);
				else
					move = best_pawn_count - 1;

				best_move[best_count].move1 = best_pawn[move].move1;
				best_move[best_count].move2 = best_pawn[move].move2;
				best_move[best_count].move3 = best_pawn[move].move3;
				best_move[best_count].move4 = best_pawn[move].move4;
				best_move[best_count].kill = best_pawn[move].kill;
				//If all kills are zero, then we choose randomly	
				if(best_move[best_count].kill != 0)
					kill_count++;
				best_count++;
			}
			//The best move of knight is stored in best move
			if(best_knight_count != 0) {
				best_move[best_count].move1 = best_knight[best_knight_count - 1].move1;
				best_move[best_count].move2 = best_knight[best_knight_count - 1].move2;
				best_move[best_count].move3 = best_knight[best_knight_count - 1].move3;
				best_move[best_count].move4 = best_knight[best_knight_count - 1].move4;
				best_move[best_count].kill = best_knight[best_knight_count - 1].kill;
				//If all kills are zero, then we choose ramdomly	
				if(best_move[best_count].kill != 0)
					kill_count++;
				best_count++;
			}
			//The best move of rook is stored in best move
			if(best_rook_count != 0) {
				best_move[best_count].move1 = best_rook[best_rook_count - 1].move1;
				best_move[best_count].move2 = best_rook[best_rook_count - 1].move2;
				best_move[best_count].move3 = best_rook[best_rook_count - 1].move3;
				best_move[best_count].move4 = best_rook[best_rook_count - 1].move4;
				best_move[best_count].kill = best_rook[best_rook_count - 1].kill;
				//If all kills are zero, then we choose ramdomly	
				if(best_move[best_count].kill != 0)
					kill_count++;
				best_count++;
			}
			//The best move of bishop is stored in best move
			if(best_bishop_count != 0) {
				best_move[best_count].move1 = best_bishop[best_bishop_count - 1].move1;
				best_move[best_count].move2 = best_bishop[best_bishop_count - 1].move2;
				best_move[best_count].move3 = best_bishop[best_bishop_count - 1].move3;
				best_move[best_count].move4 = best_bishop[best_bishop_count - 1].move4;
				best_move[best_count].kill = best_bishop[best_bishop_count - 1].kill;
				//If all kills are zero, then we choose ramdomly	
				if(best_move[best_count].kill != 0)
					kill_count++;
				best_count++;
			}
			//The best move of queen is stored in best move
			if(best_queen_count != 0) {
				best_move[best_count].move1 = best_queen[best_queen_count - 1].move1;
				best_move[best_count].move2 = best_queen[best_queen_count - 1].move2;
				best_move[best_count].move3 = best_queen[best_queen_count - 1].move3;
				best_move[best_count].move4 = best_queen[best_queen_count - 1].move4;
				best_move[best_count].kill = best_queen[best_queen_count - 1].kill;
				//If all kills are zero, then we choose ramdomly	
				if(best_move[k].kill != 0)
					kill_count++;
				best_count++;
			}
			if(kill_count == 0) { 
				move = random_number(0, best_count - 1); 
				change_board(best_move[move].move2, best_move[move].move1, best_move[move].move4, best_move[move].move3);
				turn = WHITE; 
				continue;
			}

			else {
				best_move_structure tmp;
				for(s = 0; s < best_count; s++)
					for(t = s + 1; t < best_count; t++)
						if(best_move[s].kill > best_move[t].kill) {
							tmp = best_move[s];
							best_move[s]= best_move[t]; 
							best_move[t]= tmp;
						}
				move = best_count - 1;
				change_board(best_move[move].move2, best_move[move].move1, best_move[move].move4, best_move[move].move3);
				turn = WHITE;
				continue;
			}


		}

		else {
			print_board();
			printf("Invalid move!!\n");
		}
	}
	return 0;
}


