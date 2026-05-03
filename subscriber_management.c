#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "record.h"

#define False 0
#define True 1

Node* createNode(Record R) {
    Node* newNode = (Node*)malloc (sizeof(Node));
    if(newNode == NULL) {
        printf("Khong du bo nho\n");
        exit(1);
    }
    newNode->data = R;
    newNode->next = NULL;
    return newNode;
}

void addRecord(Node** head, Record R) {
    Node* newNode = createNode(R);

    if (*head == NULL) {
        *head = newNode;
        return ;
    }

    newNode->next = *head;
    *head = newNode;
}

int validatePhone(char phone[]) {
    int len = strlen(phone);
    if (len < 9 || len > 11) {
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

void readFile(const char *filename, Node **head) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong mo duoc file!\n");
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
        addRecord(head, temp);
        valid++;
    }

    fclose(f);
    printf("Doc du lieu thanh cong!\n");
    printf("Hop le: %d dong\n", valid);
    printf("Khong hop le: %d dong\n", invalid);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pauseScreen() {
    printf("\nNhan Enter de tiep tuc...");
    clearInputBuffer();
    getchar(); 
}

void endScreen() {
    pauseScreen();
    system("clear");
}

int inputStatus() {
    int choice;
    do {
        printf("Chon trang thai thue bao:\n");
        printf("1. Dang hoat dong\n");
        printf("2. Tam khoa\n");
        printf("3. Da huy\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 3) {
            printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while (choice < 1 || choice > 3);

    return choice;
}

Record inputRecord() {
    Record R;
    clearInputBuffer();
    
    printf("Nhap so dien thoai: ");
    do {
        scanf("%s", R.phone);
        if (!validatePhone(R.phone)) {
            printf("So dien thoai khong hop le! Nhap lai: ");
        }
    } while(!validatePhone(R.phone));
    getchar();

    printf("Nhap ten don vi: ");
    do {
        fgets(R.name,sizeof(R.name),stdin);
        R.name[strcspn(R.name,"\n")]='\0';
        if (!validateInput(R.name)) {
            printf("Ten khong hop le!\n");
        }
    } while(!validateInput(R.name));

    printf("Nhap dia chi: ");
    do {
        fgets(R.address,sizeof(R.address),stdin);
        R.address[strcspn(R.address,"\n")]='\0';
        if(!validateInput(R.address)) {
            printf("Dia chi khong hop le! Vui long nhap lai.\n");
        }
    } while(!validateInput(R.address));

    printf("Nhap tinh: ");
    do {
        fgets(R.province.tentinh,sizeof(R.province.tentinh),stdin);
        R.province.tentinh[strcspn(R.province.tentinh,"\n")]='\0';
        if(!validateInput(R.province.tentinh)) {
            printf("Tinh khong hop le! Vui long nhap lai.\n");
        }
    } while(!validateInput(R.province.tentinh));

    R.status = inputStatus();

    return R;
}


Node* search_record(Node* head,char phone[15]) {
    Node* cur = head;

    while(cur!=NULL) {
        if(strcmp(cur->data.phone,phone)==0){
            printf("Da tim thay thue bao!\n\n");
            return cur;
        }
        cur=cur->next;
    }
    printf("Khong tim thay thue bao!\n");
    return NULL;
}

void menu_update(Node* head) {
    int choice;

    do {
        printf("\n1. Sua ten\n");
        printf("2. Sua dia chi\n");
        printf("3. Sua so dien thoai\n");
        printf("4. Sua trang thai hoat dong\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap ten moi: ");
                fgets(head->data.name, sizeof(head->data.name), stdin);
                head->data.name[strcspn(head->data.name, "\n")] = '\0';
                printf("Sua ten thanh cong!\n");
                pauseScreen();
                break;

            case 2:
                printf("Nhap dia chi moi: ");
                fgets(head->data.address,sizeof(head->data.address),stdin);
                head->data.address[strcspn(head->data.address,"\n")]='\0';
                printf("Sua dia chi thanh cong!\n");
                pauseScreen();
                break;

            case 3:
                printf("Nhap so moi: ");
                scanf("%s", head->data.phone);
                getchar();
                printf("Sua so thue bao thanh cong!\n");
                pauseScreen();
                break;

            case 4: 
                printf("Nhap trang thai moi:\n");
                head->data.status = inputStatus();
                printf("Sua trang thai thanh cong!\n");
                pauseScreen();
                break;

            case 0:
                printf("Thoat!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
                pauseScreen();
        }

    } while (choice != 0);
}

void updateRecord(Node* head){
    if(head == NULL) {
        printf("Danh sach rong.\n");
        return ;
    }
    
    char phone[15];
    Node* found=NULL;

    while(found==NULL) {
        printf("Nhap so dien thoai thue bao can sua: ");
        scanf("%s",phone);
        if (!validatePhone(phone)) {
            printf("So dien thoai khong hop le!\n");
            return;
        }
        found=search_record(head,phone);
        if(found==NULL) {
            printf("Khong tim thay thue bao vui long nhap lai: \n");
        }
    }
    print_record(found);
    menu_update(found);

    printf("Cap nhat thanh cong!\n");

}

void deleteRecord(Node **head) {
    char phone[15];
    printf("Nhap so dien thoai can xoa: ");
    scanf("%s", phone);

    Node *p = *head;
    Node *prev = NULL;

    while (p != NULL && strcmp(p->data.phone, phone) != 0) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Khong tim thay so dien thoai!\n");
        return;
    }

    print_record(p);

    char confirm;
    printf("Xac nhan xoa lien he nay? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Da huy xoa!\n");
        return;
    }

    if (prev == NULL) {
        *head = p->next;
    } else {
        prev->next = p->next;
    }

    free(p);
    printf("Xoa thanh cong!\n");
}

void listByProvince(Node* head) {
    if (head == NULL) { 
        printf("Danh sach rong!\n"); 
        return; 
    } 
    char province[50]; 
    int found = 0;
    int stt = 1;
    printf("Nhap tinh can tim: ");
    clearInputBuffer();
    fgets(province, sizeof(province), stdin);
    province[strcspn(province, "\n")] = '\0';
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->data.province.tentinh, province) == 0) {
            found = 1;
            break;
        }
        p = p->next;
    }
    if (!found) {
        printf("Khong tim thay tinh nay!\n");
        return;
    }
    printf("\n                                     DANH SACH THEO TINH: %s\n", province);
    p = head;
    printHeader();
    while (p != NULL) {
        if (strcmp(p->data.province.tentinh, province) == 0) {
            printRow(stt, p);
            stt++;
            found = 1;
        }
        p = p->next;
    }
    printFooter();
}

