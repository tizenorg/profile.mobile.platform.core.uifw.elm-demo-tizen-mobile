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

static Eina_Bool
_access_action_cb(void *data, Evas_Object *obj, Elm_Access_Action_Info *action_info)
{
	Evas_Object *label;
	dlog_print(DLOG_DEBUG, LOG_TAG, "action type: %d", action_info->action_type);

	label = data;
	switch (action_info->action_type) {
		case ELM_ACCESS_ACTION_HIGHLIGHT:
			elm_object_text_set(label, "<font_size=33>HIGHLIGHT</font_size>");
			break;

		case ELM_ACCESS_ACTION_UNHIGHLIGHT:
			elm_object_text_set(label, "<font_size=33>UNHIGHLIGHT</font_size>");
			break;

		case ELM_ACCESS_ACTION_HIGHLIGHT_NEXT:
			elm_object_text_set(label, "<font_size=33>HIGHLIGHT NEXT</font_size>");
			break;

		case ELM_ACCESS_ACTION_HIGHLIGHT_PREV:
			elm_object_text_set(label, "<font_size=33>HIGHLIGHT PREV</font_size>");
			break;

		case ELM_ACCESS_ACTION_ACTIVATE:
			elm_object_text_set(label, "<font_size=33>ACTIVATE</font_size>");
			break;

		default:
			elm_object_text_set(label, "<font_size=33>Check the access object example</font_size>");
			break;
	}


	return EINA_FALSE;
}

static Evas_Object*
create_layout(Evas_Object *parent)
{
	Evas_Object *btn;
	Evas_Object *layout;
	Evas_Object *label;
	Evas_Object *ao, *to;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "using_access_object");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	label = elm_label_add(layout);
	elm_object_text_set(label, "<font_size=33>Check the access object example</font_size>");
	elm_object_part_content_set(layout, "label", label);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Top");
	elm_object_style_set(btn, "default");
	elm_object_part_content_set(layout, "top_button", btn);

	/* Example using normal purpose access object */
	to = (Evas_Object *)edje_object_part_object_get(elm_layout_edje_get(layout), "normal.access.rect");
	ao = elm_access_object_register(to, layout);
	elm_access_info_set(ao, ELM_ACCESS_INFO, "Normal Access Object");

	/* Example using access object something inside */
	to = (Evas_Object *)edje_object_part_object_get(elm_layout_edje_get(layout), "something.inside.access.rect");
	ao = elm_access_object_register(to, layout);
	elm_access_action_cb_set(ao, ELM_ACCESS_ACTION_HIGHLIGHT, _access_action_cb, label);
	elm_access_action_cb_set(ao, ELM_ACCESS_ACTION_UNHIGHLIGHT, _access_action_cb, label);
	elm_access_action_cb_set(ao, ELM_ACCESS_ACTION_HIGHLIGHT_NEXT, _access_action_cb, label);
	elm_access_action_cb_set(ao, ELM_ACCESS_ACTION_HIGHLIGHT_PREV, _access_action_cb, label);
	elm_access_action_cb_set(ao, ELM_ACCESS_ACTION_ACTIVATE, _access_action_cb, label);
	elm_access_action_cb_set(ao, ELM_ACCESS_ACTION_READ, _access_action_cb, label);


	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Bottom");
	elm_object_style_set(btn, "default");
	elm_object_part_content_set(layout, "bottom_button", btn);

	return layout;
}

void
using_access_object_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout;
	Evas_Object *nf = data;

	layout = create_layout(nf);
	elm_naviframe_item_push(nf, "Using access object", NULL, NULL, layout, NULL);
}
