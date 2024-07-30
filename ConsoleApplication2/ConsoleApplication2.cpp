#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <string.h>
#include <math.h>
#include<time.h>
#include<stdlib.h>
#define width 9
#define height 3

using namespace std;
// -------------------------------------------------------- COSAS DE LA CONSOLA Y SU VISUALIZACION ------------------------------------------------------------------------

void setConsolePosition(int x, int y) {
	HWND consoleWindow = GetConsoleWindow(); // Obtiene el manejador de la ventana de la consola
	MoveWindow(consoleWindow, x, y, 800, 600, TRUE); // Mueve y redimensiona la ventana
}

void setConsoleSize(int ancho, int alto) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD newSize{};
	SMALL_RECT windowSize{};

	// Ajusta el tamaño del buffer
	newSize.X = ancho;
	newSize.Y = alto;
	SetConsoleScreenBufferSize(hConsole, newSize);

	// Ajusta el tamaño de la ventana
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = ancho - 1;
	windowSize.Bottom = alto - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void setCursorPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hConsole, coord);
}

void clearRegion(int x1, int y1, int x2, int y2) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord{};
	DWORD written{};

	// Define el punto de inicio de la región
	coord.X = x1;
	coord.Y = y1;

	// Limpia la región línea por línea
	for (int y = y1; y <= y2; ++y) {
		coord.Y = y;
		SetConsoleCursorPosition(hConsole, coord);
		for (int x = x1; x <= x2; ++x) {
			cout << ' ';
		}
	}

	// Restablece la posición del cursor al inicio de la región
	coord.X = x1;
	coord.Y = y1;
	SetConsoleCursorPosition(hConsole, coord);
}
// --------------------------------------------------------------------------------------------------------------------------------
void OcultarCursor();
void gotoxy(int x, int y);
void showImage(int pos[][width][2]);
void changePos(int positions[][width][2], char op);
void mantenerJuego(int positions[][width][2]);
void newchoosePosition(char& op);

void cuadroMenu();
void piso();
void showImage(char image[][width], int pos[][width][2]);
void presentacion();
void presentacion1();
void personaje2();
void imprimirTubo();
void gotoxy(int x, int y);
void setColor(int textColor, int backgroundColor);
void drawCircle(int centerX, int centerY, int radius, int offsetX, int offsetY, int color, int back); //dibuja las "nubes" de atras
void titulo(int x, int y);
void background(int radius, int numCircles);
void play(int a, int radio, int numCirculos, int x, int y);
void teclas(int b, int radio, int numCirculos, int x, int y);
void personaje(int c, int radio, int numCirculos, int x, int y);

int main() {
	setConsolePosition(400, 0); // Posicion de la consola aprox al centro de la pantalla
	setConsoleSize(100, 49); // Cambia el tamaño de la ventana a 100x49
	setCursorPosition(0, 0); // Restablece la posición del cursor a (0, 0)
	int position[][width][2] = { {{5,12},{6,12},{7,2},{8,12},{9,12},{10,12},{11,12},{12,12},{13,12}},{{5,13},{6,13},{7,13},{8,13},{9,13},{10,13},{11,13},{12,13},{13,13}},{{5,14},{6,14},{7,14},{8,14},{9,14},{10,14},{11,14},{12,14},{13,14}} };

	presentacion();
	OcultarCursor();
	mantenerJuego(position);
	return 0;
}
void presentacion() {
	int position[][width][2] = { {{5,12},{6,12},{7,2},{8,12},{9,12},{10,12},{11,12},{12,12},{13,12}},{{5,13},{6,13},{7,13},{8,13},{9,13},{10,13},{11,13},{12,13},{13,13}},{{5,14},{6,14},{7,14},{8,14},{9,14},{10,14},{11,14},{12,14},{13,14}} };
	const int radio = 10;
	const int numCirculos = 6;
	SetConsoleOutputCP(CP_UTF8);
	setColor(7, 3);
	int op, a = 0, b = 0, c = 0; // el a b c es de relleno como ejemplo, no va necesariamente, mas abajo lo utilizo para q funcione la operacion de las opciones, pero nel
	int x = 8, y = 2;
	do { // ------------------------------------- MENU en si
		system("cls");
		system("color 37");
		background(radio, numCirculos);
		imprimirTubo();
		titulo(x, y);
		cuadroMenu();
		piso();
		//posicion y diseño del pajarito
		int posXpaja = 5, posYpaja = 12;
		gotoxy(posXpaja, posYpaja); setColor(1, 3); cout << "   ▄▄▄"; setColor(15, 3); cout << "▄▄";
		gotoxy(posXpaja, posYpaja + 1); setColor(9, 1); cout << "██▄"; setColor(1, 3); cout << "███"; setColor(15, 3); cout << "█"; setColor(8, 0); cout << "▀"; setColor(15, 3); cout << "█";
		gotoxy(posXpaja, posYpaja + 2); setColor(9, 3); cout << " ▀█"; setColor(1, 3); cout << "████"; setColor(4, 12); cout << "▄▄▄";
		//---------

		gotoxy(x + 20, y + 9); setColor(6, 14); cout << "[1] Jugar" << endl;
		gotoxy(x + 20, y + 10); cout << "[2] Tutorial" << endl;
		gotoxy(x + 20, y + 11); cout << "[3] Opciones" << endl;
		gotoxy(x + 20, y + 12); cout << "[4] Salir" << endl;
		gotoxy(x + 20, y + 13); cout << "Ingrese una opción (1-4) : "; setColor(14, 3); gotoxy(x + 46, y + 13); cout << "█";
		cin >> op;
		cin.get();
		switch (op) {
		case 1: mantenerJuego(position); break;
		case 2: teclas(b, radio, numCirculos, x, y); break;
		case 3: personaje(c, radio, numCirculos, x, y); break;
		}
	} while (op != 4);
	gotoxy(40, 16);
	cout << "Gracias por jugar ..." << endl;
	gotoxy(27, 29);
}

