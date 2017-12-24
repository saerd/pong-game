#include "screens.h"

Screen startGame(SDL_Window* window, SDL_Renderer* rend){
	// Creating the player objects and the ball
	Object p1 = createPlayer(1, rend); // rend is passed through so that the texture of the object can be determined
	checkError(p1, window, rend); // checkError just checks any pointer is NULL and exits precedurally

	Object p2 = createPlayer(2, rend);
	checkError(p2, window, rend);

	Object b = createBall(rend);
	checkError(b, window, rend);

	// bg is different, dont need it to be an object since its not complex
	SDL_Texture* bg = createBackground(rend); 

	const unsigned char* key_states;

	// array of lists, each index holding a different type of object, so that objects can interact
	// differently with each other
	List objList[N_TYPES];
	for(int i = 0; i < N_TYPES; i++){
		objList[i] = createList();
	}
	
	// objects being added to their respective lists
	addToList(objList[PLAYERS], p1);
	addToList(objList[PLAYERS], p2);
	addToList(objList[BALL], b);
	
	/* Procedure goes as follows
	 * 1. update the event object and keyboard state array
	 * 2. loop through each object type list calling their
	 *    event handler and update object functions
	 * 3. clear the renderer and render the background
	 * 4. loop through each object type list and call their render functions
	 * 5. present the renderer
	 * Theres an unclean check on if the game is won, I play to remodel that
	 */

	Object c = NULL, n = NULL;
	while(1){
		// step 1
		SDL_Event e;
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			return NULL;
		}
		key_states = SDL_GetKeyboardState(NULL);

		// step 2
		for(int i = 0; i < N_TYPES; i++){
			c = objList[i]->head;
			while(c){
				n = c->next;
				c->event_handle(c, &e, key_states);
				c->update_object(c, objList);
				c = n;
			}
		}

		// step 3
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, bg, NULL, NULL);

		// step 4
		for(int i = 0; i < N_TYPES; i++){
			for(c = objList[i]->head; c; c = c->next){
				c->render_object(c, rend);
			}
		}

		//step 5
		SDL_RenderPresent(rend);
		Ball ball_check = b->data;
		if(ball_check->done) break;

	}

	// clear everything before returning a new function pointer
	freeList(objList);
	return (Screen) startGame; // in this case restart the game
}
