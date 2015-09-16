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

static char *items[] = {
	"Text 1line", "Text 2line", "Text 3line",
	"Text 4line", "Text 5line", "Text 6line",
	"Text 7line", "Text 8line"
};

typedef struct _win_data
{
	Evas_Object *list;
	Evas_Object *win;
} win_data;

typedef struct _grid_data
{
	Elm_Object_Item *selected_item;
	Eina_Bool selected;
} grid_data;

typedef struct _Testitem
{
	Elm_Object_Item *item;
	const char *text;
	const char *path;
} Testitem;

static void
progressbar_popup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Ecore_Timer *timer = data;
	ecore_timer_del(timer);
}

static void
popup_timeout_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void
gl_radio_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	int index = (int) data;
	Evas_Object *radio;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	radio = elm_object_item_part_content_get(it, "elm.swallow.end");
	elm_radio_value_set(radio, index + 1);
}

static Evas_Object*
gl_radio_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int index = (int) data;
	Elm_Object_Item *it = elm_genlist_nth_item_get(obj, index);

	if (!strcmp(part, "elm.swallow.end")) {
		Evas_Object *radio;
		Evas_Object *radio_main = evas_object_data_get(obj, "radio");
		radio = elm_radio_add(obj);
		elm_radio_group_add(radio, radio_main);
		elm_radio_state_value_set(radio, index + 1);
		if (index == 1) elm_radio_value_set(radio, 1);
		evas_object_size_hint_weight_set(radio, EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_propagate_events_set(radio, EINA_FALSE);
		elm_atspi_accessible_relationship_append(it, ELM_ATSPI_RELATION_DESCRIBED_BY, radio);
		elm_atspi_accessible_relationship_append(radio, ELM_ATSPI_RELATION_CONTROLLED_BY, it);
		return radio;
	}
	return NULL;
}

static char*
gl_radio_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	if (!strcmp(part,"elm.text"))
	{
		int index = (int) data;
		return strdup(items[index]);
	}
	else return NULL;
}

static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	win_data *popup_data = (win_data *)data;
	popup_data->win = NULL;
	popup_data->list = NULL;
	free(popup_data);
	elm_theme_extension_del(NULL, ELM_DEMO_EDJ);
	return EINA_TRUE;
}

static Eina_Bool
progressbar_timer_cb(void *data)
{
	Evas_Object *popup = data;
	Evas_Object *progressbar = evas_object_data_get(popup, "progressbar");
	double value = 0.0;

	value = elm_progressbar_value_get(progressbar);
	if (value == 1.0) {
		evas_object_data_del(popup, "timer");
		evas_object_del(popup);
		return ECORE_CALLBACK_CANCEL;
	}
	value = value + 0.01;
	elm_progressbar_value_set(progressbar, value);

	return ECORE_CALLBACK_RENEW;
}

static void
gl_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	int index = 0;
	Elm_Object_Item *item = event_info;

	index = (int)elm_object_item_data_get(item);
	printf("selected text %s\n",items[index]);
	printf("Index of the list=%d\n", index);
	evas_object_del(popup);
}

static char*
gl_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int index = (int) data;
	return strdup(items[index]);
}

static char*
gl_2line_top_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int index = (int) data;

	if (!strcmp(part, "elm.text") || !strcmp(part, "elm.text.sub")) {
		return strdup(items[index]);
	}
	return NULL;
}


static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

static void
_popup_block_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}

static void
_popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	elm_popup_dismiss(popup);
}

static void
_popup_hide_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}

static void
_popup_hide_finished_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void
list_it_image_text_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *img;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_image_list_layout");
	elm_object_part_text_set(layout, "elm.text", "Description text");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(popup, layout);

	/* image */
	img = elm_image_add(layout);
	elm_image_file_set(img, ICON_DIR"/tizen.png", NULL);
	elm_image_aspect_fixed_set(img, EINA_TRUE);
	evas_object_size_hint_min_set(img, ELM_SCALE_SIZE(120), ELM_SCALE_SIZE(120));
	elm_object_part_content_set(layout, "elm.swallow.content", img);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_list_cb(void *data, Evas_Object *obj, void *event_info)
{
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	int i;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = gl_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 8; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, gl_sel_cb, popup);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 192);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}

static void
list_it_2line_cb(void *data, Evas_Object *obj, void *event_info)
{
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	Evas_Object *win = data;
	int index;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "double_label";
	itc.func.text_get = gl_2line_top_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (index = 0; index < 8; index++) {
		elm_genlist_item_append(genlist, &itc, (void *) index, NULL, ELM_GENLIST_ITEM_NONE, gl_sel_cb, popup);
	}
	evas_object_show(genlist);

	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 192);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}

