#include "disparos.h"

disparo_t * disparo_crear(float px, float py, float angulo){
	disparo_t * shot; 
	shot = malloc(sizeof(disparo_t));
	if (shot==NULL)
		return NULL;

	shot->sp_disparo=sprite[6];	
	shot->posicion_x=px+cos(angulo);
	shot->posicion_y=py+sin(angulo);
	shot->angulo=angulo;
	shot->velocidad=VELOCIDAD_DISPARO;
	shot->tiempo_vida= TIEMPO_VIDA_SHOT;
	shot->escala=ESCALA_DISPARO; 

	return shot;
}

void disparo_destruir(disparo_t *shot){
	free(shot);
} 

bool disparo_dibujar(disparo_t *shot,SDL_Renderer *r){
	if(shot->tiempo_vida>0.0){
		return graficador_dibujar(r,
				shot->sp_disparo.nombre, 
				shot->escala, 
				shot->posicion_x,
				shot->posicion_y, 
				shot->angulo);
	}
	else 
		return false;
}

void disparo_mover(disparo_t *shot, float dt){
	(shot->tiempo_vida)+=-1.0;
	if (shot->tiempo_vida>0.0){
		shot->posicion_x=computar_posicion(shot->posicion_x+cos(shot->angulo),shot->velocidad,dt);
		shot->posicion_y=computar_posicion(shot->posicion_y+sin(-shot->angulo),shot->velocidad,dt);
	}
}

bool cargar_disparos(lista_t *l_shot,float px,float py,float angulo){
	disparo_t * shot = disparo_crear(px,py,angulo);//creo un disparo nuevo.
	return (lista_insertar_comienzo(l_shot,shot));//cargo en el comienzo de la lista de disparos el nuevo disparo
}

void mover_lista_disparos(lista_t*l_shot,float dt){
	struct nodo *aux;
	aux= l_shot->prim;
	while(aux!=NULL){
		disparo_mover(((disparo_t*)aux->dato),dt);
		aux=aux->sig;
	}
}

bool dibujar_lista_disparos(lista_t*l_shot,SDL_Renderer *r){
	struct nodo *aux;
	if(l_shot->prim==NULL)//caso lista vacia
		return false;

	aux= l_shot->prim;
	while(aux!=NULL){

		if(disparo_dibujar(((disparo_t*)aux->dato),r)==false)
			aux=aux->sig;
		else
			aux=aux->sig;
	}

	return true;
}
/*
bool eliminar_disparos(lista_t *l_shot){
	lista_iterador_t *li;
	li= lista_iterador_crear(l_shot);
	if(li==NULL)
		return false;
	while(lista_iterador_siguiente(li)){
		struct nodo* disparo =lista_iterador_actual(li);
		if (asteroide_choco(disparo->dato)==2)
			iterador_eliminar(li);
		if(disparo->dato->tiempo_vida<=0)
			iterador_eliminar(li);
	}
	lista_iterador_eliminar(li);
}*/