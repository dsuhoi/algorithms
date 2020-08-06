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
