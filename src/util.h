#ifndef ELM_PLUGIN_UTIL_H
#define ELM_PLUGIN_UTIL_H

#include <Elementary.h>

#define D_LOG fprintf(stderr, "FILE: %s, LINE: %d, Function: %s\n", \
        __FILE__, __LINE__, __FUNCTION__)

/*******************Evas Util functions*************************/
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
Evas_Object *create_image(Evas_Object *, char *, char *);

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

Evas_Object *add_separator(Evas_Object *parent, Evas_Object *box, Eina_Bool horizontal);

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
Evas_Object *widget_min_set(Evas_Object *obj, Evas_Object *parent, Evas_Coord w, Evas_Coord h);
/***************************************************************/

/*********************** Key event function ************************/
typedef enum _KEY_TYPE
{
   RETURN_KEY,
   ESCAPE_KEY,
}KEY_TYPE;

/**
* @fn    create getKey
* @brief This function return the object of the key.
*
* @param [in] obj
*
* @param [out] Return the key object
*/
char *getKey(KEY_TYPE);

/****************************************************************/

#endif
