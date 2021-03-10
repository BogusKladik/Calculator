/*
 ============================================================================
 Name        : Ohae.c
 Author      : Vladislav Bogushov
 Version     : 1
 Copyright   : IVT
 Description : calculator
 ============================================================================
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char operation, con;//operation - сам знак операции, con - продолжить вычисления или нет
	double a, b, res;//a - 1 число, b - 2 число, res - результат
	printf("All operation: \"+\" - addition, \"-\" - subtraction, \"*\" - multiplication, \"/\" - division, \"\\\" - division without remainder, \"#\" - modulo, \"!\" - factorial, \"^\" - exponentiation.\n");// Показывает все доступные операции
	do// Через do чтобы калькулятор выполнился хотя бы 1 раз
	{
		printf("Write expression: ");
		scanf("%lf %c", &a, &operation);// Получаем от пользователя данные
		if (operation != '!')// Если будет факториал, то нам не нужно второе число, а в остальрных нужно
			scanf("%lf", &b);
		switch (operation)// Проверяем знак
		{
		case '+':// Сумма
			res = a + b;
			printf("%lf + %lf = %lf", a, b, res); // Вывод суммы
			break;
		case '-': // Разность
			res = a - b;
			printf("%lf - %lf = %lf", a, b, res);// Вывод разности
			break;
		case '*':// Умножение
			res = a * b;
			printf("%lf * %lf = %lf", a, b, res);// Вывод умножения
			break;
		case '/':// Деление
			if (b == 0)
			{
				printf("Cannot be divided by 0\n"); // Комментарий говорит сам за себя
				continue;// Чтобы вернуться в начало цикла без "Continue?"
			}
			res = a / b;
			printf("%lf / %lf = %lf", a, b, res);// Вывод деления
			break;
		case '\\':// Деление без остатка
			if (b == 0)
			{
				printf("Cannot be divided by 0\n");// Комментарий говорит сам за себя
				continue;// Чтобы вернуться в начало цикла без "Continue?"
			}
			res = a / b;
			printf("%lf \\ %lf = %i", a, b, (int)res);// Вывод деления без остатка
			break;
		case '#':// Остаток от деления
			if (b == 0)
			{
				printf("Cannot be divided by 0\n");// Комментарий говорит сам за себя
				continue;// Чтобы вернуться в начало цикла без "Continue?"
			}
			res = a / b;
			printf("%lf # %lf = %lf", a, b, a - ((int)res * b));// Вывод остаток от деления
			break;
		case '!':// Факториал, точка с запятой нужна, чтобы не было ошибки из-за инициализации fuct
			if ((a - (int)a) == 0)// Проверка на то, что это целое число
			{
				unsigned long int fuct = a; // Результат вычисления факториала
				if ((int)a > 0)// Проверка на правильность введения числа, а также представление double, как int
				{
					for (int i = 1; i < (int)a; i++)
					{
						fuct = fuct * i;// Процесс вычисления факториала
					}
					printf("%i ! = %lu", (int)a, fuct);// Вывод факториала
				}
				else if (a == 0) // Факториал от 0 равен 1
					printf("%i ! = 1", (int)a);// Аналогично вывод
				else
					printf("Write down a positive number");// Если пользователь ввел неправильно пишем Write down a positive number
			}
			else// Если число не целое
			{
				printf("Write an integer\n");// Комментарий говорит сам за себя
				continue;// Чтобы вернуться в начало цикла без "Continue?"
			}
			break;
		case '^':// Степень
			if ((b - (int)b) == 0)// Проверка на то, что степень - целое число
			{
				res = a;
				if ((int)b > 0)// Проверка знака степени, а также из double в int, поэтому возводить только в целую степень
				{
					for (int j = 0; j < (int)b - 1; j++)
					{
						res = res * a;// Процесс вычисления степени числа
					}
					printf("%lf ^ %i = %lf", a, (int)b, res);// Вывод операции степени
				}
				else if ((int)b < 0)// Исход с отрицательной степенью
				{

					double c, d;// Добавляем числа, чтобы представить a как 1/a и возвести в положительную степень
					res = 1 / a;
					c = 1 / a;
					d = -b;
					for (int j = 0; j < (int)d - 1; j++)
					{
						res = res * c;// Процесс вычисления степени числа
					}
					printf("%lf ^ %i = %lf", a, (int)b, res);// Вывод операции отрицательной степени
				}
				else
					printf("%lf ^ %i = 1", a, (int)b); // Если степень равна 0, то число в этой степени равно 1
			}
			else// Если число не целое
			{
				printf("Write an integer to a power\n");// Комментарий говорит сам за себя
				continue;// Чтобы вернуться в начало цикла без "Continue?"
			}
			break;
		default:
			printf("I dont know this operation");// Если операция не известна, выведет эту строку
		}
		puts("");// Перевод на новую строку
		printf("Continue?(y/n)\n");// Вывод строки, с вопросом, продолжить ли вычисление
		scanf(" %c", &con);// Читает символ, если y - продолжить, если n - закончить
		while ((con != 'y') && (con !='n'))// Проверка на корректно введенное y или n
		{
			printf("invalid character, write \"y\" or \"n\"\n");
			scanf(" %c", &con);
		}
	} while (con == 'y'); // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
	return 0;
}
