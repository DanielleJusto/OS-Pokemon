#include <stdio.h>
#include <libdragon.h>
// #include <sprite.h>
#include "menu.c"
#include "battle.c"

int main(void)
{
	console_init();

	menu_loop();

	battle_loop();
	

	while(1) {}
}