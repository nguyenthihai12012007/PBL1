#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "print.h"
#include "constants.h"
#include "function.h"

void menu_update(Node* head) {
    int choice;

    do {
        printf("\n");
        printSpace();
        printf("1. Sua ten\n");
        printSpace();
        printf("2. Sua dia chi\n");
        printSpace();
        printf("3. Sua so dien thoai\n");
        printSpace();
        printf("4. Sua trang thai hoat dong\n");
        printSpace();
        printf("0. Thoat\n");
        printSpace();
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printSpace();
                printf("Nhap ten moi: ");
                fgets(head->data.name, sizeof(head->data.name), stdin);
                head->data.name[strcspn(head->data.name, "\n")] = '\0';
                printSpace();
                printf("Sua ten thanh cong!\n");
                pauseScreen();
                break;

            case 2:
                printSpace();
                printf("Nhap dia chi moi: ");
                fgets(head->data.address,sizeof(head->data.address),stdin);
                head->data.address[strcspn(head->data.address,"\n")]='\0';
                printSpace();
                printf("Sua dia chi thanh cong!\n");
                pauseScreen();
                break;

            case 3:
                printSpace();
                printf("Nhap so moi: ");
                do {
                    scanf("%s", head->data.phone);
                    if (!validatePhone(head->data.phone)) {
                        printSpace();
                        printf(RED BOLD "So dien thoai khong hop le! Nhap lai: " RESET);
                    }
                } while (!validatePhone(head->data.phone));
                getchar();
                printSpace();
                printf("Sua so thue bao thanh cong!\n");
                pauseScreen();
                break;

            case 4: 
                printSpace();
                printf("Nhap trang thai moi: ");
                head->data.status = inputStatus();
                printSpace();
                printf("Sua trang thai thanh cong!\n");
                pauseScreen();
                break;

            case 0:
                printSpace();
                printf("Thoat!\n");
                break;

            default:
                printSpace();
                printf(RED BOLD "   Lua chon khong hop le!\n" RESET);
                pauseScreen();
        }

    } while (choice != 0);
}

void menu_admin() {
    printf("\n");
    printSystemHeader("CHUC NANG CUA ADMIN");
    printSpace();
    printf("| [1] %-64s |\n", "Quan ly thue bao");
    printSpace();
    printf("| [2] %-64s |\n", "Tra cuu thue bao");
    printSpace();
    printf("| [3] %-64s |\n", "Thong ke & Cuoc");
    printSpace();
    printf("| [4] %-64s |\n", "Quan ly tai khoan");
    printSpace();
    printf("| [0] %-64s |\n", "Dang xuat");
    printSystemFooter();
}

void menu_staff() {
    printf("\n");
    printSystemHeader("CHUC NANG CUA NHAN VIEN");
    printSpace();
    printf("| [1] %-64s |\n", "Tra cuu thong tin thue bao");
    printSpace();
    printf("| [2] %-64s |\n", "Kiem tra trang thai thue bao");
    printSpace();
    printf("| [3] %-64s |\n", "Liet ke thue bao theo tinh thanh");
    printSpace();
    printf("| [4] %-64s |\n", "Tinh cuoc cho khach hang");
    printSpace();
    printf("| [0] %-64s |\n", "Dang xuat");
    printSystemFooter();
}

