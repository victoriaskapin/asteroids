#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

#define VELOCIDAD_ASTEROIDE_ORIGINAL 1000
#define VELOCIDAD_ASTEROIDE_OFFSET 100
#define CANT_SUB_ASTEROIDES 2
#define ASTEROIDE_RADIO_CHICO 8
#define ASTEROIDE_RADIO_MEDIANO 16
#define ASTEROIDE_RADIO_GRANDE 32
#define PRIMER_ASTEROIDE 1
#define ULTIMO_ASTEROIDE 4
typedef struct
{
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo=;
	size_t radio;
}asteroide_t;

typedef struct
{
	float posicion_x;
	float posicion_y;
	float angulo=;
	float tiempo_vida;
}disparo_t;

typedef enum
{
	FALSE,
	NAVE_DESTRUIDA,
	ASTEOROIDE_DESTRUIDO,
	FALLA_MEMORIA,
	ASTEROIDES_DESTRUIDOS
}status_t;

float distancia(asteroide_t asteroide, float objeto_x, float objeto_y);
float generar_aleatorio(float superior, float inferior);
void asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo);
asteroide_t cargar_asteroide(size_t radio);
void procesar_asteroide();


#endif