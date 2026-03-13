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

unsigned char** Eliminar_fila(unsigned char** board,int rows,int cols){
    bool cero;
    for (int i=0;i<rows;i++){
        bool full=true;
        for(int j=0;j<cols;j++){
            if(board[i][j]!=255){
                full=false;
                break;
            }
        }
        if (full){
            for(int j=0;j<cols;j++){
                board[i][j]=0;
            }
            int c=i;
            while(true){

            for(int j=0;j<cols;j++){
                if(board[c-1][j]!=0){
                    char* copia=new char[cols];
                    for(int m=0;m<cols;m++){
                        copia[m]=board[c-1][m];
                    }
                    for(int m=0;m<cols;m++){
                        board[c-1][m]=0;
                    }
                    for(int m=0;m<cols;m++){
                        board[c][m]=copia[m];
                    }
                    delete[] copia;
                    cero=false;
                }else{
                    cero=true;
                }
                c--;
                }
            if(cero)break;

        }
    }
}
    return board;
}
