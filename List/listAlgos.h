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
typedef int TBool;	// логический тип данных


//*********************************
// Основные константы
//*********************************
#define True 1			// логическая единица
#define False 0			// логический ноль
#define DELIM_CHR ' '	// символ разделитель
#define CARR_CHR '\n'	// символ перевода каретки
#define FORMAT_COMMAND "%4d"	// команда форматирования
#define FORMAT_COMMAND_CNT "%4d"	// команда форматирования для доп. данных


//********************************************************
// Основные константы для работы с односвязными списками
//********************************************************
#define MAX_LIST_SIZE 1000	// максимальное кол-во узлов в списке



//*****************************************************
// Основные функции по работе с односвязными списками
//*****************************************************

//структура элементов списка
typedef struct Node{
	struct Node* p_nextNode;
	TBase value; 
} Node;


// Создание списка и его первого узла
Node* InitList(TBase newValue);
// Вставить узел со значением newValue в начало списка с вершиной headNode
void PushList(Node** headNode, TBase newValue);
// Вставить узел со значением newValue в конец списка с вершиной headNode
void PushBackList(Node* headNode, TBase newValue);

// Удалить начальный узел из списка с вершиной headNode
TBase PopList(Node** headNode);
// Удалить последний узел из списка с вершиной headNode
TBase PopBackList(Node** headNode);

// Вставить узел со значением newValue в позицию index списка с вершиной headNode
void InsertList(Node* headNode, TCount index, TBase newValue);
// Удалить index узел из списка с вершиной headNode
Base RemoveList(Node** headNode, TCount index);

// Получить index узел из списка с вершиной headNode
Node* GetList(Node* headNode, TCount index);

// Получить указатель на последний узел из списка с вершиной headNode
Node* GetLastList(Node* headNode);

