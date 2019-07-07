#include "iterador.h"
#include "lista.h"
#include <stdlib.h>



lista_iterador_t *lista_iterador_crear(lista_t *l)
{
	lista_iterador_t *iterador;

	if((iterador= malloc(sizeof(lista_iterador_t)))==NULL)//pido memoria para un iterador
		return NULL;

	//iterador->nodo_iterador = NULL;//primer nodo a null, lista vacia

	iterador->nodo_anterior = NULL;
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
	
	li->nodo_anterior = li->nodo_iterador;
	li->nodo_iterador = li->nodo_iterador->sig;
	return true;

}

bool lista_iterador_termino(const lista_iterador_t *li)
{
	if(li->nodo_iterador->sig == NULL)
		return true;

	return false;
}

/*void *lista_iterador_eliminar(lista_iterador_t *li)
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
	if((lista_iterador_siguiente(iterador))==false)
			break;

	return li->nodo_iterador->dato;
}*/

bool eliminarnodo_actual (lista_t * l, struct nodo *eliminar, bool (*comparar)(void * dato1, void *dato2)){
	struct nodo *actual, *anterior;
	actual=l->prim;
	
	if(comparar(l->prim,eliminar)){
		actual=actual->sig;
		//free(l->prim->dato);
		free(l->prim);
		l->prim=actual;
		return true;
	}

	anterior=l->prim;
	actual=actual->sig;

	while (actual!=NULL){
		if(comparar(actual,eliminar)){
			anterior->sig=actual->sig;
			//free(actual->dato); 
			//esto es por si el dato tambien pide memoria. Si es estatico no hay que ponerlo, chequear cuando carguemos las listas. 
			free(actual);
			return true;
		}
		anterior=anterior->sig;
		actual=actual->sig;
	}
	return false;
}

bool comparar_punteros(void *a,void *b){
	return (a==b);
}

/* FUNCIONES AUXILIARES QUE HICE PARA PROBAR LA ANTERIOR 
LAS DEJO POR SI LAS DUDAS
struct nodo* crear_nodo(){
	struct nodo * n;
	n=malloc(sizeof(struct nodo));
	if(n==NULL){
		puts("no se asigno memoria a n");
	}
	return n;
}
void imprimir_lista(lista_t*l){
	struct nodo*iterador;
	iterador=l->prim;
	while(iterador!=NULL){
		printf("%i\t",*(int*)iterador->dato);
		iterador=iterador->sig;
	}
}
*/

void lista_iterador_eliminar(lista_iterador_t *li) {
	
	if(li->nodo_iterador == NULL)
		return;
	
	if(li->nodo_anterior == NULL) //el elemento a eliminar es el primero de la lista
	{
		free(li->nodo_iterador);
		li->nodo_iterador = li->nodo_iterador->sig;
		//return lista_extraer_primero(li->l);
	}

	void *d = li->nodo_iterador->dato;

	li->nodo_anterior->sig = li->nodo_iterador->sig;
	struct nodo *aux = li->nodo_iterador->sig;
	free(li->nodo_iterador);
	li->nodo_iterador = aux;

	//return d;
}
