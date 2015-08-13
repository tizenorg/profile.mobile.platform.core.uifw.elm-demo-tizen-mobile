/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "main.h"

static Evas_Object *
create_colorselector(Evas_Object *parent)
{
	/* add color palette widget */
	Evas_Object *colorselector;
	Elm_Object_Item *it;
	const Eina_List *color_list;

	colorselector = elm_colorselector_add(parent);
	elm_colorselector_mode_set(colorselector, ELM_COLORSELECTOR_PALETTE);
	evas_object_size_hint_weight_set(colorselector, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(colorselector, 0, EVAS_HINT_FILL);
	evas_object_show(colorselector);

	color_list = elm_colorselector_palette_items_get(colorselector);
	it = eina_list_nth(color_list, 3);

	elm_object_item_signal_emit(it, "elm,state,selected", "elm");

	return colorselector;
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "dialogue");
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

void
colorselector_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *colorselector, *scroller, *layout;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	layout = elm_layout_add(scroller);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	colorselector = create_colorselector(layout);
	elm_object_part_content_set(layout, "elm.swallow.content", colorselector);
	elm_object_content_set(scroller, layout);

	elm_naviframe_item_push(nf, "Colorselector", NULL, NULL, scroller, NULL);
}
