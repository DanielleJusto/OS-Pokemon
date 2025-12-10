#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <rdpq.h>
#include <rdpq_sprite.h>
#include <libdragon.h>


#define LIBDRAGON_RDPQ_SPRITE_H


static sprite_t *sprite;
static sprite_t *title;
static sprite_t *textOverlay;

/* Menu/Load Screen 
    - Print title to screen
    - Play button --> when pressed start game
*/ 

int menu_loop(void)
{
	int dfs_init(uint32_t base_fs_loc);
    dfs_init(DFS_DEFAULT_LOCATION);
    debug_init_isviewer();
    console_init();
	joypad_init();
    debug_init_usblog();
    console_set_debug(true);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

    sprite = sprite_load("rom:/pixelPikachu.sprite");
    title = sprite_load("rom:/menu/TITLE.sprite");
    textOverlay = sprite_load("rom:/menu/textOverlay.sprite");

	bool game_start = false;

	while(game_start == false) {
		surface_t* disp = display_get();
		graphics_draw_box(disp, 0, 0, 320, 240, graphics_make_color(154, 139, 130, 255));
		graphics_draw_sprite_trans(disp, 0, 10, title);
		graphics_draw_sprite_trans(disp, 20, 40, sprite);
		graphics_draw_text(disp, 55, 175, "Press START to start game.");
		graphics_draw_text(disp, 15, 225, "CSC262: Buddy and Dani final project");
		// graphics_draw_sprite_trans(disp, 0, 125, textOverlay);
		// graphics_draw_text(disp, 20, 150, "a wild pikachu has appeared!");

		display_show(disp);

		joypad_poll();
		joypad_port_t port;
		if (joypad_is_connected(JOYPAD_PORT_1)) port = JOYPAD_PORT_1;
		// if (joypad_is_connected(JOYPAD_PORT_2)) port = JOYPAD_PORT_2;
		// if (joypad_is_connected(JOYPAD_PORT_3)) port = JOYPAD_PORT_3;
		// if (joypad_is_connected(JOYPAD_PORT_4))	port = JOYPAD_PORT_4;

		joypad_buttons_t input = joypad_get_buttons_pressed(port);

		// printf("%d\n", input.start);
	
		if (input.start == 1) {
			game_start = true;
		}
	}
	return 0;
}