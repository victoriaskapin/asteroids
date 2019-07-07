#ifndef _ITERADOR_H_
#define _ITERADOR_H_

#include "lista.h"


typedef struct
{
	struct nodo *nodo_iterador;
	struct nodo *nodo_anterior;
}lista_iterador_t;

lista_iterador_t *lista_iterador_crear(lista_t *l);
void lista_iterador_destruir(lista_iterador_t *li);
struct nodo *lista_iterador_actual(const lista_iterador_t *li);
bool lista_iterador_siguiente(lista_iterador_t *li);
bool lista_iterador_termino(const lista_iterador_t *li);
void lista_iterador_eliminar(lista_iterador_t *li);

#endif
