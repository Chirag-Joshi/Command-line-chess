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
#include "headers.h"

/* This file contains the functions required for moving the
 * pieces. They are generic finctions for both, black and white 
 * pieces. For whtie, pass the input moves in the order 1, 2, 3,
 * 4. For black, we interchange them as 3, 4, 1, 2. There are 5 
 * functions for
 * bishop, knight, rook, queen and king.
 */



//For pawn

int move_w_pawn(int move1, int move2, int move3, int move4) {
	if(board[move4][move3] > 0 || (board[move2][move1] != pawn)) {
		//Move not possible!! end piece wrong for pawn
		return 0;
	} 
	else if((board[move4][move3] == 0) && (move4 == (move2 + 1)) && (move1 == move3)) {
		return 1;
	}	
	else if((board[move4][move3] < 0) && (move3 == (move1 + 1)) && (move4 == (move2 + 1))) {
		return 1;
	}
	else if((board[move4][move3] < 0) && (move3 == (move1 - 1)) && (move4 == (move2 + 1))) {
		return 1;
	}
	else if((move1 == move3) && (move2 == 1) && (move4 == (move2 + 2)) && (board[move4][move3] == 0) && (board[move4 - 1][move3] == 0)) {
		return 1;
	}
	else { 
		//Move not possible!! pawn illegal
		return 0;
	}
}

int move_b_pawn(int move1, int move2, int move3, int move4) {
	if(board[move4][move3] < 0 || (board[move2][move1] != -pawn)) {
		//Move not possible!! pawn - destination has wrong piece
		return 0;
	} 
	else if((board[move4][move3] == 0) && (move4 == (move2 - 1)) && (move1 == move3)) {
		return 1;
	}	
	else if((board[move4][move3] > 0) && (move3 == (move1 - 1)) && (move4 == (move2 - 1))) {
		return 1;
	}
	else if((board[move4][move3] > 0) && (move3 == (move1 + 1)) && (move4 == (move2 - 1))) {
		return 1;
	}
	else if((move1 == move3) && (move2 == 6) && (move4 == (move2 - 2)) && (board[move4][move3] == 0) && (board[move4 + 1][move3] == 0)) {
		return 1;
	}
	else { 
		//Move not possible!! pawn illegal move
		return 0;
	}
}

//For bishop

int move_w_bishop(int move1, int move2, int move3, int move4) {
	int i, j, k = 0, count = 0;
	//Checking if valid move for bishop and last piece is not positive
	if((move3 == move1) || (move2 == move4) || (board[move4][move3] > 0) || (board[move2][move1] != bishop)) {
		//Move not possible!! bishop - last piece is wrong or invalid move for bishop
		return 0;
	}

	//Moving bishop diagonally up to right side
	else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 + 1; 
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x) 
				count++;
			k++; 
			i++; 
			j++;
		}

		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - middle places not empty
			return 0;
		}
	}

	//Moving bishop diagonally up to left side
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 - 1;
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j++;
			k++;
		}

			
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - moddle places not empty diag up left
			return 0;
		}
	}

	//Moving bishop diagonally down to right side
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 + 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i++;
			j--;
			k++;
		}

		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - middle places not empty diag down right
			return 0;
		}
	}					

	//Moving bishop diagonally down to left side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 - 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j--;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - middle places not empty diag down left
			return 0;
		}
	}

	//For any other problem
	else {
		//Move not possible - bishop shitload went wrong
		return 0;
	}
}

int move_b_bishop(int move1, int move2, int move3, int move4) {
	int i, j, k = 0, count = 0;
	//Checking if valid move for bishop and last piece is not positive
	if((move3 == move1) || (move2 == move4) || (board[move4][move3] < 0) || (board[move2][move1] != -bishop)) {
		//Move not possible!! bishop - last piece is wrong or invalid move for bishop
		return 0;
	}

	//Moving bishop diagonally up to right side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 - 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j--;
			k++;
		}

		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - middle places not empty
			return 0;
		}
	}

	//Moving bishop diagonally up to left side
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 + 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i++;
			j--;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - moddle places not empty diag up left
			return 0;
		}
	}

	//Moving bishop diagonally down to right side
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 - 1;
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j++;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - middle places not empty diag down right
			return 0;
		}
	}					

	//Moving bishop diagonally down to left side
	else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 + 1;
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i++;
			j++;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! bishop - middle places not empty diag down left
			return 0;
		}
	}

	//For any other problem
	else {
		//Move not possible - bishop shitload went wrong
		return 0;
	}
}

