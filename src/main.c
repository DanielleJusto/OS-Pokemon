#include <stdio.h>
#include <libdragon.h>
// #include <sprite.h>
#include "menu.c"
#include "battle.h"
#include "battle.c" 
#include "explore.c"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <rdpq.h>
#include <rdpq_sprite.h>
// #include "battle_spaceSaver.c"
// #include "SLL.c"

static sprite_t *self;
static sprite_t *enemy;
static sprite_t *battleOverlay;
static sprite_t *battleground;

int main(void)
{
	console_init();
	menu_loop();

	struct Player player1;
	struct Player player2;
	struct Player *p1 = &player1;
	struct Player *p2 = &player2;

	struct Pokemon pokemon1;
	struct Pokemon pokemon2;
	struct Pokemon *poke1 = &pokemon1;
	struct Pokemon *poke2 = &pokemon2;

	setup(p1, p2, poke1, poke2);
	// sprite_t* avatar = choose_character();
	// explore_loop(avatar);
	// explore_loop();
	// damage(p1, 10);
	bool gameEnd = false;
	while(gameEnd == false){
		battle_loop(p1,p2);
		if (player1.health == 0 || player2.health == 0){gameEnd = true;}
		battle_loop(p2,p1);
		if (player1.health == 0 || player2.health == 0){gameEnd = true;}
	}
	printf("GAMEOVER!\n");
	return 0;
}