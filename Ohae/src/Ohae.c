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

typedef struct example_input_data {
    char whatCalculator;
    int sizeVector;
    double *firstNum;
    char operation;
    double *secondNum;
    char con;
} example_input_data;

typedef struct input_data { // Лист для записи данных для чтения
    char whatCalculator;
    int sizeVector;
    double *firstNum;
    char operation;
    double *secondNum;
    char con;
    struct input_data *next;
} input_data;

typedef struct output_data { // Лист для записи данных для вывода в другой файл
    char *result;
    struct output_data *next;
} output_data;

void fill_example(example_input_data *current, FILE *InputFile){
    fscanf(InputFile, " %c", &current->whatCalculator);
    switch (current->whatCalculator) {
        case 'v':
            fscanf(InputFile, "%d", &current->sizeVector);
            current->firstNum = malloc(current->sizeVector * sizeof(double));
            for (int i = 0; i < current->sizeVector; i++) {
                fscanf(InputFile, "%lf", &current->firstNum[i]);
            }

            fscanf(InputFile, " %c", &current->operation);

            current->secondNum = malloc(current->sizeVector * sizeof(double));
            for (int i = 0; i < current->sizeVector; i++) {
                fscanf(InputFile, "%lf", &current->secondNum[i]);
            }
            break;
        default:
            current->firstNum = malloc(sizeof(double));
            fscanf(InputFile, "%lf", current->firstNum);
            fscanf(InputFile, " %c", &current->operation);
            if (current->operation != '!') {
                current->secondNum = malloc(sizeof(double));
                fscanf(InputFile, "%lf", current->secondNum);
            }
    }
    fscanf(InputFile, " %c ", &current->con);
}

void pushback(input_data **head, example_input_data example_list){
    input_data *current;
    if (*head == NULL) {
        *head = malloc(sizeof(input_data));
        current = *head;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(input_data));
        current = current->next;
    }
    current->whatCalculator = example_list.whatCalculator;
    switch (current->whatCalculator) {
        case 'v':
            current->sizeVector = example_list.sizeVector;
            //current->firstNum = malloc(current->sizeVector * sizeof(double));
            current->firstNum = example_list.firstNum;
            current->operation = example_list.operation;
            //current->secondNum = malloc(current->sizeVector * sizeof(double));
            current->secondNum = example_list.secondNum;
            break;
        default:
            //current->firstNum = malloc(sizeof(double));
            current->firstNum = example_list.firstNum;
            current->operation = example_list.operation;
            if (current->operation != '!') {
                //current->secondNum = malloc(sizeof(double));
                current->secondNum = example_list.secondNum;
            }
    }
    current->con = example_list.con;
    current->next = NULL;
}

void push_back(input_data **head, FILE *InputFile) { // Название функции говорит само за себя
    input_data *current;
    if (*head == NULL) {
        *head = malloc(sizeof(input_data));
        current = *head;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(input_data));
        current = current->next;
    }
    fscanf(InputFile, " %c", &current->whatCalculator);
    switch (current->whatCalculator) {
        case 'v':
            fscanf(InputFile, "%d", &current->sizeVector);
            current->firstNum = malloc(current->sizeVector * sizeof(double));
            for (int i = 0; i < current->sizeVector; i++) {
                fscanf(InputFile, "%lf", &current->firstNum[i]);
            }

            fscanf(InputFile, " %c", &current->operation);

            current->secondNum = malloc(current->sizeVector * sizeof(double));
            for (int i = 0; i < current->sizeVector; i++) {
                fscanf(InputFile, "%lf", &current->secondNum[i]);
            }
            break;
        default:
            current->firstNum = malloc(sizeof(double));
            fscanf(InputFile, "%lf", current->firstNum);
            fscanf(InputFile, " %c", &current->operation);
            if (current->operation != '!') {
                current->secondNum = malloc(sizeof(double));
                fscanf(InputFile, "%lf", current->secondNum);
            }
    }
    fscanf(InputFile, " %c ", &current->con);
    current->next = NULL;
}

void deleteListI(input_data *head) { // Удалить лист input_data
    input_data *current;
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}

void deleteListO(output_data *head) { // Удалить лист output_data
    output_data *current;
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}

