
#define EFL_BETA_API_SUPPORT 1
#include <Elementary.h>

typedef struct vg_data_s
{
   Evas_Object *vg;  //vector object
   Evas_Coord_Point center;   //center position of vector object
   Elm_Transit *transit[5];   //reserved transits
   Efl_VG_Shape *shape[5];    //reserved shape nodes
   Ecore_Timer *timer;        //reseved timer
   int screen_w;              //screen width
   int screen_h;              //screen height
   Eina_Bool dirty;
} vg_data;


static void rect_toggle_chain_transits_go(vg_data *vd);
static void circle_toggle2_chain_transits_go(vg_data *vd);

static int screen_w = 0;       //Screen Width
static int screen_h = 0;       //Screen Height

static void
transit_del_cb(void *data, Elm_Transit *transit)
{
   /* Transition is just finished. Free All resources */
   vg_data *vd = data;
   free(vd);
}


static void
vg_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
   vg_data *vd = data;

   /* Any reason, Vector object size is changed.
      Update center position for vector drawing */
   Evas_Coord w, h;
   evas_object_geometry_get(obj, NULL, NULL, &w, &h);
   vd->center.x = (w/2);
   vd->center.y = (h/2);
   vd->dirty = EINA_TRUE;
}


Evas_Object *
create_vg_object(Evas_Object *grid, int x, int y, int w, int h, vg_data *vd)
{
   /* Create a vector object and pack into a grid */
   Evas *evas = evas_object_evas_get(grid);
   Evas_Object *vg = evas_object_vg_add(evas);
   evas_object_event_callback_add(vg, EVAS_CALLBACK_RESIZE, vg_resize_cb, vd);
   evas_object_show(vg);

   elm_grid_pack(grid, vg, x, y, w, h);

   return vg;
}

///////////////////////////////////////////////////////////////////////////////////////////////////#/
/* Round Rectangle Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_round_rect_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   const double SHAPE_SIZE[2] = {10, 10};
   const double SHAPE_SIZE_DIFF[2] = {50, 100};

   vg_data *vd = effect;

   
   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_rect(vd->shape[0],
                                           vd->center.x - (SHAPE_SIZE[0] / 2) - ((SHAPE_SIZE_DIFF[0] / 2) * progress),
                                           vd->center.y - (SHAPE_SIZE[1] / 2) - (SHAPE_SIZE_DIFF[1] * progress),
                                           SHAPE_SIZE[0] + (progress * SHAPE_SIZE_DIFF[0]),
                                           SHAPE_SIZE[1] + (progress * SHAPE_SIZE_DIFF[1]),
                                           10,
                                           10);

   evas_vg_node_color_set(vd->shape[0], 46, 160, 216, 255);
}

Eina_Bool
timer_round_rect_cb(void *data)
{
   vg_data *vd = data;

   //Transit for Translation
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vd->vg);
   elm_transit_effect_translation_add(transit, 0, 0, screen_w - 200, 0);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 2);

   vd->transit[1] = transit;
   vd->timer = NULL;

   elm_transit_go(transit);

   return ECORE_CALLBACK_CANCEL;
}

static void
example_round_rect(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 5, 5, 20, 30, vd);
   
   //Shape Node for Vector Drawing
   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);

   //Transit for Vector Drawing 
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_round_rect_op, vd, NULL);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);
   elm_transit_tween_mode_set(transit, ELM_TRANSIT_TWEEN_MODE_DECELERATE);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 0.35);

   /* Timer
      After 1 secs later, move the vector object */
   vd->timer = ecore_timer_add(1, timer_round_rect_cb, vd);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
///////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////////
/* Circle Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_circle_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double CIRCLE_RADIUS = 5;
   double CIRCLE_RADIUS_DIFF = 20;
   int COLOR[3] = {46, 160, 216};
   int COLOR_DIFF[3] = {209, -93, -200};

   vg_data *vd = effect;

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_circle(vd->shape[0],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE_RADIUS + (CIRCLE_RADIUS_DIFF * progress));

   evas_vg_node_color_set(vd->shape[0],
                          COLOR[0] + (COLOR_DIFF[0] * progress),
                          COLOR[1] + (COLOR_DIFF[1] * progress),
                          COLOR[2] + (COLOR_DIFF[2] * progress),
                          255);
}

Eina_Bool
timer_circle_cb(void *data)
{
   vg_data *vd = data;

   //Transit for Translation
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vd->vg);
   elm_transit_effect_translation_add(transit, 0, 0, screen_w - 200, 0);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 2);

   vd->transit[1] = transit;
   vd->timer = NULL;

   elm_transit_go(transit);

   return ECORE_CALLBACK_CANCEL;
}

static void
example_circle(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 5, 25, 20, 10, vd);

   //Shape Node for Vector Drawing
   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);

   //Transit 
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_circle_op, vd, NULL);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);
   elm_transit_tween_mode_set(transit, ELM_TRANSIT_TWEEN_MODE_DECELERATE);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 0.35);

   /* Timer
      After 1 secs later, move the vector object */
   vd->timer = ecore_timer_add(2, timer_circle_cb, vd);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////
