#include "mail.h"
#include <stdlib.h>

int main() {
    int count = 0;
    const char* filename = "mail.txt";
    mail* mails = rff(filename, &count);
    int x;
    do {
        printf("\nMenu:\n 1) display\n 2) add new\n 3) search\n 4) edit\n 5) delete\n 6) exit\n");
        printf("enter: ");
        if (scanf("%i", &x) != 1) {
            printf("Error\n");
            return 0;
        }
        switch (x) {
            case 1:
                display(mails, count);
                break;
            case 2:
                mails = realloc(mails, (count + 1) * sizeof(mail));
                if (mails == NULL) {
                    printf("Error\n");
                    return 1;
                }
                mails[count++] = add();
                wtff(filename, mails, count);
                break;
            case 3:
                search(mails, count);
                break;
            case 4:
                edit(mails, count);
                wtff(filename, mails, count);
                break;
            case 5:
                delete(&mails, &count);
                wtff(filename, mails, count);
                break;
            case 6:
                wtff(filename, mails, count);
                break;
            default:
                printf("Error\n");
                break;
        }
    } while (x != 6);
    free(mails);
    return 0;
}

