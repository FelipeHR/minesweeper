#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

enum estados {covered = 0, uncover = 1, flag = 2, doubt = 3};

void contarMinas(int n, int m, char ** campo) {
    int i, j, count;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (campo[i][j] == 0){
                count = 0;
                if (i == 0) {
                    if (j == 0) {//esquina superior izq-----------------------------
                        if (campo[i + 1][j] == -1) count++;//abajo
                        if (campo[i + 1][j + 1] == -1) count++;//diagonal dn-der
                        if (campo[i][j + 1] == -1) count++;//derecha
                    } else if (j == (m-1)) {//esquina superior der------------------
                        if (campo[i + 1][j] == -1) count++;//abajo
                        if (campo[i + 1][j - 1] == -1) count++;//diagonal dn-izq
                        if (campo[i][j - 1] == -1) count++;//izquierda
                    } else {//borde superior----------------------------------------
                        if (campo[i][j + 1] == -1) count++;//derecha
                        if (campo[i + 1][j + 1] == -1) count++;//diagonal dn-der
                        if (campo[i + 1][j] == -1) count++;//abajo
                        if (campo[i + 1][j - 1] == -1) count++;//diagonal dn-izq
                        if (campo[i][j - 1] == -1) count++;//izquierda
                    }

                } else if (i == n-1) {
                    if (j == 0) { //esquina inferior izq----------------------------
                        if (campo[i - 1][j] == -1) count++;//arriba
                        if (campo[i - 1][j + 1] == -1) count++;//diagonal up-der
                        if (campo[i][j + 1] == -1) count++;//derecha
                    } else  if (j == m-1) { //esquina inferior der-------------------
                        if (campo[i - 1][j] == -1) count++;//arriba
                        if (campo[i - 1][j - 1] == -1) count++;//diagonal up-izq
                        if (campo[i][j - 1] == -1) count++;//izquierda
                    } else { //borde inferior---------------------------------------
                        if (campo[i][j + 1] == -1) count++;//derecha
                        if (campo[i - 1][j + 1] == -1) count++;//diagonal up-der
                        if (campo[i - 1][j] == -1) count++;//arriba
                        if (campo[i - 1][j - 1] == -1) count++;//diagonal up-izq
                        if (campo[i][j - 1] == -1) count++;//izquierda
                    }
                } else {
                    if (j == 0) { //borde izq----------------------------------------
                        if (campo[i - 1][j] == -1) count++;//arriba
                        if (campo[i - 1][j + 1] == -1) count++;//diagonal up-der
                        if (campo[i][j + 1] == -1) count++;//derecha
                        if (campo[i + 1][j + 1] == -1) count++;//diagonal dn-izq
                        if (campo[i + 1][j] == -1) count++;//abajo
                    } else if (j == m-1) { //borde der-------------------------------
                        if (campo[i - 1][j] == -1) count++;//arriba
                        if (campo[i - 1][j - 1] == -1) count++;//diagonal up-izq
                        if (campo[i][j - 1] == -1) count++;//izquierda
                        if (campo[i + 1][j - 1] == -1) count++;//diagonal dn-izq
                        if (campo[i + 1][j] == -1) count++;//abajo
                    } else { //general inner cell
                        if (campo[i - 1][j] == -1) count++;//arriba
                        if (campo[i - 1][j - 1] == -1) count++;//diagonal up-izq
                        if (campo[i][j - 1] == -1) count++;//izquierda
                        if (campo[i + 1][j - 1] == -1) count++;//diagonal dn-izq
                        if (campo[i + 1][j] == -1) count++;//abajo
                        if (campo[i + 1][j + 1] == -1) count++;//diagonal dn-der
                        if (campo[i][j + 1] == -1) count++;//derecha
                        if (campo[i - 1][j + 1] == -1) count++;//diagonal up-der
                    }
                }
                campo[i][j] = count;
            }

        }
    }

}


char ** crearCampo(int n, int m) {
    char ** campo;
    int i,j;
    campo = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; ++i) {
        campo[i] = (char *)malloc(m * sizeof(char));
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            campo[i][j] = 0;
        }
    }

    return campo;
}

void rellenador(int n, int m, char ** campo, int semilla, int minas) {
    int i, j, k,l=1;
    int step = 0;
    int roll, flag;

    srand(semilla);
    for (k = 0; k < minas; ++k){
        flag = 0;
        step = 0;
        roll = rand() % (n * m);
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                step++;
                if (step == roll) {

                    if (campo[i][j] == -1) {
                        flag = 1;
                        k--;
                        break;
                    } else {
                        campo[i][j] = -1;
                        flag =1;
                        break;
                    }

                }
            }
            if (flag) break;
        }
    }
    k = 0;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (campo[i][j] == -1) k++;
        }
    }

    while(minas!=k){
        srand(semilla*l);
        i=rand()%n;
        j=rand()%m;
        if(campo[i][j]!=-1){
            campo[i][j]=-1;
            k++;
        }
        l++;
    }

}

