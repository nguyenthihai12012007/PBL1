#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "print.h"
#include "function.h"
#include "constants.h"

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

void print_account(AccountNode *Node) {
    if(Node == NULL) return ;

    printf("Ten dang nhap: %s\n",Node->A.username);
    printf("Mat khau: %s\n",Node->A.username);
    printf("Chuc vu: %d\n",Node->A.role);
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
    printf("\n+===========================================+\n");
    printf("|        TINH CO NHIEU THUE BAO NHAT        |\n");
    printf("+===========================================+\n");
    printf("| Tinh thanh  : %-27s |\n", stats[maxIndex].province_name);
    printf("| So thue bao : %-27d |\n", stats[maxIndex].total);
    printf("+===========================================+\n");
}

void printTop3RecordMaxFee(CompanyFee stats[], int limit) {
    printf("\n+=============================================================+\n");
    printf("|          TOP 3 DOANH NGHIEP CO TIEN CUOC CAO NHAT           |\n");
    printf("+=====+=====================================+=================+\n");
    printf("| STT |          Ten doanh nghiep           | Tong cuoc (VND) |\n");
    printf("+=====+=====================================+=================+\n");
    for (int i = 0; i < limit; i++) {
        printf("| %-3d | %-35s | %-15.0lf |\n", i+1, stats[i].companyName, stats[i].totalFee);
    }
    printf("+=====+=====================================+=================+\n");
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

void showScreen() {
    printf(YELLOW);
    printf("                ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
    printf("                ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
    printf("                ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
    printf("                ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
    printf("                ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
    printf("                 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
    printf(RESET);
    printf("\n");
    printf(BRIGHT GREEN);
    printf("                                   Loading...\n");
    for(int i = 0; i <= 20; i++) {
        printf("\r                                   [");
        for(int j = 0; j < i; j++) {
            printf("█");
        }
        for(int j = i; j < 20; j++) {
            printf(" ");
        }
        printf("] %d%%", i * 5);
        fflush(stdout);
        usleep(150000);
    }
    printf(RESET);
    printf("\n");
    printf("                                   Nhan Enter de tiep tuc...");
    getchar();
}
