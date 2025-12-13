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

int main(void)
{
	/* SET UP DISPLAY AND DFS */
    debug_init_isviewer();
    console_init();
    debug_init_usblog();
    console_set_debug(true);
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);

	/* INITIALIZE STRUCTS */
	struct Player player1;
	struct Player player2;
	struct Player *p1 = &player1;
	struct Player *p2 = &player2;

	struct Pokemon pokemon1;
	struct Pokemon pokemon2;
	struct Pokemon *poke1 = &pokemon1;
	struct Pokemon *poke2 = &pokemon2;

	/* BEGIN GAME */
	menu_loop();

	setup(p1, p2, poke1, poke2);
	sprite_t* avatar1 = choose_character(p1);
	sprite_t* avatar2 = choose_character(p2);
	explore_loop(avatar1, avatar2);

	bool gameEnd = false;

	load_battle_sprites();

    srand(time(0)); // Seed for damage dice roll
	
	while(gameEnd == false){
		battle_loop(p1,p2);
		if (player1.health <= 0 || player2.health <= 0){gameEnd = true; break;}
		battle_loop(p2,p1);
		if (player1.health <= 0 || player2.health <= 0){gameEnd = true; break;}
	}

	free_battle_sprites();

	/* Maybe make a screen for this */
	printf("GAMEOVER!\n");
	if (player1.health < player2.health){
		printf("%s Wins!\n", player1.name);
	} else {
		printf("%s Wins!\n", player2.name);
	}

	joypad_close();
	return 0;
}