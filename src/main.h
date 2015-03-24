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

#ifndef __DEF_elm_demo_H_
#define __DEF_elm_demo_H_

#include <Elementary.h>
#include <efl_extension.h>

typedef struct _widget_item
{
    char *name;
    Evas_Object* (*func)(void *data);
    void (*del_func)(void *data);
    char **styles;
    char **it_styles;

} widget_item;

typedef struct _appdata
{
    Evas_Object *win;
    Evas_Object *conform;
    Evas_Object *naviframe;
    Evas_Object *widget_box;
    Evas_Object *option_box;
    Evas_Object *style_hov;
    Evas_Object *item_hov;

} appdata;

Evas_Object *bg_cb(void *data);
Evas_Object *button_cb(void *data);
Evas_Object *checkbox_cb(void *data);
Evas_Object *colorselector_cb(void *data);
Evas_Object *ctxpopup_cb(void *data);
Evas_Object *datetime_cb(void *data);
Evas_Object *entry_cb(void *data);
Evas_Object *gengrid_cb(void *data);
Evas_Object *genlist_cb(void *data);
Evas_Object *index_cb(void *data);
Evas_Object *label_cb(void *data);
Evas_Object *hoversel_cb(void *data);
Evas_Object *layout_cb(void *data);
Evas_Object *multibuttonentry_cb(void *data);
Evas_Object *panel_cb(void *data);
Evas_Object *popup_cb(void *data);
Evas_Object *progressbar_cb(void *data);
Evas_Object *radio_cb(void *data);
Evas_Object *scroller_cb(void *data);
Evas_Object *slider_cb(void *data);
Evas_Object *spinner_cb(void *data);
Evas_Object *toolbar_cb(void *data);
Evas_Object *tooltip_cb(void *data);

void button_del_cb(void *data);
void checkbox_del_cb(void *data);
void ctxpopup_del_cb(void *data);
void datetime_del_cb(void *data);
void entry_del_cb(void *data);
void gengrid_del_cb(void *data);
void genlist_del_cb(void *data);
void hoversel_del_cb(void *data);
void layout_del_cb(void *data);
void popup_del_cb(void *data);
void progressbar_del_cb(void *data);
void radio_del_cb(void *data);
void scroller_del_cb(void *data);
void slider_del_cb(void *data);
void tooltip_del_cb(void *data);

void table_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);

#endif /* __DEF_elm_demo_H__ */
