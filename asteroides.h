#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

#define ASTEROIDE_RADIO_CHICO 8
#define ASTEROIDE_RADIO_MEDIANO 16
#define ASTEROIDE_RADIO_GRANDE 32
#define ASTEROIDES_DESTRUIDOS 0
#define VELOCIDAD_ASTEROIDE_ORIGINAL 1000.0
#define VELOCIDAD_ASTEROIDE_OFFSET 100.0

#include "nave.h"
#include "disparos.h"
#include "utilidades.h"

typedef struct
{
	sprite_t *sp_asteroide;
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo_rotacion;
	size_t radio;
	
}asteroide_t;

asteroide_t * asteroide_crear(size_t radio, float px, float py);
void asteroide_mover(asteroide_t *rock, float dt);
bool asteroide_dibujar(asteroide_t *rock,SDL_Renderer *r);
void asteroide_destruir(asteroide_t *asteroide);
bool cargar_asteroides_lista(lista_t *l_rock, float px, float py,size_t radio);
bool crear_asteroides_iniciales(size_t cant,lista_t* l_rock);
void mover_lista_asteroides(lista_t*l_rock,float dt);
bool dibujar_lista_asteroides(lista_t*l_rock,SDL_Renderer *r);

float distancia(asteroide_t *asteroide, float objeto_x, float objeto_y);
bool asteroide_choco(nave_t *nave,lista_t *l_shot, asteroide_t *asteroide);
void lista_asteroide_choco(lista_t *l_rock,nave_t *nave,lista_t *l_shot,int *score);

/*asteroide_t asteroide;
disparo_t disparo;
lista_t *lista_asteroides;
lista_t *lista_disparos;

status_t asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo);
float distancia(void *asteroide, float objeto_x, float objeto_y);
asteroide_t *cargar_asteroide(size_t radio, float x, float y);
size_t procesar_asteroide(lista_iterador_t * iterador);
void crear_asteorides(size_t cantidad);
bool asteroide_dibujar(asteroide_t x, SDL_Renderer *r);*/


#endif