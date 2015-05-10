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

static void
ctxpopup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(ctxpopup);
	ctxpopup = NULL;
}

static void
move_ctxpopup(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, (w / 2), y + (h / 2));
}

static void
ctxpopup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	const char *label = elm_object_item_text_get((Elm_Object_Item *) event_info);

	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);

	if (!strcmp(label, "INDICATOR_OPAQUE"))
		elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	else if (!strcmp(label, "INDICATOR_TRANSLUCENT"))
		elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSLUCENT);
	else if (!strcmp(label, "INDICATOR_TRANSPARENT"))
		elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);
	else
		elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_BG_TRANSPARENT);

	evas_object_del(ctxpopup);
	ctxpopup = NULL;
}

static void
indicator_btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Evas_Object *nf = ad->nf;

	if (!strcmp(elm_object_text_get(obj), "Indicator Show"))
	  {
		ctxpopup = elm_ctxpopup_add(nf);
		eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
		evas_object_smart_callback_add(ctxpopup,"dismissed", ctxpopup_dismissed_cb, NULL);

		elm_ctxpopup_item_append(ctxpopup, "INDICATOR_OPAQUE", NULL, ctxpopup_item_select_cb, ad);
		elm_ctxpopup_item_append(ctxpopup, "INDICATOR_TRANSLUCENT", NULL, ctxpopup_item_select_cb, ad);
		elm_ctxpopup_item_append(ctxpopup, "INDICATOR_TRANSPARENT", NULL, ctxpopup_item_select_cb, ad);
		elm_ctxpopup_item_append(ctxpopup, "INDICATOR_BG_TRANSPARENT", NULL, ctxpopup_item_select_cb, ad);

		move_ctxpopup(ctxpopup, obj);
		evas_object_show(ctxpopup);
	  }
	else
		elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_HIDE);
}

static Evas_Object*
create_conform_view(Evas_Object *parent, appdata_s *ad)
{
	Evas_Object *box, *btn;

	box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, ELM_SCALE_SIZE(50));
	evas_object_show(box);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Show");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(250), ELM_SCALE_SIZE(58));
	evas_object_smart_callback_add(btn, "clicked", indicator_btn_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Hide");
	evas_object_size_hint_min_set(btn, ELM_SCALE_SIZE(250), ELM_SCALE_SIZE(58));
	evas_object_smart_callback_add(btn, "clicked", indicator_btn_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	return box;
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "effect");
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

void
conformant_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout;
	appdata_s *ad = data;

	scroller = create_scroller(ad->nf);
	layout = create_conform_view(scroller, ad);
	elm_object_content_set(scroller, layout);

	elm_naviframe_item_push(ad->nf, "Conformant", NULL, NULL, scroller, NULL);
}
