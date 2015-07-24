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
create_embeded_ui(Evas_Object *parent)
{
	//LOGD("Creating embedded UI");
	Evas_Object *bx;
	bx = elm_box_add(parent);
	evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(bx);
	return bx;
}

void create_win_socket(Evas_Object *nf)
{
	Evas_Object *win_socket;
	/* for socket window */

	win_socket = elm_win_add(NULL, "Window Socket", ELM_WIN_SOCKET_IMAGE);

	if (!elm_win_socket_listen(win_socket, "hello", 0, EINA_FALSE))
	  {
		 printf("Fail to elm win socket listen \n");
		 evas_object_del(win_socket);
		 return;
	  }
	elm_win_title_set(win_socket, "Window Socket");
	elm_win_autodel_set(win_socket, EINA_TRUE);
	Evas_Object *bg, *sc, *bx, *en;

	bg = elm_bg_add(win_socket);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win_socket, bg);
	evas_object_show(bg);

	sc = elm_scroller_add(win_socket);
	evas_object_size_hint_weight_set(sc, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win_socket, sc);

	bx = elm_box_add(win_socket);
	evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

	en = elm_button_add(win_socket);
	evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
	elm_object_text_set(en, "Button 1");
	evas_object_show(en);
	elm_box_pack_end(bx, en);

	en = elm_button_add(win_socket);
	evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
	elm_object_text_set(en, "Button 2");
	evas_object_show(en);
	elm_box_pack_end(bx, en);
	evas_object_resize(win_socket, 500, 500);
	evas_object_show(win_socket);
}
void plug_move_resize(void *data, Evas *evas, Evas_Object *eo, void *event_info)
{
	Evas_Object * rect = data;
	Evas_Coord x,y,w,h;
	evas_object_geometry_get(eo,&x, &y, &w, &h);

	//LOGD("Moving rec to x: %i, y: %i, w: %i, h:%i", x,y,w,h);

	evas_object_geometry_set(rect,x,y,w,h);
}

void create_win_plug(Evas_Object *box)
{
	Evas_Object *plug;
	plug = elm_plug_add(box);
	if (!elm_plug_connect(plug, "hello", 0, EINA_FALSE))
	  {
		 printf("Cannot connect plug\n");
		 return;
	  }
	evas_object_size_hint_weight_set(plug, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(plug, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(plug);
	elm_box_pack_end(box, plug);

	evas_object_resize(plug, 380, 500);
	evas_object_move(plug, 10, 10);
}

void
embeded_ui_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *scroller, *box;
	Evas_Object *nf = data;

	scroller = create_scroller(nf);
	box = create_embeded_ui(scroller);
	elm_object_content_set(scroller, box);

	create_win_socket(nf);
	create_win_plug(box);

	elm_naviframe_item_push(nf, "Embeded UI", NULL, NULL, scroller, NULL);
}
