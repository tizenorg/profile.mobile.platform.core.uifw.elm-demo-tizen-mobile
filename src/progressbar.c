#include "main.h"
#include "util.h"


typedef struct Progressbar
{
    Evas_Object *pb1;
    Eina_Bool run;
    Ecore_Timer *timer;
} Progressbar;

static Progressbar _test_progressbar;

static Eina_Bool cb_vertical, cb_invert, cb_pulse;

static void _cb_changed(void *data, Evas_Object *obj, void *event_info)
{
    int val = (int)(uintptr_t)data;
    if (val == 1) {   //vertical
        elm_progressbar_horizontal_set(_test_progressbar.pb1, !cb_vertical);
    }
    else if (val == 2) {  //invert
        elm_progressbar_inverted_set(_test_progressbar.pb1, cb_invert);
    }
    else if (val == 3) {  //pulse
        if (_test_progressbar.run) {
            ecore_timer_del(_test_progressbar.timer);
            _test_progressbar.run = EINA_FALSE;
        }
        elm_progressbar_pulse(_test_progressbar.pb1, EINA_FALSE);
        elm_progressbar_pulse_set(_test_progressbar.pb1, cb_pulse);
    }
}

static Eina_Bool _my_progressbar_value_set(void *data)
{
    double progress;

    progress = elm_progressbar_value_get (_test_progressbar.pb1);
    if (progress < 1.0) progress += 0.0123;
    else progress = 0.0;

    elm_progressbar_value_set(_test_progressbar.pb1, progress);
    if (progress < 1.0) return ECORE_CALLBACK_RENEW;
    _test_progressbar.run = 0;

    return ECORE_CALLBACK_CANCEL;
}

static void _progress_filling_start(void *data, Evas_Object *obj, void *event_info)
{
    if (cb_pulse)
        elm_progressbar_pulse(_test_progressbar.pb1, EINA_TRUE);
    else if (!_test_progressbar.run)
    {
        _test_progressbar.timer = ecore_timer_add(0.1, _my_progressbar_value_set, NULL);
        _test_progressbar.run = EINA_TRUE;
    }
}

static void _progress_filling_stop(void *data, Evas_Object *obj, void *event_info)
{
    if (cb_pulse)
        elm_progressbar_pulse(_test_progressbar.pb1, EINA_FALSE);
    else if (_test_progressbar.run)
    {
        ecore_timer_del(_test_progressbar.timer);
        _test_progressbar.run = EINA_FALSE;
    }
}

void progressbar_del_cb(void *data)
{
    //If you need to do anyting when
    //progressbar is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *progressbar_cb(void *data)
{
    Evas_Object *wbox, *obox, *table, *pb, *bt, *ck;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    pb = elm_progressbar_add(wbox);
    elm_progressbar_span_size_set(pb, ELM_SCALE_SIZE(200));
    evas_object_size_hint_weight_set(pb, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_style_set(pb, "default");
    evas_object_show(pb);

    table = widget_min_set(pb, wbox, ELM_SCALE_SIZE(800), ELM_SCALE_SIZE(500));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    evas_object_show(table);
    elm_box_pack_end(wbox, table);
    _test_progressbar.pb1 = pb;

    // option box
    bt = elm_button_add(obox);
    elm_object_text_set(bt, "Start");
    evas_object_smart_callback_add(bt, "clicked", _progress_filling_start, NULL);
    evas_object_show(bt);
    evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, bt);

    bt = elm_button_add(obox);
    elm_object_text_set(bt, "Stop");
    evas_object_smart_callback_add(bt, "clicked", _progress_filling_stop, NULL);
    evas_object_show(bt);
    evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, bt);

    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Vertical");
    elm_check_state_pointer_set(ck, &cb_vertical);
    evas_object_smart_callback_add(ck, "changed", _cb_changed, (void *)1);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);

    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Invert");
    elm_check_state_pointer_set(ck, &cb_invert);
    evas_object_smart_callback_add(ck, "changed", _cb_changed, (void *)2);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);

    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Pulse");
    elm_check_state_pointer_set(ck, &cb_pulse);
    evas_object_smart_callback_add(ck, "changed", _cb_changed, (void *)3);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);

    return table;
}
