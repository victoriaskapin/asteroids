
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "config.h"
#include "modulo.h"
#include "iterador.h"
#include "lista.h"

lista_t *lista_sprites;

bool graficador_inicializar(const char *fn, int ancho, int alto)//para que sirve ancho y alto???????
{
	FILE *f;
	struct sprite_t sprite;
	
	f = fopen(fn, "rb");
	
	lista_sprites = lista_crear();//no hace falta usar listas para las estructuras

	while(feof)//inicializo los modulos uno por uno
	{
		fread(&sprite, sizeof(struct sprite_t), 1, f);
		if((lista_insertar_final(l, sprite))==false) //cargo el ultimo nodo con la estructura
			return false;
	}

	fclose(f);
	return true;
}


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


//Esta funcion es de asistencia a otros modulos, recibe dos variables x e y y las ajusta dentro
//del ancho y alto de la pantalla. De esta forma los modulos que trabajan con coordenadas
//no tienen necesidad de conocer las dimensiones del espacio.
void graficador_ajustar_variables(float *x, float *y)
{

}

//Finaliza el modulo. Deben liberarse todos los recursos asociados. Despues de llamar a esta
//funcion el modulo debe quedar como antes de llamar a graficador_inicializar().
void graficador_finalizar()
{
	for(int i=0; i<CANT_MODULOS; i++)
		free(sprite[i]);
}


