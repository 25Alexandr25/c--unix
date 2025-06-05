#include <iostream>
#include <cmath>
#include <unistd.h>
#include <csignal>
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
    int var_size = sizeof(num_iterations);
    cout << "Evaluation with parallel processes" << "\n";
    while (num_iterations < 100001) {
        auto start = chrono::steady_clock::now();
        int x[num_iterations];
        for (int i = 0; i <= num_iterations; i++) {
            x[i] = rand();
        }
        int pipe_from_f1[2], pipe_from_f2[2];
        //pipe[0] - write
        //pipe[1] - read
        pipe(pipe_from_f2);
        pipe(pipe_from_f1);
        pid_t pid_f1 = fork();
        if (pid_f1 == 0) {
            //child 1 process
            int f1[num_iterations];
            for (int i1 = 0; i1 <= num_iterations; i1++) {
                f1[i1] = formula1(x[i1]);
                write(pipe_from_f1[1], f1, var_size);
            }
            return 0;
        } else if (pid_f1 == -1) {
            cerr << "Multiprocessing failed.";
            return 1;
        }
        //back to parent process
        pid_t pid_f2 = fork();
        if (pid_f2 == 0) {
            //child 2 process
            int f2[num_iterations];
            for (int i2 = 0; i2 <= num_iterations; i2++) {
                f2[i2] = formula2(x[i2]);
                write(pipe_from_f2[1], f2, var_size);
            }
            return 0;
        } else if (pid_f2 == -1) {
            cerr << "Multiprocessing failed.";
            return 1;
        }
        //back to parent process
        int mas_fr_1[num_iterations];
        int mas_fr_2[num_iterations];
        int f3[num_iterations];
        read(pipe_from_f1[0], mas_fr_1, var_size);
        read(pipe_from_f2[0], mas_fr_2, var_size);
        for (int n = 0; n <= num_iterations; n++) {
            f3[n] = formula3(mas_fr_1[n], mas_fr_2[n]);
        }

        //end of the main evaluation
        kill(pid_f1, 0);
        kill(pid_f2, 0);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << "Time spent for " << num_iterations << " calculations is " << chrono::duration<double>(diff).count()
             << " seconds" << "\n";
        num_iterations *= 10;
    }
    return 0;
}