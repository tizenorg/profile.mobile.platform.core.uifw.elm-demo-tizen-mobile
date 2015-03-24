#include "main.h"
#include "util.h"


Evas_Object *index_cb(void *data)
{
    Evas_Object *wbox, *index;
    appdata *ad = data;
    int i = 0;
    char buf[4] = {0, };

    wbox = ad->widget_box;

    index = elm_index_add(wbox);

    for (i = 65; i <= 90; i++) {
        sprintf(buf, "%c", i);
        elm_index_item_append(index, buf, NULL, NULL);
    }
    elm_index_level_go(index, 0);

    evas_object_size_hint_weight_set(index, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(index, EVAS_HINT_FILL, EVAS_HINT_FILL);

    evas_object_show(index);
    elm_box_pack_end(wbox, index);

    return index;
}
