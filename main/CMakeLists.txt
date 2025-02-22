# SET(SRCS fonts/ui_font_montserrat_96.c)
# SET(SRCS fonts/ui_font_montserrat_140.c)

idf_component_register(SRCS "fonts/ui_font_montserrat_96.c" "fonts/ui_font_montserrat_140.c" "main.c"
                    INCLUDE_DIRS ".")

lvgl_port_create_c_image("images/esp_logo.png" "images/" "ARGB8888" "NONE")
lvgl_port_add_images(${COMPONENT_LIB} "images/")

# file(GLOB_RECURSE FONT_SOURCES "fonts/*.c")
# idf_component_register("fonts/")

set_source_files_properties(
    PROPERTIES COMPILE_OPTIONS
    "-DLV_LVGL_H_INCLUDE_SIMPLE;-Wno-format;"
    )
