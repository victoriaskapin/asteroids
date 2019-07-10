#ifndef _UTILIDADES_H_
#define _UTILIDADES_H_

#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "config.h"
#include "modulo.h"
#include "iterador.h"
#include "lista.h"
#include "nave.h"
#include "asteroides.h"
#include "disparos.h"


float generar_aleatorio(float superior, float inferior);

void setear_conficiones_iniciales(nave_t *nave);

void destruir_vector(float **v,size_t n);

float ** vector_rotar(float coordenadas[][2], size_t n, float rad);

float **matriz_a_vector(float (*m)[MAX_COORDENADAS], size_t n);

void rotar(float **coordenadas, int n, double rad);

#endif