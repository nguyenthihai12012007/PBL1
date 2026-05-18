#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "print.h"
#include "constants.h"
#include "function.h"

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
                do {
                    scanf("%s", head->data.phone);
                    if (!validatePhone(head->data.phone)) {
                        printf("So dien thoai khong hop le! Nhap lai: ");
                    }
                } while (!validatePhone(head->data.phone));
                getchar();
                printf("Sua so thue bao thanh cong!\n");
                pauseScreen();
                break;

            case 4: 
                printf("Nhap trang thai moi: ");
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

void menu_admin() {
    printf(CYAN BOLD);
    printf("=======================================================\n");
    printf("               CHUC NANG CUA ADMIN\n");
    printf("=======================================================\n");
    printf(RESET);
    printf(YELLOW);
    printf("| 1. %-45s |\n", "Quan ly thue bao");
    printf("| 2. %-45s |\n", "Tra cuu thue bao");
    printf("| 3. %-45s |\n", "Thong ke & Cuoc");
    printf("| 4. %-45s |\n", "Quan ly tai khoan");
    printf("| 0. %-45s |\n", "Dang xuat");
    printf(RESET);
    printf("=======================================================\n");
    printf(GREEN BOLD);
    printf("Nhap lua chon cua ban: ");
    printf(RESET);
}

void menu_staff() {
    printf(CYAN BOLD);
    printf("=======================================================\n");
    printf("               CHUC NANG CUA NHAN VIEN\n");
    printf("=======================================================\n");
    printf(RESET);
    printf(YELLOW);
    printf("| 1. %-45s |\n", "Tra cuu thong tin thue bao");
    printf("| 2. %-45s |\n", "Kiem tra trang thai thue bao");
    printf("| 3. %-45s |\n", "Liet ke thue bao theo tinh thanh");
    printf("| 4. %-45s |\n", "Tinh cuoc cho khach hang");
    printf("| 0. %-45s |\n", "Dang xuat");
    printf(RESET);
    printf("=======================================================\n");
    printf(GREEN BOLD);
    printf("Nhap lua chon cua ban: ");
    printf(RESET);
}

