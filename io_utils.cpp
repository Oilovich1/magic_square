#include <Windows.h>
#include <locale>
#include <iostream>
#include <thread> 
#include <chrono>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <climits>
#include "io_utils.hpp"

void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

void displayMenu(){
    std::cout << "\n=== Меню проекта \"Магический Квадрат\" ===\n";
    std::cout << "1. Сгенерировать магический квадрат (нечётный порядок)\n";
    std::cout << "2. Загрузить магический квадрат из файла\n";
    std::cout << "3. Проверить, является ли текущий квадрат магическим\n";
    std::cout << "4. Вывести текущий квадрат на экран\n";
    std::cout << "5. Показать суммы строк, столбцов и дагоналей\n";
    std::cout << "6. Сохранить текущий квадрат в файл\n";
    std::cout << "7. Выйти\n";
    std::cout << "Введите номер пункта: ";
}

int getUserChoice() {
    int choice;
    while (true)
        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 7) {
                return choice;
            }
            else {
                std::cout << "Ошибка: Введите число от 1 до 7.\n";
            }
        }
        else {
            std::cout << "Ошибка: Введите корректное число.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
}

int getOddSize() {
    int size;
    while (true) {
        std::cout << "Введите нечетный размер квадрата (n > 0): ";
        if (std::cin >> size) {
            if (size > 0 && size % 2 == 1) {
                return size;
            }
            else {
                std::cout << "Ошибка: Размер должен быть положительным нечетным числом.\n";
            }
        }
        else {
            std::cout << "Ошибка: Введите корректное число.\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
}


void printSquareWithDelay(const std::vector<std::vector<int>>& square, int delay_ms) {
    int n = square.size();

    if (n == 0) {
        std::cout << "Квадрат пуст.\n";
        return;
    }
    int max_num = 1;
    for (const auto& row : square) {
        for (int num : row) {
            if (num > max_num) max_num = num;
        }
    }
    int width = std::to_string(max_num).length() + 1;

    std::cout << "\n~~~ Магический Квадрат ~~~\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(width) << square[i][j];

            if (j < n - 1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
            }
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }

    std::cout << "--- Вывод завершён ---\n\n";
}

bool readSquareFromFile(const std::string& filename, std::vector<std::vector<int>>& matrix, int& size) {
    matrix.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл '" << filename << "' для чтения.\n";
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int num;

        while (iss >> num) {
            row.push_back(num);
        }

        if (iss.fail() && !iss.eof()) {
            std::cerr << "Ошибка: Найден некорректный символ в строке файла: " << line << "\n";
            file.close();
            return false;
        }

        if (row.empty() && !line.empty()) {
            std::istringstream check_iss(line);
            if (check_iss >> num) {
                std::string trimmed_line = line;
                size_t start = trimmed_line.find_first_not_of(" \t\n\r\f\v");
                if (start != std::string::npos) {
                    trimmed_line = trimmed_line.substr(start);
                    size_t end = trimmed_line.find_last_not_of(" \t\n\r\f\v");
                    trimmed_line = trimmed_line.substr(0, end + 1);
                }
                if (!trimmed_line.empty()) {
                    std::cerr << "Ошибка: Найден некорректный символ в строке файла (не число): " << line << "\n";
                    file.close();
                    return false;
                }
                continue;
            }
            else {
                std::cerr << "Ошибка: Найден некорректный символ в строке файла (не число): " << line << "\n";
                file.close();
                return false;
            }
        }

        matrix.push_back(row);
    }

    file.close();

    if (matrix.empty()) {
        std::cerr << "Ошибка: Файл '" << filename << "' пуст или не содержит чисел.\n";
        return false;
    }

    size_t n = matrix.size();
    for (const auto& row : matrix) {
        if (row.size() != n) {
            std::cerr << "Ошибка: Матрица в файле не является квадратной.\n";
            matrix.clear();
            return false;
        }
    }

    size = static_cast<int>(n);
    return true;
}

bool writeSquareToFile(const std::vector<std::vector<int>>& matrix) {
    std::string filename;
    std::cout << "Введите имя файла для сохранения квадрата: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл '" << filename << "' для записи.\n";
        return false;
    }

    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j];
            if (j < row.size() - 1) {
                file << " "; 
            }
        }
        file << "\n";
    }

    file.close();
    std::cout << "Квадрат успешно записан в файл '" << filename << "'.\n";
    return true;
}