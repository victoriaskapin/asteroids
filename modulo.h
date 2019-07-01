#ifndef _MODULO_H_
#define _MODULO_H_

#define MAX_SPRITES 7 

bool graficador_inicializar(const char *fn, int ancho, int alto);

bool graficador_dibujar(SDL_Renderer *r, const char *nombre, float escala, float x, float y, float angulo);

void graficador_ajustar_variables(float *x, float *y);

void graficador_finalizar();

#endif