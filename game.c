#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define col 4
#define row 4

//player and computer
#define PLAYER 1
#define COMPUTER 2

//results
#define WIN 1
#define DRAW 0
#define LOSS -1

//mode
#define MIN 0
#define MAX 1

//1 for player 1
//2 for player 2
int board[row][col];

void printBoard() {
    printf("\e[2J\e[H");
	printf("_________________\n");
	for(int i = 0; i < row; i++) {
		printf("|   |   |   |   |\n|");
		for(int j = 0; j < col; j++) {
			printf(" %d |", board[i][j]);
		}
		printf("\n");
		printf("|___|___|___|___|\n");
	}
}

//so far only for horizontal and vertical
int isWinPosition(int board[][col]) {
	//check if horizontal win
	for(int i = 0; i < row; i++) {
		if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0)
			return 1;
		if(board[i][3] == board[i][1] && board[i][1] == board[i][2] && board[i][3] != 0)
			return 1;	
	}
	
	//check if vertical win
	for(int j = 0; j < col; j++) {
		if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != 0)
			return 1;
		if(board[3][j] == board[1][j] && board[1][j] == board[2][j] && board[3][j] != 0)
			return 1;
	}


	return 0;
}

int playerMove() {
    int c;
    while(1) {
        printf("Enter column: ");
        scanf("%d", &c);
        if(c < 0 || c >= col) {
            printf("Invalid column. Entered column should be between 0 and %d\n", col-1);
            continue;
        }
        if(board[0][c] != 0) {
            printf("Column is full. Invalid move!\n");
            continue;
        }
        break;
    }

    return c;
}

int updateBoardforSolver(int move, int board[][col]) {

    for(int i = row-1; i >= 0; i--) {
        if(board[i][move] == 0) {
            board[i][move] = COMPUTER;
            return i;
        }
    }
}

int solve(int board[][col], int mode) {
    int move = 0, m = -1, flag = 0;
    for(int c = 0; c < col; c++) {
        if(board[0][c] == 0) {
            if(!flag) {
                flag = 1;
                move = c;
            }
            int i = updateBoardforSolver(c, board);
            int temp = solve(board, mode^1);
            if(temp > max) {
                max = temp;
                move = c;
            }
            board[i][c] = 0;
        }
    }
    return move;
}

int computerMove() {
    return solve(board, MAX);
}

//player is 1 or 2, move is the column number
//move should be valid!!
void updateBoard(int player, int move) {

    for(int i = row-1; i >= 0; i--) {
        if(board[i][move] == 0) {
            board[i][move] = player;
            break;
        }
    }
}

int main() {
    srand(time(0));
    printBoard();
    
    int move;
    int choice = 0;

    //player moves first
    if(choice == 0) {
        //game loop
        while(1) {
            move = playerMove();
            updateBoard(PLAYER, move);
            printBoard();
            if(isWinPosition(board)) {
                printf("YOU WIN!!!");
                break;
            }
            move = computerMove();
            updateBoard(COMPUTER, move);
            printBoard();
            if(isWinPosition(board)) {
                printf("YOU LOSE!!!");
                break;
            }
        }   
    }

	return 0;
}
