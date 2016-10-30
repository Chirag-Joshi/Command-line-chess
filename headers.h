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
#define WHITE INT_MAX
#define BLACK INT_MIN
#define OTHER 0

//GLOBALS
int board[8][8];
int turn;

//In file board.c

void initialize_board();

void print_board();

void change_board(int move1, int move2, int move3, int move4);


//In moves.c

void move_w_pawn(int move1, int move2, int move3, int move4);

void move_b_pawn(int move1, int move2, int move3, int move4);

void move_w_bishop(int move1, int move2, int move3, int move4);

void move_b_bishop(int move1, int move2, int move3, int move4);

void move_w_rook(int move1, int move2, int move3, int move4);

void move_b_rook(int move1, int move2, int move3, int move4);

void move_w_knight(int move1, int move2, int move3, int move4);

void move_b_knight(int move1, int move2, int move3, int move4);

void move_w_queen(int move1, int move2, int move3, int move4);

void move_b_queen(int move1, int move2, int move3, int move4);

void move_w_king(int move1, int move2, int move3, int move4);

void move_b_king(int move1, int move2, int move3, int move4);

#endif