//For knight

int move_w_knight(int move1, int move2, int move3, int move4) {
	//Checking if destination does not have a white piece
	if((board[move4][move3] > 0) || (board[move2][move1] != knight)) {
		//Move not possible!! knight - end point has wrong piece
		return 0;
	}
	
	//Checking if legal move for knight
	else if((move1 == move3) || (move2 == move4) || (abs(move2 - move4) == abs(move1 - move3))) {
		//Move not possible!! knight - illegal move for knight
		return 0;
	}

	//Moving knight up right 2 conditions
	else if((move1 < move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - upper right
			return 0;
		}
	}

	//Moving knight up left 2 conditions
	else if((move1 > move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - upper left
			return 0;
		}
	}

	//Moving knight down right		
	else if((move1 < move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - down right
			return 0;
		}
	}

	//Moving knight down left
	else if((move1 > move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - down left
			return 0;
		}
	}

	//All fails
	else {
		//Move not possible!! knight - impossible
		return 0;
	}
}

int move_b_knight(int move1, int move2, int move3, int move4) {
	//Checking if destination does not have a white piece
	if((board[move4][move3] < 0) || (board[move2][move1] != -knight)) {
		//Move not possible!! knight - end point has wrong piece
		return 0;
	}
	
	//Checking if legal move for knight
	else if((move1 == move3) || (move2 == move4) || (abs(move2 - move4) == abs(move1 - move3))) {
		//Move not possible!! knight - illegal move for knight
		return 0;
	}

	//Moving knight up right 2 conditions
	else if((move1 < move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - upper right
			return 0;
		}
	}

	//Moving knight up left 2 conditions
	else if((move1 > move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - upper left
			return 0;
		}
	}

	//Moving knight down right		
	else if((move1 < move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - down right
			return 0;
		}
	}

	//Moving knight down left
	else if((move1 > move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			return 1;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			return 1;
		}
		//If both condition fail
		else {
			//Move not possible!! Knight - down left
			return 0;
		}
	}

	//All fails
	else {
		//Move not possible!! knight - impossible
		return 0;
	}
}


//For rook


int move_w_rook(int move1, int move2, int move3, int move4) {
	int i, count = 0, k = 0;
	//Checking if legal move for rook
	if((board[move4][move3] > 0) || (board[move2][move1] != rook)) {
		//Move not possible!! rook - end point has wrong piece
		return 0;
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
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
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
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
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
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
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
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}
	//For any other problem
	else {
		//Move not possible!! rook - some shitload went wrong
		return 0;
	}
}

