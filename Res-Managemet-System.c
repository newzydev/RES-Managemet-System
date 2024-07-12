// It is recommended to open the source code through Visual Studio Code.
// แนะนำให้เปิด Source Code ผ่าน Visual Studio Code

// Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <unistd.h>

// Code Color
#define BLUE "\e[1;36m" // กำหนดสีข้อความน้ำเงิน
#define RESET "\e[0m" // รีเซ็ตสีข้อความ

// โครงสร้างของบุคคล
struct Person {
    char username[50];
    char password[50];
    char firstname[50];
    char lastname[50];
    char role[50];
    struct Person* next;
};

// โครงสร้างของรายการอาหาร
struct MenuItem {
    char menu_id[50];
    char menu_name[50];
    double menu_price;
    char menu_cat[50];
    struct MenuItem* next;
};

// โครงสร้างของใบเสร็จรับเงิน
struct Receiption {
    char or_id[50];
    double or_total_price;
    int or_total_quantity;
    double or_discount;
    double or_net_total;
    double or_get_money;
    double or_change;
    char username[50];
    char firstname[50];
    char lastname[50];
    struct Receiption* next;
};

// Function prototypes
// โหลดใฟล์ to linked list
void load_file_person(struct Person** head_person);
void load_file_menuitem(struct MenuItem** head_menuitem);
void load_file_receiption(struct Receiption** head_receiption);
void free_person(struct Person* head_person);
void free_menuitem(struct MenuItem* head_menuitem);
void free_receiption(struct Receiption* head_receiption);
// sorting เรียงลำดับข้อมูล
int compare_menu_id(const void* a, const void* b);
void sort_menu_items(struct MenuItem* head_menuitem);
// login
int login(const char* inputUsername, const char* inputPassword, const struct Person* head_person);
// admin case 1
void admin_register_admin(struct Person** head_person, char username[], char password[], char firstname[], char lastname[]);
void admin_person_savetofile(struct Person* head_person, char username[], char password[], char firstname[], char lastname[]);
// admin case 2
void admin_register_cashier(struct Person** head_person, char username[], char password[], char firstname[], char lastname[]);
void admin_cashier_savetofile(struct Person* head_person, char username[], char password[], char firstname[], char lastname[]);
// admin case 3
void admin_update_person(struct Person* head_person, char username[]);
// admin case 4
void admin_delete_person(struct Person** head_person, char username[]);
// admin case 5
void admin_insert_food(struct MenuItem** head_menuitem, char menu_id[], char menu_name[], double menu_price);
void admin_food_savetofile(struct MenuItem* head_menuitem, char menu_id[], char menu_name[], double menu_price);
// admin case 6
void admin_insert_drink(struct MenuItem** head_menuitem, char menu_id[], char menu_name[], double menu_price);
void admin_drink_savetofile(struct MenuItem* head_menuitem, char menu_id[], char menu_name[], double menu_price);
// admin case 7
void admin_update_menuitem(struct MenuItem* head_menuitem, char menu_id[]);
// admin case 8
void admin_delete_menuitem(struct MenuItem** head_menuitem, char menu_id[]);
// admin case 9.1
void admin_list_show_admin(struct Person* head_person);
// admin case 9.2
void admin_list_show_cashier(struct Person* head_person);
// admin case 9.3
void admin_list_show_person(struct Person* head_person);
// admin case 10.1
void admin_list_show_food(struct MenuItem* head_menuitem);
// admin case 10.2
void admin_list_show_drink(struct MenuItem* head_menuitem);
// admin case 10.3
void admin_list_show_menuitem(struct MenuItem* head_menuitem);
// admin case 11
void admin_list_show_receiption_table_1(struct Receiption* head_receiption);
void admin_list_show_receiption_table_2(struct Receiption* head_receiption);
void admin_list_show_receiption_table_3(struct Receiption* head_receiption);
// cashier case 1
void cashier_list_show_food(struct MenuItem* head_menuitem);
void cashier_list_show_drink(struct MenuItem* head_menuitem);
void cashier_list_show_menuitem(struct MenuItem* head_menuitem);
void cashier_insert_receiption(struct Receiption** head_receiption, char or_id[], double total_price, int total_quantity, double discount, double net_total, double get_money, double change, char username[], char firstname[], char lastname[]);
void cashier_receiption_savetofile(struct Receiption* head_receiption, char or_id[], double total_price, int total_quantity, double discount, double net_total, double get_money, double change, char username[], char firstname[], char lastname[]);

