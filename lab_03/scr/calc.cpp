#include <iostream>
#include <string>
#include <cmath> // для pow()

using namespace std;

double plusF(double a, double b) {
    return a + b;
}

double minusF(double a, double b) {
    return a - b;
}

//double powerF(double a, double b) {
    //return pow(a, b);
//}

double powerF(double a, double b) {
    double result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int main() {
    double a, b;
    string op;

    // Ввод данных
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите оператор (+, -, ^, plus, minus, power): ";
    cin >> op;
    cout << "Введите второе число: ";
    cin >> b;

    double result;

    // Выбор операции
    if (op == "plus" || op == "+") {
        result = plusF(a, b);
    }
    else if (op == "minus" || op == "-") {
        result = minusF(a, b);
    }
    else if (op == "power" || op == "^") {
        result = powerF(a, b);
    }
    else {
        cerr << "Ошибка: неизвестный оператор!" << endl;
        return 1;
    }

    // Вывод результата
    cout << "Результат: " << result << endl;
    return 0;
}
