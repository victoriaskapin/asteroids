
#include "modulo.h"
#include <string.h>
#include "nave.h"

bool graficador_inicializar(const char *fn){
	
	FILE *fp;
	
	fp=fopen(fn,"rb"); 
	if (fp==NULL)
		return false;

	for(int k=0;k<MAX_SPRITES;k++){

		//sprite = realloc(sprite, sizeof(sprite_t)*(k+1));
		fread(&(sprite[k].nombre),sizeof(char),10,fp);//cargo el nombre
		fread(&(sprite[k].n),sizeof(uint16_t),1,fp);//cargo el n
		
		printf("nombre:%s n:%u \n",sprite[k].nombre, sprite[k].n);

		sprite[k].cords=malloc(sizeof(float*)*sprite[k].n*2);//pido memoria para la matriz dinamica de 2 columnas
		
		for(int j=0;j<(int)sprite[k].n;j++){
			fread(&sprite[k].cords[j][0],sizeof(float),1,fp);//cargo la matriz
			fread(&sprite[k].cords[j][1],sizeof(float),1,fp);//cargo la matriz
			printf("coordenadas (%f ; %f)\n", sprite[k].cords[j][0], sprite[k].cords[j][1]);

		}
			//graficador_ajustar_variables( &(sprite[i].cords[j][0]),&(sprite[i].cords[j][1]));

	}	
	fclose(fp);
	printf("sale de inicializador\n");

	return true;
}

void graficador_ajustar_variables(float *x, float *y){
	if(*x<0){
		*x = -*x;
	}
	if(*y<0){
		*y = -*y;
	}
	
	while(*x > 10.0){
		*x = ((*x) * 0.1);
	}
	while(*y > 10.0){
		*y = (*y / 10.0);
	}
}

bool graficador_dibujar(SDL_Renderer *r,const char *nombre, float escala, float x, float y, float angulo){

	int i,j;

	for(i=0; i<MAX_SPRITES; i++){
		if(!strcmp(sprite[i].nombre, nombre))
			break;
	}
	
	//cargo las coordenadas que quiero graficar rotadas en el angulo correspondiente en una nueva matriz auxiliar para no modificar los datos iniciales. 
	float **objeto;
	objeto = matriz_a_vector(sprite[i].cords, sprite[i].n);
	rotar(objeto, sprite[0].n, angulo);	

	//printf("x %f\ty %f\n", x, y);

	trasladar(objeto, sprite[0].n, x, y-400);
	
	for(j = 0; j < sprite[i].n -1 ; j++){//grafico la matriz rotada, desplazada en x e y; 
		SDL_RenderDrawLine(
			r,
			objeto[j][0] * escala + x,
			-objeto[j][1] * escala + y,
			objeto[j+1][0] * escala + x,
			-objeto[j+1][1] * escala + y 
		);
	}	
	return true;
}

float ** vector_rotar(float coordenadas[][2], size_t n, float rad){
	int i;
	float **rotada;
	float coseno_angulo,seno_angulo;

	rotada=malloc(sizeof(float)*n);
	if (rotada==NULL)
		return NULL;

	coseno_angulo=cos(rad);
	seno_angulo=sin(rad);
	for(i=0;i<n;i++){

		rotada[i]=malloc (sizeof(float)*2);
		
		if (rotada[i]==NULL){
			for(int j=0;j<i;j++)
				free(rotada[j]);
			free(rotada);
			return NULL;
		}

		rotada[i][0] = coordenadas[i][0]*coseno_angulo-coordenadas[i][1]*seno_angulo;
		rotada[i][1] = coordenadas[i][0]*seno_angulo+coordenadas[i][1]*coseno_angulo;
	}
	return rotada;
}

void destruir_vector(float **v,size_t n){

	for(int i = 0;i < n;i++){

		free (v[i]);
	}

	free (v);
}

/*void graficador_finalizar() //no hace falta porque declare todo estatico 
{
	for(int i=0; i<CANT_MODULOS; i++)
		free(sprite[i]);
}*/




/*
//Dibuja el sprite de nombre nombre en el renderer r escalado segun escala, rotado segun
//angulo en la posicion x, y de la pantalla (tomando como (0; 0) la esquina inferior izquierda).
bool graficador_dibujar(SDL_Renderer *r, const char *nombre, float escala, float x, float y, float angulo);
{	
	lista_iterador_t *iterador = lista_iterador_crear(l);
	struct nodo *nodo_modulo = lista_iterador_actual(iterador);//me paro en el primer nodo
	
	if(nodo_modulo->dato.nombre != nombre)//mientras que no encuentre una coincidencia, avanzo
	{
		if((lista_iterador_siguiente(iterador))==false)//avanzo al siguiente nodo
			break;
		nodo_modulo = lista_iterador_actual(iterador);
	}
		for(int i = 0; i < nodo_modulo->dato.n - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				nodo_modulo->dato.cords[i][0] * escala + x / 2,//dato tiene la fila del nodo actual
				-nodo_modulo->dato.cords[i][1] * escala + y / 2,
				nodo_modulo->dato.cords[i+1][0] * escala + x / 2,//dato.cords[i][0] tiene todas las x se la mtriz
				-nodo_modulo->dato.cords[i+1][1] * escala + y / 2
			);
	//lista_destruir(l, free());
	lista_iterador_destruir(iterador);
	return true;
}

*/