int main() {
    struct Person* head_person = NULL;
    struct MenuItem* head_menuitem = NULL;
    struct Receiption* head_receiption = NULL;
    load_file_person(&head_person);
    load_file_menuitem(&head_menuitem);
    load_file_receiption(&head_receiption);

    char inputUsername[50]; // ประกาศตัวแปรรับค่าจากผู้ใช้
    char inputPassword[50]; // ประกาศตัวแปรรับค่าจากผู้ใช้
    
    char username[50]; // ประกาศตัวแปรใหม่
    char password[50]; // ประกาศตัวแปรใหม่
    char firstname[50]; // ประกาศตัวแปรใหม่
    char lastname[50]; // ประกาศตัวแปรใหม่
    char role[50]; // ประกาศตัวแปรใหม่

    char menu_name[50];
    double menu_price;
    int ch_case_1,ch_case_1_op_1;
    int ch_case_2;
    int a, b, c, d, e; // ใช้สำหรับ loop ในการแปลงตัวอักษรเป็นตัวพิมพ์ใหญ่
    char ch_logout = 'Y';

    int max_menu_id = 0; // สร้างตัวแปรเพื่อเก็บค่า MENU ITEM ID ที่มากที่สุด
    char menu_id[10]; // ประกาศตัวแปร menu_id เป็นสตริง
    
    int max_or_id = 0;
    char or_id[10];


    // โค้ดสำหรับกำหนดสิทธิ์การเข้าถึงและการเข้าสู่ระบบ
    while (ch_logout != 'N') {
        
        system("cls");
        printf("================================================\n");
        printf("============ RES. MENAGEMENT SYSTEM ============\n");
        printf("================================================\n");
        printf("\n===== WHO HAS THE RIGHT TO USE THE PROGRAM =====\n");
        printf("- ADMINISTRATOR ");
        printf(BLUE"[AD]\n"RESET);
        printf("- CASHIER ");
        printf(BLUE"[CA]\n"RESET);
        printf("\n===== LOGIN TO PROGRAM =====\n");
        printf("INPUT A USERNAME : ");
        printf(BLUE);
        scanf("%s", inputUsername);
        for (a=0;inputUsername[a];a++) {
            inputUsername[a] = toupper(inputUsername[a]); // แปลงตัวอักษรเป็นตัวพิมพ์ใหญ่
        }
        printf(RESET);
        printf("INPUT A PASSWORD : ");
        printf(BLUE);
        scanf("%s", inputPassword);
        for (b=0;inputPassword[b];b++) {
            inputPassword[b] = toupper(inputPassword[b]); // แปลงตัวอักษรเป็นตัวพิมพ์ใหญ่
        }
        printf(RESET);
        
        // printf("\nPROGRAM LOGIN COMPLETE ... ");
        // sleep(1);

        ch_case_menu:
        system("cls");
        if (strstr(inputUsername, "AD") != NULL && strstr(inputPassword, "AD") != NULL) { // ตรวจสอบระดับผู้ใช้งาน ADMINISTRATOR ถูกต้อง
            if (login(inputUsername, inputPassword, head_person)) {
                struct Person* current = head_person;
                while (current != NULL) {
                    if (strcmp(current->username, inputUsername) == 0 && strcmp(current->password, inputPassword) == 0) {
                        strcpy(username, current->username);
                        strcpy(password, current->password);
                        strcpy(firstname, current->firstname);
                        strcpy(lastname, current->lastname);
                        strcpy(role, current->role);
                        break;
                    }
                    current = current->next;
                }
                printf("================================================\n");
                printf("============ RES. MENAGEMENT SYSTEM ============\n");
                printf("================================================\n");
                            
                // โปรใฟล์ผู้ใช้งาน
                printf("\n===== PROFILE LOGIN =====\n");
                printf("USER ID : ");
                printf(BLUE"%s\n"RESET, username);
                printf("FIRSTNAME : ");
                printf(BLUE"%s\n"RESET, firstname);
                printf("LASTNAME : ");
                printf(BLUE"%s\n"RESET, lastname);
                printf("ROLE : ");
                printf(BLUE"%s\n"RESET, role);
                
                // ส่วนเนื้อหา
                printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                printf("[1] REGISTER ADMIN\n");
                printf("[2] REGISTER CASHIER\n");
                printf("[3] UPDATE USER FROM ID\n");
                printf("[4] REMOVE USER FROM ID\n");
                printf("[5] INSERT FOOD MENU\n");
                printf("[6] INSERT DRINK MENU\n");
                printf("[7] UPDATE FOOD AND DRINK MENU FROM ID\n");
                printf("[8] REMOVE FOOD AND DRINK MENU FROM ID\n");
                printf("[9] SHOW ADMIN AND CASHIER [OPTIONS]\n");
                printf("[10] SHOW FOODS AND DRINK [OPTIONS]\n");
                printf("[11] SALES REPORT\n");
                printf("[0] LOGOUT OR EXIT\n");
                printf("\n===== CHOOSE A PROGRAM =====\n");
                printf("SELECT MENU [1-11 OR 0] : ");
                printf(BLUE);
                scanf("%d", &ch_case_1);
                printf(RESET);

                // โค้ดสำหรับตรวจสอบเลือกเมนูและการดำเนินการตามเมนูที่เลือก
                switch (ch_case_1)
                {
                case 0:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);
                    
                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM LOGOUT OR EXIT =====\n");
                    printf("LOGOUT, LOGOUT TO THE LOGIN (Y)\n");
                    printf("EXIT, EXIT TO THE PROGRAM (N)\n");
                    printf("ENTER A KEY (Y/N) : ");
                    printf(BLUE);
                    scanf(" %c", &ch_logout);
                    printf(RESET);
                    ch_logout = toupper(ch_logout);
                    break;
                case 1:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nREGISTER FOR ADMIN\n");
                    printf("- USERNAME : ");
                    printf(BLUE);
                        scanf("%s", username);
                        for (a=0;username[a];a++) {
                            username[a] = toupper(username[a]);
                        }
                    printf(RESET);
                    printf("- PASSWORD : ");
                    printf(BLUE);
                    scanf("%s", password);
                    for (b=0;password[b];b++) {
                        password[b] = toupper(password[b]);
                    }
                    printf(RESET);
                    printf("- firstname : ");
                    printf(BLUE);
                    scanf("%s", firstname);
                    for (c=0;firstname[c];c++) {
                        firstname[c] = toupper(firstname[c]);
                    }
                    printf(RESET);
                    printf("- lastname : ");
                    printf(BLUE);
                    scanf("%s", lastname);
                    for (d=0;lastname[d];d++) {
                        lastname[d] = toupper(lastname[d]);
                    }
                    printf(RESET);

                    // เรียกใช้ฟังก์ชัน
                    admin_register_admin(&head_person, username, password, firstname, lastname);
                    admin_person_savetofile(head_person, username, password, firstname, lastname);

                    printf("\nSUCCESSFULLY REGISTER FOR ADMIN, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 2:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nREGISTER FOR CASHIER\n");
                    printf("- USERNAME : ");
                    printf(BLUE);
                        scanf("%s", username);
                        for (a=0;username[a];a++) {
                            username[a] = toupper(username[a]);
                        }
                    printf(RESET);
                    printf("- PASSWORD : ");
                    printf(BLUE);
                    scanf("%s", password);
                    for (b=0;password[b];b++) {
                        password[b] = toupper(password[b]);
                    }
                    printf(RESET);
                    printf("- firstname : ");
                    printf(BLUE);
                    scanf("%s", firstname);
                    for (c=0;firstname[c];c++) {
                        firstname[c] = toupper(firstname[c]);
                    }
                    printf(RESET);
                    printf("- lastname : ");
                    printf(BLUE);
                    scanf("%s", lastname);
                    for (d=0;lastname[d];d++) {
                        lastname[d] = toupper(lastname[d]);
                    }
                    printf(RESET);

                    // เรียกใช้ฟังก์ชัน
                    admin_register_cashier(&head_person, username, password, firstname, lastname);
                    admin_cashier_savetofile(head_person, username, password, firstname, lastname);

                    printf("\nSUCCESSFULLY REGISTER FOR CASHIER, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 3:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nUPDATE USER FROM ID\n");
                    
                    printf("ENTER THE USERNAME TO UPDATE : ");
                    printf(BLUE);
                    scanf("%s", username);
                    printf(RESET);
                    for (e=0;username[e];e++) {
                        username[e] = toupper(username[e]);
                    }
                    // เรียกใช้ฟังก์ชัน
                    admin_update_person(head_person, username);

                    printf("\nSUCCESSFULLY UPDATE USER, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 4:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nREMOVE USER FROM ID\n");
                    
                    printf("ENTER THE USERNAME TO DELETE : ");
                    printf(BLUE);
                    scanf("%s", username);
                    printf(RESET);
                    for (e=0;username[e];e++) {
                        username[e] = toupper(username[e]);
                    }
                    // เรียกใช้ฟังก์ชัน
                    admin_delete_person(&head_person, username);

                    printf("\nSUCCESSFULLY REMOVE USER, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 5:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");

                    FILE *csv_file_read_food = fopen("./files/menuitem.csv", "r");
                    if (csv_file_read_food == NULL) {
                        printf("Error opening the CSV file.\n");
                    } else {

                        char line[1024];
                        int hasData = 0; // ใช้เพื่อตรวจสอบว่ามีข้อมูลในไฟล์ CSV หรือไม่
                        
                        while (fgets(line, 1024, csv_file_read_food)) {
                            char *token = strtok(line, ",");
                            if (token != NULL) {
                                int current_menu_id = atoi(token);  // แปลงค่าเป็นจำนวนเต็ม
                                if (current_menu_id >= max_menu_id) {
                                    max_menu_id = current_menu_id + 1;  // เพิ่มค่า MENU ITEM ID ที่มากที่สุด
                                }
                                hasData = 1; // มีข้อมูลในไฟล์ CSV
                            }
                        }

                        if (!hasData) {
                            max_menu_id = 1; // ถ้าไม่มีข้อมูลในไฟล์ CSV ให้ max_menu_id เป็น 1
                        }

                        sprintf(menu_id, "%d", max_menu_id); // แปลงจาก int เป็นสตริง

                        fclose(csv_file_read_food);
                        
                        printf("\nMENU ITEM ID LATEST : %d\n", max_menu_id - 1);
                    }

                    printf("\nINSERT FOOD MENU\n");
                    printf("- MENU ID : ");
                    printf(BLUE);
                    printf("%s", menu_id);
                    printf(RESET);
                    printf("\n- MENU NAME : ");
                    printf(BLUE);
                    scanf("%s", menu_name);
                    for (b=0;menu_name[b];b++) {
                        menu_name[b] = toupper(menu_name[b]);
                    }
                    printf(RESET);
                    printf("- MENU PRICE : ");
                    printf(BLUE);
                    scanf("%lf", &menu_price);
                    printf(RESET);

                    // เรียกใช้ฟังก์ชัน
                    admin_insert_food(&head_menuitem, menu_id, menu_name, menu_price);
                    admin_food_savetofile(head_menuitem, menu_id, menu_name, menu_price);

                    printf("\nSUCCESSFULLY INSERT FOOD MENU, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 6:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    
                    FILE *csv_file_read_drink = fopen("./files/menuitem.csv", "r");
                    if (csv_file_read_drink == NULL) {
                        printf("Error opening the CSV file.\n");
                    } else {

                        char line[1024];
                        int hasData = 0; // ใช้เพื่อตรวจสอบว่ามีข้อมูลในไฟล์ CSV หรือไม่
                        
                        while (fgets(line, 1024, csv_file_read_drink)) {
                            char *token = strtok(line, ",");
                            if (token != NULL) {
                                int current_menu_id = atoi(token);  // แปลงค่าเป็นจำนวนเต็ม
                                if (current_menu_id >= max_menu_id) {
                                    max_menu_id = current_menu_id + 1;  // เพิ่มค่า MENU ITEM ID ที่มากที่สุด
                                }
                                hasData = 1; // มีข้อมูลในไฟล์ CSV
                            }
                        }

                        if (!hasData) {
                            max_menu_id = 1; // ถ้าไม่มีข้อมูลในไฟล์ CSV ให้ max_menu_id เป็น 1
                        }

                        sprintf(menu_id, "%d", max_menu_id); // แปลงจาก int เป็นสตริง

                        fclose(csv_file_read_drink);
                        
                        printf("\nMENU ITEM ID LATEST : %d\n", max_menu_id - 1);
                    }

                    printf("\nINSERT DRINK MENU\n");
                    printf("- MENU ID : ");
                    printf(BLUE);
                    printf("%s", menu_id);
                    printf(RESET);
                    printf("\n- MENU NAME : ");
                    printf(BLUE);
                    scanf("%s", menu_name);
                    for (b=0;menu_name[b];b++) {
                        menu_name[b] = toupper(menu_name[b]);
                    }
                    printf(RESET);
                    printf("- MENU PRICE : ");
                    printf(BLUE);
                    scanf("%lf", &menu_price);
                    printf(RESET);

                    // เรียกใช้ฟังก์ชัน
                    admin_insert_drink(&head_menuitem, menu_id, menu_name, menu_price);
                    admin_drink_savetofile(head_menuitem, menu_id, menu_name, menu_price);

                    printf("\nSUCCESSFULLY INSERT DRINK MENU, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 7:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nUPDATE FOOD AND DRINK FROM ID\n");
                    
                    printf("ENTER THE MENU ID TO UPDATE : ");
                    printf(BLUE);
                    scanf("%s", menu_id);
                    printf(RESET);
                    for (e=0;menu_id[e];e++) {
                        menu_id[e] = toupper(menu_id[e]);
                    }
                    // เรียกใช้ฟังก์ชัน
                    admin_update_menuitem(head_menuitem, menu_id);

                    printf("\nSUCCESSFULLY UPDATE FOOD AND DRINK MENU, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 8:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nREMOVE FOOD AND DRINK FROM ID\n");
                    
                    printf("ENTER THE MENU ID TO DELETE : ");
                    printf(BLUE);
                    scanf("%s", menu_id);
                    printf(RESET);
                    for (e=0;menu_id[e];e++) {
                        menu_id[e] = toupper(menu_id[e]);
                    }
                    // เรียกใช้ฟังก์ชัน
                    admin_delete_menuitem(&head_menuitem, menu_id);

                    printf("\nSUCCESSFULLY REMOVE FODD AND DRINK MENU, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 9:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nSHOW ADMIN AND CASHIER\n");
                    
                    printf("[1] ADMIN LIST SHOW\n");
                    printf("[2] CASHIER LIST SHOW\n");
                    printf("[3] SHOW ALL\n");
                    printf("\n===== CHOOSE A PROGRAM =====\n");
                    printf("SELECT MENU [1-3 OR 0] : ");
                    printf(BLUE);
                    scanf("%d", &ch_case_1_op_1);
                    printf(RESET);

                    switch (ch_case_1_op_1)
                    {
                    case 1:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        
                        // โปรใฟล์ผู้ใช้งาน
                        printf("\n===== PROFILE LOGIN =====\n");
                        printf("USER ID : ");
                        printf(BLUE"%s\n"RESET, username);
                        printf("FIRSTNAME : ");
                        printf(BLUE"%s\n"RESET, firstname);
                        printf("LASTNAME : ");
                        printf(BLUE"%s\n"RESET, lastname);
                        printf("ROLE : ");
                        printf(BLUE"%s\n"RESET, role);

                        // ส่วนเนื้อหา
                        printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                        printf("\nADMIN LIST SHOW\n");
                        
                        // เรียกใช้ฟังก์ชัน
                        admin_list_show_admin(head_person);

                        printf("\nSUCCESSFULLY ADMIN LIST SHOW, PRESS THE ENTER KEY ...");
                        getch();
                        goto ch_case_menu;
                        break;
                    case 2:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        
                        // โปรใฟล์ผู้ใช้งาน
                        printf("\n===== PROFILE LOGIN =====\n");
                        printf("USER ID : ");
                        printf(BLUE"%s\n"RESET, username);
                        printf("FIRSTNAME : ");
                        printf(BLUE"%s\n"RESET, firstname);
                        printf("LASTNAME : ");
                        printf(BLUE"%s\n"RESET, lastname);
                        printf("ROLE : ");
                        printf(BLUE"%s\n"RESET, role);

                        // ส่วนเนื้อหา
                        printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                        printf("\nCASHIER LIST SHOW\n");
                        
                        // เรียกใช้ฟังก์ชัน
                        admin_list_show_cashier(head_person);

                        printf("\nSUCCESSFULLY CASHIER LIST SHOW, PRESS THE ENTER KEY ...");
                        getch();
                        goto ch_case_menu;
                        break;
                    case 3:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        
                        // โปรใฟล์ผู้ใช้งาน
                        printf("\n===== PROFILE LOGIN =====\n");
                        printf("USER ID : ");
                        printf(BLUE"%s\n"RESET, username);
                        printf("FIRSTNAME : ");
                        printf(BLUE"%s\n"RESET, firstname);
                        printf("LASTNAME : ");
                        printf(BLUE"%s\n"RESET, lastname);
                        printf("ROLE : ");
                        printf(BLUE"%s\n"RESET, role);

                        // ส่วนเนื้อหา
                        printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                        printf("\nSHOW ALL PERSON\n");
                        
                        // เรียกใช้ฟังก์ชัน
                        admin_list_show_person(head_person);
                        admin_list_show_admin(head_person);
                        admin_list_show_cashier(head_person);

                        printf("\nSUCCESSFULLY SHOW ALL PERSON, PRESS THE ENTER KEY ...");
                        getch();
                        goto ch_case_menu;
                        break;
                    
                    default:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        printf("\nSELECTED MENU INVALID, PRESS THE ENTER KEY ... ");
                        getch();
                        goto ch_case_menu;
                        break;
                    }

                    printf("\nSUCCESSFULLY REMOVE USER, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 10:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nSHOW FOODS AND DRINK\n");
                    
                    printf("[1] FOODS LIST SHOW\n");
                    printf("[2] DRINKS LIST SHOW\n");
                    printf("[3] SHOW ALL\n");
                    printf("\n===== CHOOSE A PROGRAM =====\n");
                    printf("SELECT MENU [1-3 OR 0] : ");
                    printf(BLUE);
                    scanf("%d", &ch_case_1_op_1);
                    printf(RESET);

                    switch (ch_case_1_op_1)
                    {
                    case 1:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        
                        // โปรใฟล์ผู้ใช้งาน
                        printf("\n===== PROFILE LOGIN =====\n");
                        printf("USER ID : ");
                        printf(BLUE"%s\n"RESET, username);
                        printf("FIRSTNAME : ");
                        printf(BLUE"%s\n"RESET, firstname);
                        printf("LASTNAME : ");
                        printf(BLUE"%s\n"RESET, lastname);
                        printf("ROLE : ");
                        printf(BLUE"%s\n"RESET, role);

                        // ส่วนเนื้อหา
                        printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                        printf("\nFOODS LIST SHOW [SOFT IN ASCENDING ORDER]\n");
                        
                        // เรียกใช้ฟังก์ชัน
                        sort_menu_items(head_menuitem);
                        admin_list_show_food(head_menuitem);

                        printf("\nSUCCESSFULLY FOODS LIST SHOW, PRESS THE ENTER KEY ...");
                        getch();
                        goto ch_case_menu;
                        break;
                    case 2:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        
                        // โปรใฟล์ผู้ใช้งาน
                        printf("\n===== PROFILE LOGIN =====\n");
                        printf("USER ID : ");
                        printf(BLUE"%s\n"RESET, username);
                        printf("FIRSTNAME : ");
                        printf(BLUE"%s\n"RESET, firstname);
                        printf("LASTNAME : ");
                        printf(BLUE"%s\n"RESET, lastname);
                        printf("ROLE : ");
                        printf(BLUE"%s\n"RESET, role);

                        // ส่วนเนื้อหา
                        printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                        printf("\nDRINKS LIST SHOW [SOFT IN ASCENDING ORDER]\n");
                        
                        // เรียกใช้ฟังก์ชัน
                        sort_menu_items(head_menuitem);
                        admin_list_show_drink(head_menuitem);

                        printf("\nSUCCESSFULLY DRINKS LIST SHOW, PRESS THE ENTER KEY ...");
                        getch();
                        goto ch_case_menu;
                        break;
                    case 3:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        
                        // โปรใฟล์ผู้ใช้งาน
                        printf("\n===== PROFILE LOGIN =====\n");
                        printf("USER ID : ");
                        printf(BLUE"%s\n"RESET, username);
                        printf("FIRSTNAME : ");
                        printf(BLUE"%s\n"RESET, firstname);
                        printf("LASTNAME : ");
                        printf(BLUE"%s\n"RESET, lastname);
                        printf("ROLE : ");
                        printf(BLUE"%s\n"RESET, role);

                        // ส่วนเนื้อหา
                        printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                        printf("\nSHOW ALL FOODS AND DRINK [SOFT IN ASCENDING ORDER]\n");
                        
                        // เรียกใช้ฟังก์ชัน
                        sort_menu_items(head_menuitem);
                        admin_list_show_menuitem(head_menuitem);
                        admin_list_show_food(head_menuitem);
                        admin_list_show_drink(head_menuitem);

                        printf("\nSUCCESSFULLY SHOW ALL FOODS AND DRINK, PRESS THE ENTER KEY ...");
                        getch();
                        goto ch_case_menu;
                        break;
                    
                    default:
                        system("cls");
                        printf("================================================\n");
                        printf("============ RES. MENAGEMENT SYSTEM ============\n");
                        printf("================================================\n");
                        printf("\nSELECTED MENU INVALID, PRESS THE ENTER KEY ... ");
                        getch();
                        goto ch_case_menu;
                        break;
                    }

                    printf("\nSUCCESSFULLY REMOVE USER, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                case 11:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM ADMINISTRATOR =====\n");
                    printf("\nSALES REPORT [SOFT IN DESCENDING ORDER]\n");
                    
                    // เรียกใช้ฟังก์ชัน
                    admin_list_show_receiption_table_1(head_receiption);
                    admin_list_show_receiption_table_2(head_receiption);
                    admin_list_show_receiption_table_3(head_receiption);

                    printf("\nSUCCESSFULLY SALES REPORT, PRESS THE ENTER KEY ...");
                    getch();
                    goto ch_case_menu;
                    break;
                
                default:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    printf("\nSELECTED MENU INVALID, PRESS THE ENTER KEY ... ");
                    getch();
                    goto ch_case_menu;
                    break;
                }

            } else {
                printf("================================================\n");
                printf("============ RES. MENAGEMENT SYSTEM ============\n");
                printf("================================================\n");
                printf("\nACCESS DENIED.\nWRONG USERNAME OR PASSWORD.\nPRESS THE ENTER KEY ... ");
                getch();
                ch_logout = 'Y';
            }
        } else if (strstr(inputUsername, "CA") != NULL && strstr(inputPassword, "CA") != NULL) { // ตรวจสอบระดับผู้ใช้งาน CASHIER ถูกต้อง
            if (login(inputUsername, inputPassword, head_person)) {
                struct Person* current = head_person;
                while (current != NULL) {
                    if (strcmp(current->username, inputUsername) == 0 && strcmp(current->password, inputPassword) == 0) {
                        strcpy(username, current->username);
                        strcpy(password, current->password);
                        strcpy(firstname, current->firstname);
                        strcpy(lastname, current->lastname);
                        strcpy(role, current->role);
                        break;
                    }
                    current = current->next;
                }
                printf("================================================\n");
                printf("============ RES. MENAGEMENT SYSTEM ============\n");
                printf("================================================\n");
                            
                // โปรใฟล์ผู้ใช้งาน
                printf("\n===== PROFILE LOGIN =====\n");
                printf("USER ID : ");
                printf(BLUE"%s\n"RESET, username);
                printf("FIRSTNAME : ");
                printf(BLUE"%s\n"RESET, firstname);
                printf("LASTNAME : ");
                printf(BLUE"%s\n"RESET, lastname);
                printf("ROLE : ");
                printf(BLUE"%s\n"RESET, role);
                
                // ส่วนเนื้อหา
                printf("\n===== PROGRAM CASHIER =====\n");
                printf("[1] ADD OF ORDER AND PAYMENT\n");
                printf("[0] LOGOUT OR EXIT\n");
                printf("\n===== CHOOSE A PROGRAM =====\n");
                printf("SELECT MENU [1 OR 0] : ");
                printf(BLUE);
                scanf("%d", &ch_case_2);
                printf(RESET);

                // โค้ดสำหรับตรวจสอบเลือกเมนูและการดำเนินการตามเมนูที่เลือก
                switch (ch_case_2)
                {
                case 0:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");

                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);
                    
                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM LOGOUT OR EXIT =====\n");
                    printf("LOGOUT, LOGOUT TO THE LOGIN (Y)\n");
                    printf("EXIT, EXIT TO THE PROGRAM (N)\n");
                    printf("ENTER A KEY (Y/N) : ");
                    printf(BLUE);
                    scanf(" %c", &ch_logout);
                    printf(RESET);
                    ch_logout = toupper(ch_logout);
                    break;
                case 1:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    
                    // โปรใฟล์ผู้ใช้งาน
                    printf("\n===== PROFILE LOGIN =====\n");
                    printf("USER ID : ");
                    printf(BLUE"%s\n"RESET, username);
                    printf("FIRSTNAME : ");
                    printf(BLUE"%s\n"RESET, firstname);
                    printf("LASTNAME : ");
                    printf(BLUE"%s\n"RESET, lastname);
                    printf("ROLE : ");
                    printf(BLUE"%s\n"RESET, role);

                    // ส่วนเนื้อหา
                    printf("\n===== PROGRAM CASHIER =====\n");
                    printf("\nSHOW ALL FOOD AND DRINK MENU [SOFT IN ASCENDING ORDER]\n");
                    
                    // เรียกใช้ฟังก์ชัน
                    sort_menu_items(head_menuitem);
                    cashier_list_show_menuitem(head_menuitem);
                    cashier_list_show_food(head_menuitem);
                    cashier_list_show_drink(head_menuitem);

                    double total_price = 0.0;
                    int total_quantity = 0;
                    char continue_transaction;
                    char selected_menu_names[50][50];
                    int selected_menu_quantity[50];  // เพิ่มอาร์เรย์เก็บ Quantity
                    int selected_menu_count = 0;  // จำนวนเมนูที่ถูกเลือก

                    do {
                        char menu_id[50];
                        int quantity;

                        FILE *csv_file_read_receiption = fopen("./files/receiption.csv", "r");
                    if (csv_file_read_receiption == NULL) {
                        printf("Error opening the CSV file.\n");
                    } else {

                        char line[1024];
                        int hasData = 0; // ใช้เพื่อตรวจสอบว่ามีข้อมูลในไฟล์ CSV หรือไม่
                        
                        while (fgets(line, 1024, csv_file_read_receiption)) {
                            char *token = strtok(line, ",");
                            if (token != NULL) {
                                int current_or_id = atoi(token);  // แปลงค่าเป็นจำนวนเต็ม
                                if (current_or_id >= max_or_id) {
                                    max_or_id = current_or_id + 1;  // เพิ่มค่า MENU ITEM ID ที่มากที่สุด
                                }
                                hasData = 1; // มีข้อมูลในไฟล์ CSV
                            }
                        }

                        if (!hasData) {
                            max_or_id = 1; // ถ้าไม่มีข้อมูลในไฟล์ CSV ให้ max_menu_id เป็น 1
                        }

                        sprintf(or_id, "%d", max_or_id); // แปลงจาก int เป็นสตริง

                        fclose(csv_file_read_receiption);
                    }

                        printf("\nSELECT THE FOOD AND DRINK MENU ABOVE.\n");
                        printf("ENTER THE MENU ID : ");
                        printf(BLUE);
                        scanf("%s", menu_id);
                        printf(RESET);
                        input_validate_quantity:
                        printf("ENTER THE QUANTITY : ");
                        printf(BLUE);
                        scanf("%d", &quantity);
                        printf(RESET);

                        if (quantity < 1) {
                            printf("\nPLEASE ENTER A NUMBER GREATER THAN OR EQUAL TO 1., PLEASE ENTER AGAIN.");
                            // getch();
                            printf("\n");
                            goto input_validate_quantity;
                        }

                        // ค้นหารายการอาหารด้วย menu_id ใน linked list
                        struct MenuItem* current = head_menuitem;
                        while (current != NULL) {
                            if (strcmp(current->menu_id, menu_id) == 0) {
                                double item_price = current->menu_price * quantity;
                                total_price += item_price;
                                total_quantity += quantity;

                                // เพิ่มชื่อเมนูและจำนวน (Quantity) ที่ถูกเลือกในอาร์เรย์
                                strcpy(selected_menu_names[selected_menu_count], current->menu_name);
                                selected_menu_quantity[selected_menu_count] = quantity;
                                selected_menu_count++;

                                break;
                            }
                            current = current->next;
                        }

                        printf("\nCONTINUE THE TRANSACTION OR NOT ?\n");
                        printf("CONTINUE CHOOSING FOOD AND DRINK MENU (Y)\n");
                        printf("SUMMARY OF FOOD AND DRINK ITEM (N)\n");
                        printf("ENTER A KEY (Y/N) : ");
                        printf(BLUE);
                        scanf(" %c", &continue_transaction);
                        printf(RESET);
                        continue_transaction = toupper(continue_transaction);

                    } while (continue_transaction == 'Y');

                    // ทำการคำนวณส่วนลด (ถ้ามี) และราคาสุทธิ
                    double discount = 0.0;
                    if (total_price >= 500) {
                        discount = total_price * 2 / 100;
                    } else {
                        discount = 0.0;
                    }
                    double net_total = total_price - discount;
                    double get_money = 0.0;

                    
                    printf("\n#BILL PAYMENT\n");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| ORDER NUMBER : %-62s |\n", or_id);
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %-36s   %-38s |\n", "PROMOTION :", "");
                    printf("| %-77s |\n", "IF YOU ORDER FOOD OVER 500 BAHT, RECEIVE A 2 PERCEN DISCOUNT.");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %-36s | %-38s |\n", "SELECTED MENU NAMES :", "");
                    int i;
                    for (i = 0; i < selected_menu_count; i++) {
                        printf("| %-1d. %-33s | - QUANTITY : %-25d |\n", i + 1, selected_menu_names[i], selected_menu_quantity[i]);
                    }
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %55s %10.2f %10s |\n", "TOTAL PRICE :", total_price, " BAHT");
                    printf("| %55s %10d %10s |\n", "TOTAL QUANTITY :", total_quantity, " THINGS");
                    printf("| %55s %10.2f %10s |\n", "DISCOUNT :", discount, " BAHT");
                    printf("| %55s %10.2f %10s |\n", "NET TOTAL :", net_total, " BAHT");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("MAKE A TRANSACTION BY : (%s), %s %s\n", username, firstname, lastname);

                    input_validate_get_money:
                    printf("\nRECEIVE MONEY FROM CUSTOMERS\n");
                    printf("GET MONEY : ");
                    printf(BLUE);
                    scanf("%lf", &get_money);
                    printf(RESET);

                    if (get_money < total_price) {
                        printf("\nTHE AMOUNT GET MONEY IS LESS THAN THE TOTAL PRICE., PLEASE ENTER AGAIN. ");
                        // getch();
                        goto input_validate_get_money;
                    }
                    
                    double change = get_money - net_total;

                    printf("\n#RECEIPTION\n");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| ORDER NUMBER : %-62s |\n", or_id);
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %-36s   %-38s |\n", "PROMOTION :", "");
                    printf("| %-77s |\n", "IF YOU ORDER FOOD OVER 500 BAHT, RECEIVE A 2 PERCEN DISCOUNT.");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %-36s | %-38s |\n", "SELECTED MENU NAMES :", "");
                    for (i = 0; i < selected_menu_count; i++) {
                        printf("| %-1d. %-33s | - QUANTITY : %-25d |\n", i + 1, selected_menu_names[i], selected_menu_quantity[i]);
                    }
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %55s %10.2f %10s |\n", "TOTAL PRICE :", total_price, " BAHT");
                    printf("| %55s %10d %10s |\n", "TOTAL QUANTITY :", total_quantity, " THINGS");
                    printf("| %55s %10.2f %10s |\n", "DISCOUNT :", discount, " BAHT");
                    printf("| %55s %10.2f %10s |\n", "NET TOTAL :", net_total, " BAHT");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %55s %10.2f %10s |\n", "GET MONEY :", get_money, " BAHT");
                    printf("| %55s %10.2f %10s |\n", "CHANGE :", change, " BAHT");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("MAKE A TRANSACTION BY : (%s), %s %s\n", username, firstname, lastname);
                    
                    cashier_insert_receiption(&head_receiption, or_id, total_price, total_quantity, discount, net_total, get_money, change, username, firstname, lastname);
                    cashier_receiption_savetofile(head_receiption, or_id, total_price, total_quantity, discount, net_total, get_money, change, username, firstname, lastname);

                    printf("\nSUCCESSFULLY TRANSACTION, PRESS THE ENTER KEY ... ");
                    getch();
                    goto ch_case_menu;
                    break;
                
                default:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    printf("\nSELECTED MENU INVALID, PRESS THE ENTER KEY ... ");
                    getch();
                    goto ch_case_menu;
                    break;
                }

            } else {
                printf("================================================\n");
                printf("============ RES. MENAGEMENT SYSTEM ============\n");
                printf("================================================\n");
                printf("\nACCESS DENIED.\nWRONG USERNAME OR PASSWORD.\nPRESS THE ENTER KEY ... ");
                getch();
                ch_logout = 'Y';
            }
        } else {
            printf("================================================\n");
            printf("============ RES. MENAGEMENT SYSTEM ============\n");
            printf("================================================\n");
            printf("\nACCESS DENIED.\nTHERE IS NO RIGHT TO ACCES THIS SYSTEM.\nPRESS THE ENTER KEY ... ");
            getch();
            ch_logout = 'Y';
        }
        load_file_person(&head_person);
        load_file_menuitem(&head_menuitem);

    }

    system("cls");
    printf("================================================\n");
    printf("============ RES. MENAGEMENT SYSTEM ============\n");
    printf("================================================\n");
    printf("\nSUCCESSFULLY EXITED THE PROGRAM, PRESS THE ENTER KEY ...\n");
    
    free_person(head_person);
    free_menuitem(head_menuitem);
    free_receiption(head_receiption);

    return 0;
}

