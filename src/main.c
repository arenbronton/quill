#include <stdio.h>
#include <windows.h>
#include "renderer.h"

// void printLines(char lines[10][20])
// {
//     for (int i = 0; i < 10; i++)
//     {
//         // printf("\u001b[33 %d", i);
//         // printf("\u001b[37] ");

//         printf("%d ", i);
//         for (int j = 0; j < 20; j++)
//         {
//             printf("%c", lines[i][j]);
//         }
//         printf("\n");
//     }
// }

void moveCursor(short x, short y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hConsole, position);
}

int main(void)
{
    // hInput is a pointer to the std input stream
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    // LINES
    char lines[10][20] = {{' '}};
    int currentLine = 0;
    int currentRow = 0;

    INPUT_RECORD inputRecord;
    DWORD events;
    while (1)
    {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
        {
            char c = inputRecord.Event.KeyEvent.uChar.AsciiChar;
            if (c == 'q')
                break;

            if (c == '\b')
            {
                if (currentRow == 0)
                {
                    lines[currentLine][currentRow] = ' ';
                    currentLine--;
                    currentRow = 19;

                    while (currentRow > 0 && lines[currentLine][currentRow] == ' ')
                    {
                        currentRow--;
                    }

                    currentRow++;
                }
                else
                {
                    currentRow--;
                    lines[currentLine][currentRow] = ' ';
                }
            }
            else if (c == '\r')
            {
                currentRow = 0;
                currentLine++;
            }
            else
            {
                lines[currentLine][currentRow] = c;
                currentRow++;
            }

            if (currentRow < 0)
                currentRow = 0;
            if (currentLine < 0)
                currentLine = 0;

            system("cls");
            renderFile(lines);
        }
    }

    SetConsoleMode(hInput, mode);

    return 0;
}