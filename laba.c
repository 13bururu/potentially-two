#include <string.h>
#include <stdlib.h>
#include <stdio.h>
///в баз данных почты будет храниться:
///1) имя 
///2) место проживания(улица)
///3) его id на почте
typedef struct mail{
char name[40];
char street[40];
long int id;////id обязательно число>0
}mail;


mail* rff(const char* filename, int* count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error\n");
        return NULL;
    }
    int rcount = 0;
    mail temp;
    while (fscanf(f, "%s %s %ld", temp.name, temp.street, &temp.id) == 3) {
        rcount++;
    }
    fseek(f, 0, SEEK_SET);
    mail* mails = (mail*)calloc(rcount, sizeof(mail));
    if (mails == NULL) {
        printf("Error\n");
        fclose(f);
        return NULL;
    }
    int i = 0;
    while (fscanf(f, "%s %s %ld", mails[i].name, mails[i].street, &mails[i].id) == 3) {
        i++;
    }
    fclose(f);
    *count = rcount; 
    return mails;
}


    void display(mail* mails,int count){
        if(count !=0){ 
            for(int i=0;i<count;i++){
                printf("%i) name:%s street:%s id:%ld\n",(i+1),mails[i].name,mails[i].street,mails[i].id);
            }

        }else
        {
        printf("pustaya baza dannih\n");
        return;
        }
    }




void wtff(const char* filename,mail* mails,int count){
    FILE *f=fopen(filename,"w");
    if(!f){printf("Error\n");return;}
     for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %ld\n", mails[i].name, mails[i].street, mails[i].id);
    }
    fclose(f);
}

mail add(){
    mail newmail;
    printf("name:\n");
    scanf("%s",newmail.name);
    printf("street:\n");
    scanf("%s",newmail.street);
    printf("if:\n");
    if (scanf("%ld", &newmail.id) != 1 || newmail.id <= 0) {
        printf("Error\n");
         newmail.id = rand();////// если введеное id письма не удовлетворяет условию то прислваивается случайный
    }
    return newmail;
}


void search(mail* mails,int count){////(поиск человека который отправил письмо для этого допустим надо знать где он живет и id его письма)
    char street[40];
    int id;
    printf("gde zhivet?\n ");
    scanf("%s",street);
    printf("id?\n ");
    scanf("%ld",&id);
    ////// если нашлось то выдаст всю инфу о человеке
    for (int i=0;i<count;i++){
        if((strcmp(mails[i].street,street)==0) && mails[i].id==id){
            printf("name:%s street:%s id:%ld\n",mails[i].name, mails[i].street, mails[i].id);
            
        }
        
    }
    
}



void edit(mail* mails,int count){
printf("number of the person you want to edit: ");
int e;
if(scanf("%i",&e)!=1){printf("error");return;
}
if (e < 1 || e > count) {
       printf("Error\n");
       return;
   }
printf("new name: ");
scanf("%s", mails[e-1].name);
printf("new street: ");
scanf("%s", mails[e-1].street);
printf("new id: ");
if(scanf("%ld", &mails[e-1].id)!=1){printf("Error");}
}

void delete(mail** mails,int* count){
    printf("number of the person you want to delete: ");
    int t;
    if(scanf("%i",&t)!=1){printf("error");return;
}
if (t < 1 || t > *count) {
       printf("Error\n");
       return;
   }
for(int i=t-1; i < *count-1; i++){
       (*mails)[i] = (*mails)[i+1];
   }
*count-=1;
*mails = realloc(*mails, (*count) * sizeof(mail));
if (!mails) {
       printf("Error\n");
       return;
   }
    return;
}


int main(){

    int count=0;
    const char* filename = "mail.txt";
    mail* mails=rff(filename, &count);
    int x;
    do{
    printf("\nMenu:\n 1)display\n 2)add new\n 3)search\n 4)edit\n 5)delete\n 6)exit\n");
    printf("enter: ");
    if(scanf("%i",&x)!=1){printf("Error");return 0;}
    switch(x){
        case 1:
        display(mails,count);
        break;
        case 2:
        mails=realloc(mails,(count+1)*sizeof(mail));
         if (mails == NULL) {printf("Error\n");return 1;}
        mails[count++]=add();
        wtff(filename,mails,count);
        break;
        case 3:
        search(mails,count);
        break;
        case 4:
        edit(mails,count);
        wtff(filename,mails,count);
        break;
        case 5:
        delete(&mails,&count);
        wtff(filename,mails,count);
        break;
        case 6:
         wtff(filename,mails,count);
        break;
        default:
        printf("Error\n");
        break;
    }
    }while(x!=6);
free(mails);

   
return 0;
}

 