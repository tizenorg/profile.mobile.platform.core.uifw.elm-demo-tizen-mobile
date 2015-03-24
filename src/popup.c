#include "main.h"
#include "util.h"


static Eina_Bool title = EINA_FALSE, timeout = EINA_FALSE;
static int btn_num = 0;

static void _response_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    evas_object_del(data);
}

static void
_selected(void *data EINA_UNUSED, Evas_Object *obj, void *event_info)
{
    const char *txt = elm_object_item_text_get(event_info);
    elm_object_text_set(obj, txt);

    if (strcmp(txt, "1 Button") == 0) btn_num = 1;
    else if (strcmp(txt, "2 Buttons") == 0) btn_num = 2;
    else if (strcmp(txt, "3 Buttons") == 0) btn_num = 3;
    else btn_num = 0;
}

static void
_changed_cb(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
    Eina_Bool state = elm_check_state_get(obj);

    if (state) timeout = EINA_TRUE;
    else timeout = EINA_FALSE;
}

static void
_changed_cb2(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
    Eina_Bool state = elm_check_state_get(obj);

    if (state) title = EINA_TRUE;
    else title = EINA_FALSE;
}

static void
_btn_clicked(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    Evas_Object *win = data;
    Evas_Object *popup = elm_popup_add(win);
    Evas_Object *btn;

    elm_popup_orient_set(popup, ELM_POPUP_ORIENT_CENTER);
    elm_object_text_set(popup, "Title Sample</br>"
                        "Check the antenna cable connection.");
    evas_object_smart_callback_add(popup, "block,clicked", _response_cb, popup);
    eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _response_cb, popup);
    evas_object_show(popup);

    if (timeout) elm_popup_timeout_set(popup, 2.0);
    if (title) elm_object_part_text_set(popup, "title,text", "Title");

    if (btn_num > 0) {
        btn = elm_button_add(popup);
        elm_object_text_set(btn, "Cancel");
        elm_object_part_content_set(popup, "button1", btn);
        evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
    }
    if (btn_num > 1) {
        btn = elm_button_add(popup);
        elm_object_text_set(btn, "Cancel");
        elm_object_part_content_set(popup, "button2", btn);
        evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
    }
    if (btn_num > 2) {
        btn = elm_button_add(popup);
        elm_object_text_set(btn, "Cancel");
        elm_object_part_content_set(popup, "button3", btn);
        evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
    }
}

void popup_del_cb(void *data)
{
    //If you need to do anyting when
    //popup is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *popup_cb(void *data)
{
    Evas_Object *wbox, *obox, *btn, *ck, *table, *hov;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    btn = elm_button_add(wbox);
    elm_object_text_set(btn, "Click here to show popup");
    evas_object_show(btn);
    elm_box_pack_end(wbox, btn);
    evas_object_smart_callback_add(btn, "clicked", _btn_clicked, (void *)ad->win);

    // option box
    ck = elm_check_add(obox);
    evas_object_show(ck);
    elm_object_text_set(ck, " Timeout");
    elm_box_pack_end(obox, ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_smart_callback_add(ck, "changed", _changed_cb, NULL);

    ck = elm_check_add(obox);
    evas_object_show(ck);
    elm_object_text_set(ck, " Set Title");
    elm_box_pack_end(obox, ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_smart_callback_add(ck, "changed", _changed_cb2, NULL);

    hov = elm_hoversel_add(obox);
    elm_hoversel_hover_parent_set(hov, ad->win);
    elm_object_text_set(hov, "No Button");
    evas_object_show(hov);
    elm_hoversel_item_add(hov, "No Button", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "1 Button", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "2 Buttons", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hov, "3 Buttons", NULL, ELM_ICON_NONE, NULL, NULL);
    evas_object_smart_callback_add(hov, "selected", _selected, NULL);
    table = widget_min_set(hov, obox, ELM_SCALE_SIZE(250), ELM_SCALE_SIZE(50));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    evas_object_show(table);
    elm_box_pack_end(obox, table);
    evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    return btn;
}
