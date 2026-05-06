#ifndef RECORD_H
#define RECORD_H

typedef struct Province {
    char tentinh[50];
} Province;

typedef struct Record {
    Province province;
    char name[100];
    char address[100];
    char phone[15];
    int status;

    int onNetMinutes; // noi mang
    int offNetMinutes;
} Record;

typedef struct Node {
    Record data;
    struct Node *next;
} Node;

typedef struct {
    char provinceName[50];
    double totalFee;
} ProvinceFee;

#endif