#ifndef _NAVE_H_
#define _NAVE_H_

#include "utilidades.h"

typedef struct
{
	sprite_t  *sp_nave;
	float escala;
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo_rotacion;
	size_t potencia;
}nave_t;


nave_t nave_crear();
void nave_mover(nave_t *nave, float dt, size_t potencia);
bool nave_dibujar(nave_t x, SDL_Renderer *r);//LA ESTRUCTURA TIENE QUE SER CONST
bool nave_destruir(nave_t*n);
void setear_conficiones_iniciales(nave_t *nave);

size_t combustible_chorro(nave_t nave, size_t paso_potencia);
size_t potencia_nave(nave_t nave, size_t paso_potencia);
double computar_velocidad(double vi, double aceleracion, double dt);
double computar_posicion(double pi, double vi, double dt);
void trasladar(float **coordenadas, int n, float dx, float dy);


#endif