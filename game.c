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
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


void startGame(SDL_Window* window, SDL_Renderer* rend){
	Object p1 = createPlayer(1, rend);
	checkError(p1, window, rend);

	Object p2 = createPlayer(2, rend);
	checkError(p2, window, rend);

	Object b = createBall(rend);
	checkError(b, window, rend);

	const unsigned char* key_states;

	List objList = createList();
	addToList(objList, p1);
	addToList(objList, p2);
	addToList(objList, b);

	Object c;
	while(1){
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			break;
		}

		key_states = SDL_GetKeyboardState(NULL);

		for(c = objList->head; c; c = c->next){
			c->event_handle(c, &e, key_states);
			c->update_object(c, objList);
		}

		SDL_RenderClear(rend);

		for(c = objList->head; c; c = c->next){
			renderObject(c, rend);
		}

		SDL_RenderPresent(rend);

	}

	freeList(objList);
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