static void
list_it_text_check_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *scroller;
	Evas_Object *label;
	Evas_Object *check;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_checkview_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(layout, "elm.text", "Description text");

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* check */
	check = elm_check_add(popup);
	elm_object_text_set(check, "Do not show again");
	elm_object_part_content_set(layout, "elm.swallow.end", check);

	/* scroller */
	scroller = elm_scroller_add(layout);
	elm_scroller_bounce_set(scroller, EINA_TRUE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	elm_object_part_content_set(layout, "elm.swallow.content", scroller);

	/* label */
	label = elm_label_add(scroller);
	elm_object_style_set(label, "popup/default");
	elm_label_line_wrap_set(label, ELM_WRAP_MIXED);
	elm_object_text_set(label, "This is popup description text. To provide information about popup, it is scrollable text.");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(label);
	elm_object_content_set(scroller, label);

	elm_object_content_set(popup, layout);

	evas_object_show(popup);
}

static void
list_it_processing_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *progressbar;
	Evas_Object *win = data;
	Ecore_Timer *timer;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "processing_view_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(layout, "elm.text", "Loading...");

	progressbar = elm_progressbar_add(layout);
	elm_object_style_set(progressbar, "process_medium");
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_part_content_set(layout, "processing", progressbar);
	timer = ecore_timer_add(0.1, progressbar_timer_cb, popup);

	elm_object_content_set(popup, layout);

	evas_object_data_set(popup, "progressbar", progressbar);
	evas_object_data_set(popup, "timer", timer);
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, progressbar_popup_del_cb, timer);

	evas_object_show(popup);
}

static void
list_it_text_progressbar_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *progressbar;
	Evas_Object *win = data;
	Ecore_Timer *timer;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_text_progressbar_view_layout");
	elm_object_part_text_set(layout, "elm.text.description", "Description about progress");
	elm_object_part_text_set(layout, "progress_text", "00/00");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* progressbar */
	progressbar = elm_progressbar_add(layout);
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_signal_emit(progressbar, "elm,units,show", "elm");
	elm_object_part_content_set(layout, "progressbar", progressbar);

	timer = ecore_timer_add(0.1, progressbar_timer_cb, popup);
	elm_object_content_set(popup, layout);

	evas_object_data_set(popup, "progressbar", progressbar);
	evas_object_data_set(popup, "timer", timer);
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, progressbar_popup_del_cb, timer);

	evas_object_show(popup);
}


static void
list_it_2text_progressbar_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *progressbar;
	Evas_Object *win = data;
	Ecore_Timer *timer;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_2text_progressbar_view_layout");
	elm_object_part_text_set(layout, "elm.text.description", "Primary Text");
	elm_object_part_text_set(layout, "elm.subtext.description", "Secondry Text");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* progressbar */
	progressbar = elm_progressbar_add(layout);
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_signal_emit(progressbar, "elm,units,show", "elm");
	elm_object_part_content_set(layout, "progressbar", progressbar);

	timer = ecore_timer_add(0.1, progressbar_timer_cb, popup);
	elm_object_content_set(popup, layout);

	evas_object_data_set(popup, "progressbar", progressbar);
	evas_object_data_set(popup, "timer", timer);
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, progressbar_popup_del_cb, timer);

	evas_object_show(popup);
}

static void
list_it_groupindex_list_cb(void *data, Evas_Object *obj, void *event_info)
{
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *btn;
	Evas_Object *genlist;
	Evas_Object *layout;
	Evas_Object *progressbar;
	Evas_Object *win = data;
	int i = 0;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Stop");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_groupindex_view_layout");
	elm_object_part_text_set(layout, "elm.text", "Scanning...");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* progressbar */
	progressbar = elm_progressbar_add(layout);
	elm_object_style_set(progressbar, "process_small");
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_part_content_set(layout, "processing", progressbar);

	/* box */
	box = elm_box_add(layout);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = gl_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 4; i++) {
		elm_genlist_item_append(genlist, &itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, gl_sel_cb, popup);
	}
	evas_object_show(genlist);

	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 158);
	elm_object_part_content_set(layout, "genlist", box);
	elm_object_content_set(popup, layout);

	evas_object_show(popup);
}

static void
list_it_list_radio_cb(void *data, Evas_Object *obj, void *event_info)
{
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *genlist;
	Evas_Object *radio;
	Evas_Object *box;
	Evas_Object *win = data;
	int i;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, popup);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);

	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	/* radio */
	radio = elm_radio_add(genlist);
	elm_radio_state_value_set(radio, 0);
	elm_radio_value_set(radio, 0);
	evas_object_data_set(genlist, "radio", radio);

	itc.item_style = "default_style";
	itc.func.text_get = gl_radio_text_get_cb;
	itc.func.content_get = gl_radio_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 4; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, gl_radio_sel_cb, (void *) i);
	}
	evas_object_show(genlist);

	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 192);
	elm_object_content_set(popup, box);
	evas_object_show(popup);
}

