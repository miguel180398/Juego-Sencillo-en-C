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
#include <ctype.h>

#define FIL 7
#define COL 14

int aleatorio(int, int);
char letrasAleatorias();

void limpiar();
void saltar(int);

void llenarMatriz(char [FIL][COL]);
void mostrarMatriz(char [FIL][COL]);
void asignarPosiciones(char [FIL][COL], int *, int *);
void moverPosicion(char [FIL][COL], int *, int *,char *, int * , int *);
void acomodarMatriz(char [FIL][COL]);

void imprimirColor(char *, char *, char *);
void reproducirAudio(char *);

int leerTecla(void);

// Pantallas (interfaz)
void pantallaMenu();

void mostrarMapa(char [FIL][COL]); //nueva

void devolverLetras(char [FIL][COL],int *, int *,char *); // nueva

void convertirMayuscula(char [20][20]);

void nivel1(); //NUEVO

void pantallaPlantilla();
void pantallaCargando();
void pantallaPresentacion();

int main() {


  //pantallaPlantilla();
  //pantallaCargando();
  //pantallaPresentacion();

  nivel1();//NUEVO


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
			return 'B';
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
			//else if (mapa[i][j] == '-') imprimirColor("","azul"," ");
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

void moverPosicion(char mapa[FIL][COL], int *posicionFilas, int *posicionColumnas, char *devolverPosicion, int *coordenadaX, int  *coordenadaY) {

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
          *devolverPosicion = 'D';
          *coordenadaX = i;
          *coordenadaY = j;
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
          *devolverPosicion = 'Q';
          *coordenadaX = i;
          *coordenadaY = j;
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
          *devolverPosicion = 'Q';
          *coordenadaX = i;
          *coordenadaY = j;
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
          *devolverPosicion = 'W';
          *coordenadaX = i;
          *coordenadaY = j;
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
          *devolverPosicion = 'S';
          *coordenadaX = i;
          *coordenadaY = j;
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
	int i, j, k=0;
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			 if(i >= 1 && i < FIL-1 && j >= 1 && j < COL-1 && mapa[i][j] != 'O')
			   mapa[i][j] = '-';
		}
	}
	// Sustituye las 'O' por letras aleatorias
	for (i = 0; i < FIL; i++) {
		for (j = 0; j < COL; j++) {
			 if(mapa[i][j] == 'O'){
			   mapa[i][j]  = letrasAleatorias();
       }
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



void pantallaMenu() {
	int i, j;
	int alto = 24, ancho = 80; // Resolucion de la pantalla del terminal
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
void mostrarMapa(char mapa[FIL][COL]){

	int i, j,fila=1,bajar=1;

	for(i = 0; i < FIL; i++) {
    //espaciar(15);
		printf("               ");
		for(j = 0; j < COL; j++) {
			if (mapa[i][j] == '/') imprimirColor("azul","blanco","▒");
      else if(mapa[i][j]=='A') imprimirColor("azul","azul","♦");
		  else if(mapa[i][j]=='B') imprimirColor("blanco","blanco","♦");
      else if(mapa[i][j]=='R') imprimirColor("rojo","rojo","♦");
			else if(mapa[i][j]=='V') imprimirColor("verde","verde","♦");
			else if(mapa[i][j] == '-') imprimirColor("gris","gris"," ");

		}
   printf("   ");
   if(i == 2){ imprimirColor("negro","amarillo","W: SUBIR     ^ ");
   //espaciar(3);
   printf("   ");
   imprimirColor("negro","azul","A: AZUL   ");}
   if(i== 3){ imprimirColor("negro","cian","S: BAJAR     v ");
   //espaciar(3);
   printf("   ");
   imprimirColor("negro","rojo","R: ROJO   ");}
   if(i== 4){imprimirColor("negro","amarillo","D: DERECHA   > ");
   //espaciar(3);
   printf("   ");
   imprimirColor("negro","blanco","B: BLANCO ");}
   //espaciar(e);
   if(i== 5){imprimirColor("negro","cian","Q: DIAGONAL  / ");
  // espaciar(3);
   printf("   ");
   imprimirColor("negro","verde","V: VERDE  ");}
   saltar(1);

	}

}

void mostrarMapaCoordenadas(char mapa[FIL][COL],int *coordenadaX, int *coordenadaY){

	int i, j,fila=1,bajar=1;

	for(i = 0; i < FIL; i++) {
    //espaciar(15);
		printf("               ");
		for(j = 0; j < COL; j++) {
			if (mapa[i][j] == '/') imprimirColor("azul","blanco","▒");
      else if(i== *coordenadaX && j == *coordenadaY) imprimirColor("cian","negro","☺");
      else if(mapa[i][j]=='A') imprimirColor("azul","azul","♦");
		  else if(mapa[i][j]=='B') imprimirColor("blanco","blanco","♦");
      else if(mapa[i][j]=='R') imprimirColor("rojo","rojo","♦");
			else if(mapa[i][j]=='V') imprimirColor("verde","verde","♦");
			else if(mapa[i][j] == '-') imprimirColor("gris","gris"," ");

		}
   printf("   ");
   if(i == 2){ imprimirColor("negro","amarillo","W: SUBIR     ^ ");
   //espaciar(3);
   printf("   ");
   imprimirColor("negro","azul","A: AZUL   ");}
   if(i== 3){ imprimirColor("negro","cian","S: BAJAR     v ");
   //espaciar(3);
   printf("   ");
   imprimirColor("negro","rojo","R: ROJO   ");}
   if(i== 4){imprimirColor("negro","amarillo","D: DERECHA   > ");
   //espaciar(3);
   printf("   ");
   imprimirColor("negro","blanco","B: BLANCO ");}
   //espaciar(e);
   if(i== 5){imprimirColor("negro","cian","Q: DIAGONAL  / ");
  // espaciar(3);
   printf("   ");
   imprimirColor("negro","verde","V: VERDE  ");}
   saltar(1);

	}

}

void devolverLetras(char mapa[FIL][COL], int *coordenaX, int *coordenadaY,char *letras){

  int i,j,k;

  for(k=0;k<11;k++){
    for (i = 0; i < FIL; i++) {
		  for (j = 0; j < COL; j++) {
			  if(coordenaX[k] == i && coordenadaY[k] == j){
			    letras[k] = mapa[i][j];
        }
		  }
	  }
  }
}


void nivel1(){

  limpiar();

	int i,j,k=0,coordenadaX[11],coordenadaY[11]; //nueva
	char mapa[FIL][COL], direcciones[11],letras[11],compararLetras[10][3],compararPalabras[10][20],compararResultados[10][20],guardar[10][20]; // nueva

	srand(time(NULL)); // Generar semilla para todo el programa

	llenarMatriz(mapa);

	// Posicion incial, aleatorio para las filas
	int posicionFilas = aleatorio(1, 5);
	int posicionColumnas = 1;
  int posicionX = posicionFilas;
  int posicionY = 1;

	for (i = 0; i < 11; i++) {
		asignarPosiciones(mapa, &posicionFilas, &posicionColumnas);
		moverPosicion(mapa, &posicionFilas, &posicionColumnas,&direcciones[i],&coordenadaX[i],&coordenadaY[i]);
	}

  acomodarMatriz(mapa);
  devolverLetras(mapa,coordenadaX, coordenadaY,letras); // se encarga de devolver el color en cada posicion de la matriz



	//pantallaMenu();
  //mostrarMatriz(mapa);


  //concatena las letras
  for(i=0;i<10;i++){
      compararLetras[i][0] = direcciones[i];
  }

  for(i=0;i<10;i++){
     compararLetras[i][1] = letras[i];
     compararLetras[i][2] = '\0';
  }
  //imprimir resultado de las letras
  /*for(i=0;i<10;i++){
    printf("%s ",compararLetras[i]);
  }*/
 // printf("\n");
  //concatena palabras;
  for(i=0;i<10;i++){
    if(direcciones[i] == 'W'){
      strcpy(compararPalabras[i],"SUBIR");
    }
    else if(direcciones[i] == 'S'){
      strcpy(compararPalabras[i],"BAJAR");
    }
    else if(direcciones[i] == 'D'){
      strcpy(compararPalabras[i],"DERECHA");
    }
    else if(direcciones[i] == 'Q'){
      strcpy(compararPalabras[i],"DIAGONAL");
    }
  }
  for(i=0; i<10;i++){
    if(letras[i] == 'A'){
      strcat(compararPalabras[i],"AZUL");
    }
    else if(letras[i] == 'R'){
      strcat(compararPalabras[i],"ROJO");
    }
    else if(letras[i] == 'B'){
      strcat(compararPalabras[i],"BLANCO");
    }
    else if(letras[i] == 'V'){
      strcat(compararPalabras[i],"VERDE");
    }
  }
  //imprime resultado de las palabras
  /*for(i=0;i<10;i++){
    printf("%s \n",compararPalabras[i]);
  }*/

  saltar(1);
	mostrarMapaCoordenadas(mapa,&posicionX,&posicionY);

  //almacenar datos
  for(i=0;i<10;i++){
    imprimirColor("negro","blanco","Intruduzca la Instruccion");
    printf("(%d/%d):",i+1,10);
    scanf("%[^\n]",guardar[i]);
    getchar();
  }
  //quita espacios
  for(i=0;i<10;i++){
    for(j=0;guardar[i][j]!='\0';j++){
      if(guardar[i][j]!=' '){
       compararResultados[i][k] =  guardar[i][j];
       k++;
      }
    }
    compararResultados[i][k] = '\0';
    k=0;
  }
  //convierte en mayuscula
  for(i=0;i<10;i++){
    for(j=0;compararResultados[i][j]!='\0';j++){
      compararResultados[i][j] = compararResultados[i][j]-32;
    }
  }

  for(i=0;i<10;i++){
    printf("%s\n",compararResultados[i]);

  }

  // compara la decision
  char decision = 'v', decision2 = 'v';
  for(i=0;i<10;i++){
    for(j=0;compararResultados[i][j]!='\0';j++){

      if(compararResultados[i][j] == compararPalabras[i][j]||compararResultados[i][j] == compararLetras[i][j]){
        decision = 'v';
      }
      else{
        decision = 'f';
        break;
      }
    }
    if(decision == 'f') break;
  }

  limpiar();
  if(decision == 'v'){

   for(i=0;i<10;i++){
     mostrarMapaCoordenadas(mapa,&coordenadaX[i],&coordenadaY[i]);
     sleep(1);
     limpiar();
   }
  }
  else
   printf("perdiste");
}

void pantallaPlantilla() {
  limpiar();

	int i, j;

  // Resolucion de la pantalla del terminal
	int alto = 24, ancho = 80;

  // Psocion del texto en la pantalla
  int posi = 1, posj = 1;

	for (i = 0; i < alto; i++) {
		for (j = 0; j < ancho; j++) {
  // ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  // Letras ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  // ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  {
      // Letra 'A'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
			if (i == posi && j == posj) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 1) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 2) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 1) {imprimirColor("azul","blanco","■");continue;}
      if (i == posi + 1 && j == posj + 2) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 2) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'B'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 4) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 5) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 6) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 1 && j == posj + 4) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 5) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 6) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 4) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 5) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 6) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'C'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 8) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 9) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 10) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 8) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 10) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 2 && j == posj + 8) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 9) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 10) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'D'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 12) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 13) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 14) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 1 && j == posj + 12) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 14) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 12) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 13) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 14) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'E'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 16) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 17) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 18) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 16) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 17) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 16) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 17) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 18) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'F'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 20) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 21) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 22) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 20) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 21) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 20) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'G'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 24) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 25) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 26) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 24) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 26) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 24) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 25) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 26) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'H'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 28) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 30) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 28) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 29) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 30) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 28) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 30) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'I'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 32) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 33) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 34) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 33) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 32) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 33) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 34) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'J'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 36) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 37) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 38) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 37) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 36) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 37) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'K'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 40) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 42) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 40) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 42) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 1 && j == posj + 41) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 40) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 42) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'L'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 44) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 44) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 44) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 45) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 46) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'M'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌
      if (i == posi && j == posj + 48) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi && j == posj + 49) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi && j == posj + 50) {imprimirColor("azul","blanco","▌");continue;}
      if (i == posi + 1 && j == posj + 48) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 49) {imprimirColor("azul","blanco","▌");continue;}
      if (i == posi + 1 && j == posj + 50) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 48) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 50) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'N'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 52) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 53) {imprimirColor("azul","blanco","▌");continue;}
      if (i == posi && j == posj + 54) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 52) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 53) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 1 && j == posj + 54) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 52) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 54) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'O'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 56) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 57) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 58) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 56) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 58) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 56) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 57) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 58) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'P'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 60) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 61) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 62) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 60) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 61) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 62) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 60) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'Q'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 64) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 65) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 66) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 64) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 66) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 2 && j == posj + 64) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 65) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 66) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'R'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 68) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 69) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 70) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 68) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 69) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 70) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 68) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 70) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'S'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 72) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi && j == posj + 73) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 74) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 72) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 73) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 74) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 72) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 73) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'T'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 1) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 2) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 1) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 1) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'U'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 4) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 6) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 6) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 4) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 4) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 5) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 6) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'V'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 8) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 10) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 4 && j == posj + 9) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 10) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 5 && j == posj + 10) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'W'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 12) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 14) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 3 && j == posj + 15) {imprimirColor("azul","blanco","▌");continue;}
      if (i == posi + 3 && j == posj + 17) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 13) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 14) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 4 && j == posj + 15) {imprimirColor("azul","blanco","▌");continue;}
      if (i == posi + 4 && j == posj + 16) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 14) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 15) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'X'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 19) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 21) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 20) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 19) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 21) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'y'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 23) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 25) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 24) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 24) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'Z'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 27) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 28) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 29) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 27) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 5 && j == posj + 27) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 28) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 28) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 29) {imprimirColor("azul","blanco","▀");continue;}
  }

  // ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  // Numeros ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  // ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  {
      // Letra '1'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 31) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 3 && j == posj + 32) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 32) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 31) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 32) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 33) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '2'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 35) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 36) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 37) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 35) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 36) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 37) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 35) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 36) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 37) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '3'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 39) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 40) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 41) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 39) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 40) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 41) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 39) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 40) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 41) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '4'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 43) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 45) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 43) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 44) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 45) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 45) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '5'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 47) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 48) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 49) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 47) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 48) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 49) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 47) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 48) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 49) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '6'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 51) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 52) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 53) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 51) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 52) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 53) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 51) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 52) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 53) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '7'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 55) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 56) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 57) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 56) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 56) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '8'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 59) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 60) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 61) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 59) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 60) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 61) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 59) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 60) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 61) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '9'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 63) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 64) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 65) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 63) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 64) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 4 && j == posj + 65) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 65) {imprimirColor("azul","blanco","▀");continue;}

      // Letra '0'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 67) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 3 && j == posj + 68) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 3 && j == posj + 69) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 67) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 69) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 67) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 68) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 5 && j == posj + 69) {imprimirColor("azul","blanco","▀");continue;}

      // Letra ''
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 1) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 4 && j == posj + 1) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 5 && j == posj + 1) {imprimirColor("azul","blanco","▀");continue;}
  }

			imprimirColor("","blanco"," ");
    }
		saltar(1);
	}
}

