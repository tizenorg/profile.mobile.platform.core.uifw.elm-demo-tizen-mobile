#include <Elementary.h>
#include "config.h"
#include "main.h"

#if DESKTOP == 0
#include <appcore-efl.h>
#endif


extern char *_btn_styles[];
extern char *_en_styles[];
extern char *_sc_styles[];
extern char *_sl_styles[];
extern char *_gg_item_styles[];
extern char *_gl_item_styles[];

static widget_item widget_its[] =
{
    { "Button",  button_cb, button_del_cb, _btn_styles, NULL },
    { "Check", checkbox_cb, checkbox_del_cb, NULL, NULL },
    { "Ctxpopup", ctxpopup_cb, ctxpopup_del_cb, NULL, NULL },
    { "Datetime", datetime_cb, datetime_del_cb, NULL, NULL },
    { "Entry", entry_cb, entry_del_cb, _en_styles, NULL },
    { "Gengrid", gengrid_cb, gengrid_del_cb, NULL, _gg_item_styles },
    { "Genlist", genlist_cb, genlist_del_cb, NULL, _gl_item_styles },
    { "Hoversel", hoversel_cb, hoversel_del_cb, NULL, NULL },
    { "Layout", layout_cb, layout_del_cb, NULL, NULL },
    { "Popup", popup_cb, popup_del_cb, NULL, NULL },
    { "Progressbar", progressbar_cb, progressbar_del_cb, NULL, NULL },
    { "Radio", radio_cb, radio_del_cb, NULL, NULL },
    { "Scroller", scroller_cb, scroller_del_cb, _sc_styles, NULL },
    { "Slider", slider_cb, slider_del_cb, _sl_styles, NULL },
    { "Tooltip", tooltip_cb, tooltip_del_cb, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

static appdata *app_data = NULL;

void table_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
    elm_table_clear(obj, EINA_TRUE);
}

static void _back_btn_clicked_cb(void *data, Evas_Object *obj, void *event)
{
    elm_naviframe_item_pop(obj);
}

static char *_text_get(void *data, Evas_Object *obj, const char *part)
{
    int i = (int) data;
    char buf[32];
    sprintf(buf, "%d %s", (i+1), widget_its[i].name);

    return strdup(buf);
}

static void
_selected(void *data, Evas_Object *obj, void *event_info)
{
    const char *txt = elm_object_item_text_get(event_info);
    elm_object_text_set(obj, txt);
}

static void
_item_sel(void *data, Evas_Object *obj, void *event_info)
{
    int i = (int) data, j;
    Evas_Object *layout, *box, *hov;

    layout = elm_layout_add(app_data->naviframe);
    elm_layout_file_set(layout, DATA_DIR"layout.edj", "elm_demo/main");
    evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(layout);

    // box 1
    box = elm_box_add(layout);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_part_content_set(layout, "widget", box);
    evas_object_show(box);
    app_data->widget_box = box;

    // box 2
    box = elm_box_add(layout);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_part_content_set(layout, "option", box);
    evas_object_show(box);
    app_data->option_box = box;
    elm_box_horizontal_set(box, EINA_TRUE);

    // hoversel 1
    hov = elm_hoversel_add(layout);
    elm_hoversel_hover_parent_set(hov, layout);
    evas_object_show(hov);
    evas_object_smart_callback_add(hov, "selected", _selected, NULL);
    elm_object_part_content_set(layout, "widget.style", hov);
    elm_object_disabled_set(hov, EINA_TRUE);
    app_data->style_hov = hov;

    if (widget_its[i].styles) {
        j = 0;
        elm_object_disabled_set(app_data->style_hov, EINA_FALSE);
        elm_object_text_set(app_data->style_hov, widget_its[i].styles[0]);
        while(widget_its[i].styles[j]) {
            elm_hoversel_item_add(app_data->style_hov,
                                  widget_its[i].styles[j], NULL, ELM_ICON_NONE, NULL, NULL);
            j++;
        }
    }
    else {
        elm_object_text_set(app_data->style_hov, "default");
        elm_object_disabled_set(app_data->style_hov, EINA_TRUE);
    }

    // hoversel 2
    hov = elm_hoversel_add(layout);
    elm_hoversel_hover_parent_set(hov, layout);
    evas_object_show(hov);
    evas_object_smart_callback_add(hov, "selected", _selected, NULL);
    elm_object_part_content_set(layout, "item.style", hov);
    elm_object_disabled_set(hov, EINA_TRUE);
    app_data->item_hov = hov;

    if (widget_its[i].it_styles) {
        elm_object_text_set(app_data->item_hov, "default");
        j = 0;
        elm_object_disabled_set(app_data->item_hov, EINA_FALSE);
        elm_object_text_set(app_data->item_hov, widget_its[i].it_styles[0]);
        while(widget_its[i].it_styles[j]) {
            elm_hoversel_item_add(app_data->item_hov,
                                  widget_its[i].it_styles[j], NULL, ELM_ICON_NONE, NULL, NULL);
            j++;
        }
    }
    else {
        elm_object_text_set(app_data->item_hov, "none");
        elm_object_disabled_set(app_data->item_hov, EINA_TRUE);
    }

    widget_its[i].func(app_data);
    elm_naviframe_item_push(app_data->naviframe,
                            widget_its[i].name, NULL, NULL, layout, NULL);
}

static Evas_Object *_widget_list_create(Evas_Object *parent)
{
    Evas_Object *list;
    int i = 0;

    list = elm_genlist_add(parent);
    elm_genlist_select_mode_set(list, ELM_OBJECT_SELECT_MODE_ALWAYS);
    evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);

    Elm_Genlist_Item_Class *itc;
    itc = elm_genlist_item_class_new();
    itc->item_style = "default";
    itc->func.text_get = _text_get;
    itc->func.content_get = NULL;
    itc->func.state_get = NULL;
    itc->func.del = NULL;

    while(widget_its[i].name)
    {
        elm_genlist_item_append(list, itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, _item_sel, (void *)i);
        i++;
    }

    elm_genlist_item_class_free(itc);

    return list;
}

