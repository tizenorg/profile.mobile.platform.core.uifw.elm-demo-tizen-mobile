#define EFL_BETA_API_SUPPORT
#include "main.h"

static Evas_Object*
create_layout(Evas_Object *parent)
{
	Evas_Object *layout = elm_layout_add(parent);
	elm_layout_file_set(layout, ELM_DEMO_EDJ, "primitives_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	return layout;
}

static Eina_Bool _color_change_cb(void *data, Evas_Object *obj, Elm_Access_Action_Info *action_info)
{
	int r, g;
	evas_object_color_get(data, &r, &g, NULL, NULL);
	if (r > g)
		evas_object_color_set(data, 0, 255, 0, 255);
	else
		evas_object_color_set(data, 255, 0, 0, 255);
	return EINA_TRUE;
}

static Evas_Object*
create_rectangle(Evas_Object *parent)
{
	Evas_Object *rect = evas_object_rectangle_add(evas_object_evas_get(parent));

	Evas_Object *access = elm_access_object_register(rect, parent);
	elm_access_info_set(access, ELM_ACCESS_INFO, "Super red Button");
	elm_access_info_set(access, ELM_ACCESS_CONTEXT_INFO, "Activate to change color");
	elm_access_action_cb_set(access, ELM_ACCESS_ACTION_ACTIVATE, _color_change_cb, rect);
	elm_atspi_accessible_role_set(access, ELM_ATSPI_ROLE_PUSH_BUTTON);

	evas_object_resize(rect, 100, 50);
	evas_object_color_set(rect, 255, 0, 0, 255);
	evas_object_show(rect);

	return rect;
}

static Evas_Object*
create_image(Evas_Object *parent)
{
	Evas_Object *img = evas_object_image_add(evas_object_evas_get(parent));
	evas_object_image_file_set(img, RESDIR "/images/contacts_ic_circle_btn_call.png", NULL);
	Evas_Load_Error err = evas_object_image_load_error_get(img);
	if (err != EVAS_LOAD_ERROR_NONE)
	{
		fprintf(stderr, "could not load image. error string is \"%s\"\n", evas_load_error_str(err));
		abort();
	}
	evas_object_image_fill_set(img, 0, 0, 100, 100);
	evas_object_resize(img, 100, 100);
	evas_object_show(img);

	Evas_Object *access = elm_access_object_register(img, parent);
	elm_access_info_set(access, ELM_ACCESS_INFO, "Sample Image");
	elm_access_info_set(access, ELM_ACCESS_CONTEXT_INFO, "Activate");
	elm_access_action_cb_set(access, ELM_ACCESS_ACTION_ACTIVATE, _color_change_cb, img);
	elm_atspi_accessible_role_set(access, ELM_ATSPI_ROLE_ICON);

	return img;
}

static char* _text_info_get(void *data, Evas_Object *obj)
{
   const char *ret = evas_object_text_text_get(data);
   return ret ? strdup(ret) : NULL;
}

static void
create_edje_primitive(Evas_Object *layout)
{
	Evas_Object *edje = elm_layout_edje_get(layout);
	Evas_Object *txt = (Evas_Object*)edje_object_part_object_get(edje, "text");

	Evas_Object *access = elm_access_object_register(txt, layout);
	elm_access_info_cb_set(access, ELM_ACCESS_INFO, _text_info_get, txt);
	elm_access_info_set(access, ELM_ACCESS_CONTEXT_INFO, "Some minor description of text");
	elm_atspi_accessible_role_set(access, ELM_ATSPI_ROLE_TEXT);
}

void
primitives_ui_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout, *p1, *p2;
	Evas_Object *nf = data;

	layout = create_layout(nf);

	p1 = create_rectangle(layout);
	elm_object_part_content_set(layout, "rectangle", p1);

	p2 = create_image(layout);
	elm_object_part_content_set(layout, "image", p2);

	create_edje_primitive(layout);

	elm_naviframe_item_push(nf, "Primitives Support", NULL, NULL, layout, NULL);
}
