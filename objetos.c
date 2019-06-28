
void nave_mover(nave_t *x, float dt);
bool nave_dibujar(const nave_t *x, SDL_Renderer *r);

void asteroides_mover(asteroides_t *x, float dt);
bool asteroides_dibujar(const asteroides_t *x, SDL_Renderer *r);

void disparos_mover(disparos_t *x, float dt);
bool disparos_dibujar(const disparos_t *x, SDL_Renderer *r);