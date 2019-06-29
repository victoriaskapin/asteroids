#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo{
	struct nodo *sig;
	void *dato;
};

typedef struct nodo nodo_t;

typedef struct {
	struct nodo *prim;
}lista_t;

//le pasas la lista de donde lo queres eliminar, el puntero al nodo que queres eliminar y un puntero a la funcion que compara

bool eliminarnodo_actual (lista_t * l, nodo_t *eliminar, bool (*comparar)(void * dato1, void *dato2)){
	nodo_t *actual, *anterior;
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

nodo_t* crear_nodo(){
	nodo_t * n;
	n=malloc(sizeof(nodo_t));
	if(n==NULL){
		puts("no se asigno memoria a n");
	}
	return n;
}

void imprimir_lista(lista_t*l){
	nodo_t*iterador;
	iterador=l->prim;
	while(iterador!=NULL){
		printf("%i\t",*(int*)iterador->dato);
		iterador=iterador->sig;
	}
}
*/
