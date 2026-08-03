#include <iostream>
#include "CPU.h"
#include "GPU.h"

using namespace std;

int main() {
    CPU myCpu("AMD Ryzen 7 5700X", 8, 3.4);
    GPU myGpu("NVIDIA RTX 4060 Ti", 8);

    PCComponent* comp1 = &myCpu;
    PCComponent* comp2 = &myGpu;

    cout << "System Information:" << endl;
    comp1->showSpecs();
    comp2->showSpecs();

    return 0;
}