void statisticsByProvince(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("\nTHONG KE SO THUE BAO THEO TINH\n");
    printf("+-----+----------------------+----------------+\n");
    printf("| %-3s | %-20s | %-14s |\n", "STT", "Tinh", "So thue bao");
    printf("+-----+----------------------+----------------+\n");
    int total = 0;
    int stt = 1;
    Node* p = head;
    while (p != NULL) {
        total++;
        int printed = 0;
        Node* t = head;
        while (t != p) {
            if (strcmp(t->data.province.tentinh, p->data.province.tentinh) == 0) {
                printed = 1;
                break;
            }
            t = t->next;
        }
        if (!printed) {
            int count = 0;
            Node* q = head;
            while (q != NULL) {
                if (strcmp(p->data.province.tentinh, q->data.province.tentinh) == 0) {
                    count++;
                }
                q = q->next;
            }
            printf("| %-3d | %-20.20s | %-14d |\n", stt, p->data.province.tentinh, count);
            stt++;
        }
        p = p->next;
    }
    printf("+-----+----------------------+----------------+\n");
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
                    printf("Phat hien thue bao trung so dien thoai trong tinh %s:\n",p->data.province.tentinh);
                    found = 1;
                    printf("Thue bao 1:\n");
                    print_record(q);
                    printf("\n");
                    printf("Thue bao 2:\n");
                    print_record(p);
                    printf("\n");
                    printf("Xoa thanh cong thue bao 2\n");
                    printf("\n");

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
        printf("Khong tim thay thue bao trung!");
    }
}

void filterByStatus(Node *head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("\n");
    int status = inputStatus();
    Node *p = head;
    int stt = 1;
    int found = 0;
    printf("\n        DANH SACH THUE BAO THEO TRANG THAI\n");
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
        printf("Khong tim thay thue bao nao phu hop!\n");
    }
}

void readFileByUser(Node **head) {
    char filename[100];

    printf("Nhap ten file muon doc: ");
    scanf("%s", filename);

    readFile(filename,head);
}

void exportReport(Node *head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    FILE *f = fopen("report.txt", "w");
    if (f == NULL) {
        printf("Khong mo duoc file!\n");
        return;
    }
    int total = 0;
    int active = 0;
    int locked = 0;
    int canceled = 0;
    Node *p = head;
    while (p != NULL) {
        total++;
        if (p->data.status == 1)
            active++;
        else if (p->data.status == 2)
            locked++;
        else if (p->data.status == 3)
            canceled++;
        p = p->next;   
    }
    fprintf(f, "========================================\n");
    fprintf(f, "          THONG KE THUE BAO\n");
    fprintf(f, "========================================\n");
    fprintf(f, "| Tong so thue bao           : %-6d |\n", total);
    fprintf(f, "| Dang hoat dong             : %-6d |\n", active);
    fprintf(f, "| Tam khoa                   : %-6d |\n", locked);
    fprintf(f, "| Da huy                     : %-6d |\n", canceled);
    fprintf(f, "========================================\n");
    fclose(f);
    printf("Da xuat bao cao ra file report.txt!\n");
}

int main() {
    Node* head = NULL;

    readFile("data1.txt", &head);
    
    int choice;
    do {
        menu();

        if (scanf("%d", &choice) != 1) {   
            printf("Loi: Vui long chi nhap chu so!\n");
            while(getchar() != '\n'); // Xoa bo nho dem
            continue;
        }

        switch(choice) {
            case 1: {
                Record newR = inputRecord();
                addRecord(&head,newR);
                printf("Da them thue bao thanh cong!\n");
                endScreen();
                break;
            }
            case 2: 
                displayAll(head);
                endScreen();
                break;
            case 3: {
                char phone[15];
                printf("Nhap thue bao can tim: ");
                scanf("%s",phone);
                Node* cur=search_record(head,phone);
                if (cur != NULL) 
                    print_record(cur);
                endScreen();
                break;
            }
            case 4:
                updateRecord(head);
                endScreen();
                break;
            case 5:
                deleteRecord(&head);
                endScreen();
                break;
            case 6:
                listByProvince(head);
                endScreen();
                break;
            case 7: 
                statisticsByProvince(head);
                endScreen();
                break;
            case 8: 
                checkDuplicate(&head);
                endScreen();
                break;
            case 9:
                readFileByUser(&head);
                endScreen();
                break;
            case 10: 
                filterByStatus(head);
                endScreen();
                break;
            case 11:
                exportReport(head);
                endScreen();
                break;
            case 0:
                printf("Da thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(choice != 0);

    return 0;
}
