#include <iostream>;

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

unsigned char** Eliminar_fila(unsigned char** board,int rows,int cols,int &score)
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
            score += 10;
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

                c--;
            }
        }
    }

    return board;
}
