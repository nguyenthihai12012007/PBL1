#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "print.h"
#include "function.h"
#include "constants.h"

void printSpace(int n) {
    for(int i = 0; i < n; i++) {
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

void showScreen() {
    printf(YELLOW);
    printSpace(65);
    printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
    printSpace(65);
    printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
    printSpace(65);
    printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
    printSpace(65);
    printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
    printSpace(65);
    printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
    printSpace(65);
    printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
    printf(RESET);
    printf("\n");
    printf(BRIGHT_GREEN);
    printSpace(65);
    printf("                  Loading...\n");
    for(int i = 0; i <= 20; i++) {
        printf("\r                                                                                   [");
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
    printSpace(65);
    printf("                  Nhan Enter de tiep tuc...");
    clearInputBuffer();
    //getchar();
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
    printSpace(65);
    printf("   Thoi gian: %02d:%02d:%02d\n",
           local->tm_hour,
           local->tm_min,
           local->tm_sec);

    printf(RESET);
    printf(CYAN BOLD);
    printf("\n");
    printMiddle("+======================================================================+");
    printSpace(65);
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
    printSpace(65);
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

    printSpace(65);
    printf("Ten: %s\n", node->data.name);
    printSpace(65);
    printf("So dien thoai: %s\n", node->data.phone);
    printSpace(65);
    printf("Dia chi: %s\n", node->data.address);
    printSpace(65);
    printf("Tinh: %s\n", node->data.province.tentinh);
    printSpace(65);
    printf("Trang thai: ");
    printStatus(node->data.status);
    printf("\n");
}

void print_account(AccountNode *Node) {
    if(Node == NULL) return ;

    printSpace(65);
    printf("Ten dang nhap: %s\n",Node->A.username);
    printSpace(65);
    printf("Mat khau: %s\n",Node->A.username);
    printSpace(65);
    printf("Chuc vu: %d\n",Node->A.role);
    printf("\n");
}

void printHeader() {
    printMiddle("+-----+-------------------------------------+--------------+----------------------+------------+------------+");
    printSpace(46);
    printf("| %-3s | %-35s | %-12s | %-20s | %-10s | %-10s |\n", "STT", "Ten", "Dien thoai", "Dia chi", "Tinh", "Trang thai");
    printMiddle("+-----+-------------------------------------+--------------+----------------------+------------+------------+");
}

void printRow(int stt, Node* p) {
    char status[20];

    switch (p->data.status) {
        case 1: strcpy(status, "Hoat dong"); break;
        case 2: strcpy(status, "Tam khoa"); break;
        case 3: strcpy(status, "Da huy"); break;
        default: strcpy(status, "Khong ro");
    }

    printSpace(46);
    printf("| %-3d | %-35.35s | %-12s | %-20.20s | %-10.10s | %-10s |\n", stt, p->data.name, p->data.phone, p->data.address, p->data.province.tentinh, status);
}

void printFooter() {
    printMiddle("+-----+-------------------------------------+--------------+----------------------+------------+------------+");
}

void print_all_record(Node *head) {
    if (head == NULL) {
        printSpace(65);
        printf(RED BOLD "   Danh sach rong!\n" RESET);
        return;
    }

    printf("\n");
    printSpace(46);
    printf("                                             DANH SACH DANH BA\n");
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
    printSpace(65);
    printf("+======================================================================+\n");
    printSpace(65);
    printf("|                     TOP 3 TINH CO CUOC CAO NHAT                      |\n");
    printSpace(65);
    printf("+=====+=========================================+======================+\n");
    printSpace(65);
    printf("| STT | Tinh/Thanh                              |    Tong cuoc (VND)   |\n");
    printSpace(65);
    printf("+=====+=========================================+======================+\n");

    if (first != -1) {
        printSpace(65);
        printf("| %-3d | %-39s | %-20.0lf |\n",
               1,
               stats[first].provinceName,
               stats[first].totalFee);
    }

    if (second != -1) {
        printSpace(65);
        printf("| %-3d | %-39s | %-20.0lf |\n",
               2,
               stats[second].provinceName,
               stats[second].totalFee);
    }

    if (third != -1) {
        printSpace(65);
        printf("| %-3d | %-39s | %-20.0lf |\n",
               3,
               stats[third].provinceName,
               stats[third].totalFee);
    }
    printSpace(65);
    printf("+=====+=========================================+======================+\n");
}

void printProvinceMaxRecord(ProvinceStat stats[], int count, int maxIndex) {
    printf("\n");
    printSpace(79);
    printf("+===========================================+\n");
    printSpace(79);
    printf("|        TINH CO NHIEU THUE BAO NHAT        |\n");
    printSpace(79);
    printf("+===========================================+\n");
    printSpace(79);
    printf("| Tinh thanh  : %-27s |\n", stats[maxIndex].province_name);
    printSpace(79);
    printf("| So thue bao : %-27d |\n", stats[maxIndex].total);
    printSpace(79);
    printf("+===========================================+\n");
}

void printTop3RecordMaxFee(CompanyFee stats[], int limit) {
    printf("\n");
    printSpace(65);
    printf("+======================================================================+\n");
    printSpace(65);
    printf("|              TOP 3 DOANH NGHIEP CO TIEN CUOC CAO NHAT                |\n");
    printSpace(65);
    printf("+=====+=========================================+======================+\n");
    printSpace(65);
    printf("| STT |            Ten doanh nghiep             |    Tong cuoc (VND)   |\n");
    printSpace(65);
    printf("+=====+=========================================+======================+\n");
    for (int i = 0; i < limit; i++) {
        printSpace(65);
        printf("| %-3d | %-39s | %-20.0lf |\n", i+1, stats[i].companyName, stats[i].totalFee);
    }
    printSpace(65);
    printf("+=====+=========================================+======================+\n");
}

void printBill(Node *p) {
    if (p == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong ton tai thue bao!\n" RESET);
        return;
    }
    double onNetFee = p->data.onNetMinutes * On_net_rate;
    double offNetFee = p->data.offNetMinutes * Off_net_rate;
    double subtotal = onNetFee + offNetFee;
    double vat = subtotal * VAT;
    double total = total_Fee(p->data);
    printf("\n");
    printSpace(65);
    printf("=====================================================\n");
    printSpace(65);
    printf("                 HOA DON CUOC DIEN THOAI\n");
    printSpace(65);
    printf("=====================================================\n");
    printSpace(65);
    printf("Ten don vi      : %s\n", p->data.name);
    printSpace(65);
    printf("So dien thoai   : %s\n", p->data.phone);
    printSpace(65);
    printf("Tinh/Thanh      : %s\n", p->data.province.tentinh);
    printSpace(65);
    printf("-----------------------------------------------------\n");
    printSpace(65);
    printf("Noi mang        : %4d phut x %d = %.0lf VND\n", p->data.onNetMinutes, On_net_rate, onNetFee);
    printSpace(65);
    printf("Ngoai mang      : %4d phut x %d = %.0lf VND\n", p->data.offNetMinutes, Off_net_rate, offNetFee);
    printSpace(65);
    printf("-----------------------------------------------------\n");
    printSpace(65);
    printf("Tam tinh        : %.0lf VND\n", subtotal);
    printSpace(65);
    printf("VAT (10%%)       : %.0lf VND\n", vat);
    printSpace(65);
    printf("=====================================================\n");
    printSpace(65);
    printf("TONG THANH TOAN : %.0lf VND\n", total);
    printSpace(65);
    printf("=====================================================\n");
}

void revenueStatistics(Node *head) {
    if (head == NULL) {
        printSpace(65);
        printf(RED BOLD "\nDanh sach thue bao rong!\n" RESET);
        return;
    }

    int month, year;

    printf("\n");
    printSpace(65);
    printf("Nhap thang: ");
    scanf("%d", &month);

    printSpace(65);
    printf("Nhap nam: ");
    scanf("%d", &year);

    clearScreen();

    printf(CYAN BOLD);
    printSpace(65);
    printf("+======================================================================+\n");
    printSpace(65);
    printf("|                                                                      |\n");
    printSpace(65);
    printf("|                         THONG KE DOANH THU                           |\n");
    printSpace(65);
    printf("|                                                                      |\n");
    printSpace(65);
    printf("+======================================================================+\n");
    printf(RESET);

    int ok = revenue(head, month, year);
    
    if (!ok) {
        return;
    }

    printf(YELLOW BOLD);
    printf("\n");
    printSpace(65);
    printf("+----------------------------------------------------------------------+\n");
    printSpace(65);
    printf("| [1] DOANH THU CUA THANG                                              |\n");
    printSpace(65);
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    printf(YELLOW BOLD);
    printf("\n");
    printSpace(65);
    printf("+----------------------------------------------------------------------+\n");
    printSpace(65);
    printf("| [2] TOP 3 DOANH NGHIEP CO TIEN CUOC CAO NHAT                         |\n");
    printSpace(65);
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    top3RecordMaxFee(head, month, year);

    printf(YELLOW BOLD);
    printf("\n");
    printSpace(65);
    printf("+----------------------------------------------------------------------+\n");
    printSpace(65);
    printf("| [3] TOP 3 TINH CO TIEN CUOC CAO NHAT                                 |\n");
    printSpace(65);
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    top3ProvinceByFee(head, month, year);

    printf(CYAN BOLD);
    printf("\n");
    printSpace(65);
    printf("+======================================================================+\n");
    printSpace(65);
    printf("|                         HOAN TAT THONG KE                            |\n");
    printSpace(65);
    printf("+======================================================================+\n");
    printf(RESET);

    getchar();
}

void showHistory() {
    FILE *f = fopen("history.txt", "r");

    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Chua co lich su thao tac!\n" RESET);
        return;
    }

    char line[300];
    int found = 0;

    printf("\n");
    printSpace(65);
    printf(BLUE BOLD "====================== LICH SU THAO TAC ======================\n" RESET);

    while (fgets(line, sizeof(line), f) != NULL) {
        printSpace(65);
        printf("%s", line);
        found = 1;
    }

    if (found == 0) {
        printSpace(65);
        printf("Chua co lich su thao tac!\n");
    }

    printSpace(65);
    printf(BLUE BOLD "===============================================================\n" RESET);
    endScreen();

    fclose(f);
}