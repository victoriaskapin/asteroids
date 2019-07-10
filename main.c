#include "utilidades.h"
#include "modulo.h"
#include "nave.h"
#include "disparos.h"
#include "asteroides.h"


//void setear_conficiones_iniciales(nave_t *nave);

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;

	// BEGIN código del alumno
	//status_t st;
	graficador_inicializar("sprites.bin");

	float tiempo=0, dt=1.0/JUEGO_FPS;
	size_t cant_asteroides = CANT_INICIAL_ASTEROIDES;
	
	//setear_conficiones_iniciales(&nave);
	nave_t nave=nave_crear();
	crear_asteorides(cant_asteroides);//funcion que se llama cuando hay que crear asteroides de 0

	lista_t *l_shot=lista_crear();


	// END código del alumno

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				switch(event.key.keysym.sym) 
				{
					case SDLK_UP:
						if(1)
						{
						nave.potencia = potencia_nave(nave, NAVE_POTENCIA_PASO);//aumento potencia
						}
						break;

					case SDLK_SPACE:
						if(cargar_disparos(l_shot,nave.posicion_x,nave.posicion_y,NAVE_ANGULO_INICIAL- nave.angulo_rotacion));
						break;

					case SDLK_RIGHT:
						(nave.angulo_rotacion) += NAVE_ROTACION_PASO;
						break;
					
					case SDLK_LEFT:
						(nave.angulo_rotacion) -= NAVE_ROTACION_PASO;
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
		
		nave.potencia=nave.potencia*0.9;

		nave_mover(&nave, dt, nave.potencia);
		mover_lista_disparos(l_shot,dt);
		//objeto_mover(&disparo, dt, 0);
		//objeto_mover(&asteroide, dt, 0);


		///////////   POR AHI HACER UN CASE PARA ESTO ////////////
		//chequeo si el disparo choco con un asteoride y si lo hizo, agrego dos asteorides a la lista y destruyo el disparo y el asteroide original
		//chequeo si la nave choco con un asteroide
		/*if((st = asteroide_choco(nave_t nave, asteroide_t asteroide, disparo_t disparo))==NAVE_DESTRUIDA)
			printf("nave choco\n");
			//reiniciar con una vida menos

		else if(st==ASTEOROIDE_DESTRUIDO)
			printf("asteroide destruido\n");

		else if(st==ASTEOROIDES_DESTRUIDOS)
		{
			cant_asteroides+=CANT_ASTEROIDES_NUEVA_PARTIDA;
			crear_asteorides(cant_asteroides);
		}*/

		//////////////////////////////////////////////////////////////////////////


		//if((disparo_dibujar(disparo, renderer))==false)//dibujo cada elemento de la lista
		//	break;

		//if((asteroide_dibujar(asteroide, renderer))==false)//dibujo cada elemento de la lista
		//	break;
		if(dibujar_lista_disparos(l_shot,renderer))
			;
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


/*void setear_conficiones_iniciales(nave_t *nave)
{
	printf("condiciones iniciales\n");
	nave_t nave_aux ={500, 400, 0, 0, NAVE_ANGULO_INICIAL, 0};
	*nave=nave_aux;
}*/
