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

Record inputRecord() {
    Record R;

    printf("Nhap so dien thoai: ");
    scanf("%s", R.phone);
    getchar();

    printf("Nhap ten don vi: ");
    fgets(R.name,sizeof(R.name),stdin);
    R.name[strcspn(R.name,"\n")]='\0';

    printf("Nhap dia chi: ");
    fgets(R.address,sizeof(R.address),stdin);
    R.address[strcspn(R.address,"\n")]='\0';

    printf("Nhap tinh: ");
    fgets(R.province.tentinh,sizeof(R.province.tentinh),stdin);
    R.province.tentinh[strcspn(R.province.tentinh,"\n")]='\0';

    return R;
}

void addRecord(Node** head,Record R) {
    Node* newNode = createNode(R);

    if (*head == NULL) {
        *head = newNode;
        return ;
    }

    Node* temp = *head;

    while(temp->next != NULL) {
        temp=temp->next;
    }

    temp->next = newNode;
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
            return cur;
        }
        cur=cur->next;
    }
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
        printf("Nhap so dien thoai thue bao can sua:\n");
        scanf("%s",phone);

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

int main() {
    // Tạo danh sách giả lập
    Node* head = NULL;

    Node* n1 = (Node*)malloc(sizeof(Node));
    strcpy(n1->data.name, "An");
    strcpy(n1->data.phone, "0123");
    strcpy(n1->data.address, "HCM");
    strcpy(n1->data.province.tentinh, "TPHCM");
    n1->next = NULL;

    Node* n2 = (Node*)malloc(sizeof(Node));
    strcpy(n2->data.name, "Binh");
    strcpy(n2->data.phone, "0456");
    strcpy(n2->data.address, "Ha Noi");
    strcpy(n2->data.province.tentinh, "HN");
    n2->next = NULL;

    // nối list
    head = n1;
    n1->next = n2;

    // ===== TEST =====
    updateRecord(head);

    return 0;
}