int move_b_rook(int move1, int move2, int move3, int move4) {
	int i, count = 0, k = 0;
	//Checking if legal move for rook
	if((board[move4][move3] < 0) || (board[move2][move1] != -rook)) {
		//Move not possible!! rook - end point has wrong piece
		return 0;
	}
	//Moving rook vertically upwards
	else if((move1 == move3) && (move2 > move4)) {
		//Checking if all places from src to dest. are empty
		for(i = move2 - 1; i > move4; i--, k++) {
			if(board[i][move3] == x)
				count++;
			else 
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}		
	//Moving rook vertically downward
	else if((move1 == move3) && (move2 < move4)) {
		//Checking if all places from src to dest are empty
		for(i = move4; i > move2; i--, k++) {
			if(board[i][move3] == x) 
				count++;
			else
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}
	//Moving rook horizontally to right
	else if((move2 == move4) && (move3 < move1)) {
		//Checking if all places from src to dest are empty
		for(i = move1 - 1; i > move3; i--, k++) {
			if(board[move4][i] == x)
				count++;
			else 
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}
	//Moving rook horizontally left
	else if((move2 == move4) && (move3 > move1)) {
		//Checking if all places from src to dest are empty
		for(i = move3; i > move1; i--, k++) {
			if(board[move4][i] == x)
				count++;
			else
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}
	//For any other problem
	else {
		//Move not possible!! rook - some shitload went wrong
		return 0;
	}
}

//For queen

int move_w_queen(int move1, int move2, int move3, int move4) {
	int i, j, k = 0, count = 0;
	//Checking if endpoint has correct piece
	if((board[move4][move3] > 0) || (board[move2][move1] != queen)) {
		//Move not possible queen end point has wrong piece
		return 0;
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
			return 1;
		} 
		else {
			//Move not possible queen vertically up - middle places not empty
			return 0;
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
			return 1;
		} 
		else {
			//Move not possible queen vertically down - middle places not empty
			return 0;
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
			return 1;
		} 
		else {
			//Move not possible queen horizontally right - middle places not empty;
			return 0;
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
			return 1;
		} 
		else {
			//Move not possible queen horizontally left - middle places not empty
			return 0;
		}
	}
	//Moving queen diagonally up to right side
	else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 + 1; 
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x) 
				count++;
			k++; 
			i++; 
			j++;
		}

		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - middle places not empty
			return 0;
		}
	}

	//Moving queen diagonally up to left side
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 - 1;
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j++;
			k++;
		}

			
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - moddle places not empty diag up left
			return 0;
		}
	}

	//Moving queen diagonally down to right side
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 + 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i++;
			j--;
			k++;
		}

		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - middle places not empty diag down right
			return 0;
		}
	}					

	//Moving queen diagonally down to left side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 - 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j--;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - middle places not empty diag down left
			return 0;
		}
	}

	//For any other problem
	else {
		//Move not possible - queen shitload went wrong
		return 0;
	}

}


int move_b_queen(int move1, int move2, int move3, int move4) {
	int i, count = 0, j, k = 0;
	//Checking if legal move for rook
	if((board[move4][move3] < 0) || (board[move2][move1] != -queen)) {
		//Move not possible!! rook - end point has wrong piece
		return 0;
	}
	//Moving rook vertically upwards
	else if((move1 == move3) && (move2 > move4)) {
		//Checking if all places from src to dest. are empty
		for(i = move2 - 1; i > move4; i--, k++) {
			if(board[i][move3] == x)
				count++;
			else 
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}		
	//Moving rook vertically downward
	else if((move1 == move3) && (move2 < move4)) {
		//Checking if all places from src to dest are empty
		for(i = move4; i > move2; i--, k++) {
			if(board[i][move3] == x) 
				count++;
			else
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}
	//Moving rook horizontally to right
	else if((move2 == move4) && (move3 < move1)) {
		//Checking if all places from src to dest are empty
		for(i = move1 - 1; i > move3; i--, k++) {
			if(board[move4][i] == x)
				count++;
			else 
				continue;
		}
		if(count == k) {
			return 1;
		} 
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}
	//Moving rook horizontally left
	else if((move2 == move4) && (move3 > move1)) {
		//Checking if all places from src to dest are empty
		for(i = move3; i > move1; i--, k++) {
			if(board[move4][i] == x)
				count++;
			else
				continue;
		}
		if(count == k) {
			return 1;
		}  
		else {
			//Move not possible rook - middle places not empty
			return 0;
		}
	}

	//Moving queen diagonally up to right side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 - 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j--;
			k++;
		}

		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - middle places not empty
			return 0;
		}
	}

	//Moving queen diagonally up to left side
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		i = move1 + 1;
		j = move2 - 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i++;
			j--;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - moddle places not empty diag up left
			return 0;
		}
	}

	//Moving queen diagonally down to right side
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 - 1;
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i--;
			j++;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - middle places not empty diag down right
			return 0;
		}
	}					

	//Moving queen diagonally down to left side
	else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		i = move1 + 1;
		j = move2 + 1;
		while(i != move3) {
			if(board[j][i] == x)
				count++;
			i++;
			j++;
			k++;
		}
		if(count == k) {
			return 1;
		}
		else {
			//Move not possible!! queen - middle places not empty diag down left
			return 0;
		}
	}
	
	//For any other problem
	else {
		//Move not possible!! queen - some shitload went wrong;
		return 0;
	}
}


