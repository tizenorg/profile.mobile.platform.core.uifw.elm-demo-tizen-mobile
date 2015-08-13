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

#define NUM_OF_ITEMS 50

static char*
gl_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	static char *country_names[] = {
		"Algeria", "Andorra",
		"Argentina", "Australia", "Bahamas", "Bangladesh", "belgium", "Benin",
		"Bosnia", "Canada", "Chad", "Chile", "Cuba ", "Denmark",
		"Dominican Republic", "Egypt", "England", "Europa Island", "china",
		"Ethiopia", "Fiji", "Finland", "France", "Germany", "Ghana", "Greece",
		"Hong Kong", "Hungary", "India", "Iran", "Iraq", "Hafiz", "Italy",
		"Jordan", "kuwait", "Macau", "Mexico ", "Panama", "Poland", "Peru",
		"Russia", "Scotland", "Slovakia", "South Korea", "Sri Lanka", "Sweden",
		"Taiwan", "Tanzania", "Uganda", "Zimbabwe"
	};

	if (!strcmp(part, "elm.text")) {
		return strdup(country_names[(int)data % NUM_OF_ITEMS]);
	}

	return NULL;
}

static void
list_it_handler_v_cb(void *data, Evas_Object *obj, void *event_info)
{
	static Elm_Genlist_Item_Class itc;
	int index;
	Evas_Object *genlist;
	Evas_Object *nf = data;

	itc.item_style = "default";
	itc.func.text_get = gl_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	genlist = elm_genlist_add(nf);
	elm_object_style_set(genlist, "handler");

	for (index = 0; index < 4 * NUM_OF_ITEMS; index++) {
		elm_genlist_item_append(genlist, &itc, (void *)index, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
	}
	elm_naviframe_item_push(nf, "Vertical Handler", NULL, NULL, genlist, NULL);
}

static Evas_Object*
create_horz_handler_scroller(Evas_Object *parent)
{
	Evas_Object *img;
	Evas_Object *scroller;

	scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "handler");
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_FALSE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	img = elm_image_add(scroller);
	elm_image_file_set(img, ICON_DIR"/horz_scrollbar.png", NULL);
	elm_image_resizable_set(img, EINA_TRUE, EINA_FALSE);
	evas_object_size_hint_align_set(img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(img, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(img);

	elm_object_content_set(scroller, img);

	return scroller;
}

static void
list_it_handler_h_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout;
	Evas_Object *nf = data;

	layout = elm_layout_add(nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	scroller = create_horz_handler_scroller(layout);
	elm_object_part_content_set(layout, "elm.swallow.content", scroller);

	elm_naviframe_item_push(nf, "Horizontal Handler", NULL, NULL, layout, NULL);
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

static Evas_Object*
create_list(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_list_item_append(list, "Vertical Handler", NULL, NULL, list_it_handler_v_cb, parent);
	elm_list_item_append(list, "Horizontal Handler", NULL, NULL, list_it_handler_h_cb, parent);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);
	elm_list_go(list);

	return list;
}

void
handler_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *list;
	Evas_Object *nf = data;

	list = create_list(nf);
	elm_naviframe_item_push(nf, "Handler", NULL, NULL, list, NULL);
}
