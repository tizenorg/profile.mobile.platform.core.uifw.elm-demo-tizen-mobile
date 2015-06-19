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

typedef struct view_data {
	Evas_Object *win;
	Evas_Object *nf;
	Evas_Object *gengrid;
	int item_width;
	int item_height;
	Eina_Bool longpressed;
	char *style;
} view_data_s;

typedef struct item_data {
	int index;
	const char *path;
	view_data_s *vd;
} item_data_s;

char *item_names[] = {
	"AAAAA",
	"BBBBB",
	"CCCCC",
	"DDDDD",
	"EEEEE",
	NULL
};

static void
gengrid_moved_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;

	item_data_s *id = elm_object_item_data_get(it);
	printf("moved item index = %d", id->index);

	if (elm_gengrid_item_prev_get(it)) {
		item_data_s *prev_id = elm_object_item_data_get(elm_gengrid_item_prev_get(it));
		printf(", prev index = %d", prev_id->index);
	}
	if (elm_gengrid_item_next_get(it)) {
		item_data_s *next_id = elm_object_item_data_get(elm_gengrid_item_next_get(it));
		printf(", next index = %d", next_id->index);
	}
	printf("\n");

	/* If you want change your data, you can here. */
}

static void
gengrid_longpress_cb(void *data, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;
	vd->longpressed = EINA_TRUE;
	/* If you need to cancel select status when longpress is called(e.g. popup)
		set elm_gengrid_item_selected_set as EINA_FALSE.
		elm_gengrid_item_selected_set(ei, EINA_FALSE); */
}

static char*
gengrid_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];
	item_data_s *id = data;
	int index = id->index;

	snprintf(buf, 1023, "%s", item_names[index%5]);
	return strdup(buf);
}


static Evas_Object*
gengrid_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	item_data_s *id = data;

	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *img = elm_image_add(obj);
		elm_image_file_set(img, id->path, NULL);
		elm_image_aspect_fixed_set(img, EINA_FALSE);
		elm_image_preload_disabled_set(img, EINA_FALSE);
		evas_object_show(img);
		return img;
	} else if (!strcmp(part, "elm.swallow.end") && id->index == 199) {
		Evas_Object *layout = elm_layout_add(obj);
		elm_layout_theme_set(layout, "layout", "badge", "default");
		elm_object_part_text_set(layout, "elm.text", "199");
		return layout;
	}

	return NULL;
}

static void
gengrid_it_cb(void *data, Evas_Object *obj, void *event_info)
{
	item_data_s *id = data;
	Elm_Object_Item *it = event_info;

	printf("item selected: %p\n", it);
	elm_gengrid_item_selected_set(it, EINA_FALSE);

	if (id->vd->longpressed) {
		id->vd->longpressed = EINA_FALSE;
		return;
	}
}

static void
gengrid_realized_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("[%s][%d]\n", __func__, __LINE__);
}

static Evas_Object*
create_gengrid(view_data_s *vd)
{
	#define IMAGE_MAX 2
	static item_data_s id[IMAGE_MAX * 200];
	int i, j, n, w, h;
	char buf[PATH_MAX];
	Elm_Gengrid_Item_Class *gic;
	Evas_Object *gengrid;

	gengrid = elm_gengrid_add(vd->nf);
	evas_object_size_hint_weight_set(gengrid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(gengrid, EVAS_HINT_FILL, EVAS_HINT_FILL);

	double scale = elm_config_scale_get();
	w = (int)(ELM_SCALE_SIZE(vd->item_width)); /* 177 as per UX ver 1.7. */
	h = (int)(ELM_SCALE_SIZE(vd->item_height));
	elm_gengrid_item_size_set(gengrid, w, h);
	elm_gengrid_align_set(gengrid, 0.5, 0.5);
	elm_gengrid_horizontal_set(gengrid, EINA_TRUE);
	elm_gengrid_multi_select_set(gengrid, EINA_TRUE);
	evas_object_smart_callback_add(gengrid, "moved", gengrid_moved_cb, NULL);
	evas_object_smart_callback_add(gengrid, "longpressed", gengrid_longpress_cb, vd);
	evas_object_smart_callback_add(gengrid, "realized", gengrid_realized_cb, NULL);

	gic = elm_gengrid_item_class_new();
	gic->item_style = vd->style;

	gic->func.text_get = gengrid_text_get_cb;
	gic->func.content_get = gengrid_content_get_cb;
	gic->func.state_get = NULL;
	gic->func.del = NULL;

	for (j = 0; j < 200; j++) {
		for (i = 0; i < IMAGE_MAX; i++) {
			n = i + (j * IMAGE_MAX);
			snprintf(buf, sizeof(buf), "%s/grid_image/%d_raw.png", ICON_DIR, i + 1);
			id[n].index = n;
			id[n].path = eina_stringshare_add(buf);
			id[n].vd = vd;
			elm_gengrid_item_append(gengrid, gic, &(id[n]), gengrid_it_cb, &(id[n]));
		}
	}
	evas_object_show(gengrid);

	return gengrid;
}

static void
gengrid_type1_cb(void *data, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;
	vd->item_width = 134;
	vd->item_height= 134;
	vd->style = "default";  //type1 = default
							//You can both use of them for dafault gengrid style.

	vd->gengrid = create_gengrid(vd);

	elm_naviframe_item_push(vd->nf, "Gengrid Type1", NULL, NULL, vd->gengrid, NULL);
}

static void
gengrid_type2_cb(void *data, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;
	vd->item_width = 134;
	vd->item_height= 164;
	vd->style = "type2";

	vd->gengrid = create_gengrid(vd);

	elm_naviframe_item_push(vd->nf, "Gengrid Type2", NULL, NULL, vd->gengrid, NULL);
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *it = event_info;
    elm_list_item_selected_set(it, EINA_FALSE);
}

void
gengrid_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *list;
	view_data_s *vd;
	Evas_Object *nf = data;

	vd = calloc(1, sizeof(view_data_s));
	if (!vd) return;
	/* We convince the top widget is a window */
	vd->win = elm_object_top_widget_get(nf);
	vd->nf = nf;

	/* List */
	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	elm_list_item_append(list, "Gengrid Type1", NULL, NULL, gengrid_type1_cb, vd);
	elm_list_item_append(list, "Gengrid Type2", NULL, NULL, gengrid_type2_cb, vd);
	elm_list_go(list);

	elm_naviframe_item_push(nf, "Gengrid", NULL, NULL, list, NULL);
}
