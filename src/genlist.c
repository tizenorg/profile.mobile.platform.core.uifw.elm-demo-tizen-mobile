/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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

#define NUM_OF_ITEMS 8000

typedef struct item_data
{
	int index;
	Elm_Object_Item *item;
} item_data_s;

static void gl_del_cb(void *data, Evas_Object *obj);
static void gl_loaded_cb(void *data, Evas_Object *obj, void *event_info);
static void gl_realized_cb(void *data, Evas_Object *obj, void *event_info);
static void gl_longpressed_cb(void *data, Evas_Object *obj, void *event_info);
static void gl_selected_cb(void *data, Evas_Object *obj, void *event_info);
static void gl_mouse_down_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);

static Evas_Object*
create_image(Evas_Object *parent)
{
	Evas_Object *img;

	img = elm_image_add(parent);
	elm_image_file_set(img, ICON_DIR"/iu.png", NULL);
	evas_object_size_hint_min_set(img, 36, 36);

	return img;
}

// type1
// --------------------------------------------------------------------
// | elm.swallow.icon |   elm.text   | elm.swallow.end (elm.text.end) |
// --------------------------------------------------------------------
// |          elm.text.sub           |         elm.text.sub.end       |
// --------------------------------------------------------------------

/*
"type1" style is designed to cover various types of item style at a time.

It has two swallow parts (elm.swallow.icon, elm.swallow.end) and
four text parts (elm.text, elm.text.end, elm.text.sub, elm.text.sub.end).

In content_get_cb and text_get_cb,
you must return NULL for parts where no content is desired,
or a valid object handle, otherwise.

For example,
-----------------------------------
| elm.text     |                  |
---------------|  elm.swallow.end |
| elm.text.sub |                  |
-----------------------------------

static Evas_Object*
gl_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	if (!strcmp(elm.swallow.end))
		return (valid Evas_Object*);
	else
		return NULL;
}

static char*
gl_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	if (!strcmp(elm.text))
		return strdup("text for elm.text part");
	else if (!strcmp(elm.text.sub))
		return strdup("text for elm.text.sub part");
	else
		return NULL;
}
*/

static Evas_Object*
type1_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	item_data_s *id = data;

	switch (id->index % 11)
	{
	case 0:
	// -------------------------------
	// | elm.text                    |
	// -------------------------------
		return NULL;

	case 1:
	// -------------------------------
	// | elm.swallow.icon | elm.text |
	// -------------------------------
		if (!strcmp("elm.swallow.icon", part))
			return create_image(obj);
		else return NULL;

	case 2:
	// -------------------------------
	// | elm.text  | elm.swallow.end |
	// -------------------------------
		if (!strcmp("elm.swallow.end", part))
			return create_image(obj);
		else return NULL;

	case 3:
	// -------------------------------
	// | elm.text  | elm.text.end    |
	// -------------------------------
		return NULL;

	case 4:
	// -------------------------------
	// | elm.text                    |
	// -------------------------------
	// | elm.text.sub                |
	// -------------------------------
		return NULL;

	case 5:
	// -------------------------------
	// | elm.text  | elm.text.end    |
	// -------------------------------
	// | elm.text.sub                |
	// -------------------------------
		return NULL;

	case 6:
	// -----------------------------------
	// | elm.text                        |
	// -----------------------------------
	// | elm.text.sub | elm.text.sub.end |
	// -----------------------------------
		return NULL;

	case 7:
	// -----------------------------------
	// | elm.text     | elm.text.end     |
	// -----------------------------------
	// | elm.text.sub | elm.text.sub.end |
	// -----------------------------------
		return NULL;

	case 8:
	// -----------------------------------
	// | elm.text     |                  |
	// ---------------|  elm.swallow.end |
	// | elm.text.sub |                  |
	// -----------------------------------
		if (!strcmp("elm.swallow.end", part))
			return create_image(obj);
		else return NULL;

	case 9:
	// -----------------------------------
	// | elm.text     | elm.swallow.end  |
	// -----------------------------------
	// | elm.text.sub | elm.text.sub.end |
	// -----------------------------------
		if (!strcmp("elm.swallow.end", part))
			return create_image(obj);
		else return NULL;

	case 10:
	// --------------------------------------------------
	// | elm.swallow.icon | elm.text | elm.swallow.end  |
	// --------------------------------------------------
	// | elm.text.sub                | elm.text.sub.end |
	// --------------------------------------------------
		if (!strcmp("elm.swallow.icon", part))
			return create_image(obj);
		else if (!strcmp("elm.swallow.end", part))
			return create_image(obj);
		else return NULL;
	}

	return NULL; // You must not reach here.
}

