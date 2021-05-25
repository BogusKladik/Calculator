/*
 ============================================================================
 Name        : Ohae.c
 Author      : Vladislav Bogushov
 Version     : 1.0
 Copyright   : IVT
 Description : calculator
 Git	     : Во первых, вы должны обладать ссылкой (https://github.com/BogusKladik/Calculator/).
Теперь вы ей обладаете, самое сложное уже выполнено, осталось зайти в Eclipse, зайти в workspace(свой или новый, не важно).
Как откроется IDE сверху выбираем Window->Percpective->Open Percpective->Other...->Git.
Откроется специальное окно, нужно нажать clone git repository(в ряду с желтыми значками).
Появится окно, в нем нужно вбить сслыку, либо до откытия clone git repository сохранить в буфер обмена ссылку и Eclipse все сделает сам(Authentication заполнять не нужно, как и все остально кроме location, и в Connection выбрать протокол https).
Жмем Next, снова жмем Next, выбираем путь, где будет хранится репозиторий из гит на вашем компьютере(Путь должен содержать только английские буквы, и не должен содержать пробелыЁ!!!), а также желательно нажать на галочку в import all esisting Eclipse project after clone finishes.
Жмем finish и видим, что появилась папка в git repositories заходим в эту папку, дальше Working tree.
Видим папку Ohae, жмем 1 раз на нее, потом правой кнопкой. И жмем Import Project.
Появляется окно, в нем ничего выбирать не нужно, просто если Eclipse выбрал не ту папку, то стоит ее редактировать.
Жмем finish и уже проект появляется в C/C++. Теперь вы можете смотреть код(Ohae/src/Ohae.c).
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "libs/list.h"

int counter(unsigned long int i) { // Функция считает сколько нужно символов для числа типа int
    int counter = 0;
    if (i < 0) {
        counter++;
        i = -i;
    }
    do {
        counter++;
        i = i / 10;
    } while (i > 0);
    return counter;
}

// typedef struct example_input_data_for_lists {
//     char whatCalculator;
//     int sizeVector;
//     double *firstNum;
//     char operation;
//     double *secondNum;
//     char con;
// } example_input_data_for_lists;

// typedef struct input_data_for_lists { // Лист для записи данных для чтения
//     char whatCalculator;
//     int sizeVector;
//     double *firstNum;
//     char operation;
//     double *secondNum;
//     char con;
//     struct input_data_for_lists *next;
// } input_data_for_lists;

// typedef struct output_data_for_lists { // Лист для записи данных для вывода в другой файл
//     char *result;
//     struct output_data_for_lists *next;
// } output_data_for_lists;

// typedef struct links_for_lists
// { // Структура всех ссылок
// 	input_data_for_lists *head_in, *current_in;
// 	output_data_for_lists *head_out, *current_out;
// } links_for_lists;

// links_for_lists link_for_lists; // Создаем элемент этой структуры

// void fill_example(example_input_data_for_lists *current, FILE *InputFile){
//     fscanf(InputFile, " %c", &current->whatCalculator);
//     switch (current->whatCalculator) {
//         case 'v':
//             fscanf(InputFile, "%d", &current->sizeVector);
//             current->firstNum = malloc(current->sizeVector * sizeof(double));
//             for (int i = 0; i < current->sizeVector; i++) {
//                 fscanf(InputFile, "%lf", &current->firstNum[i]);
//             }

//             fscanf(InputFile, " %c", &current->operation);

//             current->secondNum = malloc(current->sizeVector * sizeof(double));
//             for (int i = 0; i < current->sizeVector; i++) {
//                 fscanf(InputFile, "%lf", &current->secondNum[i]);
//             }
//             break;
//         default:
//             current->firstNum = malloc(sizeof(double));
//             fscanf(InputFile, "%lf", current->firstNum);
//             fscanf(InputFile, " %c", &current->operation);
//             if (current->operation != '!') {
//                 current->secondNum = malloc(sizeof(double));
//                 fscanf(InputFile, "%lf", current->secondNum);
//             }
//     }
//     fscanf(InputFile, " %c ", &current->con);
// }

// void push_back_list_in(example_input_data_for_lists example_list){
//     if (link_for_lists.head_in == NULL) {
//         link_for_lists.head_in = malloc(sizeof(input_data_for_lists));
//         link_for_lists.current_in = link_for_lists.head_in;
//     } else {
//         link_for_lists.current_in = link_for_lists.head_in;
//         while (link_for_lists.current_in->next != NULL) {
//             link_for_lists.current_in = link_for_lists.current_in->next;
//         }
//         link_for_lists.current_in->next = malloc(sizeof(input_data_for_lists));
//         link_for_lists.current_in = link_for_lists.current_in->next;
//     }
//     link_for_lists.current_in->next = NULL;
//     link_for_lists.current_in->whatCalculator = example_list.whatCalculator;
//     switch (link_for_lists.current_in->whatCalculator) {
//         case 'v':
//             link_for_lists.current_in->sizeVector = example_list.sizeVector;
//             link_for_lists.current_in->firstNum = example_list.firstNum;
//             link_for_lists.current_in->operation = example_list.operation;
//             link_for_lists.current_in->secondNum = example_list.secondNum;
//             break;
//         default:
//             link_for_lists.current_in->firstNum = example_list.firstNum;
//             link_for_lists.current_in->operation = example_list.operation;
//             if (link_for_lists.current_in->operation != '!') {
//                 link_for_lists.current_in->secondNum = example_list.secondNum;
//             }
//     }
//     link_for_lists.current_in->con = example_list.con;
// }

// void push_back_list_out(char *line){
//     if (link_for_lists.head_out == NULL){
//         link_for_lists.head_out = malloc(sizeof(output_data_for_lists));
//         link_for_lists.current_out = link_for_lists.head_out;
//     } else {
//         link_for_lists.current_out = link_for_lists.head_out;
//         while (link_for_lists.current_out->next != NULL) {
//             link_for_lists.current_out = link_for_lists.current_out->next;
//         }
//         link_for_lists.current_out->next = malloc(sizeof(output_data_for_lists));
//         link_for_lists.current_out = link_for_lists.current_out->next;
//     }
//     link_for_lists.current_out->next = NULL;
//     link_for_lists.current_out->result = line;
// }

// void pop_list_in(){
//     if (link_for_lists.head_in == NULL || link_for_lists.current_in == NULL){
//         return;
//     }
//     if (link_for_lists.head_in == link_for_lists.current_in){
//         link_for_lists.current_in = link_for_lists.current_in->next;
//         free(link_for_lists.head_in);
//         link_for_lists.head_in = link_for_lists.current_in;
//         return;
//     }
//     input_data_for_lists *term = link_for_lists.head_in;
//     while (term->next != link_for_lists.current_in){
//         term = term->next;
//     }
//     term->next = link_for_lists.current_in->next;
//     free(link_for_lists.current_in);
//     link_for_lists.current_in = term;
// }

// char *pop_list_out(){
//     if (link_for_lists.head_out == NULL || link_for_lists.current_out == NULL){
//         return NULL;
//     }
//     char *line;
//     if (link_for_lists.head_out == link_for_lists.current_out){
//         line = link_for_lists.current_out->result;
//         link_for_lists.current_out = link_for_lists.current_out->next;
//         free(link_for_lists.head_out);
//         link_for_lists.head_out = link_for_lists.current_out;
//         return line;
//     }
//     output_data_for_lists *term = link_for_lists.head_out;
//     while (term->next != link_for_lists.current_out){
//         term = term->next;
//     }
//     line = link_for_lists.current_out->result;
//     term->next = link_for_lists.current_out->next;
//     free(link_for_lists.current_out);
//     link_for_lists.current_out = term;
//     return line;
// }

// void deleteListIn() { // Удалить лист input_data_for_lists
//     link_for_lists.current_in = link_for_lists.head_in;
//     while (link_for_lists.current_in != NULL){
//         link_for_lists.current_in = link_for_lists.head_in;
//         pop_list_in();
//     }
// }

// void deleteListOut() { // Удалить лист output_data_for_lists
//     link_for_lists.current_out = link_for_lists.head_out;
//     while (link_for_lists.current_out != NULL){
//         link_for_lists.current_out = link_for_lists.head_out;
//         pop_list_out();
//     }
// }

// void writeListIntoFile(FILE *OutputFile) { // Вписать из листа в файл
//     link_for_lists.current_out = link_for_lists.head_out;
//     while (link_for_lists.current_out != NULL) {
//         fprintf(OutputFile, "%s\n", pop_list_out());
//     }
// }

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    FILE *InputFile, *OutputFile;
    // link_for_lists.head_in = NULL;
    // link_for_lists.current_in = link_for_lists.head_in;
    // link_for_lists.head_out = NULL;
    // link_for_lists.current_out = link_for_lists.head_out;
    int NewWriteFile = 0; // NewWriteFile - Чтобы не выводил блок, который делает спрос о продолжении файла
    char inputc[255], outputc[255];   // Название файла ввода или вывода
    char confl, fl = 'n', continueCalculate;             // confl - продолжить работу с файлами, fl - оставить ли предыдущий файл или нет
    do                                // Цикл для работы с файлами
    {
        printf("File to read: ");
        scanf(" %s", inputc);
        InputFile = fopen(inputc, "r");
        while (InputFile == NULL || feof(InputFile)) // Проверяем целлосность данных
        {
            if (feof(InputFile))
                printf("The file is empty\n");
            else
                printf("Incorrect file name\n");
            scanf(" %s", inputc);
            InputFile = fopen(inputc, "r");
        }
        while (!feof(InputFile)) { // Заполнение всего листа input_data_for_lists
            example_input_data_for_lists example_list;
            fill_example(&example_list, InputFile);
            push_back_list_in(example_list);
        }
        fclose(InputFile);
        link_for_lists.current_in = link_for_lists.head_in;
        if (NewWriteFile) // Повторить ли файл вписывания
        {
            printf("Repeat the file for writing?(y/n)\n");
            scanf(" %c", &fl);                 // Читает символ, если y - продолжить, если n - закончить
            while ((fl != 'y') && (fl != 'n')) // Проверка на корректно введенное y или n
            {
                printf("invalid character, write \"y\" or \"n\"\n");
                scanf(" %c", &fl);
            }
            NewWriteFile = 0;
            if (fl == 'y') {
                OutputFile = fopen(outputc, "a");
            }
        }
        if (!NewWriteFile && fl == 'n') // Открытие нового файла
        {
            NewWriteFile = 1;
            printf("File to write: ");
            scanf(" %s", outputc);
            OutputFile = fopen(outputc, "w");
        }
        // head_out = malloc(sizeof(output_data_for_lists));
        // output_data_for_lists *outListGo = head_out;
        do // Через do чтобы калькулятор выполнился хотя бы 1 раз
        {
            char *lineExpression;
            switch (link_for_lists.current_in->whatCalculator) {
                case 'a':;
                    double res;
                    switch (link_for_lists.current_in->operation) // Проверяем знак
                    {
                        case '+': // Сумма
                            res = link_for_lists.current_in->firstNum[0] + link_for_lists.current_in->secondNum[0];
                            lineExpression = malloc(
                                    (counter((int) link_for_lists.current_in->firstNum[0]) + counter((int) link_for_lists.current_in->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char)); // Выделение памяти как и в след. вариантах
                            sprintf(lineExpression, "%lf + %lf = %lf", link_for_lists.current_in->firstNum[0], link_for_lists.current_in->secondNum[0],
                                    res); // Вывод суммы
                            break;
                        case '-': // Разность
                            res = link_for_lists.current_in->firstNum[0] - link_for_lists.current_in->secondNum[0];
                            lineExpression = malloc(
                                    (counter((int) link_for_lists.current_in->firstNum[0]) + counter((int) link_for_lists.current_in->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(lineExpression, "%lf - %lf = %lf", link_for_lists.current_in->firstNum[0], link_for_lists.current_in->secondNum[0],
                                    res); // Вывод разности
                            break;
                        case '*': // Умножение
                            lineExpression = malloc(
                                    (counter((int) link_for_lists.current_in->firstNum[0]) + counter((int) link_for_lists.current_in->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(lineExpression, "%lf * %lf = %lf", link_for_lists.current_in->firstNum[0], link_for_lists.current_in->secondNum[0],
                                    res); // Вывод умножения
                            break;
                        case '/': // Деление
                            if (link_for_lists.current_in->secondNum[0] == 0) {
                                lineExpression = malloc(23 * sizeof(char));
                                sprintf(lineExpression, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            res = link_for_lists.current_in->firstNum[0] / link_for_lists.current_in->secondNum[0];
                            lineExpression = malloc(
                                    (counter((int) link_for_lists.current_in->firstNum[0]) + counter((int) link_for_lists.current_in->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(lineExpression, "%lf / %lf = %lf", link_for_lists.current_in->firstNum[0], link_for_lists.current_in->secondNum[0],
                                    res); // Вывод деления
                            break;
                        case '\\': // Деление без остатка
                            if (link_for_lists.current_in->secondNum[0] == 0) {
                                lineExpression = malloc(23 * sizeof(char));
                                sprintf(lineExpression, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            res = link_for_lists.current_in->firstNum[0] / link_for_lists.current_in->secondNum[0];
                            lineExpression = malloc(
                                    (counter((int) link_for_lists.current_in->firstNum[0]) + counter((int) link_for_lists.current_in->secondNum[0]) +
                                     counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(lineExpression, "%lf \\ %lf = %i", link_for_lists.current_in->firstNum[0], link_for_lists.current_in->secondNum[0],
                                    (int) res); // Вывод деления без остатка
                            break;
                        case '#': // Остаток от деления
                            if (link_for_lists.current_in->secondNum[0] == 0) {
                                lineExpression = malloc(23 * sizeof(char));
                                sprintf(lineExpression, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            res = link_for_lists.current_in->firstNum[0] / link_for_lists.current_in->secondNum[0];
                            res = link_for_lists.current_in->firstNum[0] - ((int) res * link_for_lists.current_in->secondNum[0]);
                            lineExpression = malloc(
                                    (counter((int) link_for_lists.current_in->firstNum[0]) + counter((int) link_for_lists.current_in->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(lineExpression, "%lf # %lf = %lf", link_for_lists.current_in->firstNum[0], link_for_lists.current_in->secondNum[0],
                                    res); // Вывод остаток от деления
                            break;
                        case '!': // Факториал, точка с запятой нужна, чтобы не было ошибки из-за инициализации fuct
                            if ((link_for_lists.current_in->firstNum[0] - (int) link_for_lists.current_in->firstNum[0]) ==
                                0) // Проверка на то, что это целое число
                            {
                                unsigned long int fuct = link_for_lists.current_in->firstNum[0]; // Результат вычисления факториала
                                if ((int) link_for_lists.current_in->firstNum[0] >
                                    0) // Проверка на правильность введения числа, а также представление double, как int
                                {
                                    for (int i = 1; i < (int) link_for_lists.current_in->firstNum[0]; i++) {
                                        fuct = fuct * i; // Процесс вычисления факториала
                                    }
                                    lineExpression = malloc(
                                            (counter((int) link_for_lists.current_in->firstNum[0]) +
                                             counter((int) res) + 6) *
                                            sizeof(char));
                                    sprintf(lineExpression, "%i ! = %lu", (int) link_for_lists.current_in->firstNum[0],
                                            fuct); // Вывод факториала
                                } else if (link_for_lists.current_in->firstNum[0] ==
                                           0) { // Факториал от 0 равен 1
                                    lineExpression = malloc(
                                            (counter((int) link_for_lists.current_in->firstNum[0]) +
                                             7) *
                                            sizeof(char));
                                    sprintf(lineExpression, "%i ! = 1",
                                            (int) link_for_lists.current_in->firstNum[0]); // Аналогично вывод
                                } else {
                                    lineExpression = malloc(29 * sizeof(char));
                                    sprintf(lineExpression,
                                            "Write down a positive number"); // Если пользователь ввел неправильно пишем Write down a positive number
                                    break;
                                }
                            } else // Если число не целое
                            {
                                lineExpression = malloc(17 * sizeof(char));
                                sprintf(lineExpression, "Write an integer"); // Комментарий говорит сам за себя
                                break;                                          // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            break;
                        case '^': // Степень
                            if ((link_for_lists.current_in->secondNum[0] - (int) link_for_lists.current_in->secondNum[0]) ==
                                0) // Проверка на то, что степень - целое число
                            {
                                res = link_for_lists.current_in->firstNum[0];
                                if ((int) link_for_lists.current_in->secondNum[0] >
                                    0) // Проверка знака степени, а также из double в int, поэтому возводить только в целую степень
                                {
                                    for (int j = 0; j < (int) link_for_lists.current_in->secondNum[0] - 1; j++) {
                                        res = res * link_for_lists.current_in->firstNum[0]; // Процесс вычисления степени числа
                                    }
                                    lineExpression = malloc(
                                            (counter((int) link_for_lists.current_in->firstNum[0]) +
                                             counter((int) link_for_lists.current_in->secondNum[0]) +
                                             counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                            sizeof(char));
                                    sprintf(lineExpression, "%lf ^ %i = %lf", link_for_lists.current_in->firstNum[0],
                                            (int) link_for_lists.current_in->secondNum[0],
                                            res); // Вывод операции степени
                                } else if ((int) link_for_lists.current_in->secondNum[0] < 0) // Исход с отрицательной степенью
                                {
                                    double c, d; // Добавляем числа, чтобы представить a как 1/a и возвести в положительную степень
                                    res = 1 / link_for_lists.current_in->firstNum[0];
                                    c = 1 / link_for_lists.current_in->firstNum[0];
                                    d = -link_for_lists.current_in->secondNum[0];
                                    for (int j = 0; j < (int) d - 1; j++) {
                                        res = res * c; // Процесс вычисления степени числа
                                    }
                                    lineExpression = malloc(
                                            (counter((int) link_for_lists.current_in->firstNum[0]) +
                                             counter((int) link_for_lists.current_in->secondNum[0]) +
                                             counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                            sizeof(char));
                                    sprintf(lineExpression, "%lf ^ %i = %lf", link_for_lists.current_in->firstNum[0],
                                            (int) link_for_lists.current_in->secondNum[0],
                                            res); // Вывод операции отрицательной степени
                                } else {
                                    lineExpression = malloc(
                                            (counter((int) link_for_lists.current_in->firstNum[0]) +
                                             counter((int) link_for_lists.current_in->secondNum[0]) + 7 + 2 * 3 + 1) *
                                            sizeof(char));
                                    sprintf(lineExpression, "%lf ^ %i = 1", link_for_lists.current_in->firstNum[0],
                                            (int) link_for_lists.current_in->secondNum[0]); // Если степень равна 0, то число в этой степени равно 1
                                }
                            } else // Если число не целое
                            {
                                lineExpression = malloc(28 * sizeof(char));
                                sprintf(lineExpression,
                                        "Write an integer to a power"); // Комментарий говорит сам за себя
                                break;                                  // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            break;
                        default:
                            lineExpression = malloc(27 * sizeof(char));
                            sprintf(lineExpression,
                                    "I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    break;
                case 'v':
                    while (link_for_lists.current_in->sizeVector < 1) // Размер вектора не может быть отрицательным или равным нулю
                    {
                        lineExpression = malloc(24 * sizeof(char));
                        sprintf(lineExpression, "The minimum value is 1!");
                        break;
                    }
                    double *resvec; // Результат операции
                    resvec = malloc(link_for_lists.current_in->sizeVector * sizeof(double));
                    int sizeLine = 1;
                    switch (link_for_lists.current_in->operation) {
                        case '+': // Сумма векторов
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                resvec[i] = link_for_lists.current_in->firstNum[i] + link_for_lists.current_in->secondNum[i];
                                sizeLine +=
                                        counter((int) link_for_lists.current_in->firstNum[i]) + counter((int) link_for_lists.current_in->secondNum[i]) +
                                        counter((int) resvec[i]) + 7 * 3;
                            }
                            sizeLine += (2 + (link_for_lists.current_in->sizeVector - 1) * 2) * 3 + 2 * 3 + 1;
                            lineExpression = malloc(sizeLine * sizeof(char));
                            sprintf(lineExpression, "(");
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, link_for_lists.current_in->firstNum[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s) ", lineExpression);
                                }
                            }
                            sprintf(lineExpression, "%s+ (", lineExpression);
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, link_for_lists.current_in->secondNum[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s) ", lineExpression);
                                }
                            }
                            sprintf(lineExpression, "%s= (", lineExpression);
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, resvec[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s)", lineExpression);
                                }
                            }
                            break;
                        case '-': // Разность векторов
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                resvec[i] = link_for_lists.current_in->firstNum[i] - link_for_lists.current_in->secondNum[i];
                                sizeLine +=
                                        counter((int) link_for_lists.current_in->firstNum[i]) + counter((int) link_for_lists.current_in->secondNum[i]) +
                                        counter((int) resvec[i]) + 7 * 3;
                            }
                            sizeLine += (2 + (link_for_lists.current_in->sizeVector - 1) * 2) * 3 + 2 * 3 + 1;
                            lineExpression = malloc(sizeLine * sizeof(char));
                            sprintf(lineExpression, "(");
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, link_for_lists.current_in->firstNum[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s) ", lineExpression);
                                }
                            }
                            sprintf(lineExpression, "%s- (", lineExpression);
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, link_for_lists.current_in->secondNum[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s) ", lineExpression);
                                }
                            }
                            sprintf(lineExpression, "%s= (", lineExpression);
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, resvec[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s)", lineExpression);
                                }
                            }
                            break;
                        case 'c':; // Скалярное произведение
                            double resvecc = 0.0;
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                resvecc += link_for_lists.current_in->firstNum[i] * link_for_lists.current_in->secondNum[i];
                                sizeLine +=
                                        counter((int) link_for_lists.current_in->firstNum[i]) + counter((int) link_for_lists.current_in->secondNum[i]) +
                                        7 * 2;
                            }
                            sizeLine +=
                                    (2 + (link_for_lists.current_in->sizeVector - 1) * 2) * 2 + 2 * 3 + 2 + counter((int) resvecc) + 7;
                            lineExpression = malloc(sizeLine * sizeof(char));
                            sprintf(lineExpression, "((");
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, link_for_lists.current_in->firstNum[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s) ", lineExpression);
                                }
                            }
                            sprintf(lineExpression, "%s* (", lineExpression);
                            for (int i = 0; i < link_for_lists.current_in->sizeVector; i++) {
                                sprintf(lineExpression, "%s%lf", lineExpression, link_for_lists.current_in->secondNum[i]);
                                if (i < link_for_lists.current_in->sizeVector - 1) {
                                    sprintf(lineExpression, "%s, ", lineExpression);
                                } else {
                                    sprintf(lineExpression, "%s)) ", lineExpression);
                                }
                            }
                            sprintf(lineExpression, "%s= %lf", lineExpression, resvecc);
                            break;
                        default:
                            lineExpression = malloc(27 * sizeof(char));
                            sprintf(lineExpression,
                                    "I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    break;
                default:
                    lineExpression = malloc(29 * sizeof(char));
                    sprintf(lineExpression, "Required to write \"a\" or \"v\"");
            }
            push_back_list_out(lineExpression);
            continueCalculate = link_for_lists.current_in->con;
            pop_list_in();
        } while (continueCalculate ==
                 'y');     // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
        deleteListIn(); // Очищаем память
        writeListIntoFile(OutputFile);
        deleteListOut(); // Очищаем память
        fclose(OutputFile);
        printf("Continue with files?(y/n)\n");   // Вывод строки, с вопросом, продолжить ли вычисление с файлами
        scanf(" %c", &confl);                    // Читает символ, если y - продолжить, если n - закончить
        while ((confl != 'y') && (confl != 'n')) // Проверка на корректно введенное y или n
        {
            printf("Invalid character, write \"y\" or \"n\"\n");
            scanf(" %c", &confl);
        }
    } while (confl == 'y');
    return 0;
}
