#include <windows.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <fstream>
#define width 9
#define height 3

using namespace std;
// -------------------------------------------------------- COSAS DE LA CONSOLA Y SU VISUALIZACION ------------------------------------------------------------------------
void reproducirMusica(const string& rutaCancion, sf::Music& music) {
	do {
		if (!music.openFromFile(rutaCancion)) {
			return; /*error de carga*/
		}
		music.play();
		while (music.getStatus() == sf::Music::Playing) {
			/*mantiene la canción en ejecución*/
		}
	} while (music.getStatus() == sf::Music::Stopped);
	/*una vez que termine la canción va a repetir*/
}

sf::SoundBuffer buffer;
sf::Sound sound;

sf::SoundBuffer buffer2;
sf::Sound sound2;

void saltoSound() {
	if (!buffer.loadFromFile("salto.ogg")) {
		cerr << "Error al cargar el archivo de sonido" << endl;
		return;
	}
	sound.setBuffer(buffer);
}
void seleccionarSound() {
	if (!buffer2.loadFromFile("ingame.ogg")) {
		cerr << "Error al cargar el archivo de sonido" << endl;
		return;
	}
	sound2.setBuffer(buffer2);
}
void menuSound() {
	if (!buffer2.loadFromFile("menu.ogg")) {
		cerr << "Error al cargar el archivo de sonido" << endl;
		return;
	}
	sound2.setBuffer(buffer2);
}
void golpeSound() {
	if (!buffer.loadFromFile("golpe.ogg")) {
		cerr << "Error al cargar el archivo de sonido" << endl;
		return;
	}
	sound.setBuffer(buffer);
}
void tuboSound() {
	if (!buffer2.loadFromFile("tubo.ogg")) {
		cerr << "Error al cargar el archivo de sonido" << endl;
		return;
	}
	sound2.setBuffer(buffer2);
}
void flechaSound() {
	if (!buffer.loadFromFile("flecha.ogg")) {
		cerr << "Error al cargar el archivo de sonido" << endl;
		return;
	}
	sound.setBuffer(buffer);
}
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
	COORD coorden{};
	coorden.X = x;
	coorden.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coorden);
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
	setColor(80, 80);
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

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void pantallaGameOver() {
	int posXover = 52 + 24, posYover = 5;
	gotoxy(posXover, posYover);
	setColor(30, 80); cout << "▄▄▄▄▄▄▄ ▄▄▄▄ ▄▄▄ ▄▄▄▄▄▄▄▄▄▄"; gotoxy(posXover + 28, posYover); cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ";
	gotoxy(posXover, posYover + 1);
	setColor(30, 15); cout << "█ ▄▄▄▄██▀▄ ██▄ ▀█▀ ▄█▄ ▄▄ █"; gotoxy(posXover + 28, posYover + 1); cout << "█ ▄▄ █▄ █ ▄█▄ ▄▄ █▄ ▄▄▀█";
	gotoxy(posXover, posYover + 2);
	setColor(23, 15); cout << "█ ██▄ ██ ▀ █"; setColor(23, 80); cout << "▄"; setColor(23, 15); cout << "█ █▄█ █"; setColor(23, 80); cout << "▄"; setColor(23, 15); cout << "█ ▄█▀█"; gotoxy(posXover + 28, posYover + 2); cout << "█ ██ ██▄▀▄███ ▄█▀██ ▄ ▄█";
	gotoxy(posXover, posYover + 3);
	setColor(23, 15); cout << "█▄▄▄▄▄█▄▄█▄▄█▄▄▄█▄▄▄█▄▄▄▄▄█"; gotoxy(posXover + 28, posYover + 3); cout << "█▄▄▄▄█"; gotoxy(posXover + 35, posYover + 3); cout << "█▄█"; gotoxy(posXover + 39, posYover + 3); cout << "█▄▄▄▄▄█▄▄█▄▄█";
}
void cuadroScreen(int posXover, int posYover, int color) {
	setColor(15, color);
	gotoxy(posXover, posYover);
	cout << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";
	gotoxy(posXover, posYover + 1);
	cout << "█                     █";
	gotoxy(posXover, posYover + 2);
	cout << "█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";
}
void flecha(int &posXflecha, int &posYflecha) {
	setColor(15, 80);
	gotoxy(posXflecha, posYflecha + 0); setColor(195, 80); cout << "█▄ ";
	gotoxy(posXflecha, posYflecha + 1); setColor(195, 15); cout << "▀▀▀";
	gotoxy(posXflecha, posYflecha + 2); setColor(15, 80); cout << "█▀ ";
	gotoxy(posXflecha + 30, posYflecha + 0); setColor(195, 80); cout << " ▄█";
	gotoxy(posXflecha + 30, posYflecha + 1); setColor(195, 15); cout << "▀▀▀";
	gotoxy(posXflecha + 30, posYflecha + 2); setColor(15, 80); cout << " ▀█";
}
void puntajeScreen(int posXover, int posYover) {
	gotoxy(posXover, posYover);
	setColor(172,80); cout << " ▄"; setColor(172, 229); cout << "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"; setColor(172,80); cout << "▄";
	setColor(172, 222);
	gotoxy(posXover, posYover + 1);
	cout << "█▀                         ▀█";
	gotoxy(posXover, posYover + 2);
	cout << "█                           █";
	gotoxy(posXover, posYover + 3);
	cout << "█                           █";
	gotoxy(posXover, posYover + 4);
	cout << "█                           █";
	gotoxy(posXover, posYover + 5);
	cout << "█                           █";
	gotoxy(posXover, posYover + 6);
	cout << "█                           █";
	gotoxy(posXover, posYover + 7);
	cout << "█                           █";
	gotoxy(posXover, posYover + 8);
	cout << "█                           █";
	gotoxy(posXover, posYover + 9);
	cout << "█                           █";
	gotoxy(posXover, posYover + 10);
	cout << "█                           █";
	gotoxy(posXover, posYover + 11);
	cout << "█                           █";
	gotoxy(posXover, posYover + 12);
	cout << "█                           █";
	gotoxy(posXover, posYover + 13);
	cout << "█▄                         ▄█";
	gotoxy(posXover, posYover + 14);
	setColor(172, 80); cout << " ▀"; setColor(172, 215); cout << "█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"; setColor(172, 80); cout << "▀";
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void OcultarCursor();
void gotoxy(int x, int y);
void showImage(int pos[][width][2], char opMov);
void showClearImage(int pos[][width][2]);
void changePos(int position[][width][2], char op);
void mantenerJuego(int position[][width][2]);
void newchoosePosition(char& op);
void caidaSubidaIncremento(char& op);
void piso();
void presentacion();
void personaje2();
void imprimirTubo(int posXtub, int posYpos, int tamano, int hueco, int tamano2);
void gotoxy(int x, int y);
void setColor(int textColor, int backgroundColor);
void titulo(int x, int y);
void background();
void seleccionarMenu(int& op, char &selec, int &xf, int &yf);
void seleccionarPausa(int& operador);
// 1 vs 1
void showPuntaje(int k, int x, int y);
int mayorPunto();
void puntos(int c);
void vidaBoss(int rest, int dmg);
void imprimirDigito(int digito, int x, int y);
void limpiarPantalla(int x1, int y1, int x2, int y2);
void mantenerBoss(int position[][width][2]);
void mantener1VS1(int jugador1[][width][2], int jugador2[][width][2]);
void showImage2(int pos[][width][2], int pos2[][width][2]);
void changePos2(int positions[][width][2], char op);
void newchoosePosition2(char& op, char& po);
void boat(int posXboss, int posYboss);
void canon(int posXboss, int posYboss);
void balas(int positionBala[][2], int contBala);
void movBoss(int& contMov, int posXboss, int posYboss);
void showImageMenu(int &pajMov, int Xpaja, int Ypaja);
void movPiso(int& pisoMov);
void subeBaja(int& contador, int& posYboss);
void pantallaDerrotaBoss(char& op, int& pisoMov, int position[3][width][2], int& posXboss, int& posYboss, int& contMov, int& contSube, int& contBala, int positionBala[][2]);
void validacionBalas(int positionBala[][2], int position[][width][2], int contador, char& op, int& pisoMov, int& posXboss, int& posYboss, int& contMov, int& contSube, int& contBala);
void posicionBala(int contSube, int positionBala[][2], int& contBala, int posYboss, int posXboss);
bool validacionTubo1vs1(char& op, int& pisoMov, int& posicionX, int& posicionY, int& contador, int& contador1, int positionTubo[][4][2], int position[3][width][2], int& c);

void aparecerTubos(int position[][4][2], int  posicionX, int posicionY, int& contador);
void pantallaDerrota(char& op, int& pisoMov, int& posicionX, int& posicionY, int& contador, int& contador1, int position[3][width][2], int &c);
void validacionTubo(char& op, int& pisoMov, int& posicionX, int& posicionY, int& contador, int& contador1, int positionTubo[][4][2], int position[3][width][2], int &c);
void contadorTubos(int positionTubo[][4][2], int position[][width][2], int& contador1, int contador, int& c, bool& x);
// void mostrarNum(int k);
int main() {
	string rutaCancion = "profeSong.ogg";
	sf::Music profe;
	sf::SoundBuffer buffer;
	//creamos un hilo
	thread hiloMusica(reproducirMusica, rutaCancion, std::ref(profe));
	
	setConsoleFullScreen();
	SetConsoleOutputCP(CP_UTF8);
	OcultarCursor();

	presentacion();

	// cierra la consola
	HWND hWnd = GetConsoleWindow();
	PostMessage(hWnd, WM_CLOSE, 0, 0);

	hiloMusica.join();
	return 0;
}

void presentacion() {
	int op = 1;
	char selec;
	int x = 60, y = 2, xf = 52 + 33, yf = 10;
	int pajMov = 1, pisoMov = 0;
	int Xpaja = 44 + 52, Ypaja = 26, cMovXpaja = 1, verificarYpaja = 26;
	do {
		setColor(0, 0);  // color negro de fondo y texto a toda la consola (despues cambia cierta region)
		int posXpaja = 25 + 52, posYpaja = 15;
		int position[3][width][2] = {
		{{posXpaja,posYpaja},{posXpaja + 1,posYpaja},{posXpaja + 2,posYpaja},{posXpaja + 3,posYpaja},{posXpaja + 4,posYpaja},{posXpaja + 5,posYpaja},{posXpaja + 6,posYpaja},{posXpaja + 7,posYpaja},{posXpaja + 8,posYpaja}},
		{{posXpaja,posYpaja + 1},{posXpaja + 1,posYpaja + 1},{posXpaja + 2,posYpaja + 1},{posXpaja + 3,posYpaja + 1},{posXpaja + 4,posYpaja + 1},{posXpaja + 5,posYpaja + 1},{posXpaja + 6,posYpaja + 1},{posXpaja + 7,posYpaja + 1},{posXpaja + 8,posYpaja + 1}},
		{{posXpaja,posYpaja + 2},{posXpaja + 1,posYpaja + 2},{posXpaja + 2,posYpaja + 2},{posXpaja + 3,posYpaja + 2},{posXpaja + 4,posYpaja + 2},{posXpaja + 5,posYpaja + 2},{posXpaja + 6,posYpaja + 2},{posXpaja + 7,posYpaja + 2},{posXpaja + 8,posYpaja + 2}}
		};
		int posXpaja2 = 30 + 52, posYpaja2 = 15;
		int position2[3][width][2] = { // jugador 2
		{{posXpaja2,posYpaja2},{posXpaja2 + 1,posYpaja2},{posXpaja2 + 2,posYpaja2},{posXpaja2 + 3,posYpaja2},{posXpaja2 + 4,posYpaja2},{posXpaja2 + 5,posYpaja2},{posXpaja2 + 6,posYpaja2},{posXpaja2 + 7,posYpaja2},{posXpaja2 + 8,posYpaja2}},
		{{posXpaja2,posYpaja2 + 1},{posXpaja2 + 1,posYpaja2 + 1},{posXpaja2 + 2,posYpaja2 + 1},{posXpaja2 + 3,posYpaja2 + 1},{posXpaja2 + 4,posYpaja2 + 1},{posXpaja2 + 5,posYpaja2 + 1},{posXpaja2 + 6,posYpaja2 + 1},{posXpaja2 + 7,posYpaja2 + 1},{posXpaja2 + 8,posYpaja2 + 1}},
		{{posXpaja2,posYpaja2 + 2},{posXpaja2 + 1,posYpaja2 + 2},{posXpaja2 + 2,posYpaja2 + 2},{posXpaja2 + 3,posYpaja2 + 2},{posXpaja2 + 4,posYpaja2 + 2},{posXpaja2 + 5,posYpaja2 + 2},{posXpaja2 + 6,posYpaja2 + 2},{posXpaja2 + 7,posYpaja2 + 2},{posXpaja2 + 8,posYpaja2 + 2}}
		};
		system("cls");
		SetConsoleRegionColor(52, 0, 100, 54, 3, 80); // cambia el color del fondo a azul solo de la region (52,0) a (100,54). El 3 y el otro 3 son el color del fondo y texto si es que se pone
		background();
		titulo(x, y);
		piso();
		// animacion del menu del pajaro
		bool animating = true;
		setColor(80, 80);
		// para q capte una tecla (cualquiera) presionada solamente, sino el kbith nunca mostrara el menu :v
		keybd_event('A', 0, 0, 0); // Presiona la tecla 'A'
		keybd_event('A', 0, KEYEVENTF_KEYUP, 0); // Suelta la tecla 'A'
		while (animating) {
			if (_kbhit()) {
				seleccionarMenu(op,selec,xf,yf);
				// Convertir el carácter leído a entero
				if (selec == 13 || selec == 32) {
					animating = false; // Salir del bucle de animación si se presiona una tecla válida
				}
			}
			// Actualizar la imagen del menú
			if (cMovXpaja == 1)
				Ypaja++;
			else if (cMovXpaja == 10)
				Ypaja++;
			else if (cMovXpaja == 20)
				Ypaja++;
			else if (cMovXpaja == 40)
				Ypaja--;
			else if (cMovXpaja == 45)
				Ypaja--;
			else if (cMovXpaja == 50)
				Ypaja--;
			else if (cMovXpaja == 60)
				Ypaja--;
			else if (cMovXpaja == 90)
				Ypaja++;
			else if (cMovXpaja == 105)
				cMovXpaja = 0;

			if (Ypaja != verificarYpaja)
				clearRegion(52 + 44, 25, 52 + 54, 31);
			verificarYpaja = Ypaja;
			showImageMenu(pajMov, Xpaja, Ypaja);
			movPiso(pisoMov);

			Sleep(50); // Ajustar el tiempo de pausa para la animación
			cMovXpaja++;
		}

		static bool soundLoaded = false;
		if (!soundLoaded) {
			seleccionarSound();
			soundLoaded = true;
		}

		switch (op) {
		case 1:
			seleccionarSound();
			sound2.play();
			mantenerJuego(position);
			break;
		case 2:
			seleccionarSound();
			sound2.play();
			mantener1VS1(position, position2);
			break;
		case 3:
			seleccionarSound();
			sound2.play();
			mantenerBoss(position);
			break;
		}
	} while (op != 4);
}

void mantenerJuego(int position[][width][2]) {
	char op = 0;
	bool x = true;
	int pisoMov = 1;
	int posicionX = 88 + 48, posicionY = 41, contador = 0, contador1 = 0;
	int positionTubo[10][4][2], c = 0;
	setColor(0, 0);
	system("cls");
	SetConsoleRegionColor(52, 0, 100, 54, 3, 80);
	piso();
	background();
	do {
		movPiso(pisoMov);
		showImage(position, op);
		newchoosePosition(op);
		showClearImage(position); // limpia la region del pajaro despues de su movimiento (tiene como variable a position, basicamente como si fuera la sobra de showImage, solo q lo limpia)
		changePos(position, op);
		background();
		aparecerTubos(positionTubo, posicionX, posicionY, contador);
		if (contador != 0)
			validacionTubo(op, pisoMov, posicionX, posicionY, contador, contador1, positionTubo, position, c);
		contadorTubos(positionTubo, position, contador1, contador, c, x);
	} while (op != 'q');
}

//falta poner la anim de los pajaros para el 1 vs 1
void mantener1VS1(int jugador1[][width][2], int jugador2[][width][2]) {
	char op, po;
	int derrota1, derrota2;
	int pisoMov = 0;
	int posicionX = 88 + 48, posicionY = 41, contador = 0, contador1 = 0;
	int positionTubo[10][4][2], c = 0;
	setColor(0, 0);
	system("cls");
	SetConsoleRegionColor(52, 0, 100, 54, 3, 80);
	background();
	piso();
	do {
		OcultarCursor();
		showImage2(jugador1, jugador2);
		newchoosePosition2(op, po);
		showClearImage(jugador1);
		showClearImage(jugador2);
		changePos(jugador1, op);
		movPiso(pisoMov);
		changePos2(jugador2, po);
		background();
		aparecerTubos(positionTubo, posicionX, posicionY, contador);
		if (contador != 0) {
			derrota1 = validacionTubo1vs1(op, pisoMov, posicionX, posicionY, contador, contador1, positionTubo, jugador1, c);
			derrota2 = validacionTubo1vs1(po, pisoMov, posicionX, posicionY, contador, contador1, positionTubo, jugador2, c);
			if (derrota1 == 0) {
				pantallaDerrota(op, pisoMov, posicionX, posicionY, contador, contador1, jugador1, c);
				break;
			}
			else if (derrota2 == 0) {
				pantallaDerrota(po, pisoMov, posicionX, posicionY, contador, contador1, jugador2, c);
				break;
			}
		}
	} while (po != 'q' || op != 'q');
}


void mantenerBoss(int position[][width][2]) {
	char op = 0;
	int pisoMov = 0;
	int posXboss = 52 + 70, posYboss = 12;
	int contMov = 0, contSube = 0, contBala = 0;
	int positionBala[100][2]; positionBala[0][0] = posXboss;
	int muroBala[10][2];
	setColor(0, 0);
	system("cls");
	SetConsoleRegionColor(52, 0, 100, 54, 3, 80);
	background();
	piso();
	do {
		if (contSube % 3 == 0) {
			positionBala[contBala][0] = posXboss - 7;
			positionBala[contBala][1] = posYboss + 13;
			contBala++;
		}
		showImage(position, op);
		newchoosePosition(op);
		showClearImage(position);
		changePos(position, op);
		movPiso(pisoMov);
		background();
		movBoss(contMov, posXboss, posYboss);
		boat(posXboss, posYboss);
		canon(posXboss, posYboss);
		if (contSube != 31)
			subeBaja(contSube, posYboss);
		balas(positionBala, contBala);
		validacionBalas(positionBala, position, contBala, op,pisoMov, posXboss, posYboss, contMov, contSube, contBala);
	} while (op != 'q');

}

void subeBaja(int& contador, int& posYboss) {

	if (contador <= 10)
		posYboss--;
	else if (contador <= 25)
		posYboss++;
	else if (contador <= 30)
		posYboss--;
	else if (contador == 31)
		contador = 0;
	contador++;
}

void boat(int posXboss, int posYboss) {
	posYboss = posYboss + 10 + 1;
	clearRegion(posXboss, posYboss, posXboss + 29, posYboss + 10);
	gotoxy(posXboss + 5, posYboss); setColor(88, 52); cout << " ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀         ";
	gotoxy(posXboss + 6, posYboss + 1); setColor(88, 52); cout << " ███████████████████████";
	gotoxy(posXboss + 9, posYboss + 2); setColor(88, 52); cout << " ███████▀▀▀▀▀▀▀▀▀▀▀▀▀";
	gotoxy(posXboss + 9, posYboss + 3); setColor(88, 52); cout << " ████████████████▄▄▄▄";
	gotoxy(posXboss + 9, posYboss + 4); setColor(88, 52); cout << " ████████████████████";
	gotoxy(posXboss + 9, posYboss + 5); setColor(88, 52); cout << " ██████▀▀▀▀▀▀▀▀▀▀▀▀▀▀";
	gotoxy(posXboss + 10, posYboss + 6); setColor(88, 52); cout << " ███▀▀ ▀▀███▀▀  ▀▀▀▀";
	gotoxy(posXboss + 11, posYboss + 7); setColor(88, 52); cout << " ██████████████████";
	gotoxy(posXboss + 15, posYboss + 8); setColor(88, 52); cout << " ██████████████";
	gotoxy(posXboss + 20, posYboss + 9); setColor(88, 52); cout << "▀▀▀▀▀▀▀▀▀▀";
}
void canon(int posXboss, int posYboss) {
	posYboss += 10 + 1 + 2;
	clearRegion(posXboss, posYboss, posXboss + 8, posYboss + 4);
	gotoxy(posXboss, posYboss + 0); setColor(236, 80); cout << "██  ███▄ ";
	gotoxy(posXboss, posYboss + 1); setColor(236, 235); cout << "█ ▀█▀   █";
	gotoxy(posXboss, posYboss + 2); setColor(0, 234); cout << "█  █    █";
	gotoxy(posXboss, posYboss + 3); setColor(0, 234); cout << "█ ▄█▄   █";
	gotoxy(posXboss, posYboss + 4); setColor(0, 80); cout << "██  ███▀";
}
void posicionBala(int contSube, int positionBala[][2], int& contBala, int posYboss, int posXboss) { // es necesario?
	if (contSube % 3 == 0) {
		positionBala[contBala][0] = posXboss - 7; positionBala[contBala][1] = posYboss + 13;
		contBala++;
	}
}
void balas(int positionBala[][2], int contBala) {
	for (int i = 0; i < contBala; i++) {
		clearRegion(positionBala[i][0], positionBala[i][1], positionBala[i][0] + 7, positionBala[i][1] + 2);
		gotoxy(positionBala[i][0], positionBala[i][1]); setColor(124, 80); cout << "▄███▄     ";
		gotoxy(positionBala[i][0], positionBala[i][1] + 1); setColor(88, 80); cout << "█████     ";
		gotoxy(positionBala[i][0], positionBala[i][1] + 2); setColor(52, 80); cout << "▀███▀     ";
	}
	for (int i = 0; i < contBala; i++) {
		positionBala[i][0] -= 5;
	}
	if (positionBala[0][0] <= 50) {
		for (int i = 0; i < contBala; i++) {
			positionBala[i][0] = positionBala[i + 1][0];
			positionBala[i][1] = positionBala[i + 1][1];
		}
		clearRegion(52, 10, 52 + 15, 30);
		contBala--;
	}
}

void validacionBalas(int positionBala[][2], int position[][width][2], int contador, char& op, int& pisoMov, int& posXboss, int& posYboss, int& contMov, int& contSube, int& contBala) {
	for (int i = 1; i <= contador; i++) {
		if ((positionBala[i][0] <= position[0][8][0] && positionBala[i][0] >= position[0][0][0]) || (positionBala[i][0] + 5 <= position[2][0][0] && positionBala[i][0] + 5 >= position[2][0][0])) {
			if ((position[0][0][1] <= positionBala[i][1] && position[2][0][1] >= positionBala[i][1]) || (position[0][0][1] <= positionBala[i][1] + 3 && position[2][0][1] >= positionBala[i][1] + 3)) {
				pantallaDerrotaBoss(op, pisoMov, position, posXboss, posYboss, contMov, contSube, contBala, positionBala);
			}
		}
	}
	//Esquinas: position [0-2][0-8][0-1] 
}

void movBoss(int& contMov, int posXboss, int posYboss) {
	if (contMov <= 5) {
		clearRegion(posXboss, posYboss - 1, posXboss + 29, posYboss + 9);
		//frame 1
		gotoxy(posXboss, posYboss + 0); setColor(221, 80); cout << "                 ▄▄           ";
		gotoxy(posXboss, posYboss + 1); setColor(221, 80); cout << "               ▐"; setColor(221, 0); cout << "▀▀▀▀"; setColor(221, 80); cout << "█▄"; setColor(80, 80); cout << "█       ";
		gotoxy(posXboss, posYboss + 2); setColor(221, 80); cout << "               ▐"; setColor(0, 15); cout << "█▀▀██"; setColor(221, 0); cout << "▀"; setColor(208, 80); cout << "▄▄"; setColor(0, 80); cout << "▄▄   ";
		gotoxy(posXboss, posYboss + 3); setColor(221, 80); cout << "              ▄█"; setColor(208, 0); cout << "       ▀█▄"; setColor(208, 80); cout << "▄  ";
		gotoxy(posXboss, posYboss + 4); setColor(95, 80); cout << "            ▄▄"; setColor(208, 0); cout << "█▀ "; setColor(89, 0); cout << "▄█████▄  "; setColor(130, 0); cout << "▀▀"; setColor(130, 80); cout << "▄";
		gotoxy(posXboss, posYboss + 5); setColor(95, 80); cout << "           █ ▐ "; setColor(208, 80); cout << "▀▀"; setColor(0, 89); cout << "▄"; setColor(229, 89); cout << "▄"; setColor(89, 221); cout << "▀"; setColor(0, 89); cout << "▄"; setColor(229, 89); cout << "▄"; setColor(89, 208); cout << "▀"; setColor(89, 130); cout << "▀"; setColor(130, 0); cout << "▄▄▄"; setColor(130, 80); cout << "▀▀";
		gotoxy(posXboss, posYboss + 6); setColor(95, 80); cout << "           ▀█▄▄  "; setColor(0, 221); cout << "▀▀ ▀▀"; setColor(208, 208); cout << "█"; setColor(130, 52); cout << "▀"; setColor(0, 80); cout << "█"; setColor(95, 80); cout << "▀██▄";
		gotoxy(posXboss, posYboss + 7); setColor(95, 80); cout << "            ███▄█▀"; setColor(52, 80); cout << "▀"; setColor(52, 52); cout << "██"; setColor(52, 228); cout << "▀"; setColor(52, 52); cout << "██"; setColor(0, 80); cout << "█▌"; setColor(95, 80); cout << "▄██▌";
		gotoxy(posXboss, posYboss + 8); setColor(95, 80); cout << "             ▀▀▀ "; setColor(95, 80); cout << "██▀"; setColor(52, 80); cout << "▀▀▀"; setColor(95, 80); cout << "██ ▀██▌";
		gotoxy(posXboss, posYboss + 9); setColor(124, 88); cout << "█▀▀▀▀▀▀▀█"; setColor(173, 80); cout << "       ██"; setColor(173, 95); cout << "▄"; setColor(95, 80); cout << "     ██";
		gotoxy(posXboss, posYboss + 10); setColor(52, 80); cout << "▀▀▀▀▀█"; setColor(124, 88); cout << "  ▀▀▀▀▀"; setColor(52, 88); cout << "▀▀▀▀▀▀▀▀█"; setColor(80, 80); cout << "██"; setColor(173, 95); cout << "▄"; setColor(173, 80); cout << "██   ";
	}
	else {
		clearRegion(posXboss + 10, posYboss - 1, posXboss + 29, posYboss + 9);
		//frame 2
		gotoxy(posXboss, posYboss + 0); setColor(221, 80); cout << "                ▄██▄▄         ";
		gotoxy(posXboss, posYboss + 1); setColor(221, 80); cout << "               ▐"; setColor(0, 15); cout << "█▀▀█"; setColor(221, 0); cout << "▀█"; setColor(80, 80); cout << "█       ";
		gotoxy(posXboss, posYboss + 2); setColor(221, 80); cout << "               ▐"; setColor(0, 15); cout << "█▄▄███"; setColor(221, 0); cout << "▀"; setColor(208, 0); cout << "█▄ "; setColor(80, 80); cout << "█   ";
		gotoxy(posXboss, posYboss + 3); setColor(221, 80); cout << "              ▐█"; setColor(0, 80); cout << "██"; setColor(89, 0); cout << "▄▄▄▄▄ "; setColor(208, 0); cout << "▀▀█"; setColor(208, 80); cout << "▄  ";
		gotoxy(posXboss, posYboss + 4); setColor(221, 80); cout << "              ▐"; setColor(208, 0); cout << "▄▄"; setColor(89, 52); cout << "███████"; setColor(130, 0); cout << "   ▄█"; setColor(80, 80); cout << "█";
		gotoxy(posXboss, posYboss + 5); setColor(95, 80); cout << "          █▀"; setColor(95, 80); cout << "▌    "; setColor(0, 229); cout << "█▄"; setColor(221, 221); cout << " "; setColor(0, 229); cout << "█▄"; setColor(208, 221); cout << "█"; setColor(130, 208); cout << "█"; setColor(130, 80); cout << "▀▀▀   ";
		gotoxy(posXboss, posYboss + 6); setColor(95, 80); cout << "          █▄▄▄   "; setColor(221, 95); cout << "▀"; setColor(52, 221); cout << "▄▄▄▄"; setColor(52, 208); cout << "▄"; setColor(52, 221); cout << "█"; setColor(0, 80); cout << "█"; setColor(95, 80); cout << "██▄  ";
		gotoxy(posXboss, posYboss + 7); setColor(95, 80); cout << "            "; setColor(95, 95); cout << "▄██"; setColor(95, 80); cout << "▄"; setColor(95, 80); cout << "█▀ "; setColor(0, 80); cout << "█"; setColor(52, 180); cout << "▄"; setColor(52, 228); cout << "▀"; setColor(52, 180); cout << "▄▄"; setColor(0, 80); cout << "█"; setColor(0, 80); cout << "▌"; setColor(95, 80); cout << "▀"; setColor(95, 80); cout << "██▌";
		gotoxy(posXboss, posYboss + 8); setColor(95, 80); cout << "             ▀▀▀ "; setColor(95, 80); cout << "██▀"; setColor(52, 80); cout << "▀▀▀"; setColor(95, 80); cout << "██ ▐"; setColor(95, 80); cout << "██▌";
		gotoxy(posXboss, posYboss + 9); setColor(124, 88); cout << "█▀▀▀▀▀▀▀█"; setColor(173, 80); cout << "       ██"; setColor(173, 95); cout << "▄"; setColor(95, 80); cout << "     ██ ▀▀ ";
		gotoxy(posXboss, posYboss + 10); setColor(52, 80); cout << "▀▀▀▀▀█"; setColor(124, 88); cout << "  ▀▀▀▀▀"; setColor(52, 88); cout << "▀▀▀▀▀▀▀▀█"; setColor(80, 80); cout << "██"; setColor(173, 95); cout << "▄"; setColor(173, 80); cout << "██   ";
	}
	contMov++;
	if (contMov == 10)
		contMov = 0;
}

void contadorTubos(int positionTubo[][4][2], int position[][width][2], int& contador1, int contador, int& c, bool& x) {
	if (positionTubo[1][1][0] > position[2][0][0] + 1)
		x = true;
	if (positionTubo[1][1][0] <= position[2][0][0] + 1 && x) {
		static bool soundLoaded = false;
		if (!soundLoaded) {
			tuboSound();
			soundLoaded = true;
		}
		x = false;
		tuboSound();
		sound2.play();
		c++;
		SetConsoleRegionColor(90, 46, 21, 4, 222, 222);
		showPuntaje(c, 99, 46);
	}
}
void pantallaDerrotaBoss(char& op, int& pisoMov, int position[3][width][2],int& posXboss,int& posYboss,int& contMov,int& contSube,int& contBala, int positionBala[][2]) {
	int operador = 1;
	do {
		pantallaGameOver(); // "game over"

		static bool soundLoaded = false;

		if (!soundLoaded) {
			golpeSound();
			soundLoaded = true;
		}
		golpeSound();
		sound.play();

		seleccionarPausa(operador);

		// uno por uno q pereza :v
		int posXpaja = 25 + 52, posYpaja = 15;
		position[0][0][0] = posXpaja + 0; position[0][0][1] = posYpaja + 0;
		position[0][1][0] = posXpaja + 1; position[0][1][1] = posYpaja + 0;
		position[0][2][0] = posXpaja + 2; position[0][2][1] = posYpaja + 0;
		position[0][3][0] = posXpaja + 3; position[0][3][1] = posYpaja + 0;
		position[0][4][0] = posXpaja + 4; position[0][4][1] = posYpaja + 0;
		position[0][5][0] = posXpaja + 5; position[0][5][1] = posYpaja + 0;
		position[0][6][0] = posXpaja + 6; position[0][6][1] = posYpaja + 0;
		position[0][7][0] = posXpaja + 7; position[0][7][1] = posYpaja + 0;
		position[0][8][0] = posXpaja + 8; position[0][8][1] = posYpaja + 0;

		position[1][0][0] = posXpaja + 0; position[1][0][1] = posYpaja + 1;
		position[1][1][0] = posXpaja + 1; position[1][1][1] = posYpaja + 1;
		position[1][2][0] = posXpaja + 2; position[1][2][1] = posYpaja + 1;
		position[1][3][0] = posXpaja + 3; position[1][3][1] = posYpaja + 1;
		position[1][4][0] = posXpaja + 4; position[1][4][1] = posYpaja + 1;
		position[1][5][0] = posXpaja + 5; position[1][5][1] = posYpaja + 1;
		position[1][6][0] = posXpaja + 6; position[1][6][1] = posYpaja + 1;
		position[1][7][0] = posXpaja + 7; position[1][7][1] = posYpaja + 1;
		position[1][8][0] = posXpaja + 8; position[1][8][1] = posYpaja + 1;

		position[2][0][0] = posXpaja + 0; position[2][0][1] = posYpaja + 2;
		position[2][1][0] = posXpaja + 1; position[2][1][1] = posYpaja + 2;
		position[2][2][0] = posXpaja + 2; position[2][2][1] = posYpaja + 2;
		position[2][3][0] = posXpaja + 3; position[2][3][1] = posYpaja + 2;
		position[2][4][0] = posXpaja + 4; position[2][4][1] = posYpaja + 2;
		position[2][5][0] = posXpaja + 5; position[2][5][1] = posYpaja + 2;
		position[2][6][0] = posXpaja + 6; position[2][6][1] = posYpaja + 2;
		position[2][7][0] = posXpaja + 7; position[2][7][1] = posYpaja + 2;
		position[2][8][0] = posXpaja + 8; position[2][8][1] = posYpaja + 2;

		if (!soundLoaded) {
			menuSound();
			soundLoaded = true;
		}

		if (!soundLoaded) {
			seleccionarSound();
			soundLoaded = true;
		}
		switch (operador) {
		case 1:
			seleccionarSound();
			sound2.play();
			op = 'a';
			posXboss = 52 + 70, posYboss = 12;
			contMov = 0, contSube = 0, contBala = 0;

			for (int i = 0; i < 100; ++i) { // para q se reinicien las posiciones
				positionBala[i][0] = 0;
				positionBala[i][1] = 0; 
			}
			positionBala[0][0] = posXboss;

			pisoMov = 1;
			setColor(0, 0);
			system("cls");
			SetConsoleRegionColor(52, 0, 100, 54, 3, 80);
			background();
			piso();
			break; // op random q no sea q
		case 2:
			menuSound();
			sound2.play();
			op = 'q';
			break;
		}
	} while (op != 'q' && op != 'a');
}
void pantallaDerrota(char& op, int &pisoMov, int &posicionX, int &posicionY, int &contador, int &contador1, int position[3][width][2], int &c) {
	int operador = 1;
	do {
		pantallaGameOver(); // "game over"
		puntajeScreen(52 + 35, 12);
		puntos(c);

		static bool soundLoaded = false;

		if (!soundLoaded) {
			golpeSound();
			soundLoaded = true;
		}
		golpeSound();
		sound.play();

		seleccionarPausa(operador);

		// uno por uno q pereza :v
		int posXpaja = 25 + 52, posYpaja = 15;
		position[0][0][0] = posXpaja + 0; position[0][0][1] = posYpaja + 0;
		position[0][1][0] = posXpaja + 1; position[0][1][1] = posYpaja + 0;
		position[0][2][0] = posXpaja + 2; position[0][2][1] = posYpaja + 0;
		position[0][3][0] = posXpaja + 3; position[0][3][1] = posYpaja + 0;
		position[0][4][0] = posXpaja + 4; position[0][4][1] = posYpaja + 0;
		position[0][5][0] = posXpaja + 5; position[0][5][1] = posYpaja + 0;
		position[0][6][0] = posXpaja + 6; position[0][6][1] = posYpaja + 0;
		position[0][7][0] = posXpaja + 7; position[0][7][1] = posYpaja + 0;
		position[0][8][0] = posXpaja + 8; position[0][8][1] = posYpaja + 0;

		position[1][0][0] = posXpaja + 0; position[1][0][1] = posYpaja + 1;
		position[1][1][0] = posXpaja + 1; position[1][1][1] = posYpaja + 1;
		position[1][2][0] = posXpaja + 2; position[1][2][1] = posYpaja + 1;
		position[1][3][0] = posXpaja + 3; position[1][3][1] = posYpaja + 1;
		position[1][4][0] = posXpaja + 4; position[1][4][1] = posYpaja + 1;
		position[1][5][0] = posXpaja + 5; position[1][5][1] = posYpaja + 1;
		position[1][6][0] = posXpaja + 6; position[1][6][1] = posYpaja + 1;
		position[1][7][0] = posXpaja + 7; position[1][7][1] = posYpaja + 1;
		position[1][8][0] = posXpaja + 8; position[1][8][1] = posYpaja + 1;

		position[2][0][0] = posXpaja + 0; position[2][0][1] = posYpaja + 2;
		position[2][1][0] = posXpaja + 1; position[2][1][1] = posYpaja + 2;
		position[2][2][0] = posXpaja + 2; position[2][2][1] = posYpaja + 2;
		position[2][3][0] = posXpaja + 3; position[2][3][1] = posYpaja + 2;
		position[2][4][0] = posXpaja + 4; position[2][4][1] = posYpaja + 2;
		position[2][5][0] = posXpaja + 5; position[2][5][1] = posYpaja + 2;
		position[2][6][0] = posXpaja + 6; position[2][6][1] = posYpaja + 2;
		position[2][7][0] = posXpaja + 7; position[2][7][1] = posYpaja + 2;
		position[2][8][0] = posXpaja + 8; position[2][8][1] = posYpaja + 2;

		if (!soundLoaded) {
			menuSound();
			soundLoaded = true;
		}

		if (!soundLoaded) {
			seleccionarSound();
			soundLoaded = true;
		}
		switch (operador) {
		case 1:
			seleccionarSound();
			sound2.play();
			op = 'a';
			pisoMov = 1;
			posicionX = 88 + 48;
			posicionY = 41;
			contador = 0;
			contador1 = 0;
			c = 0;
			setColor(0, 0);
			system("cls");
			SetConsoleRegionColor(52, 0, 100, 54, 3, 80);
			background();
			piso();
			break; // op random q no sea q
		case 2:
			menuSound();
			sound2.play();
			op = 'q';
			break;
		}
	} while (op != 'q' && op != 'a');
}
void puntos(int c) {
	fstream record("puntuacion.txt", ios::app | ios::in);
	record<< c << endl;
	setColor(202, 222);
	gotoxy(52 + 46, 14);
	cout << "PUNTAJE";
	showPuntaje(c, 52 + 47, 15);
	setColor(202, 222);
	gotoxy(52 + 43, 20);
	cout << "MEJOR PUNTAJE";
	showPuntaje(mayorPunto(), 52 + 47, 21);
	record.close();
}
int mayorPunto() {
	int x, may = -1;
	ifstream record("puntuacion.txt");
	while (record >> x) {
		if (x > may)
			may = x;
	}
	record.close();
	return may;
}

void vidaBoss(int rest, int dmg) { // aun no se como utilizarlo
	int x, y, q, r, k, p, s;
	p = 0; s = 0;
	x = 102; y = 45;
	q = 15; r = 222;
	k = rest;

	while (k >= rest - dmg) {
		int unidades = k % 10;
		int decenas = (k / 10) % 10;
		int centenas = (k / 100) % 10;
		int unidadesMil = (k / 1000) % 10;
		limpiarPantalla(x - 20, y, x + 10, y + 5);
		// Imprimir las unidades
		if (k >= 1000) {
			imprimirDigito(unidadesMil, x - 15, y);
			imprimirDigito(centenas, x - 10, y);
			imprimirDigito(decenas, x - 5, y);
			imprimirDigito(unidades, x, y);
		}
		else
			if (k >= 100) {
				imprimirDigito(centenas, x - 10, y);
				imprimirDigito(decenas, x - 5, y);
				imprimirDigito(unidades, x, y);
			}
			else
				if (k >= 10) {
					imprimirDigito(decenas, x - 5, y);
					imprimirDigito(unidades, x, y);
				}
				else {
					imprimirDigito(unidades, x, y);
				}
		k--;
	}
}

void showPuntaje(int k,int x,int y) {
	int unidades = k % 10;
	int decenas = (k / 10) % 10;
	int centenas = (k / 100) % 10;
	int unidadesMil = (k / 1000) % 10;
	if (k >= 1000) {
		imprimirDigito(unidadesMil, x - 15, y);
		imprimirDigito(centenas, x - 10, y);
		imprimirDigito(decenas, x - 5, y);
		imprimirDigito(unidades, x, y);
	}
	else
		if (k >= 100) {
			imprimirDigito(centenas, x - 5, y);
			imprimirDigito(decenas, x, y);
			imprimirDigito(unidades, x + 5, y);
		}
		else
			if (k >= 10) {
				imprimirDigito(decenas, x - 3, y);
				imprimirDigito(unidades, x + 2, y);
			}
			else
				imprimirDigito(unidades, x, y);
}

void imprimirDigito(int digito, int x, int y) {
	int q, r;
	q = 15; r = 0;
	switch (digito) {
	case 0:
		gotoxy(x, y); setColor(0, 222); cout <<    "▄▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█ ▄▄ █";
		gotoxy(x, y + 2); setColor(0, 15); cout << "█ ██ █";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄▄█";
		break;
	case 1:
		gotoxy(x + 1, y); setColor(0, 222); cout << "▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█▀ █";
		gotoxy(x, y + 2); setColor(0, 15); cout << "██ █"; setColor(0, 222); cout << "▄";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄█";
		break;
	case 2:
		gotoxy(x + 1, y); setColor(0, 222); cout << "▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█▀▄▄▀█";
		gotoxy(x, y + 2); setColor(0, 15); cout << "██▀▄██";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄▄█";
		break;
	case 3:
		gotoxy(x, y); setColor(0, 222); cout <<    "▄▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█▄▄▄ █";
		gotoxy(x, y + 2); setColor(0, 222); cout << "▄"; setColor(0, 15); cout << "█▄▄ █";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄▄█";
		break;
	case 4:
		gotoxy(x, y); setColor(0, 222); cout <<    "▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█ █ █";
		gotoxy(x, y + 2); setColor(0, 15); cout << "█▄▄ █"; setColor(0, 222); cout << "▄";
		gotoxy(x + 1, y + 3); setColor(0, 15); cout << "█▄▄▄█";
		break;
	case 5:
		gotoxy(x, y); setColor(0, 222); cout <<    "▄▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█ ▄▄▄█";
		gotoxy(x, y + 2); setColor(0, 15); cout << "█▄▄▄ █";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄▄█";
		break;
	case 6:
		gotoxy(x, y); setColor(0, 222); cout <<    "▄▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█ ▄▄▄█";
		gotoxy(x, y + 2); setColor(0, 15); cout << "█ ▄▄ █";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄▄█";
		break;
	case 7:
		gotoxy(x, y); setColor(0, 222); cout <<       "▄▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout <<    "█▄▄▄ █";
		gotoxy(x + 1, y + 2); setColor(0, 222); cout << "▄"; setColor(0, 15); cout << "█ █"; setColor(0, 222); cout << "▀";
		gotoxy(x + 1, y + 3); setColor(0, 15); cout << "█▄█"; setColor(0, 222); cout << "▀";
		break;
	case 8:
		gotoxy(x + 1, y); setColor(0, 222); cout << "▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█▀▄▄▀█";
		gotoxy(x, y + 2); setColor(0, 15); cout << "█▀▄▄▀█";
		gotoxy(x, y + 3); setColor(0, 222); cout << "▀"; setColor(0, 15); cout << "█▄▄█"; setColor(0, 222); cout << "▀";
		break;
	case 9:
		gotoxy(x, y); setColor(0, 222); cout <<    "▄▄▄▄▄▄";
		gotoxy(x, y + 1); setColor(0, 15); cout << "█ ▄▄ █";
		gotoxy(x, y + 2); setColor(0, 15); cout << "█▄▄▄ █";
		gotoxy(x, y + 3); setColor(0, 15); cout << "█▄▄▄▄█";
		break;
	}
}

void limpiarPantalla(int x1, int y1, int x2, int y2) {
	for (int i = y1; i <= y2; ++i) {
		gotoxy(x1, i);
		for (int j = x1; j <= x2; ++j) {
			cout << " ";
		}
	}
}

void validacionTubo(char& op, int& pisoMov, int& posicionX, int& posicionY, int& contador, int& contador1, int positionTubo[][4][2], int position[3][width][2], int &c) {
	int i = 1;
	if ((positionTubo[i][0][0] <= position[0][8][0] && positionTubo[i][1][0] >= position[0][0][0]) || (positionTubo[i][0][0] <= position[2][0][0] && positionTubo[i][1][0] >= position[2][0][0])) {
		if (position[0][0][1] > positionTubo[i][0][1] && position[2][0][1] < positionTubo[i][2][1]) {}
		else
			pantallaDerrota(op, pisoMov, posicionX, posicionY, contador, contador1, position, c);
	}
	//Esquinas: position [0-2][0-8][0-1] 
}
bool validacionTubo1vs1(char& op, int& pisoMov, int& posicionX, int& posicionY, int& contador, int& contador1, int positionTubo[][4][2], int position[3][width][2], int& c) {
	for (int i = 1; i <= contador; i++) {
		if ((positionTubo[i][0][0] <= position[0][8][0] && positionTubo[i][1][0] >= position[0][0][0]) || (positionTubo[i][0][0] <= position[2][0][0] && positionTubo[i][1][0] >= position[2][0][0])) {
			if (position[0][0][1] > positionTubo[i][0][1] && position[2][0][1] < positionTubo[i][2][1]) {
				return 1;
			}
			else
				return 0;
		}
	}
}
void background() {
	int posXfondo = 52;
	int posYfondo = 32;
	gotoxy(posXfondo + 0, posYfondo + 0); setColor(194, 80); cout << "                                                     ███████████                     ███████████    ";
	gotoxy(posXfondo + 0, posYfondo + 1); setColor(194, 80); cout << "                     ███████████     ███████████   ███████████████   ███████████   ███████████████  ";
	gotoxy(posXfondo + 0, posYfondo + 2); setColor(194, 80); cout << "     ███████████   ███████████████ ████████████████████████████████████████████████████████████████ ";
	gotoxy(posXfondo + 0, posYfondo + 3); setColor(194, 80); cout << "   "; setColor(194, 151); cout << "██████████████████████████████████████    ██████    ████████████████████████████     ████████████";
	gotoxy(posXfondo + 0, posYfondo + 4); setColor(194, 80); cout << "  "; setColor(194, 151); cout << "███████████████    ████████████████████    ██          ████████     █████████████         ████████";
	gotoxy(posXfondo + 0, posYfondo + 5); setColor(194, 151); cout << "█████████████████    ██   ███████████████    ██          ████████     █     ███████         ████████";
	gotoxy(posXfondo + 0, posYfondo + 6); setColor(194, 151); cout << "███████████    ██    ██   ███████████████    ██          ██     █     █     ███████         ████   █";
	gotoxy(posXfondo + 0, posYfondo + 7); setColor(194, 151); cout << "████    ███    ██    ██     ███████    ██    ██          ██     █     █     ███████         █      █";
	gotoxy(posXfondo + 0, posYfondo + 8); setColor(194, 151); cout << "██        █          ██     █    ██    ██    ██          ██     █     █     █     █         █      █";
	gotoxy(posXfondo + 0, posYfondo + 9); setColor(194, 151); cout << "██        █          ██     █    ██    ██    ██          ██     █     █     █     █         █      █";
	int posXsol = 68;
	int posYsol = 12;
	gotoxy(posXsol + 2, posYsol + 0); setColor(229, 80); cout <<   "▄▄▄▄";
	gotoxy(posXsol + 0, posYsol + 1); setColor(229, 80); cout << "▄██████▄";
	gotoxy(posXsol + 0, posYsol + 2); setColor(229, 230); cout <<"█      █";
	gotoxy(posXsol + 0, posYsol + 3); setColor(230, 80); cout << " ▀████▀";
}

void imprimirTubo(int posXtub, int posYpos, int tamano, int hueco, int tamano2) {
	int cieloColor = 80, verde2 = 40, verde = 40, verdeBrillo = 154, verdeSombra = 34;

	// tubo de abajo
	gotoxy(posXtub - 1, posYpos - tamano);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████   ";

	gotoxy(posXtub - 1, posYpos - tamano + 1);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████   ";

	gotoxy(posXtub, posYpos - tamano + 2);
	setColor(verdeSombra, verde); cout << "▀▀▀▀▀▀▀▀▀▀▀▀"; setColor(80, 80); cout << "███";

	for (int i = 0; i <= tamano - 3; i++) {
		gotoxy(posXtub, posYpos - i);
		setColor(verde2, cieloColor); cout << "█";
		setColor(verdeBrillo, cieloColor); cout << "██";
		setColor(verde2, cieloColor); cout << "███";
		setColor(verde, cieloColor); cout << "██████   ";
	}
	// tubo de arriba
	gotoxy(posXtub, posYpos - tamano - hueco - 2);
	setColor(verdeSombra, verde); cout << "▄▄▄▄▄▄▄▄▄▄▄▄"; setColor(80, 80); cout << "███";

	gotoxy(posXtub - 1, posYpos - tamano - hueco - 1);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████   ";

	gotoxy(posXtub - 1, posYpos - tamano - hueco);
	setColor(verde2, cieloColor); cout << "█";
	setColor(verdeBrillo, cieloColor); cout << "██";
	setColor(verde2, cieloColor); cout << "███████████   ";

	for (int i = 3; i <= tamano2; i++) {
		gotoxy(posXtub, posYpos - tamano - hueco - i);
		setColor(verde2, cieloColor); cout << "█";
		setColor(verdeBrillo, cieloColor); cout << "██";
		setColor(verde2, cieloColor); cout << "█████████   ";
	}
}

void aparecerTubos(int position[][4][2], int  posicionX, int posicionY, int& contador) {
	int Puntos = 4, XY = 2;
	int tamano = 4 + rand() % 19;
	int hueco = 10 + rand() % 3;
	int tamano2 = 41 - hueco - tamano;

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

	if (contador > 0) {
			imprimirTubo(position[1][0][0], posicionY, posicionY - position[1][2][1], position[1][2][1] - position[1][0][1], position[1][0][1]);
			position[1][0][0] -= 3; // Mueve el tubo de 3 en 3 unidades
			position[1][1][0] -= 3;
			position[1][2][0] -= 3;
			position[1][3][0] -= 3;
	}

	if (position[1][0][0] < 53) {
		contador--;
		clearRegion(52, 0, 52 + 15, 41); // limpia al final la region donde termina el recorrido del tubo
	}
}

void personaje2() {
	int posXper = 5, posYper = 12;
	gotoxy(posXper + 3, posYper); setColor(13, 3); cout << "▀█▄";
	gotoxy(posXper, posYper + 1); setColor(5, 3); cout << "█▄█"; setColor(13, 5); cout << "▄█"; setColor(8, 13); cout << "▄"; setColor(13, 3); cout << "█▄";
	gotoxy(posXper, posYper + 2); setColor(5, 3); cout << "█▀█"; setColor(13, 5); cout << "▀█"; setColor(0, 13); cout << "▀"; setColor(13, 5); cout << "█▀";
}
// ---------------------------------------------
// mov del pajaro en el juego
void showImage(int pos[][width][2], char opMov) {
	if (opMov != 'w' && opMov != 'x' && opMov != 'y') {
		gotoxy(pos[0][0][0], pos[0][0][1]); setColor(25, 80); cout << "   ▄▄▄"; setColor(15, 80); cout << "▄▄";
		gotoxy(pos[1][0][0], pos[1][0][1]); setColor(39, 25); cout << "██▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
		gotoxy(pos[2][0][0], pos[2][0][1]); setColor(39, 80); cout << " ▀█"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
	}
	else if (opMov == 'w') {
		gotoxy(pos[0][0][0], pos[0][0][1]); setColor(25, 80); cout << "      "; setColor(15, 80); cout << "  ";
		gotoxy(pos[1][0][0], pos[1][0][1]); setColor(39, 80); cout << "  "; setColor(25, 80); cout << "▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(15, 0); cout << "▀"; setColor(15, 80); cout << "▄";
		gotoxy(pos[2][0][0], pos[2][0][1]); setColor(39, 80); cout << "▄██"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";

	}
	else {
		gotoxy(pos[0][0][0], pos[0][0][1]); setColor(25, 80); cout << "    ▄▄"; setColor(15, 80); cout << "▄▄";
		gotoxy(pos[1][0][0], pos[1][0][1]); setColor(39, 80); cout << "  "; setColor(25, 80); cout << "▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
		gotoxy(pos[2][0][0], pos[2][0][1]); setColor(39, 80); cout << "▀██"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
	}
}

// mov del pajaro en el menu
void showImageMenu(int &pajMov, int Xpaja, int Ypaja) {
    if (pajMov <= 2) {
        gotoxy(Xpaja, Ypaja); setColor(25, 80); cout << "   ▄▄▄"; setColor(15, 80); cout << "▄▄";
        gotoxy(Xpaja, Ypaja + 1); setColor(39, 25); cout << "██▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
        gotoxy(Xpaja, Ypaja + 2); setColor(39, 80); cout << " ▀▀"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
    }
	else if (pajMov <= 4) {
		gotoxy(Xpaja, Ypaja); setColor(25, 80); cout << "    ▄▄"; setColor(15, 80); cout << "▄▄";
		gotoxy(Xpaja, Ypaja + 1); setColor(39, 80); cout << "  "; setColor(25, 80); cout << "▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
		gotoxy(Xpaja, Ypaja + 2); setColor(39, 80); cout << "▀██"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
	}
	else if (pajMov <= 6) {
		gotoxy(Xpaja, Ypaja); setColor(25, 80); cout << "    ▄▄"; setColor(15, 80); cout << "▄▄";
		gotoxy(Xpaja, Ypaja + 1); setColor(39, 80); cout << "  "; setColor(25, 80); cout << "▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
		gotoxy(Xpaja, Ypaja + 2); setColor(39, 80); cout << "▄██"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
	}
	else{
		gotoxy(Xpaja, Ypaja); setColor(25, 80); cout << "    ▄▄"; setColor(15, 80); cout << "▄▄";
		gotoxy(Xpaja, Ypaja + 1); setColor(39, 80); cout << "  "; setColor(25, 80); cout << "▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
		gotoxy(Xpaja, Ypaja + 2); setColor(39, 80); cout << "▀██"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
    }
    if (pajMov == 9)
        pajMov = 0;
    pajMov++;
}

void showImage2(int pos[][width][2], int pos2[][width][2]) {
	gotoxy(pos[0][0][0], pos[0][0][1]); setColor(25, 80); cout << "   ▄▄▄"; setColor(15, 80); cout << "▄▄";
	gotoxy(pos[1][0][0], pos[1][0][1]); setColor(39, 25); cout << "██▄"; setColor(25, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
	gotoxy(pos[2][0][0], pos[2][0][1]); setColor(39, 80); cout << " ▀▀"; setColor(25, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";

	gotoxy(pos2[0][0][0], pos2[0][0][1]); setColor(34, 80); cout << "   ▄▄▄"; setColor(15, 80); cout << "▄▄";
	gotoxy(pos2[1][0][0], pos2[1][0][1]); setColor(76, 34); cout << "██▄"; setColor(34, 80); cout << "███"; setColor(15, 80); cout << "█"; setColor(66, 0); cout << "▀"; setColor(15, 80); cout << "█";
	gotoxy(pos2[2][0][0], pos2[2][0][1]); setColor(76, 80); cout << " ▀▀"; setColor(34, 80); cout << "████"; setColor(202, 208); cout << "▄▄▄";
}

void showClearImage(int pos[][width][2]) {// --------------------------------------- limpia la region desde el pos inicial en showImage, esquina superior izquierda del pajaro en showImage, hasta la esquina inferior derecha
	clearRegion(pos[0][0][0], pos[0][0][1], pos[2][0][0] + 9, pos[2][0][1]); // el mas 10 para q selecione hasta la esquina inferior derecha del pajaro desde le punto inicial (esquina superior izquierda)
}

void changePos(int positions[][width][2], char op) {

	static bool soundLoaded = false;
	if (!soundLoaded) {
		saltoSound();
		soundLoaded = true;
	}
	/* del chapt gpt :v:
	"soundLoaded" asegura que el archivo de sonido se carga solo una vez, cuando se llama por primera vez a changePos.
	Esto significa que todas las llamadas posteriores simplemente reproducen el sonido desde la memoria, evitando la carga repetitiva
	del archivo desde el disco. Esto mejora significativamente el rendimiento, especialmente en escenarios donde la función se llama frecuentemente.
	*/
	int pos = 1, k = 0;
	switch (op) {
	case 'a':
		pos = 0;
		k = -10;
		break;
	case 'd':
		pos = 0;
		k = 10;
		break;
	case 'w':
		k = -4;
		saltoSound();
		sound.play();
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
		if (positions[i][j][0] + k >= 52 && positions[i][j][0] + k <= 142 && positions[i][j][1] + k >= 0 && positions[height - 1][j][1] + k <= 41) {
			for (int j = 0; j < width; j++) {
				positions[i][j][pos] += k;
			}
		}
		else {
			break;
		}

	}
}
void changePos2(int positions[][width][2], char op) { // --------------------------------- jugador 2
	int pos = 1, k = 0;
	switch (op) {
	case 75:
		pos = 0;
		k = -10;
		break;
	case 77:
		pos = 0;
		k = 10;
		break;
	case 72:
		k = -3;
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
	case 'w': case 72:
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
	auto start = chrono::high_resolution_clock::now();
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
		auto now = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(now - start).count();
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
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void newchoosePosition2(char& op, char& po) { // ----------------------------------------- jugador 2
	auto start = std::chrono::high_resolution_clock::now();
	int timeout_ms = 50;
	char tecla;
	while (true) {
		if (_kbhit()) {
			tecla = _getch();
			setColor(80, 80);

			if (tecla == 'w' || tecla == 'a' || tecla == 'd') {
				op = tecla;
				caidaSubidaIncremento(po);
				return;
			}


			else if (tecla == 72 || tecla == 75 || tecla == 77 || tecla == 'q') {
				po = tecla;
				caidaSubidaIncremento(op);
				return;
			}
		}
		setColor(80, 80);
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
		if (duration >= timeout_ms) {
			if (po == 72 || po == 'x' || po == 'y' || po == 'f' || po == 'g' || po == 'h') {
				caidaSubidaIncremento(po);
			}
			else {
				po = 'f';
			}
			if (op == 'w' || op == 'x' || op == 'y' || op == 'f' || op == 'g' || op == 'h') {
				caidaSubidaIncremento(op);
			}
			else {
				op = 'f';
			}

			return;
		}
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void seleccionarPausa(int& op) {
	char selec;
	int x = 52 + 42, y = 31, xf = 52 + 33, yf = 30;
	int c1, c2;
	do {
		if (op < 1)
			op = 2;
		else if (op > 2)
			op = 1;

		if (op == 1) {
			c1 = 208;
			yf = 30;
		}
		else
			c1 = 202;
		if (op == 2) {
			c2 = 208;
			yf = 34;
		}
		else
			c2 = 202;

		flecha(xf, yf);
		cuadroScreen(52 + 38, 30, c1); gotoxy(x + 3, y + 0); cout << "REINTENTAR";
		cuadroScreen(52 + 38, 34, c2); gotoxy(x + 3, y + 4); cout << "M E N U";

		selec = _getch();
		if (selec == 224) { // 224 indica que es una tecla especial
			selec = _getch(); // Captura el código de la tecla especial
		}
		static bool soundLoaded = false;
		if (!soundLoaded) {
			flechaSound();
			soundLoaded = true;
		}

		switch (selec) {
		case 's': case 80:
			flechaSound();
			sound.play();
			op += 1;
			SetConsoleRegionColor(xf, yf, 3, 3, 15, 80);
			SetConsoleRegionColor(xf + 30, yf, 3, 3, 15, 80);
			break;
		case 'w': case 72:
			flechaSound();
			sound.play();
			op -= 1;
			SetConsoleRegionColor(xf, yf, 3, 3, 15, 80);
			SetConsoleRegionColor(xf + 30, yf, 3, 3, 15, 80);
			break;
		}
	} while (selec != 13 && selec !=32);
}
void seleccionarMenu(int& op, char &selec, int &xf, int &yf) {
	int x = 52 + 42, y = 11;
	int c1 = 202, c2= 202, c3=202, c4=202;

	selec = _getch();
	if (selec == 224) { // 224 indica que es una tecla especial
		selec = _getch(); // Captura el código de la tecla especial
	}
	static bool soundLoaded = false;
	if (!soundLoaded) {
		flechaSound();
		soundLoaded = true;
	}
	switch (selec) {
	case 's': case 80:
		flechaSound();
		sound.play();
		op += 1;
		SetConsoleRegionColor(xf, yf, 3, 3, 15, 80);
		SetConsoleRegionColor(xf + 30, yf, 3, 3, 15, 80);
		break;
	case 'w': case 72:
		flechaSound();
		sound.play();
		op -= 1;
		SetConsoleRegionColor(xf, yf, 3, 3, 15, 80);
		SetConsoleRegionColor(xf + 30, yf, 3, 3, 15, 80);
		break;
	}
	if (op < 1)
		op = 4;
	else if (op > 4)
		op = 1;

	if (op == 1) {
		c1 = 208;
		yf = 10;
	}
	else
		c1 = 202;
	if (op == 2) {
		c2 = 208;
		yf = 14;
	}
	else
		c2 = 202;
	if (op == 3) {
		c3 = 208;
		yf = 18;
	}
	else
		c3 = 202;
	if (op == 4) {
		c4 = 208;
		yf = 22;
	}
	else
		c4 = 202;
	flecha(xf, yf);
	cuadroScreen(52 + 38, 10, c1); gotoxy(x + 3, y + 0); cout << "J U G A R";
	cuadroScreen(52 + 38, 14, c2); gotoxy(x + 3, y + 4); cout << "1  V S  1";
	cuadroScreen(52 + 38, 18, c3); gotoxy(x + 2, y + 8); cout << "V S  J E F E";
	cuadroScreen(52 + 38, 22, c4); gotoxy(x + 3, y + 12); cout << "S A L I R";
}
void movPiso(int &pisoMov) {
	if (pisoMov == 1) {
		gotoxy(58, 42);
		for (int j = 0; j < 35; ++j) {
			if (j % 3 == 0) {

				setColor(112, 154);
				cout << "▄██▀";
			}
			else {
				setColor(154, 80);
				cout << "██";
			}
		}
	}
	else if (pisoMov == 2){
		gotoxy(55, 42);
		for (int j = 0; j < 35; ++j) {
			if (j % 3 == 0 ) {

				setColor(112, 154);
				cout << "▄██▀";
			}
			else {
				setColor(154, 80);
				cout << "██";
			}
		}
	}
	else {
		gotoxy(52, 42);
		for (int j = 0; j < 35; ++j) {
			if (j % 3 == 0) {

				setColor(112, 154);
				cout << "▄██▀";
			}
			else {
				setColor(154, 80);
				cout << "██";
			}
		}
	}
	if (pisoMov == 3) {
		pisoMov = 0;
	}
	pisoMov++;
}

void piso() {
	for (int i = 0; i < 12; ++i) {
		gotoxy(52, 42 + i);
		if (i == 1)
			setColor(208, 215);
		else
			setColor(222, 80);
		for (int j = 0; j < 100; ++j) {
			if (i == 1)
				cout << "▀";
			else
				cout << "█";
		}
	}
}

void titulo(int x, int y) {
	SetConsoleOutputCP(CP_UTF8);

	// F
	gotoxy(x, y);     setColor(195, 80); cout << "███████"; setColor(37, 80); cout << "██";
	gotoxy(x, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x, y + 3); setColor(195, 80); cout << "██████"; setColor(37, 80); cout << "██";
	gotoxy(x, y + 4); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x, y + 5); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x, y + 6); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";

	// L
	gotoxy(x + 8, y);     setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 8, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 8, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 8, y + 3); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 8, y + 4); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 8, y + 5); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 8, y + 6); setColor(195, 80); cout << "███████"; setColor(37, 80); cout << "█";

	// U
	gotoxy(x + 16, y);     setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 22, y);   setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 16, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 22, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 16, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 22, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 16, y + 3); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 22, y + 3); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 16, y + 4); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 22, y + 4); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 16, y + 5); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 22, y + 5); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 17, y + 6); setColor(195, 80); cout << "██████"; setColor(37, 80); cout << "█";

	// F
	gotoxy(x + 26, y);     setColor(195, 80); cout << "███████"; setColor(37, 80); cout << "█";
	gotoxy(x + 26, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 26, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 26, y + 3); setColor(195, 80); cout << "██████"; setColor(37, 80); cout << "█";
	gotoxy(x + 26, y + 4); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 26, y + 5); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";
	gotoxy(x + 26, y + 6); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "██";

	// F
	gotoxy(x + 34, y);     setColor(195, 80); cout << "███████"; setColor(37, 80); cout << "█";
	gotoxy(x + 34, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 34, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 34, y + 3); setColor(195, 80); cout << "██████"; setColor(37, 80); cout << "█";
	gotoxy(x + 34, y + 4); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 34, y + 5); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";
	gotoxy(x + 34, y + 6); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█";

	// Y
	gotoxy(x + 42, y);     setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 47, y); setColor(195, 80); cout << "██"; setColor(37, 80);
	gotoxy(x + 42, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); cout << "█"; gotoxy(x + 47, y + 1); setColor(195, 80); cout << "██"; setColor(37, 80); 
	gotoxy(x + 43, y + 2); setColor(195, 80); cout <<  "██"; setColor(37, 80); cout << "█"; gotoxy(x + 46, y + 2); setColor(195, 80); cout << "██"; setColor(37, 80); 
	gotoxy(x + 44, y + 3); setColor(195, 80); cout <<   "███"; setColor(37, 80);
	gotoxy(x + 45, y + 4); setColor(195, 80); cout <<    "██"; setColor(37, 80);
	gotoxy(x + 45, y + 5); setColor(195, 80); cout <<    "██"; setColor(37, 80);
	gotoxy(x + 45, y + 6); setColor(195, 80); cout <<    "██"; setColor(37, 80); 

	// B
	gotoxy(x + 53, y);     setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";
	gotoxy(x + 53, y + 1); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 58, y + 1); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 53, y + 2); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 58, y + 2); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 53, y + 3); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";
	gotoxy(x + 53, y + 4); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 58, y + 4); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 53, y + 5); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 58, y + 5); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 53, y + 6); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";

	// I
	gotoxy(x + 61, y);     setColor(37, 80); cout << "█"; setColor(195, 80); cout << "████";
	gotoxy(x + 62, y + 1); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 62, y + 2); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 62, y + 3); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 62, y + 4); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 62, y + 5); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 61, y + 6); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "████";

	// R
	gotoxy(x + 67, y);     setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";
	gotoxy(x + 67, y + 1); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 72, y + 1); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 67, y + 2); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 72, y + 2); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 67, y + 3); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";
	gotoxy(x + 67, y + 4); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 70, y + 4); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 67, y + 5); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 71, y + 5); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";
	gotoxy(x + 67, y + 6); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 72, y + 6); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██";

	// D
	gotoxy(x + 75, y);     setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";
	gotoxy(x + 75, y + 1); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 79, y + 1); setColor(37, 80); cout << "██"; setColor(195, 80); cout << "██";
	gotoxy(x + 75, y + 2); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 80, y + 2); setColor(37, 80); cout << "██"; setColor(195, 80); cout << "██";
	gotoxy(x + 75, y + 3); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 80, y + 3); setColor(37, 80); cout << "██"; setColor(195, 80); cout << "██";
	gotoxy(x + 75, y + 4); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 80, y + 4); setColor(37, 80); cout << "██"; setColor(195, 80); cout << "██";
	gotoxy(x + 75, y + 5); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██"; gotoxy(x + 79, y + 5); setColor(37, 80); cout << "██"; setColor(195, 80); cout << "██";
	gotoxy(x + 75, y + 6); setColor(37, 80); cout << "█"; setColor(195, 80); cout << "██████";
}
