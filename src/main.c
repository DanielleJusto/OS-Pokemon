#include <stdio.h>
#include <libdragon.h>
// #include <sprite.h>
#include "menu.c"
#include "battle.c"
// #include "SLL.c"

int main(void)
{
	// test();
	console_init();
	menu_loop();
	choose_pokemon();
	console_clear();
	battle_loop();
	while(1) {}
}