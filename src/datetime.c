#include "main.h"
#include "util.h"


static void _focus_in_cb(void *data, Evas_Object *obj, void *event_info)
{
    fprintf(stderr, "[datetime] - focus in\n");
    elm_win_focus_highlight_style_set(data, "datetime");
}

static void _focus_out_cb(void *data, Evas_Object *obj, void *event_info)
{
    fprintf(stderr, "[datetime]  - focus out\n");
    elm_win_focus_highlight_style_set(data, "default");
}

void datetime_del_cb(void *data)
{
    //If you need to do anyting when
    //datetime is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *datetime_cb(void *data)
{
    Evas_Object *wbox, *datetime;
    appdata *ad = data;

    wbox = ad->widget_box;

    // widget box
    datetime = elm_datetime_add(wbox);
    evas_object_show(datetime);
    elm_box_pack_end(wbox, datetime);

    elm_datetime_field_visible_set(datetime, ELM_DATETIME_HOUR, EINA_FALSE);
    elm_datetime_field_visible_set(datetime, ELM_DATETIME_MINUTE, EINA_FALSE);

    evas_object_smart_callback_add(datetime, "focused", _focus_in_cb, ad->win);
    evas_object_smart_callback_add(datetime, "unfocused", _focus_out_cb, ad->win);

    return datetime;
}
