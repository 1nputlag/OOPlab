#include <iostream>

using namespace std;

// Найвищий базовий клас
class PoweredDevice {
public:
    PoweredDevice(int power) {
        cout << "PoweredDevice: " << power << '\n';
    }
};

// Віртуальне успадкування для уникнення дублювання
class Scanner : virtual public PoweredDevice {
public:
    Scanner(int scanner, int power) : PoweredDevice(power) {
        cout << "Scanner: " << scanner << '\n';
    }
};

// Віртуальне успадкування
class Printer : virtual public PoweredDevice {
public:
    Printer(int printer, int power) : PoweredDevice(power) {
        cout << "Printer: " << printer << '\n';
    }
};

// Похідний клас. Через virtual він має сам ініціалізувати PoweredDevice
class Copier : public Scanner, public Printer {
public:
    Copier(int scanner, int printer, int power)
        : Scanner(scanner, power), Printer(printer, power), PoweredDevice(power) 
    {
        cout << "Copier created!" << '\n';
    }
};

int main() {
    cout << "--- Creating Copier ---" << endl;
    // Створюємо об'єкт Copier
    Copier copier(1, 2, 3);
    
    system("Pause");
    return 0;
}