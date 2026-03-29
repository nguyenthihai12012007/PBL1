#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define False 0
#define True 1

typedef struct Province {
    char tentinh[50];
} Province;

typedef struct Record {
    Province province;
    char name[100];
    char address[100];
    char phone[15];
} Record;

typedef struct Node {
    Record data;
    struct Node *next;
} Node;

Node* createNode(Record R) {
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->data = R;
    newNode->next = NULL;
    return newNode;
}

void addRecord(Node** head,Record R) {
    Node* newNode = createNode(R);

    if (*head == NULL) {
        *head = newNode;
        return ;
    }

    newNode->next = *head;
    *head = newNode;
}

void readFile(const char *filename, Node **head) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong mo duoc file!\n");
        return;
    }

    char line[300];

    while(fgets(line, sizeof(line),f) != NULL) {
        line[strcspn(line,"\n")] = '\0';

        Record temp;
        char *token = strtok(line,"|");

        if (token != NULL) {
            strcpy(temp.province.tentinh,token);
        }

        token = strtok(NULL,"|");
        if (token != NULL) {
            strcpy(temp.name,token);
        }

        token = strtok(NULL,"|");
        if (token != NULL) {
            strcpy(temp.address,token);
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strcpy(temp.phone, token);
        }
        addRecord(head,temp);
    }

    fclose(f);
    printf("Doc du lieu thanh cong!\n");
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

Record inputRecord() {
    Record R;
    while(getchar()!='\n');

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
    fgets(R.address,sizeof(R.address),stdin);
    R.address[strcspn(R.address,"\n")]='\0';

    printf("Nhap tinh: ");
    fgets(R.province.tentinh,sizeof(R.province.tentinh),stdin);
    R.province.tentinh[strcspn(R.province.tentinh,"\n")]='\0';

    return R;
}

void printList(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
        printf("\nPhone: %s", temp->data.phone);
        printf("\nName: %s", temp->data.name);
        printf("\nAddress: %s", temp->data.address);
        printf("\nProvince: %s", temp->data.province.tentinh);
        printf("--------------------\n");

        temp = temp->next;
    }
}


Node* search_record(Node* head,char phone[15]) {
    Node* cur = head;

    while(cur!=NULL) {
        if(strcmp(cur->data.phone,phone)==0){
            printf("Da tim thay thue bao!\n");
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
        printf("1. Sua ten\n");
        printf("2. Sua dia chi\n");
        printf("3. Sua so dien thoai\n");
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
                break;

            case 2:
                printf("Nhap dia chi moi: ");
                fgets(head->data.address,sizeof(head->data.address),stdin);
                head->data.address[strcspn(head->data.address,"\n")]='\0';
                printf("Sua dia chi thanh cong!\n");
                break;

            case 3:
                printf("Nhap so moi: ");
                scanf("%s", head->data.phone);
                getchar();
                printf("Sua so thue bao thanh cong!\n");
                break;

            case 0:
                printf("Thoat!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 0);
}



void print_record(Node* node) {
    if (node == NULL) return;

    printf("Ten: %s\n", node->data.name);
    printf("So dien thoai: %s\n", node->data.phone);
    printf("Dia chi: %s\n", node->data.address);
    printf("Tinh: %s\n", node->data.province.tentinh);
}

void updateRecord(Node* head){
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
    printf("Tim thay!\n");
    print_record(found);
    menu_update(found);

    printf("Cap nhat thanh cong!\n");

}

void displayAll(Node* head) {
    Node *p = head;
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("\nDANH SACH DANH BA\n");
    while (p != NULL) {
        printf("Tinh: %s\n", p->data.province.tentinh);
        printf("Ten don vi: %s\n", p->data.name);
        printf("Dia chi: %s\n", p->data.address);
        printf("So dien thoai: %s\n", p->data.phone);
        printf("\n");
        p = p->next;
    }
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
    printf("Nhap tinh can tim: ");
    while(getchar() != '\n');
    fgets(province, sizeof(province), stdin);
    province[strcspn(province, "\n")] = '\0';
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->data.province.tentinh, province) == 0) {
            printf("\nTen: %s\n", p->data.name);
            printf("so dien thoai: %s", p->data.phone);
            printf("Dia chi: %s\n", p->data.address);
            printf("Tinh: %s\n", p->data.province.tentinh);
            printf("-------------------\n");
            found = 1;
        }
        p = p->next;
    }
    if (!found) {
        printf("Khong tim thay tinh nay!\n");
    }
}

void statisticsByProvince(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("\nTHONG KE SO THUE BAO THEO TINH\n");
    int total = 0;
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
            printf("Tinh %s co %d thue bao\n", p->data.province.tentinh, count);
        }
        p = p->next;
    }
    printf("Tong so thue bao: %d\n", total);
}

void menu() {
    printf("CHUONG TRINH QUAN LY DANH BA DIEN THOAI\n");
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

int main() {
    Node* head = NULL;

    readFile("data1.txt",&head);
    
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
                break;
            }
            case 2: 
                displayAll(head);
                break;
            case 3: {
                char phone[15];
                printf("Nhap thue bao can tim:\n");
                scanf("%s",phone);
                Node* cur=search_record(head,phone);
                if (cur != NULL) 
                    print_record(cur);
                break;
            }
            case 4:
                updateRecord(head);
                break;
            case 5:
                deleteRecord(&head);
                break;
            case 6:
                listByProvince(head);
                break;
            case 7: 
                statisticsByProvince(head);
                break;
            case 8: 
                //checkDuplicate();
                break;
            case 9:
                //readingFile();
                break;
            case 0:
                printf("Da thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(choice != 0);

    return 0;
}
