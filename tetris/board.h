#ifndef BOARD_H
#define BOARD_H

unsigned char** create_board(int rows, int cols);
void print_board(unsigned char** board, int rows, int cols, int x, int y, unsigned char* piece);
unsigned char** Eliminar_fila(unsigned char** board, int rows, int cols,int &score);

#endif // BOARD_H
