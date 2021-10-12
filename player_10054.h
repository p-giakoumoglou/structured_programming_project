#include"board.h"

extern int player_10054(const Board* b);


int CheckEmpty(const Board* b);
Board* createMirror(const Board* b);
int sum_of_row(int **table, int row, int columns, int me, int enemy, Board* mirror);
int scoring(int me, int enemy, Board* mirror);
