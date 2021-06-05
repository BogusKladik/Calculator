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
#include "libs/queue.h"
#include "libs/stack.h"

links_for_lists link_for_lists;
links_for_queues link_for_queues;
links_for_stacks link_for_stack;

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

const char ALL_OPERATION[] = {'^', '*', '/', '+', '-', '!'}; // Все операции

int priority(char operation)
{ // Приоритет операций (для выполнения обратной полькой нотации)
	switch (operation)
	{
	case '(':
		return 4;
	case ')':
		return 4;
	case '^':
		return 3;
	case '*':
		return 2;
	case '/':
		return 2;
	case '+':
		return 1;
	case '-':
		return 1;
	default:
		return 0;
	}
}

short int isNum(char num)
{ // Проверка на то, что элемент типа char является числом
	int truth = 0;
	char numbersLikeChar[] =
		{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i = 0; i < 10; i++)
	{
		if (num == numbersLikeChar[i])
		{
			truth = 1;
			return truth;
		}
	}
	return truth;
}

short int isOpe(char ope)
{ // Проверка на то, что элемент типа char является операцией
	int truth = 0;
	if (ope == ' ')
	{
		truth = 1;
		return truth;
	}
	for (int i = 0; i < 6; i++)
	{
		if (ope == ALL_OPERATION[i])
		{
			truth = 1;
			return truth;
		}
	}
	return truth;
}

double calculate(double firstNum, double secondNum, char operation)
{ // Калькулятор для чисел
	switch (operation)
	{
	case '!':
		if (firstNum == 0)
		{
			return 1.0;
		}
		if (firstNum < 0)
		{
			return firstNum; // Должен выдавать ошибку, но я убрал это, для более легкой работы далее
		}
		double resultForIntegral = 1.0;
		for (int j = 1; j <= (int)firstNum; j++)
		{
			resultForIntegral *= j;
		}
		return resultForIntegral;
	case '^':
		if (secondNum == 0)
		{
			return 1;
		}
		if (secondNum < 0)
		{
			secondNum = -secondNum;
			firstNum = 1.0 / firstNum;
		}
		double result = 1.0;
		for (int i = 0; i < (int)secondNum; i++)
		{
			result *= firstNum;
		}
		return result;
	case '*':
		return firstNum * secondNum;
	case '/':
		return firstNum / secondNum;
	case '+':
		return firstNum + secondNum;
	case '-':
		return firstNum - secondNum;
	default:
		return firstNum; // Должен выдавать ошибку, но я убрал это, для более легкой работы далее
	}
}