void menu_manage(Node **head) {
    printf("\n");
    int choice;
    do {
        printf("\n");
        printSystemHeader("Quan ly thue bao");
        printSpace();
        printf("| " YELLOW "1." RESET " %-65s |\n", "Them thue bao");
        printSpace();
        printf("| " YELLOW "2." RESET " %-65s |\n", "Sua thue bao");
        printSpace();
        printf("| " YELLOW "3." RESET " %-65s |\n", "Xoa thue bao");
        printSpace();
        printf("| " YELLOW "4." RESET " %-65s |\n", "Doc file du lieu");
        printSpace();
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');  
                printSpace();               
                printf(RED BOLD "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {   
                printSpace();             
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                Record newR = inputRecord();
                addRecord(head,newR);
                saveRecordToFile("data1.txt", *head);
                printSpace();
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
                printSpace();
                printf("\nQuay lai menu chinh...\n");
                break;
            default:
                printSpace();
                printf(RED BOLD "\n   Lua chon khong hop le!" RESET);
        }
        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}

void menu_search(Node *head) {
    printf("\n");
    int choice;
    do {
        printf("\n");
        printSystemHeader("Tra cuu thue bao");
        printSpace();
        printf("| " YELLOW "1." RESET " %-65s |\n", "Tim kiem thue bao");
        printSpace();
        printf("| " YELLOW "2." RESET " %-65s |\n", "Loc thue bao theo tinh thanh");
        printSpace();
        printf("| " YELLOW "3." RESET " %-65s |\n", "Loc thue bao theo trang thai");
        printSpace();
        printf("| " YELLOW "4." RESET " %-65s |\n", "Kiem tra trung thue bao");
        printSpace();
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');  
                printSpace();               
                printf(RED BOLD "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {  
                printSpace();              
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                char phone[15];
                printf("\n");
                printSpace();
                printf("Nhap so dien thoai thue bao can tim: ");
                do {
                    scanf("%s",phone);
                    if (!validatePhone(phone)) {
                        printSpace();
                        printf(RED BOLD "So dien thoai khong hop le! Nhap lai: " RESET);
                    }
                } while (!validatePhone(phone));

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
                printf("\n");
                printSpace();
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace();
                printf(RED BOLD "   Lua chon khong hop le!" RESET);
        }

        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}

void statisticsMenu(Node *head) {
    printf("\n");
    int choice;
    do {
        printf("\n");
        printSystemHeader("Menu thong ke");
        printSpace();
        printf("| " YELLOW "1." RESET " %-65s |\n", "Thong ke so thue bao theo tinh");
        printSpace();
        printf("| " YELLOW "2." RESET " %-65s |\n", "Tinh nhieu thue bao nhat");
        printSpace();
        printf("| " YELLOW "3." RESET " %-65s |\n", "Xuat bao cao thong ke ra file");
        printSpace();
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n'); 
                printSpace();                
                printf(RED BOLD "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 5) {   
                printSpace();             
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
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
                printf("\n");
                printSpace();
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace();
                printf(RED BOLD "   Lua chon khong hop le!" RESET);
        }

        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}

void menu_statistical(Node *head) {
    printf("\n");
    int choice;
    do {
        printf("\n");
        printSystemHeader("Thong ke & Cuoc");
        printSpace();
        printf("| " YELLOW "1." RESET " %-65s |\n", "Thong ke thue bao");
        printSpace();
        printf("| " YELLOW "2." RESET " %-65s |\n", "Thong ke doanh thu");
        printSpace();
        printf("| " YELLOW "3." RESET " %-65s |\n", "Tinh cuoc thue bao");
        printSpace();
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');   
                printSpace();              
                printf(RED BOLD "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {       
                printSpace();         
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                statisticsMenu(head);
                continue;
            }
            case 2: 
                revenue(head);
                break;
            case 3:
                calculateFee(head);
                break;
            case 0:
                printf("\n");
                printSpace();
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace();
                printf(RED BOLD "   Lua chon khong hop le!" RESET);
        }
        if (choice != 0) {
            endScreen();
        }
    } while(choice != 0);
}

void menu_account(AccountNode **head) {
    printf("\n");
    int choice;
    do{
        printf("\n");
        printSystemHeader("Quan ly tai khoan");
        printSpace();
        printf("| " YELLOW "1." RESET " %-65s |\n", "Them nhan vien");
        printSpace();
        printf("| " YELLOW "2." RESET " %-65s |\n", "Xoa nhan vien");
        printSpace();
        printf("| " YELLOW "3." RESET " %-65s |\n", "Sua nhan vien");
        printSpace();
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');  
                printSpace();               
                printf(RED BOLD "Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 3) {   
                printSpace();             
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: 
                addAccount(head);
                break;
            case 2: 
                deleteAccount(head);
                break;
            case 3:
                updateAccount(*head);
                break;
            case 0:
                printf("\n");
                printSpace();
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace();
                printf(RED BOLD "   Lua chon khong hop le!" RESET);
        }
        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}
