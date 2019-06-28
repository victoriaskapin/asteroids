#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "funciones.h"
#include "config.h"
#include "caracteres.h"
#include "diccionario.h"
#include "naves.h"


double computar_velocidad(double vi, double aceleracion, double dt)
{
	return dt*aceleracion+vi;
}

double computar_posicion(double pi, double vi, double dt)
{
	return dt*vi+pi;
}

float **matriz_a_vector(const float m[][MAX_COORDENADAS], size_t n)
{
	size_t i, j;
	float **vector;

	vector = crear_vector(n, MAX_COORDENADAS);

	for(i=0; i<n; i++)
		for(j=0; j<MAX_COORDENADAS; j++)
			vector[i][j] = m[i][j];

	return vector;
}

void destruir_vector_float(float **vector, size_t n)
{
	size_t i;

	for(i=0;i<n;i++)
		free(vector[i]);/*libero cada elemento de las filas*/
	
	free(vector);/*libero lo mas "externo" del puntero*/
}

void destruir_vector_int(int **vector, size_t n)
{
	size_t i;

	for(i=0;i<n;i++)
		free(vector[i]);/*libero cada elemento de las filas*/
	
	free(vector);/*libero lo mas "externo" del puntero*/
}


float **densificar_vector(float **v, size_t nv, size_t nn, float margen)
{
	size_t nuevas_coordenadas = nn - nv;/*mi nuevo vector va a tener nn coordenadas, combinacion de las viejas(nn coordenadas) con las nuevas(nuevas_coordenadas)*/
	int i, j;
	float **vector_auxiliar, **nuevo_vector;

    vector_auxiliar = crear_vector(nuevas_coordenadas, MAX_COORDENADAS);//pido memoria para el vector auxiliar

	generar_puntos_aleatorio(v, vector_auxiliar, nv, nuevas_coordenadas, margen);//cargo el vector auxiliar con puntos aleatorios

	nuevo_vector = crear_vector(nn, MAX_COORDENADAS);  	/*pido memoria para vector nuevo*/

	for(i=0; i<nv; i++)
		for(j=0; j<MAX_COORDENADAS; j++)
			nuevo_vector[i][j]=v[i][j];/*completo el vector nuevo con el viejo*/
	
	for(i=nv; i<nn; i++)
		for(j=0; j<MAX_COORDENADAS; j++)
			nuevo_vector[i][j]=vector_auxiliar[i-nv][j]; 

	 ordenar(nuevo_vector, nn);
	destruir_vector_float(vector_auxiliar, nuevas_coordenadas);	/*libero la memoria de los vectores que ya no uso*/

	return nuevo_vector;
}

float **crear_vector(size_t filas, size_t columnas)
{
    float **vector;
    size_t i;

	if((vector = malloc(filas*sizeof(float*)))==NULL)
		return NULL;
	for(i=0; i<filas; i++)
	    if((vector[i] = malloc(columnas*sizeof(float)))==NULL) /*pido memoria para todas las columnas*/
		{
			destruir_vector_float(vector, filas);
	    	return NULL;
		}

	return vector;
}

void generar_puntos_aleatorio(float **vector_original, float **vector_aleatorio, size_t filas_originales, size_t filas_nuevas, float margen)
{
	size_t i, j;
	float random, x_aleatorio, y_aleatorio;

	for(i=0; i<filas_nuevas; i++)/*quiero generar tantas coordenadas aleatorias como el numero nuevas_coordenadas*/
	{
		x_aleatorio = generar_x_aleatorio(&random, vector_original, filas_originales);
		for(j=0; j<filas_originales; j++)/*cantidad de coordenadas originales, los nuevos puntos caen en algun intervalo de estas*/
	    	if(x_aleatorio>vector_original[j][PRIMERA_COORDENADA] && x_aleatorio<=vector_original[j+1][PRIMERA_COORDENADA])
	    	{
				generar_y_aleatorio(&y_aleatorio, vector_original, j, x_aleatorio, margen, random);
	    		/*hago un vector de nuevas coordenadas que va a estar desordenado*/
	    		vector_aleatorio[i][PRIMERA_COORDENADA] = x_aleatorio;
	    		vector_aleatorio[i][SEGUNDA_COORDENADA] = y_aleatorio;

	    	}

	}
}

void ordenar(float **vector, size_t max_puntos)
{
	int i,j;
  	float aux_x, aux_y;
	for(i=1; i<max_puntos; i++)
		for(j=0; j<max_puntos-i; j++)
			if(vector[j][0]>vector[j+1][0])
			{
			    aux_x  = vector[j+1][0];
			    aux_y  = vector[j+1][1];

				vector[j+1][0] = vector[j][0];
				vector[j+1][1] = vector[j][1];

				vector[j][0] = aux_x;
				vector[j][1] = aux_y;

			}
}