void showCell(int i, int j, int n, int m, char **cover, char **campo) {
    cover[i][j] = uncover;//uncover

    if (campo[i][j] == 0) {
        if (i == 0) {
            if (j == 0) {//esquina superior izq-----------------------------
                if (campo[i + 1][j] == 0 && cover[i + 1][j] != uncover) showCell(i + 1, j, n, m, cover, campo);//abajo
                if (campo[i + 1][j + 1] == 0 && cover[i + 1][j + 1] != uncover) showCell(i + 1, j + 1, n, m, cover, campo);//diagonal dn-der
                if (campo[i][j + 1] == 0 && cover[i][j + 1] != uncover) showCell( i, j + 1, n, m, cover, campo);//derecha

                cover[i + 1][j] = uncover; //abajo
                cover[i + 1][j + 1] = uncover; //diagonal dn-der
                cover[i][j + 1] = uncover; //derecha
                if (campo[i][j] == 0) {
                }
            } else if (j == (m-1)) {//esquina superior der------------------
                if (campo[i + 1][j] == 0 && cover[i + 1][j] != uncover) showCell(i + 1, j, n, m, cover, campo);//abajo
                if (campo[i + 1][j - 1] == 0 && cover[i + 1][j - 1] != uncover) showCell(i + 1, j - 1, n, m, cover, campo);//diagonal dn-izq
                if (campo[i][j - 1] == 0 && cover[i][j - 1] != uncover) showCell(i, j - 1, n, m, cover, campo);//izquierda

                cover[i + 1][j] = uncover; //abajo
                cover[i + 1][j - 1] = uncover; //diagonal dn-izq
                cover[i][j - 1] = uncover; //izquierda
            } else {//borde superior----------------------------------------
                if (campo[i][j + 1] == 0 && cover[i][j + 1] != uncover) showCell(i, j + 1, n, m, cover, campo);//derecha
                if (campo[i + 1][j + 1] == 0 && cover[i + 1][j + 1] != uncover) showCell(i + 1, j + 1, n, m, cover, campo);//diagonal dn-der
                if (campo[i + 1][j] == 0 && cover[i + 1][j] != uncover) showCell(i + 1, j, n, m, cover, campo);//abajo
                if (campo[i + 1][j - 1] == 0 && cover[i + 1][j - 1] != uncover) showCell(i + 1, j - 1, n, m, cover, campo);//diagonal dn-izq
                if (campo[i][j - 1] == 0 && cover[i][j - 1] != uncover) showCell(i, j - 1, n, m, cover, campo);//izquierda

                cover[i][j + 1] = uncover; //derecha
                cover[i + 1][j + 1] = uncover; //diagonal dn-der
                cover[i + 1][j] = uncover; //abajo
                cover[i + 1][j - 1] = uncover; //diagonal dn-izq
                cover[i][j - 1] = uncover; //izquierda
            }
        } else if (i == n-1) {
            if (j == 0) { //esquina inferior izq----------------------------
                if (campo[i - 1][j] == 0 && cover[i - 1][j] != uncover) showCell(i - 1, j, n, m, cover, campo);//arriba
                if (campo[i - 1][j + 1] == 0 && cover[i - 1][j + 1] != uncover) showCell(i - 1, j + 1, n, m, cover, campo);//diagonal up-der
                if (campo[i][j + 1] == 0 && cover[i][j + 1] != uncover) showCell(i, j + 1, n, m, cover, campo);//derecha

                cover[i - 1][j] = uncover; //arriba
                cover[i - 1][j + 1] = uncover; //diagonal up-der
                cover[i][j + 1] = uncover; //derecha
            } else  if (j == m-1) { //esquina inferior der-------------------
                if (campo[i - 1][j] == 0 && cover[i - 1][j] != uncover) showCell(i - 1, j, n, m, cover, campo);//arriba
                if (campo[i - 1][j - 1] == 0 && cover[i - 1][j - 1] != uncover) showCell(i - 1, j - 1, n, m, cover, campo);//diagonal up-izq
                if (campo[i][j - 1] == 0 && cover[i][j - 1] != uncover) showCell(i, j - 1, n, m, cover, campo);//izquierda

                cover[i - 1][j] = uncover; //arriba
                cover[i - 1][j - 1] = uncover; //diagonal up-izq
                cover[i][j - 1] = uncover; //izquierda
            } else { //borde inferior---------------------------------------
                if (campo[i][j + 1] == 0 && cover[i][j + 1] != uncover) showCell(i, j + 1, n, m, cover, campo);//derecha
                if (campo[i - 1][j + 1] == 0 && cover[i - 1][j + 1] != uncover) showCell(i - 1, j + 1, n, m, cover, campo);//diagonal up-der
                if (campo[i - 1][j] == 0 && cover[i - 1][j] != uncover) showCell(i - 1, j, n, m, cover, campo);//arriba
                if (campo[i - 1][j - 1] == 0 && cover[i - 1][j - 1] != uncover) showCell(i - 1, j - 1, n, m, cover, campo);//diagonal up-izq
                if (campo[i][j - 1] == 0 && cover[i][j - 1] != uncover) showCell(i, j - 1, n, m, cover, campo);//izquierda

                cover[i][j + 1] = uncover; //derecha
                cover[i - 1][j + 1] = uncover; //diagonal up-der
                cover[i - 1][j] = uncover; //arriba
                cover[i - 1][j - 1] = uncover; //diagonal up-izq
                cover[i][j - 1] = uncover; //izquierda
            }
        } else {
            if (j == 0) { //borde izq----------------------------------------
                if (campo[i - 1][j] == 0 && cover[i - 1][j] != uncover) showCell(i - 1, j, n, m, cover, campo);//arriba
                if (campo[i - 1][j + 1] == 0 && cover[i - 1][j + 1] != uncover) showCell(i - 1, j + 1, n, m, cover, campo);//diagonal up-der
                if (campo[i][j + 1] == 0 && cover[i][j + 1] != uncover) showCell(i, j + 1, n, m, cover, campo);//derecha
                if (campo[i + 1][j + 1] == 0 && cover[i + 1][j + 1] != uncover) showCell(i + 1, j + 1, n, m, cover, campo);//diagonal dn-izq
                if (campo[i + 1][j] == 0 && cover[i + 1][j] != uncover) showCell(i + 1, j, n, m, cover, campo);//abajo

                cover[i - 1][j] = uncover; //arriba
                cover[i - 1][j + 1] = uncover; //diagonal up-der
                cover[i][j + 1] = uncover; //derecha
                cover[i + 1][j + 1] = uncover; //diagonal dn-der
                cover[i + 1][j] = uncover; //abajo
            } else if (j == m-1) { //borde der-------------------------------
                if (campo[i - 1][j] == 0 && cover[i - 1][j] != uncover) showCell(i - 1, j, n, m, cover, campo);//arriba
                if (campo[i - 1][j - 1] == 0 && cover[i - 1][j - 1] != uncover) showCell(i - 1, j - 1, n, m, cover, campo);//diagonal up-izq
                if (campo[i][j - 1] == 0 && cover[i][j - 1] != uncover) showCell(i, j - 1, n, m, cover, campo);//izquierda
                if (campo[i + 1][j - 1] == 0 && cover[i + 1][j - 1] != uncover) showCell(i + 1, j - 1, n, m, cover, campo);//diagonal dn-izq
                if (campo[i + 1][j] == 0 && cover[i + 1][j] != uncover) showCell(i + 1, j, n, m, cover, campo);//abajo

                cover[i - 1][j] = uncover; //arriba
                cover[i - 1][j - 1] = uncover; //diagonal up-izq
                cover[i][j - 1] = uncover; //izquierda
                cover[i + 1][j - 1] = uncover; //diagonal dn-izq
                cover[i + 1][j] = uncover; //abajo
            } else { //general inner cell------------------------------------
                if (campo[i - 1][j] == 0 && cover[i - 1][j] != uncover) showCell(i - 1, j, n, m, cover, campo);//arriba
                if (campo[i - 1][j - 1] == 0 && cover[i - 1][j - 1] != uncover) showCell(i - 1, j - 1, n, m, cover, campo);//diagonal up-izq
                if (campo[i][j - 1] == 0 && cover[i][j - 1] != uncover) showCell(i, j - 1, n, m, cover, campo);//izquierda
                if (campo[i + 1][j - 1] == 0 && cover[i + 1][j - 1] != uncover) showCell(i + 1, j - 1, n, m, cover, campo);//diagonal dn-izq
                if (campo[i + 1][j] == 0 && cover[i + 1][j] != uncover) showCell(i + 1, j, n, m, cover, campo);//abajo
                if (campo[i + 1][j + 1] == 0 && cover[i + 1][j + 1] != uncover) showCell(i + 1, j + 1, n, m, cover, campo);//diagonal dn-der
                if (campo[i][j + 1] == 0 && cover[i][j + 1] != uncover) showCell(i, j + 1, n, m, cover, campo);//derecha
                if (campo[i - 1][j + 1] == 0 && cover[i - 1][j + 1] != uncover) showCell(i - 1, j + 1, n, m, cover, campo);//diagonal up-der

                cover[i - 1][j] = uncover; //arriba
                cover[i - 1][j - 1] = uncover; //diagonal up-izq
                cover[i][j - 1] = uncover; //izquierda
                cover[i + 1][j - 1] = uncover; //diagonal dn-izq
                cover[i + 1][j] = uncover; //abajo
                cover[i + 1][j + 1] = uncover; //diagonal dn-der
                cover[i][j + 1] = uncover; //derecha
                cover[i - 1][j + 1] = uncover; //diagonal up-der
            }
        }

    }
}

