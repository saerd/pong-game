#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TITLE "Pong game"
#define POS_UNDF (SDL_WINDOWPOS_UNDEFINED)
#define WIN_WIDTH (640)
#define WIN_HEIGHT (480)


#define min(a, b) (((a) <= (b)) ? (a): (b))
#define max(a, b) (((a) >= (b)) ? (a): (b))

void checkError(void* ptr, SDL_Window* window, SDL_Renderer* rend);

void startGame(SDL_Window* window, SDL_Renderer* rend);

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
	int width = 10, height = 10;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	checkError(surface, window, rend);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	checkError(tex, window, rend);
	SDL_FreeSurface(surface);

	SDL_Rect dest = {WIN_WIDTH /2 - 50, WIN_HEIGHT - (WIN_HEIGHT/15),  100, 20};

	while(1){
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			break;
		}

		if(e.type == SDL_KEYDOWN){
			if(e.key.keysym.sym == SDLK_LEFT){
				dest.x = max(dest.x - 1, 0);
			}
			else if (e.key.keysym.sym == SDLK_RIGHT){
				dest.x = min(dest.x + 1, WIN_WIDTH - dest.w);
			}
		}

		SDL_RenderClear(rend);

		SDL_RenderCopy(rend, tex, NULL, &dest);

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