double resultCalculatorWithController()
{ // Забирает с очереди элементы и дает их калькулятору. Потом записывает результат в очередь чисел
	char operationFromList = pop_o(&link_for_stack);
	double secondNumFromList = pop_n(&link_for_stack);
	double firstNumFromList = pop_n(&link_for_stack);
	push_back_n(
		calculate(firstNumFromList, secondNumFromList, operationFromList), &link_for_stack);
	return calculate(firstNumFromList, secondNumFromList, operationFromList);
}

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    link_for_lists.head_in = NULL;
    link_for_lists.current_in = link_for_lists.head_in;
    link_for_lists.head_out = NULL;
    link_for_lists.current_out = link_for_lists.head_out;

    link_for_queues.head_in = NULL;
    link_for_queues.tail_in = NULL;
    link_for_queues.head_out = NULL;
    link_for_queues.tail_out = NULL;

    link_for_stack.head_n = NULL;
    link_for_stack.head_o = NULL;

    FILE *InputFile, *OutputFile;
    int NewWriteFile = 0; // NewWriteFile - Чтобы не выводил блок, который делает спрос о продолжении файла
    char input[255], output[255];   // Название файла ввода или вывода
    char continueCycle, fl = 'n', continueCalculate, whatContainer;             // continueCycle - продолжить работу с файлами, fl - оставить ли предыдущий файл или нет
    do {
    	printf("What calculator you want to use? (with using: l - lists, q - queue, s - stack or any char to output): ");
    	scanf(" %c", &whatContainer);
    	switch(whatContainer){
    	case 'l':
    		do                                // Цикл для работы с файлами
    		    {
    		        printf("File to read: ");
    		        scanf(" %s", input);
    		        InputFile = fopen(input, "r");
    		        while (InputFile == NULL || feof(InputFile)) // Проверяем целлосность данных
    		        {
    		            if (feof(InputFile))
    		                printf("The file is empty\n");
    		            else
    		                printf("Incorrect file name\n");
    		            scanf(" %s", input);
    		            InputFile = fopen(input, "r");
    		        }
    		        while (!feof(InputFile)) { // Заполнение всего листа input_data_for_lists
    		            example_input_data_for_lists example_list;
    		            fill_example_list_in(&example_list, InputFile);
    		            push_back_list_in(example_list, &link_for_lists);
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
    		                OutputFile = fopen(output, "a");
    		            }
    		        }
    		        if (!NewWriteFile && fl == 'n') // Открытие нового файла
    		        {
    		            NewWriteFile = 1;
    		            printf("File to write: ");
    		            scanf(" %s", output);
    		            OutputFile = fopen(output, "w");
    		        }
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
    		            push_back_list_out(lineExpression, &link_for_lists);
    		            continueCalculate = link_for_lists.current_in->con;
    		            pop_list_in(&link_for_lists);
    		        } while (continueCalculate ==
    		                 'y');     // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
    		        deleteListIn(&link_for_lists); // Очищаем память
    		        writeListIntoFile(OutputFile, &link_for_lists);
    		        deleteListOut(&link_for_lists); // Очищаем память
    		        fclose(OutputFile);
    		        printf("Continue with files in this container?(y/n)\n");   // Вывод строки, с вопросом, продолжить ли вычисление с файлами
    		        scanf(" %c", &continueCycle);                    // Читает символ, если y - продолжить, если n - закончить
    		        while ((continueCycle != 'y') && (continueCycle != 'n')) // Проверка на корректно введенное y или n
    		        {
    		            printf("Invalid character, write \"y\" or \"n\"\n");
    		            scanf(" %c", &continueCycle);
    		        }
    		    } while (continueCycle == 'y');
    		break;
    	case 'q':
    		do{// Цикл для работы с файлами
            printf("File to read: ");
            scanf(" %s", input);
            InputFile = fopen(input, "r");
            while (InputFile == NULL || feof(InputFile)) // Проверяем целлосность данных
            {
                if (feof(InputFile))
                    printf("The file is empty\n");
                else
                    printf("Incorrect file name\n");
                scanf(" %s", input);
                InputFile = fopen(input, "r");
            }
            while (!feof(InputFile)) { // Заполнение всего листа input_data_for_queues
                example_input_data_for_queues example_queue;
                fill_example_queue_in(&example_queue, InputFile);
                push_back_queue_in(example_queue, &link_for_queues);
            }
            fclose(InputFile);
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
                    OutputFile = fopen(output, "a");
                }
            }
            if (!NewWriteFile && fl == 'n') // Открытие нового файла
            {
                NewWriteFile = 1;
                printf("File to write: ");
                scanf(" %s", output);
                OutputFile = fopen(output, "w");
            }
            // head_out = malloc(sizeof(output_data_for_queues));
            // output_data_for_queues *outqueueGo = head_out;
            do // Через do чтобы калькулятор выполнился хотя бы 1 раз
            {
                char *lineExpression;
                switch (link_for_queues.head_in->whatCalculator) {
                    case 'a':;
                        double res;
                        switch (link_for_queues.head_in->operation) // Проверяем знак
                        {
                            case '+': // Сумма
                                res = link_for_queues.head_in->firstNum[0] + link_for_queues.head_in->secondNum[0];
                                lineExpression = malloc(
                                        (counter((int) link_for_queues.head_in->firstNum[0]) + counter((int) link_for_queues.head_in->secondNum[0]) +
                                         counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                        sizeof(char)); // Выделение памяти как и в след. вариантах
                                sprintf(lineExpression, "%lf + %lf = %lf", link_for_queues.head_in->firstNum[0], link_for_queues.head_in->secondNum[0],
                                        res); // Вывод суммы
                                break;
                            case '-': // Разность
                                res = link_for_queues.head_in->firstNum[0] - link_for_queues.head_in->secondNum[0];
                                lineExpression = malloc(
                                        (counter((int) link_for_queues.head_in->firstNum[0]) + counter((int) link_for_queues.head_in->secondNum[0]) +
                                         counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                        sizeof(char));
                                sprintf(lineExpression, "%lf - %lf = %lf", link_for_queues.head_in->firstNum[0], link_for_queues.head_in->secondNum[0],
                                        res); // Вывод разности
                                break;
                            case '*': // Умножение
                                lineExpression = malloc(
                                        (counter((int) link_for_queues.head_in->firstNum[0]) + counter((int) link_for_queues.head_in->secondNum[0]) +
                                         counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                        sizeof(char));
                                sprintf(lineExpression, "%lf * %lf = %lf", link_for_queues.head_in->firstNum[0], link_for_queues.head_in->secondNum[0],
                                        res); // Вывод умножения
                                break;
                            case '/': // Деление
                                if (link_for_queues.head_in->secondNum[0] == 0) {
                                    lineExpression = malloc(23 * sizeof(char));
                                    sprintf(lineExpression, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                    break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                                }
                                res = link_for_queues.head_in->firstNum[0] / link_for_queues.head_in->secondNum[0];
                                lineExpression = malloc(
                                        (counter((int) link_for_queues.head_in->firstNum[0]) + counter((int) link_for_queues.head_in->secondNum[0]) +
                                         counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                        sizeof(char));
                                sprintf(lineExpression, "%lf / %lf = %lf", link_for_queues.head_in->firstNum[0], link_for_queues.head_in->secondNum[0],
                                        res); // Вывод деления
                                break;
                            case '\\': // Деление без остатка
                                if (link_for_queues.head_in->secondNum[0] == 0) {
                                    lineExpression = malloc(23 * sizeof(char));
                                    sprintf(lineExpression, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                    break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                                }
                                res = link_for_queues.head_in->firstNum[0] / link_for_queues.head_in->secondNum[0];
                                lineExpression = malloc(
                                        (counter((int) link_for_queues.head_in->firstNum[0]) + counter((int) link_for_queues.head_in->secondNum[0]) +
                                         counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                        sizeof(char));
                                sprintf(lineExpression, "%lf \\ %lf = %i", link_for_queues.head_in->firstNum[0], link_for_queues.head_in->secondNum[0],
                                        (int) res); // Вывод деления без остатка
                                break;
                            case '#': // Остаток от деления
                                if (link_for_queues.head_in->secondNum[0] == 0) {
                                    lineExpression = malloc(23 * sizeof(char));
                                    sprintf(lineExpression, "Cannot be divided by 0"); // Комментарий говорит сам за себя
                                    break;                                                // Чтобы вернуться в начало цикла без "Continue?"
                                }
                                res = link_for_queues.head_in->firstNum[0] / link_for_queues.head_in->secondNum[0];
                                res = link_for_queues.head_in->firstNum[0] - ((int) res * link_for_queues.head_in->secondNum[0]);
                                lineExpression = malloc(
                                        (counter((int) link_for_queues.head_in->firstNum[0]) + counter((int) link_for_queues.head_in->secondNum[0]) +
                                         counter((int) res) + 3 * 7 + 2 * 3 + 1) *
                                        sizeof(char));
                                sprintf(lineExpression, "%lf # %lf = %lf", link_for_queues.head_in->firstNum[0], link_for_queues.head_in->secondNum[0],
                                        res); // Вывод остаток от деления
                                break;
                            case '!': // Факториал, точка с запятой нужна, чтобы не было ошибки из-за инициализации fuct
                                if ((link_for_queues.head_in->firstNum[0] - (int) link_for_queues.head_in->firstNum[0]) ==
                                    0) // Проверка на то, что это целое число
                                {
                                    unsigned long int fuct = link_for_queues.head_in->firstNum[0]; // Результат вычисления факториала
                                    if ((int) link_for_queues.head_in->firstNum[0] >
                                        0) // Проверка на правильность введения числа, а также представление double, как int
                                    {
                                        for (int i = 1; i < (int) link_for_queues.head_in->firstNum[0]; i++) {
                                            fuct = fuct * i; // Процесс вычисления факториала
                                        }
                                        lineExpression = malloc(
                                                (counter((int) link_for_queues.head_in->firstNum[0]) +
                                                 counter((int) res) + 6) *
                                                sizeof(char));
                                        sprintf(lineExpression, "%i ! = %lu", (int) link_for_queues.head_in->firstNum[0],
                                                fuct); // Вывод факториала
                                    } else if (link_for_queues.head_in->firstNum[0] ==
                                               0) { // Факториал от 0 равен 1
                                        lineExpression = malloc(
                                                (counter((int) link_for_queues.head_in->firstNum[0]) +
                                                 7) *
                                                sizeof(char));
                                        sprintf(lineExpression, "%i ! = 1",
                                                (int) link_for_queues.head_in->firstNum[0]); // Аналогично вывод
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
                                if ((link_for_queues.head_in->secondNum[0] - (int) link_for_queues.head_in->secondNum[0]) ==
                                    0) // Проверка на то, что степень - целое число
                                {
                                    res = link_for_queues.head_in->firstNum[0];
                                    if ((int) link_for_queues.head_in->secondNum[0] >
                                        0) // Проверка знака степени, а также из double в int, поэтому возводить только в целую степень
                                    {
                                        for (int j = 0; j < (int) link_for_queues.head_in->secondNum[0] - 1; j++) {
                                            res = res * link_for_queues.head_in->firstNum[0]; // Процесс вычисления степени числа
                                        }
                                        lineExpression = malloc(
                                                (counter((int) link_for_queues.head_in->firstNum[0]) +
                                                 counter((int) link_for_queues.head_in->secondNum[0]) +
                                                 counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                                sizeof(char));
                                        sprintf(lineExpression, "%lf ^ %i = %lf", link_for_queues.head_in->firstNum[0],
                                                (int) link_for_queues.head_in->secondNum[0],
                                                res); // Вывод операции степени
                                    } else if ((int) link_for_queues.head_in->secondNum[0] < 0) // Исход с отрицательной степенью
                                    {
                                        double c, d; // Добавляем числа, чтобы представить a как 1/a и возвести в положительную степень
                                        res = 1 / link_for_queues.head_in->firstNum[0];
                                        c = 1 / link_for_queues.head_in->firstNum[0];
                                        d = -link_for_queues.head_in->secondNum[0];
                                        for (int j = 0; j < (int) d - 1; j++) {
                                            res = res * c; // Процесс вычисления степени числа
                                        }
                                        lineExpression = malloc(
                                                (counter((int) link_for_queues.head_in->firstNum[0]) +
                                                 counter((int) link_for_queues.head_in->secondNum[0]) +
                                                 counter((int) res) + 2 * 7 + 2 * 3 + 1) *
                                                sizeof(char));
                                        sprintf(lineExpression, "%lf ^ %i = %lf", link_for_queues.head_in->firstNum[0],
                                                (int) link_for_queues.head_in->secondNum[0],
                                                res); // Вывод операции отрицательной степени
                                    } else {
                                        lineExpression = malloc(
                                                (counter((int) link_for_queues.head_in->firstNum[0]) +
                                                 counter((int) link_for_queues.head_in->secondNum[0]) + 7 + 2 * 3 + 1) *
                                                sizeof(char));
                                        sprintf(lineExpression, "%lf ^ %i = 1", link_for_queues.head_in->firstNum[0],
                                                (int) link_for_queues.head_in->secondNum[0]); // Если степень равна 0, то число в этой степени равно 1
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
                        while (link_for_queues.head_in->sizeVector < 1) // Размер вектора не может быть отрицательным или равным нулю
                        {
                            lineExpression = malloc(24 * sizeof(char));
                            sprintf(lineExpression, "The minimum value is 1!");
                            break;
                        }
                        double *resvec; // Результат операции
                        resvec = malloc(link_for_queues.head_in->sizeVector * sizeof(double));
                        int sizeLine = 1;
                        switch (link_for_queues.head_in->operation) {
                            case '+': // Сумма векторов
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    resvec[i] = link_for_queues.head_in->firstNum[i] + link_for_queues.head_in->secondNum[i];
                                    sizeLine +=
                                            counter((int) link_for_queues.head_in->firstNum[i]) + counter((int) link_for_queues.head_in->secondNum[i]) +
                                            counter((int) resvec[i]) + 7 * 3;
                                }
                                sizeLine += (2 + (link_for_queues.head_in->sizeVector - 1) * 2) * 3 + 2 * 3 + 1;
                                lineExpression = malloc(sizeLine * sizeof(char));
                                sprintf(lineExpression, "(");
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, link_for_queues.head_in->firstNum[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s) ", lineExpression);
                                    }
                                }
                                sprintf(lineExpression, "%s+ (", lineExpression);
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, link_for_queues.head_in->secondNum[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s) ", lineExpression);
                                    }
                                }
                                sprintf(lineExpression, "%s= (", lineExpression);
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, resvec[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s)", lineExpression);
                                    }
                                }
                                break;
                            case '-': // Разность векторов
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    resvec[i] = link_for_queues.head_in->firstNum[i] - link_for_queues.head_in->secondNum[i];
                                    sizeLine +=
                                            counter((int) link_for_queues.head_in->firstNum[i]) + counter((int) link_for_queues.head_in->secondNum[i]) +
                                            counter((int) resvec[i]) + 7 * 3;
                                }
                                sizeLine += (2 + (link_for_queues.head_in->sizeVector - 1) * 2) * 3 + 2 * 3 + 1;
                                lineExpression = malloc(sizeLine * sizeof(char));
                                sprintf(lineExpression, "(");
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, link_for_queues.head_in->firstNum[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s) ", lineExpression);
                                    }
                                }
                                sprintf(lineExpression, "%s- (", lineExpression);
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, link_for_queues.head_in->secondNum[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s) ", lineExpression);
                                    }
                                }
                                sprintf(lineExpression, "%s= (", lineExpression);
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, resvec[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s)", lineExpression);
                                    }
                                }
                                break;
                            case 'c':; // Скалярное произведение
                                double resvecc = 0.0;
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    resvecc += link_for_queues.head_in->firstNum[i] * link_for_queues.head_in->secondNum[i];
                                    sizeLine +=
                                            counter((int) link_for_queues.head_in->firstNum[i]) + counter((int) link_for_queues.head_in->secondNum[i]) +
                                            7 * 2;
                                }
                                sizeLine +=
                                        (2 + (link_for_queues.head_in->sizeVector - 1) * 2) * 2 + 2 * 3 + 2 + counter((int) resvecc) + 7;
                                lineExpression = malloc(sizeLine * sizeof(char));
                                sprintf(lineExpression, "((");
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, link_for_queues.head_in->firstNum[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
                                        sprintf(lineExpression, "%s, ", lineExpression);
                                    } else {
                                        sprintf(lineExpression, "%s) ", lineExpression);
                                    }
                                }
                                sprintf(lineExpression, "%s* (", lineExpression);
                                for (int i = 0; i < link_for_queues.head_in->sizeVector; i++) {
                                    sprintf(lineExpression, "%s%lf", lineExpression, link_for_queues.head_in->secondNum[i]);
                                    if (i < link_for_queues.head_in->sizeVector - 1) {
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
                push_back_queue_out(lineExpression, &link_for_queues);
                continueCalculate = link_for_queues.head_in->con;
                pop_queue_in(&link_for_queues);
            } while (continueCalculate ==
                     'y');     // Будет продолжать пока пользователь будет вводить "y" после завершения вычислений
            deletequeueIn(&link_for_queues); // Очищаем память
            writequeueIntoFile(OutputFile, &link_for_queues);
            deletequeueOut(&link_for_queues); // Очищаем память
            fclose(OutputFile);
            printf("Continue with files in this container?(y/n)\n");   // Вывод строки, с вопросом, продолжить ли вычисление с файлами
            scanf(" %c", &continueCycle);                    // Читает символ, если y - продолжить, если n - закончить
            while ((continueCycle != 'y') && (continueCycle != 'n')) // Проверка на корректно введенное y или n
            {
                printf("Invalid character, write \"y\" or \"n\"\n");
                scanf(" %c", &continueCycle);
            }
        } while (continueCycle == 'y');
    	    break;
    	case 's':
    		do
    			{
    				printf("File to read: ");
    				scanf(" %s", input);
    				InputFile = fopen(input, "r");
    				while (InputFile == NULL || feof(InputFile)) // Проверяем целлосность данных
    				{
    					if (feof(InputFile))
    						printf("The file is empty\n");
    					else
    						printf("Incorrect file name\n");
    					scanf(" %s", input);
    					InputFile = fopen(input, "r");
    				}
    				if (NewWriteFile) // Повторить ли файл вписывания
    				{
    					printf("Repeat the file for writing?(y/n)\n");
    					scanf(" %c", &fl);				   // Читает символ, если y - продолжить, если n - закончить
    					while ((fl != 'y') && (fl != 'n')) // Проверка на корректно введенное y или n
    					{
    						printf("invalid character, write \"y\" or \"n\"\n");
    						scanf(" %c", &fl);
    					}
    					NewWriteFile = 0;
    					if (fl == 'y')
    					{
    						OutputFile = fopen(output, "a");
    					}
    				}
    				if (!NewWriteFile && fl == 'n') // Открытие нового файла
    				{
    					NewWriteFile = 1;
    					printf("File to write: ");
    					scanf(" %s", output);
    					OutputFile = fopen(output, "w");
    				}

    				char perm; // Читаем по одному элементу char
    				do
    				{

    					char *expression; // записываем эти элементы сюда
    					expression = malloc(125 * sizeof(char));
    					int i = 0;
    					do
    					{
    						fscanf(InputFile, " %c ", &perm);
    						expression[i] = (perm != 'y' && perm != 'n') ? perm : ' '; // закончится выражение должно ' '
    						if (++i >= 125)
    						{
    							break;
    						}
    					} while (perm != 'y' && perm != 'n');

    					i = 0;
    					short int brackets = 0;	   // Кол-во скобок
    					short int isNumParam = -1; // Является ли char числом
    					while (expression[i] != ' ')
    					{
    						short int mayOne; // для отрицательных чисел
    						if (isNumParam == 0 && expression[i] == '-' && (i + 1) < 125 && isNum(expression[i + 1]))
    						{
    							mayOne = 1;
    							isNumParam = 1;
    						}
    						else
    						{
    							mayOne = 0;
    							isNumParam = isNum(expression[i]);
    						}
    						switch (isNumParam)
    						{
    						case 1:;
    							char *nums; // Записываем сюда потенциальное чилсо
    							nums = malloc(15 * sizeof(char));
    							for (int j = 0; j < 15; j++)
    							{
    								if ((isOpe(expression[i]) && !mayOne) || expression[i] == ' ' || expression[i] == '(' || expression[i] == ')')
    								{
    									break;
    								}
    								nums[j] = expression[i];
    								mayOne = 0;
    								i++;
    							}
    							double numFromString; // из строки в число
    							numFromString = strtod(nums, NULL);
    							push_back_n(numFromString, &link_for_stack);
    							free(nums);
    							break;
    						case 0:
    							if (expression[i] == '!')
    							{ // случай с !
    								push_back_n(calculate(pop_n(&link_for_stack), 0.0, '!'), &link_for_stack);
    								i++;
    								break;
    							}
    							if (expression[i] == '(')
    							{ // Находим скобку
    								brackets += 1;
    								push_back_o('(', &link_for_stack);
    								i++;
    								break;
    							}
    							char operFromStack = pop_o(&link_for_stack);
    							if (expression[i] == ')')
    							{ // Решаем все до открывающей скобки
    								if (operFromStack == ' ')
    								{
    									push_back_o(operFromStack, &link_for_stack);
    									brackets -= 1;
    									i++;
    									break;
    								}
    								if (operFromStack == '(')
    								{
    									brackets -= 1;
    									i++;
    									break;
    								}
    								push_back_o(operFromStack, &link_for_stack);
    								resultCalculatorWithController();
    								break;
    							}
    							else if ((priority(operFromStack) >= priority(expression[i])))
    							{ // Если приоритет предыдущей операции больше следующей, решаем
    								if (operFromStack != '(')
    								{
    									push_back_o(operFromStack, &link_for_stack);
    									resultCalculatorWithController();
    									isNumParam = 1;
    									break;
    								}
    							}
    							if (operFromStack != ' ')
    							{
    								push_back_o(operFromStack, &link_for_stack);
    							}
    							push_back_o(expression[i], &link_for_stack);
    							i++;
    							break;
    						default:
    							break; // Такого быть не может никогда
    						}
    					}

    					while (link_for_stack.head_o != NULL)
    					{ // После конца обследуем оставшееся
    						resultCalculatorWithController();
    					}

    					switch (brackets)
    					{ // Нормально ли расставлены скобки
    					case 0:
    						if (link_for_stack.head_n->next == NULL)
    						{
    							i = 0;
    							while (expression[i] != ' ')
    							{
    								if (isNum(expression[i]))
    								{
    									do
    									{
    										if (isOpe(expression[i]) || expression[i] == ' ' || expression[i] == '(' || expression[i] == ')')
    										{
    											break;
    										}
    										fprintf(OutputFile, "%c", expression[i]);
    										i++;
    									} while (1);
    									fprintf(OutputFile, " ");
    								}
    								else
    								{
    									fprintf(OutputFile, "%c ", expression[i]);
    									i++;
    								}
    							}
    							free(expression);
    							fprintf(OutputFile, "= %lf\n", pop_n(&link_for_stack)); // Записываем результат
    						}
    						else
    						{
    							fprintf(OutputFile, "Incorrect write expression\n");
    						}
    						break;
    					default:
    						if (brackets > 0)
    						{
    							fprintf(OutputFile,
    									"Incorrect number of characters(\"(\")\n");
    						}
    						else
    						{
    							fprintf(OutputFile,
    									"Incorrect number of characters(\")\")\n");
    						}
    					}
    					delete_n(&link_for_stack); // Очищаем
    					delete_o(&link_for_stack);
    				} while (perm != 'n');
    				fclose(OutputFile); // Очищаем
    				fclose(InputFile);

    				printf("Continue with files in this container?(y/n)\n");					 // Вывод строки, с вопросом, продолжить ли вычисление с файлами
    				scanf(" %c", &continueCycle);							 // Читает символ, если y - продолжить, если n - закончить
    				while ((continueCycle != 'y') && (continueCycle != 'n')) // Проверка на корректно введенное y или n
    				{
    					printf("Invalid character, write \"y\" or \"n\"\n");
    					scanf(" %c", &continueCycle);
    				}
    			} while (continueCycle == 'y');
    	    break;
    	default:
    		printf("I don't know this symbol\n");
    		break;
    	}
    	printf("Continue work with calculator?(y/n)\n");					 // Вывод строки, с вопросом, продолжить ли вычисление с файлами
    	scanf(" %c", &continueCycle);							 // Читает символ, если y - продолжить, если n - закончить
    	while ((continueCycle != 'y') && (continueCycle != 'n')) // Проверка на корректно введенное y или n
    	{
    	    printf("Invalid character, write \"y\" or \"n\"\n");
    	    scanf(" %c", &continueCycle);
    	}
    } while (continueCycle == 'y');
    return 0;
}
