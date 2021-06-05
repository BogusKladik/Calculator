#if !defined(listh)
#define listh

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

typedef struct example_input_data_for_lists {
    char whatCalculator;
    int sizeVector;
    double *firstNum;
    char operation;
    double *secondNum;
    char con;
} example_input_data_for_lists;

typedef struct input_data_for_lists { // Лист для записи данных для чтения
    char whatCalculator;
    int sizeVector;
    double *firstNum;
    char operation;
    double *secondNum;
    char con;
    struct input_data_for_lists *next;
} input_data_for_lists;

typedef struct output_data_for_lists { // Лист для записи данных для вывода в другой файл
    char *result;
    struct output_data_for_lists *next;
} output_data_for_lists;

typedef struct links_for_lists
{ // Структура всех ссылок
	input_data_for_lists *head_in, *current_in;
	output_data_for_lists *head_out, *current_out;
} links_for_lists;

void fill_example_list_in(example_input_data_for_lists *current, FILE *InputFile);// Заполнить элемент структуры

void push_list_in(example_input_data_for_lists example_list, links_for_lists *link);// Добавить в лист с исходными данными

void push_list_out(char *line, links_for_lists *link);// Добавить в лист с выходными данными

void pop_list_in(links_for_lists *link);// Убрать из листа с иходными данными

char *pop_list_out(links_for_lists *link);// Убрать из листа с выходными данными

void deleteListIn(links_for_lists *link);// Удалить лист с исходными данными

void deleteListOut(links_for_lists *link);// Удалить лист с выходными данными

void writeListIntoFile(FILE *OutputFile, links_for_lists *link);// Написать в файл результат

#endif // listh
