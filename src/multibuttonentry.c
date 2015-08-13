/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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
btn1_clicked_cb(void *data , Evas_Object *obj, void *event_info)
{
	Evas_Object *mbe = data;
	Elm_Object_Item *clicked_item;

	clicked_item = elm_multibuttonentry_selected_item_get(mbe);

	if (elm_object_item_disabled_get(clicked_item)) {
		elm_object_item_disabled_set(clicked_item, EINA_FALSE);
	} else {
		elm_object_item_disabled_set(clicked_item, EINA_TRUE);
	}
}

static void
btn2_clicked_cb(void *data , Evas_Object *obj, void *event_info)
{
	Evas_Object *mbe = data;

	if (elm_object_disabled_get(mbe)) {
		elm_object_disabled_set(mbe, EINA_FALSE);
		elm_object_text_set(obj, "MBE Disable");
	} else {
		elm_object_disabled_set(mbe, EINA_TRUE);
		elm_object_text_set(obj, "MBE Enable");
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
mbe_item_filter_cb(Evas_Object *obj, const char* item_label, void *item_data, void *data)
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
create_scroller(Evas_Object* parent)
{
	Evas_Object *scroller;

	/* scroller */
	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(scroller);

	return scroller;
}

static Evas_Object*
create_multibuttonentry(Evas_Object* parent, Evas_Object *scroller)
{
	Evas_Object *mbe;

	/* add a multibuttonentry object */
	mbe = elm_multibuttonentry_add(parent);
	elm_object_text_set(mbe, "To: ");
	elm_object_part_text_set(mbe, "guide", "Tap to add recipient");
	evas_object_size_hint_weight_set(mbe, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(mbe, EVAS_HINT_FILL, 0.0);
	evas_object_show(mbe);

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

	elm_object_content_set(scroller, mbe);

	return mbe;
}

static Evas_Object*
create_checks(Evas_Object *parent, Evas_Object *mbe)
{
	Evas_Object *layout, *box, *check;

	box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_show(box);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "check_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	check = elm_check_add(layout);
	elm_object_text_set(check, "Editable");
	elm_check_state_set(check, EINA_TRUE);
	evas_object_smart_callback_add(check, "changed", check_changed_cb, mbe);
	evas_object_show(check);

	elm_object_part_content_set(layout, "elm.swallow.content", check);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);


	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "check_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	check = elm_check_add(layout);
	elm_object_text_set(check, "Expanded");
	elm_check_state_set(check, EINA_TRUE);
	evas_object_smart_callback_add(check, "changed", check_changed_cb, mbe);
	evas_object_show(check);

	elm_object_part_content_set(layout, "elm.swallow.content", check);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	return box;
}

static Evas_Object *
create_buttons(Evas_Object *parent, Evas_Object *mbe)
{
	Evas_Object *layout, *box, *btn1, *btn2;

	//Box (Button 1, Button 2)
	box = elm_box_add(parent);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.3);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0);
	evas_object_show(box);

	//Button 1
	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_1");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	btn1 = elm_button_add(layout);
	elm_object_text_set(btn1, "Item On/Off");
	evas_object_smart_callback_add(btn1, "clicked", btn1_clicked_cb, mbe);
	evas_object_show(btn1);

	elm_object_part_content_set(layout, "elm.swallow.content", btn1);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	//Button 2
	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_1");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	btn2 = elm_button_add(layout);
	elm_object_text_set(btn2, "MBE Disable");
	evas_object_smart_callback_add(btn2, "clicked", btn2_clicked_cb, mbe);
	evas_object_show(btn2);

	elm_object_part_content_set(layout, "elm.swallow.content", btn2);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	return box;
}

void
multibuttonentry_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *mbe, *box, *box2, *box3, *layout;
	Evas_Object *nf = data;

	layout = elm_layout_add(nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	box = elm_box_add(layout);
	elm_box_padding_set(box, ELM_SCALE_SIZE(10), ELM_SCALE_SIZE(20));
	elm_object_part_content_set(layout, "elm.swallow.content", box);
	scroller = create_scroller(box);
	mbe = create_multibuttonentry(box, scroller);
	elm_box_pack_end(box, scroller);
	box2 = create_checks(box, mbe);
	elm_box_pack_end(box, box2);
	box3 = create_buttons(box, mbe);
	elm_box_pack_end(box, box3);

	elm_naviframe_item_push(nf, "Multibuttonentry", NULL, NULL, layout, NULL);
}
