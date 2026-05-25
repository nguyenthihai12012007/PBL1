#ifndef MENU_H
#define MENU_H

#include "record.h"

void menu_update(Node* head,char currentUsername[]);
void menu_admin();
void menu_staff();
void statisticsMenu();
void menu_manage(Node **head,char currentUsername[]);
void menu_search();
void menu_statistical();
void menu_account();

#endif