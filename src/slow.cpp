#include <iostream>
#include <random>
#include <ctime>
#include <iostream>

std::mt19937 rnd(time(0));

int main() {
    int n;
    std::cin >> n;
    if (rnd() % 2 == 0)
        std::cout << n * 3;
    else
        std::cout << n * 2;
    return 0;
}