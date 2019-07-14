#include "nave.h"


void setear_conficiones_iniciales(nave_t *nave)
{

	nave_t nave_aux ={500, 400, 0, 0, 0, 0};
	*nave=nave_aux;
}

void nave_mover(nave_t *nave, float dt, size_t potencia)
{	


	nave->velocidad_x*=0.99;
	nave->velocidad_y*=0.99;

	float aceleracion_x = potencia*sin(nave->angulo_rotacion);
	float aceleracion_y = potencia*cos(nave->angulo_rotacion);
	

	//printf("angulo nave %f\n", nave->angulo_rotacion);
	//printf("ax %f\tay %f\n", aceleracion_x, aceleracion_y);



	nave->velocidad_x = computar_velocidad(nave->velocidad_x, aceleracion_x, dt);
	nave->velocidad_y = computar_velocidad(nave->velocidad_y, aceleracion_y, dt);

	//printf("vx %f\tvy %f\n", nave->velocidad_x, nave->velocidad_y);
	nave->posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
	nave->posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);


	if(nave->posicion_x<1)
		nave->posicion_x=VENTANA_ANCHO;

    if(nave->posicion_x>VENTANA_ANCHO)
		nave->posicion_x=1;


	//lista_mapear(l, rotar(nave, nave->angulo_rotacion)/*void *(*f)(void *dato)*/);//ESTO FALTA PULIRLO

}

bool nave_dibujar(nave_t x, SDL_Renderer *r)
{
	const char a[5]={"SHIP"};
	if((graficador_dibujar(r, a, 1, x.posicion_x, x.posicion_y, x.angulo_rotacion))==false)//las posiciones tienen que ser con el 0,0 abajo a la izq
		return false;
		
	return true;
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

double computar_velocidad(double vi, double aceleracion, double dt)
{
	return dt*aceleracion+vi;
}


size_t potencia_nave(nave_t nave, size_t paso_potencia)
{
	int potencia_temp=0;

	if((potencia_temp = nave.potencia + paso_potencia)>1000)//la potencia nunca sera mas de 1000
		return paso_potencia;

	return potencia_temp;
}


void trasladar(float **coordenadas, int n, float dx, float dy)
{
	for(int i=0; i<n; i++)
	{
		coordenadas[i][0] += dx;
		coordenadas[i][1] += dy;
	}

}

bool nave_destruir(nave_t*n)
{
	if(n!=NULL){
		free(n);
		return true;
	}
	else 
		return false;
}


nave_t nave_crear()
{
	nave_t nave;
	/*nave=malloc(sizeof(nave_t));
	if(nave==NULL)
		return NULL;*/

	nave.sp_nave=&sprite[0];//esto seria mas prolijo pidiendo que le cargue la que coincide con el nombre o en un define asociar el numero con la estructura onda #define ship 0 o un enum no se.  
	nave.escala=ESCALA_NAVE;//le agregue la escala al tda xq despues hay que pasarsela al graficador
	nave.posicion_x=NAVE_X_INICIAL;
	nave.posicion_y=NAVE_Y_INICIAL;
	nave.velocidad_x=NAVE_VX_INICIAL;
	nave.velocidad_y=NAVE_VY_INICIAL;
	nave.angulo_rotacion = NAVE_ANGULO_INICIAL;
	nave.potencia=0;

	return nave;
}