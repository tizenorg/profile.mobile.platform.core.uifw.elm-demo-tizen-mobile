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

static void
radio_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	int value = 0;
	printf("Selected Radio:%d\n", (int)data);
	value = elm_radio_value_get(obj);
	/* will print the value assigned to the currently selected radio */
	printf("selected value for the group:%d\n", value);
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);

	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

static Evas_Object*
create_radios(Evas_Object *parent)
{
	Evas_Object *radio, *radio_group;
	Evas_Object *layout;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "radio_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* adding a radio instance */
	radio = elm_radio_add(layout);
	elm_object_part_content_set(layout, "radio1", radio);

	/* assigning a unique value(within the group) to the radio instance */
	elm_radio_state_value_set(radio, 10);
	evas_object_smart_callback_add(radio, "changed", radio_changed_cb, (void *)1);

	/* creating a radio group with first radio */
	radio_group = radio;

	radio = elm_radio_add(layout);

	/* assigning a unique value(within the group) to the radio instance */
	elm_radio_state_value_set(radio, 20);

	/* adding this radio to the group containing the first radio */
	elm_radio_group_add(radio, radio_group);
	elm_object_part_content_set(layout, "radio2", radio);
	evas_object_smart_callback_add(radio, "changed", radio_changed_cb, (void *)2);

	radio = elm_radio_add(layout);

	/* assigning a unique value(within the group) to the radio instance */
	elm_radio_state_value_set(radio, 30);

	/* adding this radio to the group containing the first radio */
	elm_radio_group_add(radio, radio_group);
	elm_object_part_content_set(layout, "radio3", radio);
	evas_object_smart_callback_add(radio, "changed", radio_changed_cb, (void *)3);

	radio = elm_radio_add(layout);

	/* assigning a unique value(within the group) to the radio instance */
	elm_radio_state_value_set(radio, 40);

	/* adding this radio to the group containing the first radio */
	elm_radio_group_add(radio, radio_group);
	elm_object_part_content_set(layout, "radio4", radio);
	elm_object_disabled_set(radio, EINA_TRUE);
	evas_object_smart_callback_add(radio, "changed", radio_changed_cb, (void *)4);

	/* selecting the second radio in the group with value set to 10. This will set the 2nd radio instance */
	elm_radio_value_set(radio_group, 10);

	return layout;
}

void
radio_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	layout = create_radios(scroller);
	elm_object_content_set(scroller, layout);
	elm_naviframe_item_push(nf, "Normal styles", NULL, NULL, scroller, NULL);
}
