#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <string.h>
#include <math.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>
#include <vector>
#define width 9
#define height 3

using namespace std;
// -------------------------------------------------------- COSAS DE LA CONSOLA Y SU VISUALIZACION ------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void OcultarCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE; // Cambia la visibilidad del cursor a FALSE
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
// ---------------------------------------------------------------------------PARA MI COMPU DEL WIN 10 q no me deja ponerlo en pantalla completa desde su config :V (dejenlo ahi por ahora)--------------------------------------------------------------------------
void setConsoleFullScreen() {
	// Obtener el manejador de la ventana de la consola
	HWND hwnd = GetConsoleWindow();
	if (hwnd != nullptr) {
		// Ocultar la barra de título y bordes
		SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
		// Obtener el tamaño de la pantalla
		ShowWindow(hwnd, SW_MAXIMIZE);
	}
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y) {
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int textColor, int bgColor) { // ANSI (256 colores)
	cout << "\033[38;5;" << textColor << "m";
	cout << "\033[48;5;" << bgColor << "m";
}

void resetColor() {
	cout << "\033[0m";
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------
void clearRegion(int x1, int y1, int x2, int y2) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord{};

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
// ----------------------------------------------------------------------------------------------------------Estoy pensando en poner solo la pntalla de juego en el medio de la pantalla completa
void SetConsoleRegionColor(int startX, int startY, int widthC, int heightC, int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD coord = { startX, startY };

	// Cambia el color
	setColor(textColor, bgColor);

	// Escribe en la región especificada
	for (int y = startY; y < startY + heightC; ++y) {
		coord.Y = y;
		for (int x = startX; x < startX + widthC; ++x) {
			coord.X = x;
			SetConsoleCursorPosition(hConsole, coord);
			cout << " ";
		}
	}

	// Restaura el color original
	resetColor();
}
//---------------------------------------------------------------------------------------------------------
void drawCircle(int centerX, int centerY, int radius, int offsetX, int offsetY, int color, int back) {
	setColor(color, back);
	double aspectRatio = 0.8; // Ajuste de aspecto para caracteres de consola
	for (int y = -radius + 1; y <= 0; y++) { // Dibuja solo la mitad superior del círculo
		for (int x = -radius; x <= radius-1; x++) { // Dibuja horizontalmente del extremo izquierdo al derecho
			double dx = x * aspectRatio;
			double dy = y;
			if (dx * dx + dy * dy <= radius * radius) { // Ecuación de la circunferencia ajustada para una elipse
				gotoxy(centerX + x + offsetX, centerY + y + offsetY);
				cout << "█";
			}
		}
	}
}
void drawBuilding(int startX, int startY, int widthE, int heightE, int color, int back) {
	setColor(color, back);
	for (int y = startY; y > startY - heightE; --y) {
		for (int x = startX; x < startX + widthE; ++x) {
			gotoxy(x, y);
			cout << "█";
		}
	}
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void OcultarCursor();
void gotoxy(int x, int y);
void showImage(int pos[][width][2]);
void showClearImage(int pos[][width][2]);
void changePos(int position[][width][2], char op);
void mantenerJuego(int position[][width][2]);
void newchoosePosition(char& op);
void caidaSubidaIncremento(char& op);
void cuadroMenu();
void piso();
void presentacion();
void personaje2();
void imprimirTubo(int posXtub, int posYpos, int tamano, int hueco, int tamano2);
void gotoxy(int x, int y);
void setColor(int textColor, int backgroundColor);
void titulo(int x, int y);
void backgroundInicio(int radius, int numCircles, int numBuildings);
//void backgroundGame(int radius, int numCircles, int numBuildings); --- nose :/
//void play(int a, int radio, int numCirculos, int x, int y);
void teclas(int b, int radio, int numCirculos, int x, int y);
void personaje(int c, int radio, int numCirculos, int x, int y);

void aparecerTubos(int position[][4][2], int  posicionX, int posicionY, int& contador);
void pantallaDerrota(char& op);
void validacionTubo(int positionTubo[][4][2], int position[][width][2], int contador, char& op);
void contadorTubos(int positionTubo[][4][2], int position[][width][2], int& contador1, int contador);
void mostrarNum(int k);
int main() {
	setConsoleFullScreen();
	SetConsoleOutputCP(CP_UTF8);
	int position[3][width][2] = { {{5,12},{6,12},{7,12},{8,12},{9,12},{10,12},{11,12},{12,12},{13,12}},
	{{5,13},{6,13},{7,13},{8,13},{9,13},{10,13},{11,13},{12,13},{13,13}},
	{{5,14},{6,14},{7,14},{8,14},{9,14},{10,14},{11,14},{12,14},{13,14}} };

	OcultarCursor();
	presentacion();

	return 0;

}

void presentacion() {
	const int radio = 10;
	const int numCirculos = 6;
	const int numEdificios = 15;
	int op, a = 0, b = 0, c = 0;
	int x = 60, y = 2;
	do {
		setColor(0, 0);  // color negro de fondo y texto a toda la consola (despues cambia cierta region)
		int posXpaja = 25 + 52, posYpaja = 12;
		int position[3][width][2] = {
		{{posXpaja,posYpaja},{posXpaja + 1,posYpaja},{posXpaja + 2,posYpaja},{posXpaja + 3,posYpaja},{posXpaja + 4,posYpaja},{posXpaja + 5,posYpaja},{posXpaja + 6,posYpaja},{posXpaja + 7,posYpaja},{posXpaja + 8,posYpaja}},
		{{posXpaja,posYpaja + 1},{posXpaja + 1,posYpaja + 1},{posXpaja + 2,posYpaja + 1},{posXpaja + 3,posYpaja + 1},{posXpaja + 4,posYpaja + 1},{posXpaja + 5,posYpaja + 1},{posXpaja + 6,posYpaja + 1},{posXpaja + 7,posYpaja + 1},{posXpaja + 8,posYpaja + 1}},
		{{posXpaja,posYpaja + 2},{posXpaja + 1,posYpaja + 2},{posXpaja + 2,posYpaja + 2},{posXpaja + 3,posYpaja + 2},{posXpaja + 4,posYpaja + 2},{posXpaja + 5,posYpaja + 2},{posXpaja + 6,posYpaja + 2},{posXpaja + 7,posYpaja + 2},{posXpaja + 8,posYpaja + 2}}
		};
		system("cls");
		SetConsoleRegionColor(52, 0, 100, 54, 3, 80); // cambia el color del fondo a azul solo de la region (52,0) a (100,54). El 3 y el otro 3 son el color del fondo y texto si es que se pone
		backgroundInicio(radio,numCirculos, numEdificios);
		titulo(x, y);
		piso();

		int Xpaja = 42 + 52, Ypaja = 25;
		gotoxy(Xpaja, Ypaja); setColor(25, 80); cout << "   ▄▄▄"; setColor(15, 80); cout << "▄▄";
		gotoxy(Xpaja, Ypaja + 1); setColor(39, 25); cout << "██▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
		gotoxy(Xpaja, Ypaja + 2);  setColor(39, 80); cout << " ▀█"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
		//---------
		cuadroMenu();
		cin >> op;
		cin.get();
		switch (op) {
		case 1: mantenerJuego(position); break;
		case 2: teclas(b, radio, numCirculos, x, y); break;
		case 3: personaje(c, radio, numCirculos, x, y); break;
		}
	} while (op != 4);
	gotoxy(52 + 40, 19);
	cout << "Gracias por jugar ..." << endl;
	gotoxy(27, 50);
}

void mantenerJuego(int position[][width][2]) {
	char op;
	const int radio = 10;
	const int numCirculos = 6;
	const int numEdificios = 15;
	int posicionX = 88 + 48, posicionY = 41, contador = 0, contador1 = 0;
	int positionTubo[10][4][2];
	setColor(0, 0);
	system("cls");
	SetConsoleRegionColor(52, 0, 100, 54, 3, 80);
	backgroundInicio(radio, numCirculos, numEdificios);
	piso();
	do {

		OcultarCursor();
		showImage(position);
		newchoosePosition(op);
		showClearImage(position); // limpia la region del pajaro despues de su movimiento (tiene como variable a position, basicamente como si fuera la sobra de showImage, solo q lo limpia)
		changePos(position, op);
		aparecerTubos(positionTubo, posicionX, posicionY, contador);
		if (contador != 0)
			validacionTubo(positionTubo, position, contador, op);
	//	contadorTubos(positionTubo, position, contador1, contador); ---- no se immprimen bien el contador
	} while (op != 'q');

}
void contadorTubos(int positionTubo[][4][2], int position[][width][2], int& contador1, int contador) {
	int c = 0;
	for (int i = contador1 + 1; i <= contador; i++) {
		if (positionTubo[i][1][0] < position[2][0][0]) {
			contador1++;
			c++;
			mostrarNum(c);
		}
		if (contador1 == 4)
			contador--;
	}
}
void mostrarNum(int k) {
	int x = 121, y = 10;
	int p = (k % 10 == 0) ? -6 : 0;
	int q = 4, r = 15;
	char bq = (char)219;

	if (k % 10 == 0 || k == 0) {
		// Num 0
		gotoxy(x + p, y);     setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 2); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 3); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << " " << bq << bq << bq << " ";
	}
	else if (k % 10 == 1) {
		// Num 1
		gotoxy(x + p, y);     setColor(q, r); cout << "  " << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << " " << bq << bq << " " << " ";
		gotoxy(x + p, y + 2); setColor(q, r); cout << "  " << bq << " " << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << "  " << bq << " " << " ";
		gotoxy(x + p, y + 4); setColor(q, r); cout << " " << bq << bq << bq;
	}
	else if (k % 10 == 2) {
		// Num 2
		gotoxy(x + p, y);     setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 2); setColor(q, r); cout << "  " << bq << bq << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << " " << bq << "   ";
		gotoxy(x + p, y + 4); setColor(q, r); cout << bq << bq << bq << bq << bq;
	}
	else if (k % 10 == 3) {
		// Num 3
		gotoxy(x + p, y);     setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 2); setColor(q, r); cout << "  " << bq << bq << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << " " << bq << bq << bq << " ";
	}
	else if (k % 10 == 4) {
		// Num 4
		gotoxy(x + p, y);     setColor(q, r); cout << "   " << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << "  " << bq << bq << " ";
		gotoxy(x + p, y + 2); setColor(q, r); cout << " " << bq << " " << bq << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << bq << bq << bq << bq << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << "   " << bq << " ";
	}
	else if (k % 10 == 5) {
		// Num 5
		gotoxy(x + p, y);     setColor(q, r); cout << bq << bq << bq << bq << bq;
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "    ";
		gotoxy(x + p, y + 2); setColor(q, r); cout << bq << bq << bq << bq << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << "    " << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << bq << bq << bq << bq << " ";
	}
	else if (k % 10 == 6) {
		// Num 6
		gotoxy(x + p, y);     setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "    ";
		gotoxy(x + p, y + 2); setColor(q, r); cout << bq << bq << bq << bq << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << " " << bq << bq << bq << " ";
	}
	else if (k % 10 == 7) {
		// Num 7
		gotoxy(x + p, y);     setColor(q, r); cout << bq << bq << bq << bq << bq;
		gotoxy(x + p, y + 1); setColor(q, r); cout << "   " << bq << " ";
		gotoxy(x + p, y + 2); setColor(q, r); cout << "  " << bq << "  ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << " " << bq << "   ";
		gotoxy(x + p, y + 4); setColor(q, r); cout << bq << "    ";
	}
	else if (k % 10 == 8) {
		// Num 8
		gotoxy(x + p, y);     setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 2); setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 3); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << " " << bq << bq << bq << " ";
	}
	else if (k % 10 == 9) {
		// Num 9
		gotoxy(x + p, y);     setColor(q, r); cout << " " << bq << bq << bq << " ";
		gotoxy(x + p, y + 1); setColor(q, r); cout << bq << "   " << bq;
		gotoxy(x + p, y + 2); setColor(q, r); cout << " " << bq << bq << bq << bq;
		gotoxy(x + p, y + 3); setColor(q, r); cout << "    " << bq;
		gotoxy(x + p, y + 4); setColor(q, r); cout << " " << bq << bq << bq << " ";
	}
}

