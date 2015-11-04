#include <app_manager.h>
#include <app_control.h>
#include <aul.h>
#include "main.h"

static bool
is_app_toolbox_running(void)
{
	int ret;
	bool running = false;

	ret = app_manager_is_running("org.tizen.app_toolbox", &running);
	return (ret == APP_MANAGER_ERROR_NONE) && running;
}

static void
app_toolbox_launch(void)
{
	app_control_h app_control;
	int ret = 0;

	if (is_app_toolbox_running())
		return;

	ret = app_control_create(&app_control);
	if (ret == APP_CONTROL_ERROR_NONE)
		ret = app_control_set_app_id(app_control, "org.tizen.app_toolbox");
	if (ret == APP_CONTROL_ERROR_NONE)
		ret = app_control_send_launch_request(app_control, NULL, NULL);

	app_control_destroy(app_control);
}

static void
app_toolbox_terminate(void)
{
	int pid;
	int res;
	app_context_h app_context = NULL;

	res = app_manager_get_app_context("org.tizen.app_toolbox", &app_context);

	if (res != APP_MANAGER_ERROR_NONE)
		return;

	app_context_get_pid(app_context, &pid);
	res = aul_terminate_pid(pid);
	app_context_destroy(app_context);
}

static void
check_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	if(!is_app_toolbox_running())
		app_toolbox_launch();
	else
		app_toolbox_terminate();
}

static void
app_toolbox_item_cb(void *data, Evas_Object *obj, void *event_info)
{
	Eina_Bool check_state;
	Evas_Object *app_toolbox_onoff_check = data;

	if(!elm_check_state_get(app_toolbox_onoff_check))
	{
		app_toolbox_launch();
		elm_check_state_set(app_toolbox_onoff_check, is_app_toolbox_running());
	}
	else
	{
		app_toolbox_terminate();
		elm_check_state_set(app_toolbox_onoff_check, EINA_FALSE);
	}
}

static void
list_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

void
app_toolbox_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *nf = data;
	Evas_Object *list;
	Evas_Object *app_toolbox_onoff_check;

	list = elm_list_add(nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	app_toolbox_onoff_check = elm_check_add(list);
	elm_object_style_set(app_toolbox_onoff_check, "on&off");
	elm_check_state_set(app_toolbox_onoff_check, is_app_toolbox_running());
	evas_object_smart_callback_add(app_toolbox_onoff_check, "changed", check_changed_cb, NULL);
	evas_object_propagate_events_set(app_toolbox_onoff_check, EINA_FALSE);

	elm_list_item_prepend(list, "App Toolbox", NULL, app_toolbox_onoff_check, app_toolbox_item_cb,
			app_toolbox_onoff_check);
	elm_list_go(list);
	elm_naviframe_item_push(nf, "App Toolbox", NULL, NULL, list, NULL);
}

