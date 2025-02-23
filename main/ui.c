#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_lvgl_port.h"

// LVGL image declare
LV_IMG_DECLARE(esp_logo)

// LVGL fonts declare
LV_FONT_DECLARE(ui_font_montserrat_96)
LV_FONT_DECLARE(ui_font_montserrat_140)

struct game_state
{
    int player_one_score;
    int player_two_score;
    int current_player;
};

struct game_state state = {
    .player_one_score = 301,
    .player_two_score = 301,
    .current_player = 1};

static lv_obj_t *lbl_player_one_score, *lbl_player_two_score, *ta_score_input, *lst_prev_scores;

static const char *kb_map[] = {
    "1", "2", "3", LV_SYMBOL_BACKSPACE, "\n",
    "4", "5", "6", " ", "\n",
    "7", "8", "9", " ", "\n",
    " ", "0", " ", LV_SYMBOL_OK, NULL};

static const lv_buttonmatrix_ctrl_t kb_ctrl[] = {
    4, 4, 4, 5,
    4, 4, 4, LV_BUTTONMATRIX_CTRL_HIDDEN | 5,
    4, 4, 4, LV_BUTTONMATRIX_CTRL_HIDDEN | 5,
    LV_BUTTONMATRIX_CTRL_HIDDEN | 4, 4, LV_BUTTONMATRIX_CTRL_HIDDEN | 4, 5};

static void ta_score_input_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb, ta);
        lv_textarea_set_cursor_pos(ta, LV_TEXTAREA_CURSOR_LAST);
        lv_obj_add_flag(lst_prev_scores, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    else if (code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(lst_prev_scores, LV_OBJ_FLAG_HIDDEN);
    }
}

static void kb_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    lv_obj_t *ta = lv_event_get_user_data(e);

    if (code == LV_EVENT_READY)
    {
        // confirm button pressed
    }
}

static void app_main_display(void)
{
    // lv_obj_t *scr = lv_scr_act();

    // lv_style_init(&style_modal);
    // lv_style_set_bg_color(&style_modal, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    lv_obj_t *obj = lv_scr_act();
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);

    lv_obj_t *kb = lv_keyboard_create(obj);
    lv_obj_set_style_pad_top(kb, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(kb, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_1);
    lv_obj_set_align(kb, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_size(kb, 474, 316);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_keyboard_set_textarea(kb, ta_score_input);
    lv_obj_add_event_cb(kb, kb_event_cb, LV_EVENT_ALL, ta_score_input);

    {
        lv_obj_t *parent_obj = obj;
        {
            lst_prev_scores = lv_list_create(parent_obj);
            // obj = lst_prev_scores;
            lv_obj_set_pos(lst_prev_scores, 677, 240);
            lv_obj_set_size(lst_prev_scores, 114, 230);
            lv_obj_set_style_bg_opa(lst_prev_scores, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(lst_prev_scores, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = lst_prev_scores;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 611, 64);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "114");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff868686), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 611, 64);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "45");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 613, -38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "22");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 611, 64);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "39");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 611, 64);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "36");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 30, 30);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "90");
            lv_obj_set_style_text_font(obj, &ui_font_montserrat_140, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, -30, 30);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "301");
            lv_obj_set_style_text_font(obj, &ui_font_montserrat_140, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff848484), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 30, 164);
            lv_obj_set_size(obj, 134, 76);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffcd0025), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "T20");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 177, 164);
            lv_obj_set_size(obj, 134, 76);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00b713), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "D15");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            ta_score_input = lv_textarea_create(parent_obj);
            lv_obj_add_event_cb(ta_score_input, ta_score_input_event_cb, LV_EVENT_ALL, kb);
            lv_obj_set_pos(ta_score_input, 30, 370);
            lv_obj_set_size(ta_score_input, 205, 95);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(ta_score_input, "0");
            lv_textarea_set_one_line(ta_score_input, true);
            lv_textarea_set_max_length(ta_score_input, 3);
            lv_textarea_set_password_mode(ta_score_input, false);
            lv_obj_clear_flag(ta_score_input, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_opa(ta_score_input, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ta_score_input, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(ta_score_input, &ui_font_montserrat_96, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        // {
        //     lv_obj_t *obj = lv_btn_create(parent_obj);
        //     lv_obj_set_pos(obj, 837, 176);
        //     lv_obj_set_size(obj, 90, 90);
        //     // lv_obj_add_event_cb(obj, action_go_home, LV_EVENT_PRESSED, (void *)0);
        //     {
        //         lv_obj_t *parent_obj = obj;
        //         {
        //             lv_obj_t *obj = lv_label_create(parent_obj);
        //             lv_obj_set_pos(obj, 0, 0);
        //             lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        //             lv_label_set_text(obj, "");
        //             lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        //             lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
        //         }
        //     }
        // }
    }
}