#include <stdio.h>
#include <libdragon.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <rdpq.h>
#include <rdpq_sprite.h>

int gameOver(struct Player *player)
{
    /* Load Sprites */
    sprite_t *textOverlay = sprite_load("rom:/battle/textOverlay.sprite");

    sprite_t *winner;
    if(strcmp("BUDDY", player->name) == 0){
        winner = sprite_load("rom:/explore/buddy.sprite");
    } else {
        winner = sprite_load("rom:/explore/dani.sprite");
    }

    joypad_init();
    int state = 0;
    bool exit = false;
    while(exit == false){
        surface_t* disp = display_get();
        
        graphics_fill_screen(disp, graphics_make_color(154, 139, 130, 255));

        graphics_draw_sprite_trans_stride(
            disp,					// Load into itemsFrame buffer
            128,	                // Move it towards the right
            44,					    // Don't move up or down
            winner,				    // Load this spritesheet
            0                
        );

        joypad_poll();
        joypad_port_t port;
        if (joypad_is_connected(JOYPAD_PORT_1)) port = JOYPAD_PORT_1;

        joypad_buttons_t input = joypad_get_buttons_pressed(port);

        graphics_draw_sprite_trans(disp, 0, 125, textOverlay);

        switch (state){
            case 0:
                graphics_draw_text(disp, 24, 150, "GAME OVER!");
                if (input.a) state++;
                break;
            case 1:
                graphics_draw_text(disp, 24, 150, "Winner: ");
                graphics_draw_text(disp, 85, 150, player->name);
                if (input.a) state++;
                break;
            case 2:
                graphics_draw_text(disp, 24, 150, "Press START to exit game.");
                if (input.start == 1) {exit = true;}
                break;
        }
        display_show(disp);
    }
    /* Free Sprites */
    sprite_free(textOverlay);
    sprite_free(winner);
    return 0;
}