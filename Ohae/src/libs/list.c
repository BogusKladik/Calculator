#include"list.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

void fill_example_list_in(example_input_data_for_lists *current, FILE *InputFile){
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

void push_list_in(example_input_data_for_lists example_list, links_for_lists *link){
    if (link->head_in == NULL) {
        link->head_in = malloc(sizeof(input_data_for_lists));
        link->current_in = link->head_in;
    } else {
        link->current_in = link->head_in;
        while (link->current_in->next != NULL) {
            link->current_in = link->current_in->next;
        }
        link->current_in->next = malloc(sizeof(input_data_for_lists));
        link->current_in = link->current_in->next;
    }
    link->current_in->next = NULL;
    link->current_in->whatCalculator = example_list.whatCalculator;
    switch (link->current_in->whatCalculator) {
        case 'v':
            link->current_in->sizeVector = example_list.sizeVector;
            link->current_in->firstNum = example_list.firstNum;
            link->current_in->operation = example_list.operation;
            link->current_in->secondNum = example_list.secondNum;
            break;
        default:
            link->current_in->firstNum = example_list.firstNum;
            link->current_in->operation = example_list.operation;
            if (link->current_in->operation != '!') {
                link->current_in->secondNum = example_list.secondNum;
            }
    }
    link->current_in->con = example_list.con;
}

void push_list_out(char *line, links_for_lists *link){
    if (link->head_out == NULL){
        link->head_out = malloc(sizeof(output_data_for_lists));
        link->current_out = link->head_out;
    } else {
        link->current_out = link->head_out;
        while (link->current_out->next != NULL) {
            link->current_out = link->current_out->next;
        }
        link->current_out->next = malloc(sizeof(output_data_for_lists));
        link->current_out = link->current_out->next;
    }
    link->current_out->next = NULL;
    link->current_out->result = line;
}

void pop_list_in(links_for_lists *link){
    if (link->head_in == NULL || link->current_in == NULL){
        return;
    }
    if (link->head_in == link->current_in){
        link->current_in = link->current_in->next;
        free(link->head_in);
        link->head_in = link->current_in;
        return;
    }
    input_data_for_lists *term = link->head_in;
    while (term->next != link->current_in){
        term = term->next;
    }
    term->next = link->current_in->next;
    free(link->current_in);
    link->current_in = term;
}

char *pop_list_out(links_for_lists *link){
    if (link->head_out == NULL || link->current_out == NULL){
        return NULL;
    }
    char *line;
    if (link->head_out == link->current_out){
        line = link->current_out->result;
        link->current_out = link->current_out->next;
        free(link->head_out);
        link->head_out = link->current_out;
        return line;
    }
    output_data_for_lists *term = link->head_out;
    while (term->next != link->current_out){
        term = term->next;
    }
    line = link->current_out->result;
    term->next = link->current_out->next;
    free(link->current_out);
    link->current_out = term;
    return line;
}

void deleteListIn(links_for_lists *link) {
    link->current_in = link->head_in;
    while (link->current_in != NULL){
        link->current_in = link->head_in;
        pop_list_in(link);
    }
}

void deleteListOut(links_for_lists *link) {
    link->current_out = link->head_out;
    while (link->current_out != NULL){
        link->current_out = link->head_out;
        pop_list_out(link);
    }
}

void writeListIntoFile(FILE *OutputFile, links_for_lists *link) {
    link->current_out = link->head_out;
    while (link->current_out != NULL) {
        fprintf(OutputFile, "%s\n", pop_list_out(link));
    }
}
