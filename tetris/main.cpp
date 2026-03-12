#include <iostream>
#include "mov_piezas.h"
using namespace std;

int main()
{
    int rows=16;
    int cols=2;
    char** board= create_board(rows,cols);
    board[2][0]='a';
    board[9][1]='.';
    print_board(board,rows,cols);
    return 0;
}
