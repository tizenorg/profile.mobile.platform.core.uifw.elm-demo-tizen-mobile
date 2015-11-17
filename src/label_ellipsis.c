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

static Evas_Object*
create_labels(Evas_Object *parent)
{
	Evas_Object *layout, *label, *label2, *label3, *label4, *label5;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "label_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	label = elm_label_add(layout);
	elm_object_part_content_set(layout, "label1", label);
	elm_object_text_set(label, _("<font_size=24>If the string length exceeds the width</font_size>"));
	elm_label_ellipsis_set(label, EINA_TRUE);
	elm_label_wrap_width_set(label, 300);

	label2 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label2", label2);
	elm_object_text_set(label2, _("<font_size=24>If the string length exceeds the width of the</font_size>"));
	elm_label_ellipsis_set(label2, EINA_TRUE);
	elm_label_wrap_width_set(label2, 300);

	label3 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label3", label3);
	elm_object_text_set(label3, _("<font_size=24>If the string length exceeds the width of the widget, then the string will be ellipsised by label. but it's a exprimental api and very slow function.</font_size>"));
	elm_label_wrap_width_set(label3, 300);
	elm_label_ellipsis_set(label3, EINA_TRUE);

	label4 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label4", label4);
	elm_object_text_set(label4, _("<font_size=24>If the string length exceeds the width of the widget, then the string will be ellipsised by label. but it's a exprimental api and very slow function.</font_size>"));
	elm_label_wrap_width_set(label4, 300);
	elm_label_ellipsis_set(label4, EINA_TRUE);

	label5 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label5", label5);
	elm_object_text_set(label5, _("If the string length exceeds the width of the widget, then the string will be ellipsised by label. However, it's a exprimental api and very slow function. Ellipsis feature supports multiline texts. Programmers should not misuse multiline ellipsis. It's slow a function."));
	elm_label_wrap_width_set(label5, 300);
	elm_label_ellipsis_set(label5, EINA_TRUE);

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

void label_ellipsis_cb(void *data, Evas_Object *obj, void *event_info)
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

	elm_naviframe_item_push(nf, "Ellipsis", NULL, NULL, scroller, NULL);
}
