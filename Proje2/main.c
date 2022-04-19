/*
    @proje2
    @iki adet büyük sayı arasında işlem yapma
    @21.01.2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FileOperations.h"

int main(){

    FILE *file1,*file2,*sonuc;
    
    int control = 0;
    while(control == 0){
        printf("\n(1)Write numbers on screen\n");
        printf("(2)Mathematical operation(+,-)\n");
        printf("(3)Write result on screen\n");
        printf("(4)Exit\n");
        printf("Please select a number:");
        int select;
        scanf("%d",&select);
        if(select == 1){
            printf("\nNumber1\n");
            readFromFile(&file1,"sayi1.txt");
            printf("\n\nNumber2\n");
            readFromFile(&file2,"sayi2.txt");
        }else if(select == 2){
            char operation;
            printf("Please select '+' or '-':");
            scanf(" %c",&operation);
            while(operation != '+' && operation != '-'){
                printf("Just enter '+' or '-':");
                scanf(" %c",&operation);
            }
            file1 = fopen("sayi1.txt","r");
            if(file1 == NULL){
                printf("File could not found");
                exit(1);
            }
            file2 = fopen("sayi2.txt","r");
            if(file2 == NULL){
                printf("File could not found");
                exit(1);
            }
            if(operation == '+'){
                addition(file1,file2);
                printf("\nMath operation done successfully\n");
            }else{
                subtraction(file1,file2);
                printf("\nMath operation done successfully\n");
            }
        }else if(select == 3){
            printf("\nResult\n");
            readFromFile(&sonuc,"sonuclar.txt");
        }else if(select == 4){
            printf("Have a good day :)");
            control = 1;
        }else{
            printf("\nJust enter numbers between 1-5\n");
        }
    }
    return 0;
}