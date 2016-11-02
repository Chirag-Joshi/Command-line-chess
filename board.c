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
#include <stdlib.h>
#include <time.h>
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

void change_board(int move1, int move2, int move3, int move4) {
	board[move4][move3] = board[move2][move1];
	board[move2][move1] = x;
	print_board();
	//display();
}

int random_number(int min_num, int max_num) {
	if(min_num == 0 && max_num == 0) 
		return 0;
	int result = 0, low_num = 0, hi_num = 0;
	if(min_num < max_num) {
		low_num = min_num;
		hi_num = max_num + 1; // this is done to include max_num in output.
	}
	else {
		low_num=max_num + 1;// this is done to include max_num in output.
		hi_num = min_num;
	}
	srand(time(NULL));
	result = (rand() % (hi_num - low_num)) + low_num;
	return result;
}


int piece_value(int pos1, int pos2) {
	switch(board[pos1][pos2]) {
		case pawn :
			return 1;
		case bishop :
			return 3;
		case knight :
			return 3;
		case rook :
			return 5;
		case queen :
			return 9;
		}
}

//Simulate has to be called in pair with reverse simulation!!
void simulate_board(int move1, int move2, int move3, int move4) {
	board[move4][move3] = board[move2][move1];
	board[move2][move1] = x;
}

//Reverse simulation has to be called after simulate_board
void rev_simulate_board(int move1, int move2, int move3, int move4) {
	board[move2][move1] = board[move4][move3];
	board[move4][move3] = x;
}

int white_check() {
	int i, j, pos1, pos2;
	for(i = 0; i  < 8; i++) {
		for(j = 0; j < 8; j++) 
			if(board[i][j] == king) 
				break;
		if(board[i][j] == king)
			break;
	}
	pos1 = i;
	pos2 = j;

	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			switch(board[i][j]) {
				case -pawn : {
						     if(move_b_pawn(j, i, pos2, pos1) == 1)
							     return 1;
						     else 
							     continue;
					     }
				case -bishop : {
						       if(move_b_bishop(j, i, pos2, pos1) == 1)
							       return 1;
						       else 
							       continue;
					       }
				case -knight : {
						       if(move_b_knight(j, i, pos2, pos1) == 1)
							       return 1;
						       else 
							       continue;
					       }
				case -rook : {
						     if(move_b_rook(j, i, pos2, pos1) == 1)
							     return 1;
						     else 
							     continue;
					     }
				case -queen : {
						      if(move_b_queen(j, i, pos2, pos1) == 1)
							      return 1;
						      else 
							      continue;
					      }
				default : 
					      continue;
			}
		}
	}
	return 0;
}


int black_check() {
	int i, j, pos1, pos2;
	for(i = 0; i  < 8; i++) {
		for(j = 0; j < 8; j++) 
			if(board[i][j] == -king) 
				break;
		if(board[i][j] == -king)
			break;
	}
	pos1 = i;
	pos2 = j;

	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			switch(board[i][j]) {
				case pawn : {
						    if(move_w_pawn(j, i, pos2, pos1) == 1)
							    return 1;
						    else 
							    continue;
					    }
				case bishop : {
						      if(move_w_bishop(j, i, pos2, pos1) == 1)
							      return 1;
						      else 
							      continue;
					      }
				case knight : {
						      if(move_w_knight(j, i, pos2, pos1) == 1)
							      return 1;
						      else 
							      continue;
					      }
				case rook : {
						    if(move_w_rook(j, i, pos2, pos1) == 1)
							    return 1;
						    else 
							    continue;
					    }
				case queen : {
						     if(move_w_queen(j, i, pos2, pos1) == 1)
							     return 1;
						     else 
							     continue;
					     }
				default : 
					     continue;
			}
		}
	}
	return 0;
}


