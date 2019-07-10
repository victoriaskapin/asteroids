#ifndef _LISTA_H_
#define _LISTA_H_



struct nodo{
	struct nodo *sig;
	void *dato;
};

typedef struct {
	struct nodo *prim;
	// struct nodo *ult;
}lista_t;

#include "utilidades.h"

//struct lista;
//typedef struct lista lista_t;


struct nodo *nodo_crear(void *d);
lista_t *lista_crear();
void lista_destruir(lista_t *l, void (*destruir_dato)(void *d));
bool lista_es_vacia(const lista_t *l);
bool lista_insertar_comienzo(lista_t *l, void *d);
bool lista_insertar_final(lista_t *l, void *d);
void *lista_extraer_primero(lista_t *l);
void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b));
void lista_mapear(lista_t *l, void *(*f)(void *dato));

lista_t *cargar_lista(sprite_t *modulo, lista_t *l);

#endif

/*void *lista_extraer_ultimo(lista_t *l);
void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b));
void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra);*/