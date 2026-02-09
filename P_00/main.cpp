#include <stdio.h>

int Power(int p) {
    return p * p;
}

float Power(float p) {
    return p * p;
}

int main() {
    int powerInt = Power(2);
    float powerFloat = Power(2.0f);
    printf("引数int   Power関数 ＝ %d\n", powerInt);
    printf("引数float Power関数 ＝ %f\n", powerFloat);
}