void writeListIntoFile(output_data *head, FILE *OutputFile) { // Вписать из листа в файл
    output_data *current = head;
    while (current != NULL) {
        fprintf(OutputFile, "%s\n", current->result);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    FILE *InputFile, *OutputFile;
    input_data *head = NULL;          // Начало двух листов
    output_data *head_out = NULL;
    int NewWriteFile = 0, repeat = 0; // NewWriteFile - Чтобы не выводил блок, который делает спрос о продолжении файла
    char inputc[255], outputc[255];   // Название файла ввода или вывода
    char confl, fl = 'n';             // confl - продолжить работу с файлами, fl - оставить ли предыдущий файл или нет
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
        while (!feof(InputFile)) { // Заполнение всего листа input_data
            example_input_data example_list;
            fill_example(&example_list, InputFile);
            pushback(&head, example_list);
        }
        fclose(InputFile);
        input_data *inListGo = head;
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
        head_out = malloc(sizeof(output_data));
        output_data *outListGo = head_out;
        do // Через do чтобы калькулятор выполнился хотя бы 1 раз
        {
            if (repeat) {
                inListGo = inListGo->next;
                outListGo->next = malloc(sizeof(output_data));
                outListGo = outListGo->next;
            }
            switch (inListGo->whatCalculator) {
                case 'a':;
                    double res;
                    switch (inListGo->operation) // Проверяем знак
                    {
                        case '+': // Сумма
                            res = inListGo->firstNum[0] + inListGo->secondNum[0];
                            outListGo->result = malloc(
                                    (counter((int) inListGo->firstNum[0]) + counter((int) inListGo->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char)); // Выделение памяти как и в след. вариантах
                            sprintf(outListGo->result, "%lf + %lf = %lf", inListGo->firstNum[0], inListGo->secondNum[0],
                                    res); // Вывод суммы
                            break;
                        case '-': // Разность
                            res = inListGo->firstNum[0] - inListGo->secondNum[0];
                            outListGo->result = malloc(
                                    (counter((int) inListGo->firstNum[0]) + counter((int) inListGo->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(outListGo->result, "%lf - %lf = %lf", inListGo->firstNum[0], inListGo->secondNum[0],
                                    res); // Вывод разности
                            break;
                        case '*': // Умножение
                            outListGo->result = malloc(
                                    (counter((int) inListGo->firstNum[0]) + counter((int) inListGo->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(outListGo->result, "%lf * %lf = %lf", inListGo->firstNum[0], inListGo->secondNum[0],
                                    res); // Вывод умножения
                            break;
                        case '/': // Деление
                            if (inListGo->secondNum[0] == 0) {
                                outListGo->result = malloc(23 * sizeof(char));
                                sprintf(outListGo->result, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            res = inListGo->firstNum[0] / inListGo->secondNum[0];
                            outListGo->result = malloc(
                                    (counter((int) inListGo->firstNum[0]) + counter((int) inListGo->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(outListGo->result, "%lf / %lf = %lf", inListGo->firstNum[0], inListGo->secondNum[0],
                                    res); // Вывод деления
                            break;
                        case '\\': // Деление без остатка
                            if (inListGo->secondNum[0] == 0) {
                                outListGo->result = malloc(23 * sizeof(char));
                                sprintf(outListGo->result, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            res = inListGo->firstNum[0] / inListGo->secondNum[0];
                            outListGo->result = malloc(
                                    (counter((int) inListGo->firstNum[0]) + counter((int) inListGo->secondNum[0]) +
                                     counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(outListGo->result, "%lf \\ %lf = %i", inListGo->firstNum[0], inListGo->secondNum[0],
                                    (int) res); // Вывод деления без остатка
                            break;
                        case '#': // Остаток от деления
                            if (inListGo->secondNum[0] == 0) {
                                outListGo->result = malloc(23 * sizeof(char));
                                sprintf(outListGo->result, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            res = inListGo->firstNum[0] / inListGo->secondNum[0];
                            res = inListGo->firstNum[0] - ((int) res * inListGo->secondNum[0]);
                            outListGo->result = malloc(
                                    (counter((int) inListGo->firstNum[0]) + counter((int) inListGo->secondNum[0]) +
                                     counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                    sizeof(char));
                            sprintf(outListGo->result, "%lf # %lf = %lf", inListGo->firstNum[0], inListGo->secondNum[0],
                                    res); // Вывод остаток от деления
                            break;
                        case '!': // Факториал, точка с запятой нужна, чтобы не было ошибки из-за инициализации fuct
                            if ((inListGo->firstNum[0] - (int) inListGo->firstNum[0]) ==
                                0) // Проверка на то, что это целое число
                            {
                                unsigned long int fuct = inListGo->firstNum[0]; // Результат вычисления факториала
                                if ((int) inListGo->firstNum[0] >
                                    0) // Проверка на правильность введения числа, а также представление double, как int
                                {
                                    for (int i = 1; i < (int) inListGo->firstNum[0]; i++) {
                                        fuct = fuct * i; // Процесс вычисления факториала
                                    }
                                    outListGo->result = malloc(
                                            (counter((int) inListGo->firstNum[0]) +
                                             counter((int) res) + 6) *
                                            sizeof(char));
                                    sprintf(outListGo->result, "%i ! = %lu", (int) inListGo->firstNum[0],
                                            fuct); // Вывод факториала
                                } else if (inListGo->firstNum[0] ==
                                           0) { // Факториал от 0 равен 1
                                    outListGo->result = malloc(
                                            (counter((int) inListGo->firstNum[0]) +
                                             7) *
                                            sizeof(char));
                                    sprintf(outListGo->result, "%i ! = 1",
                                            (int) inListGo->firstNum[0]); // Аналогично вывод
                                } else {
                                    outListGo->result = malloc(29 * sizeof(char));
                                    sprintf(outListGo->result,
                                            "Write down a positive number"); // Если пользователь ввел неправильно пишем Write down a positive number
                                    break;
                                }
                            } else // Если число не целое
                            {
                                outListGo->result = malloc(17 * sizeof(char));
                                sprintf(outListGo->result, "Write an integer"); // Комментарий говорит сам за себя
                                break;                                          // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            break;
                        case '^': // Степень
                            if ((inListGo->secondNum[0] - (int) inListGo->secondNum[0]) ==
                                0) // Проверка на то, что степень - целое число
                            {
                                res = inListGo->firstNum[0];
                                if ((int) inListGo->secondNum[0] >
                                    0) // Проверка знака степени, а также из double в int, поэтому возводить только в целую степень
                                {
                                    for (int j = 0; j < (int) inListGo->secondNum[0] - 1; j++) {
                                        res = res * inListGo->firstNum[0]; // Процесс вычисления степени числа
                                    }
                                    outListGo->result = malloc(
                                            (counter((int) inListGo->firstNum[0]) +
                                             counter((int) inListGo->secondNum[0]) +
                                             counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                            sizeof(char));
                                    sprintf(outListGo->result, "%lf ^ %i = %lf", inListGo->firstNum[0],
                                            (int) inListGo->secondNum[0],
                                            res); // Вывод операции степени
                                } else if ((int) inListGo->secondNum[0] < 0) // Исход с отрицательной степенью
                                {
                                    double c, d; // Добавляем числа, чтобы представить a как 1/a и возвести в положительную степень
                                    res = 1 / inListGo->firstNum[0];
                                    c = 1 / inListGo->firstNum[0];
                                    d = -inListGo->secondNum[0];
                                    for (int j = 0; j < (int) d - 1; j++) {
                                        res = res * c; // Процесс вычисления степени числа
                                    }
                                    outListGo->result = malloc(
                                            (counter((int) inListGo->firstNum[0]) +
                                             counter((int) inListGo->secondNum[0]) +
                                             counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                            sizeof(char));
                                    sprintf(outListGo->result, "%lf ^ %i = %lf", inListGo->firstNum[0],
                                            (int) inListGo->secondNum[0],
                                            res); // Вывод операции отрицательной степени
                                } else {
                                    outListGo->result = malloc(
                                            (counter((int) inListGo->firstNum[0]) +
                                             counter((int) inListGo->secondNum[0]) + 7 + 2 * 3 + 1) *
                                            sizeof(char));
                                    sprintf(outListGo->result, "%lf ^ %i = 1", inListGo->firstNum[0],
                                            (int) inListGo->secondNum[0]); // Если степень равна 0, то число в этой степени равно 1
                                }
                            } else // Если число не целое
                            {
                                outListGo->result = malloc(28 * sizeof(char));
                                sprintf(outListGo->result,
                                        "Write an integer to a power"); // Комментарий говорит сам за себя
                                break;                                  // Чтобы вернуться в начало цикла без "Continue?"
                            }
                            break;
                        default:
                            outListGo->result = malloc(27 * sizeof(char));
                            sprintf(outListGo->result,
                                    "I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    break;
                case 'v':
                    while (inListGo->sizeVector < 1) // Размер вектора не может быть отрицательным или равным нулю
                    {
                        outListGo->result = malloc(24 * sizeof(char));
                        sprintf(outListGo->result, "The minimum value is 1!");
                        break;
                    }
                    double *resvec; // Результат операции
                    resvec = malloc(inListGo->sizeVector * sizeof(double));
                    int sizeLine = 1;
                    switch (inListGo->operation) {
                        case '+': // Сумма векторов
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                resvec[i] = inListGo->firstNum[i] + inListGo->secondNum[i];
                                sizeLine +=
                                        counter((int) inListGo->firstNum[i]) + counter((int) inListGo->secondNum[i]) +
                                        counter((int) resvec[i]) + 7 * 3;
                            }
                            sizeLine += (2 + (inListGo->sizeVector - 1) * 2) * 3 + 2 * 3 + 1;
                            outListGo->result = malloc(sizeLine * sizeof(char));
                            sprintf(outListGo->result, "(");
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, inListGo->firstNum[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s) ", outListGo->result);
                                }
                            }
                            sprintf(outListGo->result, "%s+ (", outListGo->result);
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, inListGo->secondNum[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s) ", outListGo->result);
                                }
                            }
                            sprintf(outListGo->result, "%s= (", outListGo->result);
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, resvec[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s)", outListGo->result);
                                }
                            }
                            break;
                        case '-': // Разность векторов
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                resvec[i] = inListGo->firstNum[i] - inListGo->secondNum[i];
                                sizeLine +=
                                        counter((int) inListGo->firstNum[i]) + counter((int) inListGo->secondNum[i]) +
                                        counter((int) resvec[i]) + 7 * 3;
                            }
                            sizeLine += (2 + (inListGo->sizeVector - 1) * 2) * 3 + 2 * 3 + 1;
                            outListGo->result = malloc(sizeLine * sizeof(char));
                            sprintf(outListGo->result, "(");
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, inListGo->firstNum[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s) ", outListGo->result);
                                }
                            }
                            sprintf(outListGo->result, "%s- (", outListGo->result);
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, inListGo->secondNum[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s) ", outListGo->result);
                                }
                            }
                            sprintf(outListGo->result, "%s= (", outListGo->result);
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, resvec[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s)", outListGo->result);
                                }
                            }
                            break;
                        case 'c':; // Скалярное произведение
                            double resvecc = 0.0;
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                resvecc += inListGo->firstNum[i] * inListGo->secondNum[i];
                                sizeLine +=
                                        counter((int) inListGo->firstNum[i]) + counter((int) inListGo->secondNum[i]) +
                                        7 * 2;
                            }
                            sizeLine +=
                                    (2 + (inListGo->sizeVector - 1) * 2) * 2 + 2 * 3 + 2 + counter((int) resvecc) + 7;
                            outListGo->result = malloc(sizeLine * sizeof(char));
                            sprintf(outListGo->result, "((");
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, inListGo->firstNum[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s) ", outListGo->result);
                                }
                            }
                            sprintf(outListGo->result, "%s* (", outListGo->result);
                            for (int i = 0; i < inListGo->sizeVector; i++) {
                                sprintf(outListGo->result, "%s%lf", outListGo->result, inListGo->secondNum[i]);
                                if (i < inListGo->sizeVector - 1) {
                                    sprintf(outListGo->result, "%s, ", outListGo->result);
                                } else {
                                    sprintf(outListGo->result, "%s)) ", outListGo->result);
                                }
                            }
                            sprintf(outListGo->result, "%s= %lf", outListGo->result, resvecc);
                            break;
                        default:
                            outListGo->result = malloc(27 * sizeof(char));
                            sprintf(outListGo->result,
                                    "I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    break;
                default:
                    outListGo->result = malloc(29 * sizeof(char));
                    sprintf(outListGo->result, "Required to write \"a\" or \"v\"");
            }
            while ((inListGo->con != 'y') && (inListGo->con != 'n')) // Проверка на корректно введенное y или n
            {
                outListGo->result = malloc(36 * sizeof(char));
                sprintf(outListGo->result, "Invalid character, write \"y\" or \"n\"");
            }
            if (inListGo->con == 'y') {
                repeat = 1;
            } else {
                repeat = 0;
            }
        } while (inListGo->con ==
                 'y');     // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
        deleteListI(head); // Очищаем память
        outListGo->next = NULL;
        writeListIntoFile(head_out, OutputFile);
        deleteListO(head_out); // Очищаем память
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
