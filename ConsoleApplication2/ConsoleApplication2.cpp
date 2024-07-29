#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
using namespace std;

void gotoxy(int x, int y);
void setColor(int textColor, int backgroundColor);
void drawCircle(int centerX, int centerY, int radius, int offsetX, int offsetY, int color, int back); //dibuja las "nubes" de atras
void titulo(int x, int y);
void background(int radius, int numCircles);
void play(int a, int radio, int numCirculos, int x, int y);
void teclas(int b, int radio, int numCirculos, int x, int y);
void personaje(int c, int radio, int numCirculos, int x, int y);

int main() {
	const int radio = 10;
	const int numCirculos = 6;
	SetConsoleOutputCP(CP_UTF8);
	setColor(7,3);
	int op, a = 0, b = 0, c = 0; // el a b c es de relleno como ejemplo, no va necesariamente, mas abajo lo utilizo para q funcione la operacion de las opciones, pero nel
	int x = 8, y = 2;
	do { // ------------------------------------- MENU en si
		system("cls");
		system("color 37");
		srand(time(NULL));
		background(radio, numCirculos);
		titulo(x, y);

		//posicion y diseño del pajarito
		int posXpaja = 5, posYpaja = 12;
		gotoxy(posXpaja, posYpaja); setColor(1, 3); cout << "   ▄▄▄"; setColor(15, 3); cout << "▄▄";
		gotoxy(posXpaja, posYpaja + 1); setColor(9, 1); cout << "██▄"; setColor(1, 3); cout << "███"; setColor(15, 3); cout << "█"; setColor(8, 0); cout << "▀"; setColor(15, 3); cout << "█";
		gotoxy(posXpaja, posYpaja + 2); setColor(9, 3); cout << " ▀█"; setColor(1, 3); cout << "████"; setColor(4, 12); cout << "▄▄▄";
		//---------
		gotoxy(10, 6);
		setColor(6, 14);
		gotoxy(x+20, y + 9); cout << "[1] Jugar" << endl;
		gotoxy(x + 20, y + 10); cout << "[2] Tutorial" << endl;
		gotoxy(x + 20, y + 11); cout << "[3] Opciones" << endl;
		gotoxy(x + 20, y + 12); cout << "[4] Salir" << endl;
		gotoxy(x + 20, y + 13); cout << "Ingrese una opción (1-4) : ";
		cin >> op;
		cin.get();
		switch (op) {
		case 1: play(a, radio, numCirculos,x,y); break;
		case 2: teclas(b, radio, numCirculos,x,y); break;
		case 3: personaje(c, radio, numCirculos,x,y); break;
		}
	} while (op != 4);
	gotoxy(40, 16);
	cout << "Gracias por jugar ..." << endl;
	gotoxy(27, 29);
	return 0;
}
// -------------------------------------------- funciones a utilizar (lo busq en inter)
void gotoxy(int x, int y) { // posicion para imprimir
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int textColor, int backgroundColor) { // en el recuadro del caracter cambia el color de texto y fondo
	// la paleta de colores esta en el pdf del profe de la sesion 9, pero aca lo pongo porsiaca:
	/*
		0 = Negro
		1 = Azul
		2 = Verde
		3 = Aguamarina
		4 = Rojo
		5 = Purpura
		6 = Amarillo
		7 = Blanco
		8 = Gris
		9 = Azul claro
		10 (A) = Verde claro 
		11 (B) = Aguamarina claro 
		12 (C) = Rojo claro 
		13 (D) = Purpura claro 
		14 (E) = Amarillo claro 
		15 (F) = Blanco brillante 
	*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor + (backgroundColor * 16));
}
void drawCircle(int centerX, int centerY, int radius, int offsetX, int offsetY, int color, int back) { // parece elipse pero asi lo dibuja :v
	setColor(color, back); 
	for (int y = 1; y <= radius - 3; y++) { // dibuja verticalmente, de la parte de arriba del circulo hasta su centro (solo dibuja la mitad del circulo)
		for (int x = 0; x <= 2 * radius; x++) { // dibuja horizontamente del extremo izquierdo al derecho por linea (diametro = 2 * radio)
			int dx = x - radius;
			int dy = y - radius;

			if (sqrt(dx * dx + dy * dy) <= radius) { // ecuacion de la circunferencia (llegua hasta que sea igual al radio)
				gotoxy(x + offsetX, y + offsetY);
				cout << "█";
			}
		}
	}
}
// --------------------------------------------

void background(int radius,int numCircles) {
	system("cls");

	//cuadro amarillo claro del menu
	setColor(14, 3); 
	for (int i = 0; i < 7; ++i) {	
		gotoxy(25, 10 + i);
		for (int j = 0; j < 50; ++j) {
			cout << "█";
		}
		cout << endl;
	}
	// nubes de atras
	for (int k = 0; k < numCircles; k++) { //numero de nubes
		int offsetX = k * 15; // de 15 en 15 pixeles? :v
		int offsetY = rand() % 3; // varia aleatoriamente la posicion altura de las nubes
		drawCircle(radius, radius, radius, offsetX, 17 + offsetY, 7,0); //el 17 le agrege para mover un poco la posicion de la nube en la consola y se ajuste aprox al piso
	}

	// nubes de adelante
	for (int k = 0; k < numCircles; k++) { //numero de nubes
		int offsetX = k * 15;
		int offsetY = rand() % 3; // varia aleatoriamente la posicion altura de las nubes
		drawCircle(radius, radius, radius, offsetX + 5, 20 + offsetY, 15,0);  // aca igual con el 5 y 20 segun los ejes claro
	}
	int i, j;
	char t1[100][100]; // cadena donde se guardaria el pasto y tierra

	for (i = 0; i < 100; i++) {
		strcpy_s(t1[i], "█"); // asigna el caracter a cada posicion de la cadena (creo q se puede optimizar este paso)
	}
	gotoxy(1, 23); //posicion del piso
	for (i = 0; i < 6; i++) { // por fila --
		if (i == 0) {
			setColor(2, 0); // verde si es la primera fila
		}
		else {
			setColor(6, 0); // el resto marron tierra (no es pero parecido)
		}
		cout << endl;
		for (j = 0; j < 100; j++) { // por columna ||
			// ------------------------------------------------   solo para alternar entre verde claro y oscuro del pasto en la primera fila (detalles)
			if (i == 0) {
				if (j % 2 == 0) {
					setColor(10, 0); // verde claro
				}
				else
					setColor(2, 0);  // verde
			}
			// ------------------------------------------------
			cout << t1[j];  // imprime cada caracter (debe haber otra forma de hacer el piso :v)
		}
	}
}

void play(int a, int radio, int numCirculos,int x, int y) { // operacion al elegir jugar, pero solo lo agrege para q rellene (aca iria el juego en si)
	do {
		// ------------- basicamente hace lo mismo que la funcion principal al iniciar el do while (era q lo agrege todo a una solo funcion y llamarlo en cada opcion)
		system("cls");
		system("color 37");
		background(radio, numCirculos);
		titulo(x, y);
		gotoxy(27, 12);
		setColor(6, 14);
		// --------------------------------
		cout << "Juega (cualquier numero) hasta q pierdas (1): "; // wbds, con tal q acabe la operacion y pase de nuevo al menu
		cin >> a;
	} while (a != 1);
	gotoxy(27, 14);
	system("pause");
}
void teclas(int b, int radio, int numCirculos, int x, int y) { // operacion de relleno (deberia mostrarse los controles)
	do {
		system("cls");
		system("color 37");
		background(radio, numCirculos);
		titulo(x, y);
		gotoxy(27, 12);
		setColor(6, 14);
		cout << "Juega (cualquier numero) hasta q pierdas (1): ";
		cin >> b;
	} while (b != 1);
	gotoxy(27, 14);
	system("pause");
}
void personaje(int c ,int radio, int numCirculos, int x, int y) { // operacion de relleno (el elegir personaje esta god)
	do {
		system("cls");
		system("color 37");
		background(radio, numCirculos);
		titulo(x, y);
		gotoxy(27, 12);
		setColor(6, 14);
		cout << "Juega (cualquier numero) hasta q pierdas (1): ";
		cin >> c;
	} while (c != 1);
	gotoxy(27, 14);
	system("pause");
}

void titulo(int x, int y) {                  // tremendo titulo, es la unica forma de coutearlo :/
	SetConsoleOutputCP(CP_UTF8);
	setColor(15, 3);
	// F
	gotoxy(x, y);     cout << "███████ ";
	gotoxy(x, y + 1); cout << "██      ";
	gotoxy(x, y + 2); cout << "██      ";
	gotoxy(x, y + 3); cout << "██████  ";
	gotoxy(x, y + 4); cout << "██      ";
	gotoxy(x, y + 5); cout << "██      ";
	gotoxy(x, y + 6); cout << "██      ";

	// L
	gotoxy(x + 8, y);     cout << "██      ";
	gotoxy(x + 8, y + 1); cout << "██      ";
	gotoxy(x + 8, y + 2); cout << "██      ";
	gotoxy(x + 8, y + 3); cout << "██      ";
	gotoxy(x + 8, y + 4); cout << "██      ";
	gotoxy(x + 8, y + 5); cout << "██      ";
	gotoxy(x + 8, y + 6); cout << "███████ ";

	// U
	gotoxy(x + 16, y);     cout << "██    ██";
	gotoxy(x + 16, y + 1); cout << "██    ██";
	gotoxy(x + 16, y + 2); cout << "██    ██";
	gotoxy(x + 16, y + 3); cout << "██    ██";
	gotoxy(x + 16, y + 4); cout << "██    ██";
	gotoxy(x + 16, y + 5); cout << "██    ██";
	gotoxy(x + 16, y + 6); cout << " ██████ ";

	// F
	gotoxy(x + 26, y);     cout << "███████ ";
	gotoxy(x + 26, y + 1); cout << "██      ";
	gotoxy(x + 26, y + 2); cout << "██      ";
	gotoxy(x + 26, y + 3); cout << "██████  ";
	gotoxy(x + 26, y + 4); cout << "██      ";
	gotoxy(x + 26, y + 5); cout << "██      ";
	gotoxy(x + 26, y + 6); cout << "██      ";

	// F
	gotoxy(x + 34, y);     cout << "███████ ";
	gotoxy(x + 34, y + 1); cout << "██      ";
	gotoxy(x + 34, y + 2); cout << "██      ";
	gotoxy(x + 34, y + 3); cout << "██████  ";
	gotoxy(x + 34, y + 4); cout << "██      ";
	gotoxy(x + 34, y + 5); cout << "██      ";
	gotoxy(x + 34, y + 6); cout << "██      ";

	// Y
	gotoxy(x + 42, y);     cout << "██   ██";
	gotoxy(x + 42, y + 1); cout << "██   ██";
	gotoxy(x + 42, y + 2); cout << " ██ ██ ";
	gotoxy(x + 42, y + 3); cout << "  ███  ";
	gotoxy(x + 42, y + 4); cout << "   ██  ";
	gotoxy(x + 42, y + 5); cout << "   ██  ";
	gotoxy(x + 42, y + 6); cout << "   ██  ";

	// Space
	gotoxy(x + 50, y);     cout << "   ";
	gotoxy(x + 50, y + 1); cout << "   ";
	gotoxy(x + 50, y + 2); cout << "   ";
	gotoxy(x + 50, y + 3); cout << "   ";
	gotoxy(x + 50, y + 4); cout << "   ";
	gotoxy(x + 50, y + 5); cout << "   ";
	gotoxy(x + 50, y + 6); cout << "   ";

	// B
	gotoxy(x + 54, y);     cout << "██████ ";
	gotoxy(x + 54, y + 1); cout << "██   ██";
	gotoxy(x + 54, y + 2); cout << "██   ██";
	gotoxy(x + 54, y + 3); cout << "██████ ";
	gotoxy(x + 54, y + 4); cout << "██   ██";
	gotoxy(x + 54, y + 5); cout << "██   ██";
	gotoxy(x + 54, y + 6); cout << "██████ ";

	// I
	gotoxy(x + 62, y);     cout << "████";
	gotoxy(x + 62, y + 1); cout << " ██ ";
	gotoxy(x + 62, y + 2); cout << " ██ ";
	gotoxy(x + 62, y + 3); cout << " ██ ";
	gotoxy(x + 62, y + 4); cout << " ██ ";
	gotoxy(x + 62, y + 5); cout << " ██ ";
	gotoxy(x + 62, y + 6); cout << "████";

	// R
	gotoxy(x + 68, y);     cout << "██████ ";
	gotoxy(x + 68, y + 1); cout << "██   ██";
	gotoxy(x + 68, y + 2); cout << "██   ██";
	gotoxy(x + 68, y + 3); cout << "██████ ";
	gotoxy(x + 68, y + 4); cout << "██ ██  ";
	gotoxy(x + 68, y + 5); cout << "██  ██ ";
	gotoxy(x + 68, y + 6); cout << "██   ██";

	// D
	gotoxy(x + 76, y);     cout << "██████ ";
	gotoxy(x + 76, y + 1); cout << "██   ██";
	gotoxy(x + 76, y + 2); cout << "██    ██";
	gotoxy(x + 76, y + 3); cout << "██    ██";
	gotoxy(x + 76, y + 4); cout << "██    ██";
	gotoxy(x + 76, y + 5); cout << "██   ██";
	gotoxy(x + 76, y + 6); cout << "██████ ";
}