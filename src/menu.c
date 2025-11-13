#include <stdio.h>
#include <libdragon.h>
#include <joypad.h>

/* Menu/Load Screen 
    - Play Button
*/ 

void menu_loop(){
    bool a_pressed = false;
    joypad_port_t port = JOYPAD_PORT_1;

    joypad_buttons_t btn = joypad_get_buttons_pressed(joypad_port_t port);
    if (btn.a){
        a_pressed = true;
        printf("a_pressed");
    }
}