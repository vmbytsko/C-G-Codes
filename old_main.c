#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int move_z(char*** commands, int** len_of_commands, float z) {
    int num_of_commands = 3;
    int estimated_size = 100;
    int i, len;
    char* str;

    *len_of_commands = malloc(num_of_commands * sizeof(int));
    if (*len_of_commands == NULL) {
        perror("Ошибка выделения памяти для длин строк");
        exit(EXIT_FAILURE);
    }

    // Выделяем память для массива указателей
    *commands = malloc(num_of_commands * sizeof(char*));
    if (*commands == NULL) {
        perror("Ошибка выделения памяти для массива строк");
        exit(EXIT_FAILURE);
    }
    
    /*for (int i = 0; i < num_of_commands; i++) {
        (*commands)[i] = malloc(100 * sizeof(char)); // 100 байт для каждой строки
        if (commands[i] == NULL) {
            perror("Ошибка выделения памяти для строки");
            exit(EXIT_FAILURE);
        }
    }*/

    i = 0;
    str = (char *)malloc(estimated_size * sizeof(char));
    free(str);
    len = snprintf(str, estimated_size, "G91");
    (*commands)[i] = malloc((len+1) * sizeof(char)); // 100 байт для каждой строки
    if (commands[i] == NULL) {
        perror("Ошибка выделения памяти для строки");
        exit(EXIT_FAILURE);
    }
    snprintf((*commands)[i], len + 1, "G91");
    (*len_of_commands)[i] = len;

    i = 1;
    str = (char *)malloc(estimated_size * sizeof(char));
    free(str);
    len = snprintf(str, estimated_size, "G1 Z%.2f F3000", z);
    (*commands)[i] = malloc((len+1) * sizeof(char)); // 100 байт для каждой строки
    if (commands[i] == NULL) {
        perror("Ошибка выделения памяти для строки");
        exit(EXIT_FAILURE);
    }
    snprintf((*commands)[i], len + 1, "G1 Z%.2f F3000", z);
    (*len_of_commands)[i] = len;

    i = 2;
    str = (char *)malloc(estimated_size * sizeof(char));
    len = snprintf(str, estimated_size, "G90");
    free(str);
    (*commands)[i] = malloc((len+1) * sizeof(char)); // 100 байт для каждой строки
    if (commands[i] == NULL) {
        perror("Ошибка выделения памяти для строки");
        exit(EXIT_FAILURE);
    }
    snprintf((*commands)[i], len + 1, "G90", z);
    (*len_of_commands)[i] = len;

    return num_of_commands;
}

int main() {
    char** commands = NULL;
    int* len_of_commands = NULL;
    int num_of_commands = move_z(&commands, &len_of_commands, 10.0);

    for (int i = 0; i < num_of_commands; i++) {
        printf("%s\n", commands[i]);
    }

    return 0;
}