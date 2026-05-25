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
int login(AccountNode *head,char currentUsername[]);
void addRecordByUser(Node** head, Record R, char currentUsername[]);
void addRecordByFile(Node** head, Record R);
void writeHistory(char username[], char action[], char target[], char detail[]);
void readFile(const char *filename, Node **head,char currentUsername[]);
void saveRecordToFile(const char *filename, Node *head);
void saveAccountToFile(const char *filename,AccountNode *head);
void clearInputBuffer();
void pauseScreen();
void clearScreen();
void endScreen();
int inputStatus();
Account inputAccount();
void addAccount(AccountNode **head,char currentUsername[]);
char* findPrefixByProvince(char tentinh[]);
Record inputRecord();
int isSimilarPhone(char inputPhone[],char phone[]);
void suggestSimilarPhone(Node *head, char inputPhone[]);
Node* search_record(Node* head,char phone[15]);
void updateAccount(AccountNode *head,char currentUsername[]);
void updateRecord(Node *head, char currentUsername[]);
void deleteAccount(AccountNode **head,char currentUsername[]);
void deleteRecord(Node **head, char currentUsername[]);
void listByProvince(Node* head);
double total_Fee(Record R);
void exportReport(Node *head);
void statisticsByProvince(Node* head);
void checkDuplicate(Node** head);
void filterByStatus(Node *head);
void readFileByUser(Node **head, char currentUsername[]);
void exportBill(Node *p);
void calculateFee(Node *head);
void showHistory();
int findProvinceIndex(ProvinceFee stats[], int count, char provinceName[]);
void pronvinceMaxRecord (Node *head);
void top3RecordMaxFee (Node *head, int month, int year);
void top3ProvinceByFee(Node *head, int month, int year);
int revenue(Node *head, int month, int year);
void revenueStatistics(Node *head);

#endif
