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

static Evas_Object *
create_content(Evas_Object* parent)
{
	Evas_Object *scroller;
	Evas_Object *box, *layout;
	Evas_Object *slider;
	Evas_Object *label, *btn, *check;

	//Box
	box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, ELM_SCALE_SIZE(2));
	evas_object_show(box);


	label = elm_label_add(box);
	elm_object_text_set(label, _("<font_size=33><align=center>Button with default reading info</align></font_size>"));
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(box);
	elm_object_text_set(btn, _("IDS_BUTTON_NAME"));
	elm_atspi_accessible_description_set(btn, _("IDS_BUTTON_DESCRIPTION"));
	elm_atspi_accessible_translation_domain_set(btn, PACKAGE);
	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);
	evas_object_show(btn);

	label = elm_label_add(box);
	elm_object_text_set(label, _("<font_size=33><align=center>Button with role and description info only</align></font_size>"));
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, 0.5, 0);
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(box);
	elm_object_text_set(btn, _("IDS_BUTTON_NAME"));
	elm_atspi_accessible_description_set(btn, _("IDS_BUTTON_DESCRIPTION"));
	elm_atspi_accessible_translation_domain_set(btn, PACKAGE);
	elm_atspi_accessible_reading_information_set(btn, (ELM_ACCESSIBLE_INFO_ROLE | ELM_ACCESSIBLE_INFO_DESCRIPTION));
	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);
	evas_object_show(btn);

	label = elm_label_add(box);
	elm_object_text_set(label, _("<font_size=33><align=center>Button with name and description info only</align></font_size>"));
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(box);
	elm_object_text_set(btn, _("IDS_BUTTON_NAME"));
	elm_atspi_accessible_description_set(btn, _("IDS_BUTTON_DESCRIPTION"));
	elm_atspi_accessible_translation_domain_set(btn, PACKAGE);
	elm_atspi_accessible_reading_information_set(btn, (ELM_ACCESSIBLE_INFO_NAME | ELM_ACCESSIBLE_INFO_DESCRIPTION));
	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);
	evas_object_show(btn);

	label = elm_label_add(box);
	elm_object_text_set(label, _("<font_size=33><align=center>Button with description only</align></font_size>"));
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "button_layout_2");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	btn = elm_button_add(box);
	elm_object_text_set(btn, _("IDS_BUTTON_NAME"));
	elm_atspi_accessible_description_set(btn, _("IDS_BUTTON_DESCRIPTION"));
	elm_atspi_accessible_translation_domain_set(btn, PACKAGE);
	elm_atspi_accessible_reading_information_set(btn, (ELM_ACCESSIBLE_INFO_DESCRIPTION));
	elm_object_part_content_set(layout, "elm.swallow.content", btn);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);
	evas_object_show(btn);

	label = elm_label_add(box);
	elm_object_text_set(label, _("<font_size=33><align=center>Favourite button with deafult reading info</align></font_size>"));
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "check_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	check = elm_check_add(box);
	elm_object_style_set(check, "favorite");
	elm_atspi_accessible_name_set(check, _("IDS_FAVOURITE_NAME"));
	elm_atspi_accessible_translation_domain_set(check, PACKAGE);
	elm_object_text_set(check, "Favorite");
	elm_check_state_set(check, EINA_FALSE);
	evas_object_show(check);

	elm_object_part_content_set(layout, "elm.swallow.content", check);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);

	label = elm_label_add(box);
	elm_object_text_set(label, _("<font_size=33><align=center>Favourite button without state info</align></font_size>"));
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0);
	evas_object_show(label);
	elm_box_pack_end(box, label);

	layout = elm_layout_add(box);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "check_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, 0.5, 0);

	check = elm_check_add(box);
	elm_object_style_set(check, "favorite");
	elm_atspi_accessible_name_set(check, _("IDS_FAVOURITE_NAME"));
	elm_atspi_accessible_translation_domain_set(check, PACKAGE);
	elm_object_text_set(check, "Favorite");
	elm_check_state_set(check, EINA_FALSE);
	elm_atspi_accessible_reading_information_set(btn, (ELM_ACCESSIBLE_INFO_NAME | ELM_ACCESSIBLE_INFO_ROLE | ELM_ACCESSIBLE_INFO_DESCRIPTION));
	evas_object_show(check);

	elm_object_part_content_set(layout, "elm.swallow.content", check);
	evas_object_show(layout);
	elm_box_pack_end(box, layout);


	return box;

}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

void
overwrite_reading_info_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout, *content, *scroller, *bg_layout;
	Evas_Object *nf = data;
	scroller = create_scroller(nf);
	bg_layout = elm_layout_add(scroller);
	evas_object_size_hint_weight_set(bg_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(bg_layout, ELM_DEMO_EDJ, "white_bg_layout");

	layout = create_content(scroller);
	elm_object_part_content_set(bg_layout, "elm.swallow.content", layout);
	elm_object_content_set(scroller, bg_layout);

	elm_naviframe_item_push(nf, "Overwriting Reading Info", NULL, NULL, scroller, NULL);
}
