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
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

static void
index_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_index_item_selected_set(event_info, EINA_FALSE);
}

static void
index_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	/* This is called on every change, no matter how often
		elm_genlist_item_bring_in(elm_object_item_data_get(event_info),
		ELM_GENLIST_ITEM_SCROLLTO_TOP); */
}

static void
index_language_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	int i = 0, j, len;
	char *str;
	char buf[PATH_MAX] = {0, };

	elm_index_item_clear(obj);

	/* 1. Special character & Numbers */
	elm_index_item_append(obj, "#", NULL, NULL);

	/* 2. Local language */
	str = dgettext("efl-extension", "IDS_EA_BODY_ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	len = strlen(str);

	while (i < len)
	{
		j = i;
		eina_unicode_utf8_next_get(str, &i);
		snprintf(buf, i - j + 1, "%s", str + j);
		buf[i - j + 1] = 0;

		elm_index_item_append(obj, buf, NULL, NULL);
	}

	elm_index_level_go(obj, 0);
}

static Evas_Object*
create_fastscroll(Evas_Object *scroller)
{
	Evas_Object *layout, *index;
	int i = 0, j, len;
	char *str;
	char buf[PATH_MAX] = {0, };

	layout = elm_layout_add(scroller);
	elm_layout_theme_set(layout, "layout", "application", "fastscroll");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(scroller, layout);

	index = elm_index_add(layout);
	elm_object_part_content_set(layout, "elm.swallow.fastscroll", index);
	elm_index_autohide_disabled_set(index, EINA_TRUE);
	elm_index_omit_enabled_set(index, EINA_TRUE);

	/* 1. Special character & Numbers */
	elm_index_item_append(index, "#", NULL, NULL);

	/* 2. Local language */
	str = dgettext("efl-extension", "IDS_EA_BODY_ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	len = strlen(str);

	while (i < len) {
		j = i;
		eina_unicode_utf8_next_get(str, &i);
		snprintf(buf, i - j + 1, "%s", str + j);
		buf[i - j + 1] = 0;

		elm_index_item_append(index, buf, NULL, NULL);
	}

	elm_index_level_go(index, 0);

	evas_object_smart_callback_add(index, "selected", index_selected_cb, NULL);
	evas_object_smart_callback_add(index, "changed", index_changed_cb, NULL);
	evas_object_smart_callback_add(index, "language,changed", index_language_changed_cb, NULL);

	return index;
}

void
fastscroll_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	elm_naviframe_item_push(nf, "Fastscroll", NULL, NULL, scroller, NULL);

	create_fastscroll(scroller);
}
