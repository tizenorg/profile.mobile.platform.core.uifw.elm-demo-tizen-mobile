#include "main.h"
#include "util.h"

#define ITEM_NUMS 20
#define BUFFER_SIZE 256


char *_gg_item_styles[] =
{
    "default",
    "video_preview",
    "folder",
    "default_2text",
    NULL
};

static const char *img[] = {
    "sky.jpg",
    NULL
};

typedef struct _Item_Data
{
    const char *path;
    int onoff;
} Item_Data;

static void
_horizontal_grid(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Evas_Object *grid = data;
   elm_gengrid_horizontal_set(grid, elm_check_state_get(obj));
}

static void
_mouse_disable(void *data, Evas_Object *obj,
               void *event_info)
{
    elm_gengrid_wheel_disabled_set(data, !(elm_gengrid_wheel_disabled_get(data)));
    printf("Current mouse disable status:%d\n", elm_gengrid_wheel_disabled_get(data));
}

static void
_gengrid_focus_item_cb(void *data, Evas_Object *obj EINA_UNUSED,
                       void *event_info)
{
   printf("%s: %p\n", (char *)data, event_info);
}

static void
_gengrid_focus_key_down_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                           Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   printf("\n=== Key Down : %s ===\n", ev->keyname);
}

static void _gengrid_longpress_cb(void *data, Evas_Object *obj, void *event_info)
{
    printf("item longressed: %p\n", event_info);
}

char *grid_text_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[BUFFER_SIZE];

   if (!strcmp(part, "elm.text.time"))
      snprintf(buf, sizeof(buf), "00:04:41");
   else
      snprintf(buf, sizeof(buf), "Sample Text");

   return strdup(buf);
}

Evas_Object *grid_content_get(void *data, Evas_Object *obj, const char *part)
{
    const Item_Data *ti = data;

    Evas_Object *image = elm_image_add(obj);
    elm_image_file_set(image, ti->path, NULL);
    elm_image_aspect_fixed_set(image, EINA_FALSE);
    evas_object_show(image);

    return image;
}

Eina_Bool grid_state_get(void *data, Evas_Object *obj, const char *part)
{
    return EINA_FALSE;
}

void grid_del(void *data, Evas_Object *obj)
{
    Item_Data *ti = data;

    eina_stringshare_del(ti->path);
    free(ti);
}

static void grid_sel(void *data, Evas_Object *obj, void *event_info)
{
    printf("sel item data [%p] on grid obj [%p], pointer [%p]\n", data, obj, event_info);
}

static void _gengrid_renew(Evas_Object *obj, const char *style)
{
    Elm_Gengrid_Item_Class *ic;
    Item_Data *ti;
    char buf[BUFFER_SIZE];
    int i;

    if (!obj) return;

    elm_gengrid_clear(obj);
    ic = elm_gengrid_item_class_new();
    ic->item_style = style;
    ic->func.text_get = grid_text_get;
    ic->func.content_get = grid_content_get;
    ic->func.state_get = grid_state_get;
    ic->func.del = grid_del;

    for (i = 0; i < ITEM_NUMS; i++)
    {
        snprintf(buf, sizeof(buf), "%s%s", IMAGE_DIR, img[0]);
        ti = calloc(1, sizeof(Item_Data));
        ti->path = eina_stringshare_add(buf);
        elm_gengrid_item_append(obj, ic, ti, grid_sel, NULL);
    }

    elm_gengrid_item_size_set(obj, ELM_SCALE_SIZE(290), ELM_SCALE_SIZE(350));

    elm_gengrid_item_class_free(ic);
}

static void
_gg_it_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *gg = data;
    const char *txt = elm_object_item_text_get(event_info);
    elm_object_text_set(obj, txt);

    _gengrid_renew(gg, txt);
}

void gengrid_del_cb(void *data)
{
    appdata *ad = data;
    evas_object_smart_callback_del(ad->item_hov, "selected", _gg_it_selected);
}

Evas_Object *gengrid_cb(void *data)
{
    Evas_Object *wbox, *obox, *grid, *ck;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    grid = elm_gengrid_add(wbox);
    elm_gengrid_select_mode_set(grid, ELM_OBJECT_SELECT_MODE_ALWAYS);
    evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
    _gengrid_renew(grid, "default");
    evas_object_show(grid);

    evas_object_smart_callback_add(ad->item_hov, "selected", _gg_it_selected, grid);
    elm_box_pack_end(wbox, grid);

    evas_object_smart_callback_add(grid, "item,focused", _gengrid_focus_item_cb, "item,focused");
    evas_object_smart_callback_add(grid, "item,unfocused", _gengrid_focus_item_cb, "item,unfocused");
    evas_object_smart_callback_add(grid, "selected", _gengrid_focus_item_cb, "selected");
    evas_object_smart_callback_add(grid, "unselected", _gengrid_focus_item_cb, "unselected");
    evas_object_smart_callback_add(grid, "activated", _gengrid_focus_item_cb, "activated");
    evas_object_smart_callback_add(grid, "highlighted", _gengrid_focus_item_cb, "highlighted");
    evas_object_smart_callback_add(grid, "unhighlighted", _gengrid_focus_item_cb, "unhighlighted");
    evas_object_event_callback_add(grid, EVAS_CALLBACK_KEY_DOWN, _gengrid_focus_key_down_cb, NULL);
    evas_object_smart_callback_add(grid, "longpressed", _gengrid_longpress_cb, NULL);

    // option box
    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Horizontal");
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_smart_callback_add(ck, "changed", _horizontal_grid, grid);
    elm_box_pack_end(obox, ck);
    evas_object_show(ck);

    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Disable Wheel");
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_smart_callback_add(ck, "changed", _mouse_disable, grid);
    elm_box_pack_end(obox, ck);
    evas_object_show(ck);

    return grid;
}
