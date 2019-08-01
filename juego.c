/*
Notas:
1) En cada funcion deberiamos especificar que librerias usan, porque ya veo que las librerias van para largoooo
2) Los comentarios como "añadido el dia tal por x persona" los borra la otra persona que los vea, para no tener tantos comentarios sueltos
3) Deberiamos usar esta parte para las notas, con este formato
4) Siempre dejar espacios entre funciones, me di cuenta que las sueles colocar juntas, bueno eso es solo algo estetico
5) Funcion "saltar", en vez de usar printf("\n");
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define FIL 7
#define COL 14

int aleatorio(int, int);
char letrasAleatorias();

void limpiar();
void saltar(int);

void llenarMatriz(char [FIL][COL]);
void mostrarMatriz(char [FIL][COL]);
void asignarPosiciones(char [FIL][COL], int *, int *);
void moverPosicion(char [FIL][COL], int *, int *);
void acomodarMatriz(char [FIL][COL]);

void imprimirColor(char *, char *, char *);
void reproducirAudio(char *);

int leerTecla(void);
void mapaColores(char,int);

// Pantallas (interfaz)
void pantallaMenu();

int main() {

	limpiar();

	int i;
	char mapa[FIL][COL];

	srand(time(NULL)); // Generar semilla para todo el programa

	llenarMatriz(mapa);

	// Posicion incial, aleatorio para las filas
	int posicionFilas = aleatorio(1, 5);
	int posicionColumnas = 1;

	for (i = 0; i < 11; i++) {
		asignarPosiciones(mapa, &posicionFilas, &posicionColumnas);
		moverPosicion(mapa, &posicionFilas, &posicionColumnas);
	}
  acomodarMatriz(mapa);

	pantallaMenu();
/*
	mostrarMatriz(mapa);

	saltar(1);
	mapaColores('M',1);
	saltar(1);
	mapaColores('M',2);
	saltar(1);
	mapaColores('M',3);
	saltar(1);
*/
	return 0;
}

int aleatorio(int a, int b){
	int c;
	c = a + rand() % b;
	return c;
}

char letrasAleatorias() {
	switch (aleatorio(1,4)){
		case 1:
			return 'M';
			break;
		case 2:
			return 'A';
			break;
		case 3:
			return 'R';
			break;
		case 4:
			return 'V';
	}
}

void limpiar() {
	system("clear");
}

void saltar(int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("\n");
	}
}

void llenarMatriz(char mapa[FIL][COL]) {
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

void mostrarMatriz(char mapa[FIL][COL]) {
	int i, j;

	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			if (mapa[i][j] == '/') imprimirColor("azul","blanco","▒");
			else if (mapa[i][j] == '-') imprimirColor("","azul"," ");
			else printf("%c", mapa[i][j]);
		}
		saltar(1);
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

void acomodarMatriz(char mapa[FIL][COL]){

  // Acomoda el mapa colocandole guiones - por donde estaban slas /
	int i, j;
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			 if(i >= 1 && i < FIL-1 && j >= 1 && j < COL-1 && mapa[i][j] != 'O')
			   mapa[i][j] = '-';
		}
	}
	// Sustituye las 'O' por letras aleatorias
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			 if(mapa[i][j] == 'O')
			   mapa[i][j] = letrasAleatorias();
		}
	}
}

void imprimirColor(char *colorTexto, char *colorFondo, char *texto) {
  /*
		-Esta funcion recibe tres parametros, el primero es el color del texto, el segundo el el color del fondo y el tercero el el texto a colorear.
		-Si los parametros se encuentran vacios se coloca el color por defecto del terminal
    -Los colores disponibles son: gris, rojo verde, amarillo, azul, rosado, cian, negro, blanco.
    -Si al nombre del color le agregas una c al final ("azul" -> "azulc") vuelve el color mas claro
    -Los parametros (colores) de deben escribir en minusculas y solo el nombre del color, sin espacion u otros caracteres
  */

  // Codiciones colores del texto
  if (colorTexto == "gris") printf("\e[30m");
  if (colorTexto == "rojo") printf("\e[31m");
  if (colorTexto == "verde") printf("\e[32m");
  if (colorTexto == "amarillo") printf("\e[33m");
  if (colorTexto == "azul") printf("\e[34m");
  if (colorTexto == "rosado") printf("\e[35m");
  if (colorTexto == "cian") printf("\e[36m");
  if (colorTexto == "blanco") printf("\e[37m");

  // Colores claros
  if (colorTexto == "negro") printf("\e[0;30m");
  if (colorTexto == "rojoc") printf("\e[0;31m");
  if (colorTexto == "verdec") printf("\e[0;32m");
  if (colorTexto == "amarilloc") printf("\e[0;33m");
  if (colorTexto == "azulc") printf("\e[0;34m");
  if (colorTexto == "rosadoc") printf("\e[0;35m");
  if (colorTexto == "cianc") printf("\e[0;36m");
  if (colorTexto == "blancoc") printf("\e[0;37m");


  // Condiciones colores del fondo
  if (colorFondo == "gris") printf("\e[100m");
  if (colorFondo == "rojo") printf("\e[101m");
  if (colorFondo == "verde") printf("\e[102m");
  if (colorFondo == "amarillo") printf("\e[103m");
  if (colorFondo == "azul") printf("\e[104m");
  if (colorFondo == "rosado") printf("\e[105m");
  if (colorFondo == "cian") printf("\e[106m");
  if (colorFondo == "blanco") printf("\e[107m");

  // Colores claros
  if (colorFondo == "negro") printf("\e[40m");
  if (colorFondo == "rojoc") printf("\e[41m");
  if (colorFondo == "verdec") printf("\e[42m");
  if (colorFondo == "amarilloc") printf("\e[43m");
  if (colorFondo == "azulc") printf("\e[44m");
  if (colorFondo == "rosadoc") printf("\e[45m");
  if (colorFondo == "cianc") printf("\e[46m");
  if (colorFondo == "blancoc") printf("\e[47m");

  // Colorear texto y fondo
  printf("%s", texto);

  // Regresar al color por defecto
  printf("\033[0m");
}

