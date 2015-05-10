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

#define NUM_OF_ITEMS 8000

typedef struct item_data
{
	 int index;
	 Elm_Object_Item *item;
} item_data_s;

typedef struct item_data_select_all
{
	int index;
	Elm_Object_Item *item;
	Evas_Object *layout;
	Eina_Bool state_pointer;
} item_data_select_all_s;

static void
gl_del_cb(void *data, Evas_Object *obj)
{
	/* FIXME: Unrealized callback can be called after this. */
	/* Accessing item_data_s can be dangerous on unrealized callback. */
	item_data_s *id = data;
	free(id);
}

static Evas_Object*
create_image(Evas_Object *parent)
{
	Evas_Object *img = elm_image_add(parent);
	elm_image_file_set(img, ICON_DIR"/iu.png", NULL);
	evas_object_size_hint_align_set(img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(img, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	return img;
}

static Evas_Object*
gl_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	item_data_s *id = data;
	const Elm_Genlist_Item_Class *itc = elm_genlist_item_item_class_get(id->item);
	Evas_Object *content = create_image(obj);

	evas_object_size_hint_min_set(content, 50, 50);
	evas_object_size_hint_max_set(content, 50, 50);

	if (strstr(itc->item_style, "group_index")) return NULL;
	if (strstr(itc->item_style, "full")) return content;
	if (rand() % 2) return NULL;

	return content;
}

static char*
gl_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	const char *demo_names[] = {
		"CARSTEN HAITZLER Raster Cedric Bail SubhransuSekhar Mohanty Theip Ha Jean Philippe Andre",
		"Aamir", "Aaralyn", "Aaron", "Abagail",
		"Rajesh PS SHILPA ONKAR SINGH PRINCE KUMAR DUBEY Amit Kamboj Shashank Pandey",
		"Tom Hacohen Stefan Schmidt JackDanielZ Michael Blumenkrantz",
		"Babitha", "Bahuratna", "Bandana", "Bulbul", "Cade", "Caldwell",
		"CaptainFantasticFasterThanSupermanSpidermanBatmanWolverineHulkAndTheFlashCombined",
		"Chandan", "Caster", "Dagan ", "Daulat", "Dag", "Earl", "Ebenzer",
		"Ellison", "Elizabeth", "Filbert", "Fitzpatrick", "Florian", "Fulton",
		"Frazer", "Gabriel", "Gage", "Galen", "Garland", "Gauhar", "Hadden",
		"Hafiz", "Hakon", "Haleem", "Hank", "Hanuman", "Jabali ", "Jaimini",
		"Jayadev", "Jake", "Jayatsena", "Jonathan", "Kamaal", "Jeirk",
		"Jasper", "Jack", "Mac", "Macy", "Marlon", "Milson",
		"Aaliyah", "Aamir", "Aaralyn", "Aaron", "Abagail",
		"Babitha", "Bahuratna", "Bandana", "Bulbul", "Cade", "Caldwell",
		"Chandan", "Caster", "Dagan ", "Daulat", "Dag", "Earl", "Ebenzer",
		"Ellison", "Elizabeth", "Filbert", "Fitzpatrick", "Florian", "Fulton",
		"Frazer", "Gabriel", "Gage", "Galen", "Garland", "Gauhar", "Hadden",
		"Hafiz", "Hakon", "Haleem", "Hank", "Hanuman", "Jabali ", "Jaimini",
		"Jayadev", "Jake", "Jayatsena", "Jonathan", "Kamaal", "Jeirk",
		"Jasper", "Jack", "Mac", "Macy", "Marlon", "Milson",
		NULL
	};

	const char *long_txt[] = {
		"Hey John, how have you been?",
		"Andy, it's been a long time, how are you man?",
		"I finally have some free time. I just finished taking a big examination, and I'm so relieved that I'm done with it",
		"Wow. How long has it been? It seems like more than a year. I'm doing pretty well. How about you?",
		"I'm playing a video game on my computer because I have nothing to do.",
		"I'm pretty busy right now. I'm doing my homework because I have an exam tomorrow.",
		"I'm taking the day off from work today because I have so many errands. I'm going to the post office to send some packages to my friends.",
		NULL
	};

	item_data_s *id = data;
	const Elm_Genlist_Item_Class *itc = elm_genlist_item_item_class_get(id->item);
	char buf[1024];
	size_t size = sizeof(demo_names)/sizeof(char *) - 1;

	if (strstr(itc->item_style, "group_index")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "GROUP %d", ((id->index)/7) + 1);
			return strdup(buf);
		}
	} else if (strstr(itc->item_style, "default")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, demo_names[id->index % size]);
			return strdup(buf);
		}
	} else if (strstr(itc->item_style, "default_style")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, demo_names[id->index % size]);
			return strdup(buf);}
	} else if (strstr(itc->item_style, "double_label")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, demo_names[id->index % size]);
			return strdup(buf);
		}
		else if(!strcmp(part, "elm.text.sub")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, long_txt[id->index % size]);
			return strdup(buf);
		}
		else { }
	} else if (strstr(itc->item_style, "one_icon")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, demo_names[id->index % size]);
			return strdup(buf);
		}
	} else if (strstr(itc->item_style, "end_icon")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, demo_names[id->index % size]);
			return strdup(buf);
		}
	} else if (strstr(itc->item_style, "message")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, demo_names[id->index % size]);
			return strdup(buf);
		}
		else if (!strcmp(part, "elm.title.1")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, long_txt[id->index % size]);
			return strdup(buf);
		}
		else if(!strcmp(part, "elm.title.2")) {
			snprintf(buf, 1023, "[%d]%s:%s", id->index, part, long_txt[id->index % size]);
			return strdup(buf);
		} else { }
	} else { }

	return NULL;
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
	int n_items = NUM_OF_ITEMS;
	int index;
	Elm_Object_Item *it = event_info;
	Evas_Object *genlist;
	Evas_Object *nf = data;
	const char *style = elm_object_item_text_get(it);
	Elm_Genlist_Item_Class *itc2 = elm_genlist_item_class_new();

	printf("Item style: %s\n", style);
	elm_list_item_selected_set(it, EINA_FALSE);

	/* Create item class */
	Elm_Genlist_Item_Class *itc = elm_genlist_item_class_new();
	itc->item_style = style;
	itc->func.content_get = gl_content_get_cb;
	itc->func.text_get = gl_text_get_cb;
	itc->func.del = gl_del_cb;

	if (strstr(itc->item_style, "group_index")) {
		itc2->item_style = "default";
		itc2->func.content_get = gl_content_get_cb;
		itc2->func.text_get = gl_text_get_cb;
		itc2->func.del = gl_del_cb;
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

	for (index = 0; index < n_items; index++) {
		item_data_s *id = calloc(sizeof(item_data_s), 1);
		id->index = index;
		if (strstr(itc->item_style, "group_index")) {
			if (index % 7 == 0)
				it = elm_genlist_item_append(genlist,					/* genlist object */
												itc,						/* item class */
												id,							/* item class user data */
												NULL,
												ELM_GENLIST_ITEM_NONE,		/* item type */
												NULL,						/* select smart callback */
												id);						/* smart callback user data */
			else
				it = elm_genlist_item_append(genlist,					/* genlist object */
												itc2,						/* item class */
												id,							/* item class user data */
												NULL,
												ELM_GENLIST_ITEM_NONE,		/* item type */
												NULL,						/* select smart callback */
												id);						/* smart callback user data */
		}
		else {
			it = elm_genlist_item_append(genlist,					/* genlist object */
											itc,						/* item class */
											id,							/* item class user data */
											NULL,
											ELM_GENLIST_ITEM_NONE,		/* item type */
											NULL,						/* select smart callback */
											id);						/* smart callback user data */
		}
		id->item = it;
		if (index == 0) elm_object_item_disabled_set(it, EINA_TRUE);
	}

	elm_genlist_item_class_free(itc);

	elm_naviframe_item_push(nf, style, NULL, NULL, genlist, NULL);
}

void
genlist_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *list_items[] = {
		"default",
		"default_style",
		"double_label",
		"end_icon",
		"full",
		"group_index",
		"one_icon",
		"message",
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

	elm_naviframe_item_push(nf, "Item Styles", NULL, NULL, list, NULL);
}
