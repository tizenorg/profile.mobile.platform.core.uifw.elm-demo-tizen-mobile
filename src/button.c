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
btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	int btn_num = (int)data;

	printf("clicked event on Button:%d\n", btn_num);
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

static Evas_Object*
create_button_view(Evas_Object *parent)
{
	Evas_Object *btn, *img, *box;

	box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, 5 * elm_config_scale_get());
	evas_object_show(box);

	/* icon_reorder style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "icon_reorder");
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)1);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
	/* icon_expand_add style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "icon_expand_add");
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)2);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
	/* icon_expand_delete style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "icon_expand_delete");
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)3);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
	/* default style */
	btn = elm_button_add(box);
	elm_object_text_set(btn, "default");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(150), ELM_SCALE_SIZE(58));
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)4);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
	/* btn_circle style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "circle");
	elm_object_text_set(btn, "circle twoline");
	img = elm_image_add(btn);
	elm_image_file_set(img, ICON_DIR"/core_icon_brightness.png", NULL);
	elm_image_resizable_set(img, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", img);
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)5);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
	/* bottom style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "bottom");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(150), ELM_SCALE_SIZE(58));
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)6);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* contacts style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "contacts");
	elm_object_text_set(btn, "contacts");
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)7);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	btn = elm_button_add(box);
	elm_object_style_set(btn, "option");
	evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)8);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	return box;
}

void
button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	layout = create_button_view(scroller);
	elm_object_content_set(scroller, layout);

	elm_naviframe_item_push(nf, "Normal Styles", NULL, NULL, scroller, NULL);
}
