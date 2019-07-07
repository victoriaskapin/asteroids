#ifndef _NAVE_H_
#define _NAVE_H_

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>


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


size_t combustible_chorro(nave_t nave, size_t paso_potencia);
size_t potencia_nave(nave_t nave, size_t paso_potencia);
void rotar(float **coordenadas, int n, double rad);
double computar_velocidad(double vi, double aceleracion, double dt);
double computar_posicion(double pi, double vi, double dt);
float **matriz_a_vector(float (*m)[MAX_COORDENADAS], size_t n);
void trasladar(float **coordenadas, int n, float dx, float dy);
float **crear_vector(size_t filas, size_t columnas);
void destruir_vector_float(float **vector, size_t n);

#endif