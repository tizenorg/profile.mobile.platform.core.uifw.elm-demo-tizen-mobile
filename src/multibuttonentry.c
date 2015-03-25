/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
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
check_changed_cb(void *data , Evas_Object *obj , void *event_info)
{
	Evas_Object *mbe = data;

	if (!strcmp(elm_object_text_get(obj), "Editable"))
		elm_multibuttonentry_editable_set(mbe, elm_check_state_get(obj));
	else if (!strcmp(elm_object_text_get(obj), "Expanded"))
		elm_multibuttonentry_expanded_set(mbe, elm_check_state_get(obj));
}

static void
btn_clicked_cb(void *data , Evas_Object *obj, void *event_info)
{
	Evas_Object *mbe = data;
	Elm_Object_Item *clicked_item;

	clicked_item = elm_multibuttonentry_selected_item_get(mbe);

	if (!strcmp(elm_object_text_get(obj), "Item Disabled"))
	{
		const Eina_List *items, *l;
		Elm_Object_Item *it;

		items = elm_multibuttonentry_items_get(mbe);

		EINA_LIST_FOREACH(items, l, it)
		{
			if (elm_object_item_disabled_get(it))
				elm_object_item_disabled_set(it, EINA_FALSE);
			else
				elm_object_item_disabled_set(it, EINA_TRUE);
		}
	}
	else if (!strcmp(elm_object_text_get(obj), "MBE Disabled"))
	{
		if (elm_object_disabled_get(mbe))
			elm_object_disabled_set(mbe, EINA_FALSE);
		else
			elm_object_disabled_set(mbe, EINA_TRUE);
	}
}

static void
refresh_end_text(Evas_Object *obj)
{
	Evas_Object *end, *entry;
	const char *end_text, *entry_text;
	char buf[1024];

	end = (Evas_Object *)evas_object_data_get(obj, "end");
	entry = elm_multibuttonentry_entry_get(obj);
	if (end) {
		entry_text = elm_object_text_get(entry);
		end_text = elm_object_text_get(end);
		if (entry_text && strlen(entry_text)) {
			if (end_text && strlen(end_text))
				snprintf(buf, sizeof(buf), "%s, %s", end_text, entry_text);
			else
				snprintf(buf, sizeof(buf), "%s", entry_text);
			elm_object_text_set(end, buf);
		}
	}
}

static void
mbe_item_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *item = (Elm_Object_Item *)event_info;
	printf("\nselected item = %s\n", elm_object_item_text_get(item));
}

static void
mbe_item_added_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *item = (Elm_Object_Item *)event_info;
	printf("\nadded item = %s\n", elm_object_item_text_get(item));

	refresh_end_text(obj);
}

static void
mbe_item_deleted_cb(void *data , Evas_Object *obj, void *event_info)
{
	printf("\ndeleted item!\n");
	refresh_end_text(obj);
}

static void
mbe_item_clicked_cb( void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *item = event_info;
	printf("\nclicked item = %s\n", elm_object_item_text_get(item));
}

static void
mbe_item_longpressed_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *item = event_info;
	printf("\npressed_item = %s\n", elm_object_item_text_get(item));
}

static void
mbe_clicked_cb( void *data, Evas_Object *obj,  void *event_info )
{
	printf("multibuttonentry is clicked!\n");
}

static void
mbe_focused_cb( void *data, Evas_Object *obj, void *event_info)
{
	printf("multibuttonentry is focused!\n");

	Evas_Object *end;
	end = (Evas_Object *)evas_object_data_get(obj, "end");
	if (end)
		elm_object_text_set(end, NULL);
}

static void
mbe_unfocused_cb( void *data, Evas_Object *obj, void *event_info)
{
	printf("multibuttonentry is unfocused!\n");
	refresh_end_text(obj);
}

static void
mbe_expanded_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("multibuttonentry is expanded!\n");
}

static void
mbe_contracted_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf("multibuttonentry is contracted!\n");
}

static void
mbe_expand_state_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	if (elm_multibuttonentry_expanded_get(obj))
		printf("\nexpand state changed: expanded!!\n");
	else
		printf("\nexpand state changed: shrinked!!\n");
}

static Eina_Bool
mbe_item_filter_cb(Evas_Object *obj, const char* item_label, const void *item_data, const void *data)
{
	printf("\"%s\" item will be added\n", item_label);

	char *str = strstr(item_label, "S");

	Evas_Object *end = (Evas_Object *)evas_object_data_get(obj, "end");
	if (end)
		elm_object_text_set(end, NULL);

	if (str)
		return EINA_FALSE;
	else
		return EINA_TRUE;
}