/* Circle Touch Effect Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_circle_touch_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double CIRCLE_RADIUS = 40;
   double CIRCLE2_RADIUS = 30;
   double CIRCLE2_RADIUS_DIFF = 10;

   vg_data *vd = effect;

   /* 1. Outer Shape */

   //Set Shape Attributes
   if (vd->dirty) {
    vd->dirty = EINA_FALSE;
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_circle(vd->shape[0],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE_RADIUS);
   evas_vg_node_color_set(vd->shape[0], 46, 160, 216, 255);
  }
   /* 2. Touch Effect Shape */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_circle(vd->shape[1],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE2_RADIUS + (CIRCLE2_RADIUS_DIFF * progress));
      evas_vg_node_color_set(vd->shape[1], 40 - (40 * progress), 141 - (141 * progress), 165 - (165 * progress), (255 - (255 * progress)));
}

static void
example_circle_touch(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));
   vd->dirty = EINA_TRUE;

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 60, 30, 20, 20, vd);

   //Shape Node for Vector Drawing
   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Outer Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Touch Effect Shape

   //Transit 
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_circle_touch_op, vd, NULL);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_duration_set(transit, 1);
   double v[4] = { 0.31, 0.06, 0.0, 1.0 };
   elm_transit_tween_mode_factor_n_set(transit, 4, v);
   elm_transit_tween_mode_set(transit, ELM_TRANSIT_TWEEN_MODE_BEZIER_CURVE);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////
/* Round Rect Touch Effect Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_round_rect_touch_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double SHAPE_SIZE[2] = {150, 70};
   double SHAPE2_SIZE[2] = {130, 55};
   double SHAPE2_SIZE_DIFF[2] = {20, 15};

   vg_data *vd = effect;

   /* 1. Outer Shape */

   //Set Shape Attributes
   if (vd->dirty) {
   vd->dirty = EINA_FALSE;
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_rect(vd->shape[0],
                                           vd->center.x - (SHAPE_SIZE[0] / 2),
                                           vd->center.y - (SHAPE_SIZE[1] / 2),
                                           SHAPE_SIZE[0],
                                           SHAPE_SIZE[1],
                                           40,
                                           100);
   evas_vg_node_color_set(vd->shape[0], 46, 160, 216, 255);
   }


   /* 2. Inner Touch Effect Shape */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_rect(vd->shape[1],
                                           vd->center.x - (SHAPE2_SIZE[0] / 2) - ((SHAPE2_SIZE_DIFF[0] / 2) * progress),
                                           vd->center.y - (SHAPE2_SIZE[1] / 2) - ((SHAPE2_SIZE_DIFF[1] / 2) * progress),
                                           SHAPE2_SIZE[0] + (SHAPE2_SIZE_DIFF[0] * progress),
                                           SHAPE2_SIZE[1] + (SHAPE2_SIZE_DIFF[1] * progress),
                                           40,
                                           100);
   evas_vg_node_color_set(vd->shape[1], 40 - (40 * progress), 141 - (141 * progress), 165 - (165 * progress), 255 - (255 * progress));
}

static void
example_round_rect_touch(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));
   vd->dirty = EINA_TRUE;

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 50, 45, 50, 20, vd);

   //Shape Node for Vector Drawing
   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Outer Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Inner Touch Effect Shape

   //Transit 
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_round_rect_touch_op, vd, NULL);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_duration_set(transit, 1);
   double v[4] = { 0.31, 0.06, 0.0, 1.0 };
   elm_transit_tween_mode_factor_n_set(transit, 4, v);
   elm_transit_tween_mode_set(transit, ELM_TRANSIT_TWEEN_MODE_BEZIER_CURVE);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////
