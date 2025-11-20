#include <stdio.h>
#include <libdragon.h>
// #include <sprite.h>
#include "menu.c"

// static sprite_t *sprite;

// int display_froakie(void)
//  {
//     display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
// 	dfs_init(DFS_DEFAULT_LOCATION);
// 	rdpq_init();

// 	sprite = sprite_load("rom://froakie.sprite");
// 	rdpq_blitparms_t parms; 
// 	parms.scale_x = parms.scale_y = 0.5;

//     while(1){
//     surface_t* disp = display_get();
// 	rdpq_attach_clear(disp, NULL);
    
// 	// Attach the buffers to the RDP (No z-buffer needed yet)
//     // graphics_draw_sprite_trans(disp, 20, 40, sprite);
// 	// rdpq_sprite_blit(sprite, display_get_width()/4-8, display_get_height()/2-8, NULL);
// 	rdpq_set_mode_copy(true);
// 	rdpq_sprite_blit(sprite, 0,0, &parms);
//     // display_show(disp);
// 	rdpq_detach_show();
//     }
// }
int main(void)
{
	console_init();

	printf("Entering menu loop \n");

	menu_loop();

	printf("Game Started.\n");

	while(1) {}
}