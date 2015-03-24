#include "main.h"
#include "util.h"


char *_ck_styles[] =
{
    "default",
    "favorite",
    "onoff",
    NULL
};


static void
_ck_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *ck = data;
    const char *txt = elm_object_item_text_get(event_info);

    elm_object_style_set(ck, txt);
}

static void
_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *check = data;
    Eina_Bool state = elm_check_state_get(obj);

    if (state) elm_object_text_set(check, "Text");
    else elm_object_text_set(check, "");
}

static void
_changed_cb2(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *check = data;
    Eina_Bool state = elm_check_state_get(obj);

    if (state) {
        Evas_Object *ic = elm_icon_add(check);
        char buf[100];
        snprintf(buf, sizeof(buf), "%s%s", IMAGE_DIR, "ico_lock_nor.png");
        elm_image_file_set(ic, buf, NULL);

        elm_object_part_content_set(check, "icon", ic);
    }
    else elm_object_part_content_set(check, "icon", NULL);
}

void checkbox_del_cb(void *data)
{
}

Evas_Object *checkbox_cb(void *data)
{
    Evas_Object *wbox, *obox, *check, *ck;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    check = elm_check_add(wbox);
    evas_object_show(check);
    elm_box_pack_end(wbox, check);

    // option box
    ck = elm_check_add(obox);
    evas_object_show(ck);
    elm_object_text_set(ck, " Set Text");
    elm_box_pack_end(obox, ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_smart_callback_add(ck, "changed", _changed_cb, check);

    ck = elm_check_add(obox);
    evas_object_show(ck);
    elm_object_text_set(ck, " Set Icon");
    elm_box_pack_end(obox, ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_smart_callback_add(ck, "changed", _changed_cb2, check);

    evas_object_smart_callback_add(ad->style_hov, "selected", _ck_selected, check);

    return check;
}