/* Rect Check Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_rect_toggle_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double SHAPE_SIZE[2] = {40, 40};
   double SHAPE2_SIZE[2] = {20, 20};
   double SHAPE2_SIZE_DIFF[2] = {20, 20};

   vg_data *vd = effect;

   /* Outer Shape */

   //Set Shape Attributes
   if (vd->dirty) {
   vd->dirty = EINA_FALSE;
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_rect(vd->shape[0],
                                            vd->center.x - (SHAPE_SIZE[0] / 2),
                                            vd->center.y - (SHAPE_SIZE[1] / 2),
                                            SHAPE_SIZE[0],
                                            SHAPE_SIZE[1],
                                            10,
                                            10);
   evas_vg_shape_stroke_width_set(vd->shape[0], 1.25);
   evas_vg_shape_stroke_color_set(vd->shape[0], 46, 160, 216, 255);
   }


   /* Inner Touch Effect Shape */
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_rect(vd->shape[1],
                                           vd->center.x - (SHAPE2_SIZE[0] / 2) - ((SHAPE2_SIZE_DIFF[0] / 2) * progress) + 0.5,
                                           vd->center.y - (SHAPE2_SIZE[1] / 2) - ((SHAPE2_SIZE_DIFF[1] / 2) * progress) + 0.5,
                                           SHAPE2_SIZE[0] + (SHAPE2_SIZE_DIFF[0] * progress),
                                           SHAPE2_SIZE[1] + (SHAPE2_SIZE_DIFF[1] * progress),
                                           10,
                                           10);
   //Set Shape Attributes
   evas_vg_node_color_set(vd->shape[1], 46 * progress, 160 * progress, 216 * progress, (255 * progress));
}

static void
transit_rect_toggle_op2(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double LINE_MOVE_TO[2] = {-5, 10};
   double LINE_LINE_TO[2] = {-10, -10};
   double LINE2_MOVE_TO[2] = {-5, 10};
   double LINE2_LINE_TO[2] = {20, -20};

   vg_data *vd = effect;

   /* Left Line */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[2]);
   evas_vg_shape_shape_append_move_to(vd->shape[2],
                                      vd->center.x + LINE_MOVE_TO[0],
                                      vd->center.y + LINE_MOVE_TO[1]);
   evas_vg_shape_shape_append_line_to(vd->shape[2],
                                      (vd->center.x + LINE_MOVE_TO[0]) + (LINE_LINE_TO[0] * progress),
                                      (vd->center.y + LINE_MOVE_TO[1]) + (LINE_LINE_TO[1] * progress));
   evas_vg_shape_stroke_width_set(vd->shape[2], 1.5);
   evas_vg_shape_stroke_color_set(vd->shape[2], 255, 255, 255, 255);


   /* Right Line */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[3]);
   evas_vg_shape_shape_append_move_to(vd->shape[3],
                                      vd->center.x + LINE2_MOVE_TO[0],
                                      vd->center.y + LINE2_MOVE_TO[1]);
   evas_vg_shape_shape_append_line_to(vd->shape[3],
                                      (vd->center.x + LINE2_MOVE_TO[0]) + (LINE2_LINE_TO[0] * progress),
                                      (vd->center.y + LINE2_MOVE_TO[1]) + (LINE2_LINE_TO[1] * progress));
   evas_vg_shape_stroke_width_set(vd->shape[3], 1.5);
   evas_vg_shape_stroke_color_set(vd->shape[3], 255, 255, 255, 255);
   evas_vg_shape_stroke_cap_set(vd->shape[3], EFL_GFX_CAP_ROUND);
}

static void
transit_rect_toggle_op3(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double LINE_MOVE_TO[2] = {-5, 10};
   double LINE_LINE_TO[2] = {-10, -10};
   double LINE2_MOVE_TO[2] = {-5, 10};
   double LINE2_LINE_TO[2] = {20, -20};

   vg_data *vd = effect;

   /* Left Line */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[2]);
   evas_vg_shape_shape_append_move_to(vd->shape[2],
                                      vd->center.x + LINE_MOVE_TO[0],
                                      vd->center.y + LINE_MOVE_TO[1]);
   evas_vg_shape_shape_append_line_to(vd->shape[2],
                                      (vd->center.x + LINE_MOVE_TO[0]) + (LINE_LINE_TO[0] - LINE_LINE_TO[0] * progress),
                                      (vd->center.y + LINE_MOVE_TO[1]) + (LINE_LINE_TO[1] - LINE_LINE_TO[1] * progress));

   /* Right Line */
   evas_vg_shape_shape_reset(vd->shape[3]);
   evas_vg_shape_shape_append_move_to(vd->shape[3],
                                      vd->center.x + LINE2_MOVE_TO[0],
                                      vd->center.y + LINE2_MOVE_TO[1]);
   evas_vg_shape_shape_append_line_to(vd->shape[3],
                                      (vd->center.x + LINE2_MOVE_TO[0]) + (LINE2_LINE_TO[0] - LINE2_LINE_TO[0] * progress),
                                      (vd->center.y + LINE2_MOVE_TO[1]) + (LINE2_LINE_TO[1] - LINE2_LINE_TO[1] * progress));
}

