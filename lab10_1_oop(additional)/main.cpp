#include <iostream>
#include <string>

using namespace std;

// 1. Спільний базовий клас (аналог PoweredDevice)
class PCComponent {
protected:
    int tdp; // Тепловиділення (W)
public:
    PCComponent(int power_draw) : tdp(power_draw) {
        cout << "[PCComponent] Initialized with TDP: " << tdp << "W\n";
    }
};

// 2. Перший похідний клас (віртуальне успадкування)
class CPU : virtual public PCComponent {
protected:
    int cores;
public:
    CPU(int c, int power_draw) : PCComponent(power_draw), cores(c) {
        cout << "[CPU] Initialized with " << cores << " cores.\n";
    }
};

// 3. Другий похідний клас (віртуальне успадкування)
class GPU : virtual public PCComponent {
protected:
    int vram;
public:
    GPU(int v, int power_draw) : PCComponent(power_draw), vram(v) {
        cout << "[GPU] Initialized with " << vram << "GB VRAM.\n";
    }
};

// 4. Фінальний клас, що об'єднує властивості обох (Алмаз смерті)
class APU : public CPU, public GPU {
private:
    string modelName;
public:
    // APU зобов'язаний викликати конструктор PCComponent безпосередньо,
    // оскільки CPU та GPU успадковують його віртуально.
    APU(string name, int c, int v, int power_draw) 
        : CPU(c, power_draw), GPU(v, power_draw), PCComponent(power_draw), modelName(name) 
    {
        cout << "[APU] " << modelName << " successfully assembled!\n";
    }
    
    void displaySpecs() {
        cout << "\n--- System Specs ---\n";
        cout << "Model: " << modelName << "\n";
        cout << "Cores: " << cores << "\n";
        cout << "Graphics VRAM: " << vram << "GB\n";
        cout << "Total Power Draw: " << tdp << "W\n";
        cout << "--------------------\n";
    }
};

int main() {
    cout << "Building system...\n\n";
    
    // Створюємо гібридний процесор (наприклад, 8 ядер, 4GB виділеної пам'яті, 65W споживання)
    APU myProcessor("Ryzen 7 8700G", 8, 4, 65);
    
    myProcessor.displaySpecs();

    return 0;
}