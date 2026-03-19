#include <iostream>
#include "mov_piezas.h"
using namespace std;

int main()
{
    int rows=8;
    int cols=3;
    unsigned char** board= create_board(rows,cols);
    int x=(cols*8)/2-1;
    int y=1;
    unsigned char* piece=create_piece();
    //print_board(board,rows,cols,x,y,piece);
    board[2][0]=255;
    board[2][1]=255;
    board[2][2]=255;
    board[4][0]=255;
    board[3][0]=43;
    board[2][0]=255;
    print_board(board,rows,cols,x,y,piece);
    board=Eliminar_fila(board,rows,cols);
    cout<<" fuck dre "<<endl;
    print_board(board,rows,cols,x,y,piece);

    return 0;
}
