#include "main.h"

#define N_ITEMS 2000
#define BUFFER_SIZE 256
#define TIME_SET 5.0

int frame_cnt, ecore_cnt;
double entering_speed, frame_set;
Ecore_Animator *anim;

static Eina_Bool
check_ecore_anim(void *data EINA_UNUSED)
{
   ecore_cnt++;
   return ECORE_CALLBACK_RENEW;
}

static void
_render_post_cb(void *data,
                Evas *e EINA_UNUSED,
                void *event_info)
{
   frame_cnt++;
}

static void
_check_entering_speed(void *data,
                Evas *e,
                void *event_info)
{
    Elm_Object_Item *gl_item = data;
    evas_event_callback_del(e, EVAS_CALLBACK_RENDER_POST, _check_entering_speed);
    entering_speed = (ecore_time_get() - entering_speed) * 1000;
    frame_set = elm_config_scroll_bring_in_scroll_friction_get();
    elm_config_scroll_bring_in_scroll_friction_set(TIME_SET);
    elm_genlist_item_bring_in(gl_item, ELM_GENLIST_ITEM_SCROLLTO_IN);
}


void _start_calc(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   entering_speed = ecore_time_get();
   evas_object_smart_callback_del(obj, "changed", _start_calc);
   evas_event_callback_add(evas_object_evas_get(obj), EVAS_CALLBACK_RENDER_POST, _check_entering_speed, data);
}

void _start_check_fps(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Evas *e = evas_object_evas_get(obj);
   ecore_cnt = 0;
   anim = ecore_animator_add(check_ecore_anim, NULL);
   evas_event_callback_add(e, EVAS_CALLBACK_RENDER_POST, _render_post_cb, NULL);
}

void _stop_check_fps(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Evas_Object *obox = data;
   Evas_Object *ly1, *ly2, *ly3;
   Evas_Object *btn1, *btn2, *btn3;
   double fps = 0.0, animator_fps = 0.0;
   char buf[BUFFER_SIZE];
   Evas *e = evas_object_evas_get(obj);

   ly1 = elm_layout_add(obox);
   elm_layout_file_set(ly1, ELM_DEMO_EDJ, "perf_button_layout");
   ly2 = elm_layout_add(obox);
   elm_layout_file_set(ly2, ELM_DEMO_EDJ, "perf_button_layout");
   ly3 = elm_layout_add(obox);
   elm_layout_file_set(ly3, ELM_DEMO_EDJ, "perf_button_layout");

   btn1 = elm_button_add(obox);
   btn2 = elm_button_add(obox);
   btn3 = elm_button_add(obox);

   evas_event_callback_del(e, EVAS_CALLBACK_RENDER_POST, _render_post_cb);
   ecore_animator_del(anim);
   evas_object_smart_callback_del(obj, "scroll,anim,start", _start_check_fps);
   evas_object_smart_callback_del(obj, "scroll,anim,stop", _stop_check_fps);
   elm_config_scroll_bring_in_scroll_friction_set(frame_set);

   fps = frame_cnt / TIME_SET;
   animator_fps = ecore_cnt / TIME_SET;

   snprintf(buf, sizeof(buf), "Entering Speed : %3.1f msec", entering_speed);
   elm_object_text_set(btn1, buf);
   evas_object_show(btn1);
   elm_object_part_content_set(ly1, "elm.swallow.content", btn1);
   evas_object_show(ly1);
   elm_box_pack_end(obox, ly1);

   snprintf(buf, sizeof(buf), "Animator FPS : %3.1f fps", animator_fps);
   elm_object_text_set(btn2, buf);
   evas_object_show(btn2);
   elm_object_part_content_set(ly2, "elm.swallow.content", btn2);
   evas_object_show(ly2);
   elm_box_pack_end(obox, ly2);

   snprintf(buf, sizeof(buf), "Evas FPS : %3.1f fps", fps);
   elm_object_text_set(btn3, buf);
   evas_object_show(btn3);
   elm_object_part_content_set(ly3, "elm.swallow.content", btn3);
   evas_object_show(ly3);
   elm_box_pack_end(obox, ly3);
}

static char *_item_label_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[BUFFER_SIZE];
   int count = (int) data % 10;
   if (!strcmp(part, "elm.text"))
     {
        if (count == 0) sprintf(buf, "%s", "Time Warner Cable(Cable)");
        else if ((int) count == 1) sprintf(buf, "%s", "ComCast (Cable)");
        else if ((int) count == 2) sprintf(buf, "%s", "Dish (Satellite)");
        else if ((int) count == 3) sprintf(buf, "%s", "DirecTV (Satellite)");
        else if ((int) count == 4) sprintf(buf, "%s", "Tata Sky (Satellite)");
        else if ((int) count == 5) sprintf(buf, "%s", "Nextra Cable(Cable)");
        else if ((int) count == 6) sprintf(buf, "%s", "DD Plus (Cable)");
        else if ((int) count == 7) sprintf(buf, "%s", "Tikona Cable(Cable)");
        else if ((int) count == 8) sprintf(buf, "%s", "True Provider (Cable)");
        else if ((int) count == 9) sprintf(buf, "%s", "Vodafone (Satellite)");
        else sprintf(buf, "%s", "Sample Text");
     }

   return strdup(buf);
}

void performance_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *gl;
   Evas_Object *nf = data;
   Evas_Object *box, *box2;
   Elm_Object_Item *target_item = NULL;
   Elm_Genlist_Item_Class *ic;
   int i;

   frame_set = 0.0;
   frame_cnt = 0;
   entering_speed = 0.0;

   box = elm_box_add(nf);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(box);

   box2 = elm_box_add(box);
   elm_box_padding_set(box2, ELM_SCALE_SIZE(10), ELM_SCALE_SIZE(10));
   evas_object_show(box2);
   elm_box_pack_end(box, box2);

   gl = elm_genlist_add(nf);
   elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_genlist_homogeneous_set(gl, EINA_TRUE);
   elm_object_style_set(gl, "solid/default");
   elm_genlist_clear(gl);

   ic = elm_genlist_item_class_new();
   ic->item_style = "type1";
   ic->func.text_get = _item_label_get;
   ic->func.state_get = NULL;
   ic->func.del = NULL;

   for (i = 0; i < N_ITEMS; i++)
     {
        if (i == 999)
          target_item = elm_genlist_item_append(gl, ic, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
        else elm_genlist_item_append(gl, ic, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
     }

   elm_genlist_item_class_free(ic);

   evas_object_smart_callback_add(gl, "changed", _start_calc, (void *)target_item);
   evas_object_smart_callback_add(gl, "scroll,anim,start", _start_check_fps, NULL);
   evas_object_smart_callback_add(gl, "scroll,anim,stop", _stop_check_fps, (void *) box2);
   evas_object_show(gl);

   elm_box_pack_end(box, gl);

   elm_naviframe_item_push(nf, "Performance", NULL, NULL, box, NULL);
}
