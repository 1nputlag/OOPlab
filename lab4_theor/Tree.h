#ifndef TREE_H
#define TREE_H

#include <iostream>

// Зв'язуємо тип інформаційного поля з типом даних (наприклад, int) 
typedef int datatype; 

// Оголошення структури вузла бінарного дерева 
struct Node {
    datatype key;   // Інформаційне поле (ключ) вузла 
    Node* parent;   // Вказівник на батьківський вузол 
    Node* left;     // Вказівник на лівого сина 
    Node* right;    // Вказівник на правого сина 
};

// Частина 1: Побудова та обхід бінарного дерева 
void CreateTree(Node** pNode, int n);
void ShowTree(Node* pNode, int L);
void PreOrder(Node* pNode);
void PostOrder(Node* pNode);
void InOrder(Node* pNode);

// Частина 2: Бінарні дерева пошуку 
Node* SearchNodeBST(Node* root, datatype searchKey);
Node* CreateRootBST(datatype data);
void InsertNodeBST(Node** root, datatype data);
Node* MinimumNodeBST(Node* pNode);
Node* MaximumNodeBST(Node* pNode);
Node* SuccessorNodeBST(Node* pNode);
Node* PredecessorNodeBST(Node* pNode);
void DeleteNodeBST(Node** root, Node** delNode);

#endif