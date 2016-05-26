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
create_button_view(Evas_Object *parent)
{
        Evas_Object *map = elm_map_add(parent);
        evas_object_size_hint_align_set(map, -1, -1);
        evas_object_show(map);

	return map;
}

void
map_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout, *map;
	Evas_Object *nf = data;

	layout = elm_layout_add(nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	map = create_button_view(layout);
	elm_object_part_content_set(layout, "elm.swallow.content", map);

	elm_naviframe_item_push(nf, "Button", NULL, NULL, layout, NULL);
}
