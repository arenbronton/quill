#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "quill.h"
#include "structures.h"
#include <windows.h>

void renderFile(char lines[20][30], EditorMode *editMode, Stack *command_buffer)
{
    for (int i = 0; i < 10; i++)
    {
        printf("\033[33m%d\033[0m", i);
        printf(" ");

        for (int j = 0; j < 20; j++)
        {
            printf("%c", lines[i][j]);
        }
        printf("\n");
    }

    // SHOW EDIT MODE
    switch (editMode->mode)
    {
    case NORMAL:
        printf("NORMAL\t%s", command_buffer->collection);
        break;
    case VISUAL:
        printf("VISUAL\n");
        break;
    case INSERT:
        printf("INSERT\n");
        break;
    }
}

void moveCursor(short x, short y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hConsole, position);
}

void backspaceToPreviousLine(char *previousLine, int previousLineIndex)
{
    // Look for last character in the line
    int xPos = 0;
    for (int i = strlen(previousLine) - 1; i >= 0; i--)
    {
        if (previousLine[i] == ' ')
        {
            xPos = strlen(previousLine - i);
            break;
        }
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {xPos, previousLineIndex};
    SetConsoleCursorPosition(hConsole, position);
}