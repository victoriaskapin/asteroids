#include "config.h"
#include "objetos.h"

disparo_t * disparo_crear(float px, float py, float angulo){
	disparo_t * shot; 
	shot = malloc(sizeof(disparo_t));
	if (shot==NULL)
		return NULL;

	shot->sp_disparo=sprite[6];
	shot->posicion_x=px;
	shot->posicion_y=py;
	shot->angulo=angulo;
	shot->velocidad=VELOCIDAD_DISPARO;
	shot->tiempo_vida= TIEMPO_VIDA_SHOT;
	shot->escala=ESCALA_DISPARO;

	return shot;
}

void disparo_destruir(disparo_t *shot){
	free(shot);
}
//asteroide destruido = 2 en el enum me parece que es mas facil ponerlo en la funcion de asteroide  

bool disparo_dibujar(disparo_t *shot,SDL_Renderer *r){
	if(shot.tiempo_vida>0){
		return graficador_dibujar(r,
								shot->sp_disparo.nombre, 
								shot->escala, 
								shot->posicion_x,
								shot->posicion_y, 
								shot->angulo;)
	}
	else 
		return false;
}

void disparo_mover(disparo_t *shot, float dt){
	shot.tiempo_vida-=1.0;
	if (shot.tiempo_vida<0)
		disparo_destruir(shot);

	trasladar(shot->sp_disparo.cords,shot->sp_disparo.n,1.0,1.0);
}

void trasladar(float **coordenadas, int n, float dx, float dy)
{
	for(int i=0; i<n; i++)
	{
		coordenadas[i][0] += dx;
		coordenadas[i][1] += dy;
	}

}

lista_t *l_shot=lista_crear();

bool cargar_disparos(lista_t *l_shot,float px,float py,float angulo){
	disparo_t * shot = disparo_crear(px,py,angulo);
	return (lista_insertar_comienzo(l_shot,shot));
}

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
}