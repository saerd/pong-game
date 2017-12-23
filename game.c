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

	
	while(startGame(window, rend));
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


int startGame(SDL_Window* window, SDL_Renderer* rend){
	Object p1 = createPlayer(1, rend);
	checkError(p1, window, rend);

	Object p2 = createPlayer(2, rend);
	checkError(p2, window, rend);

	Object b = createBall(rend);
	checkError(b, window, rend);

	const unsigned char* key_states;

	List objList[N_TYPES];
	for(int i = 0; i < N_TYPES; i++){
		objList[i] = createList();
	}
	addToList(objList[PLAYERS], p1);
	addToList(objList[PLAYERS], p2);
	addToList(objList[BALL], b);

	Object c = NULL, n = NULL;
	int return_status = 1;
	while(1){
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			return_status = 0;
			break;
		}

		key_states = SDL_GetKeyboardState(NULL);

		for(int i = 0; i < N_TYPES; i++){
			c = objList[i]->head;
			while(c){
				n = c->next;
				c->event_handle(c, &e, key_states);
				c->update_object(c, objList);
				c = n;
			}
		}

		SDL_RenderClear(rend);

		for(int i = 0; i < N_TYPES; i++){
			for(c = objList[i]->head; c; c = c->next){
				c->render_object(c, rend);
			}
		}

		SDL_RenderPresent(rend);
		Ball ball_check = b->data;
		if(ball_check->done) break;

	}

	freeList(objList);
	return return_status;
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


