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

int explore_loop(void)
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
        graphics_draw_sprite_trans_stride(disp, x, y, buddy, sprite_index);

        display_show(disp);

        if (buttons.start) {
            battle_start = true;
        }
        moving = false;
    }

    sprite_free(buddy);
    return 0;
}
