#include "game.h"

int main(void){

	// Initialise SDL Librarys and video and audio subsystems
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
		fprintf(stderr, "Error initialising: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	};	

	// Create a window
	SDL_Window* window = SDL_CreateWindow(TITLE, POS_UNDF, POS_UNDF, 
										  WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if(!window){
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	unsigned int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC; // flags for creating a renderer

	// Create a Renderer
	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, flags);
	checkError(rend, window, rend);

	// changing seed of random numbers, it is dependant on time here
	srand(time(NULL));

	// Enter Point
	begin_app(window, rend);	

	/* old implementation of screens, done through function pointer return values
	fncptr c_screen = menuScreen;
	while((c_screen = (fncptr) c_screen(window, rend)));
	*/
	
	// only required to free renderer and window here and handle closing subsystems
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void begin_app(SDL_Window* window, SDL_Renderer* rend){

	// first screen to display is our 'menu'
	Screen s = createMenuScreen(window, rend);
	checkError(s, window, rend);

	Input in = createInput();

	// we are treating screens List as a Stack, refer to screens.h for how the stack will work
	// List is generic, refer to List.h to see the reasons for these parameters
	List screens = createList(freeScreen, screenParent);

	// pushing the first screen to the stack
	addToList(screens, s);

	// the procedure here is explained in screens.h
	while(screens->head){
		Screen scr;

		updateInput(in);
		if(in->event->type == SDL_QUIT){
			break;
		}

		// take the screen from the tail (top of the stack)
		Node c = screens->tail;
		scr = c->item;

		// call its update function
		scr->update_screen(scr, in, screens);

		// begin at the head (bottom of the stack)
		c = screens->head;
		Node n;

		// clear the renderer and call each screens render function
		SDL_RenderClear(rend);
		while(c){
			// n
			n = c->next;
			scr = c->item;
			scr->render_screen(scr);
			c = n;
		}
		// present the renderer
		SDL_RenderPresent(rend);

	}

	// free all screens and the input struct
	freeList(screens);
	freeInput(in);

}

Input createInput(void){
	// create Input
	Input in = malloc(sizeof(struct input));
	in->event = malloc(sizeof(SDL_Event));

	// set a filter for what gets queued up as an event
	// in this case, take anything other than mouse MOTION
	SDL_SetEventFilter(filterMouseMotion, NULL);
	return in;
}

int updateInput(Input in){

	// dequeue next event
	SDL_PollEvent(in->event);

	// update state of keyboard
	in->key_states = SDL_GetKeyboardState(NULL);
	int x, y;

	// retrieve and store state of mouse
	unsigned int mask = SDL_GetMouseState(&x, &y);
	in->mouse_x = x;
	in->mouse_y = y;
	in->mask = mask;

	return 1;
}

void freeInput(Input in){
	free(in->event);
	free(in);
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


