#include "DSU.h"

void DSU::init(int n) {
    previous.resize(n);
    // Спочатку кожна вершина — окрема множина (вказує сама на себе)
    for (int i = 0; i < n; i++) {
        set_make(i);
    }
}

void DSU::set_make(int v) {
    // Нова вершина — корінь своєї окремої множини
    previous[v] = v;
}

int DSU::set_find(int v) {
    // Якщо v є коренем — повертаємо v
    if (previous[v] == v) return v;
    // Інакше рекурсивно піднімаємось до кореня
    return set_find(previous[v]);
}

bool DSU::set_union(int v1, int v2) {
    int root1 = set_find(v1); // корінь множини v1
    int root2 = set_find(v2); // корінь множини v2

    if (root1 == root2) {
        // Обидві вершини вже в одній множині — цикл!
        return false;
    }

    // Об'єднуємо: робимо корінь першого дерева батьком кореня другого
    // ВАЖЛИВО: об'єднуємо саме через корені, не через будь-які вузли
    previous[root2] = root1;
    return true;
}
