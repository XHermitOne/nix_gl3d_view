/**
 * Модуль модели в трехмерном пространстве
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */
#ifndef __MODEL3D_H
#define __MODEL3D_H

#include "listidx.h"

#define MODEL_NAME_MAX_LEN    256

/* Точка в трехмерном пространстве */
typedef struct
{
    double x;
    double y;
    double z;
} nix_point3d_t;

/* Ребро грани */
typedef struct
{

} nix_edge3d_t;

/* Грань */
typedef struct
{
    unsigned int vertex_count; /* Количество вершин одной грани (>=3) */
    /* Индексы вершин для каждой грани */

    /* Коэффициенты a,b,c,h одной грани */
    /* a * X + b * Y + c * Z = h - уравнение плоскости грани */
    BOOL hide_invisible; /* Флаг разрешения проверки на стирание невидимых линий */
    double a;
    double b;
    double c;
    double h;

} nix_facet3d_t;

/* Модель в трехмерном пространстве */
typedef struct
{
    char name[MODEL_NAME_LEN];      /* Имя объекта */
    int line_color;     /* Цвет линий */
    
    /* Описание вершин объекта */
    nix_single_linked_list_index_array_t *vertexes;     /* Массив координат вершин (Xw,Yw,Zw) */
    
    /* Описание ребер объекта */
    nix_single_linked_list_index_array_t *edges;
    
    /* Описание граней объекта */
    /* Грани должны быть выпуклыми(!!!) многоугольниками */
    nix_single_linked_list_index_array_t *facets;

    /* Преобразования в трехмерном пространстве */
    /*
     Вычисление матрицы поворота

           | r11  r12  r13  0 |
      R =  | r21  r22  r23  0 |
           | r31  r32  r33  0 |
           | r41  r42  r43  1 |

      Способ использования (см. функцию 'RotatePoint'):
        [_Xnew _Ynew _Znew  1] = [_X _Y _Z  1] R
      Точка (_Xnew,_Ynew,_Znew) является отображением точки (_X,_Y,_Z).
      Поворот на угол _Alpha осуществляется относительно оси
        (_Xa,_Ya,_Za)+lambda(_Xv,_Yv,_Zv).
    */
    /* Матрица поворота */
    double r11, r12, r13;
    double r21, r22, r23;
    double r31, r32, r33;
    double r41, r42, r43;
} nix_model3d_t;

//############## Внутренние функции ###############
//Расчитать и заполнить коэффициенты для всех граней объекта
// void FaceCoeffAlloc(void);

//Инициализация вектора и угла поворота
//(Вычисление матрицы поворота)
// void InitRotate(double _Xa, double _Ya, double _Za,
//                 double _Xv, double _Yv, double _Zv,
//                 double _Alpha);
//Поворот точки (_X,_Y,_Z) вокруг
//вектора (_Xv,_Yv,_Zv), проходящего ч/з точку (_Xa,_Ya,_Za)
//на угол _Alpha
//(_X,_Y,_Z) -> (_Xnew,_Ynew,_Znew)
// void RotatePoint(double _X, double _Y, double _Z,
//                  double *_Xnew, double *_Ynew, double *_Znew);


/* -------------------------- Публичные функции ------------------------ */
/**
 * Установить имя модели
 * @param name  Наименование модели
 */
BOOL set_model3d_name(nix_model3d_t *model3d, char *name);

/**
 * Получить имя модели
 * @return char* Наименование модели
 */
char *get_model3d_name(const nix_model3d_t *model3d);

/**
 * Установить цвет линий объекта
 * @param line_color Цвет линии.
 */
BOOL set_model3d_line_color(nix_model3d_t *model3d, int line_color);

/**
 * Получить цвет линий объекта
 */
int get_model3d_line_color(const nix_model3d_t *model3d);

/**
 * Функция определения количества ребер
 *
 */
unsigned int get_model3d_edge_count(const nix_model3d_t *model3d);

/**
 * Функции определения координат ребер
 *
 */
BOOL get_model3d_edge_coordinates(nix_model3d_t *model3d, double *x1, double *y1, double *z1, double *x2, double *y2, double *z2, unsigned int index);

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

/**
 * Создать объект
 */
BOOL create_model3d(nix_model3d_t *model3d);

/** 
 * Удалить все данные о объекте
 */
BOOL destroy_model3d(nix_model3d_t *model3d);

/* -------------------------- Функции движения ----------------------------------*/

/**
 * Перемещение объекта в напралении вектора (_VectorX,_VectorY,_VectorZ)
 */
BOOL move_model3d(nix_model3d_t *model3d, double vector_x, double vector_y, double vector_z);

/**
 * Поворот объекта(всех его точек) вокруг
 * вектора (vector_x, vector_y, vector_z), проходящего ч/з точку (x, y, z)
 * на угол angle
 *
 * @param x
 * @param y
 * @param z
 * @param vector_x
 * @param vector_y
 * @param vector_z
 * @param angle
 */
BOOL rotate_model3d(nix_model3d_t *model3d, double x, double y, double z,
                    double vector_x, double vector_y, double vector_z, double angle);

/**
 * Функция загрузки данных из файла
 *
 */
BOOL load_model3d(nix_model3d_t *model3d, char *filename);

#endif /*__MODEL3D_H*/
