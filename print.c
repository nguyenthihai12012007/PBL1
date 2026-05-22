#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "print.h"
#include "function.h"
#include "constants.h"

void printSpace() {
    for(int i = 0; i < 65; i++) {
        printf(" ");
    }
}

void printCenter(const char *text, int width) {
    int len = strlen(text);
    int left = (width - len) / 2;
    printf("|");
    for (int i = 0; i < left; i++) {
        printf(" ");
    }
    printf("%s", text);
    for (int i = left + len; i < width; i++) {
        printf(" ");
    }
    printf("|\n");
}

void printMiddle(const char *text) {
    int len = strlen(text);
    int left = (WIDTH - len) / 2;

    for(int i = 0; i < left; i++) {
        printf(" ");
    }

    printf("%s\n", text);
}

void printSystemHeader(const char *title) {
    clearScreen();
    printf(BLUE BOLD);
    printMiddle("+======================================================================+");
    printMiddle("|                                                                      |");
    printMiddle("|                 HE THONG QUAN LY DANH BA DIEN THOAI                  |");
    printMiddle("|                                                                      |");
    printMiddle("+======================================================================+");
    printf(RESET);
    time_t t;
    time(&t);
    struct tm *local = localtime(&t);
    printf(YELLOW);
    printf("\n");
    printSpace();
    printf("   Thoi gian: %02d:%02d:%02d\n",
           local->tm_hour,
           local->tm_min,
           local->tm_sec);

    printf(RESET);
    printf(CYAN BOLD);
    printf("\n");
    printMiddle("+======================================================================+");
    printSpace();
    printCenter(title, 70);
    printMiddle("+======================================================================+");
    printf(RESET);
}

void printSystemFooter() {
    printf(CYAN BOLD);
    printMiddle("+======================================================================+");
    printf(RESET);
    printf(GREEN BOLD);
    printf("\n");
    printSpace();
    printf("   Nhap lua chon cua ban: ");
    printf(RESET);
}

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

    printSpace();
    printf("Ten: %s\n", node->data.name);
    printSpace();
    printf("So dien thoai: %s\n", node->data.phone);
    printSpace();
    printf("Dia chi: %s\n", node->data.address);
    printSpace();
    printf("Tinh: %s\n", node->data.province.tentinh);
    printSpace();
    printf("Trang thai: ");
    printStatus(node->data.status);
    printf("\n");
}

void print_account(AccountNode *Node) {
    if(Node == NULL) return ;

    printSpace();
    printf("Ten dang nhap: %s\n",Node->A.username);
    printSpace();
    printf("Mat khau: %s\n",Node->A.username);
    printSpace();
    printf("Chuc vu: %d\n",Node->A.role);
    printf("\n");
}

void printHeader() {
    printSpace();
    printf("+-----+-------------------------------------+--------------+----------------------+------------+------------+\n");
    printSpace();
    printf("| %-3s | %-35s | %-12s | %-20s | %-10s | %-10s |\n", "STT", "Ten", "Dien thoai", "Dia chi", "Tinh", "Trang thai");
    printSpace();
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

    printSpace();
    printf("| %-3d | %-35.35s | %-12s | %-20.20s | %-10.10s | %-10s |\n", stt, p->data.name, p->data.phone, p->data.address, p->data.province.tentinh, status);
}

void printFooter() {
    printSpace();
    printf("+-----+-------------------------------------+--------------+----------------------+------------+------------+\n");
}

void displayAll(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    printSpace();
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

    printf("\n");
    printSpace();
    printf("+======================================================+\n");
    printSpace();
    printf("|             TOP 3 TINH CO CUOC CAO NHAT              |\n");
    printSpace();
    printf("+=====+==========================+=====================+\n");
    printSpace();
    printf("| STT | Tinh/Thanh               | Tong cuoc (VND)     |\n");
    printSpace();
    printf("+=====+==========================+=====================+\n");

    if (first != -1) {
        printSpace();
        printf("| %-3d | %-24s | %-19.0lf |\n",
               1,
               stats[first].provinceName,
               stats[first].totalFee);
    }

    if (second != -1) {
        printSpace();
        printf("| %-3d | %-24s | %-19.0lf |\n",
               2,
               stats[second].provinceName,
               stats[second].totalFee);
    }

    if (third != -1) {
        printSpace();
        printf("| %-3d | %-24s | %-19.0lf |\n",
               3,
               stats[third].provinceName,
               stats[third].totalFee);
    }
    printSpace();
    printf("+=====+==========================+=====================+\n");
}

void printProvinceMaxRecord(ProvinceStat stats[], int count, int maxIndex) {
    printf("\n");
    printSpace();
    printf("+===========================================+\n");
    printSpace();
    printf("|        TINH CO NHIEU THUE BAO NHAT        |\n");
    printSpace();
    printf("+===========================================+\n");
    printSpace();
    printf("| Tinh thanh  : %-27s |\n", stats[maxIndex].province_name);
    printSpace();
    printf("| So thue bao : %-27d |\n", stats[maxIndex].total);
    printSpace();
    printf("+===========================================+\n");
}

