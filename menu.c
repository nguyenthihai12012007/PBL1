#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "print.h"
#include "constants.h"
#include "function.h"

void menu_update(Node* head,char currentUsername[]) {
    int choice;

    do {
        printf("\n");
        printSpace(65);
        printf("1. Sua ten\n");
        printSpace(65);
        printf("2. Sua dia chi\n");
        printSpace(65);
        printf("3. Sua so dien thoai\n");
        printSpace(65);
        printf("4. Sua tinh\n");
        printSpace(65);
        printf("5. Sua trang thai hoat dong\n");
        printSpace(65);
        printf("0. Thoat\n");
        printSpace(65);
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:{
                printf("\n");
                printSpace(65);
                char oldName[50];
                char detail[200];

                strcpy(oldName,head->data.name);

                printf("Nhap ten moi: ");
                fgets(head->data.name, sizeof(head->data.name), stdin);
                head->data.name[strcspn(head->data.name, "\n")] = '\0';
                showUpdateResult(head, "Sua ten thanh cong!");

                snprintf(detail, sizeof(detail),
                        "Sua ten thue bao tu \"%s\" thanh \"%s\"",
                        oldName,
                        head->data.name);

                writeHistory(currentUsername,"Sua thue bao",head->data.phone,detail);
                pauseScreen();
                break;
            }
            case 2:{
                printf("\n");
                printSpace(65);

                char oldAddress[50];
                char detail[200];

                strcpy(oldAddress,head->data.address);

                printf("Nhap dia chi moi: ");
                fgets(head->data.address,sizeof(head->data.address),stdin);
                head->data.address[strcspn(head->data.address,"\n")]='\0';
                showUpdateResult(head, "Sua dia chi thanh cong!");

                snprintf(detail,sizeof(detail),
                        "Sua dia chi thue bao tu \"%s\" thanh \"%s\""
                        ,oldAddress,head->data.address);

                writeHistory(currentUsername,"Sua dia chi",head->data.phone,detail);
                pauseScreen();
                break;
            }
            case 3:{
                printf("\n");
                printSpace(65);

                char oldPhone[50];
                char lastSix[7];
                char detail[200];
                strcpy(oldPhone,head->data.phone);

                printf("Nhap 6 so cuoi moi: ");
                do {
                    scanf("%s", lastSix);
                    if (!validateLastSix(lastSix)) {
                        printSpace(65);
                        printf(RED BOLD "So dien thoai khong hop le! Nhap lai: " RESET);
                    }
                } while (!validateLastSix(lastSix));
                getchar();
                char *prefix = findPrefixByProvince(head->data.province.tentinh);
                if(prefix != NULL) {
                    strcpy(head->data.phone, prefix);
                    strcat(head->data.phone, lastSix);
                }
                showUpdateResult(head, "Sua so thue bao thanh cong!");

                snprintf(detail,sizeof(detail),
                        "Sua so thue bao tu \"%s\" thanh \"%s\""
                        ,oldPhone,head->data.phone);

                writeHistory(currentUsername,"Sua so thue bao",head->data.phone,detail);
                pauseScreen();
                break;
            }
            case 4: {
                printf("\n");
                printSpace(65);

                char oldProvince[50];
                char oldPhone[20];
                char newProvince[50];
                char detail[250];
                char *prefix = NULL;

                strcpy(oldProvince, head->data.province.tentinh);
                strcpy(oldPhone, head->data.phone);

                printf("Nhap tinh moi: ");

                do {
                    fgets(newProvince, sizeof(newProvince), stdin);
                    newProvince[strcspn(newProvince, "\n")] = '\0';

                    toLowerCase(newProvince);

                    if (!validateInput(newProvince)) {
                        printSpace(65);
                        printf(RED BOLD "Tinh khong hop le! Vui long nhap lai: " RESET);
                        continue;
                    }

                    prefix = findPrefixByProvince(newProvince);

                    if (prefix == NULL) {
                        printSpace(65);
                        printf(RED BOLD "Tinh khong co trong danh sach ma vung! Nhap lai: " RESET);
                    }

                } while (!validateInput(newProvince) || prefix == NULL);

                strcpy(head->data.province.tentinh, newProvince);

                updatePhoneAreaCode(&head->data);

                printf("\n");
                printSpace(65);
                printf(GREEN BOLD "Sua tinh thanh cong!\n" RESET);

                printSpace(65);
                printf("So dien thoai moi: %s\n", head->data.phone);

                snprintf(detail, sizeof(detail),
                        "Sua tinh tu \"%s\" thanh \"%s\", so dien thoai tu \"%s\" thanh \"%s\"",
                        oldProvince,
                        head->data.province.tentinh,
                        oldPhone,
                        head->data.phone);

                writeHistory(currentUsername, "Sua tinh", head->data.phone, detail);

                pauseScreen();
                break;
            }
            case 5: {
                printf("\n");
                int oldStatus = head->data.status;
                char detail[200];

                //printf("Nhap trang thai moi:\n");
                head->data.status = inputStatus();

                showUpdateResult(head, "Sua trang thai thanh cong!");

                snprintf(detail, sizeof(detail),
                        "Sua trang thai thue bao tu \"%d\" thanh \"%d\"",
                        oldStatus,
                        head->data.status);

                writeHistory(currentUsername, "Sua trang thai", head->data.phone, detail);

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
                printf(RED BOLD "   Lua chon khong hop le!\n" RESET);
                pauseScreen();
        }

    } while (choice != 0);
}