//For king

int move_w_king(int move1, int move2, int move3, int move4) {
	//Checking if end point has opposite side piece
	if(board[move4][move3] > 0) {
		//Move not possible! king - endpoint has wrong piece
		return 0;
	}

	//Moving king vertilcally upwards
	else if((move1 == move3) && (move2 < move4) && (abs(move2 - move4) == 1)) {
		return 1; 
	}

	//Moveing king vertically downwards
	else if((move1 == move3) && (move2 > move4) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moving king horizantally right
	else if((move2 == move4) && (move1 < move3) && (abs(move1 - move3) == 1)) {
		return 1;
	}

	//Moving king horizontally to left
	else if((move2 == move4) && (move1 > move3) && (abs(move1 - move3) == 1)) {
		return 1;
	}

	//Moving king diagonally up right
	else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moving king diagonally up left
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;	
	}

	//Moving king diagonally down right
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moving king diagonally down left
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Checking for problems
	else {
		//Move not possible king
		return 0;
	}
}


int move_b_king(int move1, int move2, int move3, int move4) {
	//Checking if end point has opposite side piece
	if(board[move4][move3] < 0) {
		//Move not possible! king - endpoint has wrong piece
		return 0;
	}

	//Moving king vertilcally upwards
	else if((move1 == move3) && (move2 > move4) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moveing king vertically downwards
	else if((move1 == move3) && (move2 < move4) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moving king horizantally right
	else if((move2 == move4) && (move1 < move3) && (abs(move1 - move3) == 1)) {
		return 1;
	}

	//Moving king horizontally to left
	else if((move2 == move4) && (move1 < move3) && (abs(move1 - move3) == 1)) {
		return 1;
	}

	//Moving king diagonally up right
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moving king diagonally up left
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1; 	
	}

	//Moving king diagonally down right
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Moving king diagonally down left
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		return 1;
	}

	//Checking for problems
	else {
		//Move not possible king
		return 0;
	}
}


//Castleing
//White king side

int white_castle_kingside() {
	if(w_rook_flag == 1 || w_king_flag == 1 || white_check() == 1) 
		return 0;
	else if(board[0][5] != 0 && board[0][6] != 0)
		return 0;
	else {
		board[0][5] = rook;
		board[0][7] = x;
		board[0][6] = king;
		board[0][4] = x;
		w_king_flag = 1;
		w_rook_flag = 1;
		return 1;
	}
}

//White queen side
int white_castle_queenside() {
	if(w_rook_flag == 1 || w_king_flag == 1 || white_check() == 1) 
		return 0;
	else if(board[0][1] != 0 && board[0][2] != 0 && board[0][3] != 0)
		return 0;
	else {
		board[0][3] = rook;
		board[0][0] = x;
		board[0][2] = king;
		board[0][4] = x;
		w_king_flag = 1;
		w_rook_flag = 1;
		return 1;
	}
}

//Black king side
int black_castle_kingside() {
	if(b_rook_flag == 1 || b_king_flag == 1 || black_check() == 1) 
		return 0;
	else if(board[7][5] != 0 && board[7][6] != 0)
		return 0;
	else {
		board[7][5] = -rook;
		board[7][7] = x;
		board[7][6] = -king;
		board[7][4] = x;
		b_king_flag = 1;
		b_rook_flag = 1;
		return 1;
	}
}

//White queen side
int black_castle_queenside() {
	if(b_rook_flag == 1 || b_king_flag == 1 || black_check() == 1) 
		return 0;
	else if(board[7][1] != 0 && board[7][2] != 0 && board[7][3] != 0)
		return 0;
	else {
		board[7][3] = -rook;
		board[7][0] = x;
		board[7][2] = -king;
		board[7][4] = x;
		b_king_flag = 1;
		b_rook_flag = 1;
		return 1;
	}
}
