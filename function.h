#ifndef FUNCTION_H
#define FUNCTION_H

#include "record.h"

Node* createNode(Record R);
AccountNode *createAccountNode(Account A);
void toLowerCase(char *str);
int validatePhone(char phone[]);
int validateLastSix(char phone[]);
int validateInput(char str[]);
void updatePhoneAreaCode(Record *R);
void loadAccountsToList(const char *filename, AccountNode **head);
int login(AccountNode *head);
void addRecord(Node** head, Record R);
void readFile(const char *filename, Node **head);
void saveRecordToFile(const char *filename, Node *head);
void saveAccountToFile(const char *filename,AccountNode *head);
void clearInputBuffer();
void pauseScreen();
void clearScreen();
void endScreen();
int inputStatus();
Account inputAccount();
void addAccount(AccountNode **head);
char* findPrefixByProvince(char tentinh[]);
Record inputRecord();
Node* search_record(Node* head,char phone[15]);
void updateAccount(AccountNode *head);
void updateRecord(Node* head);
void deleteAccount(AccountNode **head);
void deleteRecord(Node **head);
void listByProvince(Node* head);
double total_Fee(Record R);
void exportReport(Node *head);
void statisticsByProvince(Node* head);
void checkDuplicate(Node** head);
void filterByStatus(Node *head);
void readFileByUser(Node **head);
void exportBill(Node *p);
void calculateFee(Node *head);
int findProvinceIndex(ProvinceFee stats[], int count, char provinceName[]);
void pronvinceMaxRecord (Node *head);
void top3RecordMaxFee (Node *head, int month, int year);
void top3ProvinceByFee(Node *head, int month, int year);
int revenue(Node *head, int month, int year);
void revenueStatistics(Node *head);

#endif