static char*
type1_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	item_data_s *id = data;
	char *long_text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
	char buf[1024];

	snprintf(buf, sizeof(buf), "case %d: %s", id->index % 11, long_text);

	switch (id->index % 11)
	{
	case 0:
	// -------------------------------
	// | elm.text                    |
	// -------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else return NULL;

	case 1:
	// -------------------------------
	// | elm.swallow.icon | elm.text |
	// -------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else return NULL;

	case 2:
	// -------------------------------
	// | elm.text  | elm.swallow.end |
	// -------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else return NULL;

	case 3:
	// -------------------------------
	// | elm.text  | elm.text.end    |
	// -------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.end", part))
			return strdup("Sub text");
		else return NULL;

	case 4:
	// -------------------------------
	// | elm.text                    |
	// -------------------------------
	// | elm.text.sub                |
	// -------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else return NULL;

	case 5:
	// -------------------------------
	// | elm.text  | elm.text.end    |
	// -------------------------------
	// | elm.text.sub                |
	// -------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.end", part))
			return strdup("Sub text");
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else return NULL;

	case 6:
	// -----------------------------------
	// | elm.text                        |
	// -----------------------------------
	// | elm.text.sub | elm.text.sub.end |
	// -----------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub.end", part))
			return strdup("Sub text");
		else return NULL;

	case 7:
	// -----------------------------------
	// | elm.text     | elm.text.end     |
	// -----------------------------------
	// | elm.text.sub | elm.text.sub.end |
	// -----------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.end", part))
			return strdup("Sub text");
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub.end", part))
			return strdup("Sub text");
		else return NULL;

	case 8:
	// -----------------------------------
	// | elm.text     |                  |
	// ---------------|  elm.swallw.end  |
	// | elm.text.sub |                  |
	// -----------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else return NULL;

	case 9:
	// -----------------------------------
	// | elm.text     | elm.swallow.end  |
	// -----------------------------------
	// | elm.text.sub | elm.text.sub.end |
	// -----------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub.end", part))
			return strdup("Sub text");
		else return NULL;

	case 10:
	// --------------------------------------------------
	// | elm.swallow.icon | elm.text | elm.swallow.end  |
	// --------------------------------------------------
	// | elm.text.sub                | elm.text.sub.end |
	// --------------------------------------------------
		if (!strcmp("elm.text", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub", part))
			return strdup(buf);
		else if (!strcmp("elm.text.sub.end", part))
			return strdup("Sub text");
		else return NULL;
	}

	return NULL; // You must not reach here.
}

// type2
// --------------------------------------------------------------------
// |          elm.text.sub           |         elm.text.sub.end       |
// --------------------------------------------------------------------
// | elm.swallow.icon |   elm.text   | elm.swallow.end (elm.text.end) |
// --------------------------------------------------------------------
// "type2" style is almost same with "type1" except for the position of sub line.


// multiline
// -----------------------------------
// |        elm.text                 |
// -----------------------------------
// |        elm.text.multiline       |
// -----------------------------------

static char*
multiline_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	item_data_s *id = data;
	char *long_text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
	char buf[1024];

	switch (id->index % 5)
	{
	case 0:
		if (!strcmp("elm.text.multiline", part))
		{
			snprintf(buf, sizeof(buf), "<font_size=30>%s</font_size>", long_text);
			return strdup(buf);
		}
		else return NULL;

	case 1:
		if (!strcmp("elm.text.multiline",part))
			return strdup(long_text);
		else return NULL;

	case 2:
		if (!strcmp("elm.text", part))
			return strdup("Primary text");
		else if (!strcmp("elm.text.multiline", part))
			return strdup(long_text);
		else return NULL;

	case 3:
		if (!strcmp("elm.text", part))
			return strdup("Primary text");
		else if (!strcmp("elm.text.multiline", part))
		{
			snprintf(buf, sizeof(buf), "<font color=#3DB9CCFF>Secondary text</font><br>%s",long_text);
			return strdup(buf);
		}
		else return NULL;

	case 4:
		if (!strcmp("elm.text.multiline", part))
		{
			snprintf(buf, sizeof(buf), "<font color=#3DB9CCFF>Secondary text</font><br><font_size=30>%s</font_size>",long_text);
			return strdup(buf);
		}
		else return NULL;
	}

	return NULL; // You must not reach here.
}

// full
// -----------------------------------
// |       elm.swallow.content       |
// -----------------------------------

static Evas_Object*
full_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *layout, *slider;

	layout = elm_layout_add(obj);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "gl_custom_item");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_object_part_text_set(layout, "elm.text", "Description Text");

	slider = elm_slider_add(obj);
	elm_slider_indicator_show_set(slider, EINA_FALSE);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_slider_horizontal_set(slider, EINA_TRUE);
	elm_object_part_content_set(layout, "elm.swallow.content", slider);

	return layout;
}