void pantallaCargando() {
  limpiar();

	int i, j, k;
	int alto = 24, ancho = 80; // Resolucion de la pantalla del terminal
  int posi = 5, posj = 24; // Psocion del texto en la pantalla

  for (k = 0; k <= 29; k++) {
  for (i = 0; i < alto; i++) {
		for (j = 0; j < ancho; j++) {

      // Letra 'C'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 1) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 2) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 2) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 2 && j == posj) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 1) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 2) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'A'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
			if (i == posi && j == posj + 4) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 5) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 6) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 4) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 5) {imprimirColor("azul","blanco","■");continue;}
      if (i == posi + 1 && j == posj + 6) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 4) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 6) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'R'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 8) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 9) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 10) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 8) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 9) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 10) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 8) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 10) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'G'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 12) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 13) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 14) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 1 && j == posj + 12) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 14) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 12) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 13) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 14) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'A'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
			if (i == posi && j == posj + 16) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 17) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 18) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 16) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 17) {imprimirColor("azul","blanco","■");continue;}
      if (i == posi + 1 && j == posj + 18) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 16) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 18) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'N'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 20) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 21) {imprimirColor("azul","blanco","▌");continue;}
      if (i == posi && j == posj + 22) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 20) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 21) {imprimirColor("azul","blanco","▐");continue;}
      if (i == posi + 1 && j == posj + 22) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 20) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 22) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'D'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 24) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 25) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 26) {imprimirColor("azul","blanco","▄");continue;}
      if (i == posi + 1 && j == posj + 24) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 26) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 24) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 25) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 26) {imprimirColor("azul","blanco","▀");continue;}

      // Letra 'O'
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi && j == posj + 28) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi && j == posj + 29) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi && j == posj + 30) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 28) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 1 && j == posj + 30) {imprimirColor("azul","blanco","█");continue;}
      if (i == posi + 2 && j == posj + 28) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 29) {imprimirColor("azul","blanco","▀");continue;}
      if (i == posi + 2 && j == posj + 30) {imprimirColor("azul","blanco","▀");continue;}

      // Barra de carga
      // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
      if (i == posi + 3 && j == posj + 1) {
        if (k > 0)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 2) {
        if (k > 1)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 3) {
        if (k > 2)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 4) {
        if (k > 3)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 5) {
        if (k > 4)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 6) {
        if (k > 5)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 7) {
        if (k > 6)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 8) {
        if (k > 7)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 9) {
        if (k > 8)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 10) {
        if (k > 9)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 11) {
        if (k > 10)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 12) {
        if (k > 11)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 13) {
        if (k > 12)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 14) {
        if (k > 13)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 15) {
        if (k > 14)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 16) {
        if (k > 15)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 17) {
        if (k > 16)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 18) {
        if (k > 17)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 19) {
        if (k > 18)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 20) {
        if (k > 19)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 21) {
        if (k > 20)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 22) {
        if (k > 21)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 23) {
        if (k > 22)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 24) {
        if (k > 23)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 25) {
        if (k > 24)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 26) {
        if (k > 25)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 27) {
        if (k > 26)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 28) {
        if (k > 27)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }
      if (i == posi + 3 && j == posj + 29) {
        if (k > 28)
          imprimirColor("azul","blanco","█");
        else
          imprimirColor("azul","blanco","▒");
        continue;
      }

      imprimirColor("","blanco"," ");
    }
    saltar(1);
  }
  usleep(200*1000);
  limpiar();
  }
}

