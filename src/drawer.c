/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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
create_nocontent(Evas_Object *parent, const char *text)
{
	Evas_Object *layout, *scroller;

	/* Scroller */
	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	/* NoContent Layout */
	layout = elm_layout_add(scroller);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_text_set(layout, "elm.text", text);

	elm_object_content_set(scroller, layout);

	return scroller;
}

static void
list_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *panel = data;
	elm_panel_hidden_set(panel, EINA_TRUE);
}

static void
btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *panel = data;
	if (!elm_object_disabled_get(panel)) elm_panel_toggle(panel);
}

static Evas_Object*
create_panel(Evas_Object *parent)
{
	Evas_Object *panel, *list;
	int i;
	char buf[64];

	/* Panel */
	panel = elm_panel_add(parent);
	elm_panel_scrollable_set(panel, EINA_TRUE);

	/* Default is visible, hide the content in default. */
	elm_panel_hidden_set(panel, EINA_TRUE);
	evas_object_show(panel);

	/* Panel content */
	list = elm_list_add(panel);
	eext_object_event_callback_add(list, EEXT_CALLBACK_BACK, list_back_cb, panel);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	for (i = 0; i < 20; i++) {
		sprintf(buf, "list item %d", i);
		elm_list_item_append(list, buf, NULL, NULL, NULL, NULL);
	}

	evas_object_show(list);

	elm_object_content_set(panel, list);

	return panel;
}

static Evas_Object*
create_drawer_layout(Evas_Object *parent)
{
	Evas_Object *layout;
	layout = elm_layout_add(parent);
	elm_layout_theme_set(layout, "layout", "drawer", "panel");
	evas_object_show(layout);

	return layout;
}

static Evas_Object*
create_bg(Evas_Object *parent)
{
	Evas_Object *rect;
	rect = evas_object_rectangle_add(evas_object_evas_get(parent));
	evas_object_color_set(rect, 0, 0, 0, 0);
	evas_object_show(rect);

	return rect;
}

static void
panel_scroll_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Panel_Scroll_Info *ev = event_info;
	Evas_Object *bg = data;
	int col = 127 * ev->rel_x;

	/* Change color for background dim */
	evas_object_color_set(bg, 0, 0, 0, col);
}

static void
panel_unhold_cb(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object *panel = data;
	if (panel == NULL) return;
	elm_object_disabled_set(panel, EINA_TRUE);
}

static void
panel_hold_cb(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object *panel = data;
	if (panel == NULL) return;
	elm_object_disabled_set(panel, EINA_FALSE);
}

static void
panel_active_cb(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	printf("left drawer active!\n");
}

static void
panel_inactive_cb(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	printf("left drawer inactive!\n");
}

void
drawer_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout, *bg, *nocontent, *panel, *btn;
	Elm_Object_Item *nf_it;
	Evas_Object *nf = data;

	/* Create Layout for Drawer, Background, and Center View */
	layout = create_drawer_layout(nf);

	/* Left Drawer */
	panel = create_panel(layout);
	elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);
	elm_object_part_content_set(layout, "elm.swallow.left", panel);

	/* Panel Background (Dimmed Area) */
	bg = create_bg(layout);
	evas_object_smart_callback_add(panel, "scroll", panel_scroll_cb, bg);
	elm_object_part_content_set(layout, "elm.swallow.bg", bg);

	/* Center View */
	nocontent = create_nocontent(nf, "Left Drawer Demo");
	elm_object_part_content_set(layout, "elm.swallow.content", nocontent);

	/* Push the Layout as Naviframe item */
	nf_it = elm_naviframe_item_push(nf, "Left Drawer", NULL, NULL, layout, "drawers");

	/* hold & unhold signal callback */
	elm_object_signal_callback_add(panel, "elm,state,hold", "elm", panel_hold_cb, NULL);
	elm_object_signal_callback_add(panel, "elm,state,unhold", "elm", panel_unhold_cb, NULL);

	/* active & inactive signal callback */
	elm_object_signal_callback_add(panel, "elm,state,active", "elm", panel_active_cb, NULL);
	elm_object_signal_callback_add(panel, "elm,state,inactive", "elm", panel_inactive_cb, NULL);

	//left panel toggle button
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/drawers");
	evas_object_smart_callback_add(btn, "clicked", btn_cb, panel);
	elm_object_item_part_content_set(nf_it, "drawers", btn);
}
