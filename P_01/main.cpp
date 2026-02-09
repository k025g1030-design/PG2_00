#include <stdio.h>

/*
解除は &= ~フラグ
付与は |= フラグ
切替は ^= フラグ
*/
enum PlayerState {
    SLEEP = 0b1000,
    STONE = 0b0100,
    POISON = 0b0010,
    DEATH = 0b0001,
    
};

void print_state(int state) {
    printf("state = %d\n", state);
    if (state & SLEEP)  printf("眠り状態\n");
    if (state & STONE)  printf("石化状態\n");
    if (state & POISON) printf("毒状態\n");
    if (state & DEATH)  printf("戦闘不能状態\n");
    if (state == 0)     printf("正常状態\n");
}

int main() {
    int state = 0b1010; // SLEEP + POISON
    print_state(state);

    printf("\n--- 毒を解除 ---\n");
    state &= ~POISON; // 毒を解除
    print_state(state);

    printf("\n--- 石化を追加 ---\n");
    state |= STONE;   // 石化を追加
    print_state(state);

    printf("\n--- 眠りをトグル ---\n");
    state ^= SLEEP;   // 眠りをトグル（解除）
    print_state(state);


    printf("\n--- 死亡をトグル ---\n");
    state ^= DEATH;  
    print_state(state);

    printf("\n--- 死亡をトグル（切替） ---\n");
    state ^= DEATH;
    print_state(state);

    printf("\n--- 石化を解除 ---\n");
    state &= ~STONE;  // 石化だけ解除
    print_state(state);

    printf("\n--- 眠りと毒と石化をまとめて解除 ---\n");
    state = SLEEP | POISON | STONE; // 眠り＋毒＋石化
    print_state(state);

    state &= ~(SLEEP | POISON); // 眠りと毒を同時解除
    print_state(state);



    return 0;
}
