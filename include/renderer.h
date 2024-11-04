#pragma once

#include "quill.h"
#include "structures.h"

void renderFile(char lines[20][30], EditorMode *editMode, Stack *command_buffer);
void moveCursor(short x, short y);
void backspaceToPreviousLine(char *previousLine, int previousLineIndex);