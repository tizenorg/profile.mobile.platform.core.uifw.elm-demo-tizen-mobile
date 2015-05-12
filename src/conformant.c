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
opaque_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);

	/* Unset if you set the Indicator BG */
	evas_object_del(elm_object_part_content_get(ad->conform, "elm.swallow.indicator_bg"));
}

static void
translucent_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSLUCENT);
}

static void
custom_bg_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Set Indicator BG */
	Evas_Object *bg = evas_object_rectangle_add(evas_object_evas_get(obj));
	evas_object_color_set(bg, 0, 0, 0, 255);
	elm_object_part_content_set(ad->conform, "elm.swallow.indicator_bg", bg);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
}

static void
hide_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_HIDE);
}

static Evas_Object*
create_conform_view(Evas_Object *parent, appdata_s *ad)
{
	Evas_Object *box, *btn;

	/* Box */
	box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, ELM_SCALE_SIZE(10));
	evas_object_show(box);

	/* Indicator Opaque Button */
	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Opaque");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_smart_callback_add(btn, "clicked", opaque_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Indicator Translucent Button */
	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Translucent");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_smart_callback_add(btn, "clicked", translucent_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Indicator Custom BG Button */
	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Custom BG");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_smart_callback_add(btn, "clicked", custom_bg_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Indicator Hide */
	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Hide");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_smart_callback_add(btn, "clicked", hide_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	return box;
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
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
