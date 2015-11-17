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
transparent_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);
}

static void
custom_bg_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Set Indicator BG */
	Evas_Object *bg = evas_object_rectangle_add(evas_object_evas_get(obj));
	evas_object_color_set(bg, 0, 0, 255, 255);
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

static void
overlap_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Indicator Overlap Mode */
	elm_object_signal_emit(ad->conform, "elm,state,indicator,overlap", "elm");
}

static void
nooverlap_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Indicator No-Overlap Mode */
	elm_object_signal_emit(ad->conform, "elm,state,indicator,nooverlap", "elm");
}

static Evas_Object*
create_conform_view(Evas_Object *parent, appdata_s *ad)
{
	Evas_Object *layout, *box, *btn, *label;

	/* Box */
	box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, ELM_SCALE_SIZE(10));
	evas_object_show(box);

	/* Indicator Opaque Button */
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	elm_object_text_set(label, "<font_size=20><align=left>Default indicator mode:</align></font_size>");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(box);
	elm_object_text_set(btn, "Indicator Opaque");
	evas_object_smart_callback_add(btn, "clicked", opaque_btn_clicked_cb, ad);
	evas_object_show(btn);

	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	/* Indicator Transparent Button */
	label = elm_label_add(box);
	elm_label_ellipsis_set(label, EINA_TRUE);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	elm_object_text_set(label, "<font_size=20><align=left>Dragging down top screen area to show indicator:</align></font_size>");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Indicator Transparent");
	evas_object_smart_callback_add(btn, "clicked", transparent_btn_clicked_cb, ad);
	evas_object_show(btn);

	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	/* Indicator Custom BG Button */
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	elm_object_text_set(label, "<font_size=20><align=left>Custom Indicator BG Color:</align></font_size>");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Indicator Custom BG");
	evas_object_smart_callback_add(btn, "clicked", custom_bg_btn_clicked_cb, ad);
	evas_object_show(btn);

	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	/* Indicator Hide */
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	elm_object_text_set(label, "<font_size=20><align=left>Hide Indicator:</font_size>");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Indicator Hide");
	evas_object_smart_callback_add(btn, "clicked", hide_btn_clicked_cb, ad);
	evas_object_show(btn);

	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	/* Indicator Overlap */
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	elm_object_text_set(label, "<font_size=20><align=left>Indicator BG color to be transparent:</align></font_size>");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Indicator Overlap");
	evas_object_smart_callback_add(btn, "clicked", overlap_btn_clicked_cb, ad);
	evas_object_show(btn);

	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	/* Indicator No-Overlap */
	label = elm_label_add(box);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	elm_object_text_set(label, "<font_size=20><align=left>Default indicator mode:</align></font_size>");
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(layout);
	elm_object_text_set(btn, "Indicator No-Overlap");
	evas_object_smart_callback_add(btn, "clicked", nooverlap_btn_clicked_cb, ad);
	evas_object_show(btn);

	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

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
indicator_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout, *bg_layout;
	appdata_s *ad = data;

	scroller = create_scroller(ad->nf);
	bg_layout = elm_layout_add(scroller);
	evas_object_size_hint_weight_set(bg_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(bg_layout, ELM_DEMO_EDJ, "white_bg_layout");

	layout = create_conform_view(scroller, ad);
	elm_object_part_content_set(bg_layout, "elm.swallow.content", layout);
	elm_object_content_set(scroller, bg_layout);

	elm_naviframe_item_push(ad->nf, "Indicator", NULL, NULL, scroller, NULL);
}
