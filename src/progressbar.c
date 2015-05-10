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

static char *process_type[] = {
	"List Process",
	"List Process with Text",
	"Pending List",
	"Pending List with Text",
	"Process_Large",
	"Process_Medium",
	"Process_Small"
};


static Eina_Bool
progress_timer_cb(void *data)
{
	double value = 0.0;
	Evas_Object *progressbar = data;

	value = elm_progressbar_value_get(progressbar);
	if (value == 1.0) value = 0.0;
	value = value + 0.01;
	elm_progressbar_value_set(progressbar, value);

	return ECORE_CALLBACK_RENEW;
}

static void
progressbar_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Ecore_Timer *timer = data;
	ecore_timer_del(timer);
}

static Evas_Object
*create_progressbar(Evas_Object *obj, int index)
{
	Evas_Object *progressbar;
	Ecore_Timer *progress_timer;

	if (index == 0) {
		progressbar = elm_progressbar_add(obj);
		elm_object_style_set(progressbar, "custom");
		elm_progressbar_horizontal_set(progressbar, EINA_TRUE);
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_value_set(progressbar, 0.0);
		progress_timer = ecore_timer_add(0.1, progress_timer_cb, progressbar);
		evas_object_event_callback_add(progressbar, EVAS_CALLBACK_DEL, progressbar_del_cb, progress_timer);
	} else if (index == 1) {
		progressbar = elm_progressbar_add(obj);
		elm_progressbar_horizontal_set(progressbar, EINA_TRUE);
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_value_set(progressbar, 0.0);
		elm_object_text_set(progressbar, "Right Top");
		elm_object_signal_emit(progressbar, "elm,units,show", "elm");
		elm_object_part_text_set(progressbar,"elm.bottom.text", "Left Bottom");
		progress_timer = ecore_timer_add(0.1, progress_timer_cb, progressbar);
		evas_object_event_callback_add(progressbar, EVAS_CALLBACK_DEL, progressbar_del_cb, progress_timer);
	} else if (index == 2) {
		progressbar = elm_progressbar_add(obj);
		elm_object_style_set(progressbar, "pending_custom");
		elm_progressbar_horizontal_set(progressbar, EINA_TRUE);
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
	} else if (index == 3) {
		progressbar = elm_progressbar_add(obj);
		elm_object_style_set(progressbar, "pending");
		elm_progressbar_horizontal_set(progressbar, EINA_TRUE);
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
		elm_object_text_set(progressbar, "Right Top");
		elm_object_signal_emit(progressbar, "elm,units,show", "elm");
		elm_object_part_text_set(progressbar,"elm.bottom.text", "Left Bottom");
		progress_timer = ecore_timer_add(0.1, progress_timer_cb, progressbar);
		evas_object_event_callback_add(progressbar, EVAS_CALLBACK_DEL, progressbar_del_cb, progress_timer);
	} else if (index == 4) {
		progressbar = elm_progressbar_add(obj);
		elm_object_style_set(progressbar, "process_large");
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
	} else if (index == 5) {
		progressbar = elm_progressbar_add(obj);
		elm_object_style_set(progressbar, "process_medium");
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
	} else {
		progressbar = elm_progressbar_add(obj);
		elm_object_style_set(progressbar, "process_small");
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
	}
	return progressbar;
}

static Evas_Object
*create_scroller(Evas_Object* parent)
{
	Evas_Object* scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

static Evas_Object
*create_box(Evas_Object *parent, Eina_Bool hor, double align_x, double align_y, double weight_x, double weight_y)
{
	Evas_Object *box;
	box = elm_box_add(parent);
	elm_box_horizontal_set(box, hor);
	evas_object_size_hint_weight_set(box, weight_x, weight_y);
	evas_object_size_hint_align_set(box, align_x, align_y);
	evas_object_show(box);
	return box;
}

static Evas_Object
*create_content(Evas_Object* parent)
{
	Evas_Object *progressbar;
	Evas_Object *main_box, *progress_box, *label;
	Evas_Object *scroller;
	int idx = 0;

	scroller = create_scroller(parent);

	main_box = create_box(scroller, EINA_TRUE, EVAS_HINT_FILL, EVAS_HINT_FILL, EVAS_HINT_EXPAND, 0.0);
	elm_box_homogeneous_set(main_box, EINA_FALSE);
	elm_object_content_set(scroller, main_box);
	elm_box_padding_set(main_box, 15 * elm_config_scale_get(), 15 * elm_config_scale_get());

	elm_box_pack_end(main_box, create_box(main_box, EINA_FALSE, 0.0, 0.0, 0.0, 0.0));

	progress_box = create_box(main_box, EINA_FALSE, EVAS_HINT_FILL, 0.0, EVAS_HINT_EXPAND, 0.0);
	elm_box_homogeneous_set(progress_box, EINA_FALSE);
	elm_box_padding_set(progress_box, 50 * elm_config_scale_get(), 50 * elm_config_scale_get());
	elm_box_pack_end(main_box, progress_box);

	elm_box_pack_end(main_box, create_box(main_box, EINA_FALSE, 0.0, 0.0, 0.0, 0.0));

	for (idx = 0; idx < 7; idx++) {
		label = elm_label_add(progress_box);
		evas_object_size_hint_align_set(label, 0.0, 0.5);
		elm_object_text_set(label, process_type[idx]);
		elm_box_pack_end(progress_box, label);
		evas_object_show(label);
		progressbar = create_progressbar(progress_box, idx);
		evas_object_show(progressbar);
		elm_box_pack_end(progress_box, progressbar);
	}
	return scroller;
}

void
progressbar_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *content;
	Evas_Object *nf = data;

	content = create_content(nf);
	elm_naviframe_item_push(nf, "Progressbar", NULL, NULL, content, NULL);
}

