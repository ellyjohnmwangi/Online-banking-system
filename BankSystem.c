#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user {
    char phone[50];
    char ac[50];    
    char password[50];
    float balance;
};

int main(){
    struct user usr,usr1;
    FILE *fp;
    char filename[100],phone[50],pword[50];
    int opt,choice;
    char cont = 'y';
    float amount;

    printf("\nWhat do you want to do?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);

    if(opt == 1){
        system("clear");
        printf("Enter your account number:\t");
        scanf("%s",usr.ac);
        printf("Enter your phone number:\t");
        scanf("%s",usr.phone);
        printf("Enter your new password:\t");
        scanf("%s",usr.password);
        usr.balance = 0;
        strcpy(filename,"accounts/");
        strcat(filename,usr.phone);
        fp = fopen(strcat(filename,".dat"),"wb");
        if(fp == NULL){
            printf("\n\nSomething went wrong please try again");
            exit(1);
        }
        fwrite(&usr,sizeof(struct user),1,fp);
        printf("\n\nAccount successfully registered");
        fclose(fp);
    }
    else if(opt == 2){
        system("clear");
        printf("\nPhone number:\t");
        scanf("%s",phone);
        printf("Password:\t");
        scanf("%s",pword);
        strcpy(filename,"accounts/");
        strcat(filename,phone);
        fp = fopen(strcat(filename,".dat"),"rb+");
        if(fp == NULL){
            printf("\nAccount number not registered");
            exit(1);
        }
        fread(&usr,sizeof(struct user),1,fp);
        if(strcmp(pword,usr.password) == 0){
            printf("\n\t\tWelcome %s",usr.phone);;
            while(cont == 'y'){
                system("clear");
                printf("\n\nPress 1 for balance inquiry");
                printf("\nPress 2 for depositing cash");
                printf("\nPress 3 for cash withdrawal");
                printf("\nPress 4 for online transfer");
                printf("\nPress 5 for password change");
                printf("\n\nYour choice:\t");
                scanf("%d",&choice);

                switch(choice){
                    case 1:
                        printf("\nYour current balance is Rs.%.2f",usr.balance);
                        break;
                    case 2:
                        printf("\nEnter the amount:\t");
                        scanf("%f",&amount);
                        usr.balance += amount;
                        fseek(fp,-sizeof(struct user),SEEK_CUR);
                        fwrite(&usr,sizeof(struct user),1,fp);
                        printf("\nSuccessfully deposited.");
                        break;
                    case 3:
                        printf("\nEnter the amount:\t");
                        scanf("%f",&amount);
                        if(amount > usr.balance){
                            printf("\nInsufficient balance");
                            break;
                        }
                        usr.balance -= amount;
                        fseek(fp,-sizeof(struct user),SEEK_CUR);
                        fwrite(&usr,sizeof(struct user),1,fp);
                        printf("\nYou have withdrawn Rs.%.2f",amount);
                        break;

                    case 4:
                        printf("\nPlease enter the phone number to transfer the balance:\t");
                        scanf("%s",phone);
                        printf("\nPlease enter the amount to transfer:\t");
                        scanf("%f",&amount);
                        strcpy(filename,"accounts/");
                        strcat(filename,phone);
                        fp = fopen(strcat(filename,".dat"),"w");
                        usr.balance -= amount;
                        fwrite(&usr,sizeof(struct user),1,fp);
                        fclose(fp);

                        break;
                    case 5:
                         printf("\nPlease enter your new password:\t");
                        scanf("%s",pword);
                        fp = fopen(filename,"w");
                        strcpy(usr.password,pword);
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL){
                        printf("\nPassword succesfully changed");
                        }
                    break;
                default:
                    printf("\nInvalid option");
                }
                printf("\nDo you want to continue the transaction [y/n]\t");
                scanf("%s",&cont);
            }   
        }
        else {
            printf("\nInvalid password");
        }
    }
    return 0;
}
