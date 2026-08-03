#include <iostream>
#include <string>
using namespace std;

// Клас-координатор енергоспоживання
class PowerMonitor {
private:
    static int currentTdp;
public:
    static void addLoad(int watts) { currentTdp += watts; }
    static void getStatus() {
        cout << "[PowerMonitor] Total Consumption: " << currentTdp << "W" << endl;
    }
};

int PowerMonitor::currentTdp = 0;

class CPU {
    string model;
    int tdp;
public:
    CPU(string m, int t) : model(m), tdp(t) {
        cout << "CPU " << model << " connected." << endl;
        PowerMonitor::addLoad(tdp); // Пряма взаємодія з іншим класом
    }
};

class GPU {
    string model;
    int vram;
    int tdp;
public:
    GPU(string m, int v, int t) : model(m), vram(v), tdp(t) {
        cout << "GPU " << model << " (" << vram << "GB) connected." << endl;
        PowerMonitor::addLoad(tdp);
    }
};

int main() {
    PowerMonitor::getStatus(); // 0W

    // Створюємо компоненти ( Ryzen 7 5700X та RTX 4060 Ti)
    CPU myCpu("Ryzen 7 5700X", 65);
    PowerMonitor::getStatus(); // 65W

    GPU myGpu("RTX 4060 Ti", 8, 160);
    PowerMonitor::getStatus(); // 225W

    system("pause");
    return 0;
}