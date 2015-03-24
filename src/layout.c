#include "main.h"
#include "util.h"

void layout_del_cb(void *data)
{
    //If you need to do anyting when
    //layout is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *layout_cb(void *data)
{
    Evas_Object *wbox, *layout;
    appdata *ad = data;

    wbox = ad->widget_box;

    // widget box
    layout = elm_layout_add(wbox);
    evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_layout_theme_set(layout, "layout", "application", "nocontent");

    elm_object_part_text_set(layout, "elm.text", "No Plugged Source");
    elm_object_part_text_set(layout, "elm.text.1", "check connection status or install any cloud service.");

    elm_box_pack_end(wbox, layout);
    evas_object_show(layout);

    return layout;
}
