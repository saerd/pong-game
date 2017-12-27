a simple pong game to practice using a library and designing an engine

Goals / subsets

- implement simple fluid controls, no second player, cant traverse wall, no ball
	subset reached, controls took longer than expected because they didnt feel fluid when both
	left and right were held down, happy with the result
	CODE: no idea how it should be layed out, but def going to be changed to finish
		  the other subsets

- ball with random start direction
- second player with other controls
- traverse wall
- shoot projectile to redirect ball, 5 regen bullets, convert to longer map
- projectile also immobilises enemy
- second player as ai, option to play either mode
- score count, end game with restart button or menu


27/12/2017 - 

This is a little project in my two week holiday, 
I am satisfied with the progress ive made, not on the game but on the design of it.

Ive written an Object ADT to help separate logic of objects in the game.
Ive written a Screen ADT that can hold any sort of data that it wants to update and render, Objects
being an example.

The program is maintained using a stack of Screens updating the top and rendering everything afterwards.
The stack is implemented using a generic List and the same List can and is used to hold objects for a screen.

None of this was my goal to achieve, the only objective in mind was to design a working pong game.
However obstacles I wasnt bothered overcoming came about because of bad design, so refinement
after refinement of the engine allowed me to progress in the development of the game

I now have a clean pong game (albeit bad physics) with multiplayer paddles
paddles can traverse walls and the ball reacts to both parts of their hitbox
the ball has an animation loop for practice
paddles can shoot bullets (logic not programmed however)

The game starts with a menu, two buttons, one to start the game, the other to quit the game
The game can be paused with the same menu coming, only now the button can restart the game or
unpause

I am happy with the results, I dont think I need to change the design anymore and can now just keep
adding and refining the existing objects if I plan and have the time to.



24/12/2017 -

try and convert screen function to a general function, plan is
split into creating objects and returning an array of lists
a function that event handles and updates objects
function that renders everything

with this mind, if this is done carefully I can have a stack of screens to maintain
and be able to make pause menus hopefully

a screen stack has been implemented and I am very happy with the result, Ive made a generic button
that can modify the screen stack, and with that I made a menu that shows up to pause the game or
when the app starts