void presentacion1() {
	int position[][width][2] = { {{5,12},{6,12},{7,2},{8,12},{9,12},{10,12},{11,12},{12,12},{13,12}},{{5,13},{6,13},{7,13},{8,13},{9,13},{10,13},{11,13},{12,13},{13,13}},{{5,14},{6,14},{7,14},{8,14},{9,14},{10,14},{11,14},{12,14},{13,14}} };
	const int radio = 10;
	const int numCirculos = 6;

	background(radio, numCirculos);
	imprimirTubo();

	SetConsoleOutputCP(CP_UTF8);
	setColor(7, 3);
	int a = 0, b = 0, c = 0; // el a b c es de relleno como ejemplo, no va necesariamente, mas abajo lo utilizo para q funcione la operacion de las opciones, pero nel
	int x = 8, y = 2;
	gotoxy(27, 29);
}
// -------------------------------------------- funciones a utilizar (lo busq en inter)
void gotoxy(int x, int y) { // posicion para imprimir
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int textColor, int backgroundColor) { // en el recuadro del caracter cambia el color de texto y fondo
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor + (backgroundColor * 16));
}
void nubesBack(int centerX, int centerY, int radius, int offsetX, int offsetY, int color, int back) { // parece elipse pero asi lo dibuja :v
	setColor(color, back); 
	for (int y = 1; y <= radius - 5; y++) { // dibuja verticalmente, de la parte de arriba del circulo hasta su centro (solo dibuja la mitad del circulo)
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
void nubesFront(int centerX, int centerY, int radius, int offsetX, int offsetY, int color, int back) { // parece elipse pero asi lo dibuja :v
	setColor(color, back);
	for (int y = 1; y <= radius - 7; y++) { // dibuja verticalmente, de la parte de arriba del circulo hasta su centro (solo dibuja la mitad del circulo)
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
	clearRegion(0, 0, 100, 41);
	// nubes de atras
	for (int k = 0; k < numCircles; k++) { //numero de nubes
		int offsetX = k * 15; // de 15 en 15 pixeles? :v
		int offsetY = rand() % 2; // varia aleatoriamente la posicion altura de las nubes
		int limite1 = 0;
		if (offsetY == 1) {
			limite1 = 1;
		}
		nubesBack(radius, radius, radius - limite1, offsetX, 36 + offsetY, 7,3); //el 17 le agrege para mover un poco la posicion de la nube en la consola y se ajuste aprox al piso
	}

	// nubes de adelante
	for (int k = 0; k < numCircles; k++) { //numero de nubes
		int offsetX2 = k * 15;
		int offsetY2 = rand() % 2; // varia aleatoriamente la posicion altura de las nubes
		int limite2 = 0;
		if (offsetY2 == 1) {
			limite2 = 1;
		}
		nubesFront(radius, radius, radius - limite2, offsetX2 + 5, 38 + offsetY2, 15,3);  // aca igual con el 5 y 20 segun los ejes claro
	}
}

void play(int a, int radio, int numCirculos,int x, int y) { // operacion al elegir jugar, pero solo lo agrege para q rellene (aca iria el juego en si)
	do {
		// ------------- basicamente hace lo mismo que la funcion principal al iniciar el do while (era q lo agrege todo a una solo funcion y llamarlo en cada opcion)
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
		background(radio, numCirculos);
		titulo(x, y);
		cuadroMenu();
		gotoxy(27, 12);
		setColor(6, 14);
		cout << "Juega (cualquier numero) hasta q pierdas (1): "; setColor(14, 3); gotoxy(72, 12); cout << "█";
		cin >> b;
	} while (b != 1);
	gotoxy(30, 18);
	system("pause");
}
void personaje(int c ,int radio, int numCirculos, int x, int y) { // operacion de relleno (el elegir personaje esta god)
	do {
		background(radio, numCirculos);
		titulo(x, y);
		cuadroMenu();
		personaje2();
		gotoxy(27, 12);
		setColor(6, 3);
		cout << "Juega (cualquier numero) hasta q pierdas (1): ";
		cin >> c;
	} while (c != 1);
	gotoxy(27, 14);
	system("pause");
}
void imprimirTubo() {
	int tamano = 7 + rand() % 19;
	int hueco = 9 + rand() % 3;
	int tamano2 = 41 - hueco - tamano;
	int posXtub = 10, posYpos = 41;
	gotoxy(posXtub - 1, posYpos - tamano); setColor(10, 3); cout << "███████████";
	gotoxy(posXtub - 1, posYpos - tamano + 1); setColor(10, 3); cout << "███████████";
	gotoxy(posXtub, posYpos - tamano + 2); setColor(2, 10); cout << "▀▀▀▀▀▀▀▀▀"; setColor(3, 3); cout << "█";
	for (int i = 0; i <= tamano - 3; i++) {
		gotoxy(posXtub, posYpos - i); setColor(10, 3); cout << "█████████";
	}

	gotoxy(posXtub, posYpos - tamano - hueco - 2); setColor(2, 10); cout << "▄▄▄▄▄▄▄▄▄"; setColor(3, 3); cout << "█";
	gotoxy(posXtub - 1, posYpos - tamano - hueco - 1); setColor(10, 3); cout << "███████████";
	gotoxy(posXtub - 1, posYpos - tamano - hueco); setColor(10, 3); cout << "███████████";

	for (int i = 3; i <= tamano2; i++) {
		gotoxy(posXtub, posYpos - tamano - hueco - i); setColor(10, 3); cout << "█████████";
	}

}


void personaje2() {
	int posXper = 5, posYper = 12;
	gotoxy(posXper+3, posYper); setColor(13, 3); cout <<     "▀█▄";
	gotoxy(posXper, posYper + 1); setColor(5, 3); cout << "█▄█"; setColor(13, 5); cout<< "▄█"; setColor(8, 13); cout << "▄"; setColor(13, 3); cout << "█▄";
	gotoxy(posXper, posYper + 2); setColor(5, 3); cout << "█▀█"; setColor(13, 5); cout << "▀█"; setColor(0, 13); cout << "▀"; setColor(13, 5); cout << "█▀";
}
// ---------------------------------------------
void showImage(int pos[][width][2]) {
	gotoxy(pos[0][0][0], pos[0][0][1]); setColor(1, 3); cout << "   ▄▄▄"; setColor(15, 3); cout << "▄▄";
	gotoxy(pos[1][0][0], pos[1][0][1]); setColor(9, 1); cout << "██▄"; setColor(1, 3); cout << "███"; setColor(15, 3); cout << "█"; setColor(8, 0); cout << "▀"; setColor(15, 3); cout << "█";
	gotoxy(pos[2][0][0], pos[2][0][1]); setColor(9, 3); cout << " ▀█"; setColor(1, 3); cout << "████"; setColor(4, 12); cout << "▄▄▄";
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
		k = -1;
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

void newchoosePosition(char& op) {
	auto start = std::chrono::high_resolution_clock::now();
	int timeout_ms = 250;
	gotoxy(40, 0);
	while (true) {
		if (_kbhit()) {

			op = _getch();
			setColor(14, 3);
			cout << "Tecla presionada!" << endl;
			if (op == 'a' || op == 'd' || op == 'w' || op == 's' || op == 'q') {
				return;
			}
		}
		setColor(14, 3);
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
		if (duration >= timeout_ms) {
			op = 'z';
			return;
		}
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void mantenerJuego(int positions[][width][2]) {
	char op;
	system("cls");
	piso();
	do {
		presentacion1();
		showImage(positions);
		newchoosePosition(op);
		changePos(positions, op);
	} while (op != 'q');

}
// --------------------------------------------------------
void cuadroMenu() {
	setColor(14, 3);
	for (int i = 0; i < 7; ++i) {
		gotoxy(25, 10 + i);
		for (int j = 0; j < 50; ++j) {
			cout << "█";
		}
		cout << endl;
	}
}
void piso() {
	for (int i = 0; i < 7; ++i) {
		gotoxy(0, 42 + i);
		if (i == 0 || i==1)
			setColor(2, 3);
		else
			setColor(6, 3);
		for (int j = 0; j < 100; ++j) {
			if (i == 0 || i == 1) {
				if (j % 2 == 0) {
					setColor(10, 3); // verde claro
				}
				else
					setColor(2, 3);  // verde
			}
			cout << "█";
		}
	}
}
void OcultarCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE; // Cambia la visibilidad del cursor a FALSE
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void titulo(int x, int y) {                  // tremendo titulo, es la unica forma de coutearlo :/
	SetConsoleOutputCP(CP_UTF8);
	
	// F
	gotoxy(x, y);     setColor(15, 3); cout << "███████"; setColor(7, 3); cout << "██";
	gotoxy(x, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x, y + 3); setColor(15, 3); cout << "██████"; setColor(7, 3); cout << "██";
	gotoxy(x, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x, y + 6); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";

	// L
	gotoxy(x + 8, y);     setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 8, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 8, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 8, y + 3); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 8, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 8, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 8, y + 6); setColor(15, 3); cout << "███████"; setColor(7, 3); cout << "█";

	// U
	gotoxy(x + 16, y);     setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y);   setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y+1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y+2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 3); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y+3); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y+4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y+5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 17, y + 6); setColor(15, 3); cout <<  "██████"; setColor(7, 3); cout << "█";

	// F
	gotoxy(x + 26, y);     setColor(15, 3); cout << "███████"; setColor(7, 3); cout << "█";
	gotoxy(x + 26, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 26, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 26, y + 3); setColor(15, 3); cout << "██████"; setColor(7, 3); cout << "█";
	gotoxy(x + 26, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 26, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";
	gotoxy(x + 26, y + 6); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "██";

	// F
	gotoxy(x + 34, y);     setColor(15, 3); cout << "███████"; setColor(7, 3); cout << "█";
	gotoxy(x + 34, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 34, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 34, y + 3); setColor(15, 3); cout << "██████"; setColor(7, 3); cout << "█";
	gotoxy(x + 34, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 34, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 34, y + 6); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";

	// Y
	gotoxy(x + 42, y);     setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 47, y); setColor(15, 3); cout <<       "██"; setColor(7, 3); cout << " ";
	gotoxy(x + 42, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 47, y + 1); setColor(15, 3); cout <<   "██"; setColor(7, 3); cout << " ";
	gotoxy(x + 43, y + 2); setColor(15, 3); cout <<  "██"; setColor(7, 3); cout << "█"; gotoxy(x + 46, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << " ";
	gotoxy(x + 44, y + 3); setColor(15, 3); cout <<   "███"; setColor(7, 3); cout << " ";
	gotoxy(x + 45, y + 4); setColor(15, 3); cout <<    "██"; setColor(7, 3); cout << " ";
	gotoxy(x + 45, y + 5); setColor(15, 3); cout <<    "██"; setColor(7, 3); cout << " ";
	gotoxy(x + 45, y + 6); setColor(15, 3); cout <<    "██"; setColor(7, 3); cout << " ";

	// B
	gotoxy(x + 53, y);     setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 53, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 58, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 53, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 58, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 53, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 53, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 58, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 53, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 58, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 53, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";

	// I
	gotoxy(x + 61, y);     setColor(7, 3); cout << "█"; setColor(15, 3); cout << "████";
	gotoxy(x + 62, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 62, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 62, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 62, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 62, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 61, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "████";

	// R
	gotoxy(x + 67, y);     setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 67, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 72, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<   "██";
	gotoxy(x + 67, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 72, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<   "██";
	gotoxy(x + 67, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 67, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 70, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 67, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 71, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 67, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 72, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout <<   "██";

	// D
	gotoxy(x + 75, y);     setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 75, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 79, y + 1); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 80, y + 2); setColor(7, 3); cout << "██"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 75, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 80, y + 3); setColor(7, 3); cout << "██"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 75, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 80, y + 4); setColor(7, 3); cout << "██"; setColor(15, 3); cout <<  "██";
	gotoxy(x + 75, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 79, y + 5); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
}