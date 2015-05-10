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

static char *slider_type[] = {
	"   Icon-Slider",
	"   Slider Normal Style",
	"   Icon-Center Slider",
	"   Center Slider",
	NULL
};

static void
create_icon(Evas_Object *slider)
{
	Evas_Object *img;
	img = elm_image_add(slider);
	elm_image_file_set(img, ICON_DIR"/core_icon_brightness.png", NULL);
	evas_object_size_hint_aspect_set(img, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_object_part_content_set(slider, "elm.swallow.icon", img);
	evas_object_show(img);
}

static Evas_Object
*create_slider(Evas_Object *parent, Eina_Bool is_center_point)
{
	Evas_Object *slider;

	slider = elm_slider_add(parent);
	elm_slider_indicator_show_set(slider, EINA_TRUE);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_slider_indicator_format_set(slider, "%1.0f");
	elm_slider_min_max_set(slider, 0, 9);
	if (is_center_point)
		elm_object_style_set(slider, "center_point");

	return slider;
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
*create_box(Evas_Object *parent, Eina_Bool hor)
{
	Evas_Object *box;
	box = elm_box_add(parent);
	elm_box_horizontal_set(box, hor);
	if (hor) {
		evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	} else {
		evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
		evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	}
	evas_object_show(box);

	return box;
}

static Evas_Object
*create_content(Evas_Object* parent, Eina_Bool is_horizontal)
{
	Evas_Object *slider;
	Evas_Object *scroller;
	Evas_Object *main_box, *label;
	int idx = 0;
	int no_slider = 0;

	scroller = create_scroller(parent);

	main_box = create_box(scroller, !is_horizontal);
	elm_box_homogeneous_set(main_box, EINA_FALSE);
	elm_box_padding_set(main_box, 30 * elm_config_scale_get(), 30 * elm_config_scale_get());
	elm_object_content_set(scroller, main_box);
	if (is_horizontal) {
		no_slider = 4;
		for (idx = 0; idx < no_slider; idx++) {
			label = elm_label_add(main_box);
			evas_object_size_hint_align_set(label, 0.0, 0.5);
			elm_object_text_set(label, slider_type[idx]);
			elm_box_pack_end(main_box, label);
			evas_object_show(label);
			if (idx == 2 || idx == 3)
				slider = create_slider(main_box, EINA_TRUE);
			else
				slider = create_slider(main_box, EINA_FALSE);
			elm_slider_horizontal_set(slider, is_horizontal);
			elm_slider_value_set(slider, (idx + 1));
			if (idx % 2 == 0)
				create_icon(slider);
			evas_object_show(slider);
			elm_box_pack_end(main_box, slider);
		}
	} else {
		no_slider = 2;
		for (idx = 0; idx < no_slider; idx++) {
			if (idx % 2 == 0)
				slider = create_slider(main_box, EINA_FALSE);
			else
				slider = create_slider(main_box, EINA_TRUE);
			elm_slider_horizontal_set(slider, is_horizontal);
			elm_slider_value_set(slider, 1);
			evas_object_show(slider);
			elm_box_pack_end(main_box, slider);
		}
	}

	return scroller;
}

void
slider_vertical_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *content;
	Evas_Object *nf = data;
	content = create_content(nf, EINA_FALSE);
	elm_naviframe_item_push(nf, "Vertical Style", NULL, NULL, content, NULL);
}

void
slider_horizontal_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *content;
	Evas_Object *nf = data;
	content = create_content(nf, EINA_TRUE);
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
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
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
