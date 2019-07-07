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


sprite_t sprite[7];//puntero a estructura de sprites global que lleno en la funcion

bool graficador_inicializar(const char *fn){
	FILE *fp;
	int i=0,j;
	uint16_t n;
	
	fp=fopen(fn,"rb"); 
	if (fp==NULL)
		return false;

	
	while(!feof(fp) && i<2){

		//sprite=realloc(sprite,sizeof(sprite_t)*(i+1));//pido memoria para el vector de estructuras
		
		fread(&(sprite[i].nombre),sizeof(char),10,fp);//cargo el nombre
		fread(&(sprite[i].n),sizeof(uint16_t),1,fp);//cargo el n
		
		printf("nombre:%s n:%u \n",sprite[i].nombre,sprite[i].n);

		n=(int)sprite[i].n; 

		sprite[i].cords=malloc(n*sizeof(float*));//pido memoria para la matriz dinamica de 2 columnas
		

		for(j=0;j<n;j++)
		{
			fread(&(sprite[i].cords[j]),sizeof(float),2,fp);//cargo la matriz
		}
		

		for(j=0;j<n;j++)
			printf("coordenadas (%f ; %f)\n",sprite[i].cords[j][0],sprite[i].cords[j][1] );

		i++;
	}
	
	return true;
}

int main (void){ //main que arme para probar si funcionaba 

	if (graficador_inicializar("sprites.bin"))
		puts("se cargo la estructura");
	else
		puts("no se cargo la estructura");
	


	return 0;
}
