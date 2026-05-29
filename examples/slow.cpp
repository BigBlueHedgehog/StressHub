#include <iostream>
#include <vector>
#include <algorithm>


void sortArr(std::vector<int>& a) {
    std::sort(a.begin(), a.end());
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