static void
list_it_text_slider_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *slider;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_text_slider_view_layout");
	elm_object_part_text_set(layout, "elm.text.description", "Description about progress");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(popup, layout);

	/* slider */
	slider = elm_slider_add(layout);
	elm_slider_indicator_show_set(slider, EINA_TRUE);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_slider_indicator_format_set(slider, "%1.0f");
	elm_slider_min_max_set(slider, 0, 9);
	elm_slider_value_set(slider, 1);
	elm_object_part_content_set(layout, "slider", slider);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}


static void
list_it_2text_slider_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *slider;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* layout */
	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_2text_slider_view_layout");
	elm_object_part_text_set(layout, "elm.text.description", "Primary Text");
	elm_object_part_text_set(layout, "elm.subtext.description", "Secondry Text");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(popup, layout);

	/* slider */
	slider = elm_slider_add(layout);
	elm_slider_indicator_show_set(slider, EINA_TRUE);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_slider_indicator_format_set(slider, "%1.0f");
	elm_slider_min_max_set(slider, 0, 9);
	elm_slider_value_set(slider, 1);
	elm_object_part_content_set(layout, "slider", slider);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_scrollable_text(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *win = data;
	Evas_Object *btn;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	elm_object_text_set(popup, "This popup has only long text,which can be set directly "
		"to popup.If this text fit in screen,then popup view will be normal. However if "
		"this text exceeds popup permissible size, then popup will internally add a scroller "
		"inside its layout,and height of popup will be fixed to its maximum height, and "
		"excess text can be seen by scroller the scroller available inside popup. In this "
		"way applications need not to add layout and scroller from their side, popup internally "
		"handles it. This popup has only long text, which can be set directly"
		"to popup. If this text fit in screen, then popup view will be normal. However if "
		"this text exceeds popup permissible size,then popup will internally add a scroller "
		"inside its layout,and height of popup will be fixed to its maximum height, and "
		"excess text can be seen by scroller the scroller available inside popup. In this "
		"way applications need not to add layout and scroller from their side,popup internally "
		"handles it");

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_text_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	elm_popup_timeout_set(popup, 3.0);
	evas_object_smart_callback_add(popup, "timeout", popup_timeout_cb, NULL);

	evas_object_show(popup);
}

static void
list_it_title_text_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", "Title");
	elm_object_text_set(popup,"This Popup has title area and description area testing wrapping ABCDE-FGHIJ-KLMNO-PQRST-UVWXYZ (This popup gets hidden when user clicks outside and has a timeout of 3 seconds)");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	elm_popup_timeout_set(popup, 3.0);
	evas_object_smart_callback_add(popup, "timeout", popup_timeout_cb, NULL);
	evas_object_show(popup);
}

static void
list_it_title_subtitle_text_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	elm_object_part_text_set(popup, "title,text", "Title");
	elm_object_part_text_set(popup, "subtitle,text", "SubTitle");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	elm_popup_timeout_set(popup, 3.0);
	elm_object_text_set(popup,"This Popup has title area and description area testing wrapping ABCDE-FGHIJ-KLMNO-PQRST-UVWXYZ (This popup gets hidden when user clicks outside and has a timeout of 3 seconds)");
	evas_object_smart_callback_add(popup, "timeout", popup_timeout_cb, NULL);
	evas_object_show(popup);
}

static void
list_it_text_2button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup, *btn;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup,"This Popup has content area and action area, action area has two buttons OK and Cancel.");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_text_3button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup, *btn;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup,"This Popup has content area and action area, action area has two buttons OK and Cancel.");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* close button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Close");
	elm_object_part_content_set(popup, "button3", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_toast_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *win = data;

	popup = elm_popup_add(win);
	elm_object_style_set(popup, "toast");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup, "Toast popup text Toast popup text");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	elm_popup_timeout_set(popup, 2.0);
	evas_object_smart_callback_add(popup, "timeout", popup_timeout_cb, NULL);

	evas_object_show(popup);
}

