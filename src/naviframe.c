/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *		  http://www.apache.org/licenses/LICENSE-2.0
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
quit_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Elm_Object_Item *bottom_it = elm_naviframe_bottom_item_get(nf);

	/* Pop to menu view */
	elm_naviframe_item_pop_to(bottom_it);
}

static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	/* By returning FALSE, you can reject the popping the item */
	return EINA_TRUE;
}

static Evas_Object*
create_toolbar_more_btn(Evas_Object *parent, Evas_Smart_Cb func, void *data)
{
	Evas_Object *btn = elm_button_add(parent);
	if (btn == NULL) return NULL;
	elm_object_style_set(btn, "naviframe/more/default");
	evas_object_smart_callback_add(btn, "clicked", func, data);
	return btn;
}

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
toolbar_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *tab_view;
	Elm_Object_Item *tab_it, *nf_it;
	const char *str;
	char buf[128];

	tab_it = elm_toolbar_selected_item_get(obj);
	if (tab_it) {
		str = elm_object_item_text_get(tab_it);
		snprintf(buf, sizeof(buf),"%s", str);
	}
	tab_view = create_nocontent(nf, buf);

	nf_it = elm_naviframe_top_item_get(nf);
	elm_object_item_part_content_set(nf_it, NULL, tab_view);
}

static Evas_Object*
create_4_items_icon_tabbar(Evas_Object *parent, const char *style)
{
	Evas_Object *toolbar;

	/* Create Tabbar */
	toolbar = elm_toolbar_add(parent);
	if (style) {
		elm_object_style_set(toolbar, style);
	}
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);

	elm_toolbar_item_append(toolbar, ICON_DIR"/00_controlbar_icon_favorites.png", "Main", toolbar_select_cb, parent);
	elm_toolbar_item_append(toolbar, ICON_DIR"/00_controlbar_icon_playlist.png",  "Playlist", toolbar_select_cb, parent);
	elm_toolbar_item_append(toolbar, ICON_DIR"/00_controlbar_icon_artists.png", "Artists list", toolbar_select_cb, parent);
	elm_toolbar_item_append(toolbar, ICON_DIR"/00_controlbar_icon_songs.png", "Songs", toolbar_select_cb, parent);
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_ALWAYS);

	return toolbar;
}

static Evas_Object*
create_4_items_tabbar(Evas_Object *parent, const char *style)
{
	Evas_Object *toolbar;

	/* Create Tabbar */
	toolbar = elm_toolbar_add(parent);

	elm_object_style_set(toolbar, style);
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);

	elm_toolbar_item_append(toolbar, NULL, "Main", toolbar_select_cb, parent);
	elm_toolbar_item_append(toolbar, NULL,  "Playlist", toolbar_select_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Artists list", toolbar_select_cb, parent);
	elm_toolbar_item_append(toolbar, NULL, "Songs", toolbar_select_cb, parent);
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_ALWAYS);

	return toolbar;
}

static void
eighth_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *tabbar;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 8");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, NULL, NULL, NULL, content, "tabbar/icon/notitle");

	/* Tabbar */
	tabbar = create_4_items_icon_tabbar(nf, "tabbar");
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", quit_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, quit_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
seventh_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *tabbar;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 7");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Tabbar with Icon", NULL, NULL, content, "tabbar/icon");

	/* Tabbar */
	tabbar = create_4_items_icon_tabbar(nf, "tabbar_with_title");
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", eighth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, eighth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
sixth_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *tabbar;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 6");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, NULL, NULL, NULL, content, "tabbar/notitle");

	/* Tabbar */
	tabbar = create_4_items_tabbar(nf, "tabbar");
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", seventh_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, seventh_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
fifth_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *tabbar;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 5");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Tabbar", NULL, NULL, content, "tabbar");

	/* Tabbar */
	tabbar = create_4_items_tabbar(nf, "tabbar_with_title");
	elm_object_item_part_content_set(nf_it, "tabbar", tabbar);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", sixth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, sixth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
fourth_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 4");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "TitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitleTitle", NULL, NULL, content, NULL);

	/* Title Cancel Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/title_cancel");
	evas_object_smart_callback_add(btn, "clicked", fifth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "title_left_btn", btn);

	/* Title Done Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/title_done");
	evas_object_smart_callback_add(btn, "clicked", fifth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "title_right_btn", btn);

	/* Title Badge */
	elm_object_item_part_text_set(nf_it, "title_badge", "999+");

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", fifth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, fifth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
third_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 3");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Title", NULL, NULL, content, "drawers");

	/* Subtitle */
	elm_object_item_part_text_set(nf_it, "subtitle", "Subtitle");

	/* Drawers */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/drawers");
	evas_object_smart_callback_add(btn, "clicked", fourth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "drawers", btn);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", fourth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, fourth_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
second_page_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 2");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Title Buttons", NULL, NULL, content, NULL);

	/* Title Cancel Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/title_left");
	evas_object_smart_callback_add(btn, "clicked", third_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "title_left_btn", btn);

	/* Title Done Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "naviframe/title_right");
	evas_object_smart_callback_add(btn, "clicked", third_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "title_right_btn", btn);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", third_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, third_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);
}

static void
first_page(Evas_Object *nf)
{
	Evas_Object *content;
	Evas_Object *btn;
	Elm_Object_Item *nf_it;

	content = create_nocontent(nf, "Naviframe Demo<br>Page 1");

	/* Push a new item */
	nf_it = elm_naviframe_item_push(nf, "Title", NULL, NULL, content, NULL);

	/* Bottom Toolbar Button */
	btn = elm_button_add(nf);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Next Page");
	evas_object_smart_callback_add(btn, "clicked", second_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar", btn);

	/* HW More Button */
	btn = create_toolbar_more_btn(nf, second_page_cb, nf);
	elm_object_item_part_content_set(nf_it, "toolbar_more_btn", btn);

	elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, nf);
}

void
naviframe_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	first_page(nf);
}
