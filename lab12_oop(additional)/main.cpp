#include <iostream>
#include <string>
using namespace std;

class GamingPC {
private:
    int componentCount;
    string* components; // Динамічний масив комплектуючих

public:
    // Звичайний конструктор
    GamingPC(int count) {
        componentCount = count;
        // Виділяємо пам'ять під задану кількість деталей
        components = new string[componentCount];
        for (int i = 0; i < componentCount; i++) {
            components[i] = "Порожній слот";
        }
        cout << "Викликано звичайний конструктор." << endl;
    }

    // Конструктор копіювання (Глибоке копіювання)
    GamingPC(const GamingPC& other) {
        componentCount = other.componentCount;
        // Виділяємо НОВУ пам'ять для масиву комплектуючих копії
        components = new string[componentCount];
        
        // Копіюємо кожну деталь з оригіналу
        for (int i = 0; i < componentCount; i++) {
            components[i] = other.components[i];
        }
        cout << "Викликано конструктор КОПІЮВАННЯ." << endl;
    }

    // Деструктор
    ~GamingPC() {
        delete[] components; // Звільняємо пам'ять
        cout << "Викликано деструктор. Пам'ять звільнено." << endl;
    }

    // Метод для встановлення деталі
    void setComponent(int index, const string& compName) {
        if (index >= 0 && index < componentCount) {
            components[index] = compName;
        }
    }

    // Метод для виводу специфікації
    void display() const {
        for (int i = 0; i < componentCount; i++) {
            cout << "  - " << components[i] << endl;
        }
    }
};

int main() {
    // 1. Збираємо оригінальний ПК
    GamingPC myPC(2);
    myPC.setComponent(0, "AMD Ryzen 7 5700X");
    myPC.setComponent(1, "NVIDIA RTX 4060 Ti");

    cout << "\n--- Оригінальний ПК ---" << endl;
    myPC.display();

    // 2. Створюємо копію ПК (спрацює конструктор копіювання)
    GamingPC copiedPC = myPC;

    cout << "\n--- Скопійований ПК ---" << endl;
    copiedPC.display();

    // 3. Змінюємо деталь у скопійованому ПК (апгрейд)
    copiedPC.setComponent(1, "NVIDIA RTX 4070 Super");

    cout << "\n--- Після апгрейду скопійованого ПК ---" << endl;
    // Завдяки глибокому копіюванню, апгрейд копії 
    // не вплине на наш оригінальний ПК.
    
    cout << "[Оригінальний ПК]:" << endl;
    myPC.display();
    
    cout << "[Скопійований ПК]:" << endl;
    copiedPC.display();

    cout << "\nЗавершення програми..." << endl;
    return 0;
}