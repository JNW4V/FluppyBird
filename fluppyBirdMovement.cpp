#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

#define width 6
#define height 3

using namespace std;
void OcultarCursor();
void gotoxy(int x, int y);
void showImage(char image[][width], int pos[][width][2]);
void changePos(int positions[][width][2], char op);
void mantenerJuego(char image[][width], int positions[][width][2]);
void newChoosePosition(char& op);


int main()
{
    char pajaro[height][width] = { {'-','-','-','-','-',' '},
                          {'|','-','^','-','|',' '},
                          {'|','_','_','_','|','>'} };
    int position[][width][2] = { {{2,2},{3,2},{4,2},{5,2},{6,2},{7,2}},{{2,3},{3,3},{4,3},{5,3},{6,3},{7,3}},{{2,4},{3,4},{4,4},{5,4},{6,4},{7,4}} };
    OcultarCursor();
    mantenerJuego(pajaro,position);

}
void showImage(char image[][width], int pos[][width][2]) {
    int actualX, actualY;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            actualX = pos[i][j][0];
            actualY = pos[i][j][1];
            gotoxy(actualX, actualY);
            cout << image[i][j];
        }
    }
}
void changePos(int positions[][width][2], char op) {
    int pos, k;
    switch (op) {
    case 'a':
        pos = 0;
        k = -1;
        break;
    case 'd':
        pos = 0;
        k = 1;
        break;
    case 'w':
        pos = 1;
        k = -2  ;
        break;
    case 's':
        pos = 1;
        k = 1;
        break;
    default:
        pos = 1;
        k = 2;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            positions[i][j][pos] += k;
        }
    }
}

void newChoosePosition(char& op) {
    auto start = chrono::high_resolution_clock::now();
    int timeout_ms = 300;  //Este es el tiempo de espera para que el jugador presione una tecla
    gotoxy(40, 40);
        cout << "\nOPCIONES: " << endl;
        cout << "a) Izquierda " << endl;
        cout << "d) Derecha " << endl;
        cout << "w) Arriba " << endl;
        cout << "s) Abajo " << endl;
        cout << "q) Salir " << endl;
        cout << "Escoja su opcion: ";
        while (true) {
            if (_kbhit()) {
                // Lee la tecla para vaciar el buffer
                op = _getch();
                if (op == 'a' || op == 'd' || op == 'w' || op == 's' || op == 'q') {
                    return;
                }
            }
            // Comprueba si ha pasado el tiempo de espera
            auto now = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(now - start).count();
            if (duration >= timeout_ms) {
                op = 'z';  //Cualquier valor para que no pase nada
                return;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
    }
}
void mantenerJuego(char image[][width], int positions[][width][2]) {
    char op;
    do {
        
        system("cls");
        showImage(image, positions);
        newChoosePosition(op);
        changePos(positions, op);
    } while (op != 'q');

}

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
void OcultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
