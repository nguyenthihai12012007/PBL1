#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "function.h"
#include "menu.h"
#include "print.h"
#include "record.h"
#include "constants.h"

Node* createNode(Record R) {
    Node* newNode = (Node*)malloc (sizeof(Node));
    if(newNode == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong du bo nho!\n" RESET);
        exit(1);
    }
    newNode->data = R;
    newNode->next = NULL;
    return newNode;
}

AccountNode *createAccountNode(Account A) {
    AccountNode *newNode = (AccountNode *)malloc(sizeof(AccountNode));

    if (newNode == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong du bo nho!\n" RESET);
        return NULL;
    }

    newNode->A = A;
    newNode->next = NULL;

    return newNode;
}

AreaCode areaCodes[] = {
    {"an giang", "0901"},
    {"ba ria vung tau", "0902"},
    {"bac giang", "0903"},
    {"bac kan", "0904"},
    {"bac lieu", "0905"},
    {"bac ninh", "0906"},
    {"ben tre", "0907"},
    {"binh dinh", "0908"},
    {"binh duong", "0909"},
    {"binh phuoc", "0910"},

    {"binh thuan", "0911"},
    {"ca mau", "0912"},
    {"can tho", "0913"},
    {"cao bang", "0914"},
    {"da nang", "0943"},
    {"dak lak", "0916"},
    {"dak nong", "0917"},
    {"dien bien", "0918"},
    {"dong nai", "0919"},
    {"dong thap", "0920"},

    {"gia lai", "0921"},
    {"ha giang", "0922"},
    {"ha nam", "0923"},
    {"ha noi", "0924"},
    {"ha tinh", "0925"},
    {"hai duong", "0926"},
    {"hai phong", "0927"},
    {"hau giang", "0928"},
    {"hoa binh", "0929"},
    {"hue", "0975"},

    {"hung yen", "0931"},
    {"khanh hoa", "0932"},
    {"kien giang", "0933"},
    {"kon tum", "0934"},
    {"lai chau", "0935"},
    {"lam dong", "0936"},
    {"lang son", "0937"},
    {"lao cai", "0938"},
    {"long an", "0939"},
    {"nam dinh", "0940"},

    {"nghe an", "0941"},
    {"ninh binh", "0942"},
    {"ninh thuan", "0944"},
    {"phu tho", "0945"},
    {"phu yen", "0946"},
    {"quang binh", "0947"},
    {"quang nam", "0948"},
    {"quang ngai", "0949"},
    {"quang ninh", "0950"},
    {"quang tri", "0951"},

    {"soc trang", "0952"},
    {"son la", "0953"},
    {"tay ninh", "0954"},
    {"thai binh", "0955"}
};

void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int validatePhone(char phone[]) {
    int len = strlen(phone);

    if (len != 10) {
        return 0;
    }

    if (phone[0] != '0') {
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int validateLastSix(char phone[]) {
    int len = strlen(phone);
    if (len != 6) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (phone[i] < '0' || phone[i] > '9') 
        return 0;
    }
    return 1;
}

int validateInput(char str[]) {
    int len = strlen(str);
    if (len == 0)
        return 0;
    int space = 1;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            space = 0;
            break;
        }
    }
    if(space)
        return 0;
    return 1;
}

int areaCodeCount = sizeof(areaCodes)/sizeof(areaCodes[0]);

char* findPrefixByProvince(char tentinh[]) {
    for(int i=0; i < areaCodeCount; i++) {
        if (strcmp(tentinh,areaCodes[i].province) == 0) {
            return areaCodes[i].prefix;
        }
    }
    return NULL;
}

void updatePhoneAreaCode(Record *R) {
    char last[20];
    char *prefix = findPrefixByProvince(R->province.tentinh);

    strcpy(last, R->phone + 4);

    strcpy(R->phone, prefix);
    strcat(R->phone, last);
}

void loadAccountsToList(const char *filename, AccountNode **head) {
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong mo duoc file account.txt!\n" RESET);
        return;
    }

    Account A;

    while (fscanf(f, "%[^|]|%[^|]|%d\n",
                  A.username,
                  A.password,
                  &A.role) == 3) {

        AccountNode *newNode = createAccountNode(A);

        if (newNode == NULL) {
            fclose(f);
            return;
        }

        if (*head == NULL) {
            *head = newNode;
        } else {
            AccountNode *p = *head;

            while (p->next != NULL) {
                p = p->next;
            }

            p->next = newNode;
        }
    }

    fclose(f);
}

