#include <app_manager.h>
#include <app_control.h>
#include <aul.h>
#include "main.h"

static bool
is_shortcuts_running(void)
{
    bool running = false;
    int ret = app_manager_is_running("org.tizen.shortcuts", &running);
    return (ret == APP_MANAGER_ERROR_NONE) && running;
}

static void
shortcuts_launch(void)
{

    if (is_shortcuts_running())
    {
        return;
    }

    app_control_h app_control;

    int ret = app_control_create(&app_control);

    if (ret == APP_CONTROL_ERROR_NONE) {
        ret = app_control_set_app_id(app_control, "org.tizen.shortcuts");
    }

    if (ret == APP_CONTROL_ERROR_NONE) {
        ret = app_control_send_launch_request(app_control, NULL, NULL);
    }

    app_control_destroy(app_control);
}

static void
shortcuts_terminate(void)
{
    app_context_h app_context = NULL;

    int res = app_manager_get_app_context("org.tizen.shortcuts", &app_context);

    if (res != APP_MANAGER_ERROR_NONE) {
        return;
    }

    int pid;
    app_context_get_pid(app_context, &pid);

    res = aul_terminate_pid(pid);

    app_context_destroy(app_context);

}

static void
check_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
    if(!is_shortcuts_running())
        shortcuts_launch();
    else
        shortcuts_terminate();
}

static void
shortcuts_item_cb(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *shorcuts_onoff_check = data;
    Eina_Bool check_state = elm_check_state_get(shorcuts_onoff_check);

    elm_check_state_set(shorcuts_onoff_check, !check_state);

    if(!is_shortcuts_running())
        shortcuts_launch();
    else
        shortcuts_terminate();
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *it = event_info;
    elm_list_item_selected_set(it, EINA_FALSE);
}

void
shortcuts_cb(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *nf = data;
    Evas_Object *list;
    Evas_Object *shorcuts_onoff_check;

    list = elm_list_add(nf);
    elm_list_mode_set(list, ELM_LIST_COMPRESS);
    evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

    shorcuts_onoff_check = elm_check_add(list);
    elm_object_style_set(shorcuts_onoff_check, "on&off");
    elm_check_state_set(shorcuts_onoff_check, is_shortcuts_running());
    evas_object_smart_callback_add(shorcuts_onoff_check, "changed", check_changed_cb, NULL);
    evas_object_propagate_events_set(shorcuts_onoff_check, EINA_FALSE);

    elm_list_item_prepend(list, "Shorcuts", NULL, shorcuts_onoff_check, shortcuts_item_cb,
                            shorcuts_onoff_check);

    elm_list_go(list);

    elm_naviframe_item_push(nf, "Shortcuts", NULL, NULL, list, NULL);
}
