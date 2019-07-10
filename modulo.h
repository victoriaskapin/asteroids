#ifndef _MODULO_H_
#define _MODULO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "config.h"
#include "utilidades.h"
//#include "iterador.h"
//#include "lista.h"

#define MAX_SPRITES 7 

sprite_t sprite[MAX_SPRITES];

bool graficador_inicializar(const char *fn);

bool graficador_dibujar(SDL_Renderer *r, const char *nombre, float escala, float x, float y, float angulo);

void graficador_ajustar_variables(float *x, float *y);
/*
void graficador_finalizar();*/

#endif