int login(AccountNode *head,char currentUsername[]) {
    char username[30];
    char password[50];

    do {
        clearScreen();

        printf(BLUE BOLD);
        printMiddle("+======================================================================+");
        printMiddle("|                                                                      |");
        printMiddle("|                 HE THONG QUAN LY DANH BA DIEN THOAI                  |");
        printMiddle("|                                                                      |");
        printMiddle("+======================================================================+");
        printf(RESET);
        printSpace(65);
        printf(BLUE BOLD "|" RESET BRIGHT_RED "                         SINH VIEN THUC HIEN                          " RESET BLUE BOLD "|\n" RESET);
        printSpace(65);
        printf(BLUE BOLD "|" RESET BRIGHT_PURPLE " 1. Tran Nguyen Nhu Hoa - 102250015                                   " RESET BLUE BOLD "|\n" RESET);
        printSpace(65);
        printf(BLUE BOLD "|" RESET BRIGHT_PURPLE " 2. Nguyen Thi Hai      - 102250011                                   " RESET BLUE BOLD "|\n" RESET);
        printSpace(65);
        printf(BLUE BOLD "|" RESET GREEN BOLD " Lop: 25T_DT1                                                         " RESET BLUE BOLD "|\n" RESET);
        printSpace(65);
        printf(BLUE BOLD "|" RESET RED BOLD " Giang vien huong dan: ĐỖ THỊ TUYẾT HOA                               " RESET BLUE BOLD "|\n" RESET);
        printf(BLUE BOLD);
        printMiddle("+======================================================================+");
        printf(RESET);

        printf(CYAN BOLD);
        printf("\n");
        printMiddle("+----------------------------------+");
        printMiddle("|        DANG NHAP HE THONG        |");
        printMiddle("+----------------------------------+");
        printf(RESET);

        printSpace(65);
        printf("                    Ten dang nhap : ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printSpace(65);
        printf("                    Mat khau      : ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        printf(CYAN BOLD);
        printMiddle("+----------------------------------+");
        printf(RESET);

        AccountNode *p = head;

        while (p != NULL) {
            if (strcmp(username, p->A.username) == 0 &&
                strcmp(password, p->A.password) == 0) {

                strcpy(currentUsername, p->A.username);

                if (p->A.role == ROLE_ADMIN) {
                    printf("\n");
                    printSpace(65);
                    printf(GREEN BOLD "   Dang nhap thanh cong!\n");
                    printSpace(65);
                    printf(GREEN BOLD "   Xin chao admin : %s\n\n" RESET, currentUsername);
                    return ROLE_ADMIN;
                } else if (p->A.role == ROLE_STAFF) {
                    printf("\n");
                    printSpace(65);
                    printf(GREEN BOLD "   Dang nhap thanh cong!\n");
                    printSpace(65);
                    printf(GREEN BOLD "   Xin chao nhan vien : %s\n\n" RESET, currentUsername);
                    return ROLE_STAFF;
                }
            }

            p = p->next;
        }

        printf("\n");
        printSpace(65);
        printf(RED BOLD "   Sai ten dang nhap hoac mat khau. Vui long dang nhap lai!\n" RESET);
        pauseScreen();

    } while (1);
}

void writeHistory(char username[], char action[], char target[], char detail[]) {
    FILE *f = fopen("history.txt", "a+");

    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong the mo file history.txt!\n" RESET);
        return;
    }

    rewind(f);

    if (fgetc(f) == EOF) {
        fprintf(f,
        "======================================================================================================================================================================\n");
        fprintf(f, "| %-19s | %-9s | %-15s | %-10s | %-99s |\n", "Thoi gian", "Tai khoan", "Hanh dong", "Doi tuong", "Chi tiet");
        fprintf(f,
        "======================================================================================================================================================================\n");
    }

    fseek(f, 0, SEEK_END);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(f, "| %02d/%02d/%04d %02d:%02d:%02d |",
            t->tm_mday,
            t->tm_mon + 1,
            t->tm_year + 1900,
            t->tm_hour,
            t->tm_min,
            t->tm_sec);

    fprintf(f, " %-9.9s | %-15.15s | %-10.10s | %-99.99s |\n",
            username,
            action,
            target,
            detail);

    fclose(f);
}

void addRecordByUser(Node** head, Record R, char currentUsername[]) {
    Node* newNode = createNode(R);

    if (newNode == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong du bo nho de them thue bao!\n" RESET);
        return;
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* p = *head;

        while (p->next != NULL) {
            p = p->next;
        }

        p->next = newNode;
    }

    writeHistory(currentUsername,
                 "Them thue bao",
                 newNode->data.phone,
                 "Them thue bao moi vao he thong");
}

void addRecordByFile(Node** head, Record R) {
    Node* newNode = createNode(R);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
    
}

void readFile(const char *filename, Node **head,char currentUsername[]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("\n");
        printSpace(65);
        printf(RED BOLD "Khong mo duoc file!\n" RESET);
        return;
    }

    char line[300];
    int valid = 0, invalid = 0;

    while(fgets(line, sizeof(line),f) != NULL) {
        line[strcspn(line,"\n")] = '\0';

        //bỏ qua dong trong
        if (strlen(line) == 0) {
            continue;
        }

        Record temp;
        char *token = strtok(line,"|");

        if (token == NULL || !validateInput(token)) {
            invalid++;
            continue;
        }
        strcpy(temp.province.tentinh,token);

        token = strtok(NULL,"|");
        if (token == NULL || !validateInput(token)) {
            invalid++;
            continue;
        }
        strcpy(temp.name,token);

        token = strtok(NULL,"|");
        if (token == NULL || !validateInput(token)) {
            invalid++;
            continue;
        }
        strcpy(temp.address,token);

        token = strtok(NULL, "|");
        if (token == NULL || !validatePhone(token)) {
            invalid++;
            continue;
        }
        strcpy(temp.phone, token);
        
        token = strtok(NULL, "|");
        if (token == NULL) {
            invalid++;
            continue;
        }

        temp.status = atoi(token);
        if (temp.status < 1 || temp.status > 3) {
            invalid++;
            continue;
        }

        token = strtok(NULL, "|"); 
        if (token == NULL) {
            invalid++;
            continue;
        }
        temp.onNetMinutes = atoi(token);

        if (temp.onNetMinutes < 0) {
            invalid++;
            continue;
        }

        token = strtok(NULL, "|"); 
        if (token == NULL) {
            invalid++;
            continue;
        }
        temp.offNetMinutes = atoi(token);

        if (temp.offNetMinutes < 0) {
            invalid++;
            continue;
        }
        addRecordByFile(head, temp);
        valid++;
    }

    fclose(f);
    printf("\n");
    printSpace(65);
    printf("Doc du lieu thanh cong!\n");
    printSpace(65);
    printf("So thue bao doc vao: %d dong\n", valid + invalid);
    printSpace(65);
    printf("Hop le: %d dong\n", valid);
    printSpace(65);
    printf("Khong hop le: %d dong\n", invalid);
}

