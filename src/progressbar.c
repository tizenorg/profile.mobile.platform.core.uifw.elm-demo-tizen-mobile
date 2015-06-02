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

static Evas_Object *
create_pending_progressbar(Evas_Object *parent)
{
	Evas_Object *progressbar;
	Ecore_Timer *progress_timer;

	progressbar = elm_progressbar_add(parent);
	elm_object_style_set(progressbar, "pending");
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	evas_object_show(progressbar);

	elm_object_part_text_set(progressbar, "elm.text.top.left", "Lorem");
	elm_object_part_text_set(progressbar, "elm.text.top.right", "Lorem");
	elm_object_part_text_set(progressbar, "elm.text.bottom.left", "Lorem");
	elm_object_part_text_set(progressbar, "elm.text.bottom.right", "Lorem");

	return progressbar;
}

static Evas_Object *
create_process_progressbar(Evas_Object *parent, const char *style)
{
	Evas_Object *progressbar;

	progressbar = elm_progressbar_add(parent);

	elm_object_style_set(progressbar, style);
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	evas_object_show(progressbar);

	return progressbar;
}

static Evas_Object *
create_default_progressbar(Evas_Object *parent)
{
	Evas_Object *progressbar;
	Ecore_Timer *progress_timer;

	progressbar = elm_progressbar_add(parent);
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_value_set(progressbar, 0.0);
	progress_timer = ecore_timer_add(0.1, progress_timer_cb, progressbar);
	evas_object_event_callback_add(progressbar, EVAS_CALLBACK_DEL, progressbar_del_cb, progress_timer);
	evas_object_show(progressbar);

	elm_object_part_text_set(progressbar, "elm.text.top.left", "Lorem");
	elm_object_part_text_set(progressbar, "elm.text.top.right", "Lorem");
	elm_object_part_text_set(progressbar, "elm.text.bottom.left", "Lorem");
	elm_object_part_text_set(progressbar, "elm.text.bottom.right", "Lorem");

	return progressbar;
}

static Evas_Object *
create_label(Evas_Object *parent, const char *text)
{
   Evas_Object *label;

	label = elm_label_add(parent);
	elm_object_text_set(label, text);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	evas_object_show(label);

	return label;
}

static Evas_Object
*create_content(Evas_Object* parent)
{
	Evas_Object *scroller;
	Evas_Object *box;
	Evas_Object *label;
	Evas_Object *progressbar;

	/* Scroller */
	scroller = elm_scroller_add(parent);
	evas_object_show(scroller);

	/* Box */
	box = elm_box_add(scroller);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(box);

	elm_object_content_set(scroller, box);

	/* Default Progressbar */
	label = create_label(box, "default:");
	elm_box_pack_end(box, label);
	progressbar = create_default_progressbar(box);
	elm_box_pack_end(box, progressbar);

	/* Pending Progressbar */
	label = create_label(box, "pending:");
	elm_box_pack_end(box, label);
	progressbar = create_pending_progressbar(box);
	elm_box_pack_end(box, progressbar);

	/* Process Large */
	label = create_label(box, "process_large:");
	elm_box_pack_end(box, label);
	progressbar = create_process_progressbar(box, "process_large");
	elm_box_pack_end(box, progressbar);

	/* Process Medium */
	label = create_label(box, "process_medium:");
	elm_box_pack_end(box, label);
	progressbar = create_process_progressbar(box, "process_medium");
	elm_box_pack_end(box, progressbar);

	/* Process Small */
	label = create_label(box, "process_small:");
	elm_box_pack_end(box, label);
	progressbar = create_process_progressbar(box, "process_small");
	elm_box_pack_end(box, progressbar);

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

