#include <stdio.h>
#include <string.h>

#include "print.h"
#include "constants.h"
#include "billing.h"

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

void printTop3ProvinceFee(ProvinceFee stats[], int count) {
    int first = -1;
    int second = -1;
    int third = -1;

    for (int i = 0; i < count; i++) {
        if (first == -1 || stats[i].totalFee > stats[first].totalFee) {
            third = second;
            second = first;
            first = i;
        } 
        else if (second == -1 || stats[i].totalFee > stats[second].totalFee) {
            third = second;
            second = i;
        } 
        else if (third == -1 || stats[i].totalFee > stats[third].totalFee) {
            third = i;
        }
    }

    printf("\n+======================================================+\n");
    printf("|             TOP 3 TINH CO CUOC CAO NHAT              |\n");
    printf("+=====+==========================+=====================+\n");
    printf("| STT | Tinh/Thanh               | Tong cuoc (VND)     |\n");
    printf("+=====+==========================+=====================+\n");

    if (first != -1) {
        printf("| %-3d | %-24s | %-19.0lf |\n",
               1,
               stats[first].provinceName,
               stats[first].totalFee);
    }

    if (second != -1) {
        printf("| %-3d | %-24s | %-19.0lf |\n",
               2,
               stats[second].provinceName,
               stats[second].totalFee);
    }

    if (third != -1) {
        printf("| %-3d | %-24s | %-19.0lf |\n",
               3,
               stats[third].provinceName,
               stats[third].totalFee);
    }
    printf("+=====+==========================+=====================+\n");
}

void printProvinceMaxRecord(ProvinceStat stats[], int count, int maxIndex) {
    printf("\n+======================================================+\n");
    printf("|          TINH CO NHIEU THUE BAO NHAT                 |\n");
    printf("+==========================+===========================+\n");
    printf("| Tinh/Thanh               | Tong thue bao            |\n");
    printf("+==========================+===========================+\n");
    printf("| %-24s | %-24d |\n",
           stats[maxIndex].tentinh,
           stats[maxIndex].total);
    printf("+==========================+===========================+\n");
}

void printRecordMaxFee(Node *maxNode, double maxFee) {
    printf("\n+======================================================+\n");
    printf("|          DOANH NGHIEP CO TIEN CUOC CAO NHAT          |\n");
    printf("+================+=====================+===============+\n");
    printf("| CUUUU          | Ten doanh nghiep    | Tong cuoc     |\n");
    printf("+================+=====================+===============+\n");
    printf("| %-14s | %-19s | %-13.0lf |\n",
           maxNode->data.phone,
           maxNode->data.address,
           maxFee);
    printf("+================+=====================+===============+\n");
}

void printBill(Node *p) {
    if (p == NULL) {
        printf("Khong ton tai thue bao!\n");
        return;
    }
    double onNetFee = p->data.onNetMinutes * On_net_rate;
    double offNetFee = p->data.offNetMinutes * Off_net_rate;
    double subtotal = onNetFee + offNetFee;
    double vat = subtotal * VAT;
    double total = total_Fee(p->data);
    printf("\n");
    printf("=====================================================\n");
    printf("                 HOA DON CUOC DIEN THOAI\n");
    printf("=====================================================\n");
    printf("Ten don vi      : %s\n", p->data.name);
    printf("So dien thoai   : %s\n", p->data.phone);
    printf("Tinh/Thanh      : %s\n", p->data.province.tentinh);
    printf("-----------------------------------------------------\n");
    printf("Noi mang        : %4d phut x %d = %.0lf VND\n", p->data.onNetMinutes, On_net_rate, onNetFee);
    printf("Ngoai mang      : %4d phut x %d = %.0lf VND\n", p->data.offNetMinutes, Off_net_rate, offNetFee);
    printf("-----------------------------------------------------\n");
    printf("Tam tinh        : %.0lf VND\n", subtotal);
    printf("VAT (10%%)       : %.0lf VND\n", vat);
    printf("=====================================================\n");
    printf("TONG THANH TOAN : %.0lf VND\n", total);
    printf("=====================================================\n");
}

void menu() {
    printf(CYAN BOLD);
    printf("=======================================================\n");
    printf("       CHUONG TRINH QUAN LY DANH BA DIEN THOAI\n");
    printf("=======================================================\n");
    printf(RESET);
    printf(YELLOW);
    printf("| 1. %-45s |\n", "Them thue bao");
    printf("| 2. %-45s |\n", "Hien thi toan bo danh ba");
    printf("| 3. %-45s |\n", "Tim kiem thue bao");
    printf("| 4. %-45s |\n", "Sua thong tin thue bao");
    printf("| 5. %-45s |\n", "Xoa thue bao");
    printf("| 6. %-45s |\n", "Loc thue bao theo trang thai");
    printf("| 7. %-45s |\n", "Liet ke thue bao theo tinh thanh");
    printf("| 8. %-45s |\n", "Thong ke thue bao");
    printf("| 9. %-45s |\n", "Tinh cuoc thue bao");
    printf("| 10. %-44s |\n", "Kiem tra trung so dien thoai");
    printf("| 11. %-44s |\n", "Doc file du lieu thue bao");
    printf("| 0. %-45s |\n", "Thoat");
    printf(RESET);
    printf("=======================================================\n");
    printf(GREEN BOLD);
    printf("Nhap lua chon cua ban: ");
    printf(RESET);
}

