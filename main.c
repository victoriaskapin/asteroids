#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include <stdint.h>
#include "modulo.h"
#include "iterador.h"
#include "lista.h"


struct sprite_t nave;

typedef enum
{
	FALSE,
	NAVE_DESTRUIDA,
	ASTEOROIDE_DESTRUIDO,
	FALLA_MEMORIA,
	ASTEOROIDES_DESTRUIDOS
}status_t;


int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int dormir = 0;

	// BEGIN código del alumno
	// Mi nave:
	nave_t nave;
	status_t st;

	graficador_inicializar("sprites.bin", 1000, 800);

	float tiempo=0, dt=1.0/JUEGO_FPS;
	// END código del alumno

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						break;
					
					case SDLK_SPACE:
						//creo un disparo y lo agrego a la lista

						break;
					case SDLK_RIGHT:
					case SDLK_LEFT:
						break;
				}
				// END código del alumno


			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código del alumno
		tiempo+=dt;
		printf("%d\n", (int)tiempo);
		//nave_mover(nave, dt);
		

		//chequeo si el disparo choco con un asteoride y si lo hizo, agrego dos asteorides a la lista y destruyo el disparo y el asteroide original
		//chequeo si la nave choco con un asteroide

		///////////   POR AHI HACER UN CASE PARA ESTO ////////////

		if((st = asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo))==NAVE_DESTRUIDA)
			//reiniciar con una vida menos

		else if(st==ASTEOROIDE_DESTRUIDO)

		else if(st==ASTEOROIDES_DESTRUIDOS)
			//reiniciar con 2 asteroides mas


		//////////////////////////////////////////////////////////////////////////


		if((disparo_dibujar(disparo, renderer))==false)//dibujo cada elemento de la lista
			break;

		if((asteroide_dibujar(asteroide, renderer))==false)//dibujo cada elemento de la lista
			break;

		if((nave_dibujar(nave, renderer))==false)
			break;

		// END código del alumno


        	SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código del alumno
	// No tengo nada que destruir.
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

