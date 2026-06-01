#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::mt19937 rnd(time(0));

void printArr(const std::vector<int>& a) {
    std::cout << (int)a.size() << '\n';
    for (auto& x : a) std::cout << x << " ";
    std::cout << '\n';
}

int main() {
    int n = rnd() % 10;
    std::vector<int> a(n);
    for (auto& x : a) x = rnd();
    printArr(a);
    return 0;
}