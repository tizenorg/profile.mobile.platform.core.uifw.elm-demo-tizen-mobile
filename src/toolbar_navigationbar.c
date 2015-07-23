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
toolbar_it_cb(void *data, Evas_Object *obj, void *event_info);

static Evas_Object*
create_text_only_scrollable_tabbar(Evas_Object *parent)
{
	Evas_Object *obj;
	Elm_Object_Item *item[8];

	/* create toolbar */
	obj = elm_toolbar_add(parent);
	elm_object_style_set(obj, "navigationbar");
	elm_toolbar_shrink_mode_set(obj, ELM_TOOLBAR_SHRINK_SCROLL);
	elm_toolbar_transverse_expanded_set(obj, EINA_TRUE);
	elm_toolbar_align_set(obj, 0.0);
	elm_toolbar_homogeneous_set(obj, EINA_FALSE);

	item[0] = elm_toolbar_item_append(obj, NULL, "Main", toolbar_it_cb, parent);
	item[1] = elm_toolbar_item_append(obj, NULL, "Playlist", toolbar_it_cb, parent);
	item[2] = elm_toolbar_item_append(obj, NULL, "Artists list", toolbar_it_cb, parent);
	elm_object_item_disabled_set(item[2], EINA_TRUE);
	item[3] = elm_toolbar_item_append(obj, NULL, "Songs", toolbar_it_cb, parent);
	item[4] = elm_toolbar_item_append(obj, NULL, "Dialer for call", toolbar_it_cb, parent);
	item[5] = elm_toolbar_item_append(obj, NULL, "Playlist", toolbar_it_cb, parent);
	item[6] = elm_toolbar_item_append(obj, NULL, "Songs", toolbar_it_cb, parent);
	item[7] = elm_toolbar_item_append(obj, NULL, "Dialer for call", toolbar_it_cb, parent);

	elm_toolbar_select_mode_set(obj, ELM_OBJECT_SELECT_MODE_NONE);

	return obj;
}

static void
scrollable_style_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *tabbar;
	Elm_Object_Item *nf_it;
	Evas_Object *nf = data;

	nf_it = elm_naviframe_top_item_get(nf);
	elm_naviframe_item_style_set(nf_it, "tabbar");
	tabbar = create_text_only_scrollable_tabbar(nf);
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);
	elm_object_item_part_text_set(nf_it, NULL, "Multiple Items with Title");
}

static Evas_Object*
create_text_only_2_items_tabbar(Evas_Object *parent)
{
	Evas_Object *toolbar;

	/* create toolbar */
	toolbar = elm_toolbar_add(parent);
	elm_object_style_set(toolbar, "navigationbar");
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_SCROLL);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);
	elm_toolbar_align_set(toolbar, 0.0);
	elm_toolbar_homogeneous_set(toolbar, EINA_FALSE);
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_NONE);

	elm_toolbar_item_append(toolbar, NULL, "Main", toolbar_it_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Playlist", toolbar_it_cb, parent);

	return toolbar;
}

static Evas_Object*
create_text_only_3_items_tabbar(Evas_Object *parent)
{
	Evas_Object *toolbar;

	/* create toolbar */
	toolbar = elm_toolbar_add(parent);
	elm_object_style_set(toolbar, "navigationbar");
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_SCROLL);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);
	elm_toolbar_align_set(toolbar, 0.0);
	elm_toolbar_homogeneous_set(toolbar, EINA_FALSE);
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_NONE);

	elm_toolbar_item_append(toolbar, NULL, "Main", toolbar_it_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Playlist", toolbar_it_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Artists list", toolbar_it_cb, parent);

	return toolbar;
}

static Evas_Object*
create_text_only_4_items_tabbar(Evas_Object *parent)
{
	Evas_Object *toolbar;

	/* create toolbar */
	toolbar = elm_toolbar_add(parent);
	elm_object_style_set(toolbar, "navigationbar");
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_SCROLL);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);
	elm_toolbar_align_set(toolbar, 0.0);
	elm_toolbar_homogeneous_set(toolbar, EINA_FALSE);
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_NONE);

	elm_toolbar_item_append(toolbar, NULL, "Main", toolbar_it_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Playlist", toolbar_it_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Artists list", toolbar_it_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Composers", toolbar_it_cb, parent);

	return toolbar;
}

