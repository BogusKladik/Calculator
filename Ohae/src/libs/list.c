#include"list.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

void fill_example(example_input_data_for_lists *current, FILE *InputFile){
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

void push_back_list_in(example_input_data_for_lists example_list){
    if (link_for_lists.head_in == NULL) {
        link_for_lists.head_in = malloc(sizeof(input_data_for_lists));
        link_for_lists.current_in = link_for_lists.head_in;
    } else {
        link_for_lists.current_in = link_for_lists.head_in;
        while (link_for_lists.current_in->next != NULL) {
            link_for_lists.current_in = link_for_lists.current_in->next;
        }
        link_for_lists.current_in->next = malloc(sizeof(input_data_for_lists));
        link_for_lists.current_in = link_for_lists.current_in->next;
    }
    link_for_lists.current_in->next = NULL;
    link_for_lists.current_in->whatCalculator = example_list.whatCalculator;
    switch (link_for_lists.current_in->whatCalculator) {
        case 'v':
            link_for_lists.current_in->sizeVector = example_list.sizeVector;
            link_for_lists.current_in->firstNum = example_list.firstNum;
            link_for_lists.current_in->operation = example_list.operation;
            link_for_lists.current_in->secondNum = example_list.secondNum;
            break;
        default:
            link_for_lists.current_in->firstNum = example_list.firstNum;
            link_for_lists.current_in->operation = example_list.operation;
            if (link_for_lists.current_in->operation != '!') {
                link_for_lists.current_in->secondNum = example_list.secondNum;
            }
    }
    link_for_lists.current_in->con = example_list.con;
}

void push_back_list_out(char *line){
    if (link_for_lists.head_out == NULL){
        link_for_lists.head_out = malloc(sizeof(output_data_for_lists));
        link_for_lists.current_out = link_for_lists.head_out;
    } else {
        link_for_lists.current_out = link_for_lists.head_out;
        while (link_for_lists.current_out->next != NULL) {
            link_for_lists.current_out = link_for_lists.current_out->next;
        }
        link_for_lists.current_out->next = malloc(sizeof(output_data_for_lists));
        link_for_lists.current_out = link_for_lists.current_out->next;
    }
    link_for_lists.current_out->next = NULL;
    link_for_lists.current_out->result = line;
}

void pop_list_in(){
    if (link_for_lists.head_in == NULL || link_for_lists.current_in == NULL){
        return;
    }
    if (link_for_lists.head_in == link_for_lists.current_in){
        link_for_lists.current_in = link_for_lists.current_in->next;
        free(link_for_lists.head_in);
        link_for_lists.head_in = link_for_lists.current_in;
        return;
    }
    input_data_for_lists *term = link_for_lists.head_in;
    while (term->next != link_for_lists.current_in){
        term = term->next;
    }
    term->next = link_for_lists.current_in->next;
    free(link_for_lists.current_in);
    link_for_lists.current_in = term;
}

char *pop_list_out(){
    if (link_for_lists.head_out == NULL || link_for_lists.current_out == NULL){
        return NULL;
    }
    char *line;
    if (link_for_lists.head_out == link_for_lists.current_out){
        line = link_for_lists.current_out->result;
        link_for_lists.current_out = link_for_lists.current_out->next;
        free(link_for_lists.head_out);
        link_for_lists.head_out = link_for_lists.current_out;
        return line;
    }
    output_data_for_lists *term = link_for_lists.head_out;
    while (term->next != link_for_lists.current_out){
        term = term->next;
    }
    line = link_for_lists.current_out->result;
    term->next = link_for_lists.current_out->next;
    free(link_for_lists.current_out);
    link_for_lists.current_out = term;
    return line;
}

void deleteListIn() { // Удалить лист input_data_for_lists
    link_for_lists.current_in = link_for_lists.head_in;
    while (link_for_lists.current_in != NULL){
        link_for_lists.current_in = link_for_lists.head_in;
        pop_list_in();
    }
}

void deleteListOut() { // Удалить лист output_data_for_lists
    link_for_lists.current_out = link_for_lists.head_out;
    while (link_for_lists.current_out != NULL){
        link_for_lists.current_out = link_for_lists.head_out;
        pop_list_out();
    }
}

void writeListIntoFile(FILE *OutputFile) { // Вписать из листа в файл
    link_for_lists.current_out = link_for_lists.head_out;
    while (link_for_lists.current_out != NULL) {
        fprintf(OutputFile, "%s\n", pop_list_out());
    }
}
