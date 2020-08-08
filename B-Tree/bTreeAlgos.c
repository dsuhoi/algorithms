#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bTreeAlgos.h"


//***************************************************
// Основные функции по работе с бинарными деревьями
//***************************************************

// Создание узла дерева со значением value
BTreeNode* InitBTree(TBase newValue)
{
	// Выделение памяти под узел
	BTreeNode* Node = (BTreeNode*) malloc(sizeof(BTreeNode));
	// Присвоение значения узлу
	Node->value = newValue;
	Node->leftNode = NULL;
	Node->rightNode = NULL;
}


// Добавление узла со значением value в бинарное дерево с вершиной headNode
void PushBTree(BTreeNode* headNode, TBase newValue)
{
	while(headNode!=NULL){ 
		if(newValue < headNode->value){
			// Если новое значение меньше предыдущего, переводим указатель на левую ветвь
			headNode = headNode->leftNode;
		}
		else{
			// Иначе на правую
			headNode = headNode->rightNode;
		}
	}
	// Создаём новый узел
	headNode = InitBTree(newValue);
}


// Поиск узла со значением findValue в бинарном дереве с вершиной headNode
BTreeNode* FindBTree(BTreeNode* headNode, TBase findValue)
{
	while(headNode!=NULL){
		// Если узел найден, то возвращаем указатель на него
		if(findValue == headNode->value){
			return headNode;
		}
		// Если значение текущего узла больше искомого, то идём по левой ветви
		else if(findValue < headNode->value){
			headNode = headNode->leftNode;
		}
		// Иначе по правой
		else{
			headNode = headNode->rightNode;
		}
	}
	// Если узел не был найден, то возвращаем NULL
	return NULL;
}


// Получение указателя на узел с наименьшим значением бинарного дерева с вершиной headNode
BTreeNode* GetMinBTree(BTreeNode* headNode)
{
	// Итерация по левой ветви
	while(headNode->leftNode!=NULL){ 
		headNode = headNode->leftNode;
	}
	return headNode;
}
