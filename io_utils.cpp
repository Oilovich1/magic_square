#include <Windows.h>
#include <locale>

void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

