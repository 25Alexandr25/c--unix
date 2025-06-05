#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

// Структура для элемента двусвязного списка
struct Move {
    string description;
    Move* prev;
    Move* next;
    
    Move(const string& desc) : description(desc), prev(nullptr), next(nullptr) {}
};

// Класс для управления списком ходов
class MoveList {
private:
    Move* head;
    Move* tail;
    int count;
    
public:
    MoveList() : head(nullptr), tail(nullptr), count(0) {}
    
    // Добавление хода в конец списка
    void addMove(const string& desc) {
        Move* newMove = new Move(desc);
        
        if (head == nullptr) {
            head = tail = newMove;
        } else {
            tail->next = newMove;
            newMove->prev = tail;
            tail = newMove;
        }
        count++;
    }
    
    // Вывод всех ходов
    void printMoves() {
        Move* current = head;
        int moveNumber = 1;
        
        cout << "Последовательность ходов (" << count << "):" << endl;
        while (current != nullptr) {
            cout << moveNumber++ << ". " << current->description << endl;
            current = current->next;
        }
    }
    
    // Освобождение памяти
    ~MoveList() {
        Move* current = head;
        while (current != nullptr) {
            Move* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Рекурсивная функция решения Ханойской башни
void hanoi(int n, char from, char to, char aux, MoveList& moves) {
    if (n == 1) {
        string move = "Переместить диск 1 со стержня " + string(1, from) + " на стержень " + string(1, to);
        moves.addMove(move);
        return;
    }
    
    hanoi(n - 1, from, aux, to, moves);
    
    string move = "Переместить диск " + to_string(n) + " со стержня " + string(1, from) + " на стержень " + string(1, to);
    moves.addMove(move);
    
    hanoi(n - 1, aux, to, from, moves);
}

int main() {
    const int disks = 4; // Количество дисков
    MoveList moves; // Список ходов
    
    cout << "Решение Ханойской башни для " << disks << " дисков:" << endl;
    hanoi(disks, 'A', 'C', 'B', moves); // A - исходный, C - целевой, B - вспомогательный
    
    // Выводим последовательность ходов
    moves.printMoves();
    
    // Память автоматически освободится при выходе из области видимости
    return 0;
}
