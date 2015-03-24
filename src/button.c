#include "main.h"
#include "util.h"


char *_btn_styles[] =
{
    "default",
    "text",
    NULL
};

static void
_btn_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *btn = data;
    const char *txt = elm_object_item_text_get(event_info);

    elm_object_style_set(btn, txt);
}

void button_del_cb(void *data)
{
    appdata *ad = data;
    evas_object_smart_callback_del(ad->style_hov, "selected", _btn_selected);
}

Evas_Object *button_cb(void *data)
{
    Evas_Object *wbox, *btn;
    appdata *ad = data;

    wbox = ad->widget_box;

    btn = elm_button_add(wbox);
    elm_object_text_set(btn, "Button");
    evas_object_show(btn);
    elm_box_pack_end(wbox, btn);

    evas_object_smart_callback_add(ad->style_hov, "selected", _btn_selected, btn);

    return btn;
}
