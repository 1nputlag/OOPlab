#include <iostream>
using namespace std;

class CL1 {
    int x;
public:
    CL1(int x1) { x = x1; }
    void print() {
        cout << "CL1::print()->" << endl;
        cout << x << endl;
    }

    class CL2 {
        CL1& a;
        int y;
    public:
        CL2(CL1& a1, int y1) : a(a1) { y = y1; }
        void print() {
            cout << "CL1::CL2::print()-> ";
            a.print();
            cout << y << endl;
        }

        class CL3 {
            CL2& b;
            int z;
        public:
            CL3(CL2& b1, int z1) : b(b1) { z = z1; }
            void print() {
                cout << "CL1::CL2::CL3::print()-> ";
                b.print();
                cout << z << endl;
            }
        };
    };
};

int main() {
    CL1 a(1);
    a.print();

    CL1::CL2 b(a, 2);
    b.print();

    CL1::CL2::CL3 c(b, 3);
    c.print();

    system("pause");
    return 0;
}