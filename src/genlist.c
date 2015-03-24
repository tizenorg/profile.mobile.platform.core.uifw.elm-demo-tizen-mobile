#include "main.h"

#define N_ITEMS 10
#define BUFFER_SIZE 256


char *_gl_item_styles[] =
{
    "default",
    "1text_1icon",
    "1text_1icon_2",
    "2text",
    "2text_1icon",
    "3text_1icon",
    "4text_1icon",
    "2text_1icon_2",
    "progress",
    "2text_2icon",
    NULL
};

static void _item_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Coord x = 0, y = 0, w = 0, h = 0;
    Eina_Bool visible;
    Elm_Object_Item *it = event_info;
    Evas_Object *track = elm_object_item_track(it);
    evas_object_geometry_get(track, &x, &y, &w, &h);

    visible = evas_object_visible_get(track);
    printf("sel item data [%p] on genlist obj [%p], item pointer [%p]\n",
            data, obj, event_info);
    printf("track geometry = (%d %d %d %d) visible(%d)\n",
           x, y, w, h, visible);
    elm_object_item_untrack(it);
}

static void _item_longpressed_cb(void *data, Evas_Object *obj, void *event_info)
{
    printf("item longpressed! %p \n", event_info);
}

static Evas_Object *_item_content_get_default(void *data, Evas_Object *obj, const char *part)
{
    Evas_Object *ic = NULL;

    if (!strcmp(part, "elm.swallow.icon"))
    {
        ic = elm_icon_add(obj);
        elm_icon_standard_set(ic, "clock");
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    }
    else if (!strcmp(part, "elm.swallow.content"))
    {
        ic = elm_icon_add(obj);
        elm_icon_standard_set(ic, "home");
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    }
    else if (!strcmp(part, "elm.swallow.icon.1"))
    {
        ic = elm_icon_add(obj);
        elm_icon_standard_set(ic, "folder");
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    }
    else if (!strcmp(part, "elm.swallow.icon.2"))
    {
        ic = elm_icon_add(obj);
        elm_icon_standard_set(ic, "home");
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    }
    else if (!strcmp(part, "elm.swallow.bottom"))
    {
        ic = elm_progressbar_add(obj);
        evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, 0.5);
    }
    else if (!strcmp(part, "elm.swallow.end"))
    {
        ic = elm_check_add(obj);
        elm_object_focus_allow_set(ic, EINA_FALSE);
        evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    }

    return ic;
}

static Evas_Object *_item_content_get_progress(void *data, Evas_Object *obj, const char *part)
{
    Evas_Object *ic = NULL;

    if (!strcmp(part, "elm.swallow.icon"))
    {
        ic = elm_progressbar_add(obj);
        elm_progressbar_span_size_set(ic, 200);
        evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        elm_object_style_set(ic, "default");
        evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, 0.5);
    }
    else if (!strcmp(part, "elm.swallow.end"))
    {
        ic = elm_check_add(obj);
        elm_object_focus_allow_set(ic, EINA_FALSE);
        evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    }

    return ic;
}

static char *_item_label_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[BUFFER_SIZE];

   if (!strcmp(part, "elm.text"))
   {
       if ((int) data == 0) sprintf(buf, "%s", "Time Warner Cable(Cable)");
       else if ((int) data == 1) sprintf(buf, "%s", "ComCast (Cable)");
       else if ((int) data == 2) sprintf(buf, "%s", "Dish (Satellite)");
       else if ((int) data == 3) sprintf(buf, "%s", "DirecTV (Satellite)");
       else if ((int) data == 4) sprintf(buf, "%s", "Tata Sky (Satellite)");
       else if ((int) data == 5) sprintf(buf, "%s", "Nextra Cable(Cable)");
       else if ((int) data == 6) sprintf(buf, "%s", "DD Plus (Cable)");
       else if ((int) data == 7) sprintf(buf, "%s", "Tikona Cable(Cable)");
       else if ((int) data == 8) sprintf(buf, "%s", "True Provider (Cable)");
       else if ((int) data == 9) sprintf(buf, "%s", "Vodafone (Satellite)");
       else sprintf(buf, "%s", "Sample Text");
   }
   else if (!strcmp(part, "elm.text2"))
   {
       sprintf(buf, "sub text (%d)", (int) data);
   }
   else if (!strcmp(part, "elm.text3"))
   {
       sprintf(buf, "sub text#2 (%d)", (int) data);
   }
   else if (!strcmp(part, "elm.text4"))
   {
       sprintf(buf, "sub text#3 (%d)", (int) data);
   }

   return strdup(buf);
}

static void _genlist_renew(Evas_Object *obj, const char *style)
{
    Elm_Genlist_Item_Class *ic;
    int i;

    if (!obj) return;

    elm_genlist_clear(obj);

    ic = elm_genlist_item_class_new();
    ic->item_style = style;
    ic->func.text_get = _item_label_get;
    if (!strcmp(style, "progress"))
        ic->func.content_get = _item_content_get_progress;
    else
        ic->func.content_get = _item_content_get_default;
    ic->func.state_get = NULL;
    ic->func.del = NULL;

    for (i = 0; i < N_ITEMS; i++)
        elm_genlist_item_append(obj, ic, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, _item_sel_cb, NULL);

    elm_genlist_item_class_free(ic);
}

static void
_gl_focus_item_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("genlist item focused: %s\n", elm_object_item_text_get(event_info));
}

static void
_gl_unfocus_item_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("genlist item unfocused: %s\n", elm_object_item_text_get(event_info));
}

static void
_gl_focus_key_down_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                      Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   printf("\n=== Key Down : %s ===\n", ev->keyname);
}

static void
_gl_it_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *gl = data;
    const char *txt = elm_object_item_text_get(event_info);
    elm_object_text_set(obj, txt);

    _genlist_renew(gl, txt);
}

void genlist_del_cb(void *data)
{
    appdata *ad = data;
    evas_object_smart_callback_del(ad->item_hov, "selected", _gl_it_selected);
}

Evas_Object *genlist_cb(void *data)
{
    Evas_Object *wbox, *gl;
    appdata *ad = data;

    wbox = ad->widget_box;

    gl = elm_genlist_add(wbox);
    evas_object_smart_callback_add(ad->item_hov, "selected", _gl_it_selected, gl);

    elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
    evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);

    _genlist_renew(gl, "default");
    evas_object_show(gl);

    evas_object_smart_callback_add(gl, "item,focused", _gl_focus_item_cb, "item,focused");
    evas_object_smart_callback_add(gl, "item,unfocused", _gl_unfocus_item_cb, "item,unfocused");
    evas_object_smart_callback_add(gl, "activated", _gl_focus_item_cb, "activated");
    evas_object_event_callback_add(gl, EVAS_CALLBACK_KEY_DOWN, _gl_focus_key_down_cb, NULL);
    evas_object_smart_callback_add(gl, "longpressed", _item_longpressed_cb, NULL);

    elm_box_pack_end(wbox, gl);

    return gl;
}
