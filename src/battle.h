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

#ifndef BATTLE_H
#define BATTLE_H

struct Pokemon{
    char name[10];
    int health;
    int attacks[2]; // array 2
};

struct Player {
    struct Pokemon *pokemon;
    int max_health;
    int health;
    int *attacks; // pointer to pokemon attacks
    int items[2]; // array 2
};

extern struct Player player1;
extern struct Player player2;

extern struct Pokemon pokemon1;
extern struct Pokemon pokemon2;

/*
Basic setup function for two predetermined pokemon.
*/
int setup(struct Player *p1, struct Player *p2, struct Pokemon *pokemon1, struct Pokemon *pokemon2)
{
    // Initialize Pikachu 
    strcpy(pokemon1->name, "Pikachu\0");
    pokemon1->health = 15;
    pokemon1->attacks[0] = 1;
    pokemon1->attacks[1] = 2;

    // Initialize Charmander
    strcpy(pokemon2->name, "Charmander\0");
    pokemon2->health = 15;
    pokemon2->attacks[0] = 1;
    pokemon2->attacks[1] = 2;

    /* Initialize Player 1 */
    p1->pokemon = pokemon1;
    p1->health = 10;
    p1->max_health =10;
    p1->attacks = pokemon1->attacks;
     
    /* Initialize Player 2 */
    p2->pokemon = pokemon2;
    p2->health = 10;
    p2->max_health = 10;
    p2->attacks = pokemon2->attacks;

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
