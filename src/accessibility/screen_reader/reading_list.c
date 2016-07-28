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

typedef struct item_data
{
    Elm_Object_Item *item;
} item_data_s;

static Evas_Object*
group_check_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *check;
	item_data_s *id = data;

	if (!strcmp("elm.swallow.end", part))
	{
		check = elm_check_add(obj);
		evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_show(check);

		elm_atspi_accessible_relationship_append(check, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_DESCRIBED_BY, check);
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_CONTROLLER_FOR, check);

		return check;
	}
	return NULL;
}
static Evas_Object*
group_check_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];

	if (!strcmp("elm.text", part))
	{
		snprintf(buf, sizeof(buf), "Group index");
		return strdup(buf);
	}
	return NULL;
}

static Evas_Object*
group_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];

	if (!strcmp("elm.text", part))
	{
		snprintf(buf, sizeof(buf), "Group index");
		return strdup(buf);
	}
	else if (!strcmp("elm.text.end", part))
	{
		snprintf(buf, sizeof(buf), "sub text");
		return strdup(buf);
	}
	return NULL;
}


static Evas_Object*
full_slider_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
    item_data_s *id = data;
    Evas_Object *layout, *slider, *label;

    // Set custom layout style
    layout = elm_layout_add(obj);
    elm_layout_file_set(layout, ELM_DEMO_EDJ, "gl_custom_item");
    evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    // Set text into layout
    label = elm_label_add(obj);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(label, "Description Text");
    elm_object_part_content_set(layout, "elm.text", label);

    elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_LABELLED_BY, label);
    elm_atspi_accessible_relationship_append(label, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
    
	// Set slider into layout
    slider = elm_slider_add(obj);
    elm_slider_indicator_show_set(slider, EINA_FALSE);
    evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_slider_horizontal_set(slider, EINA_TRUE);
    elm_object_part_content_set(layout, "elm.swallow.content", slider);

	elm_atspi_accessible_relationship_append(slider, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
	elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_DESCRIBED_BY, slider);
	elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_CONTROLLER_FOR, slider);

	return layout;
}


static Evas_Object*
full_entry_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
    item_data_s *id = data;
    Evas_Object *layout, *entry, *label;

    // Set custom layout style
    layout = elm_layout_add(obj);
    elm_layout_file_set(layout, ELM_DEMO_EDJ, "gl_custom_item");
    evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    // Set text into layout
    label = elm_label_add(obj);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(label, "Description Text");
    elm_object_part_content_set(layout, "elm.text", label);

    elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_LABELLED_BY, label);
    elm_atspi_accessible_relationship_append(label, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
 
	entry = elm_entry_add(obj);
	elm_entry_entry_set(entry, "Text field");
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_slider_horizontal_set(entry, EINA_TRUE);
	elm_object_part_content_set(layout, "elm.swallow.content", entry);

	elm_atspi_accessible_relationship_append(entry, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
	elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_DESCRIBED_BY, entry);
	elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_CONTROLLER_FOR, entry);

	return layout;
}


static Evas_Object*
one_icon_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	item_data_s *id = data;
	Evas_Object *check;

	if (!strcmp("elm.swallow.icon", part))
	{
		check = elm_check_add(obj);
		evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_object_style_set(check, "on&off");
		evas_object_show(check);

		elm_atspi_accessible_relationship_append(check, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_DESCRIBED_BY, check);	
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_CONTROLLER_FOR, check);

		return check;
	}
	return NULL;
}

static Evas_Object*
one_icon_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];

	if (!strcmp("elm.text", part))
	{
		snprintf(buf, sizeof(buf), "Description Text");
		return strdup(buf);
	}
	return NULL;
}

static Evas_Object*
one_icon_check_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *check;
	item_data_s *id = data;

	if (!strcmp("elm.swallow.icon", part))
	{
		check = elm_check_add(obj);
		evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_show(check);
		
		elm_atspi_accessible_relationship_append(check, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_DESCRIBED_BY, check);	
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_CONTROLLER_FOR, check);

		return check;
	}
	return NULL;
}


static Evas_Object*
type1_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *check;
	item_data_s *id = data;

	if (!strcmp("elm.swallow.end", part))
	{
		check = elm_check_add(obj);
		evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_object_style_set(check, "on&off");
		evas_object_show(check);

		elm_atspi_accessible_relationship_append(check, ELM_ATSPI_RELATION_CONTROLLED_BY, id->item);
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_DESCRIBED_BY, check);
		elm_atspi_accessible_relationship_append(id->item, ELM_ATSPI_RELATION_CONTROLLER_FOR, check);

		return check;
	}
	return NULL;
}


static Evas_Object*
type1_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];

	if (!strcmp("elm.text", part))
	{
		snprintf(buf, sizeof(buf), "Description Text");
		return strdup(buf);
	}
	return NULL;
}

static void
gl_del_cb(void *data, Evas_Object *obj)
{
	/* Unrealized callback can be called after this. */
	/* Accessing item_data_s can be dangerous on unrealized callback. */
	item_data_s *id = data;
	free(id);
}

static Evas_Object* create_list(Evas_Object *parent)
{
	Evas_Object *nf = parent;
	Evas_Object *genlist = NULL;
	Elm_Genlist_Item_Class *itc = NULL;
	int index = 0;
	Elm_Genlist_Item_Type itemtype = 0;

	genlist = elm_genlist_add(nf);
	elm_genlist_block_count_set(genlist, 14);

	for( index = 0; index < 7; index++)
	{
	
		itc = elm_genlist_item_class_new();
		itc->func.del = gl_del_cb;

		switch(index)
		{
		case 0:
			itc->item_style = "group_index";
			itc->func.content_get = group_check_content_get_cb;
			itc->func.text_get = group_check_text_get_cb;
		break;
		case 1:
			itc->item_style = "full";
			itc->func.content_get = full_slider_content_get_cb;
			itc->func.text_get = NULL;
			
			break;
		case 2:
			itc->item_style = "full";
			itc->func.content_get = full_entry_content_get_cb;
			itc->func.text_get = NULL;
		break;
		case 3:
			itc->item_style = "group_index";
			itc->func.content_get = NULL;
			itc->func.text_get = group_text_get_cb;
		break;
		case 4:
			itc->item_style = "one_icon";
			itc->func.content_get = one_icon_content_get_cb;
			itc->func.text_get = one_icon_text_get_cb;
			break;
		case 5:
			itc->item_style = "one_icon";
			itc->func.content_get = one_icon_check_content_get_cb;
			itc->func.text_get = one_icon_text_get_cb;
			break;
		case 6:
			itc->item_style = "type1";
			itc->func.content_get = type1_content_get_cb;
			itc->func.text_get = type1_text_get_cb;
			break;
		}	

		if(!strcmp(itc->item_style, "group_index"))
			itemtype = ELM_GENLIST_ITEM_GROUP;
		else
			itemtype = ELM_GENLIST_ITEM_NONE;

		item_data_s *id = calloc(sizeof(item_data_s),1);
		Elm_Object_Item *it = elm_genlist_item_append(genlist, // genlist object
									itc,  // item class 
									id,   // item class user data
									NULL, // parent
									itemtype, // item type
									NULL, // select smart callback
									id);  // smart callback user data
		id->item = it;
		elm_genlist_item_class_free(itc);	
	}

	return genlist;
}


void
reading_list_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout;
	Evas_Object *nf = data;

	elm_theme_extension_add(NULL, ELM_DEMO_EDJ);
	layout = create_list(nf);
	elm_naviframe_item_push(nf, "List Sample", NULL, NULL, layout, NULL);
}

