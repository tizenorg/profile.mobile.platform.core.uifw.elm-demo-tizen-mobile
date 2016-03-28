/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
#include <app_manager.h>
#include <app_control.h>
#include "main.h"


static bool is_screen_reader_running()
{
	bool running = false;
	int ret = app_manager_is_running("org.tizen.screen-reader", &running);
	return (ret == APP_MANAGER_ERROR_NONE) && running;
}

static Eina_Bool screen_reader_on = EINA_FALSE;
void launch_reply_callback(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "reply has been delivered");
}

void
screen_reader_launch(void)
{
	if (!screen_reader_on)
		return;
	if (is_screen_reader_running()) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "screen reader already running");
		return;
	}
	app_control_h app_control;
	int ret = app_control_create(&app_control);
	dlog_print(DLOG_DEBUG, LOG_TAG, "app_control_create: %i", ret);

	if (ret == APP_CONTROL_ERROR_NONE) {
		ret = app_control_set_app_id(app_control, "org.tizen.screen-reader");
		dlog_print(DLOG_DEBUG, LOG_TAG, "app_control_set_app_id: %i", ret);
	}

	if (ret == APP_CONTROL_ERROR_NONE) {
		ret = app_control_send_launch_request(app_control, launch_reply_callback, NULL);
		dlog_print(DLOG_DEBUG, LOG_TAG, "app_control_send_launch_request: %i", ret);
	}

	screen_reader_on = ret == APP_CONTROL_ERROR_NONE;

	app_control_destroy(app_control);
}

void
screen_reader_terminate(void)
{
	app_context_h app_context = NULL;
	int res = app_manager_get_app_context("org.tizen.screen-reader", &app_context);

	if (res != APP_MANAGER_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Can't get screen reader app context - error code: %i", res);
		return;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "app_context: %p", app_context);
	res = app_manager_request_terminate_bg_app(app_context);

	if (res != APP_MANAGER_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Can't terminate screen reader app - error code: %i", res);
		return;
	}
}

static void
screen_reader_item_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *screen_reader_onoff_check = data;
	Eina_Bool check_state = elm_check_state_get(screen_reader_onoff_check);

	elm_check_state_set(screen_reader_onoff_check, !check_state);
	screen_reader_on = !check_state;

	if(screen_reader_on)
		screen_reader_launch();
	else
		screen_reader_terminate();
}

static void
check_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	screen_reader_on = elm_check_state_get(obj);

	if(screen_reader_on == EINA_TRUE)
		screen_reader_launch();
	else
		screen_reader_terminate();

}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

void
screen_reader_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *list;
	Evas_Object *screen_reader_onoff_check;

	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);
	screen_reader_on = is_screen_reader_running();
	screen_reader_onoff_check = elm_check_add(list);
	elm_object_style_set(screen_reader_onoff_check, "on&off");
	elm_check_state_set(screen_reader_onoff_check, screen_reader_on);
	evas_object_smart_callback_add(screen_reader_onoff_check, "changed", check_changed_cb, NULL);
	evas_object_propagate_events_set(screen_reader_onoff_check, EINA_FALSE);

	elm_list_item_append(list, "UI Descriptions", NULL, NULL, description_cb, nf);
	elm_list_item_append(list, "UI Reading order", NULL, NULL, reading_order_cb, nf);
	elm_list_item_append(list, "Custom Frame", NULL, NULL, custom_frame_cb, nf);

	elm_list_item_prepend(list, "Screen Reader (TTS)", NULL, screen_reader_onoff_check, screen_reader_item_cb,
							screen_reader_onoff_check);

	elm_list_go(list);

	elm_naviframe_item_push(nf, "Screen Reader", NULL, NULL, list, NULL);
}

