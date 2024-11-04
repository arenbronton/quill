#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "renderer.h"
#include "quill.h"
#include "structures.h"

void ensure_cursor_bounds(EditorMode *editMode)
{
    if (editMode->cursor_x < 0)
        editMode->cursor_x = 0;
    if (editMode->cursor_y < 0)
        editMode->cursor_y = 0;
}

int main(int argc, char *argv[])
{
    // hInput is a pointer to the std input stream
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    // Terminal Input Mode
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    // LINES
    char lines[20][30] = {{' '}};

    // EDITOR MODE
    EditorMode editMode;
    editMode.mode = NORMAL;
    editMode.cursor_x = 0;
    editMode.cursor_y = 0;
    // COMMAND BUFFER
    Stack *command_buffer = create_stack(5);

    // Input Events
    INPUT_RECORD inputRecord;
    DWORD events;

    while (1)
    {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
        {
            char c = inputRecord.Event.KeyEvent.uChar.AsciiChar;

            // HANDLE COMMANDS
            if (editMode.mode == NORMAL)
            {
                if (c == '\b')
                    pop_ignore(command_buffer);

                else if (c == '\r')
                {
                    if (strcmp(command_buffer->collection, ":q") == 0)
                    {
                        break;
                    }
                }
                else
                    push(command_buffer, c);
            }

            // * HANDLE BACKSPACE
            else if (c == '\b')
            {
                if (editMode.cursor_x == 0)
                {
                    lines[editMode.cursor_y][editMode.cursor_x] = ' ';
                    editMode.cursor_y--;
                    editMode.cursor_x = 19;

                    while (editMode.cursor_x > 0 && lines[editMode.cursor_y][editMode.cursor_x] == ' ')
                    {
                        editMode.cursor_x--;
                    }

                    editMode.cursor_x++;
                }
                else
                {
                    editMode.cursor_x--;
                    lines[editMode.cursor_y][editMode.cursor_x] = ' ';
                }
            }

            // * HANDLE ENTER PRESSED
            else if (c == '\r')
            {
                editMode.cursor_x = 0;
                editMode.cursor_y++;
            }
            else
            {
                lines[editMode.cursor_y][editMode.cursor_x] = c;
                editMode.cursor_x++;
            }

            ensure_cursor_bounds(&editMode);
        }

        system("cls");
        renderFile(lines, &editMode, command_buffer);
        moveCursor(editMode.cursor_x + 1, editMode.cursor_y);
    }

    SetConsoleMode(hInput, mode);

    // END PROGRAM
    system("cls");
    destroy_stack(command_buffer);

    return 0;
}