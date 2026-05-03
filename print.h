#ifndef PRINT_H
#define PRINT_H

#include "record.h"

void printStatus(int status);
void print_record(Node* node);
void printHeader();
void printRow(int stt, Node* p);
void printFooter();
void displayAll(Node* head);
void menu();

#endif