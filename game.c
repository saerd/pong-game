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

	srand(time(NULL));

	begin_app(window, rend);	
	/*
	fncptr c_screen = menuScreen;
	while((c_screen = (fncptr) c_screen(window, rend)));
	*/
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void begin_app(SDL_Window* window, SDL_Renderer* rend){
	Screen s = createGameScreen(window, rend);

	SDL_Event e;
	const unsigned char* key_states;

	while(1){
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			break;
		}
		key_states = SDL_GetKeyboardState(NULL);

		s->update_screen(s, &e, key_states);

		SDL_RenderClear(rend);

		s->render_screen(s);

		SDL_RenderPresent(rend);
	}
	s->free_screen(s);
}

SDL_Texture* createBackground(SDL_Renderer* rend){
	
	SDL_Surface* surface = IMG_Load("art/pong_bg.png");
	if(!surface){
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		return NULL;	
	}
	return tex;
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


