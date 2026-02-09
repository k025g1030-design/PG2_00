#include <stdio.h>

/*
[確認課題]5-2. ファイル読み込み
*/
int main() {
    FILE* fp;
    const char* configPath = "test.cnf";
    int err;
    char buffer[256];
    err = fopen_s(&fp, configPath, "r");
    if (err != 0) {
        printf("ファイルオープン失敗\n");
        return err;
    } else {
        fscanf_s(fp, "%s", buffer, (unsigned int)sizeof(buffer));
        printf("ファイル内容：%s\n", buffer);
    }

    fclose(fp);


    return 0;
}
