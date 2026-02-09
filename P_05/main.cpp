/**
 * [確認課題]4 - 1. 配列とポインタ
 **/
#include <iostream>

void PrintArray(int* array){
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", array[i]);
        printf("%p\n", &array[i]);
    }
}

int main(){
    int array[5] = { 5, 3, 8, 12, 2 };
    int* p_array = array;
    printf("------------プログラム1-------------\n");

    for (int i = 0; i < 5; ++i) {
        printf("%d\n", array[i]);
        printf("%p\n", &array[i]);
    }

    printf("--------------------------------\n");
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", p_array[i]);
        printf("%p\n", &p_array[i]);
    }

    printf("------------プログラム2-------------\n");

    int array2[5] = { 5, 3, 8, 12, 2 };
    p_array = array2;

    PrintArray(p_array);




    return 0;
}