void reproducirAudio(char *nombre) {
	/*
	-Esta funcion recibe el nombre del sonido sin la extension .mp3
	-Bibliotecas usadas, stdlib.h y string.h
	*/
	char *programa = {"mpg123 -q "};
	char *extension = {".mp3"};
	char *comando = malloc(strlen(nombre) + strlen(programa) + strlen(extension));

	strcpy(comando, programa);
	strcat(comando, nombre);
	strcat(comando, extension);

	system(comando);
}

int leerTecla(void) {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr( STDIN_FILENO, &oldattr );
  newattr = oldattr;
  newattr.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
  return ch;
}

void mapaColores(char letra,int fila){

  if(letra == 'R' &&( fila == 1|| fila == 3))
    imprimirColor("rojo","rojo","   ");
	else if (letra == 'R' && fila == 2){
	  imprimirColor("rojo","rojo"," ");
	  imprimirColor("negro","negro"," ");
		imprimirColor("rojo","rojo"," ");
	}
	else if(letra == 'V' &&( fila == 1|| fila == 3))
    imprimirColor("verde","verde","   ");
	else if (letra == 'V' && fila == 2){
	  imprimirColor("verde","verde"," ");
	  imprimirColor("negro","negro"," ");
		imprimirColor("verde","verde"," ");
	}
	else if(letra == 'M' &&( fila == 1|| fila == 3))
    imprimirColor("rosadoc","rosadoc","   ");
	else if (letra == 'M' && fila == 2){
	  imprimirColor("rosadoc","rosadoc"," ");
	  imprimirColor("negro","negro"," ");
		imprimirColor("rosadoc","rosadoc"," ");
	}
	else if(letra == 'A' &&( fila == 1|| fila == 3))
    imprimirColor("azul","azul","   ");
	else if (letra == 'A' && fila == 2){
	  imprimirColor("azul","azul"," ");
	  imprimirColor("negro","negro"," ");
		imprimirColor("azul","azul"," ");
	}
}

void pantallaMenu() {
	int i, j;
	int alto = 20, ancho = 50; // Resolucion de la pantalla del terminal
	for (i = 0; i < alto; i++) {
		for (j = 0; j < ancho; j++) {
			// Perdon por el codigo spaguetti, es que es mas comodo para leer
			// Letra 'M'
			if (i == 2 && j > 2 && j < 4) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 3 && j < 5) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 5 && j < 7) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 6 && j < 8) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 2 && j < 4) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 6 && j < 8) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 4 && j < 6) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 2 && j < 4) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 6 && j < 8) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 2 && j < 4) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 6 && j < 8) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 2 && j < 4) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 6 && j < 8) {imprimirColor("","azul"," ");continue;}
			// Letra 'E'
			if (i == 2 && j > 8 && j < 10) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 9 && j < 11) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 10 && j < 12) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 11 && j < 13) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 8 && j < 10) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 9 && j < 11) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 10 && j < 12) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 8 && j < 10) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 8 && j < 10) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 8 && j < 10) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 9 && j < 11) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 10 && j < 12) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 11 && j < 13) {imprimirColor("","azul"," ");continue;}
			// Letra 'N'
			if (i == 2 && j > 13 && j < 15) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 14 && j < 16) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 18 && j < 20) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 13 && j < 15) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 15 && j < 17) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 18 && j < 20) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 13 && j < 15) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 16 && j < 18) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 18 && j < 20) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 13 && j < 15) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 17 && j < 19) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 18 && j < 20) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 13 && j < 15) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 18 && j < 20) {imprimirColor("","azul"," ");continue;}
			// Letra 'U'
			if (i == 2 && j > 20 && j < 22) {imprimirColor("","azul"," ");continue;}
			if (i == 2 && j > 24 && j < 26) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 20 && j < 22) {imprimirColor("","azul"," ");continue;}
			if (i == 3 && j > 24 && j < 26) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 20 && j < 22) {imprimirColor("","azul"," ");continue;}
			if (i == 4 && j > 24 && j < 26) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 20 && j < 22) {imprimirColor("","azul"," ");continue;}
			if (i == 5 && j > 24 && j < 26) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 21 && j < 23) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 22 && j < 24) {imprimirColor("","azul"," ");continue;}
			if (i == 6 && j > 23 && j < 25) {imprimirColor("","azul"," ");continue;}
			imprimirColor("","blanco"," ");
		}
		saltar(1);
	}
}
