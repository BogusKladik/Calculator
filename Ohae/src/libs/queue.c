#include"queue.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

void fill_example_queue_in(example_input_data_for_queues *current, FILE *InputFile){
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

void push_back_queue_in(example_input_data_for_queues example_queue, links_for_queues *link){
    if (link->head_in == NULL) {
    	link->head_in = malloc(sizeof(input_data_for_queues));
    	link->tail_in = link->head_in;
    } else {
    	link->tail_in->next = malloc(sizeof(input_data_for_queues));
    	link->tail_in = link->tail_in->next;
    }
    link->tail_in->next = NULL;
    link->tail_in->whatCalculator = example_queue.whatCalculator;
    switch (link->tail_in->whatCalculator) {
        case 'v':
        	link->tail_in->sizeVector = example_queue.sizeVector;
        	link->tail_in->firstNum = example_queue.firstNum;
        	link->tail_in->operation = example_queue.operation;
        	link->tail_in->secondNum = example_queue.secondNum;
            break;
        default:
        	link->tail_in->firstNum = example_queue.firstNum;
        	link->tail_in->operation = example_queue.operation;
            if (link->tail_in->operation != '!') {
            	link->tail_in->secondNum = example_queue.secondNum;
            }
    }
    link->tail_in->con = example_queue.con;
}

void push_back_queue_out(char *line, links_for_queues *link){
    if (link->head_out == NULL){
    	link->head_out = malloc(sizeof(output_data_for_queues));
        link->tail_out = link->head_out;
    } else {
    	link->tail_out->next = malloc(sizeof(output_data_for_queues));
    	link->tail_out = link->tail_out->next;
    }
    link->tail_out->next = NULL;
    link->tail_out->result = line;
}

void pop_queue_in(links_for_queues *link){
    if (link->head_in == NULL){
        return;
    }
    if (link->head_in->next == NULL){
        free(link->head_in);
        link->head_in = NULL;
        link->tail_in = NULL;
        return;
    }
    input_data_for_queues *term = link->head_in;
    link->head_in = term->next;
    free(term);
}

char *pop_queue_out(links_for_queues *link){
    char *line;
    if (link->head_out == NULL){
        return NULL;
    }
    if (link->head_out->next == NULL){
        line = link->head_out->result;
        free(link->head_out);
        link->head_out = NULL;
        link->tail_out = NULL;
        return line;
    }
    output_data_for_queues *term = link->head_out;
    link->head_out = term->next;
    line = term->result;
    free(term);
    return line;
}

void deletequeueIn(links_for_queues *link) { // Удалить лист input_data_for_queues
    while (link->head_in != NULL){
        pop_queue_in(link);
    }
}

void deletequeueOut(links_for_queues *link) { // Удалить лист output_data_for_queues
    while (link->head_out != NULL){
        pop_queue_out(link);
    }
}

void writequeueIntoFile(FILE *OutputFile, links_for_queues *link) { // Вписать из листа в файл
    while (link->head_out != NULL) {
        fprintf(OutputFile, "%s\n", pop_queue_out(link));
    }
}
