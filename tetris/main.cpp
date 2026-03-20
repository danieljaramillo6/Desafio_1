#include <iostream>
#include "mov_piezas.h"
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
    int y = 0;                   // era "y=0", ahora la pieza entra desde arriba
    unsigned char* piece = create_piece();

    int ter = 0;                  // era "int ter;" sin inicializar (valor basura)

    while (true) {
        if (ter) break;
        print_board(board, rows, cols, x, y, piece);
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "W: rotar | A: Mover izquierda | D: Mover derecha | S: Mover abajo (fijar)" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        cin >> act;

        switch (act) {
        case 'W': case 'w':
            rotate_piece(piece,x,y,board,rows,cols);
            break;
        case 'A': case 'a':
            if (!move_left(board, rows, cols, x, y, piece)) cout << "No se pudo mover" << endl;
            break;
        case 'D': case 'd':
            if (!move_right(board, rows, cols, x, y, piece)) cout << "No se pudo mover" << endl;
            break;
        case 'S': case 's':
            if (!move_down(board,rows,cols,x,y,piece)) {
                board = set_piece(board, rows, cols, x, y, piece);
                delete[] piece;
                piece = create_piece();
                x = (cols * 8) / 2 - 1;
                y = 0;           // resetear a -3 igual que al inicio
                board = Eliminar_fila(board, rows, cols);
            }
            break;
        case 'Q': case 'q':
            ter = 1;
            break;
        default:
            cout << "Ingrese accion valida" << endl;
            break;
        }
    }
    return 0;
}
