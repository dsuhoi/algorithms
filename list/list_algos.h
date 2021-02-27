/*
 * list_algos.h
 * 
 * Copyright 2020 DSuhoi
 * 
 * Библиотека часто используемых функций и алгоритмов
 * для работы с односвязными списками. Функции ввода, 
 * вывода, заполнения, поиска и т.п.
 * (C library)
 */

#ifndef __LIST_LIB_H__
#define __LIST_LIB_H__


//**************
// Типы данных
//**************

typedef int TBase;  // искомая переменная (тип данных для массива и т.п.)
typedef int TCount; // переменная для дополнительных данных (константные аргументы функций и т.п.)


//************
// Константы
//************
#define DELIM_CHR ' '            // символ разделитель
#define CARR_CHR '\n'            // символ перевода каретки
#define FORMAT_COMMAND "%4d"     // команда форматирования
#define FORMAT_COMMAND_CNT "%4d" // команда форматирования для доп. данных


//***********************************************
// Константы для работы с односвязными списками
//***********************************************
#define MAX_LIST_SIZE 1000  // максимальное кол-во узлов в списке
// Для заполнения односвязных списков случайными числами раскомментируйте флаг
// и укажите диапазон для чисел RANDOM_RANGE
#define RANDOM_RANGE 500


//********************************************
// Функции по работе с односвязными списками
//********************************************

// Структура элементов списка
typedef struct List_node {
    struct List_node *p_next_node;
    TBase value; 
} List_node;


// Создание списка и его первого узла
List_node *init_list(const TBase new_value);
// Создание списка с numNode количеством узлов (заполнены случайными числами)
List_node *generate_list(const TCount num_node);

// Вставить узел со значением newValue в начало списка с вершиной head_node
void push_list(List_node **head_node, TBase new_value);
// Вставить узел со значением newValue в конец списка с вершиной head_node
void push_back_list(List_node *head_node, TBase new_value);

// Удалить начальный узел из списка с вершиной head_node
TBase pop_list(List_node **head_node);
// Удалить последний узел из списка с вершиной head_node
TBase pop_back_list(List_node **head_node);

// Вставить узел со значением newValue в позицию index списка с вершиной head_node
void insert_list(List_node *head_node, TCount index, TBase new_value);
// Удалить index узел из списка с вершиной head_node
TBase remove_list(List_node **head_node, TCount index);

// Получить index узел из списка с вершиной head_node
List_node *get_list(List_node *head_node, TCount index);
// Получить указатель на последний узел из списка с вершиной head_node
List_node *get_last_list(List_node *head_node);
// Получить размер списка (кол-во узлов в нём)
TCount get_size_list(List_node *head_node);

// Вывод узлов списка с вершиной head_node
void print_list(List_node *head_node);
// Ввод узлов списка с вершиной head_node
List_node *scan_list();

// Создание массива (с указателем на длину p_len) из элементов списка с вершиной head_node
TBase *list_to_array(List_node *head_node, TCount *p_len);
// Создание односвязного списка из массива arr с длиной len
List_node *array_to_list(TBase *arr, const TCount len);

#endif
