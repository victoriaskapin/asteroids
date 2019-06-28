
typedef struct
{
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo_rotacion;
	size_t potencia;
}nave_t



void nave_mover(nave_t *nave, float dt);
{	
	float aceleracion_x = nave->potencia*sin(-nave->angulo_rotacion);
	float aceleracion_y = nave->potencia*cos(-nave->angulo_rotacion);
	
	nave->velocidad_x = computar_velocidad(nave->velocidad_x, aceleracion_x, dt);
	nave->velocidad_y = computar_velocidad(nave->velocidad_y, aceleracion_y, dt);

	nave->posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
	nave->posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);

	if(nave->posicion_x<1)
		nave->posicion_x=VENTANA_ANCHO;

    if(nave->posicion_x>VENTANA_ANCHO)
		nave->posicion_x=1;

	lista_mapear(l, rotar(nave, nave->angulo_rotacion)/*void *(*f)(void *dato)*/);//ESTO FALTA PULIRLO

}

bool nave_dibujar(const nave_t *x, SDL_Renderer *r);
{

	if((graficador_dibujar(r, modulos[0]/*"SHIP"*/, 1, x->posicion_x, x->posicion_y, x->angulo_rotacion))==false)//las posiciones tienen que ser con el 0,0 abajo a la izq
		return false;
		
	return true;
}

size_t combustible_chorro(nave_t nave, size_t paso_potencia)
{	
	if(nave.cantidad_combustible>0)
	{
		nave.cantidad_combustible-=paso_potencia;
		return nave.cantidad_combustible;
	}

	return 0;
}

int potencia_nave(nave_t nave, size_t paso_potencia)
{
	int potencia_temp = nave.potencia + paso_potencia;

	if((potencia_temp>NAVE_MAX_POTENCIA || potencia_temp<0))
		return nave.potencia; //si cruza los limites, devuelvo la original

	return potencia_temp;
}

void rotar(float **coordenadas, int n, double rad)
{
	int i;
    float coseno_rad = cos(rad);
    float seno_rad = sin(rad);
    float x_rotada, y_rotada;
    
	for(i=0; i<n; i++)
	{
		x_rotada = (coordenadas[i][0])*coseno_rad - (coordenadas[i][1])*seno_rad;
		y_rotada = (coordenadas[i][0])*seno_rad + (coordenadas[i][1])*coseno_rad;
		
		coordenadas[i][0] = x_rotada;
		coordenadas[i][1] = y_rotada;
		
	}

}

/*void computar_parametros(struct nave_t nave, float paso_tiempo)
{


	size_t tamanio_nave = sizeof(nave_grande) / sizeof(nave_grande[0]);
	float **mi_nave;

	*nave.aceleracion_x = *nave.potencia*sin(-*nave.angulo_rotacion);
	*nave.aceleracion_y = *nave.potencia*cos(-*nave.angulo_rotacion) - G;
	
	*nave.velocidad_x = computar_velocidad(*nave.velocidad_x, *nave.aceleracion_x, paso_tiempo*10);
	*nave.velocidad_y = computar_velocidad(*nave.velocidad_y, *nave.aceleracion_y, paso_tiempo*10);

	*nave.posicion_x = computar_posicion(*nave.posicion_x, *nave.velocidad_x, paso_tiempo);
	*nave.posicion_y = computar_posicion(*nave.posicion_y, *nave.velocidad_y, paso_tiempo);

	if(*nave.posicion_x<1)
		*nave.posicion_x=VENTANA_ANCHO;

    if(*nave.posicion_x>VENTANA_ANCHO)
		*nave.posicion_x=1;

	mi_nave=matriz_a_vector(nave_grande, tamanio_nave);
	rotar(mi_nave, tamanio_nave, *nave.angulo_rotacion);	
	trasladar(mi_nave, tamanio_nave, *nave.posicion_x-NAVE_X_INICIAL, *nave.posicion_y-NAVE_Y_INICIAL);
	renderizar_flotantes(mi_nave, escala, tamanio_nave, DEFASAJE_NAVE_X, DEFASAJE_NAVE_Y, renderer);
    destruir_vector_float(mi_nave, tamanio_nave);

}*/

