#include "main.h"
#include "util.h"


Evas_Object *toolbar_cb(void *data)
{
    Evas_Object *wbox, *toolbar;
    appdata *ad = data;

    wbox = ad->widget_box;

    toolbar = elm_toolbar_add(wbox);

    elm_toolbar_item_append(toolbar, NULL, "Item1", NULL, NULL);
    elm_toolbar_item_append(toolbar, NULL, "Item2", NULL, NULL);
    elm_toolbar_item_append(toolbar, NULL, "Item3", NULL, NULL);

    evas_object_size_hint_align_set(toolbar, EVAS_HINT_FILL, 0);
    evas_object_size_hint_weight_set(toolbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    evas_object_show(toolbar);
    elm_box_pack_end(wbox, toolbar);

    return toolbar;
}
