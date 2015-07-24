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
entry_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("entry changed!\n");
}

static void
list_it_password_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *entry;
	Evas_Object *box;
	Evas_Object *scroller;
	Evas_Object *layout;
	Evas_Object *nf = data;

	scroller = elm_scroller_add(nf);

	box = elm_box_add(scroller);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
	elm_object_content_set(scroller, box);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "entry_layout");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	entry = elm_entry_add(box);
	elm_entry_password_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(entry, "changed", entry_changed_cb, NULL);
	elm_object_part_content_set(layout, "entry_part", entry);

	elm_box_pack_end(box, layout);
	evas_object_show(layout);

	elm_naviframe_item_push(nf, "Password Entry", NULL, NULL, scroller, NULL);
}

static void
list_it_multiline_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *entry;
	Evas_Object *layout;
	Evas_Object *scroller;
	Evas_Object *box;
	Evas_Object *nf = data;

	scroller = elm_scroller_add(nf);

	box = elm_box_add(scroller);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
	elm_object_content_set(scroller, box);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "entry_layout");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	entry = elm_entry_add(layout);
	eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
	elm_object_part_content_set(layout, "entry_part", entry);

	elm_box_pack_end(box, layout);
	evas_object_show(layout);

	elm_naviframe_item_push(nf, "Multiline Entry", NULL, NULL, scroller, NULL);
}

static void
entry_activated_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("enter key clicked!!\n");
}

static void
list_it_singleline_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *entry;
	Evas_Object *layout;
	Evas_Object *scroller;
	Evas_Object *box;
	Evas_Object *nf = data;

	scroller = elm_scroller_add(nf);

	box = elm_box_add(scroller);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
	elm_object_content_set(scroller, box);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "entry_layout");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	entry = elm_entry_add(layout);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(entry, "activated", entry_activated_cb, NULL);
	elm_object_part_content_set(layout, "entry_part", entry);

	elm_box_pack_end(box, layout);
	evas_object_show(layout);

	elm_naviframe_item_push(nf, "Singleline Entry", NULL, NULL, scroller, NULL);
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

void
entry_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *list;
	Evas_Object *nf = data;

	/* List */
	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	elm_list_item_append(list, "Multiline Entry", NULL, NULL, list_it_multiline_cb, nf);
	elm_list_item_append(list, "Password Entry", NULL, NULL, list_it_password_cb, nf);
	elm_list_item_append(list, "Singleline Entry", NULL, NULL, list_it_singleline_cb, nf);
	elm_list_go(list);

	elm_naviframe_item_push(nf, "Entry", NULL, NULL, list, NULL);
}
