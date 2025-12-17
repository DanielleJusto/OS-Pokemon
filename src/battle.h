#include <stdio.h>
#include <libdragon.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <rdpq.h>
#include <rdpq_sprite.h>
#include <libdragon.h>
#include <time.h>

#ifndef BATTLE_H
#define BATTLE_H

/* Declare Sprite Pointers */
extern sprite_t *self;
extern sprite_t *enemy;
extern sprite_t *battleOverlay;
extern sprite_t *battleground;
extern sprite_t *fightMenu;
extern sprite_t *itemsMenu;
extern sprite_t *enemyHP;
extern sprite_t *selfHP;
extern sprite_t *thunder;
extern sprite_t *textOverlay;
extern sprite_t *itemsMenu;

struct Pokemon{
    char name[10];
    int health;
    char attacks[2][20];
};

struct Player {
    char name[10];
    struct Pokemon *pokemon;
    int max_health;
    int health;
    char attacks[2][20];
    int inventory[2];
};

extern struct Player player1;
extern struct Player player2;

extern struct Pokemon pokemon1;
extern struct Pokemon pokemon2;

/* Basic setup function for two predetermined pokemon. */
int setup(struct Player *p1, struct Player *p2, struct Pokemon *pokemon1, struct Pokemon *pokemon2)
{
    // Initialize Pikachu 
    strcpy(pokemon1->name, "Pikachu");
    pokemon1->health = 15;
    strcpy(pokemon1->attacks[0], "THUNDER"); // Name of Attack 1
    strcpy(pokemon1->attacks[1], "SCRATCH"); // Name of Attack 2

    // Initialize Charmander
    strcpy(pokemon2->name, "Charmander");
    pokemon2->health = 15;
    strcpy(pokemon2->attacks[0], "EMBER"); // Name of Attack 1
    strcpy(pokemon2->attacks[1], "SCRATCH"); // Name of Attack 2

    /* Initialize Player 1 */
    strcpy(p1->name, "Player 1");
    p1->pokemon = pokemon1;
    p1->health = pokemon1->health;
    p1->max_health = p1->health;
    memcpy(p1->attacks, pokemon1->attacks, sizeof(p2->attacks));
    p1->inventory[0] = 1; // 1 potion
    p1->inventory[1] = 1; // 1 pokeball
     
    /* Initialize Player 2 */
    strcpy(p2->name, "Player 2");
    p2->pokemon = pokemon2;
    p2->health = pokemon2->health;
    p2->max_health = p2->health;
    memcpy(p2->attacks, pokemon2->attacks, sizeof(p2->attacks));
    p2->inventory[0] = 1; // 1 potion
    p2->inventory[1] = 1; // 1 pokeball

    return 0;
}

/* Deals damage to an opponent */
bool damage(struct Player *opponent, int damage){
    /* Dice Roll */

    int dice_roll = (rand() % 6) + 1; // generate dice roll

    if (dice_roll > 2) {
        int health = opponent->health - damage;
        if (health < 0){
            opponent->health = 0; // set lower bound
        } else {
            opponent->health = health;
        }; 
        return true;
    } else {
        return false;
    }
}

/* Heals player */
int heal(struct Player *player, int heal_points){
    int health = player->health + heal_points;
    if (health > player->max_health){
        player->health = player->max_health; // set upper bound
        player->inventory[0]--;
    } else {
        player->health = health;
        player->inventory[0]--;
    }; 
    return 0;
}   

#endif
