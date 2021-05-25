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

void fill_example(example_input_data_for_lists *current, FILE *InputFile);

void push_back_list_in(example_input_data_for_lists example_list);

void push_back_list_out(char *line);

void pop_list_in();

char *pop_list_out();

void deleteListIn();

void deleteListOut();

void writeListIntoFile(FILE *OutputFile);
#endif // listh