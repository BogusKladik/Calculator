#if !defined(queueh)
#define queueh

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

typedef struct example_input_data_for_queues {
    char whatCalculator;
    int sizeVector;
    double *firstNum;
    char operation;
    double *secondNum;
    char con;
} example_input_data_for_queues;

typedef struct input_data_for_queues { // Лист для записи данных для чтения
    char whatCalculator;
    int sizeVector;
    double *firstNum;
    char operation;
    double *secondNum;
    char con;
    struct input_data_for_queues *next;
} input_data_for_queues;

typedef struct output_data_for_queues { // Лист для записи данных для вывода в другой файл
    char *result;
    struct output_data_for_queues *next;
} output_data_for_queues;

typedef struct links_for_queues
{ // Структура всех ссылок
	input_data_for_queues *head_in, *tail_in;
	output_data_for_queues *head_out, *tail_out;
} links_for_queues;

void fill_example_queue_in(example_input_data_for_queues *current, FILE *InputFile);// Заполнить элемент структуры

void push_back_queue_in(example_input_data_for_queues example_queue, links_for_queues *link);// Добавить в очередь с исходными данными

void push_back_queue_out(char *line, links_for_queues *link);// Добавить в очередь с выходными данными

void pop_queue_in(links_for_queues *link);// Убрать из очереди с иходными данными

char *pop_queue_out(links_for_queues *link);// Убрать из очереди с выходными данными

void deletequeueIn(links_for_queues *link);// Удалить очередь с исходными данными

void deletequeueOut(links_for_queues *link);// Удалить очередь с выходными данными

void writequeueIntoFile(FILE *OutputFile, links_for_queues *link);// Написать в файл результат

#endif // queueh
