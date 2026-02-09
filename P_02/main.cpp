/**
 *[確認課題]2-2. 変数とアドレス
 **/
#include <stdio.h>


int main() {
    int *pa = nullptr;
    int *pb = nullptr;
    int a = 5;
    int b = 0;
    pa = &a;
    pb = &b;
    printf("a(整数型)：%d\n", a);
    printf("b(整数型)：%d\n", b);
    printf("pa(アドリス)：%p\n", pa);
    printf("pb(アドリス)：%p\n", pb);  
    printf("\n");

    pa = pb;
    printf("pa(整数型)：%d\n", *pa);
    printf("pb(整数型)：%d\n", *pb);
    printf("pa(アドリス)：%p\n", pa);
    printf("pb(アドリス)：%p\n", pb); 
    printf("\n");

    pb = &a;
    printf("a(整数型)：%d\n", a);
    printf("b(整数型)：%d\n", b);
    printf("pa(アドリス)：%p\n", pa);
    printf("pb(アドリス)：%p\n", pb);




}