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

void move_w_pawn(int move1, int move2, int move3, int move4) {
	if(board[move4][move3] > 0) {
		printf("Move not possible!! end piece wrong for pawn\n");
		return;
	} 
	else if((board[move4][move3] == 0) && (move4 == (move2 + 1)) && (move1 == move3)) {
		change_board(move1, move2, move3, move4);
		return;
	}	
	else if((board[move4][move3] < 0) && (move3 == (move1 + 1)) && (move4 == (move2 + 1))) {
		change_board(move1, move2, move3, move4);
		return;
	}
	else if((board[move4][move3] < 0) && (move3 == (move1 - 1)) && (move4 == (move2 + 1))) {
		change_board(move1, move2, move3, move4);
		return;
	}
	else { 
		printf("Move not possible!! pawn illegal\n");
		return;
	}
}

void move_b_pawn(int move1, int move2, int move3, int move4) {
	if(board[move4][move3] < 0) {
		printf("Move not possible!! pawn - destination has wrong piece\n");
		return;
	} 
	else if((board[move4][move3] == 0) && (move4 == (move2 - 1)) && (move1 == move3)) {
		change_board(move1, move2, move3, move4);
		return;
	}	
	else if((board[move4][move3] > 0) && (move3 == (move1 - 1)) && (move4 == (move2 - 1))) {
		change_board(move1, move2, move3, move4);
		return;
	}
	else if((board[move4][move3] > 0) && (move3 == (move1 + 1)) && (move4 == (move2 - 1))) {
		change_board(move1, move2, move3, move4);
		return;
	}
	else { 
		printf("Move not possible!! pawn illegal move\n");
		return;
	}
}

//For bishop

void move_w_bishop(int move1, int move2, int move3, int move4) {
	int i, j, k = 0, count = 0;
	//Checking if valid move for bishop and last piece is not positive
	if((move3 == move1) || (move2 == move4) || (board[move4][move3] > 0)) {
		printf("Move not possible!! bishop - last piece is wrong or invalid move for bishop\n");
		return;
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
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! bishop - moddle places not empty diag up left\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty diag down right\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty diag down left\n");
			return;
		}
	}

	//For any other problem
	else {
		printf("Move not possible - bishop shitload went wrong\n");
		return;
	}
}

void move_b_bishop(int move1, int move2, int move3, int move4) {
	int i, j, k = 0, count = 0;
	//Checking if valid move for bishop and last piece is not positive
	if((move3 == move1) || (move2 == move4) || (board[move4][move3] < 0)) {
		printf("Move not possible!! bishop - last piece is wrong or invalid move for bishop\n");
		return;
	}

	//Moving bishop diagonally up to right side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i--, j--, k++) {
			if(board[j][i] == x)
				count++;
			else 
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty\n");
			return;
		}
	}

	//Moving bishop diagonally up to left side
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i++, j--, k++) {
			if(board[j][i] == x) 
				count++;
			else
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - moddle places not empty diag up left\n");
			return;
		}
	}

	//Moving bishop diagonally down to right side
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i--, j++, k++) {
			if(board[j][i] == x)
				count++;
			else
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty diag down right\n");
			return;
		}
	}					

	//Moving bishop diagonally down to left side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i++, j++, k++) {
			if(board[j][i] == x)
				count++;
			else
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty diag down left\n");
			return;
		}
	}

	//For any other problem
	else {
		printf("Move not possible - bishop shitload went wrong\n");
		return;
	}
}

//For knight

void move_w_knight(int move1, int move2, int move3, int move4) {
	//Checking if destination does not have a white piece
	if((board[move4][move3] > 0)) {
		printf("Move not possible!! knight - end point has wrong piece\n");
		return;
	}
	
	//Checking if legal move for knight
	else if((move1 == move3) || (move2 == move4) || (abs(move2 - move4) == abs(move1 - move3))) {
		printf("Move not possible!! knight - illegal move for knight\n");
		return;
	}

	//Moving knight up right 2 conditions
	else if((move1 < move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - upper right\n");
			return;
		}
	}

	//Moving knight up left 2 conditions
	else if((move1 > move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - upper left\n");
			return;
		}
	}

	//Moving knight down right		
	else if((move1 < move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - down right\n");
			return;
		}
	}

	//Moving knight down left
	else if((move1 > move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - down left\n");
			return;
		}
	}

	//All fails
	else {
		printf("Move not possible!! knight - impossible\n");
		return;
	}
}

void move_b_knight(int move1, int move2, int move3, int move4) {
	//Checking if destination does not have a white piece
	if((board[move4][move3] < 0)) {
		printf("Move not possible!! knight - end point has wrong piece\n");
		return;
	}
	
	//Checking if legal move for knight
	else if((move1 == move3) || (move2 == move4) || (abs(move2 - move4) == abs(move1 - move3))) {
		printf("Move not possible!! knight - illegal move for knight\n");
		return;
	}

	//Moving knight up right 2 conditions
	else if((move1 < move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - upper right\n");
			return;
		}
	}

	//Moving knight up left 2 conditions
	else if((move1 > move3) && (move2 < move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - upper left\n");
			return;
		}
	}

	//Moving knight down right		
	else if((move1 < move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - down right\n");
			return;
		}
	}

	//Moving knight down left
	else if((move1 > move3) && (move2 > move4)) {
		//CASE 1
		if((abs(move1 - move3) == 1) && (abs(move2 - move4) == 2)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//CASE 2
		else if((abs(move1 - move3) == 2) && (abs(move2 - move4) == 1)) {
			change_board(move1, move2, move3, move4);
			return;
		}
		//If both condition fail
		else {
			printf("Move not possible!! Knight - down left\n");
			return;
		}
	}

	//All fails
	else {
		printf("Move not possible!! knight - impossible\n");
		return;
	}
}





//For rook


void move_w_rook(int move1, int move2, int move3, int move4) {
	int i, count = 0, k = 0;
	//Checking if legal move for rook
	if((board[move4][move3] > 0)) {
		printf("Move not possible!! rook - end point has wrong piece\n");
		return;
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
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
		}
	}
	//For any other problem
	else {
		printf("Move not possible!! rook - some shitload went wrong\n");
		return;
	}
}