void saveAccountToFile(const char *filename,AccountNode *head) {
    FILE *f = fopen(filename, "w");

    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong mo duoc file de ghi!\n" RESET);
        return;
    }

    AccountNode *p = head;

    while(p != NULL) {
        fprintf(f, "%s|%s|%d\n",p->A.username,p->A.password,p->A.role);
        p = p->next;
    }

    fclose(f);
}

void saveRecordToFile(const char *filename, Node *head) {
    FILE *f = fopen(filename, "w");

    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong mo duoc file de ghi!\n" RESET);
        return;
    }

    Node *p = head;

    while (p != NULL) {
        fprintf(f, "%s|%s|%s|%s|%d|%d|%d\n",
                p->data.province.tentinh,
                p->data.name,
                p->data.address,
                p->data.phone,
                p->data.status,
                p->data.onNetMinutes,
                p->data.offNetMinutes);
        p = p->next;
    }

    fclose(f);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pauseScreen() {
    printf("\n");
    printSpace(65);
    printf("Nhan Enter de tiep tuc...");
    clearInputBuffer();
    getchar(); 
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void endScreen() {
    pauseScreen();
    clearScreen();
}

int inputStatus() {
    int choice;
    do {
        printSpace(65);
        printf("Chon trang thai thue bao:\n");
        printSpace(65);
        printf("1. Dang hoat dong\n");
        printSpace(65);
        printf("2. Tam khoa\n");
        printSpace(65);
        printf("3. Da huy\n");
        printSpace(65);
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 3) {
            printSpace(65);
            printf(RED BOLD "Lua chon khong hop le! Vui long nhap lai! \n\n" RESET);
        }
    } while (choice < 1 || choice > 3);

    return choice;
}

Account inputAccount() {
    Account A;
    clearInputBuffer();

    printf("\n");
    printSpace(65);
    printf("Nhap ten dang nhap: ");
    scanf("%s", A.username);
    getchar();

    printSpace(65);
    printf("Nhap mat khau: ");
    scanf("%s", A.password);
    getchar();

    printf("\n");
    printSpace(65);
    printf("  Chon chuc vu\n");
    printSpace(65);
    printf("----------------\n");
    printSpace(65);
    printf("| 1. Admin     |\n");
    printSpace(65);
    printf("| 2. Nhan vien |\n");
    printSpace(65);
    printf("----------------\n");
    int role;
    printSpace(65);
    printf("Nhap lua chon: ");
    do {
        if (scanf("%d", &role) != 1) {
            printSpace(65);
            printf(RED BOLD "Loi: Vui long chi nhap chu so! Nhap lai: " RESET);
            while(getchar() != '\n');
            role = -1;
            continue;
        }
        if(role != ROLE_ADMIN && role != ROLE_STAFF) {
            printSpace(65);
            printf(RED BOLD "Lua chon khong hop le! Nhap lai: " RESET);
        }

    } while(role != ROLE_ADMIN && role != ROLE_STAFF);
    A.role = role;
    while(getchar() != '\n');
    return A;
}

void addAccount(AccountNode **head,char currentUsername[]) {
    Account A = inputAccount();

    AccountNode *newNode = createAccountNode(A);

    if (newNode == NULL) {
        return;
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        AccountNode *p = *head;

        while (p->next != NULL) {
            p = p->next;
        }

        p->next = newNode;
    }

    saveAccountToFile("account.txt", *head);
    printf("\n");
    printSpace(65);
    printf(GREEN BOLD "Them tai khoan thanh cong!\n" RESET);
}

Record inputRecord() {
    Record R;
    clearInputBuffer();

    char lastSix[20];
    char* prefix = NULL;
    
    printf("\n");
    printSpace(65);
    printf("Nhap tinh cua thue bao: ");
    do {
        fgets(R.province.tentinh, sizeof(R.province.tentinh), stdin);
        R.province.tentinh[strcspn(R.province.tentinh, "\n")] = '\0';

        toLowerCase(R.province.tentinh);

        if(!validateInput(R.province.tentinh)) {
            printSpace(65);
            printf(RED BOLD "Tinh khong hop le! Vui long nhap lai: " RESET);
            continue;
        }

        prefix = findPrefixByProvince(R.province.tentinh);

        if(prefix == NULL) {
            printSpace(65);
            printf(RED BOLD "Tinh khong co trong danh sach ma vung! Nhap lai: " RESET);
        }
    } while(!validateInput(R.province.tentinh) || prefix == NULL);

    printSpace(65);
    printf("Nhap 6 so cuoi cua thue bao: ");
    do {
        scanf("%s", lastSix);

        if(!validateLastSix(lastSix)) {
            printSpace(65);
            printf(RED BOLD "So dien thoai khong hop le! Vui long nhap lai: " RESET);
        }
    } while(!validateLastSix(lastSix));

    strcpy(R.phone, prefix);
    strcat(R.phone, lastSix);

    printf("\n");
    printSpace(65);
    printf(GREEN BOLD "So dien thoai duoc tao: %s\n" RESET, R.phone);
    getchar();

    printSpace(65);
    printf("Nhap ten don vi: ");

    do {
        fgets(R.name, sizeof(R.name), stdin);
        R.name[strcspn(R.name, "\n")] = '\0';

        if(!validateInput(R.name)) {
            printSpace(65);
            printf(RED BOLD "Ten khong hop le! Vui long nhap lai: " RESET);
        }

    } while(!validateInput(R.name));

    printSpace(65);
    printf("Nhap dia chi thue bao: ");
    do {
        fgets(R.address,sizeof(R.address),stdin);
        R.address[strcspn(R.address,"\n")]='\0';
        if(!validateInput(R.address)) {
            printSpace();
            printf(RED BOLD "Dia chi khong hop le! Vui long nhap lai.\n" RESET);
        }
    } while(!validateInput(R.address));

    R.status = inputStatus();

    printSpace(65);
    printf("Nhap so phut noi mang: ");
    do {
        scanf("%d", &R.onNetMinutes);
        if (R.onNetMinutes < 0) {
            printSpace();
            printf(RED BOLD "So phut khong hop le! Nhap lai: " RESET);
        }
    } while (R.onNetMinutes < 0);

    printSpace(65);
    printf("Nhap so phut ngoai mang: ");
    do {
        scanf("%d", &R.offNetMinutes);
        if (R.offNetMinutes < 0) {
            printSpace();
            printf(RED BOLD "So phut khong hop le! Nhap lai: " RESET);
        }
    } while (R.offNetMinutes < 0);

    return R;
}

