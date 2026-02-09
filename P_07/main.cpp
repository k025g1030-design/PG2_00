
#include <stdio.h>

int main()
{

    const char* color[] = {
        "YELLOW",
        "RED",
        "BLUE",
        "GREEN",
        "BLACK",
        "WHITE",

    };
    const char* p;
    const char** pp;
   

    p = color[4];
    printf("%s\n" , p);

    p++;
    printf("%s\n", p);

    pp = color;

    printf("%s\n", *(pp) + 2);

    printf("%s\n", *(pp + 2));

    printf("%c\n", *(*(pp + 3) + 1));

}
