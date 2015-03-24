#include "main.h"
#include "util.h"


Evas_Object *multibuttonentry_cb(void *data)
{
    Evas_Object *wbox, *mbe;
    appdata *ad = data;

    wbox = ad->widget_box;

    mbe = elm_multibuttonentry_add(wbox);
    elm_object_text_set(mbe, "To: ");
    evas_object_show(mbe);
    evas_object_size_hint_weight_set(mbe, EVAS_HINT_EXPAND, 0.0);
    evas_object_size_hint_align_set(mbe, EVAS_HINT_FILL, 0.0);
    elm_box_pack_end(wbox, mbe);

    return mbe;
}