int checkWin(int n, int m, char **cover, int minas) {
    int i, j;
    int descubiertas = 0;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (cover[i][j] == 1) descubiertas++;
        }
    }
    if (((n*m) - descubiertas) == minas) return 1;
    else return 0;
}
void moverMina(int n, int m, char **campo, int x, int y) {
    int i,j,bandera=0;
    for(i = 0; i < n; i++) {
        for(j = 0;j < m; j++) {
            if(campo[i][j]==0) {
                campo[i][j]=-1;
                bandera=1;
                break; //colocar la mina en la primera casilla disponible
            }
        }
        if(bandera)
            break;
    }
    campo[x][y]=0; //quitar la mina de su posici�n inicial
}
Uint32 get_color(SDL_Surface *s, Uint32 r, Uint32 g, Uint32 b){
    return SDL_MapRGB(s->format, r, g, b);
}
int primerTurno(int n, int m, char **cover) {
    int i, j, contador=0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(cover[i][j]!=uncover) {
                contador++;
            }
        }
    }
    if(contador==n*m) {
        return 1;
    } else return 0;
}
void saveGame (int n, int m, char **campo, char **cover, int elapsedTime) {
    FILE * fp;
    int i, j;

    fp = fopen ("saveGame.txt", "w");

    fprintf (fp, "%2d %2d\n", n, m);
    for(i = 0; i < n; ++i){
        for (j = 0; j < m; ++j) {
            fprintf (fp, "%2d ", campo[i][j]);
        }
        fprintf (fp, "\n");
    }
    fprintf (fp, "\n");

    for(i = 0; i < n; ++i){
        for (j = 0; j < m; ++j) {
            fprintf (fp, "%2d ", cover[i][j]);
        }
        fprintf (fp, "\n");
    }
    fprintf(fp, "\n");
    fprintf(fp, "%d\n", elapsedTime);

    fclose (fp);
}
void loadGame(int *n, int *m, char ***campo, char ***cover, int *elapsedTime, int *minas) {
    FILE * fp;
    int i, j;
    (*minas) = 0;
    fp = fopen("saveGame.txt","r");
    fscanf(fp, "%d %d", n, m);
    *campo = crearCampo(*n, *m);
    *cover = crearCampo(*n, *m);

    for (i = 0; i < *n; i++) {
        for (j = 0; j < *m; j++) {
            fscanf(fp, "%d", &(*campo)[i][j]);
            if ((*campo)[i][j] == -1) {
                (*minas)++;
            }
        }
    }

    for (i = 0; i < *n; ++i) {
        for (j = 0; j < *m; ++j) {
            fscanf(fp, "%d", &(*cover)[i][j]);
        }
    }
    fscanf(fp, "%d", elapsedTime);

    fclose(fp);
}

