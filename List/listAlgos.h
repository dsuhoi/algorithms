/*
 * listAlgos.h
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


//*********************************
// Основные типы данных
//*********************************

typedef int TBase;	// искомая переменная (тип данных для массива и т.п.)
typedef int TCount;	// переменная для дополнительных данных (константные аргументы функций и т.п.)


//*********************************
// Основные константы
//*********************************
#define DELIM_CHR ' '	// символ разделитель
#define CARR_CHR '\n'	// символ перевода каретки
#define FORMAT_COMMAND "%4d"	// команда форматирования
#define FORMAT_COMMAND_CNT "%4d"	// команда форматирования для доп. данных


//********************************************************
// Основные константы для работы с односвязными списками
//********************************************************
#define MAX_LIST_SIZE 1000	// максимальное кол-во узлов в списке
// Для заполнения односвязных списков случайными числами раскомментируйте флаг
// и укажите диапазон для чисел RANDOM_RANGE
#define RANDOM_RANGE 500


//*****************************************************
// Основные функции по работе с односвязными списками
//*****************************************************

//структура элементов списка
typedef struct ListNode{
	struct ListNode* p_nextNode;
	TBase value; 
} ListNode;


// Создание списка и его первого узла
ListNode* InitList(const TBase newValue);
// Создание списка с numNode количеством узлов (заполнены случайными числами)
ListNode* GenerateList(const TCount numNode);

// Вставить узел со значением newValue в начало списка с вершиной headNode
void PushList(ListNode** headNode, TBase newValue);
// Вставить узел со значением newValue в конец списка с вершиной headNode
void PushBackList(ListNode* headNode, TBase newValue);

// Удалить начальный узел из списка с вершиной headNode
TBase PopList(ListNode** headNode);
// Удалить последний узел из списка с вершиной headNode
TBase PopBackList(ListNode** headNode);

// Вставить узел со значением newValue в позицию index списка с вершиной headNode
void InsertList(ListNode* headNode, TCount index, TBase newValue);
// Удалить index узел из списка с вершиной headNode
TBase RemoveList(ListNode** headNode, TCount index);

// Получить index узел из списка с вершиной headNode
ListNode* GetList(ListNode* headNode, TCount index);
// Получить указатель на последний узел из списка с вершиной headNode
ListNode* GetLastList(ListNode* headNode);
// Получить размер списка (кол-во узлов в нём)
TCount GetSizeList(ListNode* headNode);

// Вывод узлов списка с вершиной headNode
void PrintList(ListNode* headNode);
// Ввод узлов списка с вершиной headNode
ListNode* ScanList();

// Создание массива (с указателем на длину p_len) из элементов списка с вершиной headNode
TBase* ListToArray(ListNode* headNode, TCount* p_len);

#endif
