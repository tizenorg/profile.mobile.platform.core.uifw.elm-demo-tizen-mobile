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


typedef struct __my_struct
{
   Evas_Object *rect;
   Evas_Object *hit_rect;
   Evas_Object *scr;
   Evas_Object *label;
} _my_struct;

_my_struct my_st;

static Eina_Bool
_timer_cb(void *data)
{
   static int i;
   char buf[30];

   _my_struct *my_st = (_my_struct *) data;

   Evas_Object *rect = my_st->rect;
   Evas_Object *scr = my_st->scr;
   Evas_Object *label = my_st->label;
   Evas_Object *hit_rect = my_st->hit_rect;
   Evas_Coord rect_s;
   Evas_Coord hit_rect_s;

   i++;

   switch (i & 0x3)
   {
     case 0: {
       rect_s = 300;
       hit_rect_s = 300;
       break;
     }
     case 1: {
       rect_s = 500;
       hit_rect_s = 300;
       break;
     }
     case 2: {
       rect_s = 500;
       hit_rect_s = 500;
       break;
     }
     default: {
       rect_s = 300;
       hit_rect_s = 500;
     }
   }

   if ((i & 0x4) >> 2)
{
   evas_object_size_hint_min_set(hit_rect, ELM_SCALE_SIZE(720), ELM_SCALE_SIZE(hit_rect_s));
   evas_object_size_hint_min_set(rect, ELM_SCALE_SIZE(720), ELM_SCALE_SIZE(rect_s));
   snprintf(buf, sizeof(buf), "case[%d:%d] hit[%d] con[%d]", (i & 0x4) >> 2, i & 0x3, hit_rect_s, rect_s);
}
   else
{
   evas_object_size_hint_min_set(rect, ELM_SCALE_SIZE(720), ELM_SCALE_SIZE(rect_s));
   evas_object_size_hint_min_set(hit_rect, ELM_SCALE_SIZE(720), ELM_SCALE_SIZE(hit_rect_s));
   snprintf(buf, sizeof(buf), "case[%d:%d] con[%d] hit[%d]", (i & 0x4) >> 2, i & 0x3, rect_s, hit_rect_s);
}
   elm_object_text_set(label, buf);

   return EINA_TRUE; 
}

static Evas_Object*
create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
        elm_layout_theme_set(scroller, "scroller", "base", "effect");
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(scroller);

	return scroller;
}

static Evas_Object*
create_button_view(Evas_Object *parent)
{
	Evas_Object *layout, *btn, *img, *box, *box2;

	/* outer box */
	box = elm_table_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(box);

        Evas_Object *rect, *hit_rect;
        hit_rect = evas_object_rectangle_add(evas_object_evas_get(box));
        evas_object_color_set(hit_rect, 255, 0, 0, 255);
        evas_object_size_hint_min_set(hit_rect, ELM_SCALE_SIZE(720), ELM_SCALE_SIZE(300));
        elm_table_pack(box, hit_rect, 0, 0, 1, 1);
        evas_object_show(hit_rect);

        Evas_Object *scroller;

        scroller = create_scroller(box);
        elm_table_pack(box, scroller, 0, 0, 1, 1);


        rect = evas_object_rectangle_add(evas_object_evas_get(scroller));
        evas_object_color_set(rect, 255, 255, 0, 255);
        evas_object_size_hint_min_set(rect, ELM_SCALE_SIZE(720), ELM_SCALE_SIZE(300));
        evas_object_size_hint_align_set(rect, -1, 0.5);
	elm_object_content_set(scroller, rect);
        evas_object_show(rect);


        Evas_Object *label;
        label = elm_label_add(box);
        evas_object_size_hint_align_set(label, 0.5, 0.5);
        elm_table_pack(box, label, 0, 0, 1, 1);
        elm_object_text_set(label, "default");
        evas_object_show(label);

        my_st.rect = rect;
        my_st.scr = scroller;
        my_st.hit_rect = hit_rect;
        my_st.label = label;
        ecore_timer_add(3.0, _timer_cb, &my_st);

        evas_object_move(box, 0, ELM_SCALE_SIZE(300));

	return box;
}

void
button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *box;
	Evas_Object *nf = data;

	box = create_button_view(nf);

//	elm_naviframe_item_push(nf, "Button", NULL, NULL, , NULL);
}
