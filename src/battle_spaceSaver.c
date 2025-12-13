#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <rdpq.h>
#include <rdpq_sprite.h>
#include <libdragon.h>

typedef struct {
    sprite_t *self;
    sprite_t *enemy;
    sprite_t *battleground;
    sprite_t *battleOverlay;
    sprite_t *fightMenu;
    sprite_t *itemsMenu;
    sprite_t *selfHP;
    sprite_t *enemyHP;
    sprite_t *thunder; // load only when needed
} battle_sprites_t;

// Helper to load a sprite or exit if it fails
static sprite_t* load_sprite_or_die(const char* path) {
    sprite_t* s = sprite_load(path);
    if (!s) {
        printf("Failed to load sprite: %s\n", path);
        exit(-1);
    }
    return s;
}

// Free all loaded sprites
static void free_battle_sprites(battle_sprites_t* sprites) {
    if (!sprites) return;
    if (sprites->self) sprite_free(sprites->self);
    if (sprites->enemy) sprite_free(sprites->enemy);
    if (sprites->battleground) sprite_free(sprites->battleground);
    if (sprites->battleOverlay) sprite_free(sprites->battleOverlay);
    if (sprites->fightMenu) sprite_free(sprites->fightMenu);
    if (sprites->itemsMenu) sprite_free(sprites->itemsMenu);
    if (sprites->selfHP) sprite_free(sprites->selfHP);
    if (sprites->enemyHP) sprite_free(sprites->enemyHP);
    if (sprites->thunder) sprite_free(sprites->thunder);
}

int battle = 0;
int choice = 0;       // main menu choice
int fightChoice = 0;  // fight submenu
bool fight = false;
bool items = false;
int itemsChoice = 0;
int itemsFrame = 0;

int battle_loop(void) {
    int dfs_init(uint32_t base_fs_loc);
    dfs_init(DFS_DEFAULT_LOCATION);
    debug_init_isviewer();
    console_init();
    joypad_init();
    debug_init_usblog();
    console_set_debug(true);
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);

    battle_sprites_t sprites = {0};

    // Load only essential sprites at start
    sprites.self          = load_sprite_or_die("rom:/battle/self.sprite");
    sprites.enemy         = load_sprite_or_die("rom:/battle/enemy.sprite");
    sprites.battleground  = load_sprite_or_die("rom:/battle/battleground.sprite");
    sprites.battleOverlay = load_sprite_or_die("rom:/battle/battleOverlay.sprite");
    // sprites.fightMenu     = load_sprite_or_die("rom:/battle/fightMenu.sprite");
    // sprites.itemsMenu     = load_sprite_or_die("rom:/battle/itemMenu.sprite");
    sprites.selfHP        = load_sprite_or_die("rom:/battle/selfHP.sprite");
    // sprites.enemyHP        = load_sprite_or_die("rom:/battle/enemyHP.sprite");


    while(1) {
        surface_t* disp = display_get();
        joypad_poll();
        joypad_buttons_t ckeys = joypad_get_buttons_pressed(JOYPAD_PORT_1);

        // Clear screen
        graphics_fill_screen(disp, graphics_make_color(215, 215, 215, 255));

        // Draw static sprites
        graphics_draw_sprite_trans(disp, 0, 0, sprites.battleground);
        graphics_draw_sprite_trans(disp, 0, 0, sprites.self);
        graphics_draw_sprite_trans(disp, 50, 0, sprites.enemy);
        graphics_draw_sprite_trans_stride(disp, 0, 0, sprites.selfHP, 0);
        graphics_draw_text(disp, 15, 15, "Charmander");
        graphics_draw_text(disp, 200, 115, "Pikachu");

        // Main menu
        if(choice == 0) {
            graphics_draw_sprite_trans_stride(disp, 0, 0, sprites.battleOverlay, battle);
            graphics_draw_text(disp, 30, 175, "What will");
            graphics_draw_text(disp, 30, 190, "Pikachu do?");
            graphics_draw_text(disp, 165, 180, "FIGHT");
            graphics_draw_text(disp, 250, 180, "ITEM");

            if(ckeys.a) choice = 1;
            if(ckeys.d_left) {fight = true; items = false; battle = 1;}
            if(ckeys.d_right){items = true; fight = false; battle = 2;}
        }

        // Fight menu
        if(choice == 1 && fight) {
            if(!sprites.fightMenu) {
                sprites.fightMenu = load_sprite_or_die("rom:/battle/fightMenu.sprite");
            }
            graphics_draw_sprite_trans_stride(disp, 0, 0, sprites.fightMenu, fightChoice);
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
                if(!sprites.thunder) {
                    sprites.thunder = load_sprite_or_die("rom:/battle/thunder.sprite");
                }

                graphics_draw_text(disp, 180, 85, "THUNDER");
                graphics_draw_text(disp, 185, 100, "Power: 20");
                graphics_draw_text(disp, 185, 115, "Accuracy: 100");
                graphics_draw_text(disp, 185, 148, "use move?");
                
                if(ckeys.a){
                    // ATTACK LOOP
                    graphics_draw_sprite_trans_stride(
		                disp,					// Load into itemsFrame buffer
		                0,	                    // Move it towards the right
		                0,					    // Don't move up or down
		                sprites.thunder,				    // Load this spritesheet
		                0 		                
	                );
                    
                    choice = 0;
                    fightChoice = 0;
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
                }
                if(ckeys.d_up){
                    fightChoice = 2;
                }
            }

            // Navigate fight menu
            if(fightChoice == 0 && (ckeys.d_left || ckeys.d_right)) fightChoice = 1;
            if(fightChoice == 1) {
                if(ckeys.a) fightChoice = 2;
                if(ckeys.b) { choice = 0; fightChoice = 0; }
            }
            if(fightChoice == 3) {
                if(ckeys.a) fightChoice = 1;
                if(ckeys.d_up) fightChoice = 2;
            }
        } else if(choice == 1 && items) {
            // ITEMS MENU
            if(!sprites.itemsMenu) {
                sprites.itemsMenu = load_sprite_or_die("rom:/battle/itemsMenu.sprite");
            }
            graphics_draw_sprite_trans_stride(disp, 0, 0, sprites.itemsMenu, itemsFrame);
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
                    graphics_draw_text(disp, 185, 140, "use potion?");
                    if(ckeys.d_down){
                        itemsFrame = 3;
                    }
                    if(ckeys.a){
                        //USE POTION
                        choice = 0;
                        itemsFrame = 0;
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

        display_show(disp);
    }

    // Free all sprites at the end
    free_battle_sprites(&sprites);
    return 0;
}
