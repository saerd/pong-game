#include "game.h"

int main(void){

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_NOPARACHUTE) < 0){
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
	Screen s = createMenuScreen(window, rend);
	checkError(s, window, rend);

	Input in = createInput();

	List screens = createList(freeScreen, screenParent);

	addToList(screens, s);


	while(screens->head){
		Screen scr;

		updateInput(in);
		if(in->event->type == SDL_QUIT){
			break;
		}

		Node c = screens->tail;
		scr = c->item;

		scr->update_screen(scr, in, screens);

		c = screens->head;
		Node n;

		SDL_RenderClear(rend);
		while(c){
			n = c->next;
			scr = c->item;
			scr->render_screen(scr);
			c = n;
		}
		SDL_RenderPresent(rend);

	}

	freeList(screens);

}

Input createInput(void){
	Input in = malloc(sizeof(struct input));
	in->event = malloc(sizeof(SDL_Event));
	SDL_SetEventFilter(filterMouseMotion, NULL);
	return in;
}

int updateInput(Input in){
	SDL_PollEvent(in->event);
	in->key_states = SDL_GetKeyboardState(NULL);
	int x, y;
	unsigned int mask = SDL_GetMouseState(&x, &y);
	in->mouse_x = x;
	in->mouse_y = y;
	in->mask = mask;

	return 1;
}

int filterMouseMotion(void* d, SDL_Event* event){
	if(event->type == SDL_MOUSEMOTION) {
		return 0;
	}
	return 1;
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


