//Juego simple: Space Invaders.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define V 21
#define H 65
#define N 60
#define M 60

typedef struct{
	int x,y,lleno;
	int ModiaX,ModiaY;
	char naveia;
}naves;

typedef struct{
	int naveini;
	int navefin,sht;
	int ModY;
	char nav;
	char shoot;
}jugar;

typedef struct{
	int bal;
	int aux;
	int balia;
	int auxia;
	int ModY;
}tirador;

typedef struct{
	int puntos;
	int aux;
}record;

naves nav[M];
jugar jug;
tirador tir[N];
record points;

void inicio(int *tam,char campo[V][H]);
void Intro_campo(char campo[V][H]);
void Intro_datos(char campo[V][H], int tam);
void draw(char campo[V][H]);
void gameloop(char campo[V][H], int tam);
void input(char campo[V][H], int *tam, int *fin,int *pause, int *ia);
void update(char campo[V][H], int tam, int *ia, int pause,int *fin);
void disparo(char campo[V][H],int *tam);
void disparoIA(char campo[V][H],int **fin);
void revision();

int main(){
	int tam;
	char campo[V][H];
	
	printf("**************\tSPACE INVADERS\t***********\n");
	printf("Programador: Emmanuel Guerra.\n");
	system("pause");
	inicio(&tam,campo);
	gameloop(campo,tam);
	
	system("pause");
	return 0;
}

void inicio(int *tam,char campo[V][H]){
	int i,j,k;

	jug.naveini = 31;
	jug.navefin = 33;
	jug.shoot = 30;
	jug.ModY = 0;
	jug.nav = '#';
	
	points.puntos = 0;
	points.aux = 0;
	
	*tam = 29;
	
	j = 3;
	k = 1;
	
	for(i = 0;i<M;i++){
		nav[i].lleno = i;
		nav[i].x = j;
		nav[i].y = k;
		nav[i].ModiaX = 1;
		nav[i].ModiaY = 3;
		nav[i].naveia = 2;
		j++;
	
		if(k == 3){
			if(j == 7){
				j = 17;
				k = 1;
			}
			else if(j == 21){
				j = 30;
				k = 1;
			}
			else if(j == 34){
				j = 42;
				k = 1;
			}
			else if(j == 46){
				j = 55;
				k = 1;
			}
		}
		
		else if(j == 7){
			j = 3;
			k++;
		}

		else if(j == 21){
			j = 17;
			k++;
		}
		else if(j == 34){
			j = 30;
			k++;
		}
		else if(j == 46){
			j = 42;
			k++;
		}
		else if(j == 59){
			j = 55;
			k++;
		}
	}
	
	
	for (i = 0;i<N;i++){
		tir[i].aux = 0;
		tir[i].bal = V-4;
		tir[i].balia = nav[i].y;
		tir[i].auxia = nav[i].x;
		tir[i].ModY = 1;
	}
	
	Intro_datos(campo,*tam);
	Intro_campo(campo);
	
	
}

void Intro_campo(char campo[V][H]){
	int i,j;
	
	for(i = 0;i < V; i++){
		for(j = 0;j < H; j++){
			if (i == 0 || i == V-1){
				campo[i][j] = '=';
			}
			else if(j == 0 || j == H-1){
				campo[i][j] = '|';
			}
			else{
				campo[i][j] = ' ';
			}
		}
	}
}

void Intro_datos(char campo[V][H], int tam){
	int i,j,k;
	
	for(i = V-2; i == V-2;i++){
		for(j = jug.naveini;j <= jug.navefin;j++){
			campo[i][j] = jug.nav;
			if(jug.navefin - j == 1){
				campo[V-3][j] = jug.shoot;
				jug.sht = j;
			}
		}
	}
	
	j = 30;
	k = 0;
	
	for(i = 0;i<M;i++){
		campo[nav[i].y][nav[i].x] = nav[i].naveia;
	}
	
	
}

void draw(char campo[V][H]){
	int i,j;
	
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			printf("%c",campo[i][j]);
		}
		printf("\n");
	}
	
}

void gameloop(char campo[V][H], int tam){
	int fin = 0,pause = 0,ia = 60;
	
	draw(campo);
	input(campo,&tam,&fin,&pause,&ia);
	update(campo,tam,&ia,pause,&fin);
	system("cls");
	draw(campo);
	system("pause");
	
	do{
		system("cls");
		draw(campo);
		input(campo,&tam,&fin,&pause,&ia);
		pause++;
		if(tam == 0){
			tam = 29;
		}
		update(campo,tam,&ia,pause,&fin);
		if(points.aux == 1){
			points.puntos++;
			points.aux = 0;
		}
		
	}while(fin == 0);
	
	printf("Puntuacion: %i.\n",points.puntos);
}