void contadores(int contadorMinas, int n ,SDL_Surface *contadorM[n]){
    int contadorDigito,contadorModulo;
    int i;
    SDL_Surface *contador[10];
    contador[0]=SDL_LoadBMP("contador/0c.bmp");
    contador[1]=SDL_LoadBMP("contador/1c.bmp");
    contador[2]=SDL_LoadBMP("contador/2c.bmp");
    contador[3]=SDL_LoadBMP("contador/3c.bmp");
    contador[4]=SDL_LoadBMP("contador/4c.bmp");
    contador[5]=SDL_LoadBMP("contador/5c.bmp");
    contador[6]=SDL_LoadBMP("contador/6c.bmp");
    contador[7]=SDL_LoadBMP("contador/7c.bmp");
    contador[8]=SDL_LoadBMP("contador/8c.bmp");
    contador[9]=SDL_LoadBMP("contador/9c.bmp");
    contadorModulo=contadorMinas;
    for(i=0;i<3;i++){
        contadorDigito=contadorModulo%10;
        contadorM[i]= contador[contadorDigito];
        contadorModulo/=10;
    }
}


int getTime(int startTime) {
    return (time(NULL) - startTime);
}
int opcionUsada(int n,int m,int minas){
  if(minas==10 && n==9 && m==9)
    return 1;
  else if(minas==40 && n==16 && m==16)
    return 2;
  else if(minas==99 && n==22 && m==16)
    return 3;
  else
    return 4;
}
void saveScore (char *userName, int elapsedTime, char diff) {
    FILE * fp;
    int cant, i, j, k;
    char **names;
    int *scores;
    int auxi;
    char auxc;
    char file[] = "scores_.txt";
    file[6] = '0' + diff;

    fp = fopen(file, "r");
    fscanf (fp, "%d", &cant); //la primera linea del archivo contendra la cantidad de puntajes
    fclose(fp);

    if (cant) { //si existen puntajes anteriores habra que reordenar la lista, de mayor a menor.
        //añadir puntaje al final de la lista
        fp = fopen(file, "a");
        fprintf(fp, "%s %d\n", userName, elapsedTime);
        fclose(fp);
        cant++;
        //asignamos memoria auxiliar para ayudar a reordenar la lista
        names = (char **)malloc(cant * sizeof(char *));
        for (i = 0; i < cant; ++i) {
            names[i] = (char *)malloc(20 * sizeof(char));
        }
        scores = (int *)malloc(cant * sizeof(int));
        //reordenar la lista
        fp = fopen(file, "r");
        fscanf(fp, "%d", &cant);
        cant++;
        for (i = 0; i < cant; ++i) {
            fscanf(fp, "%s %d", names[i], &scores[i]);
            printf("%s %d\n", names[i], scores[i]);
        }
        fclose(fp);
        for (i = 0; i < cant; ++i) {
            for (j = i; j < cant; ++j) {
                if (scores[i] > scores[j]) {
                    //swap scores
                    auxi = scores[i];
                    scores[i] = scores[j];
                    scores[j] = auxi;
                    //swap names
                    for (k = 0; k < 20; ++k) {
                        auxc = names[i][k];
                        names[i][k] = names[j][k];
                        names[j][k] = auxc;
                    }
                }
            }
        }
        //ahora que los arreglos tienen los nombres y puntajes ordenados, los guardamos en el archivo
        fp = fopen(file, "w");
        fprintf(fp, "%d\n", cant); //(comenzando por la cantidad)
        for (i = 0; i < cant; ++i) {
            fprintf(fp, "%s %d\n", names[i], scores[i]);
        }
        fclose(fp);
        //al terminar, liberamos la memoria
        free(scores);
        for (i = 0; i < cant; ++i) {
            free(names[i]);
        }
        free(names);

    } else {
        //añadir puntaje al final de la lista
        fp = fopen(file, "w");
        fprintf(fp, "%d\n", 1);
        fprintf(fp, "%s %d\n", userName, elapsedTime);
        fclose(fp);
    }
}
void printScores(char diff) {
    char file[] = "scores_.txt";
    file[6] = '0' + diff; // '0'=48 (sumandole la difficultad da como resultado 49='1', 50='2', 51='3'
    FILE * fp;
    fp = fopen(file, "r"); //'r'-> read
    int i, num;
    fscanf(fp, "%d", &num);
    if (num > 10)
      num = 10;
    char nombre[20];
    int puntaje;
    for(i = 0; i < num; i++) {
        fscanf(fp,"%s %d", nombre, &puntaje);
        printf("%s %d\n", nombre, puntaje);
    }
}

