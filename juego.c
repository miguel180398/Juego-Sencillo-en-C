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

int main() {

	/*limpiar();

	int i,j,coordenadaX[11],coordenadaY[11]; //nueva
	char mapa[FIL][COL], posiciones[11],letra[11]; // nueva

	srand(time(NULL)); // Generar semilla para todo el programa

	llenarMatriz(mapa);

	// Posicion incial, aleatorio para las filas
	int posicionFilas = aleatorio(1, 5);
	int posicionColumnas = 1;


	for (i = 0; i < 11; i++) {
		asignarPosiciones(mapa, &posicionFilas, &posicionColumnas);
		moverPosicion(mapa, &posicionFilas, &posicionColumnas,&posiciones[i],&coordenadaX[i],&coordenadaY[i]);
	}
  acomodarMatriz(mapa);
  
  devolverLetras(mapa,coordenadaX, coordenadaY,letra); // se encarga de devolver el color en cada posicion de la matriz
  for (i = 0; i < 10; i++){

		printf("%c ",posiciones[i]); // nueva 
	}
  printf("\n");
  for (i = 0; i < 10; i++){
		printf("%c ",letra[i]); // nueva 
	}
  printf("\n");
	//pantallaMenu();
  mostrarMatriz(mapa);
	saltar(1);
	mostrarMapa(mapa);*/


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
		  else if(mapa[i][j]=='B') imprimirColor("blanco","blanco","☺");
      else if(mapa[i][j]=='R') imprimirColor("rojo","rojo","☼");
			else if(mapa[i][j]=='V') imprimirColor("verde","verde","♣");
			else if(mapa[i][j] == '-') imprimirColor("gris","gris","■");

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
	mostrarMapa(mapa);
  //almacenar datos
  for(i=0;i<10;i++){
    printf("intruduzca la instruccion(%d/%d)",i+1,10);
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
  if(decision == 'v')
   printf("ganaste");
  else
   printf("perdiste");
}