static void
transit_rect_toggle_op4(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   vg_data *vd = effect;

   /* Inner Touch Effect */

   //Set Shape Attributes
   evas_vg_node_color_set(vd->shape[1], 46 - (46 * progress), 160 - (160 * progress), 216 - (216 * progress), 255 - (255 * progress));
}

static void
transit_rect_toggle_del_cb(void *data, Elm_Transit *transit)
{
   /* Final Transition is finished, repeat the transitions */
   vg_data *vd = data;
   rect_toggle_chain_transits_go(vd);
}

static void
rect_toggle_chain_transits_go(vg_data *vd)
{
   //Transit - Fill Background
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vd->vg);
   elm_transit_effect_add(transit, transit_rect_toggle_op, vd, NULL);
   elm_transit_duration_set(transit, 0.5);
   elm_transit_objects_final_state_keep_set(transit, EINA_TRUE);

   //Transit - Check Drawing
   Elm_Transit *transit2 = elm_transit_add();
   elm_transit_object_add(transit2, vd->vg);
   elm_transit_effect_add(transit2, transit_rect_toggle_op2, vd, NULL);
   elm_transit_duration_set(transit2, 0.35);

   //Transit - Revert Check Drawing
   Elm_Transit *transit3 = elm_transit_add();
   elm_transit_object_add(transit3, vd->vg);
   elm_transit_effect_add(transit3, transit_rect_toggle_op3, vd, NULL);
   elm_transit_duration_set(transit3, 0.35);

   //Transit - Revert Background
   Elm_Transit *transit4 = elm_transit_add();
   elm_transit_object_add(transit4, vd->vg);
   elm_transit_effect_add(transit4, transit_rect_toggle_op4, vd, NULL);
   elm_transit_del_cb_set(transit4, transit_rect_toggle_del_cb, vd);
   elm_transit_duration_set(transit4, 0.5);

   //Chain Transits
   elm_transit_chain_transit_add(transit, transit2);
   elm_transit_chain_transit_add(transit2, transit3);
   elm_transit_chain_transit_add(transit3, transit4);

   vd->transit[0] = transit;
   vd->transit[1] = transit2;
   vd->transit[2] = transit3;
   vd->transit[3] = transit4;

   //Launch Transition
   elm_transit_go(transit);
}

static void
example_rect_toggle(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));
   vd->dirty = EINA_TRUE;
   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 5, 35, 20, 10, vd);

   //Shape Node for Vector Drawing
   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Outer Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Inner Touch Effect Shape
   vd->shape[2] = evas_vg_shape_add(root);  //Left Line
   vd->shape[3] = evas_vg_shape_add(root);  //Right Line

   vd->vg = vg;

   rect_toggle_chain_transits_go(vd);
}
////////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////////
/* Circle Toggle Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_circle_toggle_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Paramters
   double CIRCLE_RADIUS = 25;
   double CIRCLE2_RADIUS = 17;
   double CIRCLE2_RADIUS_DIFF = 5;
   double CIRCLE3_RADIUS = 13;
   double CIRCLE3_RADIUS_DIFF = -13;

   vg_data *vd = effect;

   /* Outer Circle */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_circle(vd->shape[0],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE_RADIUS);
   evas_vg_node_color_set(vd->shape[0], 101 - 51 * (progress), 180 - 90 * (progress), 233 - 116 * (progress), 255 - 127 * (progress));
   evas_vg_shape_stroke_color_set(vd->shape[0], 46, 160, 216, 255);
   evas_vg_shape_stroke_width_set(vd->shape[0], 1);


   /* Middle Circle */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_circle(vd->shape[1],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE2_RADIUS + (CIRCLE2_RADIUS_DIFF * progress));
   evas_vg_node_color_set(vd->shape[1], 255, 255, 255, 255);


   /* Inner Circle */

   //Set Shape Attribute
   evas_vg_shape_shape_reset(vd->shape[2]);
   evas_vg_shape_shape_append_circle(vd->shape[2],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE3_RADIUS + (CIRCLE3_RADIUS_DIFF * progress));
   evas_vg_node_color_set(vd->shape[2], 46 - 23 * (progress), 160 - 80 * (progress), 216 - 108 * (progress), 255 - (127 * progress));
}

