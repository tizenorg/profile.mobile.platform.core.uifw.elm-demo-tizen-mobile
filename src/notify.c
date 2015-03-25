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

static void
btn_show_notify_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *notify = data;
	evas_object_show(notify);
}

static void
btn_hide_notify_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *notify = data;
	evas_object_hide(notify);
}

static Evas_Object*
create_notify_top_timeout(Evas_Object *parent)
{
	Evas_Object *notify;
	Evas_Object *box;
	Evas_Object *label;

	/* Create notify (top-aligned / hide automatically) */
	notify = elm_notify_add(parent);
	elm_notify_align_set(notify, 0.5, 0.0);
	elm_notify_timeout_set(notify, 5.0);

	/* Create box for stacking notify message */
	box = elm_box_add(notify);
	evas_object_show(box);

	/* Create label for notify message */
	label = elm_label_add(box);
	evas_object_size_hint_min_set(label, ELM_SCALE_SIZE(480), 0);
	elm_label_line_wrap_set(label, ELM_WRAP_WORD);
	elm_label_wrap_width_set(label, ELM_SCALE_SIZE(480));
	elm_object_text_set(label, "<font align=center>This notification will hide automatically in 5 seconds.</font>");
	elm_box_pack_end(box, label);
	evas_object_show(label);

	elm_object_content_set(notify, box);

	return notify;
}

static Evas_Object*
create_notify_top_manual(Evas_Object *parent)
{
	Evas_Object *notify;
	Evas_Object *box;
	Evas_Object *label;
	Evas_Object *btn;

	/* Create notify (top-aligned / hide manually) */
	notify = elm_notify_add(parent);
	elm_notify_align_set(notify, 0.5, 0.0);
	elm_notify_timeout_set(notify, 0.0);

	/* Create box for stacking notify message and button vertically */
	box = elm_box_add(notify);
	elm_box_horizontal_set(box, EINA_FALSE);
	evas_object_show(box);

	/* Create label for notify message */
	label = elm_label_add(box);
	evas_object_size_hint_min_set(label, ELM_SCALE_SIZE(480), 0);
	elm_label_line_wrap_set(label, ELM_WRAP_WORD);
	elm_label_wrap_width_set(label, ELM_SCALE_SIZE(480));
	elm_object_text_set(label, "<font align=center>Click OK button to hide notification</center>");
	elm_box_pack_end(box, label);
	evas_object_show(label);

	/* Create button to hide notify */
	btn = elm_button_add(box);
	elm_object_text_set(btn, "OK");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(80), ELM_SCALE_SIZE(58));
	elm_box_pack_end(box, btn);
	evas_object_show(btn);
	evas_object_smart_callback_add(btn, "clicked", btn_hide_notify_cb, notify);

	elm_object_content_set(notify, box);

	return notify;
}

static Evas_Object*
create_notify_top_block(Evas_Object *parent)
{
	Evas_Object *notify;
	Evas_Object *box;
	Evas_Object *label;

	/* Create notify (top-aligned / hide automatically / block outside events) */
	notify = elm_notify_add(parent);
	elm_notify_align_set(notify, 0.5, 0.0);
	elm_notify_timeout_set(notify, 5.0);
	elm_notify_allow_events_set(notify, EINA_FALSE);

	/* Create box for stacking notify message */
	box = elm_box_add(notify);
	evas_object_show(box);

	/* Create label for notify message */
	label = elm_label_add(box);
	evas_object_size_hint_min_set(label, ELM_SCALE_SIZE(480), 0);
	elm_label_line_wrap_set(label, ELM_WRAP_WORD);
	elm_label_wrap_width_set(label, ELM_SCALE_SIZE(480));
	elm_object_text_set(label, "<font align=center>Outside events are blocked while notification shows.</center>");
	elm_box_pack_end(box, label);
	evas_object_show(label);

	elm_object_content_set(notify, box);

	return notify;
}

static Evas_Object*
create_notify_bottom_timeout(Evas_Object *parent)
{
	Evas_Object *notify;
	Evas_Object *box;
	Evas_Object *label;

	/* Create notify (bottom-aligned / hide automatically) */
	notify = elm_notify_add(parent);
	elm_notify_align_set(notify, 0.5, 1.0);
	elm_notify_timeout_set(notify, 5.0);

	/* Create box for stacking notify message */
	box = elm_box_add(notify);
	evas_object_show(box);

	/* Create label for notify message */
	label = elm_label_add(box);
	evas_object_size_hint_min_set(label, ELM_SCALE_SIZE(480), 0);
	elm_label_line_wrap_set(label, ELM_WRAP_WORD);
	elm_label_wrap_width_set(label, ELM_SCALE_SIZE(480));
	elm_object_text_set(label, "<font align=center>This notification shows at the bottom of the screen.</center>");
	elm_box_pack_end(box, label);
	evas_object_show(label);

	elm_object_content_set(notify, box);

	return notify;
}

void notify_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;

	Evas_Object *layout;
	Evas_Object *box;
	Evas_Object *btn;
	Evas_Object *notify;

	/* Create base layout for box and notify */
	layout = elm_layout_add(nf);
	elm_layout_theme_set(layout, "layout", "application", "default");
	evas_object_show(layout);

	/* Create box for stacking buttons */
	box = elm_box_add(layout);
	elm_box_horizontal_set(box, EINA_FALSE);
	elm_box_padding_set(box, 0, 20 * elm_config_scale_get());
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(layout, "elm.swallow.content", box);
	evas_object_show(box);

	/* Create notify (top-aligned / hide automatically) & Add button that show notify */
	notify = create_notify_top_timeout(layout);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "top / timeout");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(320), ELM_SCALE_SIZE(58));
	elm_box_pack_end(box, btn);
	evas_object_show(btn);
	evas_object_smart_callback_add(btn, "clicked", btn_show_notify_cb, notify);

	/* Create notify (top-aligned / hide manually) & Add button that show notify */
	notify = create_notify_top_manual(layout);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "top / manual");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(320), ELM_SCALE_SIZE(58));
	elm_box_pack_end(box, btn);
	evas_object_show(btn);
	evas_object_smart_callback_add(btn, "clicked", btn_show_notify_cb, notify);

	/* Create notify (top-aligned / block outside events) & Add button that show notify */
	notify = create_notify_top_block(layout);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "top / block");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(320), ELM_SCALE_SIZE(58));
	elm_box_pack_end(box, btn);
	evas_object_show(btn);
	evas_object_smart_callback_add(btn, "clicked", btn_show_notify_cb, notify);

	/* Create notify (bottom-aligned / hide automatically) & Add button that show notify */
	notify = create_notify_bottom_timeout(layout);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "bottom / timeout");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(320), ELM_SCALE_SIZE(58));
	elm_box_pack_end(box, btn);
	evas_object_show(btn);
	evas_object_smart_callback_add(btn, "clicked", btn_show_notify_cb, notify);

	/* Push layout as naviframe's item */
	elm_naviframe_item_push(nf, "Notify", NULL, NULL, layout, NULL);
}
