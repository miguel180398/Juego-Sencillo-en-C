#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIL 7
#define COL 14

int aleatorio(int, int);
void limpiar();

void llenarMapa(char [FIL][COL]);
void mostrarMapa(char [FIL][COL]);
void asignarPosiciones(char [FIL][COL], int *, int *);
void moverPosicion(char [FIL][COL], int *, int *);

int main() {

	limpiar();
	int i;
	char mapa[FIL][COL];

	llenarMapa(mapa);

	// Posicion incial, aleatorio para las filas
	int posicionFilas = aleatorio(1, 5);
	int posicionColumnas = 1;

	for (i = 0; i < 11; i++) {
		asignarPosiciones(mapa, &posicionFilas, &posicionColumnas);
		moverPosicion(mapa, &posicionFilas, &posicionColumnas);
	}

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
			if (i == FIL - 1) mapa[i][j] = '/';
			if (j == 0) mapa[i][j] = '/';
			if (j == COL - 1) mapa[i][j] = '/';
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

void asignarPosiciones(char mapa[FIL][COL], int *posicionFilas, int *posicionColumnas) {
	// Nombre variables
	char posicion = 'X';
	char barrera = '/';
	char camino = 'O';

	// Colocar posiciones donde se puede mover

	// X arriba
	if (mapa[*posicionFilas][*posicionColumnas-1] != barrera && mapa[*posicionFilas][*posicionColumnas-1] != camino) mapa[*posicionFilas][*posicionColumnas-1] = posicion;

	// X abajo
	if (mapa[*posicionFilas+1][*posicionColumnas] != barrera && mapa[*posicionFilas+1][*posicionColumnas] != camino) mapa[*posicionFilas+1][*posicionColumnas] = posicion;

	// X izquierda
	if (mapa[*posicionFilas-1][*posicionColumnas] != barrera && mapa[*posicionFilas-1][*posicionColumnas] != camino) mapa[*posicionFilas-1][*posicionColumnas] = posicion;

	// X derecha
	if (mapa[*posicionFilas][*posicionColumnas+1] != barrera && mapa[*posicionFilas][*posicionColumnas+1] != camino) mapa[*posicionFilas][*posicionColumnas+1] = posicion;

	// X diagonal derecha abajo
	if (mapa[*posicionFilas+1][*posicionColumnas+1] != barrera && mapa[*posicionFilas+1][*posicionColumnas+1] != camino) mapa[*posicionFilas+1][*posicionColumnas+1] = posicion;

	// X diagonal izquierda arriba
	if (mapa[*posicionFilas-1][*posicionColumnas-1] != barrera && mapa[*posicionFilas-1][*posicionColumnas-1] != camino) mapa[*posicionFilas-1][*posicionColumnas-1] = posicion;

	// X diagonal dercha arriba
	if (mapa[*posicionFilas-1][*posicionColumnas+1] != barrera && mapa[*posicionFilas-1][*posicionColumnas+1] != camino) mapa[*posicionFilas-1][*posicionColumnas+1] = posicion;

	// X diagonal izquierda abajo
	if (mapa[*posicionFilas+1][*posicionColumnas-1] != barrera && mapa[*posicionFilas+1][*posicionColumnas-1] != camino) mapa[*posicionFilas+1][*posicionColumnas-1] = posicion;
}

void moverPosicion(char mapa[FIL][COL], int *posicionFilas, int *posicionColumnas) {

	// Nombre variables
	char posicion = 'X';
	char barrera = '/';
	char camino = 'O';

	// Mover a siguiente posicion
	int i, j, k, l, contadorPosiciones = 0;

	// Buscar posiciones
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			if (mapa[i][j] == posicion) contadorPosiciones++;
		}
	}

	int posicionMover = aleatorio(1, contadorPosiciones);
	contadorPosiciones = 0;

	// Mover a esa posicion
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			if (mapa[i][j] == posicion) contadorPosiciones++;
			if (contadorPosiciones == posicionMover) {
				mapa[i][j] = '>'; // Posicion donde se mueve
				mapa[*posicionFilas][*posicionColumnas] = camino; // Posicion anterior

				// Comparacion derecha
				if (*posicionFilas == i && *posicionColumnas + 1 == j) {
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (l == j - 1 && (k == 1 || k == 2 || k == 3 || k == 4 | k == 5))
							{
								if(mapa[k][l] != camino)
								{
									mapa[k][l] = barrera;
								}
							}
						}
					}
					// Arriba
					mapa[*posicionFilas-1][*posicionColumnas+1] = barrera;
					// Abajo
					mapa[*posicionFilas+1][*posicionColumnas+1] = barrera;
				}

				// Comparacion diagonal arriba
				if (*posicionFilas - 1 == i && *posicionColumnas + 1 == j) {
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (l == j - 1 && (k == 1 || k == 2 || k == 3 || k == 4 | k == 5))
							{
								if(mapa[k][l] != camino)
								{
									mapa[k][l] = barrera;
								}
							}
						}
					}
					// Abajo
					mapa[*posicionFilas][*posicionColumnas+1] = barrera;

					// Para colocar '-' en las 'X'
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (mapa[k][l] == posicion) {
								mapa[k][l] = '-';
							}
						}
					}
				}

				// Comparacion diagonal abajo
				if (*posicionFilas + 1 == i && *posicionColumnas + 1 == j) {
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (l == j - 1 && (k == 1 || k == 2 || k == 3 || k == 4 | k == 5))
							{
								if(mapa[k][l] != camino)
								{
									mapa[k][l] = barrera;
								}
							}
						}
					}
					// Arriba
					mapa[*posicionFilas][*posicionColumnas+1] = barrera;

					// Para colocar '-' en las 'X'
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (mapa[k][l] == posicion) {
								mapa[k][l] = '-';
							}
						}
					}
				}

				// Comparacion arriba
				if (*posicionFilas - 1 == i && *posicionColumnas == j) {
					mapa[*posicionFilas][*posicionColumnas+1] = barrera;
					// Para colocar '-' en las 'X'
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (mapa[k][l] == posicion) {
								mapa[k][l] = '-';
							}
						}
					}
				}

				// Comparacion abajo
				if (*posicionFilas + 1 == i && *posicionColumnas == j) {
					mapa[*posicionFilas][*posicionColumnas+1] = barrera;
					// Para colocar '-' en las 'X'
					for (k = 0; k < FIL; k++) {
						for (l = 0; l < COL; l++) {
							if (mapa[k][l] == posicion) {
								mapa[k][l] = '-';
							}
						}
					}
				}

				*posicionFilas = i;
				*posicionColumnas = j;
				break;
			}
		}
		if (contadorPosiciones == posicionMover) break;
	}
}
