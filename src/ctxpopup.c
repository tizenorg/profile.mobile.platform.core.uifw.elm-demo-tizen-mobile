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

static Evas_Object *ctxpopup = NULL;

static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	if (ctxpopup != NULL) {
		evas_object_del(ctxpopup);
		ctxpopup = NULL;
	}

	return EINA_TRUE;
}

static void
move_ctxpopup(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, (w / 2), y + (h / 2));
}

static void
move_dropdown(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, x + (w / 2), y + h);
}


static void
move_more_ctxpopup(Evas_Object *ctxpopup)
{
	Evas_Object *win;
	Evas_Coord w, h;
	int pos = -1;

	/* We convince the top widget is a window */
	win = elm_object_top_widget_get(ctxpopup);
	elm_win_screen_size_get(win, NULL, NULL, &w, &h);
	pos = elm_win_rotation_get(win);

	switch (pos) {
		case 0:
		case 180:
			evas_object_move(ctxpopup, (w / 2), h);
			break;
		case 90:
			evas_object_move(ctxpopup,  (h / 2), w);
			break;
		case 270:
			evas_object_move(ctxpopup, (h / 2), w);
			break;
	}
}

static void
ctxpopup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(ctxpopup);
	ctxpopup = NULL;
}

static void
naviframe_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Object *ctxpopup = data;
	move_more_ctxpopup(ctxpopup);
}

static void
win_rotation_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *ctxpopup = data;
	move_more_ctxpopup(ctxpopup);
}

static void
more_ctxpopup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	evas_object_event_callback_del_full(nf, EVAS_CALLBACK_RESIZE, naviframe_resize_cb, ctxpopup);
}

static void
item_move_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Coord x, y, w, h;
	evas_object_geometry_get(obj, &x, &y, &w, &h);
	printf("[%s : %d] obj=%p x=%d y=%d w=%d h=%d\n", __func__, __LINE__, obj, x, y, w,h);
}

static void
ctxpopup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *label = elm_object_item_text_get((Elm_Object_Item *) event_info);
	if (label) fprintf(stderr, "text(%s) is clicked\n", label);

	Evas_Object *icon = elm_object_item_content_get((Elm_Object_Item *) event_info);
	if (icon) fprintf(stderr, "icon is clicked\n");
}

/* Text Only */
static void
btn_text_only_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;

	if (ctxpopup != NULL) {
		evas_object_del(ctxpopup);
	}

	ctxpopup = elm_ctxpopup_add(nf);
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	evas_object_smart_callback_add(ctxpopup,"dismissed", ctxpopup_dismissed_cb, NULL);

	elm_ctxpopup_item_append(ctxpopup, "Message", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Email", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Facebook", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Flickr", NULL, ctxpopup_item_select_cb, NULL);

	move_ctxpopup(ctxpopup, obj);
	evas_object_show(ctxpopup);
}

/* Icon + Text (More button style : Naviframe Toolbar) */
static void
create_ctxpopup_more_button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *it_obj;
	Evas_Object *nf = data;
	Evas_Object *win;
	Elm_Object_Item *it;

	if (ctxpopup != NULL) {
		evas_object_del(ctxpopup);
	}

	ctxpopup = elm_ctxpopup_add(nf);
	elm_ctxpopup_auto_hide_disabled_set(ctxpopup, EINA_TRUE);
	elm_object_style_set(ctxpopup, "more/default");
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_MORE, eext_ctxpopup_back_cb, NULL);
	evas_object_smart_callback_add(ctxpopup, "dismissed", ctxpopup_dismissed_cb, NULL);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, more_ctxpopup_del_cb, nf);
	evas_object_event_callback_add(nf, EVAS_CALLBACK_RESIZE, naviframe_resize_cb, ctxpopup);

	/* We convince the top widget is a window */
	win = elm_object_top_widget_get(nf);
	evas_object_smart_callback_add(win, "rotation,changed", win_rotation_changed_cb, ctxpopup);

	it = elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, NULL);

	/* This is example to track an object item position */
	it_obj = elm_object_item_track(it);
	evas_object_event_callback_add(it_obj, EVAS_CALLBACK_MOVE, item_move_cb, NULL);

	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);

	elm_ctxpopup_direction_priority_set(ctxpopup, ELM_CTXPOPUP_DIRECTION_UP, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN);

	move_more_ctxpopup(ctxpopup);
	evas_object_show(ctxpopup);
}

void
ctxpopup_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *box;
	Evas_Object *btn;
	Evas_Object *scroller;
	Evas_Object *nf = data;
	Elm_Object_Item *nf_it;

	/* scroller */
	scroller = elm_scroller_add(nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	/* box */
	box = elm_box_add(scroller);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(box);
	elm_object_content_set(scroller, box);

	/* Text Only */
	btn = elm_button_add(box);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	elm_object_text_set(btn, "Text Only");
	evas_object_smart_callback_add(btn, "clicked", btn_text_only_cb, nf);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	nf_it = elm_naviframe_item_push(nf, "CtxPopup", NULL, NULL, scroller, NULL);
	elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, NULL);

	/* This button is set for devices which doesn't have H/W more key. */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/more/default");
	evas_object_smart_callback_add(btn, "clicked", create_ctxpopup_more_button_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}
