/**
 * [確認課題]PG2_3-2. 再帰関数
 **/
#include <iostream>

int Multiple(int bottom, int index) {
    if (index > 0) {
        return bottom * Multiple(bottom, --index);
    }
    return 1;
}

int main() {
    int b = 0;
    int i = 0;
    //std::cout << "底を入力：";
    printf("底を入力：");
    scanf_s("%d", &b);
    //std::cout << "指数を入力：";
    printf("指数を入力：");
    scanf_s("%d", &i);
    //std::cout << b << "の" << i << "乗は" << Multiple(b, i) << std::endl;
    printf("%dの%d乗は%d\n", b, i, Multiple(b, i));
}
