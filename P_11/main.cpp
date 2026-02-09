#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 [確認課題] 6. 単方向リスト
*/

typedef struct Cell {
    char* val;
    Cell* next;
};

void create(Cell* endCell, char* val) {
    if (endCell == nullptr) {
        return;
    }

    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    newCell->val = val;
    newCell->next = nullptr;

    while (endCell->next != nullptr) {
        endCell = endCell->next;
    }

    endCell->next = newCell;
}

void index(Cell* endCell) {
    if (endCell == nullptr) {
        return;
    }

    printf("[");
    while (endCell->next != nullptr) {
        endCell = endCell->next;
        printf("\"%s\"", endCell->val);
        if (endCell->next != nullptr) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    Cell* head = (Cell*)malloc(sizeof(Cell));
    head->next = nullptr;

    // buffer for input
    char buffer[256];

    while (1) {
        printf("好きなお寿司を入力してください。 ('q' 止め): ");
        scanf_s("%255s", buffer, (unsigned)_countof(buffer));

        if (buffer[0] == 'q' && buffer[1] == '\0') {
            break;
        }

        // Allocate memory for val and copy buffer
        head->val = (char*)malloc(strlen(buffer) + 1);
        strcpy_s(head->val, strlen(buffer) + 1, buffer);

        create(head, head->val);

        index(head);
    }
    return 0;
}
