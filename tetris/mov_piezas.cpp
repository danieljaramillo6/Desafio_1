#include <iostream>
#include <random>
using namespace std;

unsigned char** create_board(int rows, int cols){
    //Crear tablero donde se va a jugar
    unsigned char** board = new unsigned char*[rows];
    for (int i=0; i<rows; i++){
        board[i]= new unsigned char[cols];
        for (int j=0; j<cols;j++){
            board[i][j]=0;
        }
    }
    return board;
}

void print_board(unsigned char** board,int rows, int cols,int x,int y,unsigned char* piece){
    //Imprimir el tablero de juego
    for(int i=0; i<rows; i++ ){
        cout<<"|";
        for(int j=0; j<cols; j++ ){
            for(int b=7; b>=0; b--){
                int bit=(board[i][j]>>b)&1;
                int col_b=j*8+(7-b);
                int bx=col_b-x;
                int by=i-y+3;
                bool pieza=false;
                if (by>=0 && by<4 && bx >= 0 && bx<4){
                    int bbit=(piece[by]>>(7-bx))&1;
                    if(bbit) pieza=true;
                }
                if (bit){
                    cout<<"[]";
                }
                else if(pieza){
                    cout<<"[]";
                }
                else{
                    cout<<". ";
                }
            }
            }
            cout<<"|"<<endl;
        }
    }

unsigned char* create_piece(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,5);
    int numero = dist(gen);
    unsigned char* piece=new unsigned char[4];
    switch (numero){
    case 1:
        piece[0]=0;
        piece[1]=0;
        piece[2]=192;
        piece[3]=96;
        return piece;
        break;
    case 2:
        piece[0]=128;
        piece[1]=128;
        piece[2]=128;
        piece[3]=128;
        return piece;
        break;
    case 3:
        piece[0]=0;
        piece[1]=128;
        piece[2]=128;
        piece[3]=192;
        return piece;
        break;
    case 4:
        piece[0]=0;
        piece[1]=0;
        piece[2]=192;
        piece[3]=192;
        return piece;
        break;
    case 5:
        piece[0]=0;
        piece[1]=0;
        piece[2]=224;
        piece[3]=64;
        return piece;
        break;
    }
}

unsigned char** Eliminar_fila(unsigned char** board,int rows,int cols)
{
    for(int i=0;i<rows;i++)
    {
        bool full=true;

        for(int j=0;j<cols;j++)
        {
            if(board[i][j]!=255)
            {
                full=false;
                break;
            }
        }

        if(full)
        {
            for(int j=0;j<cols;j++)
                board[i][j]=0;

            int c=i;

            while(c>0)
            {
                for(int m=0;m<cols;m++)
                {
                    board[c][m]=board[c-1][m];
                    board[c-1][m]=0;
                }

                c--;   // ← ahora está en el lugar correcto
            }
        }
    }

    return board;
}

bool hay_colision(unsigned char** board, int rows, int cols_bytes, unsigned char* piece, int px, int py)
{
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            int bit = (piece[row] >> (7 - col)) & 1;
            if(!bit) continue;

            int board_x = px + col;
            int board_y = py - (3 - row);



            if(board_x < 0 || board_x >= cols_bytes * 8)
            {
                return true;
            }
            if(board_y >= rows)
            {
                return true;
            }
            if (board_y < 0) {

                continue;
            }

            int byte   = board_x / 8;

            int bitpos = 7 - (board_x % 8);

            if((board[board_y][byte] >> bitpos) & 1)
            {
                return true;

            }
        }
    }

    return false;
}

bool move_left(unsigned char** board, int rows, int cols_bytes, int& x, int y, unsigned char* piece)
{
    if(hay_colision(board, rows, cols_bytes, piece, x - 1, y))
    {
        return false;
    }

    x--;
    return true;
}

bool move_right(unsigned char** board, int rows, int cols_bytes, int& x, int y, unsigned char* piece)
{
    if(hay_colision(board, rows, cols_bytes, piece, x + 1, y))
    {
        return false;
    }

    x++;
    return true;
}

bool move_down(unsigned char** board, int rows, int cols_bytes, int x, int& y, unsigned char* piece)
{

    if(hay_colision(board, rows, cols_bytes, piece, x, y + 1))
    {
        return false;
    }

    y++;
    return true;
}
unsigned char** set_piece(unsigned char** board,int rows,int cols,int x,int y,unsigned char* piece){

    for(int i=0;i<=y;i++){
        if(y-i<4){
            unsigned char* copia=new unsigned char[cols];
            for(int j=0;j<cols;j++){
                copia[j]=0;
            }
            for(int j=0;j<cols;j++){
                for(int c=7;c>=0;c--){
                    int col=j*8+(7-c);
                    int px=col-x;
                    if(px >= 0 && px < 4){
                        int row=i+3-y;
                        int bit=(piece[row] >> (7-px)) & 1;
                        if(bit){
                            copia[j] |= (1 << c);
                        }
                    }
                }
            }
            for(int j=0;j<cols;j++){
                board[i][j] |= copia[j];
            }
            delete[] copia;
        }
    }
    return board;
}
void rotate_piece(unsigned char* piece, int& x, int& y, unsigned char** board, int rows, int cols_bytes)
{
    unsigned char copy_piece[4] = {0,0,0,0};

    // Rotacion 90 grados
    for(int py = 0; py < 4; py++)
    {
        unsigned char row = piece[py];
        for(int px = 0; px < 4; px++)
        {
            int bit = (row >> (7 - px)) & 1;
            if(bit)
            {
                int new_x = 3 - py;
                int new_y = px;
                copy_piece[new_y] |= (1 << (7 - new_x));
            }
        }
    }

    // Empujar hacia la izquierda
    bool left_empty = true;
    while(left_empty)
    {
        for(int i = 0; i < 4; i++)
        {
            if(copy_piece[i] & 0x80)
            {
                left_empty = false;

                break;
            }
        }

        if(left_empty)
        {

            for(int i = 0; i < 4; i++)
            {

                copy_piece[i] <<= 1;
            }
        }
    }

    // Empujar hacia abajo
    while(copy_piece[3] == 0)
    {
        for(int i = 3; i > 0; i--)
        {
            copy_piece[i] = copy_piece[i-1];
        }
        copy_piece[0] = 0;
    }

    // Solo aplicar si no hay colision con la pieza rotada
    if(!hay_colision(board, rows, cols_bytes, copy_piece, x, y))
    {
        for(int i = 0; i < 4; i++)
            piece[i] = copy_piece[i];
    }
    // Si hay colision, piece queda intacta y la rotacion se cancela
}
