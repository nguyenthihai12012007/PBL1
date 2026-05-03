#include <stdio.h>
#include <string.h>
#include "print.h"

void printStatus(int status) {
    switch (status) {
        case 1:
            printf("Dang hoat dong");
            break;
        case 2:
            printf("Tam khoa");
            break;
        case 3:
            printf("Da huy");
            break;
        default:
            printf("Khong xac dinh");
    }
}

void print_record(Node* node) {
    if (node == NULL) return;

    printf("Ten: %s\n", node->data.name);
    printf("So dien thoai: %s\n", node->data.phone);
    printf("Dia chi: %s\n", node->data.address);
    printf("Tinh: %s\n", node->data.province.tentinh);
    printf("Trang thai: ");
    printStatus(node->data.status);
    printf("\n");
}

void printHeader() {
    printf("+-----+-------------------------------------+--------------+----------------------+------------+------------+\n");
    printf("| %-3s | %-35s | %-12s | %-20s | %-10s | %-10s |\n", "STT", "Ten", "Dien thoai", "Dia chi", "Tinh", "Trang thai");
    //printf("| STT |                  Ten                |  Dien thoai  |       Dia chi        |    Tinh    | Trang thai |\n");
    printf("+-----+-------------------------------------+--------------+----------------------+------------+------------+\n");
}

void printRow(int stt, Node* p) {
    char status[20];

    switch (p->data.status) {
        case 1: strcpy(status, "Hoat dong"); break;
        case 2: strcpy(status, "Tam khoa"); break;
        case 3: strcpy(status, "Da huy"); break;
        default: strcpy(status, "Khong ro");
    }

    printf("| %-3d | %-35.35s | %-12s | %-20.20s | %-10.10s | %-10s |\n", stt, p->data.name, p->data.phone, p->data.address, p->data.province.tentinh, status);
}

void printFooter() {
    printf("+-----+-------------------------------------+--------------+----------------------+------------+------------+\n");
}

void displayAll(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\n                                          DANH SACH DANH BA\n");
    printHeader();

    Node *p = head;
    int stt = 1;

    while (p != NULL) {
        printRow(stt, p);
        p = p->next;
        stt++;
    }
    printFooter();
}

void menu() {
    printf("\nCHUONG TRINH QUAN LY DANH BA DIEN THOAI\n");
    printf("1. Them thue bao\n");
    printf("2. Hien thi toan bo danh ba\n");
    printf("3. Tim kiem thue bao\n");
    printf("4. Sua thong tin thue bao\n");
    printf("5. Xoa thue bao\n");
    printf("6. Liet ke danh ba tung tinh thanh\n");
    printf("7. Thong ke thue bao\n");
    printf("8. Kiem tra trung so dien thoai\n");
    printf("9. Ghi file du lieu thue bao\n");
    printf("0. Thoat chuong trinh\n");
    printf("-----------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}