static void
example_circle_toggle(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 30, 33, 15, 15, vd);

   //Shape Node for Vector Drawing
   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Outer Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Middle Shape
   vd->shape[2] = evas_vg_shape_add(root);  //Inner Shape

   //Transit 
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_circle_toggle_op, vd, NULL);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 0.5);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////
/* Morphing Circle Toggle Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_circle_toggle2_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   double CIRCLE_RADIUS = 35;
   int COLOR[3] = {129, 138, 140};
   int COLOR_DIFF[3] = {-85, 6, -67};

   vg_data *vd = effect;

   /* Outer Shape */

   //Set Shape Attributes
   if (vd->dirty) {
   vd->dirty = EINA_FALSE;
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_circle(vd->shape[0],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE_RADIUS);
   evas_vg_shape_stroke_width_set(vd->shape[0], 1);
   }

   evas_vg_node_color_set(vd->shape[0],
                          COLOR[0] + (progress * COLOR_DIFF[0]),
                          COLOR[1] + (progress * COLOR_DIFF[1]),
                          COLOR[2] + (progress * COLOR_DIFF[2]),
                          255);
}

static void
transit_circle_toggle2_op2(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   const double LINE_Y_HALF = 20;

   vg_data *vd = effect;

   /* Inner Line */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_move_to(vd->shape[1],
                                      vd->center.x,
                                      vd->center.y - LINE_Y_HALF + (LINE_Y_HALF * progress));
   evas_vg_shape_shape_append_line_to(vd->shape[1],
                                      vd->center.x,
                                      vd->center.y + LINE_Y_HALF - (LINE_Y_HALF * progress));

   evas_vg_shape_stroke_width_set(vd->shape[1], 1.75);
   evas_vg_shape_stroke_cap_set(vd->shape[1], EFL_GFX_CAP_ROUND);
   evas_vg_shape_stroke_color_set(vd->shape[1], 255, 255, 255, 255);
}

static void
transit_circle_toggle2_op3(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   double CIRCLE_RADIUS = 0;
   double CIRCLE_RADIUS_DIFF = 20;

   vg_data *vd = effect;

   /* Inner Circle */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[2]);
   evas_vg_shape_shape_append_circle(vd->shape[2],
                                     vd->center.x,
                                     vd->center.y,
                                     CIRCLE_RADIUS + (CIRCLE_RADIUS_DIFF * progress));
   evas_vg_shape_stroke_width_set(vd->shape[2], 1.5);
   evas_vg_shape_stroke_color_set(vd->shape[2], 255, 255, 255, 255);
}

static void
transit_circle_toggle2_op4(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   const double LINE_Y_HALF = 20;

   vg_data *vd = effect;

   /* Inner Line */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_move_to(vd->shape[1],
                                      vd->center.x,
                                      vd->center.y - LINE_Y_HALF + (LINE_Y_HALF * (1 - progress)));
   evas_vg_shape_shape_append_line_to(vd->shape[1],
                                      vd->center.x,
                                      vd->center.y + LINE_Y_HALF - (LINE_Y_HALF * (1 - progress)));
}

static void
transit_circle_toggle2_del_cb(void *data, Elm_Transit *transit)
{
   vg_data *vd = data;
   circle_toggle2_chain_transits_go(vd);
}

static void
circle_toggle2_chain_transits_go(vg_data *vd)
{
   //Transit 1 - Line
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vd->vg);
   elm_transit_effect_add(transit, transit_circle_toggle2_op2, vd, NULL);
   elm_transit_duration_set(transit, 0.25);
   elm_transit_objects_final_state_keep_set(transit, EINA_TRUE);

   //Transit 2 - Circle
   Elm_Transit *transit2 = elm_transit_add();
   elm_transit_object_add(transit2, vd->vg);
   elm_transit_effect_add(transit2, transit_circle_toggle2_op3, vd, NULL);
   elm_transit_duration_set(transit2, 0.25);
   elm_transit_auto_reverse_set(transit2, EINA_TRUE);
   elm_transit_objects_final_state_keep_set(transit2, EINA_TRUE);

   //Transit 3 - Line (Reverse)
   Elm_Transit *transit3 = elm_transit_add();
   elm_transit_object_add(transit3, vd->vg);
   elm_transit_effect_add(transit3, transit_circle_toggle2_op4, vd, NULL);
   elm_transit_duration_set(transit3, 0.25);
   elm_transit_objects_final_state_keep_set(transit3, EINA_TRUE);
   elm_transit_del_cb_set(transit3, transit_circle_toggle2_del_cb, vd);

   elm_transit_chain_transit_add(transit, transit2);
   elm_transit_chain_transit_add(transit2, transit3);

   vd->transit[1] = transit;
   vd->transit[2] = transit2;
   vd->transit[3] = transit3;

   elm_transit_go(transit);
}

