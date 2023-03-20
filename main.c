#include "func.h"
#define INTMAX_MAX  999
#define INTMAX_MIN  -999
int main(int argc, char **argv) {
    if(argv[1] == NULL){
        printf("\nFilename not found\n");
        return 0;
    }
    int SIZE, t = 0;
    printf("Input numbers of elements: ");
    SIZE = input(1, INTMAX_MAX);
    printf("Fill file: \n");
    fill_file(argv[1], SIZE);
    while(t != 2) {
        int choose;
        printf("\nAvailable tasks:\n1.Print  binary fle.\x1b[32m(Completed)\x1b[0m");
        printf("\n2.Sum of even numbers in binary file.\x1b[32m(Completed)\x1b[0m");
        printf("\n3.Delete even numbers.\x1b[32m(Completed)\x1b[0m");
        printf("\n4.Sort elements > K.\x1b[32m(Completed)\x1b[0m\n");
            printf("Choose task: ");
            choose = input(1, 4);
        if (choose == 1) {
            task1(argv[1], SIZE);
        } else if (choose == 2) {
            task2(argv[1], SIZE);
        } else {
            if (choose == 3) {
                task3(argv[1], SIZE);
            } else {
                if (choose == 4) {
                    task4(argv[1], SIZE);
                }
            }
        }
        printf("\n\nDo you want to choose one more task?\n1.Yes\n2.No\n");
        t = input(1,2);
    }
    return 0;
}