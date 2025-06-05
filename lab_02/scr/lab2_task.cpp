#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

double expression(int x)
{
    int result = pow(x,2)-pow(x,2)+x*4-x*5+x+x;
    return result;
}

int main()
{
    string recalculate = "Y";
    while(recalculate == "Y") {
        int n;
        cout << "Enter the number of calculations: ";
        cin >> n;
        if (cin.get() != (int) '\n') {
            cout << "Invalid input type, calculation denied";
            return 0;
        }
        clock_t start = clock();
        for (int i = 0; i <= n; i++) {
            int x = rand();
            double res = expression(x);
        }
        clock_t end = clock();
        auto seconds = (double) (end - start) / CLOCKS_PER_SEC;
        cout << "Time spent for " << n << " calculations is " << seconds << " seconds";
        cout << "\nEvaluate again? \n[Y/N]\n";
        cin >> recalculate;
        while(1==1){
            if(recalculate=="Y" or recalculate=="N"){break;}
            cout << "Try again!\nEvaluate again? \n[Y/N]\n";
            cin >> recalculate;
        }
    }
}