void pantallaPresentacion() {
  limpiar();

	int i, j, k;
	int alto = 24, ancho = 80; // Resolucion de la pantalla del terminal
  int posi = 9, posj = 14; // Psocion del texto en la pantalla

  char *color; // Color que varia k veces

  for (k = 0; k <= 4; k++) {

    if (k == 0) color = "verde";
    if (k == 1) color = "azul";
    if (k == 2) color = "rojo";
    if (k == 3) color = "amarillo";
    if (k == 4) color = "rosado";

    for (i = 0; i < alto; i++) {
      for (j = 0; j < ancho; j++) {

        // Letra 'S'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj) {imprimirColor(color,"blanco","▄");continue;}
        if (i == posi && j == posj + 1) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 2) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj + 1) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj + 2) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 1) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'M'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌
        if (i == posi && j == posj + 4) {imprimirColor(color,"blanco","▐");continue;}
        if (i == posi && j == posj + 5) {imprimirColor(color,"blanco","▐");continue;}
        if (i == posi && j == posj + 6) {imprimirColor(color,"blanco","▌");continue;}
        if (i == posi + 1 && j == posj + 4) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 5) {imprimirColor(color,"blanco","▌");continue;}
        if (i == posi + 1 && j == posj + 6) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 4) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 6) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'A'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
  			if (i == posi && j == posj + 8) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 9) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 10) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 8) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 9) {imprimirColor(color,"blanco","■");continue;}
        if (i == posi + 1 && j == posj + 10) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 8) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 10) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'R'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 12) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 13) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 14) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 12) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 13) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 14) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 12) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 14) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'T'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 16) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 17) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 18) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj + 17) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 17) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'M'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌
        if (i == posi && j == posj + 24) {imprimirColor(color,"blanco","▐");continue;}
        if (i == posi && j == posj + 25) {imprimirColor(color,"blanco","▐");continue;}
        if (i == posi && j == posj + 26) {imprimirColor(color,"blanco","▌");continue;}
        if (i == posi + 1 && j == posj + 24) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 25) {imprimirColor(color,"blanco","▌");continue;}
        if (i == posi + 1 && j == posj + 26) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 24) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 26) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'A'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
  			if (i == posi && j == posj + 28) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 29) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 30) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 28) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 29) {imprimirColor(color,"blanco","■");continue;}
        if (i == posi + 1 && j == posj + 30) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 28) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 30) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'C'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 32) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 33) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 34) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 32) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 34) {imprimirColor(color,"blanco","▄");continue;}
        if (i == posi + 2 && j == posj + 32) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 33) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 34) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'H'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 36) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 38) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 36) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 37) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj + 38) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 36) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 38) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'I'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 40) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 41) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 42) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj + 41) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 40) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 41) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 42) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'N'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 44) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 45) {imprimirColor(color,"blanco","▌");continue;}
        if (i == posi && j == posj + 46) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 44) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 45) {imprimirColor(color,"blanco","▐");continue;}
        if (i == posi + 1 && j == posj + 46) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 2 && j == posj + 44) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 46) {imprimirColor(color,"blanco","▀");continue;}

        // Letra 'E'
        // ░ ▒ ▓ ▲ ▼ ► ◄ ■ █ ▀ ▄ ▌ ▐
        if (i == posi && j == posj + 48) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi && j == posj + 49) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi && j == posj + 50) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 1 && j == posj + 48) {imprimirColor(color,"blanco","█");continue;}
        if (i == posi + 1 && j == posj + 49) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 48) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 49) {imprimirColor(color,"blanco","▀");continue;}
        if (i == posi + 2 && j == posj + 50) {imprimirColor(color,"blanco","▀");continue;}

        imprimirColor("","blanco"," ");
      }
      saltar(1);
    }
    sleep(1);
    limpiar();
  }
}
