#ifndef PRINT_H
#define PRINT_H

#include "record.h"

void printSpace();
void printCenter(const char *text, int width);
void printMiddle(const char *text);
void printSystemHeader(const char *title);
void printSystemFooter();
void showUpdateResult(Node *head, const char text[]);
void printStatus(int status);
void print_record(Node* node);
void print_all_record(Node *head);
void print_account(AccountNode *Node);
void printHeader();
void printRow(int stt, Node* p);
void printFooter();
void printTop3ProvinceFee(ProvinceFee stats[], int count);
void printProvinceMaxRecord(ProvinceStat stats[], int count, int maxIndex);
void printTop3RecordMaxFee(CompanyFee stats[], int limit);
void printBill(Node *p);
void showScreen();

#endif
