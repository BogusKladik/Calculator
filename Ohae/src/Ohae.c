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

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    FILE *InputFile, *OutputFile;
    int NewWriteFile = 0, NewReadFile = 0;        // NewWriteFile/NewReadFile - Чтобы не выводил блок, который делает спрос о продолжении файла
    char inputc[255], outputc[255];                 // Название файла ввода или вывода
    char choice, operation, con, confl, fl = 'n'; // choice - выбор между методом вычисления, operation - сам знак операции, con - продолжить вычисления или нет, confl - продолжить работу с файлами, fl - оставить ли предыдущий файл или нет
    char operations = ' ';                        // Чтобы выводил только нужные операции в определнном методе вычисления
    do                                            // Цикл для работы с файлами
    {
        if (NewReadFile) // Повторить ли файл чтения
        {
            printf("Repeat the file for reading?(y/n)\n");
            scanf(" %c", &fl);                 // Читает символ, если y - продолжить, если n - закончить
            while ((fl != 'y') && (fl != 'n')) // Проверка на корректно введенное y или n
            {
                printf("invalid character, write \"y\" or \"n\"\n");
                scanf(" %c", &fl);
            }
            NewReadFile = 0;
            if (fl == 'n')
            {
                fclose(InputFile); // Закрываем старый файл для открытия нового
            }
        }
        if (!NewReadFile && fl == 'n') // Открытие нового файла
        {

            NewReadFile = 1;
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
        }
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
            if (fl == 'n')
            {
                fclose(OutputFile); // Закрываем старый файл для открытия нового
            }
        }
        if (!NewWriteFile && fl == 'n') // Открытие нового файла
        {
            NewWriteFile = 1;
            printf("File to write: ");
            scanf(" %s", outputc);
            OutputFile = fopen(outputc, "w");
        }
        do // Через do чтобы калькулятор выполнился хотя бы 1 раз
        {
            //printf("What will you work with?(algebra - \"a\", vector - \"v\"): "); // Выбор метода вычисления
            fscanf(InputFile, " %c", &choice);
            switch (choice)
            {
            case 'a': ;
                double a, b, res; //a - 1 число, b - 2 число, res - результат
                    fscanf(InputFile, "%lf %c", &a, &operation); // Получаем от пользователя данные
                    if (operation != '!')                    // Если будет факториал, то нам не нужно второе число, а в остальрных нужно
                    {
                        fscanf(InputFile, "%lf", &b);
                    }
                    switch (operation) // Проверяем знак
                    {
                    case '+': // Сумма
                        res = a + b;
                        fprintf(OutputFile, "%lf + %lf = %lf", a, b, res); // Вывод суммы
                        break;
                    case '-': // Разность
                        res = a - b;
                        fprintf(OutputFile, "%lf - %lf = %lf", a, b, res); // Вывод разности
                        break;
                    case '*': // Умножение
                        res = a * b;
                        fprintf(OutputFile, "%lf * %lf = %lf", a, b, res); // Вывод умножения
                        break;
                    case '/': // Деление
                        if (b == 0)
                        {
                            fprintf(OutputFile, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                            break;                           // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        res = a / b;
                        fprintf(OutputFile, "%lf / %lf = %lf", a, b, res); // Вывод деления
                        break;
                    case '\\': // Деление без остатка
                        if (b == 0)
                        {
                            fprintf(OutputFile, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                            break;                           // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        res = a / b;
                        fprintf(OutputFile, "%lf \\ %lf = %i", a, b, (int)res); // Вывод деления без остатка
                        break;
                    case '#': // Остаток от деления
                        if (b == 0)
                        {
                            fprintf(OutputFile, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                            break;                           // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        res = a / b;
                        fprintf(OutputFile, "%lf # %lf = %lf", a, b, a - ((int)res * b)); // Вывод остаток от деления
                        break;
                    case '!':                  // Факториал, точка с запятой нужна, чтобы не было ошибки из-за инициализации fuct
                        if ((a - (int)a) == 0) // Проверка на то, что это целое число
                        {
                            unsigned long int fuct = a; // Результат вычисления факториала
                            if ((int)a > 0)             // Проверка на правильность введения числа, а также представление double, как int
                            {
                                for (int i = 1; i < (int)a; i++)
                                {
                                    fuct = fuct * i; // Процесс вычисления факториала
                                }
                                fprintf(OutputFile, "%i ! = %lu", (int)a, fuct); // Вывод факториала
                            }
                            else if (a == 0)                         // Факториал от 0 равен 1
                                fprintf(OutputFile, "%i ! = 1", (int)a); // Аналогично вывод
                            else
                            {
                                fprintf(OutputFile, "Write down a positive number"); // Если пользователь ввел неправильно пишем Write down a positive number
                                break;
                            }
                        }
                        else // Если число не целое
                        {
                            fprintf(OutputFile, "Write an integer"); // Комментарий говорит сам за себя
                            break;                     // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        break;
                    case '^':                  // Степень
                        if ((b - (int)b) == 0) // Проверка на то, что степень - целое число
                        {
                            res = a;
                            if ((int)b > 0) // Проверка знака степени, а также из double в int, поэтому возводить только в целую степень
                            {
                                for (int j = 0; j < (int)b - 1; j++)
                                {
                                    res = res * a; // Процесс вычисления степени числа
                                }
                                fprintf(OutputFile, "%lf ^ %i = %lf", a, (int)b, res); // Вывод операции степени
                            }
                            else if ((int)b < 0) // Исход с отрицательной степенью
                            {

                                double c, d; // Добавляем числа, чтобы представить a как 1/a и возвести в положительную степень
                                res = 1 / a;
                                c = 1 / a;
                                d = -b;
                                for (int j = 0; j < (int)d - 1; j++)
                                {
                                    res = res * c; // Процесс вычисления степени числа
                                }
                                fprintf(OutputFile, "%lf ^ %i = %lf", a, (int)b, res); // Вывод операции отрицательной степени
                            }
                            else
                                fprintf(OutputFile, "%lf ^ %i = 1", a, (int)b); // Если степень равна 0, то число в этой степени равно 1
                        }
                        else // Если число не целое
                        {
                            fprintf(OutputFile, "Write an integer to a power"); // Комментарий говорит сам за себя
                            break;                                // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        break;
                    default:
                        fprintf(OutputFile, "I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    fprintf(OutputFile, "\n");
                break;
            case 'v': ;
                int size;
                    fscanf(InputFile, "%d", &size);
                    while (size < 1) // Размер вектора не может быть отрицательным или равным нулю
                    {
                        fprintf(OutputFile, "The minimum value is 1!\nSize: ");
                        fscanf(InputFile, "%d", &size);
                    }
                    double *vector1 = malloc(size * sizeof(double));      // Первый вектор
                    for (int i = 0; i < size; i++)
                    {
                        fscanf(InputFile, "%lf", &vector1[i]);
                    }
                    fscanf(InputFile, " %c", &operation);                // Операция
                    double *vector2 = malloc(size * sizeof(double)); // Второй вектор
                    for (int i = 0; i < size; i++)
                    {
                        fscanf(InputFile, "%lf", &vector2[i]);
                    }
                    double resvec; // Результат операции
                    switch (operation)
                    {
                    case '+': // Сумма векторов
                        fprintf(OutputFile, "(");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(OutputFile, "%lf", vector1[i]);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ") ");
                        }
                        fprintf(OutputFile, "+ (");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(OutputFile, "%lf", vector2[i]);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ") ");
                        }
                        fprintf(OutputFile, "= (");
                        for (int i = 0; i < size; i++)
                        {
                            resvec = vector1[i] + vector2[i];
                            fprintf(OutputFile, "%lf", resvec);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ")");
                        }
                        break;
                    case '-': // Разность векторов
                        fprintf(OutputFile, "(");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(OutputFile, "%lf", vector1[i]);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ") ");
                        }
                        fprintf(OutputFile, "- (");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(OutputFile, "%lf", vector2[i]);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ") ");
                        }
                        fprintf(OutputFile, "= (");
                        for (int i = 0; i < size; i++)
                        {
                            resvec = vector1[i] - vector2[i];
                            fprintf(OutputFile, "%lf", resvec);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ")");
                        }
                        break;
                    case 'c': // Скалярное произведение
                        fprintf(OutputFile, "((");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(OutputFile, "%lf", vector1[i]);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ") ");
                        }
                        fprintf(OutputFile, "* (");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(OutputFile, "%lf", vector2[i]);
                            if (i < size - 1)
                                fprintf(OutputFile, ", ");
                            else
                                fprintf(OutputFile, ")) ");
                        }
                        fprintf(OutputFile, "= ");
                        resvec = 0.0;
                        for (int i = 0; i < size; i++)
                            resvec += vector1[i] * vector2[i];
                        fprintf(OutputFile, "%lf", resvec);
                        break;
                    default:
                        fprintf(OutputFile, "I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    free(vector1); // Очищаем память
                    free(vector2);
                    fprintf(OutputFile, "\n");
                break;
            default:
                fprintf(OutputFile, "Required to write \"a\" or \"v\"");
            }
            fscanf(InputFile, " %c", &con);          // Читает символ, если y - продолжить, если n - закончить
            while ((con != 'y') && (con != 'n')) // Проверка на корректно введенное y или n
            {
                fprintf(OutputFile, "invalid character, write \"y\" or \"n\"\n");
                fscanf(InputFile, " %c", &con);
            }
        } while (con == 'y');                    // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
        printf("Continue with files?(y/n)\n");   // Вывод строки, с вопросом, продолжить ли вычисление с файлами
        scanf(" %c", &confl);                    // Читает символ, если y - продолжить, если n - закончить
        while ((confl != 'y') && (confl != 'n')) // Проверка на корректно введенное y или n
        {
            printf("invalid character, write \"y\" or \"n\"\n");
            scanf(" %c", &confl);
        }
    } while (confl == 'y');
    fclose(InputFile); // Закрываем под конец файлы
    fclose(OutputFile);
    return 0;
}
