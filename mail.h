#include <stdio.h>

typedef struct mail {
    char name[40];
    char street[40];
    long int id; // id обязательно число > 0
} mail;

mail* rff(const char* filename, int* count);
void display(mail* mails, int count);
void wtff(const char* filename, mail* mails, int count);
mail add();
void search(mail* mails, int count);
void edit(mail* mails, int count);
void delete(mail** mails, int* count);

