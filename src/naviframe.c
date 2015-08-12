/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *		  http://www.apache.org/licenses/LICENSE-2.0
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
quit_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Elm_Object_Item *bottom_it = elm_naviframe_bottom_item_get(nf);

	/* Pop to menu view */
	elm_naviframe_item_pop_to(bottom_it);
}

static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	/* By returning FALSE, you can reject the popping the item */
	return EINA_TRUE;
}

static Evas_Object*
create_toolbar_more_btn(Evas_Object *parent, Evas_Smart_Cb func, void *data)
{
	Evas_Object *btn = elm_button_add(parent);
	if (btn == NULL) return NULL;
	elm_object_style_set(btn, "naviframe/more/default");
	evas_object_smart_callback_add(btn, "clicked", func, data);
	return btn;
}

static void
prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	elm_naviframe_item_pop(nf);
}

static Evas_Object*
create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb next_btn_clicked_cb)
{
	Evas_Object *grid, *box, *layout, *scroller, *btn, *button_layout;

	/* Scroller */
	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	/* Grid */
	grid = elm_grid_add(scroller);
	evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(grid);

	/* NoContent Layout */
	layout = elm_layout_add(grid);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	elm_object_part_text_set(layout, "elm.text", text);
	evas_object_show(layout);
	elm_grid_pack(grid, layout, 0, 0, 100, 100);

	/* Box */
	box = elm_box_add(grid);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_show(box);
	elm_grid_pack(grid, box, 0, 0, 100, 100);

	/* Previous Page Button */
	button_layout = elm_layout_add(box);
	elm_layout_file_set(button_layout, ELM_DEMO_EDJ, "button_layout_1");
	evas_object_size_hint_weight_set(button_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(button_layout, 0.5, 1);

	btn = elm_button_add(button_layout);
	elm_object_text_set(btn, "Prev");
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, parent);
	evas_object_show(btn);

	elm_object_part_content_set(button_layout, "elm.swallow.content", btn);
	evas_object_show(button_layout);
	elm_box_pack_end(box, button_layout);

	/* Next Page Button */
	button_layout = elm_layout_add(box);
	elm_layout_file_set(button_layout, ELM_DEMO_EDJ, "button_layout_1");
	evas_object_size_hint_weight_set(button_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(button_layout, 0.5, 1);

	btn = elm_button_add(button_layout);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, parent);
	evas_object_show(btn);

	elm_object_part_content_set(button_layout, "elm.swallow.content", btn);
	evas_object_show(button_layout);
	elm_box_pack_end(box, button_layout);

	elm_object_content_set(scroller, grid);

	return scroller;
}

static void
fourth_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_content(nf, "Naviframe Demo<br>Page 4", quit_cb);

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "TitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitle", NULL, NULL, content, NULL);

	/* Title Badge */
	elm_object_item_part_text_set(nf_it, "title_badge", "999+");

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, quit_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
third_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_content(nf, "Naviframe Demo<br>Page 3", fourth_page_cb);

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Title", NULL, NULL, content, NULL);

	/* Subtitle */
	elm_object_item_part_text_set(nf_it, "subtitle", "Subtitle");

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, fourth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
second_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_content(nf, "Naviframe Demo<br>Page 2", third_page_cb);

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Title Buttons", NULL, NULL, content, NULL);

	/* Title Cancel Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/title_left");
	elm_object_item_part_content_set(nf_it, "title_left_btn", btn);
	elm_object_text_set(btn, "CANCEL");
	/* Title Done Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/title_right");
	elm_object_item_part_content_set(nf_it, "title_right_btn", btn);
	elm_object_text_set(btn, "DONE");

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, third_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
first_page(Evas_Object *nf)
{
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_content(nf, "Naviframe Demo<br>Page 1", second_page_cb);

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Title", NULL, NULL, content, NULL);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, second_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);

	elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, nf);
}

void
naviframe_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	first_page(nf);
}
