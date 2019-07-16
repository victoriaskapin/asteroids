#include "nave.h"

nave_t nave_crear()
{
	nave_t nave;

	nave.sp_nave= &sprite[0];
	nave.sp_chorro= sprite[1];
	nave.vida=1;
	nave.escala=ESCALA_NAVE;//le agregue la escala al tda xq despues hay que pasarsela al graficador
	nave.posicion_x=NAVE_X_INICIAL;
	nave.posicion_y=NAVE_Y_INICIAL;
	nave.velocidad_x=NAVE_VX_INICIAL;
	nave.velocidad_y=NAVE_VY_INICIAL;
	nave.angulo_rotacion = NAVE_ANGULO_INICIAL;
	nave.potencia=NAVE_POTENCIA_INICIAL;

	return nave;
}

void nave_mover(nave_t *nave, float dt, size_t potencia)
{	

	nave->velocidad_x*=0.99;
	nave->velocidad_y*=0.99;

	float aceleracion_x = potencia*cos(nave->angulo_rotacion);
	float aceleracion_y = potencia*sin(nave->angulo_rotacion);

	nave->velocidad_x = computar_velocidad(nave->velocidad_x, aceleracion_x, dt);
	nave->velocidad_y = computar_velocidad(nave->velocidad_y, -aceleracion_y, dt);

	nave->posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
	nave->posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);


	if(nave->posicion_x < 0)
		nave->posicion_x = VENTANA_ANCHO;

    if(nave->posicion_x > VENTANA_ANCHO)
		nave->posicion_x = 0;

	if(nave->posicion_y < 0)
		nave->posicion_y = VENTANA_ALTO;

	if(nave->posicion_y > VENTANA_ALTO)
		nave->posicion_y = 0;


	//lista_mapear(l, rotar(nave, nave->angulo_rotacion)/*void *(*f)(void *dato)*/);//ESTO FALTA PULIRLO

}

bool nave_dibujar(nave_t *nave, SDL_Renderer *r)
{
	if(graficador_dibujar(r, nave->sp_nave->nombre, nave->escala, nave->posicion_x, nave->posicion_y, nave->angulo_rotacion)==true){
		if(nave->potencia > 0)
			return(graficador_dibujar(r, nave->sp_chorro.nombre, nave->escala, nave->posicion_x, nave->posicion_y, nave->angulo_rotacion));
		else 
			return true;
	}
	else 
		return false;
}

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



