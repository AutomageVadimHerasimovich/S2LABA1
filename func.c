#include "func.h"
#define INTMAX_MAX  9999
#define INTMAX_MIN  -9999

int input(int min, int max){
    int x;
    while (scanf("%d", &x) != 1 || x < min || x > max || x % 1 != 0 || getchar() != '\n') {
        printf("Error. Try again: ");
        rewind(stdin);
    }
    return x;
}

void fill_file(char* filename, int n){
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        printf("Input %d element: ", i + 1);
        arr[i] = input(INTMAX_MIN, INTMAX_MAX);
    }
    FILE* f;
    f=fopen(filename, "wb+");
    fwrite(arr, sizeof(int), n, f);
    fflush(f);
    fclose(f);
}

void read_file(char* filename, int n){
    FILE* f;
    f=fopen(filename, "r+b");
    int num;
    for (int i = 0; i < n; ++i) {
        fread(&num, sizeof(int), 1,f);
        printf("%d ", num);
    }
    fclose(f);
}
/*int catter(char* filename, int n){
    FILE* f;
    fpos_t pos;
    int num, counter=0;
    f=fopen(filename, "rb+");
    int size = sizeof(int);
    fseek(f, 0, SEEK_END);
    pos = ftell(f);
    int len = pos / size;
    rewind(f);
    for(int i=0; i<len;++i){
        fseek(f,i * size, SEEK_SET);
        fread(&num, size,1,f);
        if (num%2==0){
            counter+=4;
        }
    }
fseek(f,0,SEEK_CUR);
ftruncate(fileno(f),pos-counter);
n=len-(counter/4);
    return n;
}*/

int even_deleter(char* filename, int n) {
    FILE *f;
    fpos_t pos;
    int num, tmp, counter = 0;
    f = fopen(filename, "rb+");

    int size = sizeof(int);

    fseek(f, 0, SEEK_END);
    pos = ftell(f);
    int len = pos / size;
    rewind(f);
    for (int i = 0; i < len; ++i) {
        fseek(f, i * size, SEEK_SET);
        fread(&num, size, 1, f);
        if (num % 2 == 0) {
            counter++;
        }
        for (int i = 0; i < len; i++) {
            for (int j = 0; j <= len - 2; ++j) {
                fseek(f, j * size, SEEK_SET);
                fread(&num, size, 1, f);
                fread(&tmp, size, 1, f);
                if (num % 2 == 0) {
                    fseek(f, j * size, SEEK_SET);
                    fwrite(&tmp, size, 1, f);
                    fwrite(&num, size, 1, f);
                }
            }
        }
    }
    n=len-counter;
    int *arr;
    arr= malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        fseek(f, i * size, SEEK_SET);
        fread(&num, size, 1, f);
        arr[i]=num;
    }
    fclose(f);
    f=fopen(filename,"wb");
    //printf("\n\nTest: ");
    for (int i = 0; i < n; ++i) {
        fwrite(&arr[i], size, 1, f);
    }
    fclose(f);
    return n;
}

    int bubble_sort(char *filename, int k) {
        FILE *f;
        fpos_t pos;
        int num, tmp, n;
        f = fopen(filename, "rb+");

        int size = sizeof(int);

        fseek(f, 0, SEEK_END);
        pos = ftell(f);
        int len = pos / size;
        rewind(f);

        for (int i = 0; i < len; i++) {
            for (int j = 0; j <= len - 2; ++j) {
                fseek(f, j * size, SEEK_SET);
                fread(&num, size, 1, f);
                fread(&tmp, size, 1, f);
                if (num < tmp && num > k && tmp > k) {
                    fseek(f, j * size, SEEK_SET);
                    fwrite(&tmp, size, 1, f);
                    fwrite(&num, size, 1, f);
                }
            }
        }
        fseek(f, 0, SEEK_END);
        pos = ftell(f);
        n = pos / size;
        rewind(f);
        fclose(f);
        return n;
    }

    void task1(char *filename, int n) {
        printf("\nFile state: ");
        read_file(filename, n);
    }

    void task2(char *filename, int n) {
        printf("\nFile state: ");
        read_file(filename, n);
        FILE *f;
        f = fopen(filename, "r+b");
        int num;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            fseek(f, i * sizeof(int), SEEK_SET);
            fread(&num, sizeof(int), 1, f);
            if (num % 2 == 0) {
                sum += num;
            }
        }
        printf("\nSUM = %d\n", sum);
        fclose(f);
    }

    void task3(char *filename, int n) {
        printf("\nFile state: ");
        read_file(filename, n);
        n=even_deleter(filename, n);
        printf("\n\nCorrected file: ");
        read_file(filename, n);
    }

    void task4(char *filename, int n) {
        printf("\nInput K : ");
        int k = input(INTMAX_MIN, INTMAX_MAX);
        printf("\nSorted file: ");
        n=bubble_sort(filename, k);
        read_file(filename, n);
    }