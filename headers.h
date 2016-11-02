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

#ifndef __HEADERS_H
#define __HEADERS_H

#define pawn 1
#define bishop 2
#define knight 3
#define rook 4
#define queen 5
#define king 6
#define x 0

//For which turn
#define WHITE 1
#define BLACK 2
#define OTHER 0

//For what player
#define COMP 1
#define TWO 2

//GLOBALS
int board[8][8];
int turn;
int player;
//For casteling white
int w_rook_flag, w_king_flag;
//For casteling black
int b_rook_flag, b_king_flag;


//For one player chess
typedef struct kill_structure {
	int move1, move2, move3, move4;
} kill_structure;

typedef struct normal_structure {
	int move1, move2, move3, move4;
} normal_structure;

typedef struct best_pawn_structure {
	int move1, move2, move3, move4, kill;
} best_pawn_structure;

typedef struct best_knight_structure {
	int move1, move2, move3, move4, kill;
} best_knight_structure;

typedef struct best_rook_structure {
	int move1, move2, move3, move4, kill;
} best_rook_structure;

typedef struct best_bishop_structure {
	int move1, move2, move3, move4, kill;
} best_bishop_structure;

typedef struct best_queen_structure {
	int move1, move2, move3, move4, kill;
} best_queen_structure;

typedef struct best_move_structure {
	int move1, move2, move3, move4, kill;
} best_move_structure;


//In file board.c

void initialize_board();

void print_board();

void change_board(int move1, int move2, int move3, int move4);

void simulate_board(int move1, int move2, int move3, int move4);

void rev_simulate_board(int move1, int move2, int move3, int move4);

int piece_value(int pos1, int pos2);

int white_check();

int black_check();

int random_number(int min_num, int max_num);

//In moves.c

int move_w_pawn(int move1, int move2, int move3, int move4);

int move_b_pawn(int move1, int move2, int move3, int move4);

int move_w_bishop(int move1, int move2, int move3, int move4);

int move_b_bishop(int move1, int move2, int move3, int move4);

int move_w_knight(int move1, int move2, int move3, int move4);

int move_b_knight(int move1, int move2, int move3, int move4);

int move_w_rook(int move1, int move2, int move3, int move4);

int move_b_rook(int move1, int move2, int move3, int move4);

int move_w_queen(int move1, int move2, int move3, int move4);

int move_b_queen(int move1, int move2, int move3, int move4);

int move_w_king(int move1, int move2, int move3, int move4);

int move_b_king(int move1, int move2, int move3, int move4);

int white_castle_kingside();

int white_castle_queenside();

int black_castle_kingside();

int black_castle_queenside();
#endif

