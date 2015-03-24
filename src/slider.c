#include "main.h"
#include "util.h"


char *_sl_styles[] =
{
    "default",
    "progress",
    NULL
};

static Evas_Object *sl;
static Eina_Bool ck1, ck2, ck3;

static void _cb_changed(void *data, Evas_Object *obj, void *event_info)
{
    int val = (int) data;
    if (val == 1) {
        elm_slider_inverted_set(sl, ck1);
    }
    else if (val == 2) {
        elm_slider_indicator_show_set(sl, !ck2);
    }
    else if (val == 3) {
        elm_slider_indicator_show_on_focus_set(sl, ck3);
    }
}

static void
_sl_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *sl = data;
    const char *txt = elm_object_item_text_get(event_info);

    elm_object_style_set(sl, txt);

    _cb_changed((void *) 1, NULL, NULL);
    _cb_changed((void *) 2, NULL, NULL);
    _cb_changed((void *) 3, NULL, NULL);
}

void slider_del_cb(void *data)
{
    appdata *ad = data;
    evas_object_smart_callback_del(ad->style_hov, "selected", _sl_selected);
}

Evas_Object *slider_cb(void *data)
{
    Evas_Object *wbox, *obox, *table, *slider, *ck;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    slider = elm_slider_add(wbox);
    elm_slider_indicator_format_set(slider, "%02.0f");
    elm_object_text_set(slider, "0");
    elm_slider_unit_format_set(slider, "%1.0f ");
    elm_slider_min_max_set(slider, 0, 100);
    evas_object_show(slider);

    table = widget_min_set(slider, wbox, ELM_SCALE_SIZE(400), ELM_SCALE_SIZE(50));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    evas_object_show(table);
    elm_box_pack_end(wbox, table);

    sl = slider;
    evas_object_smart_callback_add(ad->style_hov, "selected", _sl_selected, sl);

    // option box
    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Invert");
    elm_check_state_pointer_set(ck, &ck1);
    evas_object_smart_callback_add(ck, "changed", _cb_changed, (void *)1);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);

    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Disable Indicator");
    elm_check_state_pointer_set(ck, &ck2);
    evas_object_smart_callback_add(ck, "changed", _cb_changed, (void *)2);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);

    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Indicator on Focus");
    elm_check_state_pointer_set(ck, &ck3);
    evas_object_smart_callback_add(ck, "changed", _cb_changed, (void *)3);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);

    return table;
}