void input(char campo[V][H], int *tam, int *fin, int *pause, int *ia){
	int i,j,aux,k;
	char key;
	
	aux = 0;
	
	if(*pause == 10){
		for(i = 0;i<M;i++){
			if(nav[i].x == H-2){
				nav[i].y += nav[i].ModiaY;
				nav[i].ModiaX = -1;
				nav[i].x += nav[i].ModiaX;
			}
			else if(nav[i].x == 1){
				nav[i].y += nav[i].ModiaY;
				nav[i].ModiaX = 1;
				nav[i].x += nav[i].ModiaX;
			}
			
			else{
				nav[i].x += nav[i].ModiaX;
			}
		}
		*pause = 0;
	}
	
	for(i = 0;i<M && *fin == 0;i++){
		if(nav[i].y == V-1){
			*fin = 1;
		}
	}
	
	
	for(i = 0;i<M && *fin == 0;i++){
		if(campo[nav[i].y][nav[i].x] == jug.shoot || campo[nav[i].y][nav[i].x] == jug.nav){
			*fin = 1;
		}
	}
	
	for(i = V-2; i == V-2 && *fin != 1;i++){
		for(j = jug.naveini;j <= jug.navefin && *fin != 1;j++){
			if(campo[i][j] == '+'){
				*fin = 1;
			}
			if(jug.navefin - j == 1){
				if (campo[V-3][j] == '+'){
					*fin = 1;
				}
			}
		}
	}
	
	if(*fin == 0){
		if(kbhit() == 1){
			key = getch();
				
			if(key == 'a'){
				if(jug.naveini != 1){
					jug.naveini -= 1;
					jug.navefin -= 1;	
				}
			}
			
			if(key == 'd'){
				if(jug.navefin != H-2 ){
					jug.naveini += 1;
					jug.navefin += 1;
				}
			}
			
			if(key == 'w' && *tam != 0){
				jug.ModY = -1;
				*tam -= 1;
				for(i = 0;aux == 0;i++){
					if(tir[i].aux == 0){
						tir[i].aux = jug.sht;
						aux = 1;
					}
				}
			}
		}
	}
	
	//Comprobacion de balas
	
	i = 0;
	j = 0;
	k = 0;
	aux = 0;
	
	while(i<M){
		if(campo[nav[i].y][nav[i].x] == '.' && nav[i].lleno != 0){
			nav[i].lleno = 0;
			nav[i].x = j;
			nav[i].y = 1;
			nav[i].ModiaY = 0;
			nav[i].ModiaX = 0;
			nav[i].naveia = ' ';
			*ia -= 1;
			points.aux = 1;
			for(j = 0;j<N && aux == 0;j++){
				if(tir[j].aux != 0){
					tir[j].aux = 0;
					tir[j].bal = V-3;
					campo[tir[j].bal][tir[j].aux] = ' ';
					aux = 1;
				}
			}
		}
		j++;
		i++;
	}
}

void update(char campo[V][H], int tam, int *ia,int pause,int *fin){
	Intro_campo(campo);
	Intro_datos(campo,tam);
	disparo(campo,&tam);
	disparoIA(campo,&fin);
	if(*ia == 0){
		revision();
		*ia = 60;
	}
}

void disparo(char campo[V][H],int *tam){
	int i;
	
	for(i = 0;i<N;i++){
		
		if(tir[i].aux != 0 && tir[i].bal != 1){
			tir[i].bal += jug.ModY;
			campo[tir[i].bal][tir[i].aux] = '.';
		}
		
		else if(tir[i].bal == 1){
			tir[i].aux = 0;
			tir[i].bal = V-3;
		}
	}
}

void disparoIA(char campo[V][H],int **fin){
	int i,j;
	
	for(i = 0;i<N && **fin != 1;i++){
		if(nav[i].lleno == 11){
			tir[i].balia += tir[i].ModY;
			campo[tir[i].balia][tir[i].auxia] = '+';
		}
		
		else if(nav[i].lleno == 23){
			tir[i].balia += tir[i].ModY;
			campo[tir[i].balia][tir[i].auxia] = '+';
		} 
		
		else if(nav[i].lleno == 35){
			tir[i].balia += tir[i].ModY;
			campo[tir[i].balia][tir[i].auxia] = '+';
		}

		else if(nav[i].lleno == 47){
			tir[i].balia += tir[i].ModY;
			campo[tir[i].balia][tir[i].auxia] = '+';
		}
		
		else if(nav[i].lleno == 56){
			tir[i].balia += tir[i].ModY;
			campo[tir[i].balia][tir[i].auxia] = '+';
		}
		if(tir[i].balia == V-1){
			tir[i].auxia = 0;
			tir[i].balia = 4;
			campo[tir[i].balia][tir[i].auxia] = ' ';
			for(j = 0;j<N && **fin != 1;j++){
				tir[j].balia = nav[j].y;
				tir[j].auxia = nav[j].x;
			}
		}
	}
	
}

void revision(){
	int i,j,k;
	
	j = 3;
	k = 1;
	
	for(i = 0;i<M;i++){
		nav[i].lleno = i;
		nav[i].x = j;
		nav[i].y = k;
		nav[i].ModiaX = 1;
		nav[i].ModiaY = 3;
		nav[i].naveia = 2;
		j++;
	
		if(k == 3){
			if(j == 7){
				j = 17;
				k = 1;
			}
			else if(j == 21){
				j = 30;
				k = 1;
			}
			else if(j == 34){
				j = 42;
				k = 1;
			}
			else if(j == 46){
				j = 55;
				k = 1;
			}
		}
		
		else if(j == 7){
			j = 3;
			k++;
		}

		else if(j == 21){
			j = 17;
			k++;
		}
		else if(j == 34){
			j = 30;
			k++;
		}
		else if(j == 46){
			j = 42;
			k++;
		}
		else if(j == 59){
			j = 55;
			k++;
		}
	}
}
