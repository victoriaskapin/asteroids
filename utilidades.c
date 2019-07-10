#include "utilidades.h"


void setear_conficiones_iniciales(nave_t *nave)
{

	nave_t nave_aux ={500, 400, 0, 0, 0, 0};
	*nave=nave_aux;
}

float generar_aleatorio(float superior, float inferior)
{
	float numero_aleatorio=(rand()%RAND_MAX); /*da un numero entre 1 y RAND_MAX*/
	float random = (numero_aleatorio/RAND_MAX);//lo escalo para que de entre 0 y 1

	return random*(superior - inferior) + inferior;/*x entre x_max y x_min*/
}


float ** vector_rotar(float coordenadas[][2], size_t n, float rad){
	int i;
	float **rotada;
	float coseno_angulo,seno_angulo;

	rotada=malloc(sizeof(float)*n);
	if (rotada==NULL)
		return NULL;

	coseno_angulo=cos(rad);
	seno_angulo=sin(rad);
	for(i=0;i<n;i++){

		rotada[i]=malloc (sizeof(float)*2);
		
		if (rotada[i]==NULL){
			for(int j=0;j<i;j++)
				free(rotada[j]);
			free(rotada);
			return NULL;
		}

		rotada[i][0] = coordenadas[i][0]*coseno_angulo-coordenadas[i][1]*seno_angulo;
		rotada[i][1] = coordenadas[i][0]*seno_angulo+coordenadas[i][1]*coseno_angulo;
	}
	return rotada;
}

void destruir_vector(float **v,size_t n){

	for(int i = 0;i < n;i++){

		free (v[i]);
	}

	free (v);
}


float **matriz_a_vector(float (*m)[MAX_COORDENADAS], size_t n)
{
	size_t i, j;
	float **vector;

	vector = crear_vector(n, MAX_COORDENADAS);

	for(i=0; i<n; i++)
		for(j=0; j<MAX_COORDENADAS; j++)
			vector[i][j] = m[i][j];

	return vector;
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
//esta es igual a la de rotar anterior solo que devuelve void, la puse aca para no borrarla pero la estamos usando ??? 
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
