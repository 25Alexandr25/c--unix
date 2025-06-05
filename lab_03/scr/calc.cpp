#include <iostream>
#include <string>

using namespace std;

double plusF(double a, double b) {
    return a + b;
}

double minusF(double a, double b) {
    return a - b;
}

double powerF(double a, double b) {
    double result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int wmain(int argc, wchar_t *argv[]) {
    double a = _wtoi(argv[1]);
    double b = _wtoi(argv[3]);
    double result;
    wstring operatorF = argv[2];
    wstring plus(L"plus");
    wstring minus(L"minus");
    wstring power(L"power");
    wstring plusS(L"+");
    wstring minusS(L"-");
    wstring powerS(L"^");
    if (operatorF == plus or operatorF == plusS) {
        result = plusF(a, b);
    } else if (operatorF == power or operatorF == powerS) {
        result = powerF(a, b);
    } else if (operatorF == minus or operatorF == minusS) {
        result = minusF(a, b);
    } else {
        cout << "Invalid operator!\n";
        return 0;
    }
    cout << "Result: " << result << "\n";
    cout << "Проверка";
    return 0;
}