int isSimilarPhone(char inputPhone[],char phone[]) {
    if(strlen(phone) != strlen(inputPhone)) {
        return 0;
    }

    int diff = 0;

    for(int i=0; i<strlen(phone); i++) {
        if(inputPhone[i] != phone[i]) {
            diff++;
        }

        if(diff > 1) {
            return 0;
        }
    }
    return diff == 1;
}

void suggestSimilarPhone(Node *head, char inputPhone[]) {
    Node* p = head;
    int found = 0;

    while(p != NULL) {
        if (isSimilarPhone(p->data.phone,inputPhone) == 1) {
            printf("\n");
            print_record(p);
            found = 1;
        }
        p = p->next;
    }

    if(found == 0) {
        printSpace(65);
        printf("Khong co goi y phu hop!\n");
    }
}

Node* suggestSimilarPhoneForUpdate(Node *head,char inputPhone[],int check ) {
    Node* p = head;
    char choice;
    check = 0;

    while(p != NULL) {
        if(isSimilarPhone(p->data.phone,inputPhone) == 1) {
            printf("\n");
            print_record(p);
            printSpace(65);
            printf("Day co phai la thue bao ban muon tim? (y/n): ");
            scanf(" %c",&choice);
            getchar();

            if(choice == 'Y' || choice == 'y') {
            check = 1;
            return p;
            }
        }
        p = p->next;
    }
    printSpace(65);
    return NULL;
}

Node* search_record(Node* head,char phone[15]) {
    if(head == NULL) {
        printf("\n");
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return NULL;
    }

    Node* cur = head;

    while(cur!=NULL) {
        if(strcmp(cur->data.phone,phone)==0){
            printSpace(65);
            printf("Da tim thay thue bao!\n\n");
            return cur;
        }
        cur=cur->next;
    }
    return NULL;
}

