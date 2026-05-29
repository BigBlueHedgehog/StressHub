#include <iostream>
#include <vector>


void sortArr(std::vector<int>& a) {
    for (int it = 0; it < 3; ++it) {
        for (int i = 0; i < (int)a.size() - 1; ++i) {
            if (a[i] > a[i + 1])
                std::swap(a[i], a[i + 1]);
        }
    }
}

void printArr(const std::vector<int>& a) {
    for (auto& x : a)
        std::cout << x << " ";
    std::cout << '\n';
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& x : a)
        std::cin >> x;
    sortArr(a);
    printArr(a);
    return 0;
}