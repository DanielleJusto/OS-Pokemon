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
    int attacks[2]; // array 2
};

struct Player {
    char name[10];
    struct Pokemon *pokemon;
    int max_health;
    int health;
    int *attacks;
    int inventory[2]; // array 2
};

extern struct Player player1;
extern struct Player player2;

extern struct Pokemon pokemon1;
extern struct Pokemon pokemon2;

/* Basic setup function for two predetermined pokemon. */
int setup(struct Player *p1, struct Player *p2, struct Pokemon *pokemon1, struct Pokemon *pokemon2)
{
    // Initialize Pikachu 
    strcpy(pokemon1->name, "Pikachu\0");
    pokemon1->health = 15; // test heal
    pokemon1->attacks[0] = 1; // damage of attack 1
    pokemon1->attacks[1] = 2; // damage of attack 2

    // Initialize Charmander
    strcpy(pokemon2->name, "Charmander\0");
    pokemon2->health = 15;
    pokemon2->attacks[0] = 1;
    pokemon2->attacks[1] = 2;

    /* Initialize Player 1 */
    strcpy(p1->name, "Player 1\0");
    p1->pokemon = pokemon1;
    p1->health = pokemon1->health;
    memcpy(&p1->max_health, &p1->health, sizeof(int));
    p1->attacks = pokemon1->attacks;
    p1->inventory[0] = 1; // 1 potion
    p1->inventory[0] = 1; // 1 pokeball
     
    /* Initialize Player 2 */
    strcpy(p2->name, "Player 2\0");
    p2->pokemon = pokemon2;
    p2->health = pokemon2->health;
    memcpy(&p2->max_health, &p2->health, sizeof(int));
    p2->attacks = pokemon2->attacks;
    p2->inventory[0] = 1; // 1 potion
    p2->inventory[0] = 1; // 1 pokeball

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

// int pokemon_init(int player, int choice){
//     char name[20];
//     int health;
//     int attacks;
//     // Select Attributes
//     switch(choice){
//         case 0:
//             /* Initialize Pikachu */
//             strcpy(name, "Pikachu");
//             health = 10;
//             attacks = 2;
//             break;
//         case 1:
//             /* Initialize Charmander */
//             strcpy(name,"Charmander");
//             attacks = 2;
//             health = 10;
//             break;
//         case 2:
//             /* Initialize Charmander */
//             strcpy(name,"Charmander");
//             attacks = 2;
//             health = 10;
//             break;
//     }
//     if (player == 1){
//         strcpy(pokemon1.name,name);
//         pokemon1.health = health;
//         pokemon1.attacks = attacks;
//     } else if (player == 2){
//         strcpy(pokemon2.name,name);
//         pokemon2.health = health;
//         pokemon2.attacks = attacks;
//     }
//     return 0;
// }
// int initialize_pika(struct Pokemon pokemon)
// {
//     strcpy("Pikachu", pokemon);
//     return 0;
// }

// int pokemon_init(player1){
//     /* Initialize Player 1 */
//     player1.health = pokemon1.health;
//     player1.max_health = player1.health;
//     player1.pokemon = pokemon1;
//     player1.attacks = pokemon1.attacks;
     
//     /* Initialize Player 2 */
//     player2.health = pokemon2.health;
//     player2.max_health = player2.health;
//     player2.pokemon = pokemon2;
//     player2.attacks = pokemon2.attacks;

//     return 0;
// }

// int players_init(void)
// {
//        /* Initialize Player 1 */
//     player1.health = pokemon1.health;
//     player1.max_health = player1.health;
//     player1.pokemon = pokemon1;
//     player1.attacks = pokemon1.attacks;
     
//     /* Initialize Player 2 */
//     player2.health = pokemon2.health;
//     player2.max_health = player2.health;
//     player2.pokemon = pokemon2;
//     player2.attacks = pokemon2.attacks;
//     return 0;
// }


// int choose_pokemon(void)
// {
//     // Pla yer 1 chooses pokemon
//     bool player_choice = false;
//     int selection = 0;

//     printf("Player 1, Choose Your Pokemon.\n");
//     while(player_choice == false){
//         joypad_poll();
//         joypad_port_t port;
//         if (joypad_is_connected(JOYPAD_PORT_1)) port = JOYPAD_PORT_1;
//         joypad_buttons_t input = joypad_get_buttons_pressed(port);

//         if(input.d_left == 1) selection--;
//         if(input.d_right == 1) selection++;
//         if(input.a == 1) player_choice = true;

//         if (selection > 2) selection = 2;
//         if (selection < 0) selection = 0;

//         /* THERE MUST BE A BETTER WAY */
//         printf("Player 1, Choose Your Pokemon.\n");
//         printf("%d\n", selection);
//         console_clear();
//     }
//     pokemon_init(1, selection);

//     // Reset choice vars
//     player_choice = false;
//     selection = 0;
//     console_clear();
    
//     // Player 2 chooses pokemon
//     printf("Player 2, Choose Your Pokemon.\n");
//     while(player_choice == false){
//         joypad_poll();
//         joypad_port_t port;
//         if (joypad_is_connected(JOYPAD_PORT_1)) port = JOYPAD_PORT_1;
//         joypad_buttons_t input = joypad_get_buttons_pressed(port);
        
//         if(input.d_left == 1) selection--;
//         if(input.d_right == 1) selection++;
//         if(input.a == 1) player_choice = true;

//         if (selection > 2) selection = 2;
//         if (selection < 0) selection = 0;

//         printf("Player 2, Choose Your Pokemon.\n");
//         printf("%d\n", selection);
//         console_clear();
//     }
//     pokemon_init(2, selection);

//     // Close out
//     return 0;
// }

// int 
// attack(struct Player opp, int attack)
// {
//     opp.health = opp.health - attack;
// }

// int
// battle_loop(void)
// {  

//     players_init();

//     printf("STARTING STATS:\n");
//     printf("Player 1 Health: %d\n", player1.health);
//     printf("Player 1 Damage: %d\n", player1.attacks);
//     printf("Player 1 Pokemon: %s\n", player1.pokemon.name);
//     printf("Player 2 Health: %d\n", player2.health);
//     printf("Player 2 Damage: %d\n", player2.attacks);
//     printf("Player 2 Pokemon: %s\n", player2.pokemon.name);

//     return 0;
// }