AccountNode* search_account(AccountNode *head,char userName[30]) {
    if(head == NULL) {
        return NULL;
    }

    AccountNode *cur = head;

    while(cur !=  NULL) {
        if(strcmp(cur->A.username,userName) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void updateAccount(AccountNode *head,char currentUsername[]) {
    if(head == NULL) {
        printf("\n");
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return ;
    }

    char userName[30];
    AccountNode* found = NULL;

    do {
        printf("\n");
        printSpace(65);
        printf("Nhap tai khoan can sua: ");
        scanf("%s",userName);
        found = search_account(head,userName);
        if(found == NULL) {
            printSpace(65);
            printf(RED BOLD "Khong tim thay tai khoan!\n" RESET);
        }
    } while(found == NULL);

    int choice;
    do {
        printf("\n");
        printSpace(65);
        printf("1. Sua mat khau\n");
        printSpace(65);
        printf("2. Sua vai tro\n");
        printSpace(65);
        printf("0. Thoat\n");
        printSpace(65);
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: {
                char newPassword[50];
                printf("\n");
                printSpace(65);
                printf("Nhap mat khau moi: ");
                fgets(newPassword, sizeof(newPassword), stdin);
                newPassword[strcspn(newPassword, "\n")] = '\0';
                strcpy(found->A.password, newPassword);
                printSpace(65);
                printf(GREEN BOLD "Sua mat khau thanh cong!\n" RESET);
                pauseScreen();
                break;
            }
            case 2: {
                int newRole;
                printf("\n");
                printSpace(65);
                printf("1. Admin\n");
                printSpace(65);
                printf("2. Staff\n");
                printSpace(65);
                printf("Nhap vai tro moi: ");
                do {
                    if (scanf("%d", &newRole) != 1) {
                        printSpace(65);
                        printf(RED BOLD "Loi: Vui long chi nhap chu so! Nhap lai: " RESET);
                        while(getchar() != '\n');
                        newRole = -1;
                        continue;
                    }
                    if(newRole != ROLE_ADMIN && newRole != ROLE_STAFF) {
                        printSpace(65);
                        printf(RED BOLD "Lua chon khong hop le! Nhap lai: " RESET);
                    }
                } while(newRole != ROLE_ADMIN && newRole != ROLE_STAFF);

                found->A.role = newRole;
                printSpace(65);
                printf(GREEN BOLD "Sua vai tro thanh cong!\n" RESET);
                pauseScreen();
                break;
            }
            case 0:
                printf("\n");
                printSpace(65);
                printf("Thoat!\n");
                break;

            default:
                printSpace(65);
                printf(RED BOLD "Lua chon khong hop le!\n" RESET);
                pauseScreen();
        }
    } while(choice != 0);
}

void updateRecord(Node* head,char currentUsername[]) {
    if(head == NULL) {
        printf("\n");
        printSpace(65);
        printf(RED BOLD "Danh sach rong.\n" RESET);
        return ;
    }
    
    char phone[15];
    Node* found=NULL;

    while(found==NULL) {
        int check;
        printf("\n");
        printSpace(65);
        printf("Nhap so dien thoai thue bao can sua: ");
        scanf("%s",phone);
        if (!validatePhone(phone)) {
            printSpace(65);
            printf(RED BOLD "So dien thoai khong hop le!\n" RESET);
            continue;
        }
        found=search_record(head,phone);
    
        if(found==NULL) {
            printSpace(65);
            printf(RED BOLD "Khong tim thay thue bao! \n" RESET);       
            printf("\n");
            found = suggestSimilarPhoneForUpdate(head,phone,check);

            if(found == NULL && check == 0) {
                printf("Khong co goi y nao phu hop!\n");
            } else if (found != NULL && check == 1){
                printSpace(65);
                printf("Goi y so thue bao gan dung: \n");
                printf("\n");
            }
        }
    }
    print_record(found);
    menu_update(found, currentUsername);
    saveRecordToFile(RECORD_FILE,head);

    printSpace(65);
    printf("Cap nhat thanh cong!\n");

}

void deleteAccount(AccountNode **head,char currentUsername[]) {
    char userName[30];
    printf("\n");
    printSpace(65);
    printf("Nhap tai khoan can xoa: ");
    scanf("%s", userName);
    printf("\n");

    AccountNode *p = *head;
    AccountNode *prev = NULL;

    while(p != NULL && strcmp(p->A.username,userName) != 0) {
        prev = p;
        p = p->next;
    }

    if(p == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong tim thay tai khoan can xoa!\n" RESET);
        return ;
    }

    print_account(p);

    char confirm;
    printSpace(65);
    printf("Xac nhan xoa tai khoan nay? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printSpace(65);
        printf("Da huy xoa!\n");
        return;
    }

    if(prev == NULL) {
        *head = p->next;
    } else {
        prev->next = p->next;
    }
    free(p);
    saveAccountToFile("account.txt", *head);
    printSpace(65);
    printf("Xoa thanh cong!\n");
}

void deleteRecord(Node **head,char currentUsername[]) {
    char phone[15];
    printf("\n");
    printSpace(65);
    printf("Nhap so dien thoai can xoa: ");
    scanf("%s", phone);

    Node *p = *head;
    Node *prev = NULL;

    while (p != NULL && strcmp(p->data.phone, phone) != 0) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong tim thay so dien thoai!\n" RESET);
        return;
    }

    printf("\n");
    print_record(p);

    char confirm;
    printf("\n");
    printSpace(65);
    printf("Xac nhan xoa lien he nay? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printSpace(65);
        printf("Da huy xoa!\n");
        return;
    }

    if (prev == NULL) {
        *head = p->next;
    } else {
        prev->next = p->next;
    }

    free(p);
    saveRecordToFile(RECORD_FILE, *head);
    printSpace(65);
    printf("Xoa thanh cong!\n");
}

void listByProvince(Node* head) {
    if (head == NULL) { 
        printf("\n");
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET); 
        return; 
    } 

    char province[50]; 
    char tempProvince[50];
    int found = 0;
    int stt = 1;

    printf("\n");
    printSpace(65);
    printf("Nhap tinh can tim: ");
    clearInputBuffer();

    fgets(province, sizeof(province), stdin);
    province[strcspn(province, "\n")] = '\0';

    toLowerCase(province);

    Node* p = head;
    while (p != NULL) {
        strcpy(tempProvince,p->data.province.tentinh);
        toLowerCase(tempProvince);

        if (strcmp(tempProvince, province) == 0) {
            found = 1;
            break;
        }
        p = p->next;
    }
    if (!found) {
        printSpace(65);
        printf(RED BOLD "Khong tim thay tinh nay!\n" RESET);
        return;
    }
    printf("\n");
    printSpace(46);
    printf("                                         DANH SACH THEO TINH: %s\n", province);
    p = head;
    printHeader();
    while (p != NULL) {
        strcpy(tempProvince, p->data.province.tentinh);
        toLowerCase(tempProvince);

        if (strcmp(tempProvince, province) == 0) {
            printRow(stt, p);
            stt++;
            found = 1;
        }
        p = p->next;
    }
    printFooter();
}

double total_Fee(Record R) {
    if(R.status == 2) {
        return 0;
    }

    if(R.status == 3) {
        return 0;
    }

    double onNet = R.onNetMinutes*On_net_rate;
    double offNet = R.offNetMinutes*Off_net_rate;
    double subtotal = onNet + offNet;
    double total = subtotal + subtotal*VAT;

    return total;
}