// Function
// โหลดใฟล์ to linked list
void load_file_person(struct Person** head_person) {
    FILE* file = fopen("./files/person.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    } 
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // printf("line = %s\n",line);
        char username[50], password[50], firstname[50], lastname[50], role[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%s\n", username, password, firstname, lastname, role);
        struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));
        strcpy(newPerson->username, username);
        strcpy(newPerson->password, password);
        strcpy(newPerson->firstname, firstname);
        strcpy(newPerson->lastname, lastname);
        strcpy(newPerson->role, role);
        newPerson->next = *head_person;
        *head_person = newPerson;
    }

    fclose(file);
    printf("Data loaded PERSON from 'load_file_person' CSV file successfully.\n");

}
void load_file_menuitem(struct MenuItem** head_menuitem) {
    FILE* file = fopen("./files/menuitem.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    } 

    printf("Loading data from 'load_file_menuitem' CSV file...\n");

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // printf("line = %s\n",line);
        struct MenuItem* newMenuItem = (struct MenuItem*)malloc(sizeof(struct MenuItem));
        if (newMenuItem == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return;
        }

        sscanf(line, "%[^,], %[^,], %lf, %s", newMenuItem->menu_id, newMenuItem->menu_name, &newMenuItem->menu_price, newMenuItem->menu_cat);
        newMenuItem->next = *head_menuitem;
        *head_menuitem = newMenuItem;
    }

    fclose(file);
    printf("Data loaded MENUITEM successfully from CSV file.\n");
}
void load_file_receiption(struct Receiption** head_receiption) {
    FILE* file = fopen("./files/receiption.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    } 

    printf("Loading data from 'load_file_receiption' CSV file...\n");

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        struct Receiption* newReceiption = (struct Receiption*)malloc(sizeof(struct Receiption));
        if (newReceiption == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return;
        }

        sscanf(line, "%[^,], %lf, %d, %lf, %lf, %lf, %lf, %[^,], %[^,], %s", 
            newReceiption->or_id, 
            &newReceiption->or_total_price, 
            &newReceiption->or_total_quantity, 
            &newReceiption->or_discount, 
            &newReceiption->or_net_total, 
            &newReceiption->or_get_money, 
            &newReceiption->or_change, 
            newReceiption->username, 
            newReceiption->firstname, 
            newReceiption->lastname
        );

        newReceiption->next = *head_receiption;
        *head_receiption = newReceiption;
    }

    fclose(file);
    printf("Data loaded RECEIPTION successfully from CSV file.\n");
}
void free_person(struct Person* head_person) {
    struct Person* current = head_person;
    while (current != NULL) {
        struct Person* next = current->next;
        free(current);
        current = next;
    }
}
void free_menuitem(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;
    while (current != NULL) {
        struct MenuItem* next = current->next;
        free(current);
        current = next;
    }
}
void free_receiption(struct Receiption* head_receiption) {
    struct Receiption* current = head_receiption;
    while (current != NULL) {
        struct Receiption* next = current->next;
        free(current);
        current = next;
    }
}
// sorting เรียงลำดับข้อมูล
int compare_menu_id(const void* a, const void* b) {
    const struct MenuItem* item1 = (const struct MenuItem*)a;
    const struct MenuItem* item2 = (const struct MenuItem*)b;

    // เปรียบเทียบ menu_id
    if (item1->menu_id < item2->menu_id) {
        return -1;
    } else if (item1->menu_id > item2->menu_id) {
        return 1;
    } else {
        return 0;
    }
}
void sort_menu_items(struct MenuItem* head_menuitem) {
    // นับจำนวนรายการในลิสต์
    int count = 0,i;
    struct MenuItem* current = head_menuitem;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // สร้างอาร์เรย์ของ MenuItem
    struct MenuItem* menu_items_array = (struct MenuItem*)malloc(count * sizeof(struct MenuItem));
    current = head_menuitem;
    for (i = 0; i < count; i++) {
        menu_items_array[i] = *current;
        current = current->next;
    }

    // เรียงลำดับอาร์เรย์ของ MenuItem
    qsort(menu_items_array, count, sizeof(struct MenuItem), compare_menu_id);

    // อัปเดตลิสต์หลักโดยใช้อาร์เรย์ที่ถูกเรียง
    current = head_menuitem;
    for (i = 0; i < count; i++) {
        *current = menu_items_array[i];
        current = current->next;
    }

    free(menu_items_array);
}
// login
int login(const char* inputUsername, const char* inputPassword, const struct Person* head_person) {
    const struct Person* current = head_person;
    while (current != NULL) {
        if (strcmp(current->username, inputUsername) == 0 && strcmp(current->password, inputPassword) == 0) {
            return 1; // Login successful
        }
        current = current->next;
    }
    return 0; // Login failed
}
// admin case 1
void admin_register_admin(struct Person** head_person, char username[], char password[], char firstname[], char lastname[]) {
    struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));
    strcpy(newPerson->username, username);
    strcpy(newPerson->password, password);
    strcpy(newPerson->firstname, firstname);
    strcpy(newPerson->lastname, lastname);
    strcpy(newPerson->role, "ADMINISTRATOR");
    newPerson->next = *head_person;
    *head_person = newPerson;
}
void admin_person_savetofile(struct Person* head_person, char username[], char password[], char firstname[], char lastname[]) {
    FILE* file = fopen("./files/person.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", username, password, firstname, lastname, "ADMINISTRATOR");

    fclose(file);
    printf("DATA SAVED TO CSV fILE SUCCESSFULLY.\n");
}
// admin case 2
void admin_register_cashier(struct Person** head_person, char username[], char password[], char firstname[], char lastname[]) {
    struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));
    strcpy(newPerson->username, username);
    strcpy(newPerson->password, password);
    strcpy(newPerson->firstname, firstname);
    strcpy(newPerson->lastname, lastname);
    strcpy(newPerson->role, "CASHIER");
    newPerson->next = *head_person;
    *head_person = newPerson;
}
void admin_cashier_savetofile(struct Person* head_person, char username[], char password[], char firstname[], char lastname[]) {
    FILE* file = fopen("./files/person.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", username, password, firstname, lastname, "CASHIER");

    fclose(file);
    printf("DATA SAVED TO CSV fILE SUCCESSFULLY.\n");
}
// admin case 3
void admin_update_person(struct Person* head_person, char username[]) {
    struct Person* current = head_person;

    // ค้นหาผู้ใช้ที่ต้องการอัปเดต
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            printf("\n===== USER DETAILS =====\n");
            printf("USERNAME : ");
            printf(BLUE);
            printf("%s\n", current->username);
            printf(RESET);
            printf("FIRSTNAME : ");
            printf(BLUE);
            printf("%s\n", current->firstname);
            printf(RESET);
            printf("LASTNAME : ");
            printf(BLUE);
            printf("%s\n", current->lastname);
            printf(RESET);
            printf("ROLE : ");
            printf(BLUE);
            printf("%s\n", current->role);
            printf(RESET);

            // เลือกและแสดงตัวเลือกในการแก้ไข
            printf("\n===== UPDATE USER =====\n");
            printf("1. UPDATE FIRSTNAME\n");
            printf("2. UPDATE LASTNAME\n");
            printf("3. UPDATE ROLE [ADMINISTRATOR / CASHIER]\n");
            printf("SELECT MENU [1-3] : ");

            int option,i;
            printf(BLUE);
            scanf("%d", &option);
            printf(RESET);

            switch (option) {
                case 1:
                    printf("\nENTER NEW FIRSTNAME: ");
                    printf(BLUE);
                    scanf("%s", current->firstname);
                    for (i = 0; current->firstname[i]; i++) {
                        current->firstname[i] = toupper(current->firstname[i]);
                    }
                    printf(RESET);
                    break;
                case 2:
                    printf("\nENTER NEW LASTNAME: ");
                    printf(BLUE);
                    scanf("%s", current->lastname);
                    for (i = 0; current->lastname[i]; i++) {
                        current->lastname[i] = toupper(current->lastname[i]);
                    }
                    printf(RESET);
                    break;
                case 3:
                    printf("\nENTER NEW ROLE: ");
                    printf(BLUE);
                    scanf("%s", current->role);
                    for (i = 0; current->role[i]; i++) {
                        current->role[i] = toupper(current->role[i]);
                    }
                    printf(RESET);
                    break;
                default:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    printf("\nSELECTED MENU INVALID, PRESS THE ENTER KEY ... ");
                    getch();
                    break;
            }

            printf("\nUSER UPDATED SUCCESSFULLY.\n");

            // อัปเดตไฟล์ CSV
            FILE* file = fopen("./files/person.csv", "w");
            if (file == NULL) {
                perror("Error opening file");
                return;
            }

            struct Person* writeCurrent = head_person;
            while (writeCurrent != NULL) {
                fprintf(file, "%s,%s,%s,%s,%s\n", writeCurrent->username, writeCurrent->password, writeCurrent->firstname, writeCurrent->lastname, writeCurrent->role);
                writeCurrent = writeCurrent->next;
            }

            fclose(file);
            printf("CSV FILE UPDATED SUCCESSFULLY.\n");

            return;
        }
        current = current->next;
    }
    printf("\nUSER WITH USERNAME %s NOT FOUND.\n", username);
}
// admin case 4
void admin_delete_person(struct Person** head_person, char username[]) {
    struct Person* current = *head_person;
    struct Person* prev = NULL;

    FILE* file = fopen("./files/person.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE* tempFile = fopen("./files/person_temp.csv", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            if (prev == NULL) {
                *head_person = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("DELETED PERSON WITH USERNAME %s SUCCESSFULLY.\n", username);
        } else {
            fprintf(tempFile, "%s,%s,%s,%s,%s\n", current->username, current->password, current->firstname, current->lastname, current->role);
        }
        prev = current;
        current = current->next;
    }

    fclose(file);
    fclose(tempFile);

    if (remove("./files/person.csv") != 0) {
        perror("Error deleting original file");
    }

    if (rename("./files/person_temp.csv", "./files/person.csv") != 0) {
        perror("Error renaming temporary file");
    }
}
// admin case 5
void admin_insert_food(struct MenuItem** head_menuitem, char menu_id[], char menu_name[], double menu_price) {
    struct MenuItem* newMenuFood = (struct MenuItem*)malloc(sizeof(struct MenuItem));
    strcpy(newMenuFood->menu_id, menu_id);
    strcpy(newMenuFood->menu_name, menu_name);
    newMenuFood->menu_price = menu_price;
    strcpy(newMenuFood->menu_cat, "FOOD");
    newMenuFood->next = *head_menuitem;
    *head_menuitem = newMenuFood;
}
void admin_food_savetofile(struct MenuItem* head_menuitem, char menu_id[], char menu_name[], double menu_price) {
    FILE* file = fopen("./files/menuitem.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%s,%lf,%s\n", menu_id, menu_name, menu_price, "FOOD");

    fclose(file);
    printf("DATA FOOD SAVED TO CSV FILE SUCCESSFULLY.\n");
}
// admin case 6
void admin_insert_drink(struct MenuItem** head_menuitem, char menu_id[], char menu_name[], double menu_price) {
    struct MenuItem* newMenuFood = (struct MenuItem*)malloc(sizeof(struct MenuItem));
    strcpy(newMenuFood->menu_id, menu_id);
    strcpy(newMenuFood->menu_name, menu_name);
    newMenuFood->menu_price = menu_price;
    strcpy(newMenuFood->menu_cat, "DRINK");
    newMenuFood->next = *head_menuitem;
    *head_menuitem = newMenuFood;
}
void admin_drink_savetofile(struct MenuItem* head_menuitem, char menu_id[], char menu_name[], double menu_price) {
    FILE* file = fopen("./files/menuitem.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%s,%lf,%s\n", menu_id, menu_name, menu_price, "DRINK");

    fclose(file);
    printf("DATA DRINK SAVED TO CSV FILE SUCCESSFULLY.\n");
}
// admin case 7
void admin_update_menuitem(struct MenuItem* head_menuitem, char menu_id[]) {
    struct MenuItem* current = head_menuitem;

    while (current != NULL) {
        if (strcmp(current->menu_id, menu_id) == 0) {
            printf("\n===== MENU DETAILS =====\n");
            printf("MENU ID : ");
            printf(BLUE);
            printf("%s\n", current->menu_id);
            printf(RESET);
            printf("MENU NAME : ");
            printf(BLUE);
            printf("%s\n", current->menu_name);
            printf(RESET);
            printf("MENU PRICE : ");
            printf(BLUE);
            printf("%.2f\n", current->menu_price);
            printf(RESET);

            printf("\n===== UPDATE FOOD AND DRINK MENU =====\n");
            printf("1. UPDATE NAME\n");
            printf("2. UPDATE PRICE\n");
            printf("SELECT MENU [1-3] : ");

            int option,i;
            printf(BLUE);
            scanf("%d", &option);
            printf(RESET);

            switch (option) {
                case 1:
                    printf("\nENTER NEW MENU NAME: ");
                    printf(BLUE);
                    scanf("%s", current->menu_name);
                    for (i = 0; current->menu_name[i]; i++) {
                        current->menu_name[i] = toupper(current->menu_name[i]);
                    }
                    printf(RESET);
                    break;
                case 2:
                    printf("\nENTER NEW MENU PRICE: ");
                    printf(BLUE);
                    scanf("%lf", current->menu_price);
                    printf(RESET);
                    break;
                default:
                    system("cls");
                    printf("================================================\n");
                    printf("============ RES. MENAGEMENT SYSTEM ============\n");
                    printf("================================================\n");
                    printf("\nSELECTED MENU INVALID, PRESS THE ENTER KEY ... ");
                    getch();
                    break;
            }

            printf("\nMENU UPDATED SUCCESSFULLY.\n");

            // อัปเดตไฟล์ CSV
            FILE* file = fopen("./files/menuitem.csv", "w");
            if (file == NULL) {
                perror("Error opening file");
                return;
            }

            struct MenuItem* writeCurrent = head_menuitem;
            while (writeCurrent != NULL) {
                fprintf(file, "%s,%s,%lf,%s\n", writeCurrent->menu_id, writeCurrent->menu_name, writeCurrent->menu_price, writeCurrent->menu_cat);
                writeCurrent = writeCurrent->next;
            }

            fclose(file);
            printf("CSV FILE UPDATED SUCCESSFULLY.\n");

            return;
        }
        current = current->next;
    }
    printf("\nMENU WITH MENUITEM %s NOT FOUND.\n", menu_id);
}
// admin case 8
void admin_delete_menuitem(struct MenuItem** head_menuitem, char menu_id[]) {
    struct MenuItem* current = *head_menuitem;
    struct MenuItem* prev = NULL;

    FILE* file = fopen("./files/menuitem.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE* tempFile = fopen("./files/menuitem_temp.csv", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (current != NULL) {
        if (strcmp(current->menu_id, menu_id) == 0) {
            if (prev == NULL) {
                *head_menuitem = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("DELETED MENU WITH MENUITEM %s SUCCESSFULLY.\n", menu_id);
        } else {
            fprintf(tempFile, "%s,%s,%lf,%s\n", current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        }
        prev = current;
        current = current->next;
    }

    fclose(file);
    fclose(tempFile);

    if (remove("./files/menuitem.csv") != 0) {
        perror("Error deleting original file");
    }

    if (rename("./files/menuitem_temp.csv", "./files/menuitem.csv") != 0) {
        perror("Error renaming temporary file");
    }
}
// admin case 9.1
void admin_list_show_admin(struct Person* head_person) {
    struct Person* current = head_person;

    if (current == NULL) {
        printf("No person data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-15s | %-15s | %-20s |\n", "NO.", "USER ID", "FIRSTNAME", "LASTNAME", "ROLE");
    printf("---------------------------------------------------------------------------------\n");
    int order_admin = 1;
    while (current != NULL) {
        if (strcmp(current->role, "ADMINISTRATOR") == 0) {
            printf("| %-5d | %-10s | %-15s | %-15s | %-20s |\n", order_admin++, current->username, current->firstname, current->lastname, current->role);
        }
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
// admin case 9.2
void admin_list_show_cashier(struct Person* head_person) {
    struct Person* current = head_person;

    if (current == NULL) {
        printf("No person data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-15s | %-15s | %-20s |\n", "NO.", "USER ID", "FIRSTNAME", "LASTNAME", "ROLE");
    printf("---------------------------------------------------------------------------------\n");
    int order_cashier = 1;
    while (current != NULL) {
        if (strcmp(current->role, "CASHIER") == 0) {
            printf("| %-5d | %-10s | %-15s | %-15s | %-20s |\n", order_cashier++, current->username, current->firstname, current->lastname, current->role);
        }
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
// admin case 9.3
void admin_list_show_person(struct Person* head_person) {
    struct Person* current = head_person;

    if (current == NULL) {
        printf("No person data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-15s | %-15s | %-20s |\n", "NO.", "USER ID", "FIRSTNAME", "LASTNAME", "ROLE");
    printf("---------------------------------------------------------------------------------\n");
    int order_person = 1;
    while (current != NULL) {
        printf("| %-5d | %-10s | %-15s | %-15s | %-20s |\n", order_person++, current->username, current->firstname, current->lastname, current->role);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
// admin case 10.1
void admin_list_show_food(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;

    if (current == NULL) {
        printf("No menu item data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-30s | %-10s | %-10s |\n", "NO.", "MENU ID", "MENU NAME", "MENU PRICE", "MENU CAT");
    printf("---------------------------------------------------------------------------------\n");
    int order_food = 1;
    while (current != NULL) {
        if (strcmp(current->menu_cat, "FOOD") == 0) {
            printf("| %-5d | %-10s | %-30s | %-10.2f | %-10s |\n", order_food++, current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        }
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
// admin case 10.2
void admin_list_show_drink(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;

    if (current == NULL) {
        printf("No menu item data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-30s | %-10s | %-10s |\n", "NO.", "MENU ID", "MENU NAME", "MENU PRICE", "MENU CAT");
    printf("---------------------------------------------------------------------------------\n");
    int order_drink = 1;
    while (current != NULL) {
        if (strcmp(current->menu_cat, "DRINK") == 0) {
            printf("| %-5d | %-10s | %-30s | %-10.2f | %-10s |\n", order_drink++, current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        }
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
// admin case 10.3
void admin_list_show_menuitem(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;

    if (current == NULL) {
        printf("No menu item data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-30s | %-10s | %-10s |\n", "NO.", "MENU ID", "MENU NAME", "MENU PRICE", "MENU CAT");
    printf("---------------------------------------------------------------------------------\n");
    int order_menuitem = 1;
    while (current != NULL) {
        printf("| %-5d | %-10s | %-30s | %-10.2f | %-10s |\n", order_menuitem++, current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
// admin case 11
void admin_list_show_receiption_table_1(struct Receiption* head_receiption) {
    struct Receiption* current = head_receiption;

    if (current == NULL) {
        printf("No receiption report data in the system.\n");
        return;
    }

    printf("\n#REPORT TABLE 1\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-12s | %-12s | %-12s | %-12s | %-12s |\n", "NO.", "ORDER ID", "TOTAL PRICE", "TOTAL QUA.", "DISCOUNT", "NET TOTAL");
    printf("------------------------------------------------------------------------------------\n");
    int order_receiption = 1;
    while (current != NULL) {
    printf("| %-5d | %-12s | %-12.2f | %-12d | %-12.2f | %-12.2f |\n", order_receiption++, current->or_id, current->or_total_price, current->or_total_quantity, current->or_discount, current->or_net_total);
        current = current->next;
    }
    printf("------------------------------------------------------------------------------------\n");
}
void admin_list_show_receiption_table_2(struct Receiption* head_receiption) {
    struct Receiption* current = head_receiption;

    if (current == NULL) {
        printf("No receiption report data in the system.\n");
        return;
    }

    printf("\n#REPORT TABLE 2\n");
    printf("---------------------------------------------------------------------\n");
    printf("| %-5s | %-12s | %-12s | %-12s | %-12s |\n", "NO.", "ORDER ID", "CASHIER ID", "FIRSTNAME", "LASTNAME");
    printf("---------------------------------------------------------------------\n");
    int order_receiption = 1;
    while (current != NULL) {
    printf("| %-5d | %-12s | %-12s | %-12s | %-12s |\n", order_receiption++, current->or_id, current->username, current->firstname, current->lastname);
        current = current->next;
    }
    printf("---------------------------------------------------------------------\n");
}
void admin_list_show_receiption_table_3(struct Receiption* head_receiption) {
    struct Receiption* current = head_receiption;

    if (current == NULL) {
        printf("No receiption report data in the system.\n");
        return;
    }

    printf("\n#REPORT TABLE 3\n");
    printf("------------------------------------------------------\n");
    printf("| %-5s | %-12s | %-12s | %-12s |\n", "NO.", "ORDER ID", "GET MONEY", "CHANGE");
    printf("------------------------------------------------------\n");
    int order_receiption = 1;
    while (current != NULL) {
    printf("| %-5d | %-12s | %-12.2f | %-12.2f |\n", order_receiption++, current->or_id, current->or_get_money, current->or_change);
        current = current->next;
    }
    printf("------------------------------------------------------\n");
}
// cashier case 1
void cashier_list_show_food(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;

    if (current == NULL) {
        printf("No menu item data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-30s | %-10s | %-10s |\n", "NO.", "MENU ID", "MENU NAME", "MENU PRICE", "MENU CAT");
    printf("---------------------------------------------------------------------------------\n");
    int order_food = 1;
    while (current != NULL) {
        if (strcmp(current->menu_cat, "FOOD") == 0) {
            printf("| %-5d | %-10s | %-30s | %-10.2f | %-10s |\n", order_food++, current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        }
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
void cashier_list_show_drink(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;

    if (current == NULL) {
        printf("No menu item data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-30s | %-10s | %-10s |\n", "NO.", "MENU ID", "MENU NAME", "MENU PRICE", "MENU CAT");
    printf("---------------------------------------------------------------------------------\n");
    int order_drink = 1;
    while (current != NULL) {
        if (strcmp(current->menu_cat, "DRINK") == 0) {
            printf("| %-5d | %-10s | %-30s | %-10.2f | %-10s |\n", order_drink++, current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        }
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
void cashier_list_show_menuitem(struct MenuItem* head_menuitem) {
    struct MenuItem* current = head_menuitem;

    if (current == NULL) {
        printf("No menu item data in the system.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-30s | %-10s | %-10s |\n", "NO.", "MENU ID", "MENU NAME", "MENU PRICE", "MENU CAT");
    printf("---------------------------------------------------------------------------------\n");
    int order_menuitem = 1;
    while (current != NULL) {
        printf("| %-5d | %-10s | %-30s | %-10.2f | %-10s |\n", order_menuitem++, current->menu_id, current->menu_name, current->menu_price, current->menu_cat);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}
void cashier_insert_receiption(struct Receiption** head_receiption, char or_id[], double total_price, int total_quantity, double discount, double net_total, double get_money, double change, char username[], char firstname[], char lastname[]) {
    struct Receiption* newReceiption = (struct Receiption*)malloc(sizeof(struct Receiption));
    strcpy(newReceiption->or_id, or_id);
    newReceiption->or_total_price = total_price;
    newReceiption->or_total_quantity = total_quantity;
    newReceiption->or_discount = discount;
    newReceiption->or_net_total = net_total;
    newReceiption->or_get_money = get_money;
    newReceiption->or_change = change;
    strcpy(newReceiption->username, username);
    strcpy(newReceiption->firstname, firstname);
    strcpy(newReceiption->lastname, lastname);
    newReceiption->next = *head_receiption;
    *head_receiption = newReceiption;
}
void cashier_receiption_savetofile(struct Receiption* head_receiption, char or_id[], double total_price, int total_quantity, double discount, double net_total, double get_money, double change, char username[], char firstname[], char lastname[]) {
    FILE* file = fopen("./files/receiption.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%lf,%d,%lf,%lf,%lf,%lf,%s,%s,%s\n", or_id, total_price, total_quantity, discount, net_total, get_money, change, username, firstname, lastname);

    fclose(file);
    printf("DATA RECEIPTION SAVED TO CSV FILE SUCCESSFULLY.\n");
}




