#include "asteroides.h"

status_t asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo)
{
	lista_iterador_t *iterador = lista_iterador_crear(lista_asteroides);
	struct nodo *nodo_modulo = lista_iterador_actual(iterador);//me paro en el primer nodo
	//asteroide_t asteroide_eliminado;

	while(nodo_modulo != NULL)//mientras que no llegue al final, avanzo
	{
		nodo_modulo = lista_iterador_actual(iterador);

		asteroide_t *asteroid;
		asteroid = (asteroide_t *)(nodo_modulo->dato); 

		if(distancia(nodo_modulo->dato, nave.posicion_x, nave.posicion_y) <= asteroid->radio)//choco con nave
		{
			lista_iterador_eliminar(iterador);
			return NAVE_DESTRUIDA;
		}
		
		if(distancia(nodo_modulo->dato, disparo.posicion_x, disparo.posicion_y) <= asteroid->radio)//choco con disparo
		{
			if(procesar_asteroide(iterador)!=ASTEROIDE_RADIO_CHICO)//se encarga de saber de que tamaño era el asteroide destruido
				for(int i=0; i<CANT_SUB_ASTEROIDES; i++)
					{
						asteroide_t *asteroide_nuevo = cargar_asteroide((asteroid->radio)/2, asteroid->posicion_x, asteroid->posicion_y);//la posicion inicial del subasteroide es la final del anterior
						if((lista_insertar_final(lista_asteroides, asteroide_nuevo))==false) //cargo el ultimo nodo con la estructura
							return FALLA_MEMORIA;
					}

			lista_iterador_eliminar(iterador);//lo borro de la lista
			return ASTEOROIDE_DESTRUIDO;
		}


		if((lista_iterador_siguiente(iterador))==false)//avanzo al siguiente nodo
			break;
	}

	return FALSE;
}


float distancia(void *asteroide, float objeto_x, float objeto_y)
{
	asteroide_t *asteroid;
	asteroid = (asteroide_t *)asteroide; 
	float dx = (float)asteroid->posicion_x - objeto_x;
	float dy = (float)asteroid->posicion_y - objeto_y;

	float modulo_cuadrado = dx*dx + dy*dy;
	return sqrt(modulo_cuadrado);
}


asteroide_t *cargar_asteroide(size_t radio, float x, float y)
{
	asteroide_t *asteroide_nuevo;

	asteroide_nuevo=malloc(sizeof(asteroide_t));

	asteroide_nuevo->posicion_x = x;
	asteroide_nuevo->posicion_y = y;

	asteroide_nuevo->radio = radio;
	asteroide_nuevo->angulo_rotacion = generar_aleatorio(NAVE_ANGULO_INICIAL, NAVE_ANGULO_INICIAL + PI);//un angulo entre 0 y pi
	
	asteroide_nuevo->velocidad_x = generar_aleatorio(VELOCIDAD_ASTEROIDE_ORIGINAL/radio + VELOCIDAD_ASTEROIDE_OFFSET, VELOCIDAD_ASTEROIDE_ORIGINAL/radio - VELOCIDAD_ASTEROIDE_OFFSET);
	asteroide_nuevo->velocidad_y = generar_aleatorio(VELOCIDAD_ASTEROIDE_ORIGINAL/radio + VELOCIDAD_ASTEROIDE_OFFSET, VELOCIDAD_ASTEROIDE_ORIGINAL/radio - VELOCIDAD_ASTEROIDE_OFFSET);


	return asteroide_nuevo;

}

size_t procesar_asteroide(lista_iterador_t * iterador)
{
	struct nodo *nodo = lista_iterador_actual(iterador);	
	
	asteroide_t *asteroid;
	asteroid = (asteroide_t*)nodo->dato;

	if(asteroid->radio == ASTEROIDE_RADIO_CHICO)//si destruyo uno chiquito, no se crean mas
	{
		//sumar puntos correspondientes
		lista_iterador_eliminar(iterador);//lo borro de la lista			
		//if(lista_es_vacia(l))
		//	return ASTEROIDES_DESTRUIDOS;
	}

	else if(asteroid->radio == ASTEROIDE_RADIO_MEDIANO)
		printf("primer else\n");
				//sumar puntos correspondientes
			
	else if(asteroid->radio == ASTEROIDE_RADIO_GRANDE) 
		printf("segundo else\n");
				//sumar puntos correspondientes

	return asteroid->radio;

}

void crear_asteorides(size_t cantidad)//funcion que se llama cuando hay que crear asteroides de 0
{
	lista_asteroides = lista_crear();

	for(int i=0; i<cantidad; i++)
	{
		//size_t i = (size_t)generar_aleatorio(1, 5);//numero entre 1 y 4
		
		asteroide_t *asteroide_nuevo = cargar_asteroide(ASTEROIDE_RADIO_GRANDE, 0, 0/*nodo_modulo->dato.posicion_y*/);//la posicion inicial del subasteroide es la final del anterior
		if((lista_insertar_final(lista_asteroides, asteroide_nuevo))==false) //cargo el ultimo nodo con la estructura
			return;
	
	}
	printf("creo asteroides\n");

}

bool asteroide_dibujar(asteroide_t x, SDL_Renderer *r)
{
	lista_iterador_t *iterador = lista_iterador_crear(lista_asteroides);
	struct nodo *nodo_modulo;

	while(nodo_modulo != NULL)//mientras que no llegue al final, avanzo
	{
		nodo_modulo = lista_iterador_actual(iterador);

		//asteroide_t *asteroid;
		//asteroid = (asteroide_t *)(nodo_modulo->dato); 

		//int tipo_asteroide = procesar_asteroide(iterador);

		const char a[6]={"ROCK1"};

		if((graficador_dibujar(r, a, 1, x.posicion_x, x.posicion_y, x.angulo_rotacion))==false)//las posiciones tienen que ser con el 0,0 abajo a la izq
			return false;

		if((lista_iterador_siguiente(iterador))==false)//avanzo al siguiente nodo
			break;

	}
	return true;
}

//void procesar_choque()