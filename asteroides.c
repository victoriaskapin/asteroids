
asteroide_t asteroide;
disparo_t disparo;
lista_t *lista_asteroides;
lista_t *lista_disparos;



status_t asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo)
{
	lista_iterador_t *iterador = lista_iterador_crear(l);
	struct nodo *nodo_modulo = lista_iterador_actual(iterador);//me paro en el primer nodo
	asteroide_t asteroide_eliminado;

	while(nodo_modulo != NULL)//mientras que no llegue al final, avanzo
	{
		nodo_modulo = lista_iterador_actual(iterador);

		procesar_asteroide();

		if(distancia(nodo_modulo->dato, nave.posicion_x, nave.posicion_y) <= nodo_modulo->dato.radio)//choco con nave
		{
			asteroide_eliminado = lista_iterador_eliminar(iterador);
			if(lista_es_vacia(l))
				return ASTEROIDES_DESTRUIDOS;

			return NAVE_DESTRUIDA;
		}
		
		if(distancia(nodo_modulo->dato, disparo.posicion_x, disparo.posicion_y) <= nodo_modulo->dato.radio)//choco con disparo
		{
			
			for(int i=0; i<CANT_SUB_ASTEROIDES, i++)
				{
					asteroide_t asteroide_nuevo = cargar_asteroide((nodo_modulo->dato.radio)/2, nodo_modulo->dato.posicion_x, nodo_modulo->dato.posicion_y);//la posicion inicial del subasteroide es la final del anterior
					if((lista_insertar_final(lista_asteroides, asteroide_nuevo))==false) //cargo el ultimo nodo con la estructura
						return FALLA_MEMORIA;
				}

			asteroide_eliminado = lista_iterador_eliminar(iterador);//lo borro de la lista

			return ASTEOROIDE_DESTRUIDO;
		}

		if((lista_iterador_siguiente(iterador))==false)//avanzo al siguiente nodo
			break;
	}

	return FALSE;
}


float distancia(asteroide_t asteroide, float objeto_x, float objeto_y)
{
	float dx = asteroide.posicion_x - objeto_x;
	float dy = asteroide.posicion_y - objeto_y;
	return sqrt(dx*dx, dy*dy);
}

void 

asteroide_t cargar_asteroide(size_t radio, float x, float y)
{
	asteroide_t asteroide_nuevo;

	asteroide_nuevo.posicion_x = x;
	asteroide_nuevo.posicion_y = y;

	asteroide_nuevo.radio = radio;
	asteroide_nuevo.angulo = generar_aleatorio(NAVE_ANGULO_INICIAL, NAVE_ANGULO_INICIAL + PI);//un angulo entre 0 y pi
	
	asteroide_nuevo.velocidad_x = generar_aleatorio(VELOCIDAD_ASTEROIDE_ORIGINAL/radio + VELOCIDAD_ASTEROIDE_OFFSET, VELOCIDAD_ASTEROIDE_ORIGINAL/radio - VELOCIDAD_ASTEROIDE_OFFSET)
	asteroide_nuevo.velocidad_y = generar_aleatorio(VELOCIDAD_ASTEROIDE_ORIGINAL/radio + VELOCIDAD_ASTEROIDE_OFFSET, VELOCIDAD_ASTEROIDE_ORIGINAL/radio - VELOCIDAD_ASTEROIDE_OFFSET)


	return asteroide_nuevo;

}

float generar_aleatorio(float superior, float inferior)
{
	float numero_aleatorio=(rand()%RAND_MAX); /*da un numero entre 1 y RAND_MAX*/
	float random = (numero_aleatorio/RAND_MAX);//lo escalo para que de entre 0 y 1

	return random*(superior - inferior) + inferior;/*x entre x_max y x_min*/
}

void procesar_asteroide(lista_iterador_t * iterador)
{
	struct nodo nodo = lista_iterador_actual(iterador);	
	if(nodo->dato.radio == ASTEROIDE_RADIO_CHICO)//si destruyo uno chiquito, no se crean mas
	{
		//sumar puntos correspondientes

		asteroide_eliminado = lista_iterador_eliminar(iterador);//lo borro de la lista			
		if(lista_es_vacia(l))
			return ASTEROIDES_DESTRUIDOS;

		return ASTEOROIDE_DESTRUIDO;
	}

	if(nodo->dato.radio == ASTEROIDE_RADIO_MEDIANO)
				//sumar puntos correspondientes
			
	if(nodo->dato.radio == ASTEROIDE_RADIO_GRANDE) 
				//sumar puntos correspondientes

}

void crear_asteorides(size_t cantidad)//funcion que se llama cuando hay que crear asteroides de 0
{
	lista_asteroides = lista_crear();

	for(int i=0; i<cantidad; i++)
	{
		lista_sprites = 

		size_t i = (size_t)generar_aleatorio(PRIMER_ASTEROIDE, ULTIMO_ASTEROIDE);//numero entre 1 y 4
		
		asteroide_t asteroide_nuevo = cargar_asteroide(ASTEROIDE_RADIO_GRANDE, nodo_modulo->dato.posicion_x, nodo_modulo->dato.posicion_y);//la posicion inicial del subasteroide es la final del anterior
		if((lista_insertar_final(lista_asteroides, asteroide_nuevo))==false) //cargo el ultimo nodo con la estructura
	}

}