////////////////////////////////////////////////////////////////////////////

static void
gl_del_cb(void *data, Evas_Object *obj)
{
	/* Unrealized callback can be called after this. */
	/* Accessing item_data_s can be dangerous on unrealized callback. */
	item_data_s *id = data;
	free(id);
}

static void
gl_loaded_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("loaded\n");
}

static void
gl_realized_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	item_data_s *id = elm_object_item_data_get(it);
	printf("%s: [%d]\n", __func__, id->index);
}

static void
gl_longpressed_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	item_data_s *id = elm_object_item_data_get(it);
	printf("%s: [%d]\n", __func__, id->index);
}

static void
gl_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	item_data_s *id = elm_object_item_data_get(it);
	printf("%s: [%d]\n", __func__, id->index);
	/* Unhighlight item */
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

static void
gl_mouse_down_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Down *ev = event_info;
	int ret;
	Elm_Object_Item *it = elm_genlist_at_xy_item_get(obj, ev->canvas.x, ev->canvas.y, &ret);
	printf("down %d %d (%d) (%p)\n", ev->canvas.x, ev->canvas.y, elm_genlist_item_index_get(it), it);
}

static void
genlist_test_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
	Evas_Object *genlist;
	Evas_Object *nf = data;
	Elm_Object_Item *it = event_info;
	Elm_Genlist_Item_Class *itc;

	int index;
	int n_items = NUM_OF_ITEMS;
	const char *style = elm_object_item_text_get(it);

	printf("Item style: %s\n", style);
	elm_list_item_selected_set(it, EINA_FALSE);

	/* Create item class */
	if (!strcmp("type1", style) || !strcmp("type2", style))
	{
		itc = elm_genlist_item_class_new();
		itc->item_style = style;
		itc->func.content_get = type1_content_get_cb;
		itc->func.text_get = type1_text_get_cb;
		itc->func.del = gl_del_cb;
	}
	else if (!strcmp("multiline", style))
	{
		itc = elm_genlist_item_class_new();
		itc->item_style = style;
		itc->func.content_get = NULL;
		itc->func.text_get = multiline_text_get_cb;
		itc->func.del = gl_del_cb;
	}
	else
	{
		itc = elm_genlist_item_class_new();
		itc->item_style = style;
		itc->func.content_get = full_content_get_cb;
		itc->func.text_get = NULL;
		itc->func.del = gl_del_cb;
	}

	/* Create genlist */
	genlist = elm_genlist_add(nf);

	/* Optimize your application with appropriate genlist block size. */
	elm_genlist_block_count_set(genlist, 14);

	/* COMPRESS MODE
	   For the Mobile view, because it has full window, compresse mode should be used.
	   If multiline text (multiline textblock or sliding mode)
	   is used, use compress mode for compressing width to fit the viewport width. */

	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
	printf("Compress mode enabled\n");

	evas_object_event_callback_add(genlist, EVAS_CALLBACK_MOUSE_DOWN, gl_mouse_down_cb, NULL);
	evas_object_smart_callback_add(genlist, "realized", gl_realized_cb, NULL);
	evas_object_smart_callback_add(genlist, "loaded", gl_loaded_cb, NULL);
	evas_object_smart_callback_add(genlist, "selected", gl_selected_cb, NULL);
	evas_object_smart_callback_add(genlist, "longpressed", gl_longpressed_cb, NULL);

	for (index = 0; index < n_items; index++)
	{
		item_data_s *id = calloc(sizeof(item_data_s), 1);
		id->index = index;
		it = elm_genlist_item_append(genlist, // genlist object
						itc,  // item class
						id,   // item class user data
						NULL,
						ELM_GENLIST_ITEM_NONE, // item type
						NULL, // select smart callback
						id);  // smart callback user data
		id->item = it;
		if (index == 0) elm_object_item_disabled_set(it, EINA_TRUE);
	}

	elm_genlist_item_class_free(itc);

	elm_naviframe_item_push(nf, style, NULL, NULL, genlist, NULL);
}

void genlist_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *list_items[] = {
		"type1",
		"type2",
		"multiline",
		"full",
		NULL
	};

	Evas_Object *list;
	Evas_Object *nf = data;
	int i;

	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);

	for (i = 0; list_items[i]; i++) {
		elm_list_item_append(list, list_items[i], NULL, NULL, genlist_test_cb, nf);
	}

	elm_list_go(list);

	elm_naviframe_item_push(nf, "Genlist", NULL, NULL, list, NULL);
}