void printTop3RecordMaxFee(CompanyFee stats[], int limit) {
    printf("\n");
    printSpace();
    printf("+=============================================================+\n");
    printSpace();
    printf("|          TOP 3 DOANH NGHIEP CO TIEN CUOC CAO NHAT           |\n");
    printSpace();
    printf("+=====+=====================================+=================+\n");
    printSpace();
    printf("| STT |          Ten doanh nghiep           | Tong cuoc (VND) |\n");
    printSpace();
    printf("+=====+=====================================+=================+\n");
    for (int i = 0; i < limit; i++) {
        printSpace();
        printf("| %-3d | %-35s | %-15.0lf |\n", i+1, stats[i].companyName, stats[i].totalFee);
    }
    printSpace();
    printf("+=====+=====================================+=================+\n");
}

void printBill(Node *p) {
    if (p == NULL) {
        printSpace();
        printf(RED BOLD "Khong ton tai thue bao!\n" RESET);
        return;
    }
    double onNetFee = p->data.onNetMinutes * On_net_rate;
    double offNetFee = p->data.offNetMinutes * Off_net_rate;
    double subtotal = onNetFee + offNetFee;
    double vat = subtotal * VAT;
    double total = total_Fee(p->data);
    printf("\n");
    printSpace();
    printf("=====================================================\n");
    printSpace();
    printf("                 HOA DON CUOC DIEN THOAI\n");
    printSpace();
    printf("=====================================================\n");
    printSpace();
    printf("Ten don vi      : %s\n", p->data.name);
    printSpace();
    printf("So dien thoai   : %s\n", p->data.phone);
    printSpace();
    printf("Tinh/Thanh      : %s\n", p->data.province.tentinh);
    printSpace();
    printf("-----------------------------------------------------\n");
    printSpace();
    printf("Noi mang        : %4d phut x %d = %.0lf VND\n", p->data.onNetMinutes, On_net_rate, onNetFee);
    printSpace();
    printf("Ngoai mang      : %4d phut x %d = %.0lf VND\n", p->data.offNetMinutes, Off_net_rate, offNetFee);
    printSpace();
    printf("-----------------------------------------------------\n");
    printSpace();
    printf("Tam tinh        : %.0lf VND\n", subtotal);
    printSpace();
    printf("VAT (10%%)       : %.0lf VND\n", vat);
    printSpace();
    printf("=====================================================\n");
    printSpace();
    printf("TONG THANH TOAN : %.0lf VND\n", total);
    printSpace();
    printf("=====================================================\n");
}


void showScreen() {
    printf(YELLOW);
    printSpace();
    printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
    printSpace();
    printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
    printSpace();
    printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
    printSpace();
    printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
    printSpace();
    printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
    printSpace();
    printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
    printf(RESET);
    printf("\n");
    printf(BRIGHT_GREEN);
    printSpace();
    printf("                   Loading...\n");
    for(int i = 0; i <= 20; i++) {
        printf("\r                                                                                    [");
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
    printf("\n\n");
    printSpace();
    printf("                   Nhan Enter de tiep tuc...");
    clearInputBuffer();
    //getchar();
}

void revenueStatistics(Node *head) {
    if (head == NULL) {
        printSpace();
        printf(RED BOLD "\nDanh sach thue bao rong!\n" RESET);
        return;
    }

    clearScreen();

    printf(CYAN BOLD);
    printSpace();
    printf("+======================================================================+\n");
    printSpace();
    printf("|                                                                      |\n");
    printSpace();
    printf("|                         THONG KE DOANH THU                           |\n");
    printSpace();
    printf("|                                                                      |\n");
    printSpace();
    printf("+======================================================================+\n");
    printf(RESET);

    printf(YELLOW BOLD);
    printf("\n");
    printSpace();
    printf("+----------------------------------------------------------------------+\n");
    printSpace();
    printf("| [1] DOANH THU CUA THANG                                              |\n");
    printSpace();
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    printf(GREEN);
    revenue(head);
    printf(RESET);

    printf(YELLOW BOLD);

    printf("\n");
    printSpace();
    printf("+----------------------------------------------------------------------+\n");
    printSpace();
    printf("| [2] TOP 3 DOANH NGHIEP CO TIEN CUOC CAO NHAT                         |\n");
    printSpace();
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    top3RecordMaxFee(head);

    printf(YELLOW BOLD);
    printf("\n");
    printSpace();
    printf("+----------------------------------------------------------------------+\n");
    printSpace();
    printf("| [3] TOP 3 TINH CO TIEN CUOC CAO NHAT                                 |\n");
    printSpace();
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    printTop3ProvinceByFee(head);

    printf(CYAN BOLD);
    printf("\n");
    printSpace();
    printf("+======================================================================+\n");
    printSpace();
    printf("|                         HOAN TAT THONG KE                            |\n");
    printSpace();
    printf("+======================================================================+\n");
    printf(RESET);

    getchar();
}
