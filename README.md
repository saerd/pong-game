a simple pong game to practice using SDL

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

try and convert screen function to a general function, plan is
split into creating objects and returning an array of lists
a function that event handles and updates objects
function that renders everything

with this mind, if this is done carefully I can have a stack of screens to maintain
and be able to make pause menus hopefully
