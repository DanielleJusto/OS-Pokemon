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


static sprite_t *self;
static sprite_t *enemy;
static sprite_t *battleOverlay;
static sprite_t *battleground;
static sprite_t *fightMenu;
static sprite_t *itemsMenu;
static sprite_t *enemyHP;
static sprite_t *selfHP;
static sprite_t *thunder;

int select = 0;
int self_damage = 0;
int enemy_damage = 0;
int turn = 0;

int fightChoice = 0;
bool attackSelected = false;

int itemsChoice = 0;
int itemsFrame = 0;

// char health_str1[10];
// char health_str_2[10];

int battle_loop(struct Player *player, struct Player *opp)
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

    int choice = 0;
    int i = 0;

    bool fight = false;
    bool items = false;

    thunder = sprite_load("rom:/battle/thunder.sprite");
    self = sprite_load("rom:/battle/self.sprite");
    enemy = sprite_load("rom:/battle/enemy.sprite");
    battleground = sprite_load("rom:/battle/battleground.sprite");
    battleOverlay = sprite_load("rom:/battle/battleOverlay.sprite");
    
    fightMenu = sprite_load("rom:/battle/p1_fightMenu.sprite");
    itemsMenu = sprite_load("rom:/battle/itemMenu.sprite");

    selfHP = sprite_load("rom:/battle/selfHP.sprite");
    enemyHP = sprite_load("rom:/battle/enemyHP.sprite");

    while(1){
    surface_t* disp = display_get();
    joypad_poll();
    joypad_buttons_t ckeys = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    graphics_fill_screen(disp, graphics_make_color(215, 215, 215, 255));
    // graphics_draw_box(disp, 0, 0, 320, 240, graphics_make_color(215, 215, 215, 255));
    graphics_draw_sprite_trans(disp, 0, 0, battleground);
    graphics_draw_sprite_trans(disp, 0, 0, self);
    graphics_draw_sprite_trans(disp, 50, 0, enemy);

    graphics_draw_sprite_trans_stride(
		disp,					// Load into itemsFrame buffer
		185,	                    // Move it towards the right
		106,					    // Don't move up or down
		selfHP,				    // Load this spritesheet
		15-player->health	                
	);
    // graphics_draw_text(disp, 15, 30, health_str1);
    // itoa(player->health, health_str1, 10);
    graphics_draw_sprite_trans_stride(
		disp,					// Load into itemsFrame buffer
		0,	                    // Move it towards the right
		0,					    // Don't move up or down
		enemyHP,				// Load this spritesheet
		15-opp->health      // Select the next sprite in the spritesheet every 4 itemsFrames
	);
    // graphics_draw_text(disp, 15, 30, health_str2);
    // itoa(enemy->health, health_str1, 10);

    graphics_draw_text(disp, 15, 15, "Charmander");
    graphics_draw_text(disp, 200, 115, "Pikachu");

    if(choice == 1) {
        if(fight == true){
            graphics_draw_sprite_trans_stride(
		        disp,					// Load into itemsFrame buffer
		        0,	                    // Move it towards the right
		        0,					    // Don't move up or down
		        fightMenu,				// Load this spritesheet
		        fightChoice
	        );
            if(fightChoice == 0){
                graphics_draw_text(disp, 30, 170, "Thunder");
                graphics_draw_text(disp, 180, 170, "Scratch");
                if(ckeys.d_left){
                    // Select Thunder
                    fightChoice = 1;
                }
                if(ckeys.d_right){
                    // Select Scratch
                    fightChoice = 2;
                }
            } else if(fightChoice == 1){
                // Thunder move currently selected
                graphics_draw_text(disp, 30, 170, "Thunder");
                graphics_draw_text(disp, 180, 170, "Scratch");
                if(ckeys.a){
                    // shows move stats and prompt user to use move
                    fightChoice = 3;
                }
                if(ckeys.d_right){
                    // select Scratch
                    fightChoice = 2;
                }
                if(ckeys.b){
                    // exit fight menu
                    choice = 0;
                    fightChoice = 0;
                }
            } else if(fightChoice == 3){
                // STATS + Use Thunder -> Yes
                graphics_draw_text(disp, 30, 170, "Thunder");
                graphics_draw_text(disp, 180, 85, "THUNDER");
                graphics_draw_text(disp, 185, 100, "Power: 20");
                graphics_draw_text(disp, 185, 115, "Accuracy: 100");
                graphics_draw_text(disp, 185, 148, "use move?");
                
                if(ckeys.a){
                    // for(int i = 0; i < 7; i++){
                        graphics_draw_sprite_trans_stride(
		                    disp,					// Load into itemsFrame buffer
		                    0,	                    // Move it towards the right
		                    0,					    // Don't move up or down
		                    thunder,				// Load this spritesheet
		                    (i>>2)%36		                
	                    );
                        i++;
                        // usleep(500000);
                    // }
                    
                    // enemy_damage++;
                    // enemy_damage++;
                    damage(opp, 3);
                    choice = 0;
                    fightChoice = 0;
                }
                if(ckeys.d_down){
                    // Select NO
                    fightChoice = 4;
                }
            } else if(fightChoice == 4){
                // STATS + Use Thunder -> No
                graphics_draw_text(disp, 30, 170, "Thunder");
                graphics_draw_text(disp, 180, 85, "THUNDER");
                graphics_draw_text(disp, 185, 100, "Power: 20");
                graphics_draw_text(disp, 185, 115, "Accuracy: 100");
                graphics_draw_text(disp, 185, 148, "use move?");
                if(ckeys.a){
                    // Didn't use move, back to fight menu
                    fightChoice = 1;
                }
                if(ckeys.d_up){
                    // Select YES
                    fightChoice = 3;
                }
            } else if(fightChoice == 2){
                // SCRATCH selected
                graphics_draw_text(disp, 30, 170, "Thunder");
                graphics_draw_text(disp, 180, 170, "Scratch");
                if(ckeys.d_left){
                    // select Thunder
                    fightChoice = 1;
                }
                if(ckeys.a){
                    // show Stats menu, promt user to use scratch
                    fightChoice = 5;
                }
                if(ckeys.b){
                    // exit fight menu
                    choice = 0;
                    fightChoice = 0;
                }
            } else if(fightChoice == 5){
                // STATS + use Scratch -> YES
                graphics_draw_text(disp, 180, 170, "Scratch");
                graphics_draw_text(disp, 30, 85, "SCRATCH");
                graphics_draw_text(disp, 35, 100, "Power: 10");
                graphics_draw_text(disp, 35, 115, "Accuracy: 100");
                graphics_draw_text(disp, 35, 148, "use move?");
                
                if(ckeys.a){
                    // ATTACK LOOP
                    // graphics_draw_sprite_trans_stride(
		            //     disp,					// Load into itemsFrame buffer
		            //     0,	                    // Move it towards the right
		            //     0,					    // Don't move up or down
		            //     thunder,				    // Load this spritesheet
		            //     0 		                
	                // );
                    // enemy_damage++;
                    damage(opp, 1);
                    choice = 0;
                    fightChoice = 0;
                }
                if(ckeys.d_down){
                    // select NO
                    fightChoice = 6;
                }
            } else if(fightChoice == 6){
                // STATS + use Scratch -> NO
                graphics_draw_text(disp, 180, 170, "Scratch");
                graphics_draw_text(disp, 30, 85, "SCRATCH");
                graphics_draw_text(disp, 35, 100, "Power: 10");
                graphics_draw_text(disp, 35, 115, "Accuracy: 100");
                graphics_draw_text(disp, 35, 148, "use move?");
                
                if(ckeys.a){
                    // no move used, go back to fight menu
                    fightChoice = 2;
                }
                if(ckeys.d_up){
                    // Select YES
                    fightChoice = 5;
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
                }else if(itemsFrame == 2){
                    graphics_draw_text(disp, 180, 75, "POTION");
                    graphics_draw_text(disp, 185, 90, "+20 HP");
                    
                    if(self_damage > 0){
                        graphics_draw_text(disp, 185, 140, "use potion?");
                        if(ckeys.a){
                            self_damage--;
                            choice = 0;
                            itemsFrame = 0;
                        }
                    } else if(self_damage == 0){
                        graphics_draw_text(disp, 185, 140, "FULL HEALTH");
                    }
                    
                    if(ckeys.d_down){
                        itemsFrame = 3;
                    }
                }else if(itemsFrame == 3){
                    graphics_draw_text(disp, 180, 75, "POTION");
                    graphics_draw_text(disp, 185, 90, "+20 HP");
                    graphics_draw_text(disp, 185, 140, "use potion?");
                    if(ckeys.d_up){
                        itemsFrame = 2;
                    }
                    if(ckeys.a){
                        itemsFrame = 1;
                    }
                }
                
            } else if (itemsChoice == 2){
                // pokeball selected
                if(ckeys.a){
                    itemsFrame = 5;
                }
                if(itemsFrame == 4){
                    if(ckeys.b) {
                        choice = 0;
                        itemsFrame = 0;
                    }
                }else if(itemsFrame == 5){
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
    } else if(choice == 0) {
        if(ckeys.a) {
            choice = 1;
        }
        if(ckeys.d_left){
            fight = true;
            items = false;
            select = 1;
        }else if(ckeys.d_right){
            items = true;
            fight = false;
            select = 2;
        }

        graphics_draw_sprite_trans_stride(
	        disp,					// Load into itemsFrame buffer
	        0,	                    // Move it towards the right
            0,					    // Don't move up or down
	        battleOverlay,				// Load this spritesheet
	        select
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
