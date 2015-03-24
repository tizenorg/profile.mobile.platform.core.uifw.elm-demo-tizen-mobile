#include "main.h"
#include "util.h"


Evas_Object *label_cb(void *data)
{
    Evas_Object *wbox, *label;
    appdata *ad = data;

    wbox = ad->widget_box;

    label = elm_label_add(wbox);
    elm_object_text_set(label, "This is a label");
    evas_object_show(label);
    elm_box_pack_end(wbox, label);

    return label;
}
