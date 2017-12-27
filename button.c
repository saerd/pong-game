#include "button.h"

// Object sample implementation
// This is a simple button that triggers a function when pressed and unpressed
//
// A create function is required and calls createObject
// 	This function must take care of:
// 	1. creating a texture that will be used to render the graphic of the object
// 		- you can load a sprite as a texture, and keep some logic to display different parts of the texture
// 	2.	allocating its own data to maintain the object and storing it within the void* of the Object
// 	3.  Not required, as this is was in the original development process, it just holds memory of
// 	its collision box, however you can choose to maintain this in its personal void* data
// 	
// 	Lastly, valid !NULL functions need to be provided for the function, refer below of how to implement

Object createButton(int x, int y, int w, int h,
					int (*action)(Object, List), SDL_Renderer* rend){
	Object b;

	// button.png is an animation sprite of two simple images
	SDL_Surface* surface = IMG_Load("art/button.png");

//	SDL_Surface* surface = SDL_CreateRGBSurface(0, side, side, 32, 0, 0, 0, 0); old still implementation
//	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));

	// convert surface to texture and make sure its valid
	if(!surface){
		return NULL;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		return NULL;	
	}

	b = createObject(tex, rend, button_EH, button_update, button_render, button_col_check, free_button);	

	Button new_button = malloc(sizeof(struct button));
	new_button->pressed = 0; // pressed will give us the logic of which button animation to render
	new_button->trigger = 0; // trigger will give us the logic of when to perform an action
	new_button->action = action; // the action to perform
	// int (*action)(Object, List); it can modify itself (Object), or the stack of screens (List)
	// the program has, and consequently the screen it lives in (at the tail), and then also its
	// surrounding objects (See screens.h for more information)
	// it also returns 0 if it has destroyed the screen it lives in (and consequently itself)

	b->data = new_button;

	b->colBox.x = x;
	b->colBox.y = y;
	b->colBox.w = w;
	b->colBox.h = h;

	return b;
}

// sample event handler for our button
int button_EH(Object b, Input in, List screens){

	Button d = b->data;
	// our button will only react to being left clicked, hence need only use
	// Input's mask, mouse_x and mouse_y
	int x = in->mouse_x, y = in->mouse_y;

	if(in->mask & SDL_BUTTON(SDL_BUTTON_LEFT)){ // checks if the left button is currently pressed
		if(b->colBox.x < x && x < b->colBox.x + b->colBox.w &&
		   b->colBox.y < y && y < b->colBox.y + b->colBox.h){ // checks if that press is in the button
			if(!d->pressed){
				d->pressed = PRESSED; // changes its state to PRESSED
			}
		}
		else{
			d->pressed = HELD; // otherwise notes that the mouse is 'HELD'
		}
	}
	else{
		// else if its not pressed anymore, and the mouse is on the button and the previous state
		// was pressed, then this is a trigger
		if(b->colBox.x < x && x < b->colBox.x + b->colBox.w &&
		   b->colBox.y < y && y < b->colBox.y + b->colBox.h && d->pressed == PRESSED){
			d->pressed = 0;
			d->trigger = 1;
			return d->action(b, screens); // here we just return the value returned from its action
										  // as it may delete itself from the screen stack, this
										  // function needs to relay that info
		}
		else {
			d->pressed = 0;
			d->trigger = 0;
		}
	}

	return 1; // if we are here, we did not delete ourselves from the Screen Stack (List) so return 1
}

// sample update implementation
// this function that doesnt do much for a button, however the key idea is the same
// just make sure the object's personal data is up to date, whether it be an animation loop that needs
// incrementing (which you can choose to maintain in render function) or an interaction has occured
// with another object in the list and needs to be updated, e.g. a collision has occured
void button_update(Object b, List* objList){
	Button d = b->data;
	if(d->trigger){
		d->trigger = 0;
	}
}

// sample render implementation
// this function has to call SDL_RenderCopy or SDL_RenderCopyEx and render its object
// SDL_QueryTexture is used to find dimensions of its texture, however recommended to store this
// in personal data of object
void button_render(Object b, SDL_Renderer* rend){
	int w, h;
	// the sprite is just two pictures on top of each other
	// so need to divide the result of h
	SDL_QueryTexture(b->tex, NULL, NULL, &w, &h);
	h /= 2;

	// unpressed button is at x = 0, y = 0, however if its been pressed, move y down exactly h
	// keep in mind coords start at (0, 0) from the TOP-LEFT
	SDL_Rect r = {0, 0, w, h};
	Button d = b->data;
	if(d->pressed == PRESSED){
		r.y = h;
	}

	SDL_RenderCopy(rend, b->tex, &r, &b->colBox);

}

// sample collision_check implementation, a button will never touch another rectangle (or say it has)
// and so returns 0 all the time
int button_col_check(Object b, SDL_Rect* r){
	return 0;
}

// free_data implementation, its personal data is just a few values, only need to call free
void free_button(void * b){
	free(b);
}
