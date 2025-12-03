#include <stdio.h>
#include <libdragon.h>
// #include <sprite.h>
#include "menu.c"
#include "battle.h"
#include "battle.c" 
#include "explore.c"
// #include "SLL.c"

int main(void)
{
	// test();
	console_init();
	menu_loop();
	// choose_pokemon();
	// console_clear();
	// battle_loop();
	// explore_loop();
	struct Player player1;
	struct Player player2;
	struct Player *p1 = &player1;
	struct Player *p2 = &player2;

	struct Pokemon pokemon1;
	struct Pokemon pokemon2;
	struct Pokemon *poke1 = &pokemon1;
	struct Pokemon *poke2 = &pokemon2;

	setup(p1, p2, poke1, poke2);

	printf("Player 1 Stats\n");
	printf("Player 1 Health: %d\n", player1.health);
	printf("Player 1 Pokemon: %s\n", player1.pokemon->name);

	while(1) {
	}
}