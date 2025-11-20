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
static sprite_t *battleOverlay;
static sprite_t *battleground;



int battle_loop(void)
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
    battleground = sprite_load("rom:/battle/battleground.sprite");
    battleOverlay = sprite_load("rom:/battle/battleOverlay.sprite");
    // selfHP = sprite_load("rom:/battle/selfHP.sprite");
    // enemyHP = sprite_load("rom:/battle/enemyHP.sprite");

    while(1){
    surface_t* disp = display_get();

    graphics_draw_box(disp, 0, 0, 320, 240, graphics_make_color(215, 215, 215, 255));
    graphics_draw_sprite_trans(disp, 0, 0, battleground);
    graphics_draw_sprite_trans(disp, 0, 0, battleOverlay);
    // graphics_draw_sprite_trans(disp, 0, 0, selfHP);
    // graphics_draw_sprite_trans(disp, 0, 0, enemyHP);
    // graphics_draw_text(disp, 55, 175, "Press START to start game.");
    // graphics_draw_text(disp, 15, 225, "CSC262: Buddy and Dani final project");
    // graphics_draw_sprite_trans(disp, 0, 125, textOverlay);
    graphics_draw_text(disp, 20, 150, "What will Pikachu do?");
    graphics_draw_text(disp, 150, 175, "FIGHT");
    graphics_draw_text(disp, 200, 175, "ITEM");

    display_show(disp);
    }
}
