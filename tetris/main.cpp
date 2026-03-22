#include <iostream>
#include "piece.h"
#include "board.h"
using namespace std;

int main() {
    char act;
    int rows, cols;
    while (true) {
        cout << "Ingrese el numero de filas (minimo 8): " << endl;
        cin >> rows;
        cout << "Ingrese el numero de columnas (minimo 8, multiplo de 8): " << endl;
        cin >> cols;
        if (rows >= 8 && cols >= 8 && cols % 8 == 0) break;
        cout << "Datos no validos" << endl;
    }

    cols = cols / 8;
    unsigned char** board = create_board(rows, cols);
    int x = (cols * 8) / 2 - 1;
    int y = 0;
    int score=0;
    unsigned char* piece = create_piece();

    bool ter=true;

    while (ter) {
        print_board(board, rows, cols, x, y, piece);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "W: rotar | A: Mover izquierda | D: Mover derecha | S: Mover abajo (fijar) | Q: Terminar Juego  | Puntaje: " <<score<< endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cin >> act;

        switch (act) {
        case 'W': case 'w':
            if(!rotate_piece(piece,x,y,board,rows,cols))cout << "No se pudo Rotar"<<endl;
            break;
        case 'A': case 'a':
            if (!move_left(board, rows, cols, x, y, piece)) cout << "No se pudo mover" << endl;
            break;
        case 'D': case 'd':
            if (!move_right(board, rows, cols, x, y, piece)) cout << "No se pudo mover" << endl;
            break;
        case 'S': case 's':
            if (!move_down(board,rows,cols,x,y,piece)) {
                ter=act_piece(board,piece,x,y,rows,cols,score);
            }
            break;
        case 'Q': case 'q':
            ter = false;
            break;
        default:
            cout << "Ingrese accion valida" << endl;
            break;
        }
    }
    return 0;
}
