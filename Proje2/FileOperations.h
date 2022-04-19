/*
    @proje2
    @iki adet büyük sayı arasında işlem yapma
    @21.01.2022
*/
#ifndef FILEOPERATIONS
#define FILEOPERATIONS

uint8_t *numberToArray(FILE *name);

uint8_t *makeArray(int size);

int findFileSize(FILE *name);

void addition(FILE *num1, FILE *num2);

void subtraction(FILE *num1, FILE *num2);

void resultToFile(uint8_t *array, int size);

void readFromFile(FILE **file, char *fileName);

#endif