static void
toolbar_2_items_text_style_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *tabbar;
	Elm_Object_Item *nf_it;
	Evas_Object *nf = data;

	nf_it = elm_naviframe_top_item_get(nf);
	elm_naviframe_item_style_set(nf_it, "tabbar");
	tabbar = create_text_only_2_items_tabbar(nf);
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	elm_object_item_part_text_set(nf_it, NULL, "2 Items with Title");
}

static void
toolbar_3_items_text_style_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *tabbar;
	Elm_Object_Item *nf_it;
	Evas_Object *nf = data;

	nf_it = elm_naviframe_top_item_get(nf);
	elm_naviframe_item_style_set(nf_it, "tabbar");
	tabbar = create_text_only_3_items_tabbar(nf);
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	elm_object_item_part_text_set(nf_it, NULL, "3 Items with Title");
}

static void
toolbar_4_items_text_style_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *tabbar;
	Elm_Object_Item *nf_it;
	Evas_Object *nf = data;

	nf_it = elm_naviframe_top_item_get(nf);
	elm_naviframe_item_style_set(nf_it, "tabbar");
	tabbar = create_text_only_4_items_tabbar(nf);
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	elm_object_item_part_text_set(nf_it, NULL, "4 Items with Title");
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

static Evas_Object *
create_dialer_list(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_list_item_append(list, "Aquila", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Pantheon", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Kessler", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Neptune", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Aqua", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Beat", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "NBeat", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Tizen", NULL, NULL, NULL, NULL);

	elm_list_go(list);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	evas_object_show(list);

	return list;
}

static Evas_Object *
create_song_list(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_list_item_append(list, "Eina", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Evas", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Ecore", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Elementary", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Edje", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Eet", NULL, NULL, NULL, NULL);

	elm_list_go(list);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	evas_object_show(list);

	return list;
}

static Evas_Object *
create_artists_list(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_list_item_append(list, "Tab Bar", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Navigation Bar", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Slider", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Genlist", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Tool Bar", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Color Picker", NULL, NULL, NULL, NULL);

	elm_list_go(list);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	evas_object_show(list);

	return list;
}

static Evas_Object *
create_play_list(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_list_item_append(list, "Music", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Message", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Call", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Memo", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Alarm", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "SNS", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Email", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Worldclock", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Conventer", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Stopwatch", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Calculator", NULL, NULL, NULL, NULL);

	elm_list_go(list);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	evas_object_show(list);

	return list;
}

static Evas_Object *
create_main_list(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_list_item_append(list, "2 Items with Title", NULL, NULL, toolbar_2_items_text_style_cb, parent);
	elm_list_item_append(list, "3 Items with Title", NULL, NULL, toolbar_3_items_text_style_cb, parent);
	elm_list_item_append(list, "4 Items with Title", NULL, NULL, toolbar_4_items_text_style_cb, parent);
	elm_list_item_append(list, "Multiple Items with Title", NULL, NULL, scrollable_style_cb, parent);

	elm_list_go(list);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	evas_object_show(list);

	return list;
}

/* Change View */
static void
toolbar_it_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *sub_view;
	Elm_Object_Item *it;
	const char *str = NULL;

	it = event_info;

	str = elm_object_item_text_get(it);

	if (str == NULL || !strcmp(str, "Main")) {
		sub_view = create_main_list(nf);
	} else if (!strcmp(str, "Playlist")) {
		sub_view = create_play_list(nf);
	} else if (!strcmp(str, "Artists list")) {
		sub_view = create_artists_list(nf);
	} else if (!strcmp(str, "Songs")) {
		sub_view = create_song_list(nf);
	} else if (!strcmp(str, "Dialer")) {
		sub_view = create_dialer_list(nf);
	} else {
		sub_view = create_main_list(nf);
	}

	elm_object_content_set(nf, sub_view);
}

void
toolbar_navigation_style_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *tabbar, *sub_view;
	Evas_Object *nf = data;
	Elm_Object_Item *nf_it;

	nf_it = elm_naviframe_item_push(nf, "2 Items with Title", NULL, NULL, NULL, "tabbar");
	tabbar = create_text_only_2_items_tabbar(nf);
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);
	sub_view = create_main_list(nf);
	elm_object_item_part_content_set(nf_it, NULL, sub_view);
}
