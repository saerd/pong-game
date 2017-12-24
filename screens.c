#include "screens.h"

Screen startGame(SDL_Window* window, SDL_Renderer* rend){
	Object p1 = createPlayer(1, rend);
	checkError(p1, window, rend);

	Object p2 = createPlayer(2, rend);
	checkError(p2, window, rend);

	Object b = createBall(rend);
	checkError(b, window, rend);

	SDL_Texture* bg = createBackground(rend);

	const unsigned char* key_states;

	List objList[N_TYPES];
	for(int i = 0; i < N_TYPES; i++){
		objList[i] = createList();
	}
	addToList(objList[PLAYERS], p1);
	addToList(objList[PLAYERS], p2);
	addToList(objList[BALL], b);

	Object c = NULL, n = NULL;
	while(1){
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			return NULL;
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
		SDL_RenderCopy(rend, bg, NULL, NULL);

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
	return (Screen) startGame;
}
