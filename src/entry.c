#include "main.h"
#include "util.h"


static Evas_Object *entry, *table, *check, *icon = NULL;
static Eina_Bool ck1;
static Eina_Bool is_pin_style;

char *_en_styles[] =
{
    "input.field",
    "input.field.icon",
    "input.field.small",
    "input.field.small.icon",
    "input.field.pin",
    NULL
};

static void _preedit_cb(void *data, Evas_Object *obj, void *event_info)
{
    int x;
    Ecore_IMF_Context *imf_context = data;
    char im_data[30] = "entrylimit=20&entrycharlen=0";

    x = eina_unicode_utf8_get_len(elm_object_text_get(obj));
    sprintf(im_data, "entrylimit=20&entrycharlen=%d",x);
    ecore_imf_context_input_panel_imdata_set(imf_context, im_data, eina_unicode_utf8_get_len(im_data)+1);
}

static void _preedit_pin_cb(void *data, Evas_Object *obj, void *event_info)
{
    int x;
    Ecore_IMF_Context *imf_context = data;
    char im_data[30] = "entrylimit=1&entrycharlen=0";

    x = eina_unicode_utf8_get_len(elm_object_text_get(obj));
    sprintf(im_data, "entrylimit=1&entrycharlen=%d",x);
    ecore_imf_context_input_panel_imdata_set(imf_context, im_data, eina_unicode_utf8_get_len(im_data)+1);
}

static void
pin_style()
{
    Evas_Object *en, *rect;
    static Elm_Entry_Filter_Limit_Size limit_filter_data;
    Ecore_IMF_Context *imf_context;

    elm_table_clear(table, EINA_TRUE);
    elm_table_padding_set(table, 50, 0);
    elm_table_homogeneous_set(table, EINA_TRUE);

    rect = evas_object_rectangle_add(evas_object_evas_get(table));
    evas_object_size_hint_min_set(rect, 240, 0);
    evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(table, rect, 0, 0, 4, 1);

    en = elm_entry_add(table);
    evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_style_set(en, "input.field.pin");
    elm_object_text_set(en, "");
    elm_entry_password_set(en, EINA_TRUE);
    elm_entry_single_line_set(en, EINA_TRUE);
    elm_table_pack(table, en, 0, 0, 1, 1);
    evas_object_show(en);

    imf_context = elm_entry_imf_context_get(en);
    limit_filter_data.max_char_count = 1;
    limit_filter_data.max_byte_count = 0;
    elm_entry_markup_filter_append(en, elm_entry_filter_limit_size, &limit_filter_data);
    evas_object_smart_callback_add(en, "preedit,changed", _preedit_pin_cb, imf_context);
    evas_object_smart_callback_add(en, "changed", _preedit_pin_cb, imf_context);

    en = elm_entry_add(table);
    evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_style_set(en, "input.field.pin");
    elm_object_text_set(en, "");
    elm_entry_password_set(en, EINA_TRUE);
    elm_entry_single_line_set(en, EINA_TRUE);
    elm_table_pack(table, en, 1, 0, 1, 1);
    evas_object_show(en);

    imf_context = elm_entry_imf_context_get(en);
    limit_filter_data.max_char_count = 1;
    limit_filter_data.max_byte_count = 0;
    elm_entry_markup_filter_append(en, elm_entry_filter_limit_size, &limit_filter_data);
    evas_object_smart_callback_add(en, "preedit,changed", _preedit_pin_cb, imf_context);
    evas_object_smart_callback_add(en, "changed", _preedit_pin_cb, imf_context);

    en = elm_entry_add(table);
    evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_style_set(en, "input.field.pin");
    elm_object_text_set(en, "");
    elm_entry_password_set(en, EINA_TRUE);
    elm_entry_single_line_set(en, EINA_TRUE);
    elm_table_pack(table, en, 2, 0, 1, 1);
    evas_object_show(en);

    imf_context = elm_entry_imf_context_get(en);
    limit_filter_data.max_char_count = 1;
    limit_filter_data.max_byte_count = 0;
    elm_entry_markup_filter_append(en, elm_entry_filter_limit_size, &limit_filter_data);
    evas_object_smart_callback_add(en, "preedit,changed", _preedit_pin_cb, imf_context);
    evas_object_smart_callback_add(en, "changed", _preedit_pin_cb, imf_context);

    en = elm_entry_add(table);
    evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_style_set(en, "input.field.pin");
    elm_object_text_set(en, "");
    elm_entry_password_set(en, EINA_TRUE);
    elm_entry_single_line_set(en, EINA_TRUE);
    elm_table_pack(table, en, 3, 0, 1, 1);
    evas_object_show(en);

    imf_context = elm_entry_imf_context_get(en);
    limit_filter_data.max_char_count = 1;
    limit_filter_data.max_byte_count = 0;
    elm_entry_markup_filter_append(en, elm_entry_filter_limit_size, &limit_filter_data);
    evas_object_smart_callback_add(en, "preedit,changed", _preedit_pin_cb, imf_context);
    evas_object_smart_callback_add(en, "changed", _preedit_pin_cb, imf_context);
}

