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

void
_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *it;

   it = event_info;
   printf("label of selected item is: %s\n", elm_object_item_text_get(it));
}

void
_underflow_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   printf("underflow!\n");
}

void
_overflow_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   printf("overflow!\n");
}

static Evas_Object*
create_flipselector(Evas_Object *nf)
{
	Evas_Object *flipselector;
	char buf[8];
	int i;

	flipselector = elm_flipselector_add(nf);
	evas_object_smart_callback_add(flipselector, "underflowed", _overflow_cb, NULL);
	evas_object_smart_callback_add(flipselector, "overflowed", _underflow_cb, NULL);
	evas_object_size_hint_weight_set(flipselector, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	for (i = 0; i <= 99; i++) {
        snprintf(buf, 8, "%u", i);
        elm_flipselector_item_append(flipselector, buf, _sel_cb, NULL);
     }

	return flipselector;
}

void
flipselector_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *flipselector;
	Evas_Object *nf = data;

	flipselector = create_flipselector(nf);
	elm_naviframe_item_push(nf, "Flipselector", NULL, NULL, flipselector, NULL);
}
