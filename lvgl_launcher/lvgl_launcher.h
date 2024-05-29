/**
 * @file lvgl_launcher.h
 *
 */

#ifndef LVGL_LAUNCHER_H
#define LVGL_LAUNCHER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl/lvgl.h"

void lvgl_launcher(void);
static void draw_top(lv_obj_t *obj);
static void draw_main(lv_obj_t *obj);
static void draw_bottom(lv_obj_t *obj);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
