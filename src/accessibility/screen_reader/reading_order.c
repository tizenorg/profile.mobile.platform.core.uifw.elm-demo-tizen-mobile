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
create_reading_order(Evas_Object *parent)
{
	Evas_Object *layout;
	Evas_Object *btnA;
	Evas_Object *btnB;
	Evas_Object *btnC;
	Evas_Object *btnD;
	Evas_Object *btnE;
	Evas_Object *labelCustom;

	Evas_Object *btnDefaultA;
	Evas_Object *btnDefaultB;
	Evas_Object *btnDefaultC;
	Evas_Object *btnDefaultD;
	Evas_Object *btnDefaultE;
	Evas_Object *labelDefault;

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "reading_order_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	labelCustom = elm_label_add(layout);
	elm_object_text_set(labelCustom, _("<font_size=33>Custom reading order</font_size>"));
	elm_object_part_content_set(layout, "custom_lbl", labelCustom);

	btnA = elm_button_add(layout);
	elm_object_text_set(btnA, "a");
	elm_object_part_content_set(layout, "button_a", btnA);


	btnB = elm_button_add(layout);
	elm_object_text_set(btnB, "b");
	elm_object_part_content_set(layout, "button_b", btnB);

	btnC = elm_button_add(layout);
	elm_object_text_set(btnC, "c");
	elm_object_part_content_set(layout, "button_c", btnC);

	btnD = elm_button_add(layout);
	elm_object_text_set(btnD, "d");
	elm_object_part_content_set(layout, "button_d", btnD);

	btnE = elm_button_add(layout);
	elm_object_text_set(btnE, "e");
	elm_object_part_content_set(layout, "button_e", btnE);


	labelDefault = elm_label_add(layout);
	elm_object_text_set(labelDefault, _("<font_size=33>Default reading order</font_size>"));
	elm_object_part_content_set(layout, "default_lbl", labelDefault);

	btnDefaultA = elm_button_add(layout);
	elm_object_text_set(btnDefaultA, "A");
	elm_object_part_content_set(layout, "button_default_a", btnDefaultA);


	btnDefaultB = elm_button_add(layout);
	elm_object_text_set(btnDefaultB, "B");
	elm_object_part_content_set(layout, "button_default_b", btnDefaultB);

	btnDefaultC = elm_button_add(layout);
	elm_object_text_set(btnDefaultC, "C");
	elm_object_part_content_set(layout, "button_default_c", btnDefaultC);

	btnDefaultD = elm_button_add(layout);
	elm_object_text_set(btnDefaultD, "D");
	elm_object_part_content_set(layout, "button_default_d", btnDefaultD);

	btnDefaultE = elm_button_add(layout);
	elm_object_text_set(btnDefaultE, "E");
	elm_object_part_content_set(layout, "button_default_e", btnDefaultE);

	// inform Assisitve Technology that UI information should be prosented in
	// following order:
	elm_atspi_accessible_relationship_append(labelCustom, ELM_ATSPI_RELATION_FLOWS_TO, btnD);

	elm_atspi_accessible_relationship_append(btnD, ELM_ATSPI_RELATION_FLOWS_TO, btnE);
	elm_atspi_accessible_relationship_append(btnE, ELM_ATSPI_RELATION_FLOWS_TO, btnB);
	elm_atspi_accessible_relationship_append(btnB, ELM_ATSPI_RELATION_FLOWS_TO, btnC);

	elm_atspi_accessible_relationship_append(btnC, ELM_ATSPI_RELATION_FLOWS_FROM, btnB);
	elm_atspi_accessible_relationship_append(btnB, ELM_ATSPI_RELATION_FLOWS_FROM, btnE);
	elm_atspi_accessible_relationship_append(btnE, ELM_ATSPI_RELATION_FLOWS_FROM, btnD);
	elm_atspi_accessible_relationship_append(btnD, ELM_ATSPI_RELATION_FLOWS_FROM, labelCustom);
	return layout;
}

void
reading_order_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *layout;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	layout = create_reading_order(scroller);
	elm_object_content_set(scroller, layout);

	elm_naviframe_item_push(nf, "UI Reading Order", NULL, NULL, scroller, NULL);
}
