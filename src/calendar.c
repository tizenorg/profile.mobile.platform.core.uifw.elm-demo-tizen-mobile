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

static Evas_Object*
create_calendar(Evas_Object *nf)
{
	Evas_Object *calendar;
	time_t the_time;

	time(&the_time); /* Get Current Time */

	calendar = elm_calendar_add(nf);
	elm_calendar_first_day_of_week_set(calendar, ELM_DAY_SUNDAY);
	evas_object_size_hint_weight_set(calendar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_calendar_selected_time_set(calendar, gmtime(&the_time));
	elm_calendar_min_max_year_set(calendar, 1973, 2030);

	return calendar;
}

void
calendar_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *calendar;
	Evas_Object *nf = data;

	calendar = create_calendar(nf);
	elm_naviframe_item_push(nf, "Calendar", NULL, NULL, calendar, NULL);
}
