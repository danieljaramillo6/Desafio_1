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

bool move_right(unsigned char** board,int rows,int cols,int& x,int y,unsigned char* piece)
{
    int coor_x;

    coor_x = x + 1; // la coordenada a mover a la derecha ->

    for(int py = 0 ; py<4 ; py++ ){ // recorre la fila de la figura

        unsigned char row = piece[py];

        for(int px = 0 ; px < 8; px++){ // recorre los bits de la fila

            int bit = (row >> (7 - px)) & 1;

            if(bit){ // revisa si hay un bloque si hay debe ser bit = 1

                int bx = coor_x + px, by = y + py ; //calcula la posicion del tablero

                // revisa el limite de la pared derecha
                if(bx >= cols * 8)
                    return false;

                // revisa el suelo
                if(by >= rows)
                    return false;

                int byte = bx / 8; // calcular byte del tablero de la columna
                int bitpos = 7 - (bx % 8); // mover el bit hasta la ultima posicion

                if((board[by][byte] >> bitpos)& 1) // calcula si hay espacio disponible 1 = lleno, 0 = vacio
                {
                    return false;
                }


            }
        }
    }
    x = coor_x ;
    return true;
}

bool move_left(unsigned char** board,int rows,int cols,int& x,int y,unsigned char* piece)
{
    int coor_x;
    coor_x = x - 1;

    for(int py = 0 ; py<4 ; py++ ){ // recorre la fila de la figura

        unsigned char row = piece[py];

        for(int px = 0 ; px < 8; px++){ // recorre los bits de la fila

            int bit = (row >> (7 - px)) & 1;

            if(bit){// revisa si hay un bloque si hay debe ser bit = 1

                int bx = coor_x + px, by = y + py ; //calcula la posicion del tablero

                //revisar limite de la parde izquierda
                if(bx < 0){

                    return false;
                }// limite del suelo
                if(by >= rows){
                    return false;
                }
                int byte = bx / 8; // calcular byte del tablero de la columna
                int bitpos = 7 - (bx % 8); // mover el bit hasta la ultima posicion

                if((board[by][byte] >> bitpos)& 1) // calcula si hay espacio disponible 1 = lleno, 0 = vacio
                {
                    return false;
                }

            }

        }
    }
    x = coor_x ;
    return true;
}

bool move_down(unsigned char** board,int rows,int cols,int x,int& y,unsigned char* piece)
{
    int coor_y;
    coor_y = y + 1;

    for(int py = 0; py < 4; py++)
    {
        unsigned char row = piece[py];

        for(int px = 0; px < 8; px++)
        {

            int bit = (row >> (7 - px)) & 1;

            if(bit)
            {
                int bx = x + px, by = coor_y + py ;

                if(by >= rows){
                    return false;
                }
                int byte = bx / 8; // calcular byte del tablero de la columna
                int bitpos = 7 - (bx % 8); // mover el bit hasta la ultima posicion

                if((board[by][byte] >> bitpos)& 1) // calcula si hay espacio disponible 1 = lleno, 0 = vacio
                {
                    return false;
                }
            }
        }

    }
    y = coor_y;
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