static void
example_circle_toggle2(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));
   vd->dirty = EINA_TRUE;

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 30, 45, 20, 20, vd);

   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Outer Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Inner Line Shape
   vd->shape[2] = evas_vg_shape_add(root);  //Inner Circle Shape

   //Transit
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_circle_toggle2_op, vd, NULL);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 0.5);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);

   circle_toggle2_chain_transits_go(vd);
}
////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////
/* Star Toggle Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_star_toggle_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   #define PT_CNT 10
   const double STAR_PT[PT_CNT][2] = {{0, -20}, {5, -5}, {20, -5}, {7, 4}, {13, 20},
                                      {0, 12}, {-13, 20}, {-7, 4}, {-20, -5}, {-5, -5}};

   int i;
   double diff[2];

   vg_data *vd = effect;

   /* Outer Shape */
   if (vd->dirty) {
   vd->dirty = EINA_FALSE;
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_move_to(vd->shape[0],
                                      vd->center.x + STAR_PT[0][0],
                                      vd->center.y + STAR_PT[0][1]);
   for (i = 1; i < PT_CNT; i++) {
     evas_vg_shape_shape_append_line_to(vd->shape[0],
                                        vd->center.x + STAR_PT[i][0],
                                        vd->center.y + STAR_PT[i][1]);
   }
   evas_vg_shape_shape_append_close(vd->shape[0]);

   //Set Shape Attributes
   evas_vg_shape_stroke_color_set(vd->shape[0], 247, 178, 26, 255);
   evas_vg_shape_stroke_width_set(vd->shape[0], 1);
   evas_vg_shape_stroke_join_set(vd->shape[0], EFL_GFX_JOIN_ROUND);
   }

   Eina_Matrix3 translate;
   eina_matrix3_translate(&translate, vd->center.x, vd->center.y);


   Eina_Matrix3 rotate;
   double radian = 360 * progress * 2 * 3.141 / 360.0;
   eina_matrix3_rotate(&rotate, radian);

   Eina_Matrix3 scale;
   eina_matrix3_scale(&scale, 1 + .5 * progress, 1 + .5 * progress);

   Eina_Matrix3 result1;
   eina_matrix3_compose(&translate, &scale, &result1);

   Eina_Matrix3 result2;
   eina_matrix3_compose(&result1, &rotate, &result2);

   eina_matrix3_translate(&translate, -vd->center.x, -vd->center.y);

   Eina_Matrix3 result;
   eina_matrix3_compose(&result2, &translate, &result);
   evas_vg_node_transformation_set(vd->shape[0], &result);

   /* Inner Shape */

   //Set Shape Attributes
   diff[0] = (STAR_PT[0][0] * (progress * 0.65 + 0.35));
   diff[1] = (STAR_PT[0][1]) * (progress * 0.65 + 0.35);
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_move_to(vd->shape[1],
                                      vd->center.x + diff[0] + 0.5,
                                      vd->center.y + diff[1] + 0.5);
   for (i = 1; i < PT_CNT; i++)
     {
        diff[0] = (STAR_PT[i][0] * (progress * 0.65 + 0.35));
        diff[1] = (STAR_PT[i][1]) * (progress * 0.65 + 0.35);
        evas_vg_shape_shape_append_line_to(vd->shape[1],
                                           vd->center.x + diff[0] + 0.5,
                                           vd->center.y + diff[1] + 0.5);
     }
   evas_vg_shape_shape_append_close(vd->shape[1]);

   evas_vg_node_color_set(vd->shape[1], 247 * progress, 178 * progress, 26 * progress, 255 * progress);
   evas_vg_shape_stroke_color_set(vd->shape[1], 247 * progress, 178 * progress, 26 * progress, 255 * progress);
   evas_vg_shape_stroke_join_set(vd->shape[1], EFL_GFX_JOIN_ROUND);
   evas_vg_node_transformation_set(vd->shape[1], &result);
}