static void
_en_selected(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *en, *rect;
    const char *txt = elm_object_item_text_get(event_info);

    if (!strcmp(txt, elm_object_text_get(obj))) return;

    // 1. pin style -> normal style
    if (is_pin_style)
    {
        elm_table_clear(table, EINA_TRUE);
        is_pin_style = EINA_FALSE;

        entry = en = elm_entry_add(table);
        elm_object_text_set(en, "Input Field");
        elm_entry_scrollable_set(en, EINA_TRUE);
        elm_entry_single_line_set(en, EINA_TRUE);
        elm_table_pack(table, en, 0, 0, 1, 1);
        evas_object_show(en);

        rect = evas_object_rectangle_add(evas_object_evas_get(table));
        evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_size_hint_min_set(rect, 400, 0);
        elm_table_pack(table, rect, 0, 0, 1, 1);

        elm_object_style_set(en, txt);
        elm_object_disabled_set(check, EINA_FALSE);
    }
    // 2. normal style -> pin style
    else if (!is_pin_style && !strcmp(txt, "input.field.pin"))
    {
        elm_table_clear(table, EINA_TRUE);
        if (icon)
        {
            evas_object_del(icon);
            icon = NULL;
        }
        pin_style();
        is_pin_style = EINA_TRUE;
        elm_object_disabled_set(check, EINA_TRUE);
    }
    // 3. normal style -> normal style
    else
    {
        elm_object_style_set(entry, txt);
    }

    // icon set
    if (!strcmp(txt, "input.field.icon") || !strcmp(txt, "input.field.small.icon"))
    {
        if (!icon)
        {
            icon = elm_icon_add(entry);
            elm_image_file_set(icon, IMAGE_DIR"ico_lock_nor.png", NULL);
            evas_object_color_set(icon, 0, 0, 0, 255);
        }
        elm_object_part_content_set(entry, "icon", icon);
    }
    else
    {
        if (icon)
        {
            evas_object_del(icon);
            icon = NULL;
        }
    }
}

static void _ck_changed(void *data, Evas_Object *obj, void *event_info)
{
    int val = (int) data;
    static Elm_Entry_Filter_Limit_Size limit_filter_data;
    Ecore_IMF_Context *imf_context;

    if (val == 1)
    {
        if (ck1)
        {
            imf_context = elm_entry_imf_context_get(entry);

            limit_filter_data.max_char_count = 20;
            limit_filter_data.max_byte_count = 0;
            elm_entry_markup_filter_append(entry, elm_entry_filter_limit_size, &limit_filter_data);
            evas_object_smart_callback_add(entry, "preedit,changed", _preedit_cb, imf_context);
            evas_object_smart_callback_add(entry, "changed", _preedit_cb, imf_context);
        }
        else
        {
            imf_context = elm_entry_imf_context_get(entry);
            elm_entry_markup_filter_remove(entry, elm_entry_filter_limit_size, &limit_filter_data);
            evas_object_smart_callback_del_full(entry, "preedit,changed", _preedit_cb, imf_context);
            evas_object_smart_callback_del_full(entry, "changed", _preedit_cb, imf_context);
        }
    }
}

void entry_del_cb(void *data)
{
    appdata *ad = data;
    evas_object_smart_callback_del(ad->style_hov, "selected", _en_selected);
    if (icon)
    {
        evas_object_del(icon);
        icon = NULL;
    }
}

Evas_Object *entry_cb(void *data)
{
    Evas_Object *wbox, *obox, *en, *tb, *ck;
    appdata *ad = data;

    wbox = ad->widget_box;
    obox = ad->option_box;

    // widget box
    en = elm_entry_add(wbox);
    tb = widget_min_set(en, wbox, ELM_SCALE_SIZE(400), 0);
    evas_object_event_callback_add(tb, EVAS_CALLBACK_DEL, table_del_cb, NULL);
    elm_object_style_set(en, "input.field");
    elm_object_text_set(en, "Input Field");
    elm_entry_scrollable_set(en, EINA_TRUE);
    elm_entry_single_line_set(en, EINA_TRUE);
    elm_box_pack_end(wbox, tb);
    evas_object_show(tb);
    evas_object_show(en);

    table = tb;
    entry = en;
    is_pin_style = EINA_FALSE;
    evas_object_smart_callback_add(ad->style_hov, "selected", _en_selected, NULL);

    // option box
    ck = elm_check_add(obox);
    elm_object_text_set(ck, " Limit # of Characters to 20");
    elm_check_state_pointer_set(ck, &ck1);
    evas_object_smart_callback_add(ck, "changed", _ck_changed, (void *)1);
    evas_object_show(ck);
    evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_box_pack_end(obox, ck);
    check = ck;

    return table;
}
