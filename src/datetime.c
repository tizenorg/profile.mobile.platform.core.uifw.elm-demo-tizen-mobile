/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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

#define FORMAT "%d/%b/%Y"
#define LAYOUT "date_layout"

static void
_popup_cancel_btn_clicked_cb(void *data , Evas_Object *obj , void *event_info)
{
	appdata_s *ad = data;
	evas_object_del(ad->popup);
}

static void
_popup_set_btn_clicked_cb(void *data , Evas_Object *obj , void *event_info)
{
	appdata_s *ad = data;
	char buff[200] = {0};
	elm_datetime_value_get(ad->datetime, &ad->saved_time);
	strftime(buff, 200, FORMAT,&ad->saved_time);
	elm_object_text_set(ad->button, buff);
	evas_object_del(ad->popup);
}


static void
create_datetime_popup(appdata_s *ad)
{
	Evas_Object *set_btn, *cancel_btn;

	ad->popup = elm_popup_add(ad->nf);
	eext_object_event_callback_add(ad->popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(ad->popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->popup, EVAS_HINT_FILL, 0.5);

	cancel_btn = elm_button_add(ad->popup);
	elm_object_style_set(cancel_btn, "popup");
	elm_object_text_set(cancel_btn, "Cancel");
	elm_object_part_content_set(ad->popup, "button1", cancel_btn);
	evas_object_smart_callback_add(cancel_btn, "clicked", _popup_cancel_btn_clicked_cb, ad);

	set_btn = elm_button_add(ad->popup);
	elm_object_style_set(set_btn, "popup");
	elm_object_text_set(set_btn, "Set");
	elm_object_part_content_set(ad->popup, "button2", set_btn);
	evas_object_smart_callback_add(set_btn, "clicked", _popup_set_btn_clicked_cb, ad);
}

static void
_launch_popup_cb(void *data , Evas_Object *obj , void *event_info)
{
	appdata_s *ad = data;
	create_datetime_popup(ad);
	elm_object_part_text_set(ad->popup, "title,text", "Date Picker");
	Evas_Object *box = elm_box_add(ad->popup);

	ad->datetime = elm_datetime_add(ad->nf);
	elm_object_style_set(ad->datetime, LAYOUT);
	elm_datetime_value_set(ad->datetime, &ad->saved_time);
	elm_datetime_format_set(ad->datetime, FORMAT);
	evas_object_size_hint_align_set(ad->datetime, 0.5 , 0.5);

	evas_object_show(ad->datetime);
	elm_box_pack_end(box, ad->datetime);
	elm_object_content_set(ad->popup, box);

	evas_object_show(ad->popup);
}

void
datetime_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	ad->button = elm_button_add(ad->nf);
	elm_object_style_set(ad->button, "popup");
	time_t local_time = time(NULL);
	char buff[200] = {0};
	struct tm *time_info = localtime(&local_time);
	ad->saved_time = *time_info;
	ad->saved_time.tm_hour = 15;
	strftime(buff, 200,FORMAT,&ad->saved_time);

	elm_object_text_set(ad->button, buff);
	evas_object_smart_callback_add(ad->button, "clicked", _launch_popup_cb, ad);
	elm_naviframe_item_push(ad->nf, "DateTime", NULL, NULL, ad->button, NULL);
}
