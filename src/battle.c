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
#include "battle.h"

#define LIBDRAGON_RDPQ_SPRITE_H

static sprite_t *self;
static sprite_t *enemy;
static sprite_t *battleOverlay;
static sprite_t *battleground;
static sprite_t *fightMenu;
static sprite_t *itemsMenu;
// static sprite_t *enemyHP;
static sprite_t *selfHP;
// static sprite_t *thunder;

int battle = 0; 
int p1_damage = 0;
int p2_damage = 0;
int turn = 0; 

int fightChoice = 0;
bool attackSelected = false;

int itemsChoice = 0;
int itemsFrame = 0;

    // void load_background(){
    // dfs_init(DFS_DEFAULT_LOCATION);

    // debug_init_isviewer();

    // console_init();
    // joypad_init();

    // debug_init_usblog();
    // console_set_debug(true);

    // display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

    // self = sprite_load("rom:/battle/self.sprite");
    // enemy = sprite_load("rom:/battle/enemy.sprite");
    // battleground = sprite_load("rom:/battle/battleground.sprite");
    // battleOverlay = sprite_load("rom:/battle/battleOverlay.sprite");

    // surface_t* background = display_get();

    // graphics_fill_screen(disp, graphics_make_color(215, 215, 215, 255));
    // graphics_draw_sprite_trans(disp, 0, 0, battleground);
    // graphics_draw_sprite_trans(disp, 0, 0, self);
    // graphics_draw_sprite_trans(disp, 50, 0, enemy);

    // display_show(background);

    // return 0;
    // }

