#include "main.h"
#include "util.h"


Evas_Object *bg_cb(void *data)
{
    Evas_Object *wbox, *bg;
    appdata *ad = data;

    wbox = ad->widget_box;

    bg = elm_bg_add(wbox);
    elm_bg_color_set(bg, 66, 162, 206);
    evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(bg);
    elm_box_pack_end(wbox, bg);

    return bg;
}
