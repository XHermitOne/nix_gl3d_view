/**
 * Модуль модели в трехмерном пространстве
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */

#inclide <stdlib.h>
#include "model3d.h"
#include "logfunc.h"
#include "strfunc.h"

extern BOOL DebugMode;

/**
 * Создать объект
 */
BOOL create_model3d(nix_model3d_t *model3d)
{
    if ((model3d != NULL) && DebugMode)
        log_warning("Не инициализирован указатель модели трехмерного пространства перед созданием");

    model3d = (nix_model3d_t *) malloc(sizeof(nix_model3d_t));
    model3d->vertexes = (nix_single_linked_list_index_array_t *) malloc(sizeof(nix_double_linked_list_index_array_t));
    model3d->edges = (nix_single_linked_list_index_array_t *) malloc(sizeof(nix_double_linked_list_index_array_t));
    model3d->facets = (nix_single_linked_list_index_array_t *) malloc(sizeof(nix_double_linked_list_index_array_t));

    return TRUE;
}

/**
 * Удалить все данные о объекте
 */
BOOL destroy_model3d(nix_model3d_t *model3d)
{
    BOOL result = TRUE;

    if ((model3d == NULL) && DebugMode)
        log_warning("Модель трехмерного пространства уже удалена")
    else
    {
        result = result && destroy_single_linked_list_index_array(model3d->vertexes);
        result = result && destroy_single_linked_list_index_array(model3d->edges);
        result = result && destroy_single_linked_list_index_array(model3d->facets);
    }
    return result;
}

/**
 * Установить имя модели
 * @param name  Наименование модели
 */
BOOL set_model3d_name(nix_model3d_t *model3d, char *name)
{
    if ((model3d != NULL) && (name != NULL))
        return str_copy_limit(name, model3d->name, MODEL_NAME_MAX_LEN);
    return FALSE
}

/**
 * Получить имя модели
 * @return char* Наименование модели
 */
char *get_model3d_name(const nix_model3d_t *model3d)
{
    return model3d->name;
}


/**
 * Установить цвет линий объекта
 * @param line_color Цвет линии.
 */
BOOL set_model3d_line_color(nix_model3d_t *model3d, int line_color)
{
    return FALSE;
}

/**
 * Получить цвет линий объекта
 */
int get_model3d_line_color(const nix_model3d_t *model3d)
{
    return model3d->line_color;
}

/**
 * Функция определения количества ребер
 *
 */
unsigned int get_model3d_edge_count(const nix_model3d_t *model3d)
{
    if ((model3d == NULL) && DebugMode )
        log_warning("Не определена модель трехмерного пространства");

    if (model3d != NULL)
        if ((model3D->edges == NULL) && DebugMode)
            log_warning("В модели трехмерного пространства не определен список ребер")
        else
            return model3d->edges->count;
    return 0;
}

/**
 * Функции определения координат ребер
 *
 */
BOOL get_model3d_edge_coordinates(nix_model3d_t *model3d, double *x1, double *y1, double *z1, double *x2, double *y2, double *z2, unsigned int index)
{
    return FALSE;
}

/**
 * Определение количества граней
 *
 * @return unsigned int
 */
unsigned int get_model3d_facet_count(nix_model3d_t *model3d);

/**
 * Определить количество вершин каждой грани
 *
 * @param index Индекс грани
 * @return unsigned int
 */
unsigned int get_model3d_facet_count(nix_model3d_t *model3d, unsigned int index);

/**
 * Определение координаты вершины грани
 *
 * @param x
 * @param y
 * @param z
 * @param facet_index Индекс грани
 * @param vertex_index Индекс вершины
 */
BOOL get_model3d_facet_coordinates(nix_model3d_t *model3d, double *x, double *y, double *z, unsigned int facet_index, unsigned int vertex_index);

/**
 * Определение коэффициентов грани
 *
 * @param a
 * @param b
 * @param c
 * @param h
 * @param index Индекс грани
 * @return BOOL
 */
BOOL get_model3d_facet_coefficients(nix_model3d_t *model3d, double *a, double *b, double *c, double *h, unsigned int index);

/**
 * Установить коэффициенты плоскости грани
 *
 * @param hide_invisible
 * @param a
 * @param b
 * @param c
 * @param h
 * @param index Индекс грани
 */
//
BOOL set_model3d_facet_coefficients(nix_model3d_t *model3d, BOOL hide_invisible, double a, double b, double c, double h, unsigned int index);