void pantallaDerrota(char& op) {
	cout << "Hola Mundo";
	op = 'q';
}
void validacionTubo(int positionTubo[][4][2], int position[][width][2], int contador, char& op) {
	for (int i = 1; i <= contador; i++) {
		if ((positionTubo[i][0][0] <= position[0][8][0] && positionTubo[i][1][0] >= position[0][0][0]) || (positionTubo[i][0][0] <= position[2][0][0] && positionTubo[i][1][0] >= position[2][0][0])) {
			if (position[0][0][1] > positionTubo[i][0][1] && position[2][0][1] < positionTubo[i][2][1]) {}
			else
				pantallaDerrota(op);
		}
	}
	//Esquinas: position [0-2][0-8][0-1] 
}

void backgroundInicio(int radius, int numCircles, int numBuildings) {

	for (int k = 0; k < numCircles; k++) { // Número de nubes
		int offsetX = k * 16; // De 15 en 15 píxeles
		int offsetY = 1 + rand() % 3; // Varía aleatoriamente la posición altura de las nubes
		drawCircle(radius, radius, radius, 52 + offsetX, 30 + offsetY, 194, 194); // Ajuste de posición de la nube
	}

	// Inicializa la semilla para números aleatorios
	for (int i = 0; i < numBuildings; ++i) {
		int heightE = rand() % 7 + 1; // Altura aleatoria entre 1 y maxHeight
		int widthE = 3 + rand() % 3 + 1; // Ancho aleatorio entre 1 y maxWidth
		int offsetX = i * (4 + 2); // Espacio entre edificios

		drawBuilding(5 + 52 + offsetX, 41, widthE, heightE, 151, 151); // Color gris con fondo negro
	}
}

