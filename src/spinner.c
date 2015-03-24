#include "main.h"
#include "util.h"


Evas_Object *spinner_cb(void *data)
{
    Evas_Object *wbox, *spinner;
    appdata *ad = data;

    wbox = ad->widget_box;

    spinner = elm_spinner_add(wbox);
    evas_object_size_hint_align_set(spinner, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(spinner, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(spinner);
    elm_box_pack_end(wbox, spinner);

    return spinner;
}
