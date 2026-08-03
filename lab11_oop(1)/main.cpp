#include <iostream>

using namespace std;

class Contained1 {
public:
    Contained1() {
        cout << "Contained1 ctor\n";
    }
};

class Contained2 {
public:
    Contained2() {
        cout << "Contained2 ctor\n";
    }
};

class Contained3 {
public:
    Contained3() {
        cout << "Contained3 ctor\n";
    }
};

class BaseContainer {
public:
    BaseContainer() {
        cout << "BaseContainer ctor\n";
    }
private:
    Contained1 c1;
    Contained2 c2;
};

class DerivedContainer : public BaseContainer {
public:
    DerivedContainer() : BaseContainer() {
        cout << "DerivedContainer ctor\n";
    }
private:
    Contained3 c3;
};

int main() {
    DerivedContainer dc;
    system("pause");
    return 0;
}