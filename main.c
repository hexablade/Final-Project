#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "engine.h"
int main(int argc, char *argv[])
{
  int mode = 0;
  int flags[] = { 0, SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP };
  //argument checking
  for(int i = 1; i < argc; i++)
  {
    if(strcasecmp(argv[i], "-mode") == 0 && i+1 < argc)
    {
      mode = atoi(argv[i+1]);
      if(mode < 0 || mode > 2)
        mode = 0;
    }
  }
  
  
  GameState gameState;
  SDL_Window *window = NULL;                    // Declare a window
  SDL_Renderer *renderer = NULL;                // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);              // Initialize SDL2
  
  gameState.joystick = SDL_JoystickOpen(0);
  
  srandom((int)time(NULL));
  
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640,                               // width, in pixels
                            480,                               // height, in pixels
                            flags[mode]);                      // flags
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  gameState.renderer = renderer;
  gameState.window = window;
  
  //Hide mouse
  SDL_ShowCursor(0);
  
  SDL_RenderSetLogicalSize(renderer, 640, 480);
  
  TTF_Init(); //initialize font system
  
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initialize sound
  
  loadGame(&gameState);
  
  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &gameState);
    
    process(&gameState);
    collisionDetect(&gameState);
    
    //Render display
    doRender(renderer, &gameState);
    
   
  }
  

  //Shutdown game and unload all memory
  SDL_DestroyTexture(gameState.star);
  SDL_DestroyTexture(gameState.manFrames[0]);
  SDL_DestroyTexture(gameState.manFrames[1]);
  SDL_DestroyTexture(gameState.brick);
  if(gameState.label != NULL)
    SDL_DestroyTexture(gameState.label);
  if(gameState.label2 != NULL)
    SDL_DestroyTexture(gameState.label2);
  if(gameState.joystick)
    SDL_JoystickClose(gameState.joystick);
  TTF_CloseFont(gameState.font);

  Mix_FreeChunk(gameState.bgMusic);
  Mix_FreeChunk(gameState.dieSound);
  Mix_FreeChunk(gameState.jumpSound);
  Mix_FreeChunk(gameState.landSound);

  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  TTF_Quit();
  Mix_CloseAudio();
  
  // Clean up
  SDL_Quit();
  return 0;
}
