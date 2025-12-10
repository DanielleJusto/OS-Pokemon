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

/* Menu/Load Screen 
    - Print title to screen
    - Play button --> when pressed start game
*/ 

typedef enum {
    DOWN = 0,
    LEFT,
    RIGHT,
    UP
} direction_t;

sprite_t* choose_character(void)
{
    int dfs_init(uint32_t base_fs_loc);
    dfs_init(DFS_DEFAULT_LOCATION);

    debug_init_isviewer();
    console_init();
    joypad_init();
    debug_init_usblog();
    console_set_debug(true);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);

    sprite_t* buddy = sprite_load("rom:/explore/buddy.sprite");
    sprite_t* dani = sprite_load("rom:/explore/dani.sprite");

    bool choiceMade = false;
    sprite_t* character_choice = buddy;
    sprite_t* the_unwanted = dani;
    char selection[10];
    strcpy(selection, "Buddy");
    int x = 76;
    int y = 150;

    while (choiceMade == false) {
        surface_t* disp = display_get();
        joypad_poll();
        
        joypad_buttons_t ckeys = joypad_get_buttons_pressed(JOYPAD_PORT_1);
        graphics_fill_screen(disp, graphics_make_color(154, 139, 130, 255));
        graphics_draw_text(disp, 110, 30, "WHO ARE YOU?");
        graphics_draw_text(disp, x, y, selection);

        graphics_draw_sprite_trans_stride(
            disp,					// Load into itemsFrame buffer
            64,	                // Move it towards the right
            88,					// Don't move up or down
            buddy,				    // Load this spritesheet
            0                
        );

        /*UNCOMMENT TO ADD DANI*/

        // graphics_draw_sprite_trans_stride(
        //     disp,					// Load into itemsFrame buffer
        //     216,	                // Move it towards the right
        //     88,					// Don't move up or down
        //     dani,				    // Load this spritesheet
        //     0                
        // );
        if(ckeys.d_left){x = 76; y= 150; strcpy(selection, "Buddy"); character_choice = buddy; the_unwanted = dani;}
        if(ckeys.d_right){x = 216; y= 150; strcpy(selection, "Dani"); character_choice = dani; the_unwanted = buddy;}
        if(ckeys.a){choiceMade = true;}
        display_show(disp);
    }
    sprite_free(the_unwanted);
    return character_choice;
}

int explore_loop(sprite_t* avatar)
{
    int dfs_init(uint32_t base_fs_loc);
    dfs_init(DFS_DEFAULT_LOCATION);

    debug_init_isviewer();
    console_init();
    joypad_init();
    debug_init_usblog();
    console_set_debug(true);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);

    int x = 128, y = 88;           // initial position
    direction_t dir = DOWN;         // current facing direction
    int frame = 0;                  // current sprite frame 0-3
    int frame_timer = 0;            // simple timer to control animation speed
    const int FRAME_DELAY = 8;      // smaller delay for smoother cycling

    bool battle_start = false;
    bool moving = false;

    while (!battle_start) {
        surface_t* disp = display_get();
        joypad_poll();
        joypad_port_t port = JOYPAD_PORT_1;
        joypad_inputs_t input = joypad_get_inputs(port);
        joypad_buttons_t buttons = joypad_get_buttons_pressed(port);
        // joypad_inputs_s aInput = joypad_get_buttons_pressed(port);

        graphics_fill_screen(disp, graphics_make_color(154, 139, 130, 255));
        graphics_draw_text(disp, 40, 30, "Press START to Commence Battle!!");

        // Check movement and update position
        if (input.stick_y > 0) {
            y -= 2;
            dir = UP;
            moving = true;
        } 
        if (input.stick_y < 0) {
            y += 2;
            dir = DOWN;
            moving = true;
        } 
        if (input.stick_x < 0) {
            x -= 2;
            dir = LEFT;
            moving = true;
        } 
        if (input.stick_x > 0) {
            x += 2;
            dir = RIGHT;
            moving = true;
        }

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > 320 - 64) x = 320 - 64;
        if (y > 240 - 64) y = 240 - 64;


        // Update animation frame only if moving
        if(moving) {
            frame_timer++;
            if (frame_timer >= FRAME_DELAY) {
                frame = (frame + 1) % 4; // cycle frames 0-3 continuously
                frame_timer = 0;
            }
        }

        // Calculate sprite index based on current direction and frame
        int sprite_index = frame + (dir * 4);

        // Draw the sprite
        graphics_draw_sprite_trans_stride(disp, x, y, avatar, sprite_index);

        display_show(disp);

        if (buttons.start) {
            battle_start = true;
        }
        moving = false;
    }
    sprite_free(avatar);
    return 0;
}
