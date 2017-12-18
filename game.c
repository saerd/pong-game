#include "game.h"


int main(void){

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
		fprintf(stderr, "Error initialising: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	};	

	SDL_Window* window = SDL_CreateWindow(TITLE, POS_UNDF, POS_UNDF, 
										  WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if(!window){
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	unsigned int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, flags);
	checkError(rend, window, rend);

	startGame(window, rend);
	
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


void startGame(SDL_Window* window, SDL_Renderer* rend){
	Object p1 = createPlayer(1, rend);
	checkError(p1, window, rend);

	Object b = createBall(rend);

	const unsigned char* key_states;

	while(1){
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			break;
		}

		key_states = SDL_GetKeyboardState(NULL);

		p1->event_handle(p1, &e, key_states);
		p1->update_object(p1);

		b->event_handle(b, &e, key_states);
		b->update_object(b);
	
		SDL_RenderClear(rend);

		renderObject(p1, rend);
		renderObject(b, rend);

		SDL_RenderPresent(rend);

	}

	


}

void checkError(void* ptr, SDL_Window* window, SDL_Renderer* rend){
	if(!ptr){
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		if(window) SDL_DestroyWindow(window);
		if(rend) SDL_DestroyRenderer(rend);
		SDL_Quit();
		exit(1);
	}
}