void exportReport(Node *head) {
    if (head == NULL) {
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return;
    }
    FILE *f = fopen("report.txt", "w");
    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong mo duoc file!\n" RESET);
        return;
    }
    int total = 0;
    int active = 0;
    int locked = 0;
    int canceled = 0;

    int totalOnNet = 0 ;
    int totalOffNet = 0;
    double totalFee = 0;
    double maxFee = 0;

    Node *maxNode = NULL;
    Node *p = head;
    while (p != NULL) {
        total++;
        if (p->data.status == 1)
            active++;
        else if (p->data.status == 2)
            locked++;
        else if (p->data.status == 3)
            canceled++;
        totalOnNet += p->data.onNetMinutes;
        totalOffNet += p->data.offNetMinutes;
        double fee = total_Fee(p->data);
        totalFee += fee;
        if (fee > maxFee) {
            maxFee = fee;
            maxNode = p;
        }
        p = p->next;   
    }
    fprintf(f, "+==================================================+\n");
    fprintf(f, "|                THONG KE THUE BAO                 |\n");
    fprintf(f, "+==================================================+\n");
    fprintf(f, "| %-35s : %-10d |\n", "Tong so thue bao", total);
    fprintf(f, "| %-35s : %-10d |\n", "Dang hoat dong", active);
    fprintf(f, "| %-35s : %-10d |\n", "Tam khoa", locked);
    fprintf(f, "| %-35s : %-10d |\n", "Da huy", canceled);
    fprintf(f, "+==================================================+\n");
    fprintf(f, "| %-35s : %-10d |\n", "Tong phut noi mang", totalOnNet);
    fprintf(f, "| %-35s : %-10d |\n", "Tong phut ngoai mang", totalOffNet);
    fprintf(f, "+==================================================+\n");
    fprintf(f, "| %-35s : %-10.0lf |\n", "Tong doanh thu", totalFee);
    if (maxNode != NULL) {
        fprintf(f, "| %-35s : %-10s |\n", "Thue bao co cuoc cao nhat", maxNode->data.phone);
        fprintf(f, "| %-35s : %-10.0lf |\n", "Cuoc cao nhat", maxFee);
    }
    fprintf(f, "+==================================================+\n");
    fclose(f);
    printSpace(65);
    printf("   Da xuat bao cao ra file report.txt!\n");
}

void statisticsByProvince(Node* head) {
    if (head == NULL) {
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return;
    }
    printf("\n");
    printSpace(77);
    printf("        THONG KE SO THUE BAO THEO TINH\n");
    printSpace(77);
    printf("+-----+----------------------+----------------+\n");
    printSpace(77);
    printf("| %-3s | %-20s | %-14s |\n", "STT", "Tinh", "So thue bao");
    printSpace(77);
    printf("+-----+----------------------+----------------+\n");
    int total = 0;
    int stt = 1;
    Node* p = head;
    while (p != NULL) {
        total++;
        int printed = 0;
        Node* t = head;
        while (t != p) {
            char temp1[100], temp2[100];
            strcpy(temp1, t->data.province.tentinh);
            strcpy(temp2, p->data.province.tentinh);
            toLowerCase(temp1);
            toLowerCase(temp2);
            if (strcmp(temp1, temp2) == 0) {
                printed = 1;
                break;
            }
            t = t->next;
        }
        if (!printed) {
            int count = 0;
            Node* q = head;
            while (q != NULL) {
                char temp1[100], temp2[100];
                strcpy(temp1, p->data.province.tentinh);
                strcpy(temp2, q->data.province.tentinh);
                toLowerCase(temp1);
                toLowerCase(temp2);
                if (strcmp(temp1, temp2) == 0) {
                    count++;
                }
                q = q->next;
            }

            printSpace(77);
            printf("| %-3d | %-20.20s | %-14d |\n", stt, p->data.province.tentinh, count);
            stt++;
        }
        p = p->next;
    }
    printSpace(77);
    printf("+-----+----------------------+----------------+\n");
    printSpace(77);
    printf("Tong so thue bao: %d\n", total);
}

void checkDuplicate(Node** head) {
    Node *p = *head;
    int found = 0;

    while(p != NULL) {
        Node *prev = p;
        Node *q = p->next;

        while(q != NULL) {
            if(strcmp(p->data.province.tentinh,q->data.province.tentinh) == 0 &&
                strcmp(p->data.phone,q->data.phone) == 0) {
                    printf("\n");
                    printSpace(65);
                    printf("Phat hien thue bao trung so dien thoai trong tinh %s:\n",p->data.province.tentinh);
                    found = 1;
                    printSpace(65);
                    printf("Thue bao 1:\n");
                    print_record(q);
                    printf("\n");
                    printSpace(65);
                    printf("Thue bao 2:\n");
                    print_record(p);
                    printf("\n");
                    printSpace(65);
                    printf("Xoa thanh cong thue bao 2\n");

                    Node* temp = q;
                    prev->next = q->next;
                    q = q->next;
                    free(temp);
            } else {
                prev = q;
                q = q->next;
            }
        }
        p = p->next;
    }
    if(found == 0) {
        printf("\n");
        printSpace(65);
        printf("Khong tim thay thue bao trung!");
    }
}

void filterByStatus(Node *head) {
    if (head == NULL) {
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return;
    }
    printf("\n");
    int status = inputStatus();
    Node *p = head;
    int stt = 1;
    int found = 0;
    printf("\n");
    printSpace(46);
    printf("                                       DANH SACH THUE BAO THEO TRANG THAI\n");
    printHeader();
    while (p != NULL) {
        if (p->data.status == status) {
            printRow(stt, p);
            stt++;
            found = 1;
        }  
        p = p->next;
    }
    printFooter();
    if (!found) {
        printSpace(65);
        printf("Khong tim thay thue bao nao phu hop!\n");
    }
}

void readFileByUser(Node **head,char currentUsername[]) {
    char filename[100];

    printf("\n");
    printSpace(65);
    printf("Nhap ten file muon doc: ");
    scanf("%s", filename);

    readFile(filename,head,currentUsername);
}

