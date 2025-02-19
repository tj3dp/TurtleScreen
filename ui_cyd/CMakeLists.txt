SET(SOURCES screens/ui_LaneSelect.c
    screens/ui_LaneFunctions.c
    screens/ui_Wait.c
    ui_theme_manager.cpp
    ui_themes.cpp
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_filament_png.c
    images/ui_img_bed_png.c
    images/ui_img_1470730272.c
    images/ui_img_922480046.c
    images/ui_img_642937331.c
    images/ui_img_642936306.c
    images/ui_img_539412392.c
    images/ui_img_542316787.c
    images/ui_img_642943729.c
    images/ui_img_642942704.c
    images/ui_img_642941679.c
    images/ui_img_642940654.c
    images/ui_img_642948077.c
    images/ui_img_642947052.c
    images/ui_img_642946043.c
    images/ui_img_642945018.c
    images/ui_img_print_bar1_png.c
    images/ui_img_print_bar2_png.c)

add_library(ui ${SOURCES})
