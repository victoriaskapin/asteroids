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
	srand(time(NULL));
	graficador_inicializar("sprites.bin");

	float tiempo = 0.0;
	int score = 0;
	int best_score = 0;
	int cantidad_asteroides = CANT_INICIAL_ASTEROIDES;
	int vida_nave = NAVE_VIDAS_INICIALES;

	//setear_conficiones_iniciales(&nave);
	nave_t nave = nave_crear();
	lista_t *l_shot = lista_crear();//creo la lista a llenar de disparos
	lista_t *l_rock = lista_crear();
	
	if(crear_asteroides_iniciales(cantidad_asteroides, l_rock));
	//funcion que se llama cuando hay que crear asteroides de 0
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
						if(nave.potencia < NAVE_POTENCIA_PASO)
							nave.potencia += NAVE_POTENCIA_PASO;//aumento potencia
						break;

					case SDLK_SPACE:
						if(cargar_disparos(
							l_shot,nave.posicion_x,
							nave.posicion_y,
							nave.angulo_rotacion));
						break;

					case SDLK_RIGHT:	
							(nave.angulo_rotacion) -= NAVE_ROTACION_PASO;
						break;
					
					case SDLK_LEFT:
							(nave.angulo_rotacion) += NAVE_ROTACION_PASO;
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
		tiempo+=DT;
		
		lista_asteroide_choco(l_rock,&nave,l_shot,&score);

		nave_mover(&nave, DT, nave.potencia);
		mover_lista_disparos(l_shot,DT);
		mover_lista_asteroides(l_rock,DT);

		datos_en_pantalla(renderer,score,best_score,vida_nave);


		if(!nave.vida){
			dormir=1000;
			vida_nave-=1;
			nave=nave_crear();
			nave.vida=vida_nave;

			if(!vida_nave){//caso que no queden mas vidas
				best_score=bestscore(best_score,score);
				dormir = 3000;
				mensajes_finde_partida(renderer,score);
				vida_nave=NAVE_VIDAS_INICIALES;
				score=0;
			}
		}

	
		//verifico si quedan asteroides 
		if(lista_es_vacia(l_rock)){
			cantidad_asteroides+=2;
			if(crear_asteroides_iniciales(cantidad_asteroides, l_rock));
		}

		if(dibujar_lista_asteroides(l_rock,renderer))
			;//dibujo cada elemento de la lista
		if(dibujar_lista_disparos(l_shot,renderer))
			;
		if(nave.vida)
			if((nave_dibujar(&nave, renderer))==false)
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
	graficador_finalizar();
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
