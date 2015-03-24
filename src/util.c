#include "util.h"

/***************** Evas helper functions *******************************/
/**
* @fn    create_image
* @brief This function return the object of the image.
*
* @param [in] parent
* @param [in] path
* @param [in] group
*
* @param [out] Return the image object
*/
Evas_Object *create_image(Evas_Object *parent, char *path, char *group)
{
    Evas_Object *img;
    img = elm_image_add(parent);
    elm_image_file_set(img, path, group);
    evas_object_show(img);

    return img;
}

/**
* @fn    add separater
* @brief This function return the object of the separater.
*
* @param [in] parent
* @param [in] box
* @param [in] horizontal
*
* @param [out] Return the separator object
*/
Evas_Object *add_separator(Evas_Object *parent, Evas_Object *box, Eina_Bool horizontal)
{
    Evas_Object *sp = elm_separator_add(parent);
    elm_separator_horizontal_set(sp, horizontal); // by default, separator is vertical, we must set it horizontal
    elm_box_pack_end(box, sp);
    evas_object_show(sp);

    return sp;
}

/**
* @fn    create widget_min_set
* @brief This function create the object of the table.
*
* @param [in] obj
* @param [in] parent
* @param [in] coordinate w
* @param [in] coordinate h
*
* @param [out] Return the table object
*/
Evas_Object *widget_min_set(Evas_Object *obj, Evas_Object *parent, Evas_Coord w, Evas_Coord h)
{
    Evas_Object *table, *rect;

    table = elm_table_add(parent);

    rect = evas_object_rectangle_add(evas_object_evas_get(table));
    evas_object_size_hint_min_set(rect, w, h);
    evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(table, rect, 0, 0, 1, 1);

    evas_object_size_hint_weight_set(obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(obj, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(table, obj, 0, 0, 1, 1);

    return table;
}

/**
* @fn    create getKey
* @brief This function return the object of the key.
*
* @param [in] obj
*
* @param [out] Return the key object
*/
char *getKey(KEY_TYPE kt)
{
    static char *keys[] =
    {
        "XF86Back",
        "Escape"
    };

   return keys[kt];
}

/**
* @fn    create get_format
* @brief This function return the length of string.
*
* @param [in] format
* @param [in] value
*
* @param [out] Return the string
*/

char *get_format(char *format, char *value)
{
    int len = strlen(format) + strlen(value);
    char *str = (char *)malloc(len+1);
    sprintf(str, format, value);

    return str;
}
