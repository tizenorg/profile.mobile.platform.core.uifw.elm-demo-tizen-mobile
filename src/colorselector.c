#include "main.h"
#include "util.h"


Evas_Object *colorselector_cb(void *data)
{
   Evas_Object *wbox, *colorselector;
   appdata *ad = data;

   wbox = ad->widget_box;

   colorselector = elm_colorselector_add(wbox);
   elm_colorselector_mode_set(colorselector, ELM_COLORSELECTOR_PALETTE);
   evas_object_size_hint_align_set(colorselector, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(colorselector, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

   evas_object_show(colorselector);
   elm_box_pack_end(wbox, colorselector);

   return colorselector;
}
