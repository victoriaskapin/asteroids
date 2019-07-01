#ifndef _NAVE_H_
#define _NAVE_H_

#include "modulo.h"
#include <math.h>


typedef struct
{	
	sprite_t  *sp_nave;
	float escala;
	float px;
	float py;
	float vx;
	float vy;
	float angulo;
	size_t potencia;

}nave_t;

nave_t *nave_crear();
void nave_mover(nave_t *nave, float dt);
bool nave_destruir(nave_t*n);
bool nave_dibujar(const nave_t *x, SDL_Renderer *r);

float ** vector_rotar(float coordenadas[][2], size_t n, float rad);
void destruir_vector(float **v,size_t n);


#endif


