#include "main.h"
#include "util.h"

/* macro to store evas-object data key string for hoversel object last selected item */
#define KEY_LAST_SELECTED_ITEM "last_selected_item"


static void _hoversel_clicked_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    printf("Hover button is clicked and 'clicked' callback is called.\n");
}

static void _hoversel_selected_cb(void *data EINA_UNUSED, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *last_selected_it, *hoversel_it;
    Evas_Object *ic = NULL;
    const char *item_label, *icon;

    hoversel_it = event_info;
    last_selected_it = evas_object_data_get(obj, KEY_LAST_SELECTED_ITEM);
    if (hoversel_it == last_selected_it) return;
    if (hoversel_it == NULL) return;

    evas_object_data_set(obj, KEY_LAST_SELECTED_ITEM, (void*)hoversel_it);
    item_label = elm_object_item_text_get(hoversel_it);
    elm_object_text_set(obj, item_label);

    printf("Item selected: %s\n", item_label);

    elm_hoversel_item_icon_get(hoversel_it, &icon, NULL, NULL);
    if (icon)
    {
        ic = elm_icon_add(obj);
        elm_image_file_set(ic, icon, NULL);
    }
    elm_object_content_set(obj, ic);
}

static void _hoversel_dismissed_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    printf("'dismissed' callback is called.\n");
}

static void _hoversel_expanded_cb(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
    const Eina_List *l;
    Elm_Object_Item *last_selected_it, *hoversel_it, *last_it = NULL;
    const Eina_List *items = elm_hoversel_items_get(obj);

    printf("'expanded' callback is called.\n");

    last_selected_it = evas_object_data_get(obj, KEY_LAST_SELECTED_ITEM);
    if (last_selected_it != NULL)
    elm_object_item_signal_emit(last_selected_it, "elm,state,highlight", "elm");

    EINA_LIST_FOREACH(items, l, hoversel_it)
    {
        last_it = hoversel_it;
    }
    elm_object_item_signal_emit(last_it, "elm,state,last,item", "elm");
}

void hoversel_del_cb(void *data)
{
    //If you need to do anyting when
    //hoversel is deleted and another widget is selected on the menu,
    //please do in this function.
}

Evas_Object *hoversel_cb(void *data)
{
    Evas_Object *wbox, *table, *hoversel;
    appdata *ad = data;
    Elm_Object_Item *it;

    wbox = ad->widget_box;

    hoversel = elm_hoversel_add(wbox);
    table = widget_min_set(hoversel, wbox, ELM_SCALE_SIZE(400), ELM_SCALE_SIZE(50));
    evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    elm_hoversel_hover_parent_set(hoversel, ad->win);
    elm_object_text_set(hoversel, "Hoversel");
    it = elm_hoversel_item_add(hoversel, "Item 1", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_icon_set(it, IMAGE_DIR"ico_arrow_down.png", NULL, ELM_ICON_FILE);
    it = elm_hoversel_item_add(hoversel, "Item 2", NULL, ELM_ICON_FILE, NULL, NULL);
    elm_hoversel_item_icon_set(it, IMAGE_DIR"ico_arrow_up.png", NULL, ELM_ICON_FILE);
    elm_hoversel_item_add(hoversel, "Item 3", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hoversel, "Item 4", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_add(hoversel, "Item 5 This item is long", NULL, ELM_ICON_NONE, NULL, NULL);
    it = elm_hoversel_item_add(hoversel, "Item 6 This item is long", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_icon_set(it, IMAGE_DIR"ico_arrow_down.png", NULL, ELM_ICON_FILE);
    it = elm_hoversel_item_add(hoversel, "Item 7 This item is long", NULL, ELM_ICON_NONE, NULL, NULL);
    elm_hoversel_item_icon_set(it, IMAGE_DIR"ico_arrow_up.png", NULL, ELM_ICON_FILE);

    evas_object_smart_callback_add(hoversel, "clicked", _hoversel_clicked_cb, NULL);
    evas_object_smart_callback_add(hoversel, "selected", _hoversel_selected_cb, NULL);
    evas_object_smart_callback_add(hoversel, "dismissed", _hoversel_dismissed_cb, NULL);
    evas_object_smart_callback_add(hoversel, "expanded", _hoversel_expanded_cb, NULL);

    evas_object_show(table);
    evas_object_show(hoversel);

    elm_box_pack_end(wbox, table);

    return table;
}