/*void backgroundGame(int radius, int numCircles, int numBuildings) { // para q en juego el fondo este estatico (tavia inutil)

	for (int k = 0; k < numCircles; k++) { // Número de nubes
		int offsetX = k * 16; // De 15 en 15 píxeles
		int offsetY = 1 + 2; // Varía aleatoriamente la posición altura de las nubes
		drawCircle(radius, radius, radius, 52 + offsetX, 30 + offsetY, 194, 194); // Ajuste de posición de la nube
	}

	// Inicializa la semilla para números aleatorios
	for (int i = 0; i < numBuildings; ++i) {
		int heightE = 5; // Altura aleatoria entre 1 y maxHeight
		int widthE = 3 + (2 + 1); // Ancho aleatorio entre 1 y maxWidth
		int offsetX = i * (4 + 2); // Espacio entre edificios

		drawBuilding(5 + 52 + offsetX, 41, widthE, heightE, 151, 151); // Color gris con fondo negro
	}
}
*/

/*
void play(int a, int radio, int numCirculos, int x, int y) { // inservible
	do {

		system("color 37");
		titulo(x, y);
		gotoxy(27, 12);
		setColor(6, 14);
		// --------------------------------
		cout << "Juega (cualquier numero) hasta q pierdas (1): ";
		cin >> a;
	} while (a != 1);
	gotoxy(27, 14);
	system("pause");
}
*/
void teclas(int b, int radio, int numCirculos, int x, int y) {
	do {
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
void personaje(int c, int radio, int numCirculos, int x, int y) {
	do {
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
const int MAX_WIDTH = 100;

void imprimirTubo(int posXtub, int posYpos, int tamano, int hueco, int tamano2) {
	int cieloColor = 80, verde2 = 40, verde = 40, verdeBrillo = 154, verdeSombra = 34;

	// tubo de abajo
	gotoxy(posXtub - 1, posYpos - tamano);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████";

	gotoxy(posXtub - 1, posYpos - tamano + 1);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████";

	gotoxy(posXtub, posYpos - tamano + 2);
	setColor(verdeSombra, verde); cout << "▀▀▀▀▀▀▀▀▀▀▀▀";

	for (int i = 0; i <= tamano - 3; i++) {
		gotoxy(posXtub, posYpos - i);
		setColor(verde2, cieloColor); cout << "█";
		setColor(verdeBrillo, cieloColor); cout << "██";
		setColor(verde2, cieloColor); cout << "███";
		setColor(verde, cieloColor); cout << "██████";
	}
	// tubo de arriba
	gotoxy(posXtub, posYpos - tamano - hueco - 2);
	setColor(verdeSombra, verde); cout << "▄▄▄▄▄▄▄▄▄▄▄▄";

	gotoxy(posXtub - 1, posYpos - tamano - hueco - 1);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████";

	gotoxy(posXtub - 1, posYpos - tamano - hueco);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████";

	for (int i = 3; i <= tamano2; i++) {
		gotoxy(posXtub, posYpos - tamano - hueco - i);
		setColor(verde2, cieloColor); cout << "█";
		setColor(verdeBrillo, cieloColor); cout << "██";
		setColor(verde2, cieloColor); cout << "█████████";
	}
}
void clearTubo(int posXtub, int posYpos, int tamano, int hueco, int tamano2) {
	clearRegion(posXtub + 12, posYpos - tamano, posXtub + 15, posYpos);
	clearRegion(posXtub + 12, posYpos - tamano - hueco - tamano2, posXtub + 15, posYpos - tamano - hueco);
}

void aparecerTubos(int position[][4][2], int  posicionX, int posicionY, int& contador) {
	int Puntos = 4, XY = 2;

	int tamano = 4 + rand() % 19;
	int hueco = 14 + rand() % 3;
	int tamano2 = 41 - hueco - tamano;
	int distancia = 110;
	if (contador < 100) {
		if (contador == 0) {
			contador++;
			position[contador][0][0] = posicionX;
			position[contador][0][1] = tamano2 + 1;
			position[contador][1][0] = posicionX + 11;
			position[contador][1][1] = tamano2;
			position[contador][2][0] = posicionX;
			position[contador][2][1] = tamano2 + hueco - 1;
			position[contador][3][0] = posicionX + 11;
			position[contador][3][1] = tamano2 + hueco - 1;
		}
		else {
			if (position[contador][1][0] + distancia < 100 + 77) {
				contador++;
				position[contador][0][0] = posicionX;
				position[contador][0][1] = tamano2 + 1;
				position[contador][1][0] = posicionX + 11;
				position[contador][1][1] = tamano2;
				position[contador][2][0] = posicionX;
				position[contador][2][1] = tamano2 + hueco - 1;
				position[contador][3][0] = posicionX + 11;
			}
		}

		if (contador > 0) {
			for (int i = 1; i <= contador; i++) {
				clearTubo(position[i][0][0], posicionY, posicionY - position[i][2][1], position[i][2][1] - position[i][0][1], position[i][0][1]);
				imprimirTubo(position[i][0][0], posicionY, posicionY - position[i][2][1], position[i][2][1] - position[i][0][1], position[i][0][1]);
			}
			for (int i = 1; i <= contador; i++) {
				position[i][0][0] -= 3; // Mueve el tubo de 3 en 3 unidades
				position[i][1][0] -= 3;
				position[i][2][0] -= 3;
				position[i][3][0] -= 3;
			}
		}

		if (contador > 1) {
			if (position[1][0][0] < 77) {
				for (int i = 1; i <= contador; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 2; k++) {
							position[i][j][k] = position[i + 1][j][k];
						}
					}
				}
				contador--;
				clearRegion(52, 0, 52 + 15, 41); // limpia al final la region donde termina el recorrido del tubo
			}
		}
	}
}

void personaje2() {
	int posXper = 5, posYper = 12;
	gotoxy(posXper + 3, posYper); setColor(13, 3); cout << "▀█▄";
	gotoxy(posXper, posYper + 1); setColor(5, 3); cout << "█▄█"; setColor(13, 5); cout << "▄█"; setColor(8, 13); cout << "▄"; setColor(13, 3); cout << "█▄";
	gotoxy(posXper, posYper + 2); setColor(5, 3); cout << "█▀█"; setColor(13, 5); cout << "▀█"; setColor(0, 13); cout << "▀"; setColor(13, 5); cout << "█▀";
}
// ---------------------------------------------
void showImage(int pos[][width][2]) {
	gotoxy(pos[0][0][0], pos[0][0][1]); setColor(25, 80); cout << "   ▄▄▄"; setColor(15, 80); cout << "▄▄";
	gotoxy(pos[1][0][0], pos[1][0][1]); setColor(39, 25); cout << "██▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
	gotoxy(pos[2][0][0], pos[2][0][1]); setColor(39, 80); cout << " ▀█"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
}
void showClearImage(int pos[][width][2]) {// --------------------------------------- limpia la region desde el pos inicial en showImage, esquina superior izquierda del pajaro en showImage, hasta la esquina inferior derecha
	clearRegion(pos[0][0][0], pos[0][0][1], pos[2][0][0] + 10, pos[2][0][1]); // el mas 10 para q selecione hasta la esquina inferior derecha del pajaro desde le punto inicial (esquina superior izquierda)
}


void changePos(int positions[][width][2], char op) {
	int pos = 1, k = 0;
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
		k = -4;
		break;
	case 'x':
		k = -2;
		break;
	case 'y':
		k = -1;
		break;

	case 'f':
		k = 0;
		break;

	case 'g':
		k = 1;
		break;
	case 'h':
		k = 2;
		break;

	}
	int j = 0;
	for (int i = 0; i < height; i++) {
		if (positions[height - 1][j][1] + k > 41) {
			k = 1;
		}
		if (positions[i][j][pos] + k >= 0 && positions[height - 1][j][1] + k <= 41) {
			for (int j = 0; j < width; j++) {
				positions[i][j][pos] += k;
			}
		}
		else {
			break;
		}

	}
}
void caidaSubidaIncremento(char& op) {
	switch (op) {
		//Subida
	case 'w':
		op = 'x';
		break;
	case 'x':
		op = 'y';
		break;
	case 'y':
		op = 'f';
		break;
		//Caida
	case 'f':
		op = 'g';
		break;

	case 'g':
		op = 'h';
		break;
	}

}
void newchoosePosition(char& op) {
	auto start = std::chrono::high_resolution_clock::now();
	int timeout_ms = 50;
	while (true) {
		if (_kbhit()) {

			op = _getch();
			setColor(80, 80);
			if (op == 'a' || op == 'd' || op == 'w' || op == 'q') {
				return;
			}
		}
		setColor(80, 80);
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
		if (duration >= timeout_ms) {
			if (op == 'w' || op == 'x' || op == 'y') {
				caidaSubidaIncremento(op);
			}
			else if (op == 'f' || op == 'g' || op == 'h') {
				caidaSubidaIncremento(op);
			}
			else {
				op = 'f';
			}

			return;
		}
		this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

// --------------------------------------------------------
void cuadroMenu() {
	setColor(222,80);
	int x=77, y=13;
	for (int i = 0; i < 7; ++i) {
		gotoxy(x, y + i);
		for (int j = 0; j < 50; ++j) {
			cout << "█";
		}
		cout << endl;
	}
	gotoxy(x + 3, y + 1); setColor(202, 222); cout << "[1] Jugar" << endl;
	gotoxy(x + 3, y + 2); cout << "[2] Tutorial" << endl;
	gotoxy(x + 3, y + 3); cout << "[3] Opciones" << endl;
	gotoxy(x + 3, y + 4); cout << "[4] Salir" << endl;
	gotoxy(x + 3, y + 5); cout << "Ingrese una opción (1-4) : ";
}
void piso() {
	for (int i = 0; i < 12; ++i) {
		gotoxy(52, 42 + i);
		if (i == 0)
			setColor(148, 80);
		else if (i == 1)
			setColor(208, 215);
		else
			setColor(222, 80);
		for (int j = 0; j < 100; ++j) {
			if (i == 0) {
				if (j % 2 == 0) {
					setColor(154, 80);
					cout << "█";
				}
				else {
					setColor(112, 80);
					cout << "█";
				}
			}
			else if(i == 1)
				cout << "▀";
			else
				cout << "█";
		}
	}
}

void titulo(int x, int y) {
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
	gotoxy(x + 16, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 3); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y + 3); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y + 4); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 16, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 22, y + 5); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█";
	gotoxy(x + 17, y + 6); setColor(15, 3); cout << "██████"; setColor(7, 3); cout << "█";

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
	gotoxy(x + 42, y);     setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 47, y); setColor(15, 3); cout << "██"; setColor(7, 3);
	gotoxy(x + 42, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); cout << "█"; gotoxy(x + 47, y + 1); setColor(15, 3); cout << "██"; setColor(7, 3); 
	gotoxy(x + 43, y + 2); setColor(15, 3); cout <<  "██"; setColor(7, 3); cout << "█"; gotoxy(x + 46, y + 2); setColor(15, 3); cout << "██"; setColor(7, 3); 
	gotoxy(x + 44, y + 3); setColor(15, 3); cout <<   "███"; setColor(7, 3);
	gotoxy(x + 45, y + 4); setColor(15, 3); cout <<    "██"; setColor(7, 3);
	gotoxy(x + 45, y + 5); setColor(15, 3); cout <<    "██"; setColor(7, 3);
	gotoxy(x + 45, y + 6); setColor(15, 3); cout <<    "██"; setColor(7, 3); 

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
	gotoxy(x + 62, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 62, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 62, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 62, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 62, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 61, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "████";

	// R
	gotoxy(x + 67, y);     setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 67, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 72, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 67, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 72, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 67, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 67, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 70, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 67, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 71, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";
	gotoxy(x + 67, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 72, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██";

	// D
	gotoxy(x + 75, y);     setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
	gotoxy(x + 75, y + 1); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 79, y + 1); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 2); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 80, y + 2); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 3); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 80, y + 3); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 4); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 80, y + 4); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 5); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██"; gotoxy(x + 79, y + 5); setColor(7, 3); cout << "██"; setColor(15, 3); cout << "██";
	gotoxy(x + 75, y + 6); setColor(7, 3); cout << "█"; setColor(15, 3); cout << "██████";
}