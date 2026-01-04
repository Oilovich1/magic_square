#include "io_utils.hpp"
#include "magic_square.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    setupConsole();
    int userChoice;
    int size;
    std::vector<std::vector<int>> square;
    do {
        displayMenu();
        userChoice = getUserChoice();

        switch (userChoice) {
        case 1: {
            std::cout << "Вы выбрали: Сгенерировать магический квадрат.\n";
            size = getOddSize();
            square = generateMagicSquare(size);
            int rotate = generateRandomNumber(0, 3);
            for (int i = 0; i <= rotate; i++) {
                square = rotateSquare(square);
            }
            int reflect = generateRandomNumber(0, 1);
            square = reflectSquare(square, reflect);
            printSquareWithDelay(square, 250);
        }
            break;
        case 2:
            std::cout << "Вы выбрали: Загрузить магический квадрат из файла.\n";
            break;
        case 3:
            std::cout << "Вы выбрали: Проверить является ли текущий квадрат магическим.\n";
            break;
        case 4:
            std::cout << "Вы выбрали: Вывести текущий квадрат.\n";
            break;
        case 5:
            std::cout << "Вы выбрали: Показать суммы строк, столбцов и дагоналей\n";
            break;
        case 6:
            std::cout << "Вы выбрали: Сохранить текущий квадрат в файл\n";
            break;
        case 7:
            std::cout << "Выход из программы";
            break;
        default:
            std::cout << "Неизвестная команда.\n";
        }
    } while (userChoice != 7);

    return 0;
}