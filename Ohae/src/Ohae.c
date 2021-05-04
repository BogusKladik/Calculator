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

const char ALL_OPERATION[] = { '^', '*', '/', '+', '-', '!' }; // Все операции

int priority(char operation) { // Приоритет операций (для выполнения обратной полькой нотации)
	switch (operation) {
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

typedef struct numbers { // Очередь для чисел
	double num;
	struct numbers *prev, *next;
} numbers;

typedef struct operations { // Очередь для операций
	char operation;
	int priority;
	struct operations *prev, *next;
} operations;

typedef struct links { // Структура всех ссылок
	numbers *head_n, *current_n, *tail_n;
	operations *head_o, *current_o, *tail_o;
} links;

links link; // Создаем элемент этой структуры

double pop_n() { // Удалить из очереди чисел
	double lastNum = 0.0;
	if (link.head_n == NULL) {
		return lastNum;
	}
	if (link.head_n->next == NULL) {
		lastNum = link.head_n->num;
		free(link.head_n);
		link.head_n = NULL;
		link.tail_n = NULL;
		return lastNum;
	}
	lastNum = link.tail_n->num;
	link.tail_n = link.tail_n->prev;
	free(link.tail_n->next);
	link.tail_n->next = NULL;
	return lastNum;
}

char pop_o() { // Удалить из очереди операций
	char lastOperation = ' ';
	if (link.head_o == NULL) {
		return lastOperation;
	}
	if (link.head_o->next == NULL) {
		lastOperation = link.head_o->operation;
		free(link.head_o);
		link.head_o = NULL;
		link.tail_o = NULL;
		return lastOperation;
	}
	lastOperation = link.tail_o->operation;
	link.tail_o = link.tail_o->prev;
	free(link.tail_o->next);
	link.tail_o->next = NULL;
	return lastOperation;
}

void delete_n() { // Удалить всю очередь номеров
	while (link.head_n != NULL) {
		pop_n();
	}
}

void delete_o() { // Удалить всю очередь операций
	while (link.head_o != NULL) {
		pop_o();
	}
}

void push_back_n(double data) { // Добавить в конец очереди с номерами
	if (link.head_n == NULL) {
		link.head_n = malloc(sizeof(numbers));
		link.head_n->prev = NULL;
		link.head_n->next = NULL;
		link.tail_n = link.head_n;
		link.head_n->num = data;
		return;
	}
	link.tail_n->next = malloc(sizeof(numbers));
	link.tail_n->next->prev = link.tail_n;
	link.tail_n->next->num = data;
	link.tail_n = link.tail_n->next;
	link.tail_n->next = NULL;
}

void push_back_o(char data) { // Добавить в конец очереди с операциями
	if (link.head_o == NULL) {
		link.head_o = malloc(sizeof(operations));
		link.head_o->prev = NULL;
		link.head_o->next = NULL;
		link.tail_o = link.head_o;
		link.head_o->operation = data;
		link.head_o->priority = priority(data);
		return;
	}
	link.tail_o->next = malloc(sizeof(operations));
	link.tail_o->next->prev = link.tail_o;
	link.tail_o->next->operation = data;
	link.tail_o->next->priority = priority(data);
	link.tail_o = link.tail_o->next;
	link.tail_o->next = NULL;
}

short int isNum(char num) { // Проверка на то, что элемент типа char является числом
	int truth = 0;
	char numbersLikeChar[] =
			{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (int i = 0; i < 10; i++) {
		if (num == numbersLikeChar[i]) {
			truth = 1;
			return truth;
		}
	}
	return truth;
}

short int isOpe(char ope) { // Проверка на то, что элемент типа char является операцией
	int truth = 0;
	if (ope == ' ') {
		truth = 1;
		return truth;
	}
	for (int i = 0; i < 6; i++) {
		if (ope == ALL_OPERATION[i]) {
			truth = 1;
			return truth;
		}
	}
	return truth;
}

double calculate(double firstNum, double secondNum, char operation) { // Калькулятор для чисел
	switch (operation) {
	case '!':
		if (firstNum == 0) {
			return 1.0;
		}
		if (firstNum < 0) {
			return firstNum; // Должен выдавать ошибку, но я убрал это, для более легкой работы далее
		}
		double resultForIntegral = 1.0;
		for (int j = 1; j <= (int) firstNum; j++) {
			resultForIntegral *= j;
		}
		return resultForIntegral;
	case '^':
		if (secondNum == 0) {
			return 1;
		}
		if (secondNum < 0) {
			secondNum = -secondNum;
			firstNum = 1.0 / firstNum;
		}
		double result = 1.0;
		for (int i = 0; i < (int) secondNum; i++) {
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

double resultCalculatorWithController() { // Забирает с очереди элементы и дает их калькулятору. Потом записывает результат в очередь чисел
	char operationFromList = pop_o();
	double secondNumFromList = pop_n();
	double firstNumFromList = pop_n();
	push_back_n(
			calculate(firstNumFromList, secondNumFromList, operationFromList));
	return calculate(firstNumFromList, secondNumFromList, operationFromList);
}

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	FILE *InputFile, *OutputFile; // Файлы
	char input[125], output[125], continueFiles, fl = 'n'; // input/output - название файла чтения/записи, continueFiles - Продолжать ли работу с файлами, fl - повторить ли файл записи
	int NewWriteFile = 0; // Новый ли файл записи

	link.head_n = NULL;
	link.head_o = NULL;
	link.tail_n = NULL;
	link.tail_o = NULL;

	do {
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
			scanf(" %c", &fl); // Читает символ, если y - продолжить, если n - закончить
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

		char perm; // Читаем по одному элементу char
		do {

			char *expression; // записываем эти элементы сюда
			expression = malloc(125 * sizeof(char));
			int i = 0;
			do {
				fscanf(InputFile, " %c ", &perm);
				expression[i] = (perm != 'y' && perm != 'n') ? perm : ' '; // закончится выражение должно ' '
				if (++i >= 125) {
					break;
				}
			} while (perm != 'y' && perm != 'n');

			i = 0;
			short int brackets = 0; // Кол-во скобок
			short int isNumParam = -1; // Является ли char числом
			while (expression[i] != ' ') {
				short int mayOne; // для отрицательных чисел
				if (isNumParam == 0 && expression[i] == '-' && (i + 1) < 125
						&& isNum(expression[i + 1])) {
					mayOne = 1;
					isNumParam = 1;
				} else {
					mayOne = 0;
					isNumParam = isNum(expression[i]);
				}
				switch (isNumParam) {
				case 1:
					;
					char *nums; // Записываем сюда потенциальное чилсо
					nums = malloc(15 * sizeof(char));
					for (int j = 0; j < 15; j++) {
						if ((isOpe(expression[i]) && !mayOne)
								|| expression[i] == ' ' || expression[i] == '('
								|| expression[i] == ')') {
							break;
						}
						nums[j] = expression[i];
						i++;
					}
					double numFromString; // из строки в число
					numFromString = strtod(nums, NULL);
					push_back_n(numFromString);
					free(nums);
					break;
				case 0:
					if (expression[i] == '!') { // случай с !
						push_back_n(calculate(pop_n(), 0.0, '!'));
						i++;
						break;
					}
					if (expression[i] == '(') { // Находим скобку
						brackets += 1;
						push_back_o('(');
						i++;
						break;
					}
					if (expression[i] == ')') { // Решаем все до открывающей скобки
						if (link.head_o == NULL) {
							brackets -= 1;
							i++;
							break;
						}
						if (link.tail_o->operation == '(') {
							pop_o();
							brackets -= 1;
							i++;
							break;
						}
						resultCalculatorWithController();
						break;
					} else if (link.tail_o != NULL
							&& (link.tail_o->priority >= priority(expression[i]))) { // Если приоритет предыдущей операции больше следующей, решаем
						if (link.tail_o->operation != '(') {
							resultCalculatorWithController();
							break;
						}
					}
					push_back_o(expression[i]);
					i++;
					break;
				default:
					break; // Такого быть не может никогда
				}
			}

			while (link.head_o != NULL) { // После конца обследуем оставшееся
				resultCalculatorWithController();
			}

			switch (brackets) { // Нормально ли расставлены скобки
			case 0:
				if (link.head_n->next == NULL) {
					i = 0;
					while (expression[i] != ' ') {
						if (isNum(expression[i])) {
							do {
								if (isOpe(expression[i]) || expression[i] == ' '
										|| expression[i] == '('
										|| expression[i] == ')') {
									break;
								}
								fprintf(OutputFile, "%c", expression[i]);
								i++;
							} while (1);
							fprintf(OutputFile, " ");
						} else {
							fprintf(OutputFile, "%c ", expression[i]);
							i++;
						}
					}
					free(expression);
					fprintf(OutputFile, "= %lf\n", link.tail_n->num); // Записываем результат
				} else {
					fprintf(OutputFile, "Incorrect write expression\n");
				}
				break;
			default:
				if (brackets > 0) {
					fprintf(OutputFile,
							"Incorrect number of characters(\"(\")\n");
				} else {
					fprintf(OutputFile,
							"Incorrect number of characters(\")\")\n");
				}
			}
			delete_n(); // Очищаем
			delete_o();
		} while (perm != 'n');
		fclose(OutputFile); // Очищаем
		fclose(InputFile);

		printf("Continue with files?(y/n)\n"); // Вывод строки, с вопросом, продолжить ли вычисление с файлами
		scanf(" %c", &continueFiles); // Читает символ, если y - продолжить, если n - закончить
		while ((continueFiles != 'y') && (continueFiles != 'n')) // Проверка на корректно введенное y или n
		{
			printf("Invalid character, write \"y\" or \"n\"\n");
			scanf(" %c", &continueFiles);
		}
	} while (continueFiles == 'y');
	return 0;
}
