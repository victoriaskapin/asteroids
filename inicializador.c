#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nombre[10];
	uint16_t n;
	float cords[][2]; 
}sprite_t;

#define MAX_SPRITES 7 

sprite_t sprite[MAX_SPRITES];//puntero a estructura de sprites global que lleno en la funcion

bool graficador_inicializar(const char *fn){
	FILE *fp;
	int i=0;
	uint16_t n;
	
	fp=fopen(fn,"rb"); 
	if (fp==NULL)
		return false;

	//sprite=malloc(sizeof(sprite_t)*MAX_SPRITES);
	
	for(i=0;i<MAX_SPRITES;i++){
		
		fread(sprite[i].nombre,sizeof(char),10,fp);//cargo el nombre
		fread(&sprite[i].n,sizeof(uint16_t),1,fp);//cargo el n
		
		n=sprite[i].n; 

		fread(sprite[i].cords,sizeof(float),n*2,fp);//cargo la matriz	

	}	
	fclose(fp);
	return true;
}


int main (void){ //main que arme para probar si funcionaba 
	int c;
	if (graficador_inicializar("sprites.bin"))
		puts("se cargo la estructura");
	else
		puts("no se cargo la estructura");

	for(c=0;c<MAX_SPRITES;c++){
		printf("\n");
		
		printf("nombre:%s n:%u \n",sprite[c].nombre,sprite[c].n);

		for(int i=0;i<sprite[c].n;i++)
			printf("coordenadas (%f ; %f)\n",sprite[c].cords[i][0],sprite[c].cords[i][1] );
	}

	return 0;
}
