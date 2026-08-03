#include <iostream>
using namespace std;

class MyCl {
    int* p;
public:
    // Конструктор з параметром
    MyCl(int x) {
        p = new int(x);
    }
    
    // Конструктор копіювання
    //MyCl(const MyCl& a) {
       // p = new int(*a.p);
    //}
    
    // Деструктор
    ~MyCl() {
        delete p;
    }
    
    // Методи класу
    int Get(void) {
        return *p;
    }
    
    void Set(int x) {
        *p = x;
    }
};

int main() {
    int x = 5;
    
    MyCl a(x);
    cout << "*a.p => " << a.Get() << endl;
    
    MyCl b(a);
    cout << "*b.p => " << b.Get() << endl;
    
    a.Set(7);
    cout << "*b.p => " << b.Get() << endl;
    
    system("pause");
    return 0;
}