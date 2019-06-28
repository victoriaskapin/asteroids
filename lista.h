#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdbool.h>
#include <stdint.h>
#include "config.h"
struct nodo{
	struct nodo *sig;
	void *dato;
};

typedef struct {
	struct nodo *prim;
	// struct nodo *ult;
}lista_t;




//struct lista;
//typedef struct lista lista_t;

/*struct sprite_t{
	char nombre[10];
	uint16_t n;
	float cords[6][2];
};*/

struct nodo *nodo_crear(void *d);
lista_t *lista_crear();
void lista_destruir(lista_t *l, void (*destruir_dato)(void *d));
bool lista_es_vacia(const lista_t *l);
bool lista_insertar_comienzo(lista_t *l, void *d);
bool lista_insertar_final(lista_t *l, void *d);
float *lista_extraer_primero(lista_t *l);
float *lista_buscar(const lista_t *l, const float *d, int (*cmp)(const float *a, const float *b));
void lista_mapear(lista_t *l, float *(*f)(float *dato));
void lista_nodo_borrar(lista_t *l, void *estructura);

lista_t *cargar_lista(struct sprite_t *modulo, lista_t *l);

#endif

/*float *lista_extraer_ultimo(lista_t *l);
float *lista_borrar(lista_t *l, const float *dato, int (*cmp)(const float *a, const float *b));
void lista_recorrer(const lista_t *l, bool (*visitar)(float *dato, float *extra), float *extra);*/