void exportBill(Node *p) {
    if (p == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong ton tai thue bao!\n" RESET);
        return;
    }
    char filename[50];
    sprintf(filename, "bill_%s.txt", p->data.phone);
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printSpace(65);
        printf(RED BOLD "Khong mo duoc file!\n" RESET);
        return;
    }
    double onNetFee = p->data.onNetMinutes * On_net_rate;
    double offNetFee = p->data.offNetMinutes * Off_net_rate;
    double subtotal = onNetFee + offNetFee;
    double vat = subtotal * VAT;
    double total = total_Fee(p->data);
    fprintf(f, "=====================================================\n");
    fprintf(f, "               HOA DON CUOC DIEN THOAI\n");
    fprintf(f, "=====================================================\n");
    fprintf(f, "Ten don vi      : %s\n", p->data.name);
    fprintf(f, "So dien thoai   : %s\n", p->data.phone);
    fprintf(f, "Tinh/Thanh      : %s\n", p->data.province.tentinh);
    fprintf(f, "-----------------------------------------------------\n");
    fprintf(f, "Noi mang        : %4d phut x %d = %.0lf VND\n", p->data.onNetMinutes, On_net_rate, onNetFee);
    fprintf(f, "Ngoai mang      : %4d phut x %d = %.0lf VND\n", p->data.offNetMinutes, Off_net_rate, offNetFee);
    fprintf(f, "-----------------------------------------------------\n");
    fprintf(f, "Tam tinh        : %.0lf VND\n", subtotal);
    fprintf(f, "VAT (10%%)       : %.0lf VND\n", vat);
    fprintf(f, "=====================================================\n");
    fprintf(f, "TONG THANH TOAN : %.0lf VND\n", total);
    fprintf(f, "=====================================================\n");
    fclose(f);
    printSpace(65);
    printf("Da xuat bill ra file %s!\n", filename);
}

void calculateFee(Node *head) {
    if (head == NULL) {
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return;
    }

    char phone[15];
    Node *found = NULL;
    do {
        printf("\n");
        printSpace(65);
        printf("Nhap so dien thoai can tinh cuoc: ");
        scanf("%14s", phone);
        if(!validatePhone(phone)) {
            printSpace(65);
            printf(RED BOLD "So dien thoai khong hop le!\n" RESET);
            continue;
        }
        found = search_record(head, phone);
        if(found == NULL) {
            printSpace(65);
            printf(RED BOLD "Khong tim thay thue bao!\n" RESET);
            printf("\n");
            printSpace(65);
            printf("Goi y cac so gan dung:\n");
            suggestSimilarPhone(head, phone);
        }
    } while(found == NULL);

    if (found->data.status == 2) {
        printSpace(65);
        printf("=====================================\n");
        printSpace(65);
        printf("         THUE BAO TAM KHOA\n");
        printSpace(65);
        printf("Tong cuoc : 0 VND\n");
        printSpace(65);
        printf("Ly do     : Thue bao dang tam khoa\n");
        printSpace(65);
        printf("=====================================\n");

        return;
    }

    if (found->data.status == 3) {
        printSpace(65);
        printf("=====================================\n");
        printSpace(65);
        printf("         THUE BAO DA HUY\n");
        printSpace(65);
        printf("Tong cuoc : 0 VND\n");
        printSpace(65);
        printf("Ly do     : Thue bao da huy\n");
        printSpace(65);
        printf("=====================================\n");

        return;
    }

    double total = total_Fee(found->data);
    printSpace(65);
    printf("=======================================\n");
    printSpace(65);
    printf("           THONG TIN CUOC\n");
    printSpace(65);
    printf("=======================================\n");
    printSpace(65);
    printf("So dien thoai : %s\n", found->data.phone);
    printSpace(65);
    printf("Ten don vi    : %s\n", found->data.name);
    printSpace(65);
    printf("Tong cuoc     : %.0lf VND\n", total);
    printSpace(65);
    printf("=======================================\n");
    char choice;
    printf("\n");
    printSpace(65);
    printf("Ban co muon in bill khong? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        printBill(found);
        printf("\n");
        printSpace(65);
        printf("Ban co muon xuat bill ra file khong? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            exportBill(found);
        }
    }
}

int findProvinceIndex(ProvinceFee stats[], int count, char provinceName[]) {
    for (int i = 0; i < count; i++) {
        char temp1[100], temp2[100];
        strcpy(temp1, stats[i].provinceName);
        strcpy(temp2, provinceName);
        toLowerCase(temp1);
        toLowerCase(temp2);
        if (strcmp(temp1, temp2) == 0) {
            return i;
        }
    }
    return -1;
}

void pronvinceMaxRecord (Node *head) {
    if(head == NULL) {
        return ;
    }

    ProvinceStat stats[100];
    int count = 0;

    Node *p = head;

    while(p != NULL) {
        int found = -1;
        for(int i=0 ;i < count ;i++) {
            char temp1[100], temp2[100];
            strcpy(temp1, stats[i].province_name);
            strcpy(temp2, p->data.province.tentinh);
            toLowerCase(temp1);
            toLowerCase(temp2);
            if(strcmp(temp1, temp2) == 0) {
                found = i;
                break;
            }
        }

        if(found == -1) {
            strcpy(stats[count].province_name,p->data.province.tentinh);
            stats[count].total = 1;
            count++;
        } else {
            stats[found].total++;
        }

        p=p->next;
    }

    int maxIndex = 0;
    for (int i = 1; i < count; i++) {
        if (stats[i].total > stats[maxIndex].total) {
            maxIndex = i;
        }
    }

    printProvinceMaxRecord(stats, count, maxIndex);
}

void top3RecordMaxFee (Node *head) {
    if(head == NULL) {
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return;
    }

    CompanyFee stats[100];
    int count = 0;

    Node *p = head;
    
    while (p != NULL) {
        if (p->data.status != 1) {
            p = p->next;
            continue;
        }
        strcpy(stats[count].companyName, p->data.name);
        stats[count].totalFee = total_Fee(p->data);
        count++;
        p = p->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (stats[i].totalFee < stats[j].totalFee) {
                CompanyFee temp = stats[i];
                stats[i] = stats[j];
                stats[j] = temp;
            }
        }
    }
    int limit = (count < 3) ? count : 3;
    printTop3RecordMaxFee(stats, limit);
}

