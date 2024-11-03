#include <stdio.h>
#include "renderer.h"

void renderFile(char lines[10][20])
{
    for (int i = 0; i < 10; i++)
    {
        printf("\u001b[33m%d\033[0m", i);
        printf(" ");

        for (int j = 0; j < 20; j++)
        {
            printf("%c", lines[i][j]);
        }
        printf("\n");
    }
}