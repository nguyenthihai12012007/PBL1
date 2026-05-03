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
} Record;

typedef struct Node {
    Record data;
    struct Node *next;
} Node;

#endif