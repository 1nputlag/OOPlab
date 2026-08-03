#include "Tree.h"

using namespace std;

// ================= ЧАСТИНА 1 =================

// Рекурсивний алгоритм створення бінарного дерева
void CreateTree(Node** pNode, int n) {
    if (n == 0) { // Умова зупинки рекурсії
        *pNode = NULL; // Дерево порожнє
    } else {
        *pNode = new Node; // Створити новий вузол
        (*pNode)->key = rand() % 100; // Заповнити даними
        (*pNode)->left = (*pNode)->right = NULL; // Встановити вказівники як NULL
        (*pNode)->parent = NULL; // Вказівник parent не використовується в цьому алгоритмі
        
        int n_left = n / 2; // Кількість вузлів ліворуч
        int n_right = n - n_left - 1; // Кількість вузлів праворуч
        
        CreateTree(&((*pNode)->left), n_left); // Створити ліве піддерево
        CreateTree(&((*pNode)->right), n_right); // Створити праве піддерево
        
        // Відновлюємо parent для повноти структури, хоча алгоритм цього не вимагає
        if((*pNode)->left != NULL) (*pNode)->left->parent = *pNode;
        if((*pNode)->right != NULL) (*pNode)->right->parent = *pNode;
    }
}

// Рекурсивний алгоритм відображення дерева
void ShowTree(Node* pNode, int L) {
    if (pNode != NULL) { // Поки не досягнуто листків
        ShowTree(pNode->right, L + 1); // Вивести праве піддерево
        for (int i = 0; i < L; i++) cout << "    "; // Вивести пробіли
        cout << pNode->key << endl; // Вивести ключ
        ShowTree(pNode->left, L + 1); // Вивести ліве піддерево
    }
}

// Обхід у прямому порядку
void PreOrder(Node* pNode) {
    if (pNode != NULL) { // Поки не досягнуто листків
        cout << pNode->key << " "; // Обробити дані
        PreOrder(pNode->left); // Здійснити обхід лівого піддерева
        PreOrder(pNode->right); // Здійснити обхід правого піддерева
    }
}

// Обхід у зворотному порядку
void PostOrder(Node* pNode) {
    if (pNode != NULL) { // Поки не досягнуто листків
        PostOrder(pNode->left); // Здійснити обхід лівого піддерева
        PostOrder(pNode->right); // Здійснити обхід правого піддерева
        cout << pNode->key << " "; // Обробити дані
    }
}

// Обхід у внутрішньому порядку
void InOrder(Node* pNode) {
    if (pNode != NULL) { // Поки не досягнуто листків
        InOrder(pNode->left); // Здійснити обхід лівого піддерева
        cout << pNode->key << " "; // Обробити дані
        InOrder(pNode->right); // Здійснити обхід правого піддерева
    }
}

// ================= ЧАСТИНА 2 (BST) =================

// Алгоритм пошуку даних
Node* SearchNodeBST(Node* root, datatype searchKey) {
    Node* pNode = root; // Починаємо з кореня
    while (pNode != NULL) { // Поки не досягнуто листків
        if (pNode->key == searchKey) {
            return pNode; // Дані знайдено
        } else if (pNode->key > searchKey) {
            pNode = pNode->left; // Перейти до лівого піддерева
        } else {
            pNode = pNode->right; // Перейти до правого піддерева
        }
    }
    return NULL; // Вузол не знайдено
}

// Алгоритм створення кореня
Node* CreateRootBST(datatype data) {
    Node* pNode = new Node; // Виділити динамічну пам'ять
    pNode->key = data; // Заповнити поле
    pNode->parent = pNode->left = pNode->right = NULL; // Встановити вказівники як NULL
    return pNode; // Повернути вказівник на корінь
}

