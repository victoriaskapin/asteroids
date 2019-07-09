#ifndef _DISPAROS_H_
#define _DISPAROS_H_

#include "config.h"
#include "objetos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

disparo_t * disparo_crear(float px, float py, float angulo);
void disparo_destruir(disparo_t *shot);
bool disparo_dibujar(disparo_t *shot,SDL_Renderer *r);
void disparo_mover(disparo_t *shot, float dt);
void trasladar(float **coordenadas, int n, float dx, float dy);
bool cargar_disparos(lista_t *l_shot,float px,float py,float angulo);
bool eliminar_disparos(lista_t *l_shot);

#endif