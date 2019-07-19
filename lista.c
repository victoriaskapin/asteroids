#include "lista.h"

struct nodo *nodo_crear(void *d) 
{
	struct nodo *n = malloc(sizeof(struct nodo)); //creo el nodo
	if(n == NULL)
		return NULL;

	n->sig = NULL;//como va a ser el ultimo, el siguiente lo apunto a null
	n->dato = d;//le asigno a dato la informacion de "d"

	return n;
}

lista_t *lista_crear() {
	lista_t *l = malloc(sizeof(lista_t));//pido memoria para una lista
	
	if(l == NULL)
		return NULL;

	l->prim = NULL;//primer nodo a null, lista vacia
	return l;
}


void lista_destruir(lista_t *l, void (*destruir_dato)(void *d)) //recibo la lista y la funcion con la cual voy a destruirla
{
	struct nodo *n = l->prim;//declaro un nodo que apunte al primer elemento de la lista
	while(n != NULL) {
	struct	nodo *sig = n->sig; //voy recorriendo la lista: con otro nodo que con cada iteracion se pare en el siguiente

		if(destruir_dato != NULL)//si la funcion de destruir existe, destruyo lo que hay en el nodo n
			destruir_dato(n->dato);

		free(n);//libero el nodo n

		n = sig;//paso al siguiente nodo con el nodo auxiliar sig.
	}

	free(l);//libero la lista.
}

bool lista_es_vacia(const lista_t *l) {
	return l->prim == NULL;
}

bool lista_insertar_comienzo(lista_t *l, void *d) //recibo la lista y el dato para el nodo que voy a crear
{
	struct nodo *n = nodo_crear(d);//creo el nodo con el dato que me pasan
	if(n == NULL)//valido
		return false;

	n->sig = l->prim;//conecto las variables de la estructura nodo: siguiente apunta al primer elemento de la lista
	l->prim = n;//el primer elemento de la lista pasa a ser el nodo creado

	return true;
}

bool lista_insertar_final(lista_t *l, void *d) {
	struct nodo *n = nodo_crear(d);
	if(n == NULL) return false;

	// Si está vacía inserto al principio:
	if(l->prim == NULL) //si la lista estaba vacia, el primer elemento pasa a ser el nodo
	{
		l->prim = n;
		return true;
	}

	// La lista no estaba vacía:
	struct nodo *aux = l->prim;//creo un nodo que apunta al primer elemento
	while(aux->sig != NULL)//voy recorriendo la lista hasta llegar al ultimo nodo(por eso la condicion de corte es cuando el aux->sig es NULL)
		aux = aux->sig;//como no era null, guardo el siguiente nodo en el auxiliar

	//a esta altura, aux tiene guardado el ultimo nodo de la lista.
	aux->sig = n;

	return true;
}

void *lista_extraer_primero(lista_t *l) {
	if(lista_es_vacia(l))
		return NULL;

	struct nodo *n = l->prim;//creo un nodo y le asigno el primer valor de la lista
	void *d = n->dato;//le asigno el dato a d

	l->prim = n->sig;//ahora el primer valor de la lista es el que antes era el siguiente
	free(n);//libero la memoria del nodo que estaba al principio

	return d;
}

void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b))//recibo la lista, el dato que quiero encontrar, y la funcion para comparar 
{

	struct nodo *n = l->prim;//creo un nodo auxiliar
	while(n != NULL) {
		if(cmp(n->dato, d) == 0)//comparo el nodo auxiliar en cada iteracion hasta encontrar una coincidencia entre su dato y d
			return n->dato;//devuelvo el dato

		n = n->sig;
	}

	return NULL;
}

void lista_mapear(lista_t *l, void *(*f)(void *dato))
{
	struct	nodo *nodo_aux = l->prim;

	while(nodo_aux!=NULL)
	{
		nodo_aux->dato = f(nodo_aux->dato);
		nodo_aux = nodo_aux->sig;
	}
}

lista_t *cargar_lista(sprite_t *modulo, lista_t *l)
{

	for(int i=0; i<6; i++)
	{
		if((lista_insertar_final(l, modulo->cords[i]))==false) //cargo el ultimo nodo con la fila de la matriz
			return false;
	}
	
	return l;
	//lista cargada
}

void lista_estructura_borrar(lista_t *l, void *estructura) 
{
   // Borro al principio:
   
   while(l->prim && l->prim->dato == estructura) 
   {
      struct nodo *aux = l->prim->sig;
      //free(l->prim->dato);
      //free(l->prim);
      l->prim = aux;
   }

   // Borro del resto:
   struct nodo *ant = l->prim;
   struct nodo *actual;
   while(ant->sig) 
   {
      actual = ant->sig;
      if(actual->dato == estructura) 
      {
         ant->sig = actual->sig;
        // free(actual->dato);
         //free(actual);
      }
      else
          ant = actual;
   }
}
