/*
 * screen.h
 *
 *  Created on: Jan 12, 2021
 *      Author: David		Original work by Jose (PTDreamer), 2017
 */

#ifndef GRAPHICS_GUI_SCREEN_H_
#define GRAPHICS_GUI_SCREEN_H_

#include "main.h"
#include "iron.h"
#include "pid.h"
#include "settings.h"
#include "ssd1306.h"

#include "widgets.h"
#include "adc_global.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include "tempsensors.h"
#include "voltagesensors.h"

enum {
    screen_boot,
		screen_main,
      screen_settingsmenu,
          screen_iron,
          screen_system,
              screen_reset,
                screen_reset_confirmation,
          screen_edit_iron_tips,
            screen_edit_tip_name,
            screen_edit_tip_settings,
          screen_edit_calibration,
              screen_edit_calibration_start,
              screen_edit_calibration_adjust,
              screen_edit_calibration_input,
          screen_debug,
              screen_debug2,
		};

typedef struct screen_t screen_t;
typedef enum{ screenRefresh_idle=0, screenRefresh_eraseNow, screenRefresh_alreadyErased} screenRefreshType;
struct screen_t
{
	struct screen_t *next_screen;
	widget_t *widgets;
	widget_t *current_widget;
	bool enabled;
	screenRefreshType refresh;
	int (*processInput)(struct screen_t *scr, RE_Rotation_t input, RE_State_t *);
	void (*update)(screen_t *scr);
	void (*draw)(screen_t *scr);
	void (*onExit)(screen_t *scr);
	void (*onEnter)(screen_t *scr);
	uint8_t index;
	void (*init)(screen_t *scr);
};



widget_t *screen_tabToWidget(screen_t * scr, uint8_t tab);
void screen_addWidget(widget_t *widget, screen_t *scr);
void default_screenDraw(screen_t *scr);
int default_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *);
void default_screenUpdate(screen_t *scr);
void screen_setDefaults(screen_t *scr);
void default_init(screen_t *scr);

#endif /* GRAPHICS_GUI_SCREEN_H_ */
