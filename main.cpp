#include "io_utils.hpp"
#include "magic_square.hpp"
#include <iostream>

int main() {
    setupConsole();
    int userChoice;
    int size;
    std::vector<std::vector<int>> square;
    do {
        displayMenu();
		std::cin.clear();
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

            const int print_confirm = 15;
            if (size > print_confirm) {
                std::cout << "Квадрат размера " << size << "x" << size << " большой. Вывести полностью в консоль? (y/yes/д/да): ";
                std::string ans;
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::getline(std::cin, ans);

                if (ans == "y" || ans == "yes" || ans == "д" || ans == "да") {
                    printSquareWithDelay(square, 0);
                }
                else {
                    std::cout << "Вывод большого квадрата отменён пользователем.\n";
                }
            }
            else {
                printSquareWithDelay(square, 100);
            }
        }
            break;
        case 2:{
            std::cout << "Вы выбрали: Загрузить магический квадрат из файла.\n";
			std::string filename;
			std::cout << "Введите имя файла: ";
			std::cin >> filename;
            if (!readSquareFromFile(filename, square, size)) {
                std::cout << "Ошибка: Не удалось загрузить квадрат из файла.\n";
                break;
			}
            else {
                std::cout << "Файл был успешно прочитан.\n";
            }
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
            if (isValidSquare(square)){
                const int print_confirm = 15;
                if (size > print_confirm) {
                    std::cout << "Квадрат размера " << size << "x" << size << " большой. Вывести полностью в консоль? (y/yes/д/да): ";
                    std::string ans;
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::getline(std::cin, ans);

                    if (ans == "y" || ans == "yes" || ans == "д" || ans == "да") {
                        printSquareWithDelay(square, 0);
                    }
                    else {
                        std::cout << "Вывод большого квадрата отменён пользователем.\n";
                    }
                }
                else {
                    printSquareWithDelay(square, 100);
                }
            }
            else
                std::cout << "Невозможно вывести текущий квадрат\n";
        }
            break;
        case 5:{
            std::cout << "Вы выбрали: Показать суммы строк, столбцов и дагоналей\n";
            if (!isValidSquare(square)) {
                std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
                break;
            }
            std::vector<int> rows = getRowSums(square);
            std::vector<int> cols = getColSums(square);
            std::array<int,2> diagonals = getDiagonalSums(square);
            for (int i = 0; i < size; i++) {
                std::cout << "Сумма значений " << i + 1 << " ряда = " << rows[i] << std::endl;
            }
            for (int j = 0; j < size; j++) {
                std::cout << "Сумма значений " << j + 1 << " столбца = " << cols[j] << std::endl;
            }
            std::cout << "Сумма значений на главной диагонали = " << diagonals[0] << std::endl;
            std::cout << "Сумма значений на побочной диагонали = " << diagonals[1] << std::endl;
        }
            break;
        case 6:{
            std::cout << "Вы выбрали: Сохранить текущий квадрат в файл\n";
            if (isValidSquare(square)) {
                writeSquareToFile(square);
            }
            else {
                std::cout << "Текущий квадрат невозможно записать в файл";
            }
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