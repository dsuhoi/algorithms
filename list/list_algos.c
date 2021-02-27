#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list_algos.h"


//********************************************
// Функции по работе с односвязными списками
//********************************************

// Создание списка и его первого узла
List_node *init_list(const TBase new_value)
{
    // Выделение памяти под первый узел и присвоение значений
    List_node *head_node = malloc(sizeof(List_node));
    head_node->value = new_value;
    return head_node;
}

// Создание списка с numNode количеством узлов (заполнены случайными числами)
List_node *generate_list(const TCount num_node)
{
    List_node *head_node = init_list(0);   // Первый элемент является нулевым
    #ifdef RANDOM_RANGE
        srand(time(NULL));
    #endif
    // Если заполнение случайными числами отключено, то заполняем узлы 0
    for (size_t index = 1; index < num_node; ++index)
        #ifdef RANDOM_RANGE
            push_back_list(head_node, rand() % RANDOM_RANGE);
        #else
            push_back_list(head_node, 0);
        #endif
    return head_node;
}


// Вставить узел со значением new_value в начало списка с вершиной head_node
void push_list(List_node** head_node, TBase new_value)
{
    // Выделение памяти под первый узел и присвоение значений
    List_node *new_node = malloc(sizeof(List_node));
    new_node->value = new_value;
    // Смена указателя на верхний узел
    new_node->p_next_node = (*head_node);
    // Перестановка указателя на новый верхний узел
    (*head_node) = new_node;
}

// Вставить узел со значением new_value в конец списка с вершиной head_node
void push_back_list(List_node* head_node, TBase new_value)
{
    // Выделение памяти под первый узел и присвоение значений
    List_node *new_node = malloc(sizeof(List_node));
    new_node->value = new_value;
    new_node->p_next_node = NULL;
    // Получение указателя на последний узел
    List_node *last_node = get_last_list(head_node);
    last_node->p_next_node = new_node;
}


// Удалить начальный узел из списка с вершиной head_node
TBase pop_list(List_node **head_node)
{
    // Проверка на наличие узлов в списке
    if (head_node == NULL)
        return 0;

    // Создание указателя на вершину списка
    List_node *last_node = (*head_node);
    TBase last_value = last_node->value;
    (*head_node) = (*head_node)->p_next_node;
    // Удаление узла
    free(last_node);
    // Возвращение значения удалённого узла
    return last_value;
}

// Удалить последний узел из списка с вершиной head_node
TBase pop_back_list(List_node **head_node)
{
    // Проверка на наличие узлов в списке
    if (head_node == NULL)
        return 0;
    // Проверка на наличие одного узла в списке и его удаление
    if ((*head_node)->p_next_node == NULL){
        free(*head_node);
        *head_node = NULL;
        return 0;
    }
    // Нахождение указателя на предпоследний узел
    while ((*head_node)->p_next_node->p_next_node != NULL)
        (*head_node) = (*head_node)->p_next_node;
    // Создание указателя на предпоследний узел
    List_node *last_node = (*head_node);
    TBase last_value = last_node->p_next_node->value;
    // Удаление последнего узла
    free(last_node->p_next_node);
    last_node->p_next_node = NULL;
    // Возвращение значения удалённого узла
    return last_value;
}


// Вставить узел со значением new_value в позицию index списка с вершиной head_node
void insert_list(List_node *head_node, TCount index, TBase new_value)
{
    // Получение указателя на узел по индексу
    List_node *prev_node = get_list(head_node, index);
    // Создание нового узла
    List_node *new_node = malloc(sizeof(List_node));
    new_node->value = new_value;
    // Вставка узла в нужную позицию
    new_node->p_next_node = prev_node->p_next_node;
    prev_node->p_next_node = new_node;
}

// Удалить index узел из списка с вершиной head_node
TBase remove_list(List_node **head_node, TCount index)
{
    // Проверка индекса (удаление первого элемента)
    if (index <= 0)
        return pop_list(head_node);
    // Получение указателя на узел перед искомым
    List_node *prev_node = get_list(*head_node, index - 1);
    // Если узлов нет, то выходим из функции
    if (prev_node == NULL)
        return 0;
    // Создание указателя на удаляемый узел
    List_node *del_node = prev_node->p_next_node;
    prev_node->p_next_node = del_node->p_next_node;
    TBase last_value = del_node->value;
    // Удаление узла
    free(del_node);
    // Возвращение значения удалённого узла
    return last_value;
}


// Получить index узел из списка с вершиной head_node
List_node *get_list(List_node *head_node, TCount index)
{
    TCount cnt = 0;
    // Получение указателя на искомый узел
    while ((cnt++) < index && head_node != NULL)
        head_node = head_node->p_next_node;
    // Возвращение указателя на узел
    return head_node;
}

// Получить указатель на последний узел из списка с вершиной head_node
List_node *get_last_list(List_node *head_node)
{
    // Проверка на наличие узлов в списке
    if (head_node == NULL)
        return NULL;
    // Нахождение последнего элемента
    while (head_node->p_next_node != NULL)
        head_node = head_node->p_next_node;
    // Возвращение указателя на последний узел
    return head_node;
}

// Получить размер списка (кол-во узлов в нём)
TCount get_size_list(List_node *head_node)
{
    TCount size_list = 0;
    // Подсчёт узлов до конца списка
    while (head_node != NULL)
        ++size_list;
        head_node = head_node->p_next_node;
    // Возвращение размера списка
    return size_list;
}


// Вывод узлов списка с вершиной head_node
void print_list(List_node *head_node)
{
    TCount size_list = get_size_list(head_node);
    for (size_t index = 0 ; index < size_list; ++index){
        printf(FORMAT_COMMAND, get_list(head_node, index)->value);    // Вывод элемента
        putchar(DELIM_CHR); // Вывод символа разделителя
    }
    putchar(CARR_CHR);  // Вывод символа перевода каретки
}

// Ввод узлов списка с вершиной head_node
List_node *scan_list()
{
    TCount size_list = 0;    // Размер списка
    // Ввод размера списка
    printf("Enter the number of nodes in the list: ");
    do {
        scanf("%d", &size_list);
    } while (size_list < 0 || MAX_LIST_SIZE < size_list);
    
    TBase value = 0;
    printf("Enter the value [0] list node: ");
    scanf(FORMAT_COMMAND, &value);
    // Создание списка
    List_node *head_node = init_list(value);
    // Заполнение списка
    for (size_t i = 1; i < size_list; ++i) {
        printf("Enter the value [%ld] list node: ", i);
        scanf(FORMAT_COMMAND, &value);
        push_back_list(head_node, value);
    }
    // Возвращение указателя на готовый список
    return head_node;
}


// Создание линейного массива из элементов списка с вершиной head_node
TBase *list_to_array(List_node *head_node, TCount *p_len)
{
    // Получение длины будущего массива (кол-ва узлов в списке)
    *p_len = get_size_list(head_node);
    // Выделение памяти под массив
    TBase *arr = malloc((*p_len) * sizeof(TBase));
    // Заполнение массива
    for (size_t i = 0; i < *p_len; ++i)
        // Получение значения из узла под индексом i
        arr[i] = get_list(head_node, i)->value;
    // Возвращение указателя на массив
    return arr;
}

// Создание односвязного списка из массива arr с длиной len
List_node *array_to_list(TBase *arr, const TCount len)
{
    // Создание верщины списка
    List_node *head_node = init_list(arr[0]);
    for (size_t i = 0; i < len; ++i)
        // Создание узлов списка с элементами массива
        push_back_list(head_node, arr[i]);
    // Возвращение указателя на вершину списка
    return head_node;
}
