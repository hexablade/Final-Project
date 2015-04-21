#ifndef ENGINE_H_
#define ENGINE_H_



void doRender(SDL_Renderer *renderer, GameState *game);
int processEvents(SDL_Window *window, GameState *game);
void collisionDetect(GameState *game);
void process(GameState *game);
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
void process(GameState *game);
void loadGame(GameState *game);
void initStars(GameState *game);

#endif