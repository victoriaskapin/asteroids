#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//#include "lista.h"

typedef struct{
	char nombre[10];
	uint16_t n;
	float (*cords)[2]; //para poder llenarla me pedia un vector dinamico
}sprite_t;


sprite_t *sprite;//puntero a estructura de sprites global que lleno en la funcion

bool graficador_inicializar(const char *fn){
	FILE *fp;
	int i=0,j;
	uint16_t n;
	
	fp=fopen(fn,"rb"); 
	if (fp==NULL)
		return false;

	
	while(!feof(fp)){
		
		sprite=realloc(sprite,sizeof(sprite_t)*i+1);//pido memoria para el vector de estructuras
		fread(&(sprite[i].nombre),sizeof(char),10,fp);//cargo el nombre
		fread(&(sprite[i].n),sizeof(uint16_t),1,fp);//cargo el n
		
		n=(int)sprite[i].n; 

		sprite[i].cords=malloc(sizeof(float*)*n);//pido memoria para la matriz dinamica de 2 columnas
		
		for(j=0;j<n;j++){
			fread(&(sprite[i].cords[j]),sizeof(float),n*2,fp);//cargo la matriz
		}
		
		i++;
	}
	
	return true;
}

int main (void){ //main que arme para probar si funcionaba 

	if (graficador_inicializar("sprites.bin"))
		puts("se cargo la estructura");
	else
		puts("no se cargo la estructura");
	
	printf("nombre:%s n:%u \n",sprite[1].nombre,sprite[1].n);

	for(int i=0;i<sprite[0].n;i++)
		printf("coordenadas (%f ; %f)\n",sprite[1].cords[i][0],sprite[1].cords[i][1] );


	return 0;
}
