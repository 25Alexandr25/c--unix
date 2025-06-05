#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <chrono>
#include <sstream>
#include <fstream>

// Глобальный мьютекс для безопасного вывода
std::mutex cout_mutex;

// ========== КЛАССЫ КОМАНД ==========

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class PrintCommand : public Command {
    std::string message;
public:
    PrintCommand(const std::string& msg) : message(msg) {}
    void execute() override {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << message << std::endl;
    }
};

class FileAppendCommand : public Command {
    std::string filename;
    std::string content;
public:
    FileAppendCommand(const std::string& fn, const std::string& cnt)
        : filename(fn), content(cnt) {}
    void execute() override {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::ofstream file(filename, std::ios::app);
        if (file) {
            file << content << std::endl;
            std::cout << "Appended to file: " << filename << std::endl;
        } else {
            std::cerr << "Error writing to file: " << filename << std::endl;
        }
    }
};

class ArithmeticCommand : public Command {
    double left, right;
    char op;
public:
    ArithmeticCommand(double l, double r, char o)
        : left(l), right(r), op(o) {}
    void execute() override {
        double result;
        switch(op) {
            case '+': result = left + right; break;
            case '-': result = left - right; break;
            case '*': result = left * right; break;
            case '/': result = right != 0 ? left / right : 0; break;
            default: result = 0;
        }
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << left << " " << op << " " << right << " = " << result << std::endl;
    }
};

class LoopCommand : public Command {
    int iterations;
    std::vector<std::unique_ptr<Command>> commands;
public:
    LoopCommand(int it) : iterations(it) {}
    void addCommand(std::unique_ptr<Command> cmd) {
        commands.push_back(std::move(cmd));
    }
    void execute() override {
        for(int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Loop iteration " << (i+1) << "/" << iterations << std::endl;
            for(auto& cmd : commands) {
                cmd->execute();
            }
        }
    }
};

// ========== ПАРСЕР ==========

std::unique_ptr<Command> parseCommand(const std::string& line) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "print") {
        std::string message;
        std::getline(iss, message);
        return std::make_unique<PrintCommand>(message.substr(1));
    }
    else if (cmd == "file_append") {
        std::string filename, content;
        iss >> filename;
        std::getline(iss, content);
        return std::make_unique<FileAppendCommand>(filename, content.substr(1));
    }
    else if (cmd == "add" || cmd == "sub" || cmd == "mul" || cmd == "div") {
        double x, y;
        if (iss >> x >> y) {
            char op;
            if (cmd == "add") op = '+';
            else if (cmd == "sub") op = '-';
            else if (cmd == "mul") op = '*';
            else op = '/';
            return std::make_unique<ArithmeticCommand>(x, y, op);
        }
    }
    else if (cmd == "loop") {
        int iterations;
        if (iss >> iterations) {
            return std::make_unique<LoopCommand>(iterations);
        }
    }

    return std::make_unique<PrintCommand>("Unknown command: " + line);
}

// ========== ГЛАВНАЯ ПРОГРАММА ==========

int main() {
    std::vector<std::unique_ptr<Command>> program;
    std::string input;

    std::cout << "Parallel Language Interpreter (type 'run' to execute, 'exit' to quit)\n";
    
    while(true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if(input == "exit") break;
        if(input == "run") {
            // Запускаем все команды параллельно
            std::vector<std::thread> threads;
            for(size_t i = 0; i < program.size(); ++i) {
                threads.emplace_back([i, &program]() {
                    auto start = std::chrono::high_resolution_clock::now();
                    
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        std::cout << "Starting command #" << (i+1) << " in thread "
                                  << std::this_thread::get_id() << std::endl;
                    }
                    
                    program[i]->execute();
                    
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Command #" << (i+1) << " completed in "
                              << duration.count() << " ms" << std::endl;
                });
            }
            
            for(auto& t : threads) {
                t.join();
            }
            
            program.clear();
            continue;
        }
        
        // Парсим и добавляем команду
        auto cmd = parseCommand(input);
        if(cmd) {
            program.push_back(std::move(cmd));
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Command added to program (" << program.size() << " total)" << std::endl;
        }
    }
    
    return 0;
}
