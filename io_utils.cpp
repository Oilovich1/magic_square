#include <Windows.h>
#include <locale>
#include <iostream>
#include <thread> 
#include <chrono>
#include <iomanip>
#include <vector>
#include <string>
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