#include "main.h"
#include "util.h"


static int dir = 0;

static void
_ctxpopup_item_cb(void *data, Evas_Object *obj, void *event_info)
{
    printf("ctxpopup item selected: %s\n", elm_object_item_text_get(event_info));
}

Elm_Object_Item *item_new(Evas_Object *ctxpopup, const char * label, const char *icon)
{
    Evas_Object *ic = elm_icon_add(ctxpopup);
    elm_icon_standard_set(ic, icon);
    elm_image_resizable_set(ic, EINA_FALSE, EINA_FALSE);

    return elm_ctxpopup_item_append(ctxpopup, label, ic, _ctxpopup_item_cb, NULL);
}

static void
_ctxpopup_back_key_cb(void *data, Evas_Object *obj, void *event)
{
    evas_object_del(obj);
}

static void
_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *win = data;
    Evas_Object *ctxpopup;
    Evas_Coord x,y;

    ctxpopup = elm_ctxpopup_add(win);

    elm_object_style_set(ctxpopup, "1text.1icon");
    elm_object_signal_emit(ctxpopup, "elm,action,focus", "elm");
    item_new(ctxpopup, "Text List1", "home");
    item_new(ctxpopup, "Text List2", "file");
    item_new(ctxpopup, "Text List3", "delete");

    switch (dir) {
        case 0:
            elm_ctxpopup_direction_priority_set(ctxpopup,
                                                ELM_CTXPOPUP_DIRECTION_UP, 0, 0, 0);
            break;
        case 1:
            elm_ctxpopup_direction_priority_set(ctxpopup,
                                                ELM_CTXPOPUP_DIRECTION_DOWN, 0, 0, 0);
            break;
        case 2:
            elm_ctxpopup_direction_priority_set(ctxpopup,
                                                ELM_CTXPOPUP_DIRECTION_LEFT, 0, 0, 0);
            break;
        case 3:
            elm_ctxpopup_direction_priority_set(ctxpopup,
                                                ELM_CTXPOPUP_DIRECTION_RIGHT, 0, 0, 0);
            break;
    }

    evas_pointer_canvas_xy_get(evas_object_evas_get(obj), &x, &y);
    evas_object_move(ctxpopup, x, y);
    evas_object_show(ctxpopup);
    eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, _ctxpopup_back_key_cb, NULL);
}

static void
_selected(void *data, Evas_Object *obj, void *event_info)
{
    const char *txt = elm_object_item_text_get(event_info);
    elm_object_text_set(obj, txt);

    if (strcmp(txt, "Up") == 0) dir = 0;
    else if (strcmp(txt, "Down") == 0) dir = 1;
    else if (strcmp(txt, "Left") == 0) dir = 2;
    else if (strcmp(txt, "Right") == 0) dir = 3;
    else dir = 0;
}

void ctxpopup_del_cb(void *data)
{
    //If you need to do anyting when
    //ctxpopup is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *ctxpopup_cb(void *data)
{
    Evas_Object *wbox, *obox, *btn, *table, *hov;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    btn = elm_button_add(wbox);
    elm_object_text_set(btn, "Click here to show ctxpopup");
    evas_object_show(btn);
    elm_box_pack_end(wbox, btn);
    evas_object_smart_callback_add(btn, "clicked", _btn_clicked, (void *)ad->win);

    // option box
    hov = elm_hoversel_add(obox);
    elm_hoversel_hover_parent_set(hov, ad->win);
    elm_object_text_set(hov, "Up");
    evas_object_show(hov);
    elm_hoversel_item_add(hov, "Up", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "Down", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "Left", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "Right", NULL, ELM_ICON_NONE, NULL, NULL);
    evas_object_smart_callback_add(hov, "selected", _selected, NULL);
    table = widget_min_set(hov, obox, ELM_SCALE_SIZE(200), ELM_SCALE_SIZE(50));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    evas_object_show(table);
    elm_box_pack_end(obox, table);
    evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    return btn;
}
