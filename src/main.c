#include <stdio.h>
#include <malloc.h>
#include <libdragon.h>
#include <sprite.h>


static sprite_t *sprite;

int main(void)
 {
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);

    sprite = sprite_load("rom:/froakie.sprite");

    while(1){
    surface_t* disp = display_get();
    
    graphics_draw_sprite_trans(disp, 20, 40, sprite);

    display_show(disp);
    }
}






	// // Initialize file system
	// int dfs_init(uint32_t base_fs_loc);


	// debug_init_isviewer();
	// console_init();
	// joypad_init();

	// debug_init_usblog();
    // console_set_debug(true);

	// // Main loop
	// while (1) {
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