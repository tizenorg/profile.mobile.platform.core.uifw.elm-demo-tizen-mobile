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
bg_color_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *bg;
	Evas_Object *nf = data;

	bg = elm_bg_add(nf);
	elm_bg_color_set(bg, 66, 162, 206);

	elm_naviframe_item_push(nf, "Solid Color", NULL, NULL, bg, NULL);
}

static void
bg_image_center_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *bg;
	Evas_Object *nf = data;
	char buf[PATH_MAX];

	bg = elm_bg_add(nf);
	elm_bg_option_set(bg, ELM_BG_OPTION_CENTER);
	snprintf(buf, sizeof(buf), "%s/tizen.png", ICON_DIR);
	elm_bg_file_set(bg, buf, NULL);

	elm_naviframe_item_push(nf, "Image - CENTER", NULL, NULL, bg, NULL);
}

static void
bg_image_scale_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *bg;
	Evas_Object *nf = data;
	char buf[PATH_MAX];

	bg = elm_bg_add(nf);
	elm_bg_option_set(bg, ELM_BG_OPTION_SCALE);
	snprintf(buf, sizeof(buf), "%s/tizen.png", ICON_DIR);
	elm_bg_file_set(bg, buf, NULL);

	elm_naviframe_item_push(nf, "Image - SCALE", NULL, NULL, bg, NULL);
}

static void
bg_image_stretch_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *bg;
	Evas_Object *nf = data;
	char buf[PATH_MAX];

	bg = elm_bg_add(nf);
	elm_bg_option_set(bg, ELM_BG_OPTION_STRETCH);
	snprintf(buf, sizeof(buf), "%s/tizen.png", ICON_DIR);
	elm_bg_file_set(bg, buf, NULL);

	elm_naviframe_item_push(nf, "Image - STRETCH", NULL, NULL, bg, NULL);
}

static void
bg_image_tile_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *bg;
	Evas_Object *nf = data;
	char buf[PATH_MAX];

	bg = elm_bg_add(nf);
	elm_bg_option_set(bg, ELM_BG_OPTION_TILE);
	snprintf(buf, sizeof(buf), "%s/tizen.png", ICON_DIR);
	elm_bg_file_set(bg, buf, NULL);

	elm_naviframe_item_push(nf, "Image - TILE", NULL, NULL, bg, NULL);
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

void
bg_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *list;
	Evas_Object *nf = data;

	/* List */
	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	elm_list_item_append(list, "Solid Color", NULL, NULL, bg_color_cb, nf);
	elm_list_item_append(list, "Image - CENTER", NULL, NULL, bg_image_center_cb, nf);
	elm_list_item_append(list, "Image - SCALE", NULL, NULL, bg_image_scale_cb, nf);
	elm_list_item_append(list, "Image - STRETCH", NULL, NULL, bg_image_stretch_cb, nf);
	elm_list_item_append(list, "Image - TILE", NULL, NULL, bg_image_tile_cb, nf);
	elm_list_go(list);

	elm_naviframe_item_push(nf, "Bg", NULL, NULL, list, NULL);
}

