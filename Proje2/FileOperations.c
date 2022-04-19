/*
    @proje2
    @iki adet büyük sayı arasında işlem yapma
    @21.01.2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FileOperations.h"

FILE *sonuc;

//Creating an array in memory
uint8_t *makeArray(int size){

    return (uint8_t*)malloc(size*sizeof(uint8_t));
}

int findFileSize(FILE *name){

    rewind(name);
    int count = 0,indent =0;
    while(!feof(name)){
        //check if there is a carriage return
        if(fgetc(name) == '\n') indent++;
        count++;
    }
    return count-indent-1;
}

uint8_t *numberToArray(FILE *name){

    int size = findFileSize(name);
    //beginning of the file
    rewind(name);
    uint8_t *array = makeArray(size);
    int i=0;
    while((i<size) && !(feof(name))){
        char ch = getc(name);
        //If the character taken from the file is not carriage return, add it to array
        if(ch != '\n'){
            *(array+i) = ch - '0';
            i++;
        }
    }
    return array;
}

void addition(FILE *num1, FILE *num2){

    uint8_t *number1 = numberToArray(num1);
    int num1Size = findFileSize(num1);
    uint8_t *number2 = numberToArray(num2);
    int num2Size = findFileSize(num2);

    uint8_t *result;
    int i=num1Size-1,j=num2Size-1,resSize;
    uint8_t sum = 0;
    
    if(num1Size > num2Size){
        result = makeArray(num1Size+1);
        resSize = num1Size;
        while(j>=0){
            sum += *(number1+i) + *(number2+j);
            //if sum is greater than 9 take the mod and set sum as 1
            if(sum > 9){
                *(result + resSize) = sum%10;
                sum = 1;
            }else{
                *(result + resSize) = sum;
                sum = 0;
            }
            i--,j--,resSize--;
        }
        //add the remaining elements of the larger number to the array
        while(i>=0){
            if(sum == 1){
                *(result + resSize) = *(number1+i) + 1;
                sum = 0;
            }else{
                *(result + resSize) = *(number1+i);
            }
            i--,resSize--;
        }
        while(resSize>=0){
            *(result + resSize) = sum;
            resSize--;
        }
        resSize = num1Size + 1;
    }else{
        result = makeArray(num2Size+1);
        resSize = num2Size;
        while(i>=0){
            sum += *(number1+i) + *(number2+j);
            if(sum > 9){
                *(result + resSize) = sum%10;
                sum = 1;
            }else{
                *(result + resSize) = sum;
                sum = 0;
            }
            i--,j--,resSize--;
        }
        while(j>=0){
            if(sum == 1){
                *(result + resSize) = *(number2+j) + 1;
                sum = 0;
            }else{
                *(result + resSize) = *(number2+j);
            }
            j--,resSize--;
        }
        while(resSize>=0){
            *(result + resSize) = sum;
            resSize--;
        }
        resSize = num2Size + 1;
    }
    //export the resulting array to file
    resultToFile(result,resSize);
    free(number1),free(number2),free(result);
}

void subtraction(FILE *num1, FILE *num2){

    uint8_t *number1 = numberToArray(num1);
    int num1Size = findFileSize(num1);
    uint8_t *number2 = numberToArray(num2);
    int num2Size = findFileSize(num2);

    uint8_t *result;
    int i=num1Size-1,j=num2Size-1;
    int resSize,k,isExclusion = 0;

    if(num1Size == num2Size){
        result = makeArray(num1Size);
        resSize = num1Size;
        int bigNum;
        //If the digits are equal, find which one is greater
        for(i=0;i<num1Size;i++){
            if(*(number1+i) > *(number2+i)){
                bigNum = 0;
                break;
            }else if(*(number2+i) > *(number1+i)){
                bigNum = 1;
                break;
            }
        }
        if(bigNum == 0){
            for(i = num1Size-1;i>=0;i--){
                //If the element of the number to be subtracted is greater, take it as a debit
                if(*(number2+i) > *(number1+i)){
                    isExclusion = 1;
                    *(result+i) = 10 + *(number1+i) - *(number2+i);
                }else{
                    *(result+i) = *(number1+i) - *(number2+i);
                }
                if(isExclusion == 1){
                    k = i-1;
                    //If the borrowed number is equal to 0, set it as 9 and borrow
                    if(*(number1+k) == 0){
                        *(number1+k) = 9;
                        isExclusion = 1;
                    }else{
                        *(number1+k) -= 1;
                        isExclusion = 0;
                    }
                }
            }
        }else if(bigNum == 1){
            for(i = num1Size-1;i>=0;i--){
                if(*(number1+i) > *(number2+i)){
                    isExclusion = 1;
                    *(result+i) = 10 + *(number2+i) - *(number1+i);
                }else{
                    *(result+i) = *(number2+i) - *(number1+i);
                }
                if(isExclusion == 1){
                    k = i-1;
                    if(*(number2+k) == 0){
                        *(number2+k) = 9;
                        isExclusion = 1;
                    }else{
                        *(number2+k) -= 1;
                        isExclusion = 0;
                    }
                }
            }
        }
    }else if(num1Size > num2Size){
        result = makeArray(num1Size);
        resSize = num1Size;
        while(j >= 0){
            if(*(number2+j) > *(number1+i)){
                isExclusion = 1;
                *(result+i) = 10 + *(number1+i) - *(number2+j);
            }else{
                *(result+i) = *(number1+i) - *(number2+j);
            }
            if(isExclusion == 1){
                k = i-1;
                if(*(number1+k) == 0){
                    *(number1+k) = 9;
                    isExclusion = 1;
                }else{
                    *(number1+k) -= 1;
                    isExclusion = 0;
                }
            }
            i--, j--;
        }
        while(i >= 0){
            if(isExclusion == 1){
                k = i-1;
                if(*(number1+k) == 0){
                    *(number1+k) = 9;
                    isExclusion = 1;
                }else{
                    *(number1+k) -= 1;
                    isExclusion = 0;
                }
            }
            *(result+i) = *(number1+i);
            i--;
        }
    }else{
        result = makeArray(num2Size);
        resSize = num2Size;
        while(i >= 0){
            if(*(number1+i) > *(number2+j)){
                isExclusion = 1;
                *(result+j) = 10 + *(number2+j) - *(number1+i);
            }else{
                *(result+j) = *(number2+j) - *(number1+i);
            }
            if(isExclusion == 1){
                k = j-1;
                if(*(number2+k) == 0){
                    *(number2+k) = 9;
                    isExclusion = 1;
                }else{
                    *(number2+k) -= 1;
                    isExclusion = 0;
                }
            }
            i--, j--;
        }
        while(j >= 0){
            if(isExclusion == 1){
                k = j-1;
                if(*(number2+k) == 0){
                    *(number2+k) = 9;
                    isExclusion = 1;
                }else{
                    *(number2+k) -= 1;
                    isExclusion = 0;
                }
            }
            *(result+j) = *(number2+j);
            j--;
        }
    }
    //export the resulting array to file
    resultToFile(result, resSize);
    free(number1),free(number2),free(result);
}

void resultToFile(uint8_t *array, int size){

    //open results.txt in write mode
    sonuc = fopen("sonuclar.txt","w");
    int startWithZero = 1;
    if(sonuc == NULL){
        printf("File could not found");
        exit(1);
    }else{
        for(int i=0; i<size; i++){
            //if array starts with 0, not write 0 to file
            if(*(array+i) == 0 && startWithZero == 1){
                //if result is 0 write to file
                if(i == size - 1){
                    fprintf(sonuc,"%d",*(array+i));
                }else{
                    if(*(array+i+1) == 0) startWithZero = 1;
                    else startWithZero = 0;
                }
            }else{
                fprintf(sonuc,"%d",*(array+i));
                startWithZero = 0;
            }
        }
    }
    fclose(sonuc);
}

void readFromFile(FILE **file, char *fileName){

    //open file in read mode
    *file = fopen(fileName,"r");
    if(*file == NULL){
        printf("File could not found");
        exit(1);
    }else{
        while(!feof(*file)){
            char ch = fgetc(*file);
            printf("%c",ch);
        }
    }
    fclose(*file);
}
