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

static void
changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("Value changed to %0.f\n", elm_spinner_value_get(obj));
}

static void
delay_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("Value delay changed to %0.f\n", elm_spinner_value_get(obj));
}

static Evas_Object*
create_spinner_view(Evas_Object *parent)
{
	Evas_Object *bx, *sp;

	bx = elm_box_add(parent);
	evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(bx);

	sp = elm_spinner_add(bx);
	evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, -1.0);
	evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_pack_end(bx, sp);
	evas_object_show(sp);
	evas_object_smart_callback_add(sp, "changed", changed_cb, NULL);
	evas_object_smart_callback_add(sp, "delay,changed", delay_changed_cb, NULL);

	sp = elm_spinner_add(bx);
	elm_spinner_editable_set(sp, EINA_FALSE);
	elm_spinner_label_format_set(sp, "%1.1f units");
	elm_spinner_step_set(sp, 1.5);
	elm_spinner_wrap_set(sp, EINA_TRUE);
	evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, -1.0);
	evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_pack_end(bx, sp);
	evas_object_show(sp);

	sp = elm_spinner_add(bx);
	elm_object_style_set(sp, "vertical");
	elm_spinner_interval_set(sp, 0.2);
	evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, -1.0);
	evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_pack_end(bx, sp);
	evas_object_show(sp);

	sp = elm_spinner_add(bx);
	elm_spinner_editable_set(sp, EINA_FALSE);
	elm_spinner_min_max_set(sp, 1, 12);
	elm_spinner_special_value_add(sp, 1, "January");
	elm_spinner_special_value_add(sp, 2, "February");
	elm_spinner_special_value_add(sp, 3, "March");
	elm_spinner_special_value_add(sp, 4, "April");
	elm_spinner_special_value_add(sp, 5, "May");
	elm_spinner_special_value_add(sp, 6, "June");
	elm_spinner_special_value_add(sp, 7, "July");
	elm_spinner_special_value_add(sp, 8, "August");
	elm_spinner_special_value_add(sp, 9, "September");
	elm_spinner_special_value_add(sp, 10, "October");
	elm_spinner_special_value_add(sp, 11, "November");
	elm_spinner_special_value_add(sp, 12, "December");
	evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, -1.0);
	evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_pack_end(bx, sp);
	evas_object_show(sp);

	evas_object_show(bx);

	return bx;
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

void
spinner_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout, *bg_layout;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	bg_layout = elm_layout_add(scroller);
	evas_object_size_hint_weight_set(bg_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(bg_layout, ELM_DEMO_EDJ, "white_bg_layout");

	layout = create_spinner_view(bg_layout);
	elm_object_part_content_set(bg_layout, "elm.swallow.content", layout);
	elm_object_content_set(scroller, bg_layout);

	elm_naviframe_item_push(nf, "Spinner", NULL, NULL, scroller, NULL);
}