int get_selection(joypad_buttons_t input);
/*
- In one turn you can Attack or Use an Item, Once that's done, end loop.
*/
int battle_loop(struct Player *player, struct Player *opponent)
{
    int dfs_init(uint32_t base_fs_loc);
    dfs_init(DFS_DEFAULT_LOCATION);

    debug_init_isviewer();

    console_init();
    joypad_init();

    debug_init_usblog();
    console_set_debug(true);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

    int choice = 0;

    bool fight = false;
    bool items = false;

    /* Load all sprites */
    // thunder = sprite_load("rom:/battle/thunder.sprite");
    self = sprite_load("rom:/battle/self.sprite");
    enemy = sprite_load("rom:/battle/enemy.sprite");
    battleground = sprite_load("rom:/battle/battleground.sprite");
    battleOverlay = sprite_load("rom:/battle/battleOverlay.sprite");
    
    fightMenu = sprite_load("rom:/battle/fightMenu.sprite");
    itemsMenu = sprite_load("rom:/battle/itemMenu.sprite");

    selfHP = sprite_load("rom:/battle/selfHP.sprite");
    // enemyHP = sprite_load("rom:/battle/enemyHP.sprite");

    // int i = 0;
    bool turn_end = false;
    while(turn_end == false){
        surface_t* disp = display_get();
        joypad_poll();
        joypad_buttons_t ckeys = joypad_get_buttons_pressed(JOYPAD_PORT_1);

        /* Draw all sprites */
        graphics_fill_screen(disp, graphics_make_color(215, 215, 215, 255));
        // graphics_draw_box(disp, 0, 0, 320, 240, graphics_make_color(215, 215, 215, 255));
        graphics_draw_sprite_trans(disp, 0, 0, battleground);
        graphics_draw_sprite_trans(disp, 0, 0, self);
        graphics_draw_sprite_trans(disp, 50, 0, enemy);

        graphics_draw_sprite_trans_stride(
            disp,					// Load into itemsFrame buffer
            0,	                    // Move it towards the right
            0,					    // Don't move up or down
            selfHP,				    // Load this spritesheet
            0 		                
        );

        // graphics_draw_sprite_trans_stride(
        // 	disp,					// Load into itemsFrame buffer
        // 	0,	                    // Move it towards the right
        // 	0,					    // Don't move up or down
        // 	enemyHP,				// Load this spritesheet
        // 	damage 		    // Select the next sprite in the spritesheet every 4 itemsFrames
        // );

        char health_str1[10];
        itoa(opponent->health, health_str1, 10);
        graphics_draw_text(disp, 15, 15, "Charmander");
        graphics_draw_text(disp, 15, 30, health_str1);

        char health_str2[10];
        itoa(player->health, health_str2, 10);
        graphics_draw_text(disp, 200, 115, "Pikachu");
        graphics_draw_text(disp, 200, 130, health_str2);

        if(choice == 1) { // you've made a choice between fight and item
            if(fight == true){
                graphics_draw_sprite_trans_stride(
                    disp,					// Load into itemsFrame buffer
                    0,	                    // Move it towards the right
                    0,					    // Don't move up or down
                    fightMenu,				// Load this spritesheet
                    fightChoice
                );
                graphics_draw_text(disp, 30, 170, "Thunder");
                graphics_draw_text(disp, 45, 137, "Player 1");

                if(fightChoice == 0){
                    if(ckeys.d_left || ckeys.d_right){
                        fightChoice = 1;
                    }
                } else if(fightChoice == 1){
                    if(ckeys.a){
                        fightChoice = 2;
                    }
                    if(ckeys.b){
                        choice = 0;
                        fightChoice = 0;
                    }
                } else if(fightChoice == 2){
                    graphics_draw_text(disp, 180, 85, "THUNDER");
                    graphics_draw_text(disp, 185, 100, "Power: 20");
                    graphics_draw_text(disp, 185, 115, "Accuracy: 100");
                    graphics_draw_text(disp, 185, 148, "use move?");
                    
                    if(ckeys.a){
                        // ATTACK LOOP
                        // graphics_draw_sprite_trans_stride(
                        //     disp,					// Load into itemsFrame buffer
                        //     0,	                    // Move it towards the right
                        //     0,					    // Don't move up or down
                        //     thunder,				    // Load this spritesheet
                        //     0 		                
                        // );
                        fightChoice = 0;
                        damage(opponent, 2);
                        turn_end = true;
                    }
                    if(ckeys.d_down){
                        fightChoice = 3;
                    }
                } else if(fightChoice == 3){
                    graphics_draw_text(disp, 180, 85, "THUNDER");
                    graphics_draw_text(disp, 185, 100, "Power: 20");
                    graphics_draw_text(disp, 185, 115, "Accuracy: 100");
                    graphics_draw_text(disp, 185, 148, "use move?");
                    if(ckeys.a){
                        fightChoice = 1;
                        turn_end = true;
                    }
                    if(ckeys.d_up){
                        fightChoice = 2;
                    }
                }

            } else if(items == true){
                graphics_draw_sprite_trans_stride(
                    disp,					// Load into itemsFrame buffer
                    0,	                    // Move it towards the right
                    0,					    // Don't move up or down
                    itemsMenu,				// Load this spritesheet
                    itemsFrame
                );
                if(ckeys.d_left){
                    itemsFrame = 1;
                    itemsChoice = 1;
                }
                if(ckeys.d_right){
                    itemsFrame = 4;
                    itemsChoice = 2;
                }
                if(itemsChoice == 1){
                    // potion selected
                    if(itemsFrame == 1){
                        if(ckeys.a){
                            itemsFrame = 2;
                        }
                        if(ckeys.b) {
                            choice = 0;
                            itemsFrame = 0;
                        }
                    } else if(itemsFrame == 2){
                        graphics_draw_text(disp, 180, 75, "POTION");
                        graphics_draw_text(disp, 185, 90, "+20 HP");
                        graphics_draw_text(disp, 185, 140, "use potion?");
                        if(ckeys.d_down){
                            itemsFrame = 3;
                        }
                        if(ckeys.a){
                            //USE POTION
                            choice = 0;
                            itemsFrame = 0;
                            turn_end = true;
                        }
                    } else if(itemsFrame == 3){
                        graphics_draw_text(disp, 180, 75, "POTION");
                        graphics_draw_text(disp, 185, 90, "+20 HP");
                        graphics_draw_text(disp, 185, 140, "use potion?");
                        if(ckeys.d_up){
                            itemsFrame = 2;
                        }
                        if(ckeys.a){
                            itemsFrame = 1;
                            turn_end = true;
                        }
                    }
                    
                } else if (itemsChoice == 2){
                    // pokeball selected
                    if(ckeys.a){
                        itemsFrame = 5;
                        turn_end = true;
                    }
                    if(itemsFrame == 4){
                        if(ckeys.b) {
                            choice = 0;
                            itemsFrame = 0;
                        }
                    } else if(itemsFrame == 5){
                        graphics_draw_text(disp, 180, 75, "POKEBALL");
                        graphics_draw_text(disp, 185, 100, "you can't use");
                        graphics_draw_text(disp, 185, 115, "that now.");
                        if(ckeys.b) {
                            itemsFrame = 4;
                        }
                    }
                }
            } else {
                choice = 0;
            }
        } else if(choice == 0) { // No choice made between item and attack
            if(ckeys.a) {
                choice = 1;
            }
            if(ckeys.d_left){
                fight = true;
                items = false;
                battle = 1;
            } else if(ckeys.d_right){
                items = true;
                fight = false;
                battle = 2;
            }

            graphics_draw_sprite_trans_stride(
                disp,					// Load into itemsFrame buffer
                0,	                    // Move it towards the right
                0,					    // Don't move up or down
                battleOverlay,				// Load this spritesheet
                battle
            );
            graphics_draw_text(disp, 30, 175, "What will");
            graphics_draw_text(disp, 30, 190, "Pikachu do?");
            graphics_draw_text(disp, 165, 180, "FIGHT");
            graphics_draw_text(disp, 250, 180, "ITEM");
        }
        display_show(disp);
    }
    return 0;
}
