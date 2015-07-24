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
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

static Evas_Object*
create_list(Evas_Object *nf)
{
	Evas_Object *list;

	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);
	elm_list_item_append(list, "Horizontal Style", NULL, NULL, pagecontrol_horizontal_cb, nf);
	elm_list_item_append(list, "Horizontal Loop Style", NULL, NULL, pagecontrol_horizontal_loop_cb, nf);

	elm_list_go(list);

	return list;
}

void
pagecontrol_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *list;
	Evas_Object *nf = data;

	list = create_list(nf);
	elm_naviframe_item_push(nf, "Pagecontrol", NULL, NULL, list, NULL);
}
