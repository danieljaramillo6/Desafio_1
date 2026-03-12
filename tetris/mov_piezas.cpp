#include <iostream>
using namespace std;

char** create_board(int rows, int cols){
    //Crear tablero donde se va a jugar
    char** board = new char*[rows];
    for (int i=0; i<rows; i++){
        board[i]= new char[cols];
        for (int j=0; j<cols;j++){
            board[i][j]=0;
        }
    }
    return board;
}

void print_board(char** board,int rows, int cols){
    //Imprimir el tablero de juego
    for(int i=0; i<rows; i++ ){
        cout<<"|";
        for(int j=0; j<cols; j++ ){
            for(int b=7; b>=0; b--){
                int bit=(board[i][j]>>b)&1;
                if (bit){
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