static void
example_star_toggle(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));
   vd->dirty = EINA_TRUE;
   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 5, 45, 20, 20, vd);

   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Outer Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Inner Line Shape

   //Transit
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_star_toggle_op, vd, NULL);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_duration_set(transit, 1.5);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////
/* Line Progress Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_progress_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   double LINE_HALF_SIZE = 200;

   double pos;
   double v[4];

   vg_data *vd = effect;

   /* Outer Shape */

   //Set Shape Attributes
   if (vd->dirty) {
   vd->dirty = EINA_FALSE;
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_move_to(vd->shape[0],
                                      vd->center.x - LINE_HALF_SIZE,
                                      vd->center.y);
   evas_vg_shape_shape_append_line_to(vd->shape[0],
                                      vd->center.x + LINE_HALF_SIZE,
                                      vd->center.y);
   evas_vg_shape_stroke_color_set(vd->shape[0], 203, 205, 206, 255);
   evas_vg_shape_stroke_width_set(vd->shape[0], 4);
   evas_vg_shape_stroke_cap_set(vd->shape[0], EFL_GFX_CAP_ROUND);
   }


   /* Fill Line Shape */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[1]);
   evas_vg_shape_shape_append_move_to(vd->shape[1],
                                      vd->center.x - LINE_HALF_SIZE,
                                      vd->center.y);
   v[0] = 0.15;
   v[1] = 0.84;
   v[2] = 0.28;
   v[3] = 0.96;
   pos = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v);

   evas_vg_shape_shape_append_line_to(vd->shape[1],
                                      vd->center.x - LINE_HALF_SIZE + (LINE_HALF_SIZE * 2 * pos),
                                      vd->center.y);
   evas_vg_shape_stroke_color_set(vd->shape[1], 181, 225, 236, 255);
   evas_vg_shape_stroke_width_set(vd->shape[1], 4);
   evas_vg_shape_stroke_cap_set(vd->shape[1], EFL_GFX_CAP_ROUND);


   /* Cursor Shape */
   pos = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v);

   v[0] = 0.33;
   v[1] = 0.66;
   v[2] = 0.76;
   v[3] = 0.8;
   pos = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v);
   evas_vg_shape_shape_reset(vd->shape[2]);
   evas_vg_shape_shape_append_move_to(vd->shape[2],
                                      vd->center.x - LINE_HALF_SIZE + (LINE_HALF_SIZE * 2 * pos),
                                      vd->center.y);
   v[0] = 0.15;
   v[1] = 0.84;
   v[2] = 0.28;
   v[3] = 0.96;
   pos = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v);

   evas_vg_shape_shape_append_line_to(vd->shape[2],
                                      vd->center.x - LINE_HALF_SIZE + (LINE_HALF_SIZE * 2 * pos),
                                      vd->center.y);
   //Set Shape Attributes
   evas_vg_shape_stroke_color_set(vd->shape[2], 48, 170, 204, 255);
   evas_vg_shape_stroke_width_set(vd->shape[2], 4);
   evas_vg_shape_stroke_cap_set(vd->shape[2], EFL_GFX_CAP_ROUND);
}

static void
example_progress(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));
   vd->dirty = EINA_TRUE;
   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 0, 65, 100, 5, vd);

   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //BG Shape
   vd->shape[1] = evas_vg_shape_add(root);  //Fill Line Shape
   vd->shape[2] = evas_vg_shape_add(root);  //Cursor Shape

   //Transit
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_progress_op, vd, NULL);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_duration_set(transit, 1);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////
/* Circle Progress Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
// static void
// transit_progress2_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
// {
//    //Input Parameters
//    //const double CIRCLE_RADIUS = 50;

//    // double *path_pts;
//    // double pos, pos2;
//    // double v[4];
//    // double v2[4];

//    vg_data *vd = effect;

//    /* Outer Shape */

//    //Set Shape Attributes
//    // v[0] = 0.0;
//    // v[1] = 1.0;
//    // v[2] = 0.7;
//    // v[3] = 0.94;
//    // pos = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v);

//    // v2[0] = 0.73;
//    // v2[1] = 0.79;
//    // v2[2] = 0.7;
//    // v2[3] = 0.94;
//    // pos2 = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v2);

//    // // evas_vg_shape_shape_append_arc(vd->shape[0],
//    // //                                10,
//    // //                                50,
//    // //                                2 * CIRCLE_RADIUS,
//    // //                                2 * CIRCLE_RADIUS,
//    // //                                90 + (-360 * pos2),
//    // //                                -360 * pos - (-360 * pos2));

//    // evas_vg_shape_stroke_color_set(vd->shape[0], 181, 225, 236, 255);
//    // evas_vg_shape_stroke_width_set(vd->shape[0], 4);
//    // evas_vg_shape_stroke_cap_set(vd->shape[0], EFL_GFX_CAP_ROUND);


//    // /* Inner Shape */

//    // //Set Shape Attributes
//    // v[0] = 0.0;
//    // v[1] = 1.0;
//    // v[2] = 0.7;
//    // v[3] = 0.94;
//    // pos = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v);

//    // v2[0] = 0.33;
//    // v2[1] = 0.79;
//    // v2[2] = 0.7;
//    // v2[3] = 0.94;
//    // pos2 = ecore_animator_pos_map_n(progress, ECORE_POS_MAP_CUBIC_BEZIER, 4, v2);

