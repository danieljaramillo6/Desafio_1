#ifndef MOV_PIEZAS_H
#define MOV_PIEZAS_H
unsigned char** create_board(int rows, int cols);
void print_board(unsigned char** board,int rows, int cols,int x,int y,unsigned char* piece);
unsigned char* create_piece();
unsigned char** Eliminar_fila(unsigned char** board, int rows,int cols);

#endif // MOV_PIEZAS_H
