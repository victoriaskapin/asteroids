
#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "utilidades.h"
#include "lista.h"
#include "nave.h"
#include "iterador.h"
#include "disparos.h"

#define ASTEROIDE_RADIO_CHICO 8
#define ASTEROIDE_RADIO_MEDIANO 16
#define ASTEROIDE_RADIO_GRANDE 32
#define ASTEROIDES_DESTRUIDOS 0
#define VELOCIDAD_ASTEROIDE_ORIGINAL 1000
#define VELOCIDAD_ASTEROIDE_OFFSET 100

typedef struct
{
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo_rotacion;
	size_t radio;
}asteroide_t;


asteroide_t asteroide;
disparo_t disparo;
lista_t *lista_asteroides;
lista_t *lista_disparos;

status_t asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo);
float distancia(void *asteroide, float objeto_x, float objeto_y);
asteroide_t *cargar_asteroide(size_t radio, float x, float y);
size_t procesar_asteroide(lista_iterador_t * iterador);
void crear_asteorides(size_t cantidad);
bool asteroide_dibujar(asteroide_t x, SDL_Renderer *r);


#endif