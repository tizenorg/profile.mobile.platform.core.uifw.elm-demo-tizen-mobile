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

static Evas_Object *
create_labels(Evas_Object *parent)
{
	Evas_Object *layout, *label, *label2, *label3, *label4, *label5;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "label_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	label = elm_label_add(layout);
	elm_object_part_content_set(layout, "label1", label);
	elm_object_text_set(label, _("<font_size=15><align=center>fontsize is set to 15</align></font_size>"));

	label2 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label2", label2);
	elm_object_text_set(label2, _("<font_size=20><align=center>fontsize is set to 20</align></font_size>"));

	label3 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label3", label3);
	elm_object_text_set(label3, _("<font_size=25><align=center>fontsize is set to 25</align></font_size>"));

	label4 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label4", label4);
	elm_object_text_set(label4, _("<font_size=30><align=center>fontsize is set to 30</align></font_size>"));

	label5 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label5", label5);
	elm_object_text_set(label5, _("<font_size=40><align=center>fontsize is set to 40</align></font_size>"));

	return layout;
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "effect");
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

void
label_text_styles_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout_inner;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);

	layout_inner = create_labels(nf);
	elm_object_content_set(scroller, layout_inner);

	elm_naviframe_item_push(nf, "Text Styles", NULL, NULL, scroller, NULL);
}
