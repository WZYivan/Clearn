#include <stdio.h>
#include <stdlib.h>

#define N 8

int board[N][N];

void printSolution() {
    static int count = 1;
    printf("Solution %d:\n", count++);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isSafe(int row, int col) {
    int i, j;
  
    for (i = 0; i < col; i++) {
        if (board[row][i]) {
            return 0;
        }
    }
  
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return 0;
        }
    }
  
    for (i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return 0;
        }
    }
  
    return 1;
}

int solveNQUtil(int col) {
    if (col >= N) {
        printSolution();
        return 1;
    }
  
    int res = 0;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
  
            res = solveNQUtil(col + 1) || res;//res 防止报告错误
  
            board[i][col] = 0; // backtrack
        }
    }
  
    return res;
}

void solveNQ() {
    if (solveNQUtil(0) == 0) {
        printf("No solution exists");
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
  
    solveNQ();
    return 0;
}