void statisticsMenu(Node *head) {
    int choice;
    do {
        printf("\n");
        printf(CYAN BOLD);
        printf("+===========================================+\n");
        printf("|               Menu thong ke               |\n");
        printf("+===========================================+\n");
        printf(RESET);
        printf("| " YELLOW "1." RESET " Thong ke so thue bao theo tinh         |\n");
        printf("| " YELLOW "2." RESET " Tinh nhieu thue bao nhat               |\n");
        printf("| " YELLOW "3." RESET " Xuat bao cao thong ke ra file          |\n");
        printf("| " RED "0." RESET " Quay lai                               |\n");
        printf(CYAN);
        printf("+===========================================+\n");
        printf(RESET);
        printf(GREEN "Nhap lua chon cua ban: " RESET); 

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');                 
                printf(RED "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 5) {                
                printf(RED "Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        }        
        
        switch(choice) {
            case 1:
                statisticsByProvince(head);
                break;
            
            case 2: 
                pronvinceMaxRecord(head);
                break;
            case 3:
                exportReport(head);
                break;
                
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("Lua chon khong hop le!");
        }

        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}

void menu_manage(Node **head) {
    int choice;
    do {
        printf("\n");
        printf(CYAN BOLD);
        printf("+===========================================+\n");
        printf("|             Quan ly thue bao              |\n");
        printf("+===========================================+\n");
        printf(RESET);
        printf("| " YELLOW "1." RESET " Them thue bao                          |\n");
        printf("| " YELLOW "2." RESET " Sua thue bao                           |\n");
        printf("| " YELLOW "3." RESET " Xoa thue bao                           |\n");
        printf("| " YELLOW "4." RESET " Doc file du lieu                       |\n");
        printf("| " RED "0." RESET " Quay lai                               |\n");
        printf(CYAN);
        printf("+===========================================+\n");
        printf(RESET);
        printf(GREEN "Nhap lua chon cua ban: " RESET); 

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');                 
                printf(RED "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {                
                printf(RED "Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                Record newR = inputRecord();
                addRecord(head,newR);
                saveToFile("data1.txt", *head);
                printf("Da them thue bao va luu vao file thanh cong!\n");
                break;
            }
            case 2: 
                updateRecord(*head);
                break;
            case 3:
                deleteRecord(head);
                break;
            case 4:
                readFileByUser(head);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            default:
                printf("Lua chon khong hop le!");
        }
        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}

void menu_search(Node *head) {
    int choice;
    do {
        printf("\n");
        printf(CYAN BOLD);
        printf("+===========================================+\n");
        printf("|             Tra cuu thue bao              |\n");
        printf("+===========================================+\n");
        printf(RESET);
        printf("| " YELLOW "1." RESET " Tim kiem thue bao                      |\n");
        printf("| " YELLOW "2." RESET " Loc thue bao theo tinh thanh           |\n");
        printf("| " YELLOW "3." RESET " Loc thue bao theo trang thai           |\n");
        printf("| " YELLOW "4." RESET " Kiem tra trung thue bao                |\n");
        printf("| " RED "0." RESET " Quay lai                               |\n");
        printf(CYAN);
        printf("+===========================================+\n");
        printf(RESET);
        printf(GREEN "Nhap lua chon cua ban: " RESET); 

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');                 
                printf(RED "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {                
                printf(RED "Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                char phone[15];
                printf("Nhap so dien thoai thue bao can tim: ");
                scanf("%s",phone);
                Node* cur=search_record(head,phone);
                if (cur != NULL) 
                    print_record(cur);
                break;
            }
            case 2: 
                listByProvince(head);
                break;
            case 3:
                filterByStatus(head);
                break;
            case 4:
                checkDuplicate(&head);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("Lua chon khong hop le!");
        }

        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}

void menu_statistical(Node *head) {
    int choice;
    do {
        printf("\n");
        printf(CYAN BOLD);
        printf("+===========================================+\n");
        printf("|              Thong ke & Cuoc              |\n");
        printf("+===========================================+\n");
        printf(RESET);
        printf("| " YELLOW "1." RESET " Thong ke thue bao                      |\n");
        printf("| " YELLOW "2." RESET " Thong ke doanh thu                     |\n");
        printf("| " YELLOW "3." RESET " Tinh cuoc thue bao                     |\n");
        printf("| " RED "0." RESET " Quay lai                               |\n");
        printf(CYAN);
        printf("+===========================================+\n");
        printf(RESET);
        printf(GREEN "Nhap lua chon cua ban: " RESET); 

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');                 
                printf(RED "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {                
                printf(RED "Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                statisticsMenu(head);
                break;
            }
            case 2: 
                //thong ke doanh thu
                break;
            case 3:
                calculateFee(head);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("Lua chon khong hop le!");
        }
        if (choice != 0) {
            endScreen();
        }
    } while(choice != 0);
}

void menu_account(AccountNode **head) {
    int choice;
    do{
        printf("\n");
        printf(CYAN BOLD);
        printf("+===========================================+\n");
        printf("|             Quan ly tai khoan             |\n");
        printf("+===========================================+\n");
        printf(RESET);
        printf("| " YELLOW "1." RESET " Them nhan vien                         |\n");
        printf("| " YELLOW "2." RESET " Xoa nhan vien                          |\n");
        printf("| " YELLOW "3." RESET " Sua nhan vien                          |\n");
        printf("| " RED "0." RESET " Quay lai                               |\n");
        printf(CYAN);
        printf("+===========================================+\n");
        printf(RESET);
        printf(GREEN "Nhap lua chon cua ban: " RESET); 

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');                 
                printf(RED "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 3) {                
                printf(RED "Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: 
                addAccount(head);
                endScreen();
                break;
            case 2: 
                deleteAccount(head);
                break;
            case 3:
                updateAccount(*head);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("Lua chon khong hop le!");
        }
        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}