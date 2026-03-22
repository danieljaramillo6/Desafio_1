#ifndef MOV_PIEZAS_H
#define MOV_PIEZAS_H

unsigned char* create_piece();
bool hay_colision(unsigned char** board, int rows, int cols_bytes, unsigned char* piece, int px, int py, int &score);
bool move_right(unsigned char** board, int rows, int cols, int& x, int y, unsigned char* piece);
bool move_left(unsigned char** board, int rows, int cols, int& x, int y, unsigned char* piece);
bool move_down(unsigned char** board, int rows, int cols_bytes, int x, int& y, unsigned char* piece);
unsigned char** set_piece(unsigned char** board, int rows, int cols, int x, int y, unsigned char* piece);
bool rotate_piece(unsigned char* piece, int& x, int& y, unsigned char** board, int rows, int cols_bytes);
bool act_piece(unsigned char** &board, unsigned char* &piece, int &x,int &y, int rows,int cols, int &score);

#endif // MOV_PIEZAS_H