// Алгоритм вставки нового вузла
void InsertNodeBST(Node** root, datatype data) {
    if (*root == NULL) {
        *root = CreateRootBST(data);
        return;
    }

    if (SearchNodeBST(*root, data) != NULL) { // Пошук за ключем
        cout << "Вузол з такими даними вже існує!" << endl; // Повідомлення про існування
        return;
    }

    Node* pNew = new Node; // Виділити пам'ять
    pNew->key = data; // Заповнити даними
    pNew->parent = pNew->left = pNew->right = NULL; // Встановити як NULL

    Node* pNode = *root; // Починаємо з кореня
    Node* previous = NULL;

    while (pNode != NULL) { // Поки не досягнуто листків
        previous = pNode; // Встановити вказівник на попередній вузол
        if (pNode->key > data) {
            pNode = pNode->left; // Перейти до лівого
        } else {
            pNode = pNode->right; // Перейти до правого
        }
    }

    pNew->parent = previous; // Встановити батьківським для нового вузла
    if (previous->key > data) {
        previous->left = pNew; // Приєднати як лівого сина
    } else {
        previous->right = pNew; // Приєднати як правого сина
    }
}

Node* MinimumNodeBST(Node* pNode) {
    Node* previous = pNode;
    while (previous->left != NULL) previous = previous->left;
    return previous;
}

Node* MaximumNodeBST(Node* pNode) {
    Node* previous = pNode;
    while (previous->right != NULL) previous = previous->right;
    return previous;
}

// Алгоритм пошуку Successor
Node* SuccessorNodeBST(Node* pNode) {
    if (pNode->right != NULL) { // Якщо існує правий син
        return MinimumNodeBST(pNode->right); // Кроки 1.1-1.3
    }
    Node* previous = pNode->parent; // Перейти у батьківський вузол
    Node* current = pNode;
    // Поки поточний є правим сином батьківського
    while (previous != NULL && current == previous->right) { 
        current = previous; // Піднімаємось деревом вгору ліворуч
        previous = previous->parent; 
    }
    return previous; // Повернути адресу
}

// Алгоритм пошуку Predecessor
Node* PredecessorNodeBST(Node* pNode) {
    if (pNode->left != NULL) {
        return MaximumNodeBST(pNode->left); // Пошук максимального у лівому піддереві
    }
    Node* previous = pNode->parent;
    Node* current = pNode;
    while (previous != NULL && current == previous->left) {
        current = previous;
        previous = previous->parent;
    }
    return previous;
}

// Алгоритм видалення вузла
void DeleteNodeBST(Node** root, Node** delNode) {
    if (*delNode == NULL) return;

    // Випадок 1: Вузол не має нащадків (листок)
    if ((*delNode)->left == NULL && (*delNode)->right == NULL) {
        if (*delNode == *root) { // Якщо є коренем
            delete *root; // Видалити корінь
            *root = NULL;
            return;
        }
        if (((*delNode)->parent)->left == *delNode) { // Якщо лівий син
            ((*delNode)->parent)->left = NULL; // Встановити вказівник як NULL
        } else { // Якщо правий син
            ((*delNode)->parent)->right = NULL; // Встановити вказівник як NULL
        }
        delete *delNode; // Звільнити пам'ять
        return;
    }

    // Випадок 3: Вузол має обох нащадків
    if ((*delNode)->left != NULL && (*delNode)->right != NULL) {
        Node* term = SuccessorNodeBST(*delNode); // Знайти термінальний вузол
        (*delNode)->key = term->key; // Оновити ключ значенням термінального
        DeleteNodeBST(root, &term); // Видалити термінальний вузол рекурсивно
        return;
    }

    // Випадок 2: Вузол має одного нащадка
    // Визначити якого нащадка має вузол
    Node* next = ((*delNode)->left != NULL) ? (*delNode)->left : (*delNode)->right; 
    
    if (*delNode == *root) { // Якщо є коренем
        *root = next; // Встановити нащадок як корінь
        next->parent = NULL;
        delete *delNode; // Звільнити пам'ять
        return;
    }

    if (((*delNode)->parent)->left == *delNode) { // Якщо лівий син
        ((*delNode)->parent)->left = next; // Встановити вказівник на вузол-нащадок
    } else { // Якщо правий син
        ((*delNode)->parent)->right = next; // Встановити вказівник на вузол-нащадок
    }
    next->parent = (*delNode)->parent; // Зв'язати вузол-нащадок з батьківським
    delete *delNode; // Звільнити пам'ять
}