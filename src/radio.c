#include "main.h"
#include "util.h"


static int val = 1;

static void _cb(void *data, Evas_Object *obj, void *event_info)
{
    printf("val is now: %d\n", val);
}

void radio_del_cb(void *data)
{
    //If you need to do anyting when
    //radio is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *radio_cb(void *data)
{
    Evas_Object *wbox, *table, *radio, *group, *ic;
    appdata *ad = data;

    wbox = ad->widget_box;

    // widget box
    table = elm_table_add(wbox);
    elm_table_padding_set(table, ELM_SCALE_SIZE(7), ELM_SCALE_SIZE(7));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);

    // radio 1
    group = radio = elm_radio_add(table);
    evas_object_size_hint_weight_set(radio, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(radio, "Tizen");
    elm_radio_state_value_set(radio, 1);
    elm_radio_value_pointer_set(radio, &val);
    evas_object_smart_callback_add(radio, "changed", _cb, NULL);
    evas_object_show(radio);

    ic = elm_icon_add(radio);
    elm_icon_standard_set(ic, "home");
    elm_object_part_content_set(radio, "icon", ic);

    elm_table_pack(table, radio, 0, 1, 1, 1);

    // radio 2
    radio = elm_radio_add(table);
    evas_object_size_hint_weight_set(radio, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(radio, "Android");
    elm_radio_state_value_set(radio, 2);
    elm_radio_value_pointer_set(radio, &val);
    evas_object_smart_callback_add(radio, "changed", _cb, NULL);
    evas_object_show(radio);

    ic = elm_icon_add(radio);
    elm_icon_standard_set(ic, "file");
    elm_object_part_content_set(radio, "icon", ic);

    elm_table_pack(table, radio, 0, 2, 1, 1);
    elm_radio_group_add(radio, group);

    // radio 3
    radio = elm_radio_add(table);
    evas_object_size_hint_weight_set(radio, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(radio, "  Disabled ");
    elm_object_disabled_set(radio, EINA_TRUE);
    evas_object_show(radio);

    ic = elm_icon_add(radio);
    elm_icon_standard_set(ic, "folder");
    elm_object_part_content_set(radio, "icon", ic);

    elm_table_pack(table, radio, 0, 3, 1, 1);
    elm_radio_group_add(radio, group);

    evas_object_show(table);
    elm_box_pack_end(wbox, table);

    return table;
}
