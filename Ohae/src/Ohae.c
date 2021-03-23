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
    FILE *input, *output;
    char choice, operation, con; // choice - выбор между методом вычисления, operation - сам знак операции, con - продолжить вычисления или нет
    char operations = ' ';       // Чтобы выводил только нужные операции в определнном методе вычисления
    do                           // Через do чтобы калькулятор выполнился хотя бы 1 раз
    {
        printf("What will you work with?(algebra - \"a\", vector - \"v\"): "); // Выбор метода вычисления
        scanf(" %c", &choice);
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
                scanf("%lf %c", &a, &operation); // Получаем от пользователя данные
                if (operation != '!')            // Если будет факториал, то нам не нужно второе число, а в остальрных нужно
                    scanf("%lf", &b);
                switch (operation) // Проверяем знак
                {
                case '+': // Сумма
                    res = a + b;
                    printf("%lf + %lf = %lf", a, b, res); // Вывод суммы
                    break;
                case '-': // Разность
                    res = a - b;
                    printf("%lf - %lf = %lf", a, b, res); // Вывод разности
                    break;
                case '*': // Умножение
                    res = a * b;
                    printf("%lf * %lf = %lf", a, b, res); // Вывод умножения
                    break;
                case '/': // Деление
                    if (b == 0)
                    {
                        printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
                        continue;                           // Чтобы вернуться в начало цикла без "Continue?"
                    }
                    res = a / b;
                    printf("%lf / %lf = %lf", a, b, res); // Вывод деления
                    break;
                case '\\': // Деление без остатка
                    if (b == 0)
                    {
                        printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
                        continue;                           // Чтобы вернуться в начало цикла без "Continue?"
                    }
                    res = a / b;
                    printf("%lf \\ %lf = %i", a, b, (int)res); // Вывод деления без остатка
                    break;
                case '#': // Остаток от деления
                    if (b == 0)
                    {
                        printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
                        continue;                           // Чтобы вернуться в начало цикла без "Continue?"
                    }
                    res = a / b;
                    printf("%lf # %lf = %lf", a, b, a - ((int)res * b)); // Вывод остаток от деления
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
                            printf("%i ! = %lu", (int)a, fuct); // Вывод факториала
                        }
                        else if (a == 0)                // Факториал от 0 равен 1
                            printf("%i ! = 1", (int)a); // Аналогично вывод
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
                            printf("%lf ^ %i = %lf", a, (int)b, res); // Вывод операции степени
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
                            printf("%lf ^ %i = %lf", a, (int)b, res); // Вывод операции отрицательной степени
                        }
                        else
                            printf("%lf ^ %i = 1", a, (int)b); // Если степень равна 0, то число в этой степени равно 1
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
                printf("\nContinue this method?(y/n)\n"); // Вывод строки, с вопросом, продолжить ли вычисление
                scanf(" %c", &con);                       // Читает символ, если y - продолжить, если n - закончить
                while ((con != 'y') && (con != 'n'))      // Проверка на корректно введенное y или n
                {
                    printf("invalid character, write \"y\" or \"n\"\n");
                    scanf(" %c", &con);
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
                scanf("%d", &size);
                while (size < 1) // Размер вектора не может быть отрицательным или равным нулю
                {
                    printf("The minimum value is 1!\nSize: ");
                    scanf("%d", &size);
                }
                printf("Write expression(example: x1 y1 + x2 y2): "); // Ожидаем написания 2 векторов
                double *vector1 = malloc(size * sizeof(double)); // Первый вектор
                for (int i = 0; i < size; i++)
                    scanf("%lf", &vector1[i]);
                scanf(" %c", &operation); // Операция
                double *vector2 = malloc(size * sizeof(double)); // Второй вектор
                for (int i = 0; i < size; i++)
                    scanf("%lf", &vector2[i]);
                double resvec; // Результат операции
                switch (operation)
                {
                case '+': // Сумма векторов
                    printf("(");
                    for (int i = 0; i < size; i++)
                    {
                        printf("%lf", vector1[i]);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(") ");
                    }
                    printf("+ (");
                    for (int i = 0; i < size; i++)
                    {
                        printf("%lf", vector2[i]);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(") ");
                    }
                    printf("= (");
                    for (int i = 0; i < size; i++)
                    {
                        resvec = vector1[i] + vector2[i];
                        printf("%lf", resvec);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(")");
                    }
                    break;
                case '-': // Разность векторов
                    printf("(");
                    for (int i = 0; i < size; i++)
                    {
                        printf("%lf", vector1[i]);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(") ");
                    }
                    printf("- (");
                    for (int i = 0; i < size; i++)
                    {
                        printf("%lf", vector2[i]);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(") ");
                    }
                    printf("= (");
                    for (int i = 0; i < size; i++)
                    {
                        resvec = vector1[i] - vector2[i];
                        printf("%lf", resvec);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(")");
                    }
                    break;
                case 'c': // Скалярное произведение
                    printf("((");
                    for (int i = 0; i < size; i++)
                    {
                        printf("%lf", vector1[i]);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(") ");
                    }
                    printf("* (");
                    for (int i = 0; i < size; i++)
                    {
                        printf("%lf", vector2[i]);
                        if (i < size - 1)
                            printf(", ");
                        else
                            printf(")) ");
                    }
                    printf("= ");
                    resvec = 0.0;
                    for (int i = 0; i < size; i++)
                        resvec += vector1[i] * vector2[i];
                    printf("%lf", resvec);
                    break;
                default:
                    printf("I dont know this operation"); // Если операция не известна, выведет эту строку
                }
                free(vector1); // очищаем память
                free(vector2);
                printf("\nContinue this method?(y/n)\n"); // Вывод строки, с вопросом, продолжить ли вычисление
                scanf(" %c", &con);                       // Читает символ, если y - продолжить, если n - закончить
                while ((con != 'y') && (con != 'n'))      // Проверка на корректно введенное y или n
                {
                    printf("invalid character, write \"y\" or \"n\"\n");
                    scanf(" %c", &con);
                }
            } while (con == 'y'); // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
            break;
        default:
            printf("Required to write \"a\" or \"v\"");
        }
        printf("Continue?(y/n)\n");          // Вывод строки, с вопросом, продолжить ли вычисление
        scanf(" %c", &con);                  // Читает символ, если y - продолжить, если n - закончить
        while ((con != 'y') && (con != 'n')) // Проверка на корректно введенное y или n
        {
            printf("invalid character, write \"y\" or \"n\"\n");
            scanf(" %c", &con);
        }
    } while (con == 'y'); // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
    return 0;
}
