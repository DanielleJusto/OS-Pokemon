// #include <stdio.h>

// #include <libdragon.h>
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

int main(void)
{
    int dfs_init(uint32_t base_fs_loc);
    dfs_init(DFS_DEFAULT_LOCATION);


    debug_init_isviewer();

    console_init();

    debug_init_usblog();
    console_set_debug(true);


    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);

    sprite = sprite_load("rom:/pixelPikachu.sprite");
    title = sprite_load("rom:/menu/TITLE.sprite");
    textOverlay = sprite_load("rom:/textOverlay.sprite");

    while(1){
    surface_t* disp = display_get();

    graphics_draw_box(disp, 0, 0, 320, 240, graphics_make_color(154, 139, 130, 255));
    graphics_draw_sprite_trans(disp, 0, 10, title);
    graphics_draw_sprite_trans(disp, 20, 40, sprite);
    graphics_draw_text(disp, 55, 175, "Press START to start game.");
    graphics_draw_text(disp, 15, 225, "CSC262: Buddy and Dani final project");
    // graphics_draw_sprite_trans(disp, 0, 125, textOverlay);
    // graphics_draw_text(disp, 20, 150, "a wild pikachu has appeared!");

    display_show(disp);


    	// joypad_poll();

		// joypad_port_t port = JOYPAD_PORT_1;
		// joypad_2d_t axes = JOYPAD_2D_ANY;
		// joypad_8way_t direction = joypad_get_direction(port, axes);

		// switch(direction){
		// 	case JOYPAD_8WAY_NONE:
		// 		printf("None");
		// 		break;
		// 	case JOYPAD_8WAY_RIGHT:
		// 		printf("Right");
		// 		break;
		// 	case JOYPAD_8WAY_UP_RIGHT:
		// 		printf("Up Right");
		// 		break;
		// 	case JOYPAD_8WAY_UP:
		// 		printf("Up");
		// 		break;
		// 	case JOYPAD_8WAY_UP_LEFT:
		// 		printf("Up left");
		// 		break;
		// 	case JOYPAD_8WAY_LEFT:
		// 		printf("Left");
		// 		break;
		// 	case JOYPAD_8WAY_DOWN_LEFT:
		// 		printf("Down Left");
		// 		break;
		// 	case JOYPAD_8WAY_DOWN:
		// 		printf("Down");
		// 		break;
		// 	case JOYPAD_8WAY_DOWN_RIGHT:
		// 		printf("Down Right");
		// 		break;
		// }
		
		// bool a_pressed = false;
		// joypad_port_t port = JOYPAD_PORT_1;

		// joypad_buttons_t btn = joypad_get_buttons_pressed(joypad_port_t port);
		// if (btn.a){
		// 	a_pressed = true;
		// 	printf("a_pressed");
        // }
    }
}