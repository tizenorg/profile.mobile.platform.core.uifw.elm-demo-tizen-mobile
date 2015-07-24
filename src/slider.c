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

static Evas_Object *
create_slider(Evas_Object *parent, const char *style, Eina_Bool indicator, Eina_Bool horizontal)
{
	Evas_Object *slider;

	slider = elm_slider_add(parent);
	if (style) elm_object_style_set(slider, style);

	elm_slider_horizontal_set(slider, horizontal);

	if (indicator) {
		elm_slider_indicator_show_set(slider, EINA_TRUE);
		elm_slider_indicator_format_set(slider, "%1.0f");
	}

	elm_slider_min_max_set(slider, 0, 9);

	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(slider);

	return slider;
}

static Evas_Object
*create_vertical_content(Evas_Object* parent)
{
	Evas_Object *scroller;
	Evas_Object *box;
	Evas_Object *slider;
	Evas_Object *label;
	int idx = 0;

	//Scroller
	scroller = elm_scroller_add(parent);
	evas_object_show(scroller);

	//Box
	box = elm_box_add(scroller);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(box);
	elm_object_content_set(scroller, box);

	//1. Default Slider
	slider = create_slider(box, NULL, EINA_TRUE, EINA_FALSE);
	elm_slider_value_set(slider, 0);
	elm_box_pack_end(box, slider);

	//Default Slider, Disabled
	slider = create_slider(box, NULL, EINA_TRUE, EINA_FALSE);
	elm_object_disabled_set(slider, EINA_TRUE);
	elm_slider_value_set(slider, 0);
	elm_box_pack_end(box, slider);


	//2. Center Point Slider
	slider = create_slider(box, "center_point", EINA_TRUE, EINA_FALSE);
	elm_slider_value_set(slider, 3);
	elm_box_pack_end(box, slider);

	//Center Point Slider, Disabled
	slider = create_slider(box, "center_point", EINA_TRUE, EINA_FALSE);
	elm_object_disabled_set(slider, EINA_TRUE);
	elm_slider_value_set(slider, 3);
	elm_box_pack_end(box, slider);


	//3. No Indicator Slider
	slider = create_slider(box, NULL, EINA_FALSE, EINA_FALSE);
	elm_slider_value_set(slider, 4);
	elm_box_pack_end(box, slider);

	//No Indicator Slider, Center Point
	slider = create_slider(box, "center_point", EINA_FALSE, EINA_FALSE);
	elm_slider_value_set(slider, 4);
	elm_box_pack_end(box, slider);

	return scroller;
}

static Evas_Object *
create_horizontal_content(Evas_Object* parent)
{
	Evas_Object *scroller;
	Evas_Object *box;
	Evas_Object *slider;
	Evas_Object *label;
	int idx = 0;

	//Scroller
	scroller = elm_scroller_add(parent);
	evas_object_show(scroller);

	//Box
	box = elm_box_add(scroller);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(box);
	elm_object_content_set(scroller, box);


	//1. Default Slider
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(label, "default:");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	slider = create_slider(box, NULL, EINA_TRUE, EINA_TRUE);
	elm_slider_value_set(slider, 0);
	elm_box_pack_end(box, slider);

	//Default Slider, Disabled
	slider = create_slider(box, NULL, EINA_TRUE, EINA_TRUE);
	elm_object_disabled_set(slider, EINA_TRUE);
	elm_slider_value_set(slider, 0);
	elm_box_pack_end(box, slider);


	//2. Center Point Slider
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(label, "center_point:");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	slider = create_slider(box, "center_point", EINA_TRUE, EINA_TRUE);
	elm_slider_value_set(slider, 3);
	elm_box_pack_end(box, slider);

	//Center Point Slider, Disabled
	slider = create_slider(box, "center_point", EINA_TRUE, EINA_TRUE);
	elm_object_disabled_set(slider, EINA_TRUE);
	elm_slider_value_set(slider, 3);
	elm_box_pack_end(box, slider);

	//No Indicator Slider
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(label, "no indicator:");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	//No Indicator Slider, Default
	slider = create_slider(box, NULL, EINA_FALSE, EINA_TRUE);
	elm_slider_value_set(slider, 4);
	elm_box_pack_end(box, slider);

	//No Indicator Slider, Center Point
	slider = create_slider(box, "center_point", EINA_FALSE, EINA_TRUE);
	elm_slider_value_set(slider, 4);
	elm_box_pack_end(box, slider);


	//3. Warning Slider
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(label, "warning:");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	//Warning Slider, Default
	slider = create_slider(box, "warning", EINA_TRUE, EINA_TRUE);
	elm_slider_value_set(slider, 2);
	elm_box_pack_end(box, slider);

	//Warning Slider, No Indicator
	slider = create_slider(box, "warning", EINA_FALSE, EINA_TRUE);
	elm_slider_value_set(slider, 2);
	elm_box_pack_end(box, slider);

	//Warning Slider, Disabled
	slider = create_slider(box, "warning", EINA_TRUE, EINA_TRUE);
	elm_object_disabled_set(slider, EINA_TRUE);
	elm_slider_value_set(slider, 2);
	elm_box_pack_end(box, slider);

	return scroller;
}

void
slider_vertical_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *content;
	Evas_Object *nf = data;
	content = create_vertical_content(nf);
	elm_naviframe_item_push(nf, "Vertical Style", NULL, NULL, content, NULL);
}

void
slider_horizontal_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *content;
	Evas_Object *nf = data;
	content = create_horizontal_content(nf);
	elm_naviframe_item_push(nf, "Horizontal Style", NULL, NULL, content, NULL);
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

static Evas_Object*
create_list(Evas_Object *nf)
{
	Evas_Object *list;

	list = elm_list_add(nf);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);
	elm_list_item_append(list, "Horizontal Style", NULL, NULL, slider_horizontal_cb, nf);
	elm_list_item_append(list, "Vertical Style", NULL, NULL, slider_vertical_cb, nf);

	elm_list_go(list);

	return list;
}

void
slider_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *list;
	Evas_Object *nf = data;

	list = create_list(nf);
	elm_naviframe_item_push(nf, "Slider", NULL, NULL, list, NULL);
}
