#include "game.h"
#include "objects.h"


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
	/*
	int width = 10, height = 10;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	checkError(surface, window, rend);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	checkError(tex, window, rend);
	SDL_FreeSurface(surface);

	SDL_Rect dest = {WIN_WIDTH /2 - 50, WIN_HEIGHT - (WIN_HEIGHT/15),  100, 20};
	*/
	SDL_Rect ball = {WIN_WIDTH /2 - 10, WIN_HEIGHT /2 - 10,  20, 20};

	struct player p = {0, 0};
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
	
		/*
		if(key_states[LEFT]){
			p.moving = 1;
			p.direction = LEFT;
		}
		if(key_states[RIGHT]){
			p.moving = 1;
			p.direction = RIGHT;
		}
		if(e.type == SDL_KEYDOWN){
			if(e.key.keysym.sym == SDLK_LEFT){
				p.moving = 1;
				p.direction = LEFT;
			}
			if (e.key.keysym.sym == SDLK_RIGHT){
				p.moving = 1;
				p.direction = RIGHT;
			}
		}

		if(!key_states[LEFT] && !key_states[RIGHT]){
			p.moving = 0;
		}

		if(p.moving){
			switch(p.direction) {
				case LEFT :
					dest.x = max(dest.x - 2, 0);
					break;

				case RIGHT :
					dest.x = min(dest.x + 2, WIN_WIDTH - dest.w);
					break;
			}
		}

		if(key_states[LEFT]){
			printf("left ");
		}
		if(key_states[RIGHT]){
			printf("right ");
		}
		printf("\n");
		*/

		SDL_RenderClear(rend);

		renderObject(p1, rend);

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