void menu_admin() {
    printf("\n");
    printSystemHeader("CHUC NANG CUA ADMIN");
    printSpace(65);
    printf("| [1] %-64s |\n", "Quan ly thue bao");
    printSpace(65);
    printf("| [2] %-64s |\n", "Tra cuu thue bao");
    printSpace(65);
    printf("| [3] %-64s |\n", "Thong ke & Cuoc");
    printSpace(65);
    printf("| [4] %-64s |\n", "Quan ly tai khoan");
    printSpace(65);
    printf("| [5] %-64s |\n", "Xem lich su thay doi");
    printSpace(65);
    printf("| [0] %-64s |\n", "Dang xuat");
    printSystemFooter();
}

void menu_staff() {
    printf("\n");
    printSystemHeader("CHUC NANG CUA NHAN VIEN");
    printSpace(65);
    printf("| [1] %-64s |\n", "Tra cuu thong tin thue bao");
    printSpace(65);
    printf("| [2] %-64s |\n", "Kiem tra trang thai thue bao");
    printSpace(65);
    printf("| [3] %-64s |\n", "Liet ke thue bao theo tinh thanh");
    printSpace(65);
    printf("| [4] %-64s |\n", "Tinh cuoc cho khach hang");
    printSpace(65);
    printf("| [0] %-64s |\n", "Dang xuat");
    printSystemFooter();
}

