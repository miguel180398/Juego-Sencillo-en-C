#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIL 7
#define COL 10

int aleatorio(int, int);
void limpiar();

void llenarMapa(char [FIL][COL]);
void mostrarMapa(char [FIL][COL]);
void asignarPosiciones(char [FIL][COL], int, int);
void moverPosicion(char [FIL][COL], int, int);

int main() {

	limpiar();
	char mapa[FIL][COL];

	llenarMapa(mapa);

	// Posicion incial, aleatorio para las filas
	int posicionFilas = aleatorio(1, 5);
	int posicionColumnas = 1;
	mapa[posicionFilas][posicionColumnas] = '0';

	asignarPosiciones(mapa, posicionFilas, posicionColumnas);

	moverPosicion(mapa, posicionFilas, posicionColumnas);

	mostrarMapa(mapa);

	return 0;
}

int aleatorio(int a, int b){
	int c;
	srand(time(NULL));
	c = a + rand() % b;
	return c;
}

void limpiar() {
	system("clear");
}

void llenarMapa(char mapa[FIL][COL]) {
	int i, j;
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			mapa[i][j] = '-';
			if (i == 0) mapa[i][j] = '/';
			if (i == 6) mapa[i][j] = '/';
			if (j == 0) mapa[i][j] = '/';
			if (j == 9) mapa[i][j] = '/';
		}
	}
}

void mostrarMapa(char mapa[FIL][COL]) {
	int i, j;
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			printf("%c", mapa[i][j]);
		}
		printf("\n");
	}
}

void asignarPosiciones(char mapa[FIL][COL], int posicionFilas, int posicionColumnas) {
	// Colocar posiciones donde se puede mover

	// X arriba
	if (mapa[posicionFilas][posicionColumnas-1] != '/') mapa[posicionFilas][posicionColumnas-1] = 'X';

	// X abajo
	if (mapa[posicionFilas+1][posicionColumnas] != '/') mapa[posicionFilas+1][posicionColumnas] = 'X';

	// X izquierda
	if (mapa[posicionFilas-1][posicionColumnas] != '/') mapa[posicionFilas-1][posicionColumnas] = 'X';

	// X derecha
	if (mapa[posicionFilas][posicionColumnas+1] != '/') mapa[posicionFilas][posicionColumnas+1] = 'X';

	// X diagonal derecha abajo
	if (mapa[posicionFilas+1][posicionColumnas+1] != '/') mapa[posicionFilas+1][posicionColumnas+1] = 'X';

	// X diagonal izquierda arriba
	if (mapa[posicionFilas-1][posicionColumnas-1] != '/') mapa[posicionFilas-1][posicionColumnas-1] = 'X';

	// X diagonal dercha arriba
	if (mapa[posicionFilas-1][posicionColumnas+1] != '/') mapa[posicionFilas-1][posicionColumnas+1] = 'X';

	// X diagonal izquierda abajo
	if (mapa[posicionFilas+1][posicionColumnas-1] != '/') mapa[posicionFilas+1][posicionColumnas-1] = 'X';
}

void moverPosicion(char mapa[FIL][COL], int posicionFilas, int posicionColumnas) {
	// Mover a siguiente posicion
	int i, j, contadorPosiciones = 0;

	// Buscar posiciones

	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			if (mapa[i][j] == 'X') contadorPosiciones++;
		}
	}

	int posicionMover = aleatorio(1, contadorPosiciones);
	contadorPosiciones = 0;
	// Mover a esa posicion

	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			if (mapa[i][j] == 'X') contadorPosiciones++;
			if (contadorPosiciones == posicionMover) {
				mapa[i][j] = 'O';
				mapa[posicionFilas][posicionColumnas] = 'O';
				break;
			}
		}
		if (contadorPosiciones == posicionMover) break;
	}
}
