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

static void
hoversel_clicked_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
	dlog_print(DLOG_INFO, LOG_TAG, "Hover button is clicked and 'clicked' callback is called.\n");
}

static void
hoversel_selected_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                      void *event_info)
{
	const char *txt = elm_object_item_text_get(event_info);

	dlog_print(DLOG_INFO, LOG_TAG, "'selected' callback is called. (selected item : %s)\n", txt);
}

static void
hoversel_dismissed_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                       void *event_info EINA_UNUSED)
{
	dlog_print(DLOG_INFO, LOG_TAG, "'dismissed' callback is called.\n");
}

static Evas_Object*
create_hoversel_view(Evas_Object *parent)
{
	Evas_Object *box, *hoversel;

	/* Add box for base layout */
	box = elm_box_add(parent);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* Add Hoversel */
	hoversel = elm_hoversel_add(box);
	elm_hoversel_hover_parent_set(hoversel, parent);
	elm_object_text_set(hoversel, "Mobile");

	elm_hoversel_item_add(hoversel, "Mobile", NULL, ELM_ICON_NONE, NULL, NULL);
	elm_hoversel_item_add(hoversel, "Fax (HOME)", NULL, ELM_ICON_NONE, NULL, NULL);
	elm_hoversel_item_add(hoversel, "Fax (Office)", NULL, ELM_ICON_NONE, NULL, NULL);
	elm_hoversel_item_add(hoversel, "Home", NULL, ELM_ICON_NONE, NULL, NULL);
	elm_hoversel_item_add(hoversel, "Office", NULL, ELM_ICON_NONE, NULL, NULL);

	evas_object_size_hint_align_set(hoversel, 0.5, 0.5);
	evas_object_size_hint_weight_set(hoversel, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(hoversel);
	elm_box_pack_end(box, hoversel);

	evas_object_smart_callback_add(hoversel, "clicked", hoversel_clicked_cb, NULL);
	evas_object_smart_callback_add(hoversel, "selected", hoversel_selected_cb, NULL);
	evas_object_smart_callback_add(hoversel, "dismissed", hoversel_dismissed_cb, NULL);

	/* Add Hoversel expanding to screen width */
	hoversel = elm_hoversel_add(box);
	elm_hoversel_hover_parent_set(hoversel, parent);
	elm_object_text_set(hoversel, "Dropdown");

	elm_hoversel_item_add(hoversel, "List 01", NULL, ELM_ICON_NONE, NULL, NULL);
	elm_hoversel_item_add(hoversel, "List 02", NULL, ELM_ICON_NONE, NULL, NULL);
	elm_hoversel_item_add(hoversel, "List 03", NULL, ELM_ICON_NONE, NULL, NULL);

	evas_object_size_hint_align_set(hoversel, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(hoversel, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(hoversel);
	elm_box_pack_end(box, hoversel);

	evas_object_smart_callback_add(hoversel, "clicked", hoversel_clicked_cb, NULL);
	evas_object_smart_callback_add(hoversel, "selected", hoversel_selected_cb, NULL);
	evas_object_smart_callback_add(hoversel, "dismissed", hoversel_dismissed_cb, NULL);

	return box;
}

void
hoversel_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *content, *layout;
	Evas_Object *nf = data;

	layout = elm_layout_add(nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	content = create_hoversel_view(layout);
	elm_object_part_content_set(layout, "elm.swallow.content", content);

	elm_naviframe_item_push(nf, "Hoversel", NULL, NULL, layout, NULL);
}