static void
list_it_title_text_2button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *btn;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup,"This Popup has title area, content area and action area set, action area has two buttons OK and Cancel.");
	elm_object_part_text_set(popup, "title,text", "Title");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_input_text_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup, *btn;
	appdata_s *ad = data;
	Evas_Object *entry;
	Evas_Object *layout;

	/* popup */
	popup = elm_popup_add(ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", "Title");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_input_text");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(popup, layout);

	entry = elm_entry_add(layout);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
	elm_object_part_text_set(entry, "elm.guide", "Guide Text");
	elm_object_part_content_set(layout, "elm.swallow.content" , entry);

	/* Cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* Set button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Set");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_text_input_text_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup, *btn;
	appdata_s *ad = data;
	Evas_Object *entry;
	Evas_Object *layout;

	/* popup */
	popup = elm_popup_add(ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", "Title");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "popup_text_input_text");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(layout, "elm.text.description", "Input Field");
	elm_object_content_set(popup, layout);

	entry = elm_entry_add(layout);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
	elm_object_part_text_set(entry, "elm.guide", "Guide Text");
	elm_object_part_content_set(layout, "elm.swallow.content" , entry);

	/* Cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	/* Set button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Set");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void
list_it_text_1button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *btn1;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup,"This Popup has content area and action area, action area has one button OK.");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn1 = elm_button_add(popup);
	elm_object_style_set(btn1, "bottom");
	elm_object_text_set(btn1, "OK");
	elm_object_part_content_set(popup, "button1", btn1);
	evas_object_smart_callback_add(btn1, "clicked", _popup_btn_clicked_cb, popup);
	evas_object_show(popup);
}

static void
list_it_title_text_1button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *btn;
	Evas_Object *win = data;

	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "title,text", "Title");
	elm_object_text_set(popup, "This Popup has title area, content area and action area, action area has one button OK");

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _popup_btn_clicked_cb, popup);
	evas_object_show(popup);
}

void
popup_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it;
	Evas_Object *win;
	Evas_Object *list;
	appdata_s *ad = data;
	win_data *popup_data = (win_data*)malloc(sizeof(win_data));

	elm_theme_extension_add(NULL, ELM_DEMO_EDJ);
	/* We convince the top widget is a window */
	win = ad->win;
	list = elm_list_add(ad->nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	popup_data->list = list;
	popup_data->win = win;

	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);
	elm_list_item_append(list, "popup - text", NULL, NULL, list_it_text_cb, win);
	elm_list_item_append(list, "popup - input text", NULL, NULL, list_it_input_text_cb, ad);
	elm_list_item_append(list, "popup - text + input text", NULL, NULL, list_it_text_input_text_cb, ad);
	elm_list_item_append(list, "popup - text + 1 button", NULL, NULL, list_it_text_1button_cb, win);
	elm_list_item_append(list, "popup - text + 2 buttons", NULL, NULL, list_it_text_2button_cb, win);
	elm_list_item_append(list, "popup - text + 3 buttons", NULL, NULL, list_it_text_3button_cb, win);
	elm_list_item_append(list, "popup - toast", NULL, NULL, list_it_toast_cb, win);
	elm_list_item_append(list, "popup - title + text", NULL, NULL, list_it_title_text_cb, win);
	elm_list_item_append(list, "popup - title + subtitle + text", NULL, NULL, list_it_title_subtitle_text_cb, win);
	elm_list_item_append(list, "popup - title + text + 1 button", NULL, NULL, list_it_title_text_1button_cb, win);
	elm_list_item_append(list, "popup - title + text + 2 buttons", NULL, NULL, list_it_title_text_2button_cb, win);
	elm_list_item_append(list, "popup - image + text", NULL, NULL, list_it_image_text_cb, win);
	elm_list_item_append(list, "popup - list", NULL, NULL, list_it_list_cb, win);
	elm_list_item_append(list, "popup - 2 line", NULL, NULL, list_it_2line_cb, win);
	elm_list_item_append(list, "popup - text + check", NULL, NULL, list_it_text_check_cb, win);
	elm_list_item_append(list, "popup - processing", NULL, NULL, list_it_processing_cb, win);
	elm_list_item_append(list, "popup - text + progressbar", NULL, NULL, list_it_text_progressbar_cb, win);
	elm_list_item_append(list, "popup - 2text + progressbar", NULL, NULL, list_it_2text_progressbar_cb, win);
	elm_list_item_append(list, "popup - groupindex + list", NULL, NULL, list_it_groupindex_list_cb, win);
	elm_list_item_append(list, "popup - list + radio", NULL, NULL, list_it_list_radio_cb, win);
	elm_list_item_append(list, "popup - text + slider", NULL, NULL, list_it_text_slider_cb, win);
	elm_list_item_append(list, "popup - 2text + slider", NULL, NULL, list_it_2text_slider_cb, win);
	elm_list_item_append(list, "popup - scrollable text", NULL, NULL, list_it_scrollable_text, win);
	elm_list_go(list);

	it = elm_naviframe_item_push(ad->nf, "Popup", NULL, NULL, list, NULL);
	elm_naviframe_item_pop_cb_set(it, naviframe_pop_cb, popup_data);
}
