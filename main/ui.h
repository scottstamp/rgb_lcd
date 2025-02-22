#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_lvgl_port.h"

// LVGL image declare
LV_IMG_DECLARE(esp_logo)

// LVGL fonts declare
LV_FONT_DECLARE(ui_font_montserrat_96)
LV_FONT_DECLARE(ui_font_montserrat_140)


// typedef struct _objects_t {
//     lv_obj_t *main;
//     lv_obj_t *versus;
//     lv_obj_t *obj0;
//     lv_obj_t *obj1;
//     lv_obj_t *obj2;
//     lv_obj_t *obj3;
//     lv_obj_t *obj4;
// } objects_t;