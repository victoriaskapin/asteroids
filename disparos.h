#ifndef _DISPAROS_H_
#define _DISPAROS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "modulo.h"
#include "config.h"
#include "lista.h"
#include "iterador.h"


typedef struct
{
	sprite_t  sp_disparo;
	float escala;
	float posicion_x;
	float posicion_y;
	float velocidad;
	float angulo;
	float tiempo_vida;
}disparo_t;


disparo_t * disparo_crear(float px, float py, float angulo);
void disparo_destruir(disparo_t *shot);
bool disparo_dibujar(disparo_t *shot,SDL_Renderer *r);
void disparo_mover(disparo_t *shot, float dt);
void trasladar_shot(float (*coordenadas)[2], int n, float dx, float dy);
bool cargar_disparos(lista_t *l_shot,float px,float py,float angulo);
bool dibujar_lista_disparos(lista_t*l_shot,SDL_Renderer *r);
void mover_lista_disparos(lista_t*l,float dt);
//bool eliminar_disparos(lista_t *l_shot);

#endif