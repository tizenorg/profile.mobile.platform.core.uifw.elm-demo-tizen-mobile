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

static Evas_Object *
create_nocontents(Evas_Object *parent)
{
	Evas_Object  *nocontents;

	/* Create elm_layout and set its style as nocontents/text */
	nocontents = elm_layout_add(parent);
	elm_layout_theme_set(nocontents, "layout", "nocontents", "default");
	evas_object_size_hint_weight_set(nocontents, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(nocontents, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_text_set(nocontents, "elm.text", "No Items");
	elm_object_part_text_set(nocontents, "elm.help.text", "No Contents help text. This part is for hints and useful information for users. No Contents help text. This part is for hints and useful information for users.");
	elm_layout_signal_emit(nocontents, "align.center", "elm");

	return nocontents;
}

void
nocontents_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nocontents;
	Evas_Object *nf = data;

	nocontents = create_nocontents(nf);
	elm_naviframe_item_push(nf, "Nocontents", NULL, NULL, nocontents, NULL);
}
