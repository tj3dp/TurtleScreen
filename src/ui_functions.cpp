#include "ui_functions.h"
#include "moonraker.h"

lv_obj_t *gif_img;


void tool0Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T0");
}
void tool1Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T1");
}
void tool2Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T2");
}
void tool3Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T3");
}

void gif_end_callback(lv_timer_t * timer) {
    if(gif_img != NULL) {
        lv_obj_del(gif_img);  // Remove the GIF image from the screen
        gif_img = NULL;       // Set to NULL to avoid dangling pointer
    }
}

// Function to create and play the GIF at a specific location
void play_gif_at_position() {
    // Create the GIF image directly on the screen
    gif_img = lv_gif_create(lv_scr_act());
    lv_gif_set_src(gif_img, &barfturtle);  // Assume my_gif_dsc is defined with GIF data
    
    // Set position for the GIF at the desired x and y coordinates (e.g., 50, 100)
    lv_obj_set_pos(gif_img, 50, 50);

    // Add an event listener to remove the GIF when it finishes playing
    lv_timer_create(gif_end_callback, 1000, NULL);
}

void turtleTest(lv_event_t * e){
    play_gif_at_position();
}