int main() {
    char **campo;
    char **cover;
    int n, m, semilla, minas, opcion, tiempo;
    do {
        printf("Elija una opcion\n1)Principiante\n2)Intermedio\n3)Experto\n4)Personalizado\n5)Cargar partida\n");
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                n=9;
                m=9;
                minas=10;
                semilla=time(NULL);
                break;
            case 2:
                n=16;
                m=16;
                minas=40;
                semilla=time(NULL);
                break;
            case 3:
                n=20;
                m=20;
                minas=85;
                semilla=time(NULL);
                break;
            case 4:
                do{
                    printf("Ingrese dimensiones, numero de minas y semilla:\n");
                    scanf("%d %d %d %d", &n, &m, &minas, &semilla);
                } while((n>30||m>50)||minas>1500);
                break;
						case 5:
								loadGame(&n,&m,&campo,&cover,&tiempo,&minas);
								break;
        }
    } while(opcion>5||opcion<1);
    start:
		if(opcion!=5){
      tiempo=0;
    	campo = crearCampo(n, m);
    	rellenador(n, m, campo, semilla, minas);
      cover = crearCampo(n, m);
		}

		int x,y,i,j;
    int w=(m*30)+300,h=(n*30); // variables para ancho y alto de la ventana
    int contadorMinas,BanderasPuestas,PonerBanderas=1; //variables para contador minas
    int startTime; //variales para contador del tiempo
    SDL_Window *window = NULL;
    SDL_Surface *scr_surfc = NULL;
  	SDL_Surface *pic[n][m];
    SDL_Surface *imagenes[15];
    imagenes[0]=SDL_LoadBMP("30px/Mina.bmp");
    imagenes[1]=SDL_LoadBMP("30px/CasillaD.bmp");
    imagenes[2]=SDL_LoadBMP("30px/1.bmp");
    imagenes[3]=SDL_LoadBMP("30px/2.bmp");
    imagenes[4]=SDL_LoadBMP("30px/3.bmp");
    imagenes[5]=SDL_LoadBMP("30px/4.bmp");
    imagenes[6]=SDL_LoadBMP("30px/5.bmp");
    imagenes[7]=SDL_LoadBMP("30px/6.bmp");
    imagenes[8]=SDL_LoadBMP("30px/7.bmp");
    imagenes[9]=SDL_LoadBMP("30px/8.bmp");
    imagenes[10]=SDL_LoadBMP("30px/MinaA.bmp");
    imagenes[11]=SDL_LoadBMP("30px/Bandera.bmp");
    imagenes[12]=SDL_LoadBMP("30px/duda.bmp");
    imagenes[13]=SDL_LoadBMP("30px/BanderaE.bmp");

    SDL_Surface *guardar = SDL_LoadBMP("contador/guardar.bmp");
    SDL_Surface *reset = SDL_LoadBMP("contador/reset.bmp");
    SDL_Surface *taiko[3];
    taiko[0] = SDL_LoadBMP("contador/taiko1.bmp");
    taiko[1] = SDL_LoadBMP("contador/taiko2.bmp");
    taiko[2] = SDL_LoadBMP("contador/taiko3.bmp");
    SDL_Surface *contadorM[3];
    SDL_Surface *TcontadorM= SDL_LoadBMP("contador/MinasTitulo.bmp");
    contadorMinas=minas;
    contadores(contadorMinas,3,contadorM);
    SDL_Surface *contadorT[3];
    SDL_Surface *TcontadorT= SDL_LoadBMP("contador/TiempoTitulo.bmp");
    if(opcion!=5){
      for(i=0;i<3;i++){
        contadorT[i]= SDL_LoadBMP("contador/0c.bmp");
      }
    }
    else{
      startTime=time(NULL);
      contadores(getTime(startTime-tiempo),3,contadorT);
    }


    SDL_Event e;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect dim[n][m];
    SDL_Rect dimM[3];
    SDL_Rect dimT[3];
    SDL_Rect TdimM;
    SDL_Rect TdimT;
    SDL_Rect dimG;
    SDL_Rect dimC;
    SDL_Rect dimReset;

    //Dimension casillas de la matriz
    for(i=0;i<n;i++){
      for(j=0;j<m;j++){
        dim[i][j].x = 0+(j*30);
        dim[i][j].y = 0+(i*30);
        dim[i][j].h = 30;
        dim[i][j].w = 30;
      }
    }
    //Dimension titulo minas
    TdimM.x = w-300;
    TdimM.y = h/30;
    TdimM.h = 56;
    TdimM.w = 126;

    //Dimension contador minas
    for(i=0;i<3;i++){
      dimM[i].x = w-42-(i*42);
      dimM[i].y = h/30;
      dimM[i].h = 56;
      dimM[i].w = 42;
    }
    //Dimension titulo tiempo
    TdimT.x = w-300;
    TdimT.y = h/30+50;
    TdimT.h = 56;
    TdimT.w = 126;

    //Dimension contador tiempo
    for(i=0;i<3;i++){
      dimT[i].x = w-42-(i*42);
      dimT[i].y = h/30+50;
      dimT[i].h = 56;
      dimT[i].w = 42;
    }
    //Dimension boton de guardado
    dimG.x = w-260;
    dimG.y = 4*h/9;
    dimG.h = 60;
    dimG.w = 150;

    //Dimension carita
    dimC.x = w-195;
    dimC.y = 6*h/9;
    dimC.h = 80;
    dimC.w = 80;

    //Dimension reset
    dimReset.x = w-100;
    dimReset.y = 4*h/9;
    dimReset.h = 60;
    dimReset.w = 60;

    window = SDL_CreateWindow("Buscaminas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    scr_surfc = SDL_GetWindowSurface(window);
    SDL_FillRect(scr_surfc, NULL, get_color(scr_surfc, 0x77, 0x77, 0x77));

    //Dibujar en pantalla el campo de juego (cada casilla)
    for(i=0;i<n;i++){
      for(j=0;j<m;j++){
        if(cover[i][j]==0){
          pic[i][j]= SDL_LoadBMP("30px/Casilla.bmp");
          SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
        }
        else if(cover[i][j]==2){
          pic[i][j]= imagenes[11];
          SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
        }
        else if(cover[i][j]==3){
          pic[i][j]= imagenes[12];
          SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
        }
        else{
          pic[i][j]= imagenes[campo[i][j]+1];
          SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
        }
      }
    }
    // Dibujar en pantalla titulo y contador de minas
    SDL_BlitSurface(TcontadorM, NULL, scr_surfc, &TdimM);
    for(i=0;i<3;i++){
        SDL_BlitSurface(contadorM[i], NULL, scr_surfc, &dimM[i]);
    }
    // Dibujar en pantalla titulo y contador de tiempo
    SDL_BlitSurface(TcontadorT, NULL, scr_surfc, &TdimT);
    for(i=0;i<3;i++){
        SDL_BlitSurface(contadorT[i], NULL, scr_surfc, &dimT[i]);
    }
    // Dibujar carita taiko
    SDL_BlitSurface(taiko[2],NULL,scr_surfc,&dimC);

    // Dibujar Boton de guardado
    SDL_BlitSurface(guardar,NULL,scr_surfc,&dimG);

    // Dibujar Boton de reset
    SDL_BlitSurface(reset,NULL,scr_surfc,&dimReset);

    SDL_UpdateWindowSurface(window);

    int primerTurno;
    if(opcion!=5)
      primerTurno=1;
    else
      primerTurno=0;

    while(1){

        while(!SDL_PollEvent(&e));
        if (e.type == SDL_QUIT)
            break;
        if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_RIGHT && !(primerTurno)){
            for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    SDL_GetMouseState(&x, &y);
                    if(x>=dim[i][j].x+1 && x<=dim[i][j].w+dim[i][j].x-1 && y>=dim[i][j].y+1 && y<=dim[i][j].h+dim[i][j].y-1 && cover[i][j]==0 && PonerBanderas){
                        pic[i][j]= imagenes[11];
                        SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
                        cover[i][j]=2;
                        }
                    else if(x>=dim[i][j].x+1 && x<=dim[i][j].w+dim[i][j].x-1 && y>=dim[i][j].y+1 && y<=dim[i][j].h+dim[i][j].y-1 && cover[i][j]==2){
                        pic[i][j]= imagenes[12];
                        SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
                        cover[i][j]=3;
                    }
                    else if(x>=dim[i][j].x+1 && x<=dim[i][j].w+dim[i][j].x-1 && y>=dim[i][j].y+1 && y<=dim[i][j].h+dim[i][j].y-1 && cover[i][j]==3){
                        pic[i][j]=SDL_LoadBMP("30px/Casilla.bmp");
                        SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
                        cover[i][j]=0;
                    }
                }
            }
            SDL_UpdateWindowSurface(window);
        }
        if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT ){
            if(x>=dimG.x && x<=dimG.w+dimG.x && y>=dimG.y && y<=dimG.h+dimG.y && !primerTurno){
                saveGame(n,m,campo,cover,getTime(startTime));
                goto fin;
            }
            if(x>=dimReset.x && x<=dimReset.w+dimReset.x && y>=dimReset.y && y<=dimReset.h+dimReset.y && !primerTurno){
                semilla=time(NULL);
                opcion=opcionUsada(n,m,minas);
                SDL_DestroyWindow(window);
                SDL_Quit();
                goto start;
            }
            for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    SDL_GetMouseState(&x, &y);
                    if(x>=dim[i][j].x+1 && x<=dim[i][j].w+dim[i][j].x-1 && y>=dim[i][j].y+1 && y<=dim[i][j].h+dim[i][j].y-1 && cover[i][j]==0){
                        if(primerTurno && campo[i][j]==-1){
                            startTime = time(NULL);
                            moverMina(n,m,campo,i,j);
                            contarMinas(n,m,campo);
                            showCell(i,j,n,m,cover,campo);
                            primerTurno=0;
                        }
                        else if (primerTurno){
                            startTime = time(NULL);
                            contarMinas(n,m,campo);
                            showCell(i,j,n,m,cover,campo);
                            primerTurno=0;
                        }
                        else
                            showCell(i,j,n,m,cover,campo);
                    }
                }
            }
            for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    if (cover[i][j]==1){
                        if(campo[i][j]==-1){
                            pic[i][j]= imagenes[10];
                            SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
                            for(int k=0;k<n;k++){
                                for(int l=0;l<m;l++){
                                    if(k==i && l==j)
                                        continue;
                                    else if (cover[k][l]==2 && campo[k][l]!=-1){
                                        pic[k][l]= imagenes[13];
                                        SDL_BlitSurface(pic[k][l], NULL, scr_surfc, &dim[k][l]);
                                    }
                                    else{
                                        cover[k][l]=1;
                                        pic[k][l]= imagenes[campo[k][l]+1];
                                        SDL_BlitSurface(pic[k][l], NULL, scr_surfc, &dim[k][l]);
                                    }
                                }
                            }
                            SDL_BlitSurface(taiko[0],NULL,scr_surfc,&dimC);
                            printf("Has Perdido :c\n" );
                            SDL_UpdateWindowSurface(window);
                            while(1){
                                SDL_GetMouseState(&x, &y);
                                while(!SDL_PollEvent(&e));
                                if (e.type == SDL_QUIT)
                                    break;
                                    if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT ){
                                        if(x>=dimReset.x && x<=dimReset.w+dimReset.x && y>=dimReset.y && y<=dimReset.h+dimReset.y && !primerTurno){
                                            semilla=time(NULL);
                                            opcion=opcionUsada(n,m,minas);
                                            SDL_DestroyWindow(window);
                                            SDL_Quit();
                                            goto start;
                                        }
                                    }
                                SDL_UpdateWindowSurface(window);
                            }
                            goto fin;
                        }
                        else{
                            pic[i][j]= imagenes[campo[i][j]+1];
                            SDL_BlitSurface(pic[i][j], NULL, scr_surfc, &dim[i][j]);
                            }
                        }
                }
            }
            SDL_UpdateWindowSurface(window);
        }
        //Contador Tiempo, si no ha empezado el juego no entra
        if(!primerTurno && opcion!=5){
            contadores(getTime(startTime),3,contadorT);
            for(i=0;i<3;i++){
                SDL_BlitSurface(contadorT[i], NULL, scr_surfc, &dimT[i]);
                SDL_UpdateWindowSurface(window);
            }
        }
        else if(opcion==5){
            contadores(getTime(startTime-tiempo),3,contadorT);
            for(i=0;i<3;i++){
                SDL_BlitSurface(contadorT[i], NULL, scr_surfc, &dimT[i]);
                SDL_UpdateWindowSurface(window);
            }
        }
        //Contador de banderas puestas
        BanderasPuestas=0;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(cover[i][j]==2){
                    BanderasPuestas++;
                }
            }
        }
        //Comprobamos si hay igual cantidad de banderas que minas
        //Si se cumple no se podran poner mas banderas
        if(BanderasPuestas==contadorMinas)
            PonerBanderas=0;
        else
            PonerBanderas=1;
        // Actualizacion contador Minas
        contadores((contadorMinas-BanderasPuestas),3,contadorM);
        for(i=0;i<3;i++){
            SDL_BlitSurface(contadorM[i], NULL, scr_surfc, &dimM[i]);
        }

        SDL_UpdateWindowSurface(window);
        //Comprobamos si el usuario ha ganado
        if(checkWin(n,m,cover,minas)){
            opcion=opcionUsada(n,m,minas);
            SDL_BlitSurface(taiko[1],NULL,scr_surfc,&dimC);
            SDL_UpdateWindowSurface(window);
            printf("Has Ganado c:\n" );
            if(opcion!=4){
              tiempo=getTime(startTime-tiempo);
              char nombreUsuario[20];
              printf("Ingrese nombre de usuario:\n");
              scanf(" %s",nombreUsuario);
              saveScore(nombreUsuario,tiempo,opcion);
              printf("Los 10 puntajes mas altos son:\n");
              printScores(opcion);
            }
            while(1){
                while(!SDL_PollEvent(&e));
                SDL_GetMouseState(&x, &y);
                if (e.type == SDL_QUIT)
                    break;
                if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT ){
                    if(x>=dimReset.x && x<=dimReset.w+dimReset.x && y>=dimReset.y && y<=dimReset.h+dimReset.y && !primerTurno){
                        semilla=time(NULL);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        goto start;
                    }
                }
                SDL_UpdateWindowSurface(window);
            }
            goto fin;
        }
    }
    fin:
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
