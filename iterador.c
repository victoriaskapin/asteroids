#include "iterador.h"
#include "lista.h"
#include <stdlib.h>



lista_iterador_t *lista_iterador_crear(lista_t *l)
{
	lista_iterador_t *iterador;

	if((iterador= malloc(sizeof(lista_iterador_t)))==NULL)//pido memoria para un iterador
		return NULL;

	//iterador->nodo_iterador = NULL;//primer nodo a null, lista vacia

	iterador->nodo_iterador = l->prim;

	return iterador;

}


void lista_iterador_destruir(lista_iterador_t *li)
{
	free(li);
}


struct nodo *lista_iterador_actual(const lista_iterador_t *li)
{
	if(li->nodo_iterador==NULL)
		return NULL;

	return li->nodo_iterador;
}

bool lista_iterador_siguiente(lista_iterador_t *li)
{
	if(li->nodo_iterador->sig==NULL)
		return false;

	li->nodo_iterador = li->nodo_iterador->sig;
	return true;

}

bool lista_iterador_termino(const lista_iterador_t *li)
{
	if(li->nodo_iterador->sig == NULL)
		return true;

	return false;
}

void *lista_iterador_eliminar(lista_iterador_t *li)
{

   //while(l->prim && l->prim->dato == estructura) 
	  struct nodo *anterior = l->prim;

      li->nodo_iterador = li->nodo_iterador->sig;
      
      free(l->prim);
      
      l->prim = aux;
   }

   // Borro del resto:
   struct nodo *ant = l->prim;
   while(ant->sig) 
   {
      struct nodo *actual = ant->sig;
      if(actual->dato == estructura) 
      {
         ant->sig = actual->sig;
         free(actual);
      }
      else
          ant = actual;
   }
	if((lista_iterador_siguiente(iterador))==false)//avanzo al siguiente nodo
			break;

	return li->nodo_iterador->dato;
}