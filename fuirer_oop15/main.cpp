#include "Interfaces.h"
#include "Functions.h"
#include "Integrators.h"
#include "Plotter.h"

int main() {
    std::vector<IFunction*> functions;
    functions.push_back(new SawtoothWave()); 
    functions.push_back(new SquareWave());

    std::vector<IIntegrator*> integrators;
    integrators.push_back(new SimpsonRule()); 
    integrators.push_back(new RectangleRule());
    integrators.push_back(new TrapezoidalRule());

    Plotter app;
    app.runInteractive(functions, integrators); 

    for (auto f : functions) delete f;
    for (auto i : integrators) delete i;

    return 0;
}