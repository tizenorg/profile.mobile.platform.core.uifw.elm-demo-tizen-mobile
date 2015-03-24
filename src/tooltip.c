#include "main.h"
#include "util.h"


static void _btn_focus_cb(void *data, Evas_Object *obj, void *event_info )
{
    printf("signal : %s\n", (char*)event_info);
}

static void _btn_unfocus_cb(void *data, Evas_Object *obj, void *event_info )
{
    printf("signal : %s\n", (char*)event_info);
    elm_object_tooltip_hide(obj);
}

static void
_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *bt = data;
    const char *txt = elm_object_item_text_get(event_info);
    elm_object_text_set(obj, txt);

    if (!strcmp(txt, "Top"))
    {
        elm_object_tooltip_orient_set(bt, ELM_TOOLTIP_ORIENT_TOP);
        elm_object_tooltip_text_set(bt, "Top Tooltip");
    }
    else if (!strcmp(txt, "Bottom"))
    {
        elm_object_tooltip_orient_set(bt, ELM_TOOLTIP_ORIENT_BOTTOM);
        elm_object_tooltip_text_set(bt, "Bottom Tooltip");
    }
}

void tooltip_del_cb(void *data)
{
}

Evas_Object *tooltip_cb(void *data)
{
    Evas_Object *wbox, *obox, *bt, *table, *hov;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    bt = elm_button_add(wbox);
    elm_object_text_set(bt, "Mouse over to show tooltip");
    elm_object_tooltip_text_set(bt, "Top Tooltip");
    elm_object_tooltip_orient_set(bt, ELM_TOOLTIP_ORIENT_TOP);
    evas_object_show(bt);
    elm_box_pack_end(wbox, bt);
    evas_object_smart_callback_add(bt, "focused", _btn_focus_cb, bt);
    evas_object_smart_callback_add(bt, "unfocused", _btn_unfocus_cb, bt);

    // option box
    hov = elm_hoversel_add(obox);
    elm_hoversel_hover_parent_set(hov, ad->win);
    elm_object_text_set(hov, "Top");
    evas_object_show(hov);
    elm_hoversel_item_add(hov, "Top", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "Bottom", NULL, ELM_ICON_NONE, NULL, NULL);
    evas_object_smart_callback_add(hov, "selected", _selected, bt);

    table = widget_min_set(hov, obox, ELM_SCALE_SIZE(250), ELM_SCALE_SIZE(50));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    evas_object_show(table);
    elm_box_pack_end(obox, table);
    evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    return bt;
}
