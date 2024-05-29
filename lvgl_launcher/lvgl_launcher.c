#include "lvgl_launcher.h"
#include LV_THEME_DEFAULT_INCLUDE

void lvgl_launcher(void)
{
    // 绘制背景图
    //  LV_IMG_DECLARE(background);
    //  lv_obj_t *background_img = lv_img_create(lv_scr_act(),NULL);
    //  lv_img_set_src(background_img, &background);
    //  lv_obj_align(background_img, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

    LV_IMG_DECLARE(logo);
    lv_obj_t *logo_img = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(logo_img, &logo);
    lv_obj_align(logo_img, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 30, 50);

    lv_obj_t *obj_top = lv_obj_create(lv_scr_act(), NULL);
    static lv_style_t style_top;
    lv_style_init(&style_top);
    lv_style_set_bg_color(&style_top, LV_STATE_DEFAULT, lv_color_hex(0x444444));
    lv_style_set_border_width(&style_top, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&style_top, LV_STATE_DEFAULT, 0);
    lv_obj_set_size(obj_top, 1280, 40);
    lv_obj_add_style(obj_top, LV_OBJ_PART_MAIN, &style_top);
    lv_obj_align(obj_top, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 0);
    draw_top(obj_top);

    static lv_style_t style_main;
    lv_style_init(&style_main);
    lv_style_set_border_width(&style_main, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&style_main, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&style_main, LV_STATE_DEFAULT, LV_OPA_0);
    lv_obj_t *obj_main = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(obj_main, 1280, 520);
    lv_obj_add_style(obj_main, LV_OBJ_PART_MAIN, &style_main);
    lv_obj_align(obj_main, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 40);

    /*Create a Tab view object*/
    lv_obj_t *tabview;
    tabview = lv_tabview_create(obj_main, NULL);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled)*/
    lv_tabview_add_tab(tabview, "Tab 1");
    lv_tabview_add_tab(tabview, "Tab 2");
    lv_tabview_add_tab(tabview, "Tab 3");

    /*Hide the buttons of the Tab view*/
    // lv_tabview_set_btns_pos(tabview, LV_TABVIEW_TAB_POS_TOP);

    static lv_style_t style_bottom;
    lv_style_init(&style_bottom);
    lv_style_set_border_width(&style_bottom, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&style_bottom, LV_STATE_DEFAULT, 15);
    lv_style_set_bg_opa(&style_bottom, LV_STATE_DEFAULT, LV_OPA_50);
    lv_obj_t *obj_bottom = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(obj_bottom, 700, 140);
    lv_obj_add_style(obj_bottom, LV_OBJ_PART_MAIN, &style_bottom);
    lv_obj_align(obj_bottom, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, -20);

    //draw_bottom(obj_bottom);
}

static void draw_top(lv_obj_t *obj)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    lv_style_set_text_color(&style, LV_STATE_DEFAULT, lv_color_hex(0xffffff));

    // 绘制时间
    lv_obj_t *time_label = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(time_label, LV_OBJ_PART_MAIN, &style);
    lv_label_set_text(time_label, "2024/05/27 Mon 18:00");
    lv_obj_align(time_label, obj, LV_ALIGN_CENTER, 0, 0);

    // 绘制地区天气
    lv_obj_t *whether_label = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(whether_label, LV_OBJ_PART_MAIN, &style);
    lv_label_set_text(whether_label, "Jiangxia District\nWuhan City");
    lv_obj_align(whether_label, obj, LV_ALIGN_IN_LEFT_MID, 0, 0);

    // 绘制WIFI、蓝牙等设置按钮
    LV_IMG_DECLARE(shutdown);
    LV_IMG_DECLARE(Bluetooth);
    LV_IMG_DECLARE(Bluetooth_disconnect);
    LV_IMG_DECLARE(WIFI);
    LV_IMG_DECLARE(WIFI_disconnect);

    lv_obj_t *shutdown_imgbtn = lv_imgbtn_create(obj, NULL);
    lv_imgbtn_set_src(shutdown_imgbtn, LV_BTN_STATE_PRESSED, &shutdown);
    lv_imgbtn_set_src(shutdown_imgbtn, LV_BTN_STATE_RELEASED, &shutdown);
    lv_imgbtn_set_src(shutdown_imgbtn, LV_BTN_STATE_DISABLED, &shutdown);
    lv_obj_align(shutdown_imgbtn, obj, LV_ALIGN_IN_RIGHT_MID, -10, 0);

    lv_obj_t *bluetooth_imgbtn = lv_imgbtn_create(obj, NULL);
    lv_imgbtn_set_src(bluetooth_imgbtn, LV_BTN_STATE_PRESSED, &Bluetooth);
    lv_imgbtn_set_src(bluetooth_imgbtn, LV_BTN_STATE_RELEASED, &Bluetooth);
    lv_imgbtn_set_src(bluetooth_imgbtn, LV_BTN_STATE_DISABLED, &Bluetooth);
    lv_obj_align(bluetooth_imgbtn, shutdown_imgbtn, LV_ALIGN_OUT_LEFT_MID, -10, 0);
    
    
    lv_obj_t *wifi_imgbtn = lv_imgbtn_create(obj, NULL);
    lv_imgbtn_set_src(wifi_imgbtn, LV_BTN_STATE_PRESSED, &WIFI);
    lv_imgbtn_set_src(wifi_imgbtn, LV_BTN_STATE_RELEASED, &WIFI);
    lv_imgbtn_set_src(wifi_imgbtn, LV_BTN_STATE_DISABLED, &WIFI);
    lv_obj_align(wifi_imgbtn, bluetooth_imgbtn, LV_ALIGN_OUT_LEFT_MID, -10, 0);
}

static void draw_main(lv_obj_t *obj)
{
}

static void draw_bottom(lv_obj_t *obj)
{
    LV_IMG_DECLARE(settings);
    lv_obj_t *settings_imgbtn = lv_imgbtn_create(obj, NULL);
    lv_imgbtn_set_src(settings_imgbtn, LV_BTN_STATE_PRESSED, &settings);
    lv_imgbtn_set_src(settings_imgbtn, LV_BTN_STATE_RELEASED, &settings);
    lv_imgbtn_set_src(settings_imgbtn, LV_BTN_STATE_DISABLED, &settings);
    lv_obj_align(settings_imgbtn, obj, LV_ALIGN_IN_LEFT_MID, 20, 0);

    // lv_obj_t *file_imgbtn = lv_imgbtn_create(obj,NULL);
    // lv_imgbtn_set_src(file_imgbtn, LV_BTN_STATE_PRESSED, &settings);
    // lv_imgbtn_set_src(file_imgbtn, LV_BTN_STATE_RELEASED, &settings);
    // lv_imgbtn_set_src(file_imgbtn, LV_BTN_STATE_DISABLED, &settings);
    // lv_obj_align(file_imgbtn, obj, LV_ALIGN_IN_LEFT_MID, 20, 0);
}