void menu_manage(Node **head,char currentUsername[]) {
    printf("\n");
    int choice;
    do {
        printf("\n");
        printSystemHeader("Quan ly thue bao");
        printSpace(65);
        printf("| " YELLOW "1." RESET " %-65s |\n", "Them thue bao");
        printSpace(65);
        printf("| " YELLOW "2." RESET " %-65s |\n", "Sua thue bao");
        printSpace(65);
        printf("| " YELLOW "3." RESET " %-65s |\n", "Xoa thue bao");
        printSpace(65);
        printf("| " YELLOW "4." RESET " %-65s |\n", "Doc file du lieu");
        printSpace(65);
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');  
                printSpace(65);               
                printf(RED BOLD "   Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {   
                printSpace(65);             
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: {
                Record newR = inputRecord();
                addRecordByUser(head,newR,currentUsername);
                saveRecordToFile("data1.txt", *head);
                printSpace(65);
                printf("Da them thue bao va luu vao file thanh cong!\n");
                break;
            }
            case 2: 
                updateRecord(*head, currentUsername);
                break;
            case 3:
                deleteRecord(head, currentUsername);
                break;
            case 4:
                readFileByUser(head, currentUsername);
                break;
            case 0:
                printf("\n");
                printSpace(65);
                printf("Quay lai menu chinh...\n");
                break;
            default:
                printSpace(65);
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
        printSpace(65);
        printf("| " YELLOW "1." RESET " %-65s |\n", "Tim kiem thue bao");
        printSpace(65);
        printf("| " YELLOW "2." RESET " %-65s |\n", "Loc thue bao theo tinh thanh");
        printSpace(65);
        printf("| " YELLOW "3." RESET " %-65s |\n", "Loc thue bao theo trang thai");
        printSpace(65);
        printf("| " YELLOW "4." RESET " %-65s |\n", "Kiem tra trung thue bao");
        printSpace(65);
        printf("| " YELLOW "5." RESET " %-65s |\n", "Danh sach danh ba");
        printSpace(65);
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');  
                printSpace(65);               
                printf(RED BOLD "   Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 5) {  
                printSpace(65);              
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

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
                    printf(RED BOLD "Khong tim thay so dien thoai nay!\n" RESET);
                    printf("\n");
                    printSpace(65);
                    printf("Goi y cac so thue bao gan dung:\n");
                    suggestSimilarPhone(head, phone);
                }

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
            case 5:
                print_all_record(head);
                break;
            case 0:
                printf("\n");
                printSpace(65);
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace(65);
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
        printSpace(65);
        printf("| " YELLOW "1." RESET " %-65s |\n", "Thong ke so thue bao theo tinh");
        printSpace(65);
        printf("| " YELLOW "2." RESET " %-65s |\n", "Tinh nhieu thue bao nhat");
        printSpace(65);
        printf("| " YELLOW "3." RESET " %-65s |\n", "Xuat bao cao thong ke ra file");
        printSpace(65);
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n'); 
                printSpace(65);                
                printf(RED BOLD "   Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 5) {   
                printSpace(65);             
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
                printSpace(65);
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace(65);
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
        printSpace(65);
        printf("| " YELLOW "1." RESET " %-65s |\n", "Thong ke thue bao");
        printSpace(65);
        printf("| " YELLOW "2." RESET " %-65s |\n", "Thong ke doanh thu");
        printSpace(65);
        printf("| " YELLOW "3." RESET " %-65s |\n", "Tinh cuoc thue bao");
        printSpace(65);
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');   
                printSpace(65);              
                printf(RED BOLD "   Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 4) {       
                printSpace(65);         
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
                revenueStatistics(head);
                break;
            case 3:
                calculateFee(head);
                break;
            case 0:
                printf("\n");
                printSpace(65);
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace(65);
                printf(RED BOLD "   Lua chon khong hop le!" RESET);
        }
        if (choice != 0) {
            endScreen();
        }
    } while(choice != 0);
}

void menu_account(AccountNode **head,char currentUsername[]) {
    printf("\n");
    int choice;
    do{
        printf("\n");
        printSystemHeader("Quan ly tai khoan");
        printSpace(65);
        printf("| " YELLOW "1." RESET " %-65s |\n", "Them nhan vien");
        printSpace(65);
        printf("| " YELLOW "2." RESET " %-65s |\n", "Xoa nhan vien");
        printSpace(65);
        printf("| " YELLOW "3." RESET " %-65s |\n", "Sua nhan vien");
        printSpace(65);
        printf("| " RED "0." RESET " %-65s |\n", "Quay lai");
        printSystemFooter();

        while (1) {                       
            if(scanf("%d", &choice) != 1) {  
                while(getchar() != '\n');  
                printSpace(65);               
                printf(RED BOLD "   Loi: Vui long nhap so! Nhap lai: " RESET);                             
                continue;            
            }            
            if(choice < 0 || choice > 3) {   
                printSpace(65);             
                printf(RED BOLD "   Lua chon khong hop le! Nhap lai: " RESET);                
                continue;            
            }            
            break;        
        } 

        switch(choice) {
            case 1: 
                addAccount(head, currentUsername);
                break;
            case 2: 
                deleteAccount(head, currentUsername);
                break;
            case 3:
                updateAccount(*head, currentUsername);
                break;
            case 0:
                printf("\n");
                printSpace(65);
                printf("Quay lai menu chinh...\n");
                break;
            
            default:
                printf("\n");
                printSpace(65);
                printf(RED BOLD "   Lua chon khong hop le!" RESET);
        }
        if (choice != 0) {
            endScreen();
        }

    } while(choice != 0);
}
