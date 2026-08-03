#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tree.h"

using namespace std;

int main() {
    srand(time(0));
    int mainChoice;

    while (true) {
        cout << "\n=== ГОЛОВНЕ МЕНЮ ===" << endl;
        cout << "1. Частина 1: Побудова та обхід бінарного дерева" << endl;
        cout << "2. Частина 2: Бінарне дерево пошуку (BST)" << endl;
        cout << "3. Вихід" << endl;
        cout << "Оберіть частину лабораторної: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            Node* basicTree = NULL;
            int n;
            cout << "Введіть кількість вузлів для дерева: ";
            cin >> n;
            CreateTree(&basicTree, n); // Створення дерева
            
            cout << "\nСтруктура дерева:" << endl;
            ShowTree(basicTree, 0); // Відображення дерева

            cout << "\nОбхід у прямому порядку (PreOrder): ";
            PreOrder(basicTree); // Обхід дерева
            cout << "\nОбхід у внутрішньому порядку (InOrder): ";
            InOrder(basicTree); // Обхід дерева
            cout << "\nОбхід у зворотному порядку (PostOrder): ";
            PostOrder(basicTree); // Обхід дерева
            cout << endl;

        } else if (mainChoice == 2) {
            Node* bstRoot = NULL;
            int bstChoice, val;

            while (true) {
                cout << "\n--- Бінарне Дерево Пошуку ---" << endl;
                cout << "1. Додати вузол" << endl;
                cout << "2. Видалити вузол" << endl;
                cout << "3. Знайти вузол" << endl;
                cout << "4. Знайти Successor (наступний елемент)" << endl;
                cout << "5. Знайти Predecessor (попередній елемент)" << endl;
                cout << "6. Повернутися до головного меню" << endl;
                cout << "Ваш вибір: ";
                cin >> bstChoice; // Меню операцій

                if (bstChoice == 1) {
                    cout << "Введіть значення: ";
                    cin >> val;
                    InsertNodeBST(&bstRoot, val);
                    cout << "\nДерево після додавання:\n";
                    ShowTree(bstRoot, 0); 
                } else if (bstChoice == 2) {
                    cout << "Введіть значення для видалення: ";
                    cin >> val;
                    Node* delNode = SearchNodeBST(bstRoot, val); 
                    if (delNode != NULL) {
                        DeleteNodeBST(&bstRoot, &delNode);
                        cout << "Вузол видалено.\nДерево після видалення:\n";
                        ShowTree(bstRoot, 0); 
                    } else {
                        cout << "Вузол не знайдено!" << endl; 
                    }
                } else if (bstChoice == 3) {
                    cout << "Введіть значення: ";
                    cin >> val;
                    if (SearchNodeBST(bstRoot, val) != NULL) {
                        cout << "Вузол знайдено!" << endl;
                    } else {
                        cout << "Вузол не знайдено!" << endl;
                    }
                } else if (bstChoice == 4) {
                    cout << "Введіть значення вузла, для якого шукаємо Successor: ";
                    cin >> val;
                    Node* targetNode = SearchNodeBST(bstRoot, val);
                    if (targetNode != NULL) {
                        Node* succ = SuccessorNodeBST(targetNode);
                        if (succ != NULL) {
                            cout << "Successor для " << val << " є " << succ->key << endl;
                        } else {
                            cout << "Successor для " << val << " не існує (це максимальний елемент)." << endl;
                        }
                    } else {
                        cout << "Вузол зі значенням " << val << " не знайдено!" << endl;
                    }
                } else if (bstChoice == 5) {
                    cout << "Введіть значення вузла, для якого шукаємо Predecessor: ";
                    cin >> val;
                    Node* targetNode = SearchNodeBST(bstRoot, val);
                    if (targetNode != NULL) {
                        Node* pred = PredecessorNodeBST(targetNode);
                        if (pred != NULL) {
                            cout << "Predecessor для " << val << " є " << pred->key << endl;
                        } else {
                            cout << "Predecessor для " << val << " не існує (це мінімальний елемент)." << endl;
                        }
                    } else {
                        cout << "Вузол зі значенням " << val << " не знайдено!" << endl;
                    }
                } else if (bstChoice == 6) {
                    break;
                } else {
                    cout << "Невірний вибір." << endl;
                }
            }
        } else if (mainChoice == 3) {
            break;
        } else {
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    }
    return 0;
}