void app_init(appdata *ad)
{
    Evas_Object *win, *conform, *naviframe, *list;

    elm_config_focus_highlight_enabled_set(EINA_TRUE);
    elm_config_focus_highlight_animate_set(EINA_TRUE);
    elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
    elm_theme_extension_add(NULL, DATA_DIR"button.edj"); // for customized button

    // window
    win = elm_win_util_standard_add("elm-demo-tizen-mobile", "elm-demo-tizen-mobile");
    elm_win_autodel_set(win, EINA_TRUE);
    elm_win_fullscreen_set(win, EINA_TRUE);
    elm_win_focus_highlight_style_set(win, "elmtv");
    evas_object_show(win);
    ad->win = win;

    // conform
    conform = elm_conformant_add(win);
    evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(win, conform);
    evas_object_show(conform);
    ad->conform = conform;

    // naviframe
    naviframe = elm_naviframe_add(conform);
    elm_object_content_set(conform, naviframe);
    evas_object_show(naviframe);
    ad->naviframe = naviframe;

    // widget list
    list = _widget_list_create(naviframe);
    elm_naviframe_item_push(naviframe, "Tizen 3.0 Mobile", NULL, NULL, list, NULL);
    eext_object_event_callback_add(naviframe, EEXT_CALLBACK_BACK, _back_btn_clicked_cb, NULL);
}

#if DESKTOP == 1
EAPI_MAIN
int elm_main(int argc, char **argv)
{
    char *edj_path = NULL;

    appdata *ad = calloc(1, sizeof(appdata));
    app_data = ad;

    if(argc == 2)
    {
        int len = strlen(argv[1]) + 1;
        edj_path = (char *)malloc(len);
        strncpy(edj_path, argv[1], len - 1);
        edj_path[len-1] = '\0';

        // Theme overlay when there is a command line parameter
        // otherwise, use environment variable.
        elm_theme_overlay_add(NULL, edj_path);

        free(edj_path);
    }

    app_init(ad);

    elm_run();

    elm_shutdown();

    free(ad);

    return 0;
}
ELM_MAIN()
#else
bool app_create(void *userdata)
{
    appdata *ad = userdata;

    app_init(ad);

    return true;
}

void app_terminate(void *user_data)
{
}

int main(int argc, char **argv)
{
    appdata app;
    memset(&app, 0, sizeof(app));
    struct appcore_ops ops = {
        .data = &app,
        .create = app_create,
        .terminate = app_terminate,
        .pause = NULL,
        .resume = NULL,
        .reset = NULL,
    };
    return appcore_efl_main("org.tizen.elm-demo-tizen-mobile", &argc, &argv, &ops);
}
#endif
