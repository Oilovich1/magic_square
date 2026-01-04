#include <Windows.h>
#include <locale>
#include <iostream>
#include <thread> 
#include <chrono>
#include <iomanip>
#include <vector>
#include <string>
#include <climits>

void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

int getUserChoise() {
    int choise;
    std::cout << "Введите порядок магического квадрата (положительное нечетное число): ";
    std::cin >> choise;
    if (choise < 0 || choise % 2 == 0) {
        std::cout << "Число должно быть положитеьным нечетным!\n Введите ещё раз: ";
        std::cin >> choise;
    }
    return choise;
}
void menu(){
    bool exitRequested = false;
    while (!exitRequested) {
    std::cout << "\n=== Меню проекта \"Магический Квадрат\" ===\n";
    std::cout << "1. Сгенерировать магический квадрат (нечётный порядок)\n";
    std::cout << "2. Загрузить магический квадрат из файла\n";
    std::cout << "3. Проверить, является ли текущий квадрат магическим\n";
    std::cout << "4. Вывести текущий квадрат на экран\n";
    std::cout << "5. Показать суммы строк\n";
    std::cout << "6. Показать суммы столбцов\n";
    std::cout << "7. Показать суммы диагоналей\n";
    std::cout << "8. Сохранить текущий квадрат в файл\n";
    std::cout << "9. Выйти\n";
    std::cout << "Введите номер пункта: ";

    int choice;
    if (!(std::cin >> choice)) {
        std::cout << "Ошибка: введите число.\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n'); 
        continue;
    }
    std::cin.ignore(INT_MAX, '\n');

    switch (choice) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:

        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        exitRequested = true;
        std::cout << "До свидания!\n";
        break;
    default:
        std::cout << "Неверный номер пункта. Пожалуйста, попробуйте снова.\n";
        break;
    }
} }

void printSquareWithDelay(const std::vector<std::vector<int>>& square, int delay_ms = 250) {
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