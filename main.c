#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Вспомогательная функция для добавления строки в массив
void add_command(char*** commands, int** len_of_commands, int index, const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Вычисляем длину строки
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Выделяем память для строки
    (*commands)[index] = malloc((len + 1) * sizeof(char));
    if ((*commands)[index] == NULL) {
        perror("Ошибка выделения памяти для строки");
        exit(EXIT_FAILURE);
    }

    // Записываем строку
    va_start(args, format);
    vsnprintf((*commands)[index], len + 1, format, args);
    va_end(args);

    // Сохраняем длину строки
    (*len_of_commands)[index] = len;
}

int move_z(char*** commands, int** len_of_commands, float z) {
    int num_of_commands = 3;

    // Выделяем память для массивов
    *commands = malloc(num_of_commands * sizeof(char*));
    if (*commands == NULL) {
        perror("Ошибка выделения памяти для массива строк");
        exit(EXIT_FAILURE);
    }

    *len_of_commands = malloc(num_of_commands * sizeof(int));
    if (*len_of_commands == NULL) {
        perror("Ошибка выделения памяти для длин строк");
        exit(EXIT_FAILURE);
    }

    // Добавляем команды
    add_command(commands, len_of_commands, 0, "G91");
    add_command(commands, len_of_commands, 1, "G1 Z%.2f F3000", z);
    add_command(commands, len_of_commands, 2, "G90");

    return num_of_commands;
}

int main() {
    char** commands = NULL;
    int* len_of_commands = NULL;
    int num_of_commands = move_z(&commands, &len_of_commands, 10.0);

    // Выводим команды
    for (int i = 0; i < num_of_commands; i++) {
        printf("Команда %d: %s (длина: %d)\n", i, commands[i], len_of_commands[i]);
        free(commands[i]); // Освобождаем память для каждой строки
    }

    free(commands); // Освобождаем память для массива указателей
    free(len_of_commands); // Освобождаем память для массива длин

    return 0;
}