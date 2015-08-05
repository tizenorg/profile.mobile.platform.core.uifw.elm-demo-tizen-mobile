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
create_custom_frame(Evas_Object *parent)
{
	Evas_Object *btn;
	Evas_Object *layout;
	Evas_Object *img;
	Evas_Object *label;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "custom_frame_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	label = elm_label_add(layout);
	elm_object_text_set(label, _("<font_size=33><align=center>Default frame</align></font_size>"));
	elm_object_part_content_set(layout, "button_name_lbl", label);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Test Name");
	elm_object_style_set(btn, "default");
	elm_object_part_content_set(layout, "button_name", btn);

	label = elm_label_add(layout);
	elm_object_text_set(label, _("<font_size=33><align=center>Button with custom_frame</align></font_size>"));
	elm_object_part_content_set(layout, "button_custom_frame_lbl", label);

	img = elm_image_add(layout);
	elm_image_file_set(img, ICON_DIR"/contacts_ic_circle_btn_call.png", NULL);
	evas_object_size_hint_aspect_set(img, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Test Name");
	elm_object_part_content_set(layout, "button_custom_frame", btn);
	elm_object_style_set(btn, "custom1");
	elm_object_part_content_set(btn, "icon", img);

	label = elm_label_add(layout);
	elm_object_text_set(label, _("<font_size=33><align=center>Button with custom_frame</align></font_size>"));
	elm_object_part_content_set(layout, "button_custom_frame_lbl2", label);
	img = elm_image_add(layout);
	elm_image_file_set(img, ICON_DIR"/contacts_ic_circle_btn_call.png", NULL);
	evas_object_size_hint_aspect_set(img, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Test Name");
	elm_object_part_content_set(layout, "button_custom_frame2", btn);
	elm_object_style_set(btn, "custom2");
	elm_object_part_content_set(btn, "icon", img);

	return layout;
}

void
custom_frame_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout;
	Evas_Object *nf = data;

	elm_theme_extension_add(NULL, ELM_DEMO_EDJ);
	layout = create_custom_frame(nf);
	elm_naviframe_item_push(nf, "Custom frame", NULL, NULL, layout, NULL);
}
