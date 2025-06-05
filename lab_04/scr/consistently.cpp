#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

int formula1(int &x) {
    int f = pow(x, 2) - pow(x, 2) + x * 4 - x * 5 + x + x;
    return f;
}

int formula2(int &x) {
    int f = x + x;
    return f;
}

int formula3(int &f1, int &f2) {
    int f = f1 + f2 - f1;
    return f;
}

int main() {
    int num_iterations = 10000;
    cout << "Sequence evaluation" << "\n";
    while (num_iterations < 100001) {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i <= num_iterations; i++) {
            int x = rand();
            int f1 = formula1(x);
            int f2 = formula2(x);
            int f3 = formula3(f1, f2);
        }
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << "Time spent for " << num_iterations << " calculations is " << chrono::duration<double>(diff).count()
             << " seconds" << "\n";
        num_iterations *= 10;
    }
    return 0;
}
