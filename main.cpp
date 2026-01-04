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
            printSquareWithDelay(square, 100);
        }
            break;
        case 2:{
            std::cout << "Вы выбрали: Загрузить магический квадрат из файла.\n";
        }
             break;
        case 3:{
            std::cout << "Вы выбрали: Проверить является ли текущий квадрат магическим.\n";
            if (isMagicSquare(square)) {
                std::cout << "Текущий квадрат магический\n";
            }
            else {
                std::cout << "Текщий квадрат НЕ магический\n";
            }
        }
            break;
        case 4:{
            std::cout << "Вы выбрали: Вывести текущий квадрат.\n";
            printSquareWithDelay(square, 100);
        }
            break;
        case 5:{
            std::cout << "Вы выбрали: Показать суммы строк, столбцов и дагоналей\n";
            std::vector<int> rows = getRowSums(square);
            std::vector<int> cols = getColSums(square);
            std::pair<int, int> diagonals = getDiagonalSums(square);
            for (int i = 0; i < size; i++) {
                std::cout << "Сумма значений " << i + 1 << " ряда = " << rows[i] << std::endl;
            }
            for (int j = 0; j < size; j++) {
                std::cout << "Сумма значений " << j + 1 << " столбца = " << cols[j] << std::endl;
            }
            std::cout << "Сумма значений на главной диагонали = " << diagonals.first << std::endl;
            std::cout << "Сумма значений на побочной диагонали = " << diagonals.second << std::endl;
        }
            break;
        case 6:{
            std::cout << "Вы выбрали: Сохранить текущий квадрат в файл\n";
        }
            break;
        case 7:{
            std::cout << "Выход из программы";
        }
            break;
        default:
            std::cout << "Неизвестная команда.\n";
        }
    } while (userChoice != 7);

    return 0;
}