void top3ProvinceByFee(Node *head) {
    if (head == NULL) {
        return ;
    }

    ProvinceFee stats[100];
    int count = 0;

    Node* p = head;

    while(p!=NULL) {
        if (p->data.status != 1 ) {
            p = p->next;
            continue;
        }
        
        char *provinceName = p->data.province.tentinh;
        double fee = total_Fee(p->data);

        int index = findProvinceIndex(stats,count,provinceName);

        if(index == -1) {
            strcpy(stats[count].provinceName,provinceName);
            stats[count].totalFee = fee;
            count++;
        } else {
            stats[index].totalFee += fee;
        }

        p=p->next;
    }

    printTop3ProvinceFee(stats, count);
}

int revenue(Node *head) {
    if(head == NULL) {
        printSpace(65);
        printf(RED BOLD "Danh sach rong!\n" RESET);
        return 0;
    }

    double sumRevenue = 0;
    int totalOnNet = 0;
    int totalOffNet = 0;
    int found = 0;

    Node* p = head;

    while(p != NULL) {
        if (p->data.status == 1) {
            found = 1;
            double fee = total_Fee(p->data);
            sumRevenue += fee;
            totalOnNet += p->data.onNetMinutes;
            totalOffNet += p->data.offNetMinutes;
        }

        p = p->next;
    }

    if (!found) {
        printSpace(65);
        printf(RED BOLD "   Khong co du lieu thong ke doanh thu!\n" RESET);
        return 0;
    }

    printSpace(65);
    printf("| %-45s | %16.0lf VND |\n", "Doanh thu thang nay", sumRevenue);
    printSpace(65);
    printf("| %-45s | %15d phut |\n", "Tong phut noi mang", totalOnNet);
    printSpace(65);
    printf("| %-45s | %15d phut |\n", "Tong phut ngoai mang", totalOffNet);
    printSpace(65);
    printf(YELLOW);
    printf("+----------------------------------------------------------------------+\n");
    printf(RESET);

    return 1;
}

int main() {
    Node* head = NULL;
    AccountNode *headAccount = NULL;
    char currentUsername[30];
    int role;

    clearScreen();
    showScreen();

    readFile(RECORD_FILE, &head,currentUsername);
    loadAccountsToList("account.txt", &headAccount);

    while(1) {
        role = login(headAccount, currentUsername);

        if (role == ROLE_ADMIN) {
            int choice;
            do {
                menu_admin();

                do {
                    if (scanf("%d", &choice) != 1) { 
                        printSpace(65);  
                        printf(RED BOLD"   Loi: Vui long chi nhap chu so! Nhap lai: " RESET);
                        while(getchar() != '\n');
                        choice = -1;
                        continue;
                    }
                    if (choice < 0 || choice > 5) {
                        printSpace(65);
                        printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);
                    }
                } while(choice < 0 || choice > 5);

                switch(choice) {
                    case 1: 
                        menu_manage(&head,currentUsername);
                        break;

                    case 2:
                        menu_search(head);
                        break;

                    case 3:
                        menu_statistical(head);
                        break;

                    case 4:
                        menu_account(&headAccount,currentUsername);
                        break;

                    case 5:
                        showHistory();
                        break;

                    case 0:
                        printSpace(65);
                        printf(RED BOLD "   Da dang xuat!\n" RESET);
                        endScreen();
                        break;

                    default:
                        printf("\n");
                        printSpace(65);
                        printf(RED BOLD "   Lua chon khong hop le!" RESET);
                }

            } while(choice != 0);
        } 
        
        else if (role == ROLE_STAFF) {
            int choice;
            do {
                menu_staff();

                do {
                    if (scanf("%d", &choice) != 1) { 
                        printSpace(65);  
                        printf(RED BOLD"   Loi: Vui long chi nhap chu so! Nhap lai: " RESET);
                        while(getchar() != '\n');
                        choice = -1;
                        continue;
                    }
                    if (choice < 0 || choice > 5) {
                        printSpace(65);
                        printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);
                    }
                } while(choice < 0 || choice > 4);

                switch(choice) {
                    case 1: {
                        char phone[15];

                        printf("\n");
                        printSpace(65);
                        printf("Nhap so dien thoai thue bao can tim: ");

                        do {
                            scanf("%s", phone);

                            if (!validatePhone(phone)) {
                                printSpace(65);
                                printf(RED BOLD "So dien thoai khong hop le! Nhap lai: " RESET);
                            }

                        } while (!validatePhone(phone));

                        Node* cur = search_record(head, phone);

                        if (cur != NULL) {
                            print_record(cur);
                        } else {
                            printSpace(65);
                            printf(RED BOLD "Khong tim thay so dien thoai nay!\n\n" RESET);
                            printSpace(65);
                            printf("Goi y cac so thue bao gan dung:\n");        
                            suggestSimilarPhone(head, phone);
                        }
                        endScreen();
                        break;
                    }
                    case 2:
                        filterByStatus(head);
                        endScreen();
                        break;

                    case 3:
                        listByProvince(head);
                        endScreen();
                        break;

                    case 4:
                        calculateFee(head);
                        endScreen();
                        break;

                    case 0:
                        printSpace(65);
                        printf(RED BOLD "   Da dang xuat!\n" RESET);
                        endScreen();
                        break;

                    default:
                        printf("\n");
                        printSpace(65);
                        printf(RED BOLD "   Lua chon khong hop le!" RESET);
                }

            } while(choice != 0);
        }
    }

    return 0;
}
