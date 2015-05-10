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
	Evas_Object *ctxpopup;
	Eina_Bool rotate_flag;
	Eina_Bool longpressed;
} view_data_s;

typedef struct item_data {
	int index;
	const char *path;
	view_data_s *vd;
} item_data_s;

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
	w = (int)(vd->item_width * scale); /* 177 as per UX ver 1.7. */
	h = (int)(vd->item_height * scale);
	elm_gengrid_item_size_set(gengrid, w, h);
	elm_gengrid_align_set(gengrid, 0.5, 0.5);
	elm_gengrid_horizontal_set(gengrid, EINA_TRUE);
	elm_gengrid_multi_select_set(gengrid, EINA_TRUE);
	evas_object_smart_callback_add(gengrid, "moved", gengrid_moved_cb, NULL);
	evas_object_smart_callback_add(gengrid, "longpressed", gengrid_longpress_cb, vd);
	evas_object_smart_callback_add(gengrid, "realized", gengrid_realized_cb, NULL);

	gic = elm_gengrid_item_class_new();
	gic->item_style = "default";

	gic->func.text_get = NULL;
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

static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	view_data_s *vd = data;

	if (vd->ctxpopup != NULL) {
		evas_object_del(vd->ctxpopup);
		vd->ctxpopup = NULL;
	}

	free(vd);

	return EINA_TRUE;
}

static void
ctxpopup_it_cb(void *data, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;
	Elm_Object_Item *it, *ctxpopup_it;
	ctxpopup_it = event_info;
	const char *label = elm_object_item_text_get(ctxpopup_it);

	if (label != NULL) {
		if (!strcmp(label, "Small Size")) {
			vd->item_width = 106;
			vd->item_height = 106;
		} else if (!strcmp(label, "Large Size")) {
			vd->item_width = 160;
			vd->item_height = 160;
		}
	}

	vd->gengrid = create_gengrid(vd);

	it = elm_gengrid_last_item_get(vd->gengrid);
	elm_gengrid_item_show(it, ELM_GENGRID_ITEM_SCROLLTO_IN);

	elm_object_content_set(vd->nf, vd->gengrid);

	evas_object_del(obj);
}

static void
move_ctxpopup(Evas_Object *win, Evas_Object *ctxpopup)
{
	Evas_Coord w, h;
	int pos = -1;

	elm_win_screen_size_get(win, NULL, NULL, &w, &h);
	pos = elm_win_rotation_get(win);
	switch (pos) {
		case 0:
		case 180:
			evas_object_move(ctxpopup, 0, h);
			break;
		case 90:
			evas_object_move(ctxpopup, 0, w);
			break;
		case 270:
			evas_object_move(ctxpopup, h, w);
			break;
	}
	evas_object_show(ctxpopup);
}

static void
ctxpopup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;

	if (!vd->rotate_flag) {
		evas_object_del(obj);
	}
	else {
		move_ctxpopup(vd->win, obj);
		vd->rotate_flag = EINA_FALSE;
	}
}

static void
naviframe_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;

	if (vd->ctxpopup != NULL)
		vd->rotate_flag = EINA_TRUE;
	else
		vd->rotate_flag = EINA_FALSE;
}

static void
win_rotation_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	view_data_s *vd = data;
	move_ctxpopup(vd->win, vd->ctxpopup);
}

static void
ctxpopup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;

	evas_object_event_callback_del(nf, EVAS_CALLBACK_RESIZE, naviframe_resize_cb);
	evas_object_smart_callback_del(elm_object_top_widget_get(obj), "rotation,changed", win_rotation_changed_cb);
}

static void
toolbar_more_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *ctxpopup;
	view_data_s *vd = data;
	double scale = elm_config_scale_get();

	ctxpopup = elm_ctxpopup_add(vd->nf);
	elm_object_style_set(ctxpopup, "more/default");
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	evas_object_smart_callback_add(ctxpopup,"dismissed", ctxpopup_dismissed_cb, vd);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, ctxpopup_del_cb, vd);
	evas_object_event_callback_add(vd->nf, EVAS_CALLBACK_RESIZE, naviframe_resize_cb, vd);
	evas_object_smart_callback_add(elm_object_top_widget_get(ctxpopup), "rotation,changed", win_rotation_changed_cb, vd);
	elm_ctxpopup_item_append(ctxpopup, "Small Size", NULL, ctxpopup_it_cb, vd);
	elm_ctxpopup_item_append(ctxpopup, "Large Size", NULL, ctxpopup_it_cb, vd);
	evas_object_size_hint_max_set(ctxpopup, scale * 500, scale * 600);
	elm_ctxpopup_direction_priority_set(ctxpopup, ELM_CTXPOPUP_DIRECTION_UP, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN);

	move_ctxpopup(vd->win, ctxpopup);

	vd->ctxpopup = ctxpopup;
}

void
gengrid_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *btn;
	Elm_Object_Item *navi_it;
	view_data_s *vd;
	Evas_Object *nf = data;

	vd = calloc(1, sizeof(view_data_s));
	if (!vd) return;
	/* We convince the top widget is a window */
	vd->win = elm_object_top_widget_get(nf);
	vd->nf = nf;
	vd->item_width = 160;
	vd->item_height = 160;

	vd->gengrid = create_gengrid(vd);

	navi_it = elm_naviframe_item_push (vd->nf, "Default", NULL, NULL, vd->gengrid, NULL);
	elm_naviframe_item_pop_cb_set(navi_it, naviframe_pop_cb, vd);

	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/more/default");
	evas_object_smart_callback_add(btn, "clicked", toolbar_more_btn_clicked_cb, vd);
	elm_object_item_part_content_set(navi_it, "toolbar_more_btn", btn);
}
