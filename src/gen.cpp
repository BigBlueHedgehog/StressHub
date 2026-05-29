#include <cstdlib>
#include <random>
#include <ctime>
#include <iostream>

std::mt19937 rnd(time(0));

int main() {
    int n = rnd() % 100;
    std::cout << n;
    return 0;
}