void generar_y_aleatorio(float *y_aleatorio, float **vector_original, size_t i, float x_aleatorio, float margen, float random)
{
	float y_inferior, y_superior, x1, x2, y1, y2;

	x1 = vector_original[i][PRIMERA_COORDENADA];
	x2 = vector_original[i+1][PRIMERA_COORDENADA];
	y1 = vector_original[i][SEGUNDA_COORDENADA];
	y2 = vector_original[i+1][SEGUNDA_COORDENADA];

	/*Ecuaciones para hallar las rectas que delimitan la densificacion*/
	y_superior=((y2-y1)*((x_aleatorio-x1)/(x2-x1)))+y1+margen;
	y_inferior=((y2-y1)*((x_aleatorio-x1)/(x2-x1)))+y1-margen;

	*y_aleatorio = random*(y_superior - y_inferior) + y_inferior;/*punto "y" dentro de la densificacion = random*(y_superior - y_inferior) + y_inferior       da un punto entre -margen y +margen , coordenada y*/

}

float generar_x_aleatorio(float *random, float **vector_original, int filas_originales)
{

	float numero_aleatorio=(rand()%RAND_MAX); /*da un numero entre 1 y RAND_MAX*/
	float aux;
	*random = (numero_aleatorio/RAND_MAX);/*numero aleatorio entre 0 y 1*/
	aux = *random*(vector_original[filas_originales-1][PRIMERA_COORDENADA] - vector_original[PRIMER_FILA][PRIMERA_COORDENADA]) + vector_original[PRIMER_FILA][PRIMERA_COORDENADA];/*x entre x_max y x_min*/
	return aux;
}

bool esta_arriba(float **coordenadas, int n, float x, float y)
{
	/*Se asume que las coordenadas ingresadas pertenecen a algun intervalo de los valores del vector coordenadas*/
	int i;
	float recta_y;

	for(i=0; i<n-1; i++)
	{
	    if(x>coordenadas[i][0])
	    {	
	    	if(x<=coordenadas[i+1][0])
	    	{
	    		/*Ecuacion para hallar la coordenada y de la recta que une los puntos del vector, y que corresponde a la coordenada x ingresada*/
	    		recta_y=(((x-coordenadas[i][0])/(coordenadas[i+1][0]-coordenadas[i][0]))*(coordenadas[i+1][1]-coordenadas[i][1]))+coordenadas[i][1];
	    		
	    		if(y>recta_y)
	    			return true;
			}

		}

	}

	return false;
}


