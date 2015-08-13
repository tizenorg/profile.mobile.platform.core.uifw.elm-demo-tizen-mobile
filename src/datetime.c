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

#include "main.h"
#include <langinfo.h>

#define DATE_FORMAT "%d/%b/%Y"
#define DATE_LAYOUT "date_layout"

#define TIME_12_FORMAT "%I:%M %p"
#define TIME_12_LAYOUT "time_layout"

#define TIME_24_FORMAT "%H:%M"
#define TIME_24_LAYOUT "time_layout_24hr"

typedef struct datetimedata {
	Evas_Object *nf;
	Evas_Object *datetime;
	Evas_Object *popup;
	Evas_Object *button1;
	Evas_Object *button2;
	Evas_Object *button3;
	struct tm saved_time;
} datetimedata_s;

static void
popup_cancel_btn_clicked_cb(void *data , Evas_Object *obj , void *event_info)
{
	datetimedata_s *dd = data;
	evas_object_del(dd->popup);
}

static void
popup_set_btn_clicked_cb(void *data , Evas_Object *obj , void *event_info)
{
	datetimedata_s *dd = data;
	char buff[200] = {0};
	const char *format;

	elm_datetime_value_get(dd->datetime, &dd->saved_time);
	format = elm_datetime_format_get(dd->datetime);

	if (!strcmp(format, "%d/%b/%Y")) {
		strftime(buff, 200, DATE_FORMAT, &dd->saved_time);
		elm_object_text_set(dd->button1, buff);
	}
	else if (!strcmp(format, "%d/%b/%Y %I:%M %p")) {
		strftime(buff, 200, TIME_12_FORMAT, &dd->saved_time);
		elm_object_text_set(dd->button2, buff);
	}
	else {
		strftime(buff, 200, TIME_24_FORMAT, &dd->saved_time);
		elm_object_text_set(dd->button3, buff);
	}

	evas_object_del(dd->popup);
}

static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	datetimedata_s *dd = data;
	free(dd);

	return EINA_TRUE;
}

static void
create_datetime_popup(datetimedata_s *dd)
{
	Evas_Object *set_btn, *cancel_btn;

	dd->popup = elm_popup_add(dd->nf);
	eext_object_event_callback_add(dd->popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(dd->popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_popup_align_set(dd->popup, ELM_NOTIFY_ALIGN_FILL, 0.5);

	cancel_btn = elm_button_add(dd->popup);
	elm_object_text_set(cancel_btn, "Cancel");
	elm_object_part_content_set(dd->popup, "button1", cancel_btn);
	evas_object_smart_callback_add(cancel_btn, "clicked", popup_cancel_btn_clicked_cb, dd);

	set_btn = elm_button_add(dd->popup);
	elm_object_text_set(set_btn, "Set");
	elm_object_part_content_set(dd->popup, "button2", set_btn);
	evas_object_smart_callback_add(set_btn, "clicked", popup_set_btn_clicked_cb, dd);
}

static void
launch_popup_cb(void *data , Evas_Object *obj , void *event_info)
{
	datetimedata_s *dd = data;
	char *format;
	create_datetime_popup(dd);
	Evas_Object *box = elm_box_add(dd->popup);

	dd->datetime = elm_datetime_add(dd->nf);

	format = evas_object_data_get(obj, "format");
	if (!strcmp(format, DATE_FORMAT)) {
		elm_object_part_text_set(dd->popup, "title,text", "Date Picker");
		elm_object_style_set(dd->datetime, DATE_LAYOUT);
		elm_datetime_format_set(dd->datetime, "%d/%b/%Y");
	}
	else if (!strcmp(format, TIME_12_FORMAT)) {
		elm_object_part_text_set(dd->popup, "title,text", "Time_12 Picker");
		elm_object_style_set(dd->datetime, TIME_12_LAYOUT);
		elm_datetime_format_set(dd->datetime, "%d/%b/%Y %I:%M %p");
	}
	else {
		elm_object_part_text_set(dd->popup, "title,text", "Time_24 Picker");
		elm_object_style_set(dd->datetime, TIME_24_LAYOUT);
		elm_datetime_format_set(dd->datetime, "%d/%b/%Y %H:%M");
	}

	elm_datetime_value_set(dd->datetime, &dd->saved_time);
	evas_object_size_hint_align_set(dd->datetime, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_show(dd->datetime);
	elm_box_pack_end(box, dd->datetime);
	elm_object_content_set(dd->popup, box);

	evas_object_show(dd->popup);
}

static Evas_Object *
create_button(datetimedata_s *dd, Evas_Object *parent, char *text, char *format)
{
	Evas_Object *layout, *button;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_1");

	button = elm_button_add(layout);
	elm_object_text_set(button, text);
	evas_object_show(button);
	evas_object_data_set(button, "format", format);
	evas_object_smart_callback_add(button, "clicked", launch_popup_cb, dd);

	elm_object_part_content_set(layout, "elm.swallow.content", button);
	evas_object_show(layout);
	elm_box_pack_end(parent, layout);

	return button;
}

void
datetime_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it;
	Evas_Object *box, *layout;

	datetimedata_s *dd = calloc(1, sizeof(datetimedata_s));
	dd->nf = ad->nf;

	time_t local_time = time(NULL);
	char buff[200] = {0};
	struct tm *time_info = localtime(&local_time);
	dd->saved_time = *time_info;

	layout = elm_layout_add(ad->nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	box = elm_box_add(layout);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, ELM_SCALE_SIZE(70));
	elm_object_part_content_set(layout, "elm.swallow.content", box);

	strftime(buff, 200, DATE_FORMAT, &dd->saved_time);
	dd->button1 = create_button(dd, box, buff, DATE_FORMAT);

	strftime(buff, 200, TIME_12_FORMAT, &dd->saved_time);
	dd->button2 = create_button(dd, box, buff, TIME_12_FORMAT);

	strftime(buff, 200, TIME_24_FORMAT, &dd->saved_time);
	dd->button3 = create_button(dd, box, buff, TIME_24_FORMAT);

	it = elm_naviframe_item_push(ad->nf, "DateTime", NULL, NULL, layout, NULL);
	elm_naviframe_item_pop_cb_set(it, naviframe_pop_cb, dd);
}
