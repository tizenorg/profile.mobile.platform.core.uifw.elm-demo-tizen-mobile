#include "main.h"
#include "util.h"


Evas_Object *panel_cb(void *data)
{
    Evas_Object *wbox, *panel, *list;
    appdata *ad = data;
	int i;
	char buf[64];

    wbox = ad->widget_box;

    panel = elm_panel_add(wbox);
    elm_panel_scrollable_set(panel, EINA_TRUE);
    elm_panel_hidden_set(panel, EINA_TRUE);
    elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);
    evas_object_size_hint_weight_set(panel, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(panel, EVAS_HINT_FILL, EVAS_HINT_FILL);

    list = elm_list_add(panel);
    evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);

    for (i = 0; i < 20; i++) {
         sprintf(buf, "list item %d", i);
         elm_list_item_append(list, buf, NULL, NULL, NULL, NULL);
    }
    evas_object_show(list);
    elm_object_content_set(panel, list);

    evas_object_show(panel);
    elm_box_pack_end(wbox, panel);

    return panel;
}
