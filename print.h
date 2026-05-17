#ifndef PRINT_H
#define PRINT_H

#include "record.h"

void printStatus(int status);
void print_record(Node* node);
void printHeader();
void printRow(int stt, Node* p);
void printFooter();
void displayAll(Node* head);
void printTop3ProvinceFee(ProvinceFee stats[], int count);
void printProvinceMaxRecord(ProvinceStat stats[], int count, int maxIndex);
void printTop3RecordMaxFee(CompanyFee stats[], int limit);
void printBill(Node *p);
void menu_admin();
void menu_statistical();
void menu_account();
void menu_staff();

#endif
