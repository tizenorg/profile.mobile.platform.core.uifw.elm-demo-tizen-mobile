#include "main.h"
#include "util.h"


char *_sc_styles[] =
{
    "default",
    "white",
    "no_bar",
    NULL
};

static void
_sc_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *sc = data;
    const char *txt = elm_object_item_text_get(event_info);

    elm_object_style_set(sc, txt);
}

void scroller_del_cb(void *data)
{
    appdata *ad = data;
    evas_object_smart_callback_del(ad->style_hov, "selected", _sc_selected);
}

Evas_Object *scroller_cb(void *data)
{
    Evas_Object *wbox, *sc, *table, *btn;
    appdata *ad = data;
    int i, j;

    wbox = ad->widget_box;

    // widget box
    sc = elm_scroller_add(wbox);
    evas_object_size_hint_weight_set(sc, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(sc, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(sc);
    elm_box_pack_end(wbox, sc);

    evas_object_smart_callback_add(ad->style_hov, "selected", _sc_selected, sc);

    table = elm_table_add(sc);
    elm_table_padding_set(table, ELM_SCALE_SIZE(20), ELM_SCALE_SIZE(20));
    elm_table_homogeneous_set(table, EINA_TRUE);
    evas_object_size_hint_align_set(table, 0.5, EVAS_HINT_FILL);
    elm_object_content_set(sc, table);
    evas_object_show(table);

    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            btn = elm_button_add(table);
            elm_object_text_set(btn, "scroller");
            elm_table_pack(table, btn, i, j, 1, 1);
            evas_object_show(btn);
        }
    }

    return sc;
}