void move_b_rook(int move1, int move2, int move3, int move4) {
	int i, count = 0, k = 0;
	//Checking if legal move for rook
	if((board[move4][move3] < 0)) {
		printf("Move not possible!! rook - end point has wrong piece\n");
		return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
		}
	}
	//For any other problem
	else {
		printf("Move not possible!! rook - some shitload went wrong\n");
		return;
	}
}

//For queen

void move_w_queen(int move1, int move2, int move3, int move4) {
	int i, j, k = 0, count = 0;
	//Checking if endpoint has correct piece
	if(board[move4][move3] > 0) {
		printf("Move not possible queen end point has wrong piece\n");
		return;
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
			return;
		} 
		else {
			printf("Move not possible queen vertically up - middle places not empty\n");
			return;
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
			return;
		} 
		else {
			printf("Move not possible queen vertically down - middle places not empty\n");
			return;
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
			return;
		} 
		else {
			printf("Move not possible queen horizontally right - middle places not empty\n");
			return;
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
			return;
		} 
		else {
			printf("Move not possible queen horizontally left - middle places not empty\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! queen - middle places not empty diag up right\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! queen - moddle places not empty diag up left\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! queen - middle places not empty diag down right\n");
			return;
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
			return;
		}
		else {
			printf("Move not possible!! queen - middle places not empty diag down left\n");
			return;
		}
	}

	//For any other problem
	else {
		printf("Move not possible - queen shitload went wrong\n");
		return;
	}

}


void move_b_queen(int move1, int move2, int move3, int move4) {
	int i, count = 0, j, k = 0;
	//Checking if legal move for rook
	if((board[move4][move3] < 0)) {
		printf("Move not possible!! rook - end point has wrong piece\n");
		return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
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
			change_board(move1, move2, move3, move4);
			return;
		} 
		else {
			printf("Move not possible rook - middle places not empty\n");
			return;
		}
	}

	//Moving bishop diagonally up to right side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i--, j--, k++) {
			if(board[j][i] == x)
				count++;
			else 
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty\n");
			return;
		}
	}

	//Moving bishop diagonally up to left side
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and dest are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i++, j--, k++) {
			if(board[j][i] == x) 
				count++;
			else
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - moddle places not empty diag up left\n");
			return;
		}
	}

	//Moving bishop diagonally down to right side
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i--, j++, k++) {
			if(board[j][i] == x)
				count++;
			else
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty diag down right\n");
			return;
		}
	}					

	//Moving bishop diagonally down to left side
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == abs(move2 - move4))) {
		//Checking if middle places between src and destination are empty
		for(i = (move1 - 1), j = (move2 - 1); i > move3 && j > move4; i++, j++, k++) {
			if(board[j][i] == x)
				count++;
			else
				continue;
		}
		if(count == k) {
			change_board(move1, move2, move3, move4);
			return;
		}
		else {
			printf("Move not possible!! bishop - middle places not empty diag down left\n");
			return;
		}
	}//For any other problem
	else {
		printf("Move not possible!! queen - some shitload went wrong\n");
		return;
	}
}


//For king

void move_w_king(int move1, int move2, int move3, int move4) {
	//Checking if end point has opposite side piece
	if(board[move4][move3] > 0) {
		printf("Move not possible! king - endpoint has wrong piece\n");
		return;
	}

	//Moving king vertilcally upwards
	else if((move1 == move3) && (move2 < move4) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moveing king vertically downwards
	else if((move1 == move3) && (move2 > move4) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king horizantally right
	else if((move2 == move4) && (move1 < move3) && (abs(move1 - move3) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king horizontally to left
	else if((move2 == move4) && (move1 > move3) && (abs(move1 - move3) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king diagonally up right
	else if((move1 < move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king diagonally up left
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;	
	}

	//Moving king diagonally down right
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king diagonally down left
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Checking for problems
	else {
		printf("Move not possible king\n");
		return;
	}
}


void move_b_king(int move1, int move2, int move3, int move4) {
	//Checking if end point has opposite side piece
	if(board[move4][move3] < 0) {
		printf("Move not possible! king - endpoint has wrong piece\n");
		return;
	}

	//Moving king vertilcally upwards
	else if((move1 == move3) && (move2 > move4) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moveing king vertically downwards
	else if((move1 == move3) && (move2 < move4) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king horizantally right
	else if((move2 == move4) && (move1 < move3) && (abs(move1 - move3) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king horizontally to left
	else if((move2 == move4) && (move1 < move3) && (abs(move1 - move3) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king diagonally up right
	else if((move1 > move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king diagonally up left
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;	
	}

	//Moving king diagonally down right
	else if((move1 < move3) && (move2 > move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Moving king diagonally down left
	else if((move1 > move3) && (move2 < move4) && (abs(move1 - move3) == 1) && (abs(move2 - move4) == 1)) {
		change_board(move1, move2, move3, move4);
		return;
	}

	//Checking for problems
	else {
		printf("Move not possible king\n");
		return;
	}
}
