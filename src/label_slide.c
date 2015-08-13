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

typedef struct {
	Evas_Object *labels[6];
	Eina_Bool slide_go;
} label_data;

static void
btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	label_data *ld = data;
	int i;

	if (ld->slide_go)
	{
		for (i = 0; i < 6; i++)
		{
			elm_label_slide_mode_set(ld->labels[i], ELM_LABEL_SLIDE_MODE_NONE);
			elm_label_slide_go(ld->labels[i]);
		}

		elm_object_text_set(obj, "Start Sliding");
		ld->slide_go = EINA_FALSE;
	}
	else
	{
		for (i = 0; i < 6; i++)
		{
			elm_label_slide_mode_set(ld->labels[i], ELM_LABEL_SLIDE_MODE_AUTO);
			elm_label_slide_go(ld->labels[i]);
		}

		elm_object_text_set(obj, "Stop Sliding");
		ld->slide_go = EINA_TRUE;
	}
}

static Evas_Object*
create_labels(Evas_Object *parent)
{
	Evas_Object *layout, *label_long_5sec, *label_long_10sec, *label_short, *label_bounce, *label_rollShort, *label_rollLong, *btn;
	static label_data ld;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "label_slide_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	label_long_5sec = elm_label_add(layout);
	elm_object_style_set(label_long_5sec, "slide_long");
	elm_object_text_set(label_long_5sec, "This is a long text for sliding demo in elementary label.");
	elm_label_wrap_width_set(label_long_5sec, 100);
	elm_label_slide_duration_set(label_long_5sec, 5);
	elm_label_slide_mode_set(label_long_5sec, ELM_LABEL_SLIDE_MODE_ALWAYS);
	elm_object_part_content_set(layout, "swallow_label_1", label_long_5sec);

	ld.labels[0] = label_long_5sec;

	label_long_10sec = elm_label_add(layout);
	elm_object_style_set(label_long_10sec, "slide_long");
	elm_object_text_set(label_long_10sec, "This is a long text for sliding demo in elementary label.");
	elm_object_part_content_set(layout, "swallow_label_2", label_long_10sec);
	elm_label_wrap_width_set(label_long_10sec, 100);
	elm_label_slide_duration_set(label_long_10sec, 10);
	elm_label_slide_mode_set(label_long_10sec, ELM_LABEL_SLIDE_MODE_ALWAYS);

	ld.labels[1] = label_long_10sec;

	label_short = elm_label_add(layout);
	elm_object_style_set(label_short, "slide_short");
	elm_object_text_set(label_short, "This is a long text for sliding demo in elementary label.");
	elm_label_wrap_width_set(label_short, 100);
	elm_label_slide_duration_set(label_short, 5);
	elm_label_slide_mode_set(label_short, ELM_LABEL_SLIDE_MODE_ALWAYS);
	elm_object_part_content_set(layout, "swallow_label_3", label_short);

	ld.labels[2] = label_short;

	label_bounce = elm_label_add(layout);
	elm_object_style_set(label_bounce, "slide_bounce");
	elm_object_text_set(label_bounce, "This is a long text for sliding demo in elementary label.");
	elm_label_wrap_width_set(label_bounce, 100);
	elm_label_slide_duration_set(label_bounce, 3);
	elm_label_slide_mode_set(label_bounce, ELM_LABEL_SLIDE_MODE_ALWAYS);
	elm_object_part_content_set(layout, "swallow_label_4", label_bounce);

	ld.labels[3] = label_bounce;

	label_rollShort = elm_label_add(layout);
	elm_object_style_set(label_rollShort, "slide_roll");
	elm_object_text_set(label_rollShort, "Too short text!!");
	elm_label_wrap_width_set(label_rollShort, 100);
	elm_label_slide_duration_set(label_rollShort, 3);
	elm_label_slide_mode_set(label_rollShort, ELM_LABEL_SLIDE_MODE_ALWAYS);
	elm_object_part_content_set(layout, "swallow_label_5", label_rollShort);

	ld.labels[4] = label_rollShort;

	label_rollLong = elm_label_add(layout);
	elm_object_style_set(label_rollLong, "slide_roll");
	elm_object_text_set(label_rollLong, "This is a long text for slide-rolling demo in elementary label.");
	elm_label_wrap_width_set(label_rollLong, 100);
	elm_label_slide_mode_set(label_rollLong, ELM_LABEL_SLIDE_MODE_ALWAYS);
	elm_object_part_content_set(layout, "swallow_label_6", label_rollLong);

	ld.labels[5] = label_rollLong;

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Start Sliding");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, &ld);
	elm_object_part_content_set(layout, "swallow_btn", btn);

	return layout;
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

void label_slide_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout_inner, *layout;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	layout = elm_layout_add(scroller);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	layout_inner = create_labels(nf);
	elm_object_part_content_set(layout, "elm.swallow.content", layout_inner);
	elm_object_content_set(scroller, layout);

	elm_naviframe_item_push(nf, "Slide Text", NULL, NULL, scroller, NULL);
}
