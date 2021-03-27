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
    FILE *Input, *Output;
    int NewWriteFile = 0, NewReadFile = 0;        // NewWriteFile/NewReadFile - Чтобы не выводил блок, который делает спрос о продолжении файла
    char input[255], output[255];                 // Название файла ввода или вывода
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
                fclose(Input); // Закрываем старый файл для открытия нового
            }
        }
        if (!NewReadFile && fl == 'n') // Открытие нового файла
        {

            NewReadFile = 1;
            printf("File to read: ");
            scanf(" %s", &input);
            Input = fopen(input, "r");
            while (Input == NULL || !feof(input)) // Проверяем целлосность данных
            {
                if (!feof(Input))
                    printf("The file is empty\n");
                else
                    printf("Incorrect file name\n");
                scanf(" %s", &input);
                Input = fopen(input, "r");
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
                fclose(Output); // Закрываем старый файл для открытия нового
            }
        }
        if (!NewWriteFile && fl == 'n') // Открытие нового файла
        {
            NewWriteFile = 1;
            printf("File to write: ");
            scanf(" %s", &output);
            Output = fopen(output, "w");
        }
        do // Через do чтобы калькулятор выполнился хотя бы 1 раз
        {
            //printf("What will you work with?(algebra - \"a\", vector - \"v\"): "); // Выбор метода вычисления
            fscanf(Input, " %c", &choice);
            switch (choice)
            {
            case 'a':
                if ((operations == ' ') || (operations != 'a')) // Чтобы не повторял какие есть операции в том же методе
                {
                    printf("All operation: \"+\" - addition, \"-\" - subtraction, \"*\" - multiplication, \"/\" - division, \"\\\" - division without remainder, \"#\" - modulo, \"!\" - factorial, \"^\" - exponentiation.\n"); // Показывает все доступные операции
                    operations = 'a';
                }
                double a, b, res; //a - 1 число, b - 2 число, res - результат
                do
                {
                    printf("Write expression(example: x + y): ");
                    fscanf(Input, "%lf %c", &a, &operation); // Получаем от пользователя данные
                    if (operation != '!')                    // Если будет факториал, то нам не нужно второе число, а в остальрных нужно
                    {
                        fscanf(Input, "%lf", &b);
                    }
                    switch (operation) // Проверяем знак
                    {
                    case '+': // Сумма
                        res = a + b;
                        fprintf(Output, "%lf + %lf = %lf", a, b, res); // Вывод суммы
                        break;
                    case '-': // Разность
                        res = a - b;
                        fprintf(Output, "%lf - %lf = %lf", a, b, res); // Вывод разности
                        break;
                    case '*': // Умножение
                        res = a * b;
                        fprintf(Output, "%lf * %lf = %lf", a, b, res); // Вывод умножения
                        break;
                    case '/': // Деление
                        if (b == 0)
                        {
                            printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
                            continue;                           // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        res = a / b;
                        fprintf(Output, "%lf / %lf = %lf", a, b, res); // Вывод деления
                        break;
                    case '\\': // Деление без остатка
                        if (b == 0)
                        {
                            printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
                            continue;                           // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        res = a / b;
                        fprintf(Output, "%lf \\ %lf = %i", a, b, (int)res); // Вывод деления без остатка
                        break;
                    case '#': // Остаток от деления
                        if (b == 0)
                        {
                            printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
                            continue;                           // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        res = a / b;
                        fprintf(Output, "%lf # %lf = %lf", a, b, a - ((int)res * b)); // Вывод остаток от деления
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
                                fprintf(Output, "%i ! = %lu", (int)a, fuct); // Вывод факториала
                            }
                            else if (a == 0)                         // Факториал от 0 равен 1
                                fprintf(Output, "%i ! = 1", (int)a); // Аналогично вывод
                            else
                            {
                                printf("Write down a positive number\n"); // Если пользователь ввел неправильно пишем Write down a positive number
                                continue;
                            }
                        }
                        else // Если число не целое
                        {
                            printf("Write an integer\n"); // Комментарий говорит сам за себя
                            continue;                     // Чтобы вернуться в начало цикла без "Continue?"
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
                                fprintf(Output, "%lf ^ %i = %lf", a, (int)b, res); // Вывод операции степени
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
                                fprintf(Output, "%lf ^ %i = %lf", a, (int)b, res); // Вывод операции отрицательной степени
                            }
                            else
                                fprintf(Output, "%lf ^ %i = 1", a, (int)b); // Если степень равна 0, то число в этой степени равно 1
                        }
                        else // Если число не целое
                        {
                            printf("Write an integer to a power\n"); // Комментарий говорит сам за себя
                            continue;                                // Чтобы вернуться в начало цикла без "Continue?"
                        }
                        break;
                    default:
                        printf("I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    fprintf(Output, "\n");
                    printf("\nContinue this method?(y/n)\n"); // Вывод строки, с вопросом, продолжить ли вычисление
                    fscanf(Input, " %c", &con);               // Читает символ, если y - продолжить, если n - закончить
                    while ((con != 'y') && (con != 'n'))      // Проверка на корректно введенное y или n
                    {
                        printf("invalid character, write \"y\" or \"n\"\n");
                        fscanf(Input, " %c", &con);
                    }
                } while (con == 'y'); // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
                break;
            case 'v':

                if ((operations == ' ') || (operations != 'v')) // Чтобы не повторял какие есть операции в том же методе
                {
                    printf("All operation: \"+\" - addition, \"-\" - subtraction, \"c\" - scalar product.\n"); // Показывает все доступные операции
                    operations = 'v';
                }
                int size;
                do
                {
                    printf("Write vector`s size (The minimum value is 1): "); // Задаем размер вектора
                    fscanf(Input, "%d", &size);
                    while (size < 1) // Размер вектора не может быть отрицательным или равным нулю
                    {
                        printf("The minimum value is 1!\nSize: ");
                        fscanf(Input, "%d", &size);
                    }
                    printf("Write expression(example: x1 y1 + x2 y2): "); // Ожидаем написания 2 векторов
                    double *vector1 = malloc(size * sizeof(double));      // Первый вектор
                    for (int i = 0; i < size; i++)
                    {
                        fscanf(Input, "%lf", &vector1[i]);
                    }
                    fscanf(Input, " %c", &operation);                // Операция
                    double *vector2 = malloc(size * sizeof(double)); // Второй вектор
                    for (int i = 0; i < size; i++)
                    {
                        fscanf(Input, "%lf", &vector2[i]);
                    }
                    double resvec; // Результат операции
                    switch (operation)
                    {
                    case '+': // Сумма векторов
                        fprintf(Output, "(");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(Output, "%lf", vector1[i]);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ") ");
                        }
                        fprintf(Output, "+ (");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(Output, "%lf", vector2[i]);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ") ");
                        }
                        fprintf(Output, "= (");
                        for (int i = 0; i < size; i++)
                        {
                            resvec = vector1[i] + vector2[i];
                            fprintf(Output, "%lf", resvec);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ")");
                        }
                        break;
                    case '-': // Разность векторов
                        fprintf(Output, "(");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(Output, "%lf", vector1[i]);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ") ");
                        }
                        fprintf(Output, "- (");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(Output, "%lf", vector2[i]);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ") ");
                        }
                        fprintf(Output, "= (");
                        for (int i = 0; i < size; i++)
                        {
                            resvec = vector1[i] - vector2[i];
                            fprintf(Output, "%lf", resvec);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ")");
                        }
                        break;
                    case 'c': // Скалярное произведение
                        fprintf(Output, "((");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(Output, "%lf", vector1[i]);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ") ");
                        }
                        fprintf(Output, "* (");
                        for (int i = 0; i < size; i++)
                        {
                            fprintf(Output, "%lf", vector2[i]);
                            if (i < size - 1)
                                fprintf(Output, ", ");
                            else
                                fprintf(Output, ")) ");
                        }
                        fprintf(Output, "= ");
                        resvec = 0.0;
                        for (int i = 0; i < size; i++)
                            resvec += vector1[i] * vector2[i];
                        fprintf(Output, "%lf", resvec);
                        break;
                    default:
                        printf("I dont know this operation"); // Если операция не известна, выведет эту строку
                    }
                    free(vector1); // Очищаем память
                    free(vector2);
                    fprintf(Output, "\n");
                    printf("\nContinue this method?(y/n)\n"); // Вывод строки, с вопросом, продолжить ли вычисление
                    fscanf(Input, " %c", &con);               // Читает символ, если y - продолжить, если n - закончить
                    while ((con != 'y') && (con != 'n'))      // Проверка на корректно введенное y или n
                    {
                        printf("invalid character, write \"y\" or \"n\"\n");
                        fscanf(Input, " %c", &con);
                    }
                } while (con == 'y'); // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
                break;
            default:
                printf("Required to write \"a\" or \"v\"");
            }
            printf("Continue?(y/n)\n");          // Вывод строки, с вопросом, продолжить ли вычисление
            fscanf(Input, " %c", &con);          // Читает символ, если y - продолжить, если n - закончить
            while ((con != 'y') && (con != 'n')) // Проверка на корректно введенное y или n
            {
                printf("invalid character, write \"y\" or \"n\"\n");
                fscanf(Input, " %c", &con);
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
    fclose(Input); // Закрываем под конец файлы
    fclose(Output);
    return 0;
}