static Evas_Object*
create_scroller(Evas_Object* parent ,Evas_Object* mbe)
{
	Evas_Object* scroller;

	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);
	elm_object_content_set(scroller, mbe);
	return scroller;
}


static Evas_Object*
create_multibuttonentry(Evas_Object* parent)
{
	Evas_Object* mbe;

	/* add a multibuttonentry object */
	mbe = elm_multibuttonentry_add(parent);
	elm_object_text_set(mbe, "To: ");
	elm_object_part_text_set(mbe, "guide", "Tap to add recipient");
	evas_object_size_hint_weight_set(mbe, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(mbe, EVAS_HINT_FILL, 0.0);

	/* add item filter callback */
	elm_multibuttonentry_item_filter_append(mbe, mbe_item_filter_cb, NULL);

	/* add state-related callbacks */
	evas_object_smart_callback_add(mbe, "clicked", mbe_clicked_cb, NULL);
	evas_object_smart_callback_add(mbe, "focused", mbe_focused_cb, NULL);
	evas_object_smart_callback_add(mbe, "unfocused", mbe_unfocused_cb, NULL);

	/* add size-related callbacks */
	evas_object_smart_callback_add(mbe, "expanded", mbe_expanded_cb, NULL);
	evas_object_smart_callback_add(mbe, "contracted", mbe_contracted_cb, NULL);
	evas_object_smart_callback_add(mbe, "expand,state,changed", mbe_expand_state_changed_cb, NULL);

	/* add item-related callbacks */
	evas_object_smart_callback_add(mbe, "item,selected", mbe_item_selected_cb, NULL);
	evas_object_smart_callback_add(mbe, "item,added", mbe_item_added_cb, NULL);
	evas_object_smart_callback_add(mbe, "item,deleted", mbe_item_deleted_cb, NULL);
	evas_object_smart_callback_add(mbe, "item,clicked", mbe_item_clicked_cb, NULL);
	evas_object_smart_callback_add(mbe, "longpressed", mbe_item_longpressed_cb, NULL);

	elm_object_focus_set(mbe, EINA_TRUE);

	return mbe;
}

static Evas_Object*
create_checks(Evas_Object *parent, Evas_Object *mbe)
{
	Evas_Object *box, *check;

	box = elm_box_add(parent);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_show(box);

	check = elm_check_add(box);
	elm_object_style_set(check,"popup");
	elm_object_text_set(check, "Editable");
	elm_check_state_set(check, EINA_TRUE);
	evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(check, "changed", check_changed_cb, mbe);
	elm_box_pack_end(box, check);
	evas_object_show(check);

	check = elm_check_add(box);
	elm_object_style_set(check,"popup");
	elm_object_text_set(check, "Expanded");
	elm_check_state_set(check, EINA_TRUE);
	evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(check, "changed", check_changed_cb, mbe);
	elm_box_pack_end(box, check);
	evas_object_show(check);

	return box;
}

void
multibuttonentry_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout, *mbe, *scroller, *box;
	Evas_Object *btn1, *btn2;
	Evas_Object *nf = data;

	layout = elm_layout_add(nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "multibuttonentry_layout");
	elm_naviframe_item_push(nf, "Multibuttonentry", NULL, NULL, layout, NULL);

	mbe = create_multibuttonentry(layout );

	scroller = create_scroller(layout, mbe );
	elm_object_part_content_set(layout, "multibuttonentry", scroller);

	box = create_checks(layout, mbe);
	elm_object_part_content_set(layout, "check_box", box);

	btn1 = elm_button_add(layout);
	elm_object_text_set(btn1, "Item Disabled");
	evas_object_smart_callback_add(btn1, "clicked", btn_clicked_cb, mbe);
	evas_object_size_hint_weight_set(btn1, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(btn1, EVAS_HINT_FILL, 0.0);
	elm_object_part_content_set(layout, "btn1", btn1);
	evas_object_show(btn1);

	btn2 = elm_button_add(layout);
	elm_object_text_set(btn2, "MBE Disabled");
	evas_object_smart_callback_add(btn2, "clicked", btn_clicked_cb, mbe);
	evas_object_size_hint_weight_set(btn2, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(btn2, EVAS_HINT_FILL, 0.0);
	elm_object_part_content_set(layout, "btn2", btn2);
	evas_object_show(btn2);
}
