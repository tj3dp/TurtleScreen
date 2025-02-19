#include "ui_functions.h"
#include "moonraker.h"

lv_obj_t *gif_img;
lv_color_t color;

int selected = -1;

void afcBrushCall(){
    moonraker.post_gcode_to_queue("AFC_BRUSH");
}

void afcCutCall(){
    moonraker.post_gcode_to_queue("AFC_CUT");
}

void afcKickCall(){
    moonraker.post_gcode_to_queue("AFC_KICK");
}

void afcParkCall(){
    moonraker.post_gcode_to_queue("AFC_PARK");
}

void afcPoopCall(){
    moonraker.post_gcode_to_queue("AFC_POOP");
}

void btPrepCall(){
    moonraker.post_gcode_to_queue("BT_PREP");
}

void g32Call(){
    moonraker.post_gcode_to_queue("G32");
}

void DoUnload()
{
    moonraker.post_gcode_to_queue("BT_TOOL_UNLOAD");
}

void DoLoadTool(int tool)
{
    char command[10];
    snprintf(command, sizeof(command), "T%d", tool);
    moonraker.post_gcode_to_queue(command);
}

void DoEjectLane(int lane)
{
    char command[40];
    snprintf(command, sizeof(command), "BT_LANE_EJECT LANE=%d", lane);
    moonraker.post_gcode_to_queue(command);
    
}
