#include <ctime>
#include <iostream>
#include <random>
#include <vector>

void printArr(const std::vector<int>& a) {
    std::cout << (int)a.size() << '\n';
    for (auto& x : a) std::cout << x << " ";
    std::cout << '\n';
}

void generationFunction(std::mt19937& rnd) {
    int n = rnd() % 10;
    std::vector<int> a(n);
    for (auto& x : a) x = rnd();
    printArr(a);
}

int main(int argc, char* argv[]) {
    int seed = std::stoi(argv[1]);
    int test_number = std::stoi(argv[2]);

    std::mt19937 rnd(seed + test_number);

    generationFunction(rnd);
    return 0;
}