//    // evas_vg_shape_shape_append_arc(vd->shape[1],
//    //                                10,
//    //                                50,
//    //                                2 * CIRCLE_RADIUS,
//    //                                2 * CIRCLE_RADIUS,
//    //                                90 + (-360 * pos2),
//    //                                -360 * pos - (-360 * pos2));

//    evas_vg_shape_stroke_color_set(vd->shape[1], 48, 170, 204, 255);
//    evas_vg_shape_stroke_width_set(vd->shape[1], 4);
//    evas_vg_shape_stroke_cap_set(vd->shape[1], EFL_GFX_CAP_ROUND);
// }

// static void
// example_progress2(Evas_Object *grid)
// {
//    vg_data *vd = calloc(1, sizeof(vg_data));

//    //Vector Object
//    Evas_Object *vg = create_vg_object(grid, 5, 70, 50, 30, vd);

//    Efl_VG *root = evas_object_vg_root_node_get(vg);
//    vd->shape[0] = evas_vg_shape_add(root);  //Fill Line Shape
//    vd->shape[1] = evas_vg_shape_add(root);  //Cursor Shape

//    //Transit
//    Elm_Transit *transit = elm_transit_add();
//    elm_transit_object_add(transit, vg);
//    elm_transit_effect_add(transit, transit_progress2_op, vd, NULL);
//    elm_transit_repeat_times_set(transit, -1);
//    elm_transit_duration_set(transit, 1);
//    elm_transit_del_cb_set(transit, transit_del_cb, vd);

//    vd->vg = vg;
//    vd->transit[0] = transit;

//    //Launch Transition
//    elm_transit_go(transit);
// }
////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////
/* Index Drawing */
///////////////////////////////////////////////////////////////////////////////////////////////////
static void
transit_index_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   //Input Parameters
   const double CIRCLE_RADIUS = 45;
   const double CIRCLE_RADIUS_DIFF = 5;
   const double MOVE_Y = 20;

   vg_data *vd = effect;

   /* Outer Shape */

   //Set Shape Attributes
   evas_vg_shape_shape_reset(vd->shape[0]);
   evas_vg_shape_shape_append_circle(vd->shape[0],
                                     vd->center.x,
                                     vd->center.y - (MOVE_Y * progress),
                                     CIRCLE_RADIUS + (CIRCLE_RADIUS_DIFF * progress));
   evas_vg_node_color_set(vd->shape[0], 46 * progress, 160 * progress, 216 * progress, 255 * progress);
}


static void
example_index(Evas_Object *grid)
{
   vg_data *vd = calloc(1, sizeof(vg_data));

   //Vector Object
   Evas_Object *vg = create_vg_object(grid, 50, 70, 50, 30, vd);

   Efl_VG *root = evas_object_vg_root_node_get(vg);
   vd->shape[0] = evas_vg_shape_add(root);  //Circle

   //Transit
   Elm_Transit *transit = elm_transit_add();
   elm_transit_object_add(transit, vg);
   elm_transit_effect_add(transit, transit_index_op, vd, NULL);
   elm_transit_repeat_times_set(transit, -1);
   elm_transit_duration_set(transit, 1);
   elm_transit_tween_mode_set(transit, ELM_TRANSIT_TWEEN_MODE_DECELERATE);
   elm_transit_auto_reverse_set(transit, EINA_TRUE);
   elm_transit_del_cb_set(transit, transit_del_cb, vd);

   vd->vg = vg;
   vd->transit[0] = transit;

   //Launch Transition
   elm_transit_go(transit);
}


void
vector_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *nf = data;
   elm_win_screen_size_get(elm_object_top_widget_get(nf), NULL, NULL, &screen_w, &screen_h);
   Evas_Object *grid = elm_grid_add(nf);

   
   //Scalable Round Rectangle
   example_round_rect(grid);

   //Scalable Circle   //                                10,
   //                                50,
   //                                2 * CIRCLE_RADIUS,
   //                                2 * CIRCLE_RADIUS,
   //                                90 + (-360 * pos2),
   //                                -360 * pos - (-360 * pos2));
   example_circle(grid);

   // //Circle Touch Effect
    example_circle_touch(grid);

   // //Round Rect Touch Effect
    example_round_rect_touch(grid);

   //Rectangular Toggle
   example_rect_toggle(grid);

   //Stripe Circle Toggle
   example_circle_toggle(grid);

   //Morphing Circle Toggle
   example_circle_toggle2(grid);

   //Start Toggle
   example_star_toggle(grid);

   //Line Progress
   example_progress(grid);

   //Circle Progress
   //example_progress2(grid);

   //Index
   example_index(grid);

   elm_naviframe_item_push(nf, "Vector Drawing", NULL, NULL, grid, NULL);
}
