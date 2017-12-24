#include "screens.h"

Screen menuScreen(SDL_Window* window, SDL_Renderer* rend){

	while(1){
		// step 1
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			return NULL;
		}
		if(e.type == SDL_MOUSEBUTTONDOWN){
			return (Screen) startGame;
		}
	}
}
