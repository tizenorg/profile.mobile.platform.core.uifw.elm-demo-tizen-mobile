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
create_calendar(Evas_Object *nf)
{
	Evas_Object *scroller, *box, *calendar;
	time_t the_time;

	time(&the_time); /* Get Current Time */

	scroller = elm_scroller_add(nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	box = elm_box_add(scroller);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(box);
	elm_object_content_set(scroller, box);

	calendar = elm_calendar_add(box);
	elm_calendar_first_day_of_week_set(calendar, ELM_DAY_SUNDAY);
	evas_object_size_hint_weight_set(calendar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(calendar, 0.5, 0);
	elm_calendar_selected_time_set(calendar, gmtime(&the_time));
	elm_calendar_min_max_year_set(calendar, 1973, 2030);
	evas_object_show(calendar);

	elm_box_pack_end(box, calendar);

	return scroller;
}

void
calendar_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout, *calendar;
	Evas_Object *nf = data;

	layout = elm_layout_add(nf);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "white_bg_layout");

	calendar = create_calendar(layout);
	elm_object_part_content_set(layout, "elm.swallow.content", calendar);

	elm_naviframe_item_push(nf, "Calendar", NULL, NULL, layout, NULL);
}