void print_board(){
	system("clear");
	printf("\n");
	char displayBoard[39][55] = {

		{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'd', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', 'f', ' ', ' ', ' ', ' ', ' ', 'g', ' ', ' ', ' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '8', ' ', '#', ' ', ' ', 'R', ' ', ' ', '#', ' ', ' ', 'N', ' ', ' ', '#', ' ', ' ', 'B', ' ', ' ', '#', ' ', ' ', 'Q', ' ', ' ', '#', ' ', ' ', 'K', ' ', ' ', '#', ' ', ' ', 'B', ' ', ' ', '#', ' ', ' ', 'N', ' ', ' ', '#', ' ', ' ', 'R', ' ', ' ', '#', ' ', '8'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '7', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', '7'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '6', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '6'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '5', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '5'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '4', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '4'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '3', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '3'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '2', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', '2'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', '1', ' ', '#', ' ', ' ', 'R', ' ', ' ', '#', ' ', ' ', 'N', ' ', ' ', '#', ' ', ' ', 'B', ' ', ' ', '#', ' ', ' ', 'Q', ' ', ' ', '#', ' ', ' ', 'K', ' ', ' ', '#', ' ', ' ', 'B', ' ', ' ', '#', ' ', ' ', 'N', ' ', ' ', '#', ' ', ' ', 'R', ' ', ' ', '#', ' ', '1'},
		{' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
		{' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}, 
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'd', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', 'f', ' ', ' ', ' ', ' ', ' ', 'g', ' ', ' ', ' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ', ' '},

	};



	//DisplayRow -> it converts the standard board coordinates to display coordinates
	//i.e. the 0th row of the real board is equivalent to the 31st row of the display board just by how I've set it up
	int dR0 = 31;
	int dR1 = 27;
	int dR2 = 23;
	int dR3 = 19;
	int dR4 = 15;
	int dR5 = 11;
	int dR6 = 7;
	int dR7 = 3;

	//"displayColumn"
	int dC0 = 7;
	int dC1 = 13;
	int dC2 = 19;
	int dC3 = 25;
	int dC4 = 31;
	int dC5 = 37;
	int dC6 = 43;
	int dC7 = 49;

	int tempRow = 0;
	int tempColumn = 0;

	//updates real piece locations on the "display board"
	for(int i = 0; i < 8; i++){

		if(i == 0)
			tempRow = dR0;
		else if(i == 1)
			tempRow = dR1;
		else if(i == 2)
			tempRow = dR2;
		else if(i == 3)
			tempRow = dR3;
		else if(i == 4)
			tempRow = dR4;
		else if(i == 5)
			tempRow = dR5;
		else if(i == 6)
			tempRow = dR6;
		else
			tempRow = dR7;



		for(int j = 0; j < 8; j++){

			if(j == 0)
				tempColumn = dC0;
			else if(j == 1)
				tempColumn = dC1;
			else if(j == 2)	
				tempColumn = dC2;
			else if(j == 3)
				tempColumn = dC3;
			else if(j == 4)
				tempColumn = dC4;
			else if(j == 5)
				tempColumn = dC5;
			else if(j == 6)
				tempColumn = dC6;
			else
				tempColumn = dC7;

			//update display board pieces to match the real board
			if(board[i][j] == 0)
				displayBoard[tempRow][tempColumn] = ' ';

			else if(board[i][j] == pawn)
				displayBoard[tempRow][tempColumn] = 'P';

			else if(board[i][j] == king)
				displayBoard[tempRow][tempColumn] = 'K';

			else if(board[i][j] == queen)
				displayBoard[tempRow][tempColumn] = 'Q';

			else if(board[i][j] == bishop)
				displayBoard[tempRow][tempColumn] = 'B';

			else if(board[i][j] == knight)
				displayBoard[tempRow][tempColumn] = 'N';

			else if(board[i][j] == rook)
				displayBoard[tempRow][tempColumn] = 'R';

			else if(board[i][j] == -pawn)
				displayBoard[tempRow][tempColumn] = 'p';

			else if(board[i][j] == -king)
				displayBoard[tempRow][tempColumn] = 'k';

			else if(board[i][j] == -queen)
				displayBoard[tempRow][tempColumn] = 'q';

			else if(board[i][j] == -bishop)
				displayBoard[tempRow][tempColumn] = 'b';

			else if(board[i][j] == -knight)
				displayBoard[tempRow][tempColumn] = 'n';

			else 
				displayBoard[tempRow][tempColumn] = 'r';


		}
	}


	int i, j;
	for(i = 0; i < 39; i++){
		for(j = 0; j < 55; j++)
			printf("%c", displayBoard[i][j]);
		printf("\n");
	}

}