void computar_parametros(struct parametros_nave_t nave, float paso_tiempo, SDL_Renderer *renderer, float **mi_chorro_llama)
{
	const float chorro[3][2] = {
		{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
		{0, NAVE_GRANDE_TOBERA_Y},
		{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};


	size_t tamanio_nave = sizeof(nave_grande) / sizeof(nave_grande[0]);
	float **mi_nave, **mi_chorro;
	int chorro_tam=3, escala=1;

	*nave.aceleracion_x = *nave.potencia*sin(-*nave.angulo_rotacion);
	*nave.aceleracion_y = *nave.potencia*cos(-*nave.angulo_rotacion) - G;
	
	*nave.velocidad_x = computar_velocidad(*nave.velocidad_x, *nave.aceleracion_x, paso_tiempo*10);
	*nave.velocidad_y = computar_velocidad(*nave.velocidad_y, *nave.aceleracion_y, paso_tiempo*10);

	*nave.posicion_x = computar_posicion(*nave.posicion_x, *nave.velocidad_x, paso_tiempo);
	*nave.posicion_y = computar_posicion(*nave.posicion_y, *nave.velocidad_y, paso_tiempo);//aca en vez de pasarle un punto de posicion, le tengo que pasar todos, osea la matriz

	if(*nave.posicion_x<1)
		*nave.posicion_x=VENTANA_ANCHO;

    if(*nave.posicion_x>VENTANA_ANCHO)
		*nave.posicion_x=1;

	mi_nave=matriz_a_vector(nave_grande, tamanio_nave);
	rotar(mi_nave, tamanio_nave, *nave.angulo_rotacion);	
	trasladar(mi_nave, tamanio_nave, *nave.posicion_x-NAVE_X_INICIAL, *nave.posicion_y-NAVE_Y_INICIAL);
	renderizar_flotantes(mi_nave, escala, tamanio_nave, DEFASAJE_NAVE_X, DEFASAJE_NAVE_Y, renderer);
    destruir_vector_float(mi_nave, tamanio_nave);

	mi_chorro=matriz_a_vector(chorro, chorro_tam);
	mi_chorro[1][1]=mi_chorro_llama[1][1];//asigno a la llama del chorro su tamaNIO
	rotar(mi_chorro, chorro_tam, *nave.angulo_rotacion);
	trasladar(mi_chorro, chorro_tam, *nave.posicion_x-NAVE_X_INICIAL, *nave.posicion_y-NAVE_Y_INICIAL);
	renderizar_flotantes(mi_chorro, escala, chorro_tam, DEFASAJE_NAVE_X, DEFASAJE_NAVE_Y, renderer);
	destruir_vector_float(mi_chorro, chorro_tam);

}

void trasladar(float **coordenadas, int n, float dx, float dy)
{
	int i;

	for(i=0; i<n; i++)
	{
		coordenadas[i][0] += dx;
		coordenadas[i][1] += dy;
	}

}


float ** crear_terreno ( size_t * n ) {
	* n = 0;

	const float terreno_estatico [][2] = {
		{0 , 100} ,							//izquierda
		{ -1 , VENTANA_ALTO * 2.0 / 3} ,	//"medio"
		{ VENTANA_ANCHO , 100}				//derecha
	};
	size_t nt = 3;
	float ** terreno = matriz_a_vector( terreno_estatico , nt ) ;
	if ( terreno == NULL ) return NULL ;

	srand (time(NULL));
	// Asignamos la coordenada del medio aleatoriamente :
	terreno [1][0] = rand () % VENTANA_ANCHO ;

	// Iterativamente densificamos PRIMER_RENGLON veces achicando el margen cada vez :
	for ( size_t i = 1; i < 40; i ++) {
		float ** aux = densificar_vector ( terreno , nt , 2 * ( i + 5) , 100/i) ;
		destruir_vector_float ( terreno , nt ) ;

		if ( aux == NULL ) return NULL ;
		terreno = aux ;
		nt = 2 * ( i + 5) ;

	}

	* n = nt ;

	return terreno ;
}


void renderizar_flotantes(float **objeto_grafico, float escala, int filas, int defasaje_x, int defasaje_y, SDL_Renderer *renderer)
{
	for(int i = 0; i < filas - 1; i++)
		SDL_RenderDrawLine(
		renderer,
		(objeto_grafico[i][0] * escala) + defasaje_x,
		(-objeto_grafico[i][1] * escala) + (defasaje_y),
		(objeto_grafico[i+1][0] * escala) + defasaje_x,
		(-objeto_grafico[i+1][1] * escala) + (defasaje_y)
		);

}

void renderizar_enteros(const int objeto_grafico[][2], int escala, int filas, int defasaje_x, int defasaje_y, SDL_Renderer *renderer)
{
	for(int i = 0; i < filas - 1; i++)
		SDL_RenderDrawLine(
		renderer,
		objeto_grafico[i][0] * escala + defasaje_x,
		-objeto_grafico[i][1] * escala + defasaje_y,
		objeto_grafico[i+1][0] * escala + defasaje_x,
		-objeto_grafico[i+1][1] * escala + defasaje_y
		);

}

void renderizar_enteros_variables(int **objeto_grafico, int escala, int filas, int defasaje_x, int defasaje_y, SDL_Renderer *renderer)
{
	for(int i = 0; i < filas - 1; i++)
		SDL_RenderDrawLine(
		renderer,
		objeto_grafico[i][0] * escala + defasaje_x,
		-objeto_grafico[i][1] * escala + defasaje_y,
		objeto_grafico[i+1][0] * escala + defasaje_x,
		-objeto_grafico[i+1][1] * escala + defasaje_y
		);

}

int *entero_a_digitos(int parametro)
{
	int *vector_digitos;

	if((vector_digitos=malloc(MAX_DIGITOS*sizeof(int)))==NULL)
		return NULL;

    for(int i=0; i<MAX_DIGITOS; i++)
    {
        vector_digitos[i]=parametro%10;
        parametro/=10;
    }
    return vector_digitos;
}

void imprimir_parametros(SDL_Renderer *renderer, int escala, int primera_sangria, int posicion_y, int digitos_parametro[])
{
	int separador_caracteres = 7, filas;
	int **matriz_caracter;
	for(int i=0; i<MAX_DIGITOS; i++)
	{
		matriz_caracter = opcion_letra_a_cadena((int)digitos_parametro[i], &filas); 
		renderizar_enteros_variables(matriz_caracter, escala, filas, primera_sangria-separador_caracteres*i, posicion_y, renderer);
		destruir_vector_int(matriz_caracter, filas);
	}	
}


void imprimir_caracteres(SDL_Renderer *renderer)
{
	int escala_caracteres = 1;
	size_t longitud;

	longitud=strlen(MSJ_SCORE);
	imprimir_mensaje_aterrizaje(renderer, MSJ_SCORE, longitud, PRIMERA_SANGRIA, PRIMER_RENGLON, escala_caracteres);
	
	longitud=strlen(MSJ_TIME);
		imprimir_mensaje_aterrizaje(renderer, MSJ_TIME, longitud, PRIMERA_SANGRIA, SEGUNDO_RENGLON, escala_caracteres);

	longitud=strlen(MSJ_FUEL);
		imprimir_mensaje_aterrizaje(renderer, MSJ_FUEL, longitud, PRIMERA_SANGRIA, TERCER_RENGLON, escala_caracteres);

	longitud=strlen(MSJ_ALTITUDE);
	imprimir_mensaje_aterrizaje(renderer, MSJ_ALTITUDE, longitud, SEGUNDA_SANGRIA, PRIMER_RENGLON, escala_caracteres);

	longitud=strlen(MSJ_HORIZONTAL_SPEED);
		imprimir_mensaje_aterrizaje(renderer, MSJ_HORIZONTAL_SPEED, longitud, SEGUNDA_SANGRIA, SEGUNDO_RENGLON, escala_caracteres);

	longitud=strlen(MSJ_VERTICAL_SPEED);
	imprimir_mensaje_aterrizaje(renderer, MSJ_VERTICAL_SPEED, longitud, SEGUNDA_SANGRIA, TERCER_RENGLON, escala_caracteres);

}

void imprimir_variable(int tiempo, SDL_Renderer *renderer, struct parametros_nave_t nave)
{
	int *parametros_enteros;        
	int sangria_flechas = 150;
	int primera_sangria = 260;
	int segunda_sangria = 740;
        
 	parametros_enteros = entero_a_digitos(*nave.puntaje);
	imprimir_parametros(renderer, 1, primera_sangria, PRIMER_RENGLON, parametros_enteros);
	free(parametros_enteros);

	parametros_enteros = entero_a_digitos(tiempo);
	imprimir_parametros(renderer, 1, primera_sangria, SEGUNDO_RENGLON, parametros_enteros);
	free(parametros_enteros);

	parametros_enteros = entero_a_digitos(*nave.cantidad_combustible);
	imprimir_parametros(renderer, 1, primera_sangria, TERCER_RENGLON, parametros_enteros);
	free(parametros_enteros);

	int velocidad_entero=(int)*nave.posicion_y;
	parametros_enteros = entero_a_digitos(abs(velocidad_entero));
	imprimir_parametros(renderer, 1, segunda_sangria, PRIMER_RENGLON, parametros_enteros);
	free(parametros_enteros);

	velocidad_entero=(int)*nave.velocidad_x;
	parametros_enteros = entero_a_digitos(abs(velocidad_entero));
	imprimir_parametros(renderer, 1, segunda_sangria, SEGUNDO_RENGLON, parametros_enteros);
	free(parametros_enteros);

	if(*nave.velocidad_x<0)
		renderizar_enteros(caracter_izquierda, 1, 5, SEGUNDA_SANGRIA+sangria_flechas, SEGUNDO_RENGLON, renderer);

	if(*nave.velocidad_x>0)
		renderizar_enteros(caracter_derecha, 1, 5, SEGUNDA_SANGRIA+sangria_flechas, SEGUNDO_RENGLON, renderer);

	velocidad_entero=(int)*nave.velocidad_y;
	parametros_enteros = entero_a_digitos(abs(velocidad_entero));
	imprimir_parametros(renderer, 1, segunda_sangria, TERCER_RENGLON, parametros_enteros);
	free(parametros_enteros);

	if(*nave.velocidad_y<0)
		renderizar_enteros(caracter_abajo, 1, 5, SEGUNDA_SANGRIA+sangria_flechas, TERCER_RENGLON, renderer);

	if(*nave.velocidad_y>0)
		renderizar_enteros(caracter_arriba, 1, 5, SEGUNDA_SANGRIA+sangria_flechas, TERCER_RENGLON, renderer);


}

void imprimir_mensaje_aterrizaje(SDL_Renderer *renderer, char *cadena, size_t longitud, int sangria, int posicion_y, int escala)
{
	int separador_caracteres = 7*escala;
	int **matriz_caracter;
	int filas;
	
	for(int i=0; i<longitud; i++)
	{
		matriz_caracter = opcion_char_a_matriz(cadena[i], &filas);
		renderizar_enteros_variables(matriz_caracter, escala, filas, sangria+separador_caracteres*i, posicion_y, renderer);
		destruir_vector_int(